````markdown
# 🧪 Exercise 05 – `ft_strlcat`  
**File:** `ft_strlcat.c`  
**Goal:** Reproduce the behavior of `strlcat(3)` without using any other functions.

---

## 1. What does `strlcat` actually do?

`strlcat` tries to **append** `src` to the end of `dest`, but it never writes beyond the buffer size given by `size`.

- `dest` = destination buffer (already contains a C-string)
- `src`  = string we want to append
- `size` = **total capacity of the `dest` buffer in bytes**  
  (not “how much is free”, not “how much to copy”, but **the full size of the array**)

The function:

1. Looks how long `dest` already is (but only inside the first `size` bytes).
2. Looks how long `src` is.
3. Appends as many characters from `src` as possible **without exceeding `size - 1`**.
4. Always null-terminates `dest` if `size > 0` and there is at least 1 free byte.
5. Returns:  
   > the length of the string it *wanted* to build =  
   > `initial_dest_length + src_length`  
   even if the result was truncated in the buffer.

---

## 2. Indexing version (array style)

```c
unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	i;

	dest_len = 0;
	while (dest_len < size && dest[dest_len] != '\0')
		dest_len++;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;

	if (dest_len == size)
		return (size + src_len);

	i = 0;
	while (src[i] != '\0' && (dest_len + i + 1) < size)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
````

---

## 3. Pointer version

```c
unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	char			*d = dest;
	const char		*s = src;
	unsigned int	dest_len = 0;
	unsigned int	src_len = 0;
	unsigned int	space_left;

	while (dest_len < size && *d != '\0')
	{
		d++;
		dest_len++;
	}
	while (*s != '\0')
	{
		s++;
		src_len++;
	}
	if (dest_len == size)
		return (size + src_len);

	s = src;
	space_left = size - dest_len;

	while (*s != '\0' && space_left > 1)
	{
		*d = *s;
		d++;
		s++;
		space_left--;
	}
	*d = '\0';
	return (dest_len + src_len);
}
```

### Why more variables in the pointer version?

* `d` – walks on `dest` without recalculating `dest[dest_len + i]`.
* `s` – walks on `src` instead of using `src[i]`.
* `space_left` – makes the “room left in the buffer including `'\0'`” explicit instead of hiding it inside `(dest_len + i + 1) < size`.

Logically, both versions do **exactly the same thing**.
The pointer version just turns complicated index expressions into simpler pointer moves.

---

## 4. Step-by-step walkthrough (index version)

### 4.1 Measure `dest` safely

```c
dest_len = 0;
while (dest_len < size && dest[dest_len] != '\0')
	dest_len++;
```

Why this condition is **exactly** like this:

* `dest_len < size`
  → We **never** read outside the given buffer.
  Even if `dest` is not null-terminated properly, we stop once we reach `size`.
* `dest[dest_len] != '\0'`
  → Normal C-string logic: stop at the null terminator.

So after this loop:

* If we found `'\0'` before `size` → `dest_len` = actual length of the string in `dest`.
* If we **never** found `'\0'` and `dest_len == size` →
  we **don’t actually know** the real length of `dest`’s string.
  We only know: “it is at least `size` long (or badly formed)”.

This is why the next `if` is important.

---

### 4.2 Measure `src`

```c
src_len = 0;
while (src[src_len] != '\0')
	src_len++;
```

Easy: no size limit here, we assume `src` is a valid C-string.

---

### 4.3 Handle the “no space at all” case

```c
if (dest_len == size)
	return (size + src_len);
