````markdown
# 🧵 C07 – exx09  
## `trim left, trim right, trim all` – peer_explanation.md

---

## 1. 🧠 Exercise Overview

### 🔹 Goal

We want to:

1. Read a line of text from standard input (`stdin`), dynamically (we don’t know the length in advance).
2. Implement **three trimming functions** that work **in-place** on a `char *`:
   - `ft_trim_left`  → remove leading spaces/tabs  
   - `ft_trim_right` → remove trailing spaces/tabs  
   - `ft_trim_all`   → remove both sides, by combining the two above
3. Show the result for each kind of trim in `main`.

The trimming is done **without allocating new strings** for the trims.  
We reuse the same buffer and modify it directly.

---

## 2. 🧬 High-level Data Flow

1. `read_string()`  
   - Reads characters until `'\n'`  
   - Stores them in a dynamically growing buffer  
   - Returns a **heap-allocated** `char *` that you must `free()` later

2. `ft_trim_left()` / `ft_trim_right()` / `ft_trim_all()`  
   - Take that same pointer and **modify its contents** in place  
   - Return the same pointer (for convenience / chaining)

3. `main()` calls:
   - First: `read_string()` → `ft_trim_left()`  
   - Second: `read_string()` → `ft_trim_right()`  
   - Third: `read_string()` → `ft_trim_all()`  

Each time, after printing, the buffer is freed.

Think of it like this:

```text
stdin -> [read_string] -> "   Hello 42  "  (heap)
              |
         [ft_trim_*] edits SAME memory
              |
            "Hello 42"
````

---

## 3. 🛠 Utility Functions

### 3.1 `ft_putchar`

```c
void	ft_putchar(char c)
{
	write(1, &c, 1);
}
```

* Very simple: writes a single character to **file descriptor 1** (standard output).
* We use it everywhere for output to respect the 42 style (no `printf`).

---

### 3.2 `ft_putstr`

```c
void	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}
```

* If `str` is `NULL`, we **do nothing** → safety check.
* Otherwise, loop until we hit the terminating `'\0'`.
* Print each character with `ft_putchar`.

> Memory picture:
> `str` points to an array of chars on the **heap**, but `ft_putstr` only **reads** from it; it does not modify.

---

### 3.3 `ft_strncpy`

```c
char	*ft_strncpy(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	// Only copy if src is not NULL
	if (!src || !dst)
		return (dst);
	while (i < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
```

* This function is **not used** in the rest of the program, but let’s still understand it:

1. Early check: if `src == NULL` or `dst == NULL` → just return `dst` (no copy, avoid crash).
2. Copy at most `size` characters, **stopping earlier** if `src[i] == '\0'`.
3. After the loop, explicitly write a `'\0'` to terminate the destination string.

> 🔑 Important: It **assumes** `dst` points to memory large enough to hold at least `size + 1` chars.
> This function does **not** allocate memory; it only copies.

---

## 4. 📦 Dynamic Reallocation: `ft_reall_str`

```c
char *ft_reall_str(char *str, size_t *size)
{
	char	*new_str;
	size_t	new_size;
	size_t	old_size;

	old_size = *size;
	new_size = (old_size == 0) ? 32 : old_size * 2;
	
	new_str = (char*)malloc(sizeof(char) * (new_size + 1));
	if (!new_str)
		return (NULL);
	
	if (str)
	{
		// Copy old data into new buffer
		int i = 0;
		while (i < (int)old_size && str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = '\0';
		free(str);
	}
	else
		new_str[0] = '\0';

	*size = new_size;
	return (new_str);
}
```

### 4.1 What is this doing?

This is a **custom `realloc`-like** helper, specialized for our string buffer:

* `str`      → old buffer (may be `NULL` if first allocation)
* `*size`    → old capacity (how many chars it can hold, not including `'\0'`)
* Returns a **new** buffer with **bigger capacity** and copies the old contents.

### 4.2 Step-by-step

1. **Read old size**

   ```c
   old_size = *size;
   ```

2. **Compute new size**

   ```c
   new_size = (old_size == 0) ? 32 : old_size * 2;
   ```

   * First time: if `old_size == 0` → start with capacity `32`.
   * Later: double the capacity each time (`32 → 64 → 128 → ...`).
     This is a classic dynamic array growth strategy.

3. **Allocate new buffer**

   ```c
   new_str = (char*)malloc(sizeof(char) * (new_size + 1));
   ```

   * `new_size` space for characters
   * `+1` for the **null terminator**
   * If allocation fails → return `NULL` (caller must handle it).

4. **Copy old content (if any)**

   ```c
   if (str)
   {
       int i = 0;
       while (i < (int)old_size && str[i])
       {
           new_str[i] = str[i];
           i++;
       }
       new_str[i] = '\0';
       free(str);
   }
   else
       new_str[0] = '\0';
   ```

   * If we already had an old buffer `str`:

     * Copy characters until we hit `old_size` or a `'\0'`.
     * Terminate the new string.
     * Free the old buffer to avoid memory leaks.
   * If `str == NULL`, we just create an **empty string** (`new_str[0] = '\0'`).

5. **Update capacity and return**

   ```c
   *size = new_size;
   return (new_str);
   ```

### 4.3 Memory diagram

Imagine we have this situation:

```text
str (old)  capacity = 4
 contents: "ABC\0"
```

We need more space → call `ft_reall_str(str, &size)`:

```text
[before]
 str  ───► [ 'A' 'B' 'C' '\0' ? ? ]
 size = 4

[new allocation]
 new_size = 8
 new_str ─► [ 'A' 'B' 'C' '\0' ? ? ? ? ]
 str is freed
 size = 8
```

---

## 5. 📥 Dynamic Reader: `read_string`

```c
char *read_string(void)
{
	char	  ch;
	size_t	length;
	char	  *buffer;
	size_t	buffer_size;

	length = 0;
	buffer = NULL;
	buffer_size = 0;

	ft_putstr("Please Enter Your String:\n");

	while (read(0, &ch, 1) > 0 && ch != '\n')
	{
		// +1 for the character, +1 for the null terminator
		if (length + 2 >= buffer_size)
		{
			buffer = ft_reall_str(buffer, &buffer_size);
			if (!buffer)
				return (NULL);
		}
		buffer[length++] = ch;
	}

	if (buffer)
		buffer[length] = '\0';
	return (buffer);
}
```

### 5.1 Variables

* `ch`          → one character read from stdin.
* `length`      → number of characters **currently stored** (string length, excluding `'\0'`).
* `buffer`      → pointer to our dynamic string on the heap.
* `buffer_size` → current capacity (how many chars we *can* store, not counting `'\0'`).

### 5.2 Loop condition

```c
while (read(0, &ch, 1) > 0 && ch != '\n')
```

* `read(0, &ch, 1)` reads **1 byte** from stdin into `ch`.
* If `read` returns > 0 → we got a character.
* We stop reading when:

  * `read` fails or reaches EOF, or
  * the user presses **Enter** (so `ch == '\n'`).

### 5.3 Capacity check: why `length + 2`?

```c
if (length + 2 >= buffer_size)
```

We’re about to add **one more char**, and we always want room for the `'\0'`.

* `+1` for the new character
* `+1` for the null terminator
  → `length + 2` is the **minimum total space** we need.

If that would go beyond `buffer_size`, we grow the buffer:

```c
buffer = ft_reall_str(buffer, &buffer_size);
if (!buffer)
    return (NULL);
```

### 5.4 Store character

```c
buffer[length++] = ch;
```

* Put `ch` at index `length`.
* Then increment `length`.

### 5.5 Final null terminator

```c
if (buffer)
    buffer[length] = '\0';
```

Once the loop finishes, we put `'\0'` after the **last valid character**.

> Result: `buffer` now holds a **proper C-string** allocated on the heap, ready to be passed to trimming functions and later `free()`-d.

---

## 6. 📏 `ft_strlen`

```c
int ft_strlen(char *str)
{
	int i = 0;
	if (!str) return (0);
	while (str[i])
		i++;
	return (i);
}
```

* If `str == NULL`, returns `0` (safety).
* Otherwise, counts characters until the first `'\0'`.

This is used in `ft_trim_right` to find where the string ends.

---

## 7. ✂️ Trimming Functions

### 7.1 `ft_trim_left`

```c
char *ft_trim_left(char *str)
{
	int i = 0;
	int j = 0;

	if (!str)
		return (NULL);

	while (str[i] == ' ' || str[i] == '\t')
		i++;

	if (i == 0)
		return (str);

	while (str[i])
		str[j++] = str[i++];

	str[j] = '\0';
	return (str);
}
```

#### 7.1.1 Idea

We skip leading spaces/tabs, then **shift the remaining characters** to the beginning of the string, overwriting the old content.

#### 7.1.2 Step-by-step

1. Safety:

   ```c
   if (!str)
       return (NULL);
   ```

2. Find first non-space/tab:

   ```c
   while (str[i] == ' ' || str[i] == '\t')
       i++;
   ```

   After this loop:

   * `i` points to the first non-space/tab character, or to `'\0'` if the whole string is spaces/tabs.

3. If nothing to trim:

   ```c
   if (i == 0)
       return (str);
   ```

   * This means the first char was already not a space/tab; no change needed.

4. Shift characters left:

   ```c
   while (str[i])
       str[j++] = str[i++];
   ```

   * Copy from `str[i]` to `str[j]`.
   * Both `i` and `j` move forward.
   * This compresses the string, removing leading blanks.

5. Null-terminate:

   ```c
   str[j] = '\0';
   ```

#### 7.1.3 Memory diagram

Example: `"   Hello\t42"` (3 spaces, then Hello, tab, 42)

Before:

```text
index: 0   1   2   3   4   5   6   7   8   9   10
value: ' ' ' ' ' ' 'H' 'e' 'l' 'l' 'o' '\t' '4' '2' '\0'
           ^i
```

After skipping spaces: `i = 3`.

Now copy:

```text
str[0] = str[3] = 'H'
str[1] = str[4] = 'e'
str[2] = str[5] = 'l'
...
```

Result:

```text
index: 0   1   2   3   4   5   6   ...
value: 'H' 'e' 'l' 'l' 'o' '\t' '4' '2' '\0' ...
```

---

### 7.2 `ft_trim_right`

```c
char *ft_trim_right(char *str)
{
	int len;

	if (!str || (len = ft_strlen(str)) == 0)
		return (str);

	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
		len--;

	str[len] = '\0';
	return (str);
}
```

#### 7.2.1 Idea

We find the last non-space/tab character and put `'\0'` **right after it**, effectively cutting off trailing blanks.

#### 7.2.2 Step-by-step

1. Handle `NULL` or empty string:

   ```c
   if (!str || (len = ft_strlen(str)) == 0)
       return (str);
   ```

2. Move `len` backward while the last char is space/tab:

   ```c
   while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
       len--;
   ```

   After this:

   * `len` is the index where the **trimmed string should end**.

3. Place terminator:

   ```c
   str[len] = '\0';
   ```

Example:

```text
"Hello 42   "
 len = 10 (before '\0')

Check str[9], str[8], str[7] → spaces → decrement len each time.
Stop when we reach the '2' index.
Then put '\0' right after '2'.
```

---

### 7.3 `ft_trim_all`

```c
char *ft_trim_all(char *str)
{
	return (ft_trim_left(ft_trim_right(str)));
}
```

* First: `ft_trim_right(str)` → trims the **end**.
* Then `ft_trim_left(...)` → trims the **beginning** of the already right-trimmed string.
* Returns the same pointer (both functions are in-place).

> Important: Order is `right` then `left`.
> For spaces-only string `"   "`:
>
> * Right trim makes it `""` (empty string).
> * Left trim then sees `i == 0`, and just returns.

---

## 8. 🧪 `main` Walkthrough

```c
int main(void)
{
	char *input;

	/* --- LEFT TRIM SECTION --- */
	input = read_string();
	if (input)
	{
		ft_putstr("\nOriginal: \"");
		ft_putstr(input);
		ft_putstr("\"\n");

		ft_trim_left(input);
		ft_putstr("Left Trim: \"");
		ft_putstr(input);
		ft_putstr("\"\n");
		free(input);
	}

	/* --- RIGHT TRIM SECTION --- */
	input = read_string();
	if (input)
	{
		ft_trim_right(input);
		ft_putstr("Right Trim: \"");
		ft_putstr(input);
		ft_putstr("\"\n");
		free(input);
	}

	/* --- TRIM ALL SECTION --- */
	input = read_string();
	if (input)
	{
		ft_trim_all(input);
		ft_putstr("Trim All: \"");
		ft_putstr(input);
		ft_putstr("\"\n");
		free(input);
	}

	return (0);
}
```

### 8.1 Important observations

* We call `read_string()` **three times**:

  1. For testing left trim
  2. For testing right trim
  3. For testing both

* After each section, we call `free(input);` → no memory leak.

* All trims are **in-place**:

  * The value of `input` (the pointer) is the same before and after trimming.
  * Only the contents of the allocated memory change.

---

## 9. 🧠 Typical Test Cases

Try entering these lines for each prompt:

1. `"   Hello 42"`

   * Left trim → `"Hello 42"`

2. `"Hello 42   "`

   * Right trim → `"Hello 42"`

3. `"   Hello 42   "`

   * Trim all → `"Hello 42"`

4. `"NoSpaces"`

   * Any trim → `"NoSpaces"`

5. `"   \t  "` (only spaces/tabs)

   * Trim all → `""` (empty string)

---

## 10. ❓ Peer Evaluation Q&A

Here are some typical questions you might get in a peer evaluation, with short, precise answers.

---

### Q1: Where is the string stored, and who is responsible for freeing it?

* The string returned by `read_string()` is stored on the **heap**, allocated by `malloc` inside `ft_reall_str`.
* The caller (here: `main`) is responsible for calling `free(input);` after using it.

---

### Q2: Why do we use `length + 2 >= buffer_size` instead of `length + 1 >= buffer_size`?

We need space for:

1. The **new character** we’re about to add.
2. The **null terminator** `'\0'` after it.

So the total minimum capacity we need is `length + 2`.
If `buffer_size` is smaller than that, we grow the buffer.

---

### Q3: Why are trims done **in-place** instead of returning new allocated strings?

* Simpler memory management: we only allocate once in `read_string`.
* More efficient: no extra allocations or copies for trims.
* The function still returns `str` to allow chaining, but it’s always the same pointer.

---

### Q4: In `ft_trim_left`, why do we use both `i` and `j`?

* `i` is used to **scan** the original string until the first non-space/tab.
* `j` is used to **write** from the beginning of the string.

This allows us to shift the relevant part of the string left, overwriting the leading spaces.

---

### Q5: Can `ft_trim_all` be called safely with `NULL`?

* In this code, `main` never calls trims if `input == NULL`.
* If you call `ft_trim_all(NULL)`:

  * `ft_trim_right(NULL)` would receive `str == NULL` and return `str` → `NULL`.
  * `ft_trim_left` then receives `NULL` and returns `NULL`.
    So it won’t crash because both functions check for `NULL`, but it’s still better practice to avoid calling them with `NULL`.

---

### Q6: Why does `ft_trim_right` use `ft_strlen` instead of scanning from the left like `ft_trim_left`?

We want to remove **trailing** spaces, i.e., at the **end** of the string.
Using `ft_strlen` gives us the index of the `'\0'`, then we move backward until we find the last non-space/tab. This is the cleanest way to trim from the right.

---

### Q7: What happens if the string is only spaces and tabs, e.g. `"   \t "`?

* `ft_trim_right`:

  * Moves `len` backward until it becomes `0`.
  * Then writes `str[0] = '\0'` → empty string.
* `ft_trim_left` (called after in `ft_trim_all`):

  * Sees `str[0] == '\0'` → `i` stays 0.
  * `if (i == 0) return (str);` → no shift needed.

Final result: an **empty string** `""`.

---

### Q8: Why does `ft_reall_str` start with size 32 and then double?

This is a common dynamic array strategy:

* Start with a **reasonable small block** (32).
* Doubling capacity gives amortized **O(1)** insertion (we don’t reallocate on every character).
* Keeps reallocations relatively rare but still bounded.

---

```
```