```

This means:

* We scanned up to `size` bytes of `dest` and **never saw `'\0'`**.
* So either:

  * `dest` has no terminator in the first `size` bytes
    **or**
  * `dest` is exactly full up to `size - 1` and there is no room for `'\0'`.

In both cases, we **must not write anything**, because we might overflow.

So we just return:

> `size + src_len`

Why not `dest_len + src_len` here?
Because in this case `dest_len == size` but we **cannot trust** `dest_len` to be the *real* string length (it might be bigger).
The official `strlcat` behavior says:

> “Return the length you *tried* to create.”
>
> In this situation, we only know **for sure** that the initial dest string is **at least** `size` long, so we use `size` as the safe lower bound.

So:

* “No concatenation performed.”
* “We would like the final string to have length `at least size + src_len`.”

---

### 4.4 Copy loop (actual concatenation)

```c
i = 0;
while (src[i] != '\0' && (dest_len + i + 1) < size)
{
	dest[dest_len + i] = src[i];
	i++;
}
dest[dest_len + i] = '\0';
```

Think of `(dest_len + i + 1) < size` like:

> “Do we still have room for **one more character plus the final `'\0'`**?”

* `dest_len` – how many chars were already in `dest` before we start.
* `i` – how many chars from `src` we already copied.
* `+ 1` – reserve one byte for `'\0'`.
* `< size` – stay inside the buffer.

We stop the loop if:

* `src[i] == '\0'`
  → we copied all of `src` successfully.
* or `(dest_len + i + 1) == size`
  → **no more room** for another character plus the end `'\0'`.

Then we place the null terminator:

```c
dest[dest_len + i] = '\0';
```

So `dest` is always a valid C-string (as long as `size > 0` and the early `if` didn’t trigger).

---

### 4.5 Return value

```c
return (dest_len + src_len);
```

This is:

> “The length of the string we **wanted** to build,
> assuming there was infinite space in `dest`.”

* If no truncation happened → this equals the real final length of `dest`.
* If truncation happened → the return value is **bigger** than the real final length.
  The caller can detect truncation by checking:

  ```c
  if (ret >= size)
      // truncation
  ```

---

## 5. The suitcase analogy (with 17 and 15)

We use **only this analogy**, with clothes and a suitcase.

### Definitions

* `size`  → **Capacity of the suitcase** (how many T-shirts it can hold in total).
* `dest_len` → How many T-shirts are **already inside**.
* `src_len`  → How many new T-shirts you **want to add**.

We will use the following numbers:

* Suitcase capacity: `size = 12` T-shirts.
* Inside the suitcase at the start: either `10` or `12`.
* New T-shirts from `src`: `src_len = 5`.

---

### Case A – suitcase already full → returns **17**

* Capacity (`size`) = 12.
* Already inside (`dest_len`) = 12 (full).
* New T-shirts (`src_len`) = 5.

You **cannot** add anything (no free space).
What does `ft_strlcat` do?

1. It checks how many T-shirts are already inside:

   * It counts until it reaches the limit `size = 12`.
   * There is no more space, so `dest_len` becomes `12` and the loop stops.
   * We are in the case `dest_len == size`.

2. In this situation it returns:

   ```c
   size + src_len = 12 + 5 = 17
   ```

Meaning in human language:

> “To fit everything, I would need a suitcase that can hold **17 T-shirts**.”

No copying happens, because the suitcase is completely full.

---

### Case B – suitcase has some free space → returns **15**

* Capacity (`size`) = 12.
* Already inside (`dest_len`) = 10.
* New T-shirts (`src_len`) = 5.

There is space for only **2** more T-shirts, but you want to pack **5**.

What happens?

1. It counts the T-shirts already inside: `dest_len = 10`.

2. It sees: `dest_len < size`, so we have some room.

3. It starts copying T-shirts from `src`:

   * Copy 1st T-shirt → now 11 inside.
   * Copy 2nd T-shirt → now 12 inside.
   * No more room for another T-shirt, but we still have to “close the suitcase” (null terminator).
     So we stop.

4. Final suitcase contents:

   * **Actual** T-shirts inside after copying: 12 (full).
   * T-shirts we could **not** pack from `src`: 3 left outside.

5. Return value:

   ```c
   dest_len + src_len = 10 + 5 = 15
   ```

Meaning:

> “If I had a big enough suitcase, I would want to end up with a string of length **15**
> (10 original + 5 new). But in reality, I could only pack up to 12.”

So:

* Case A (completely full at the start) → returns **17**.
* Case B (some space, then truncated) → returns **15**.

This is the **key** idea:

> The return value always describes the **ideal final length**,
> not the **real packed length** when truncated.

That’s why the caller can use:

```c
if (ft_strlcat(dest, src, size) >= size)
    // suitcase was not big enough → truncation
```

---

## 6. Your specific questions – short notes

### Q1 – What exactly is `size`?

> Is `size` the full size of `dest`, the size of `src`, or how much we want to copy?

* `size` is **only**:

  > “How big is the `dest` buffer in total (in bytes)?”
* It does **not** depend on how long `src` is.
* It does **not** mean “number of bytes to copy”.

Example:

```c
char dest[20] = "Hello";
ft_strlcat(dest, " World", 20); // here size = 20 (sizeof(dest))
```

---

### Q2 – Why do we check `dest_len < size` in the first loop?

> Why don’t we just measure `dest` with `strlen(dest)`?

Because of **safety**:

* We must **never read beyond the first `size` bytes** of `dest`.
* The caller promises only that `dest` has at least `size` valid bytes of memory,
  **not** that the string is null-terminated inside those `size` bytes.

So we write:

```c
while (dest_len < size && dest[dest_len] != '\0')
    dest_len++;
```

If there is no `'\0'` in those `size` bytes, we stop at `dest_len == size`
and treat it as “no space to append anything safely”.

---

### Q3 – Why not compare directly “free space” with `src_len`?

> Wouldn’t it be easier to check:
> “free_space_in_dest >= src_len” ?

We *could* compute it like this:

```c
free_space = size - dest_len - 1; // minus 1 for '\0'
```

Then check if `free_space >= src_len`.
This would tell us if we can copy everything without truncation.

But:

* `strlcat` does **not** care about “all or nothing”.
* It **always copies as much as it can**, then stops, and always null-terminates if possible.
* The caller can later inspect the return value to see if it was truncated.

So the implementation just loops while there is room for **one more character**, not all of them:

```c
while (src[i] && (dest_len + i + 1) < size)
    ...
```

This makes the function **incremental**: copy until you run out of room.

---

### Q4 – Why two different returns?

> Why don’t we always return `dest_len + src_len`?
> Why in the first `if` do we return `size + src_len`?

Two cases:

1. **Normal case (we found `'\0'` in dest)**
   We know the real `dest_len`, so we return:

   ```c
   return (dest_len + src_len);
   ```

   → “Ideal final length = real dest length + src length.”

2. **Special case: `dest_len == size`**
   We scanned `size` bytes and didn’t see `'\0'`.
   We **do not know** the actual length of the string in `dest`.
   All we know is:

   > “It is at least `size`.”

   So the standard definition uses:

   ```c
   return (size + src_len);
   ```

   That is a **safe lower bound** for “how long the final string would need to be”.

So:

* First return: “I don’t know `dest_len`, but I know there are at least `size` bytes.”
* Second return: “I know exactly `dest_len`, so I can use it.”

---

### Q5 – Are the two return values sometimes equal?

Sometimes yes, sometimes no:

* If `dest` is correct and null-terminated and fits in `size`, then:

  * `dest_len < size`
  * Return value = `dest_len + src_len`.

* If `dest` has no `'\0'` inside the first `size` bytes:

  * We *must* use `size + src_len`.
  * That is **different** from the unknown real length + `src_len`.

So the code **must** keep these two cases separate.

---

## 7. Small test main (for your repo)

```c
#include <stdio.h>

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);

int	main(void)
{
	char			buffer1[20] = "Hello";
	char			buffer2[10] = "Hello";
	char			buffer3[5] = "Hi";
	char			buffer4[20] = "Test";
	char			src[] = " World!";
	unsigned int	ret;

	printf("=== Test 1: Normal concat (size > dest_len) ===\n");
	printf("Before: \"%s\"\n", buffer1);
	ret = ft_strlcat(buffer1, src, 20);
	printf("After : \"%s\"\n", buffer1);
	printf("Return: %u\n\n", ret);

	printf("=== Test 2: Small size (truncation expected) ===\n");
	printf("Before: \"%s\"\n", buffer2);
	ret = ft_strlcat(buffer2, src, 10);
	printf("After : \"%s\"\n", buffer2);
	printf("Return: %u\n\n", ret);

	printf("=== Test 3: size <= dest_len (no concat) ===\n");
	printf("Before: \"%s\"\n", buffer3);
	ret = ft_strlcat(buffer3, src, 2);
	printf("After : \"%s\"\n", buffer3);
	printf("Return: %u\n\n", ret);

	printf("=== Test 4: size = 0 ===\n");
	ret = ft_strlcat(buffer4, src, 0);
	printf("Buffer unchanged: \"%s\"\n", buffer4);
	printf("Return: %u\n", ret);

	return (0);
}
```

---

## 8. Index vs pointer version – quick comparison

| Aspect             | Index version                             | Pointer version                               |
| ------------------ | ----------------------------------------- | --------------------------------------------- |
| Access style       | `dest[dest_len + i]`, `src[i]`            | `*d`, `*s`, then `d++`, `s++`                 |
| Extra variables    | `dest_len`, `src_len`, `i`                | `dest_len`, `src_len`, `d`, `s`, `space_left` |
| Clarity of “space” | Hidden in `(dest_len + i + 1) < size`     | Explicit in `space_left > 1`                  |
| Performance        | Practically the same after compilation    | Practically the same                          |
| Readability        | Easier if you think in arrays and indices | Easier if you think in “moving pointers”      |

Both are perfectly valid for 42.
Pointer version mainly adds **`space_left`** to make the “room for `'\0'`” logic clearer.

---

## 9. Peer evaluation – possible questions & answers

**Q: What is the purpose of `ft_strlcat` compared to `ft_strcat`?**
A: `ft_strlcat` appends a string but **never writes past the given buffer size** and always tries to null-terminate. It also returns the length it *wanted* to create, so the caller can detect truncation.

**Q: What does the `size` parameter represent?**
A: It is the **total size of the destination buffer in bytes**, usually `sizeof(dest_array)`, not the current string length and not “number of bytes to copy”.

**Q: Why do you check `dest_len < size` when scanning `dest`?**
A: To avoid reading out of bounds if `dest` is not null-terminated inside the first `size` bytes. This is a security and robustness check.

**Q: When do we return `size + src_len` and when `dest_len + src_len`?**
A:

* If `dest_len == size` → we don’t know the real length of the string in `dest`, so we return `size + src_len`.
* Otherwise → we know `dest_len`, so we return `dest_len + src_len`.

**Q: How can the caller know if truncation happened?**
A: If `ft_strlcat(dest, src, size) >= size`, then truncation occurred or no concatenation was possible.

**Q: Does `ft_strlcat` always null-terminate?**
A:

* If `size > 0` and we are not in the `dest_len == size` early-return case, then yes, it always writes a `'\0'` byte at the end.

---

## 10. Memory diagram – walking through `ft_strlcat` step by step

Here we simulate the **index version** of `ft_strlcat` on a small buffer and watch memory change step by step.

### 10.1 Setup

```c
char dest[8] = "Hello";   // capacity = 8 bytes
char src[]   = " World";  // 6 chars + '\0'
unsigned int size = 8;

unsigned int ret = ft_strlcat(dest, src, size);
````

Remember:

* `size` = **total capacity** of `dest`, so here `size = 8`.
* `dest` currently contains `"Hello"` → 5 characters + `'\0'`.

In memory (ASCII, conceptual):

| Index | dest byte | Char               |
| ----- | --------- | ------------------ |
| 0     | 'H'       | H                  |
| 1     | 'e'       | e                  |
| 2     | 'l'       | l                  |
| 3     | 'l'       | l                  |
| 4     | 'o'       | o                  |
| 5     | '\0'      | \0                 |
| 6     | ?         | (garbage / unused) |
| 7     | ?         | (garbage / unused) |

---

### 10.2 First loop – measuring `dest_len`

Code:

```c
dest_len = 0;
while (dest_len < size && dest[dest_len] != '\0')
	dest_len++;
```

We walk the table:

* Step 1: `dest_len = 0`

  * Check: `0 < 8` → true
  * `dest[0] = 'H' != '\0'` → true
    → increment → `dest_len = 1`

* Step 2: `dest_len = 1`

  * `1 < 8` → true
  * `dest[1] = 'e' != '\0'` → true
    → `dest_len = 2`

* Step 3: `dest_len = 2`

  * `2 < 8` → true
  * `dest[2] = 'l' != '\0'` → true
    → `dest_len = 3`

* Step 4: `dest_len = 3`

  * `3 < 8` → true
  * `dest[3] = 'l' != '\0'` → true
    → `dest_len = 4`

* Step 5: `dest_len = 4`

  * `4 < 8` → true
  * `dest[4] = 'o' != '\0'` → true
    → `dest_len = 5`

* Step 6: `dest_len = 5`

  * `5 < 8` → true
  * `dest[5] = '\0'` → **false**

Loop stops.
Result: `dest_len = 5`.

We **never** read beyond index `4` + terminator at `5`, and we also would have stopped if we had ever reached `dest_len == size`.

---

### 10.3 Second loop – measuring `src_len`

Code:

```c
src_len = 0;
while (src[src_len] != '\0')
	src_len++;
```

For `" World"`:

| Index | Char |
| ----- | ---- |
| 0     | ' '  |
| 1     | 'W'  |
| 2     | 'o'  |
| 3     | 'r'  |
| 4     | 'l'  |
| 5     | 'd'  |
| 6     | '\0' |

We count until the `'\0'`, so `src_len = 6`.

---

### 10.4 Check “no space at all?” (`if (dest_len == size)`)

```c
if (dest_len == size)
	return (size + src_len);
```

Here:

* `dest_len = 5`
* `size = 8`

So `dest_len == size` is **false**, we have some room.

---

### 10.5 Copy loop – how many bytes can we really add?

Code:

```c
i = 0;
while (src[i] != '\0' && (dest_len + i + 1) < size)
{
	dest[dest_len + i] = src[i];
	i++;
}
dest[dest_len + i] = '\0';
```

Think again about the condition:

* `(dest_len + i + 1) < size`
  → we must keep **1 byte for `'\0'`**.

At this moment:

* `dest_len = 5`
* `size = 8`

So the maximum index allowed for characters is:

```text
dest_len + i + 1 < size
→ 5 + i + 1 < 8
→ 6 + i < 8
→ i < 2
```

So the loop may only run for `i = 0` and `i = 1`.
This means we can copy at most **2 characters** from `src`.

Let’s walk it:

#### Iteration 1 – `i = 0`

* Check `src[0] != '\0'` → `' '` (space) → true
* Check `(dest_len + i + 1) < size` → `5 + 0 + 1 = 6 < 8` → true

So we copy:

```c
dest[5 + 0] = src[0]; // dest[5] = ' ';
i++;                  // i = 1
```

Memory now:

| Index | dest byte | Char          |
| ----- | --------- | ------------- |
| 0     | 'H'       | H             |
| 1     | 'e'       | e             |
| 2     | 'l'       | l             |
| 3     | 'l'       | l             |
| 4     | 'o'       | o             |
| 5     | ' '       | (space)       |
| 6     | ?         | (unknown yet) |
| 7     | ?         | (unknown yet) |

#### Iteration 2 – `i = 1`

* `src[1] = 'W'` → not `'\0'`
* `(dest_len + i + 1) < size` → `5 + 1 + 1 = 7 < 8` → true

Copy:

```c
dest[5 + 1] = src[1]; // dest[6] = 'W';
i++;                  // i = 2
```

Memory now:

| Index | dest byte | Char          |
| ----- | --------- | ------------- |
| 0     | 'H'       | H             |
| 1     | 'e'       | e             |
| 2     | 'l'       | l             |
| 3     | 'l'       | l             |
| 4     | 'o'       | o             |
| 5     | ' '       | (space)       |
| 6     | 'W'       | W             |
| 7     | ?         | (unknown yet) |

#### Iteration 3 – `i = 2`

Now:

* `src[2] = 'o'` → not `'\0'`
* Check `(dest_len + i + 1) < size`:

  * `dest_len + i + 1 = 5 + 2 + 1 = 8`
  * `8 < 8` → **false**

So the loop stops. We **don’t** copy `'o'`, because that would leave no room for the terminator.

#### Null-termination

After loop:

```c
dest[dest_len + i] = '\0'; // dest[5 + 2] = dest[7] = '\0';
```

Final memory:

| Index | dest byte | Char    |
| ----- | --------- | ------- |
| 0     | 'H'       | H       |
| 1     | 'e'       | e       |
| 2     | 'l'       | l       |
| 3     | 'l'       | l       |
| 4     | 'o'       | o       |
| 5     | ' '       | (space) |
| 6     | 'W'       | W       |
| 7     | '\0'      | \0      |

Final visible string in `dest`:

```c
"Hello W"
```

We successfully:

* Kept memory safe
* Null-terminated
* Truncated `src` because there wasn’t enough room.

---

### 10.6 Return value for this example

We return:

```c
return (dest_len + src_len); // 5 + 6 = 11
```

Even though the real final string in the buffer is only `"Hello W"` (length 7), the **return value is 11**, meaning:

> “If my suitcase were big enough, I would like to end up with a total length of 11 characters.”

Caller can detect truncation:

```c
if (ret >= size)  // 11 >= 8 → true
{
    // truncation happened
}
```

This matches the suitcase idea:

* Suitcase capacity (`size`) = 8 slots.
* Initially inside (`dest_len`) = 5 items.
* New items (`src_len`) = 6.
* Ideal total = `5 + 6 = 11` items.
* Real total that fits = 7 items.
* Return value = 11 → “I needed an 11-slot suitcase, but I only had 8.”

---


