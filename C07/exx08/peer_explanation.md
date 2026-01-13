# 🧠Exx08: peer_explanation.md — Dynamic Input Reader & Tokenizer

This document explains the **exact behavior, memory usage, and execution flow** of the program. It contains:

* Full source code
* Function-by-function analysis
* Low-level **stack frame (B2)** diagrams with offsets
* Heap allocation diagrams
* Call stack traces
* Recursion theory (integrated in `ft_putnbr`)
* Answers to **your saved recursion questions**
* Defense questions for viva-style peer evaluation

---

## 📌 Full Source Code

```c
#include <stdlib.h>
#include <unistd.h>

/* ============================== */
/*            UTILS               */
/* ============================== */

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

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

void	ft_putnbr(int nbr)
{
	long	num;

	num = nbr;
	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	if (num >= 10)
		ft_putnbr(num / 10);
	ft_putchar((num % 10) + '0');
}

char	*ft_strncpy(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/* ============================== */
/*        DYNAMIC REALLOC         */
/* ============================== */

char	*ft_realloc_str(char *str, size_t *size)
{
	char	*new_str;
	size_t	new_size;
	size_t	old_size;

	old_size = *size;
	if (*size == 0)
		new_size = 32;
	else
		new_size = *size * 2;
	new_str = (char *)malloc(sizeof(char) * new_size);
	if (!new_str)
		return (NULL);
	if (str)
	{
		/* copy old buffer contents (up to old_size) */
		ft_strncpy(new_str, str, old_size);
		free(str);
	}
	*size = new_size;
	return (new_str);
}

/* ============================== */
/*          READ STRING           */
/* ============================== */

char	*read_string(void)
{
	char	ch;
	size_t	length;
	char	*buffer;
	size_t	buffer_size;

	length = 0;
	buffer = NULL;
	buffer_size = 0;
	ft_putstr("Please Enter Your String:\n");

	while (1)
	{
		if (read(0, &ch, 1) <= 0 || ch == '\n')
			break;
		if (length + 1 >= buffer_size)
		{
			buffer = ft_realloc_str(buffer, &buffer_size);
			if (!buffer)
				return (NULL);
		}
		buffer[length] = ch;
		length++;
	}
	if (buffer)
		buffer[length] = '\0';
	return (buffer);
}

/* ============================== */
/*        TOKEN FUNCTIONS         */
/* ============================== */

int	is_Delimiter(char c, char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (c == delim[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_tokens_in_str(char *str, char *delim)
{
	int		count;
	char	*start;
	char	*current;

	if (!str || !delim)
		return (0);
	count = 0;
	start = str;
	current = str;
	while (*current)
	{
		if (is_Delimiter(*current, delim))
		{
			if (current > start)
				count++;
			start = current + 1;
		}
		current++;
	}
	if (current > start)
		count++;
	return (count);
}

char	**split_string(char *str, char *delim)
{
	int		i;
	int		j;
	int		len;
	int		words;
	int		start;
	char	**result;

	if (!str || !delim)
		return (NULL);
	words = count_tokens_in_str(str, delim);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < words)
	{
		while (str[i] && is_Delimiter(str[i], delim))
			i++;
		if (str[i] && !is_Delimiter(str[i], delim))
		{
			len = 0;
			start = i;
			while (str[i] && !is_Delimiter(str[i], delim))
			{
				len++;
				i++;
			}
			result[j] = (char *)malloc(sizeof(char) * (len + 1));
			if (!result[j])
				return (NULL);
			ft_strncpy(result[j], &str[start], len);
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}

/* ============================== */
/*     PRINT & FREE FUNCTIONS     */
/* ============================== */

void	print_split_result(char **result)
{
	int	i;

	if (!result)
	{
		ft_putstr("Result is NULL\n");
		return;
	}
	i = 0;
	while (result[i])
	{
		ft_putstr(result[i]);
		ft_putstr("\n");
		i++;
	}
}

void	free_split_result(char **result)
{
	int	i;

	if (!result)
		return;
	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

/* ============================== */
/*              MAIN              */
/* ============================== */

int	main(void)
{
	char	*input;
	char	**tokens;
	int		token_count;
	char	*delim;

	delim = " \t\n";

	input = read_string();
	if (!input)
		return (1);

	token_count = count_tokens_in_str(input, delim);
	ft_putstr("Tokens = ");
	ft_putnbr(token_count);
	ft_putstr("\n");

	tokens = split_string(input, delim);
	if (!tokens)
	{
		free(input);
		return (1);
	}

	print_split_result(tokens);

	free_split_result(tokens);
	free(input);
	return (0);
}
```

---

# 🧾 FUNCTION-BY-FUNCTION EXPLANATION

---

# 1. `ft_putchar`

### Purpose

Low-level wrapper around `write(2)`.

### Behavior

* Writes a **single byte** to stdout (fd = 1).

### Stack Frame (B2 Style)

```
Stack Frame: ft_putchar
[offset +8]   ← return address
[offset +0]   ← c (1 byte, but padded in stack)
```

No heap usage here.

---

# 2. `ft_putstr`

### Purpose

Print a null-terminated C string.

### Important Logic

* Stops at first `'\0'`.

### Example Memory Layout

For `char *str = "Hi";`

```
Heap or Static Area:
address   value
------    -----
0x...00 → 'H'
0x...01 → 'i'
0x...02 → '\0'
```

### Execution Trace

```
i = 0 → print 'H'
i = 1 → print 'i'
i = 2 → stop (str[2] == '\0')
```

### Stack Frame (B2)

```
Stack Frame: ft_putstr
[offset +8]  ← return address
[offset +4]  ← i (int)
[offset +0]  ← str (char *)
```

---

# 3. `ft_putnbr` (DEEP SECTION)

### Purpose

Print an integer using **recursion**.

### Key Cautions

* Negatives handled safely via `long`.
* Recursion prints digits in **left-to-right order**.

---

## 🔸 Step-by-step Logic

```c
num = nbr;          // promote to long
if (num < 0)        // handle negative sign
    print '-'
    num = -num
if (num >= 10)      // more than one digit?
    recurse on num / 10
print num % 10      // print last digit
```

---

## 🔸 Why cast to `long`?

If `nbr == INT_MIN` (`-2147483648` on 32-bit int), `-nbr` causes signed overflow in `int`. Using `long` prevents that.

---

## 🔸 Recursion Anatomy (Descent + Ascent)

Let’s trace `ft_putnbr(1234)`.

### **Phase 1: Descent (recursive calls)**

```
ft_putnbr(1234)
 → ft_putnbr(123)
    → ft_putnbr(12)
        → ft_putnbr(1)
```

No printing happens yet except for possible `'-'`.

### **Phase 2: Base Case**

When `num = 1`, `num < 10`:

```
print 1
```

### **Phase 3: Ascent (unwinding / printing)**

Returning from recursion:

* return to `12`: print `2`
* return to `123`: print `3`
* return to `1234`: print `4`

Final output: `1234`

---

## 🔸 **Related Questions Explained**

### Q1: **Why do we need both `/ 10` and `% 10`?**

* `/ 10` → **shifts right**, removes last digit. (Recursive progression)
* `% 10` → **extracts last digit**. (Actual digit to print)

Using only `/ 10` loses digits.
Using only `% 10` prints digits in **reverse**.

Together they create:

```
Descent: num / 10 → move left
Ascent:  num % 10 → print current digit
```

---

### Q2: **Why does `if (num >= 10) ft_putnbr(num / 10)` behave like a loop?**

Because:

* It keeps calling itself with a **smaller argument**
* Until a **base condition** (`num < 10`) stops further calls

This mimics:

```c
while (num >= 10)
    num /= 10;
```

But recursion preserves order when unwinding.

---

### Q3: **What does it mean that recursion has descent and unfold?**

Terminology matching execution:

| Phase | Name    | Action                         |
| ----- | ------- | ------------------------------ |
| 1     | Descent | pushing frames, reducing `num` |
| 2     | Base    | print first digit              |
| 3     | Ascent  | popping frames, printing rest  |

---

## 🔸 Low-Level Stack Frame Diagram (B2)

For `ft_putnbr(1234)` recursion:

### When calling `ft_putnbr(1234)`:

```
Stack Frame #0 — ft_putnbr(1234)
[offset +16] ← return address to caller
[offset +8]  ← saved RBP
[offset +0]  ← num = 1234 (long)
```

### After calling recursion:

```
Stack Frame #1 — ft_putnbr(123)
[offset +16] ← return address to frame0
[offset +8]  ← saved RBP
[offset +0]  ← num = 123 (long)
```

Next:

```
Stack Frame #2 — ft_putnbr(12)
[offset +0] ← num = 12
```

Next:

```
Stack Frame #3 — ft_putnbr(1)
[offset +0] ← num = 1
```

### Unwinding visualization:

```
Frame #3 prints '1'  ← base
return to frame #2 → print '2'
return to frame #1 → print '3'
return to frame #0 → print '4'
```

Final output = `1234`.

---

## 🔸 Heap Interaction

`ft_putnbr` does **not** use heap.
All frames are **stack-only**.

---

# 4. `ft_strncpy`

### Purpose

Copy `size` characters from `src` to `dst`, append `'\0'`.

### Stack Frame B2

```
Stack Frame: ft_strncpy
[offset +16] ← return addr
[offset +12] ← size (int)
[offset +8]  ← src (char *)
[offset +4]  ← dst (char *)
[offset +0]  ← i (int)
```

### Behavior Notes

* Does **not** check `src[i] != '\0'` — assumes valid range.
* Safe here because caller controls `size`.

---

# 5. `ft_realloc_str`

### Purpose

Grow buffer exponentially (`32 → 64 → 128 → …`).

### Heap Behavior

Allocation timeline for input `"Hello"`:

```
malloc(32)  → buffer at 0xH0
copy        → "H e l l o \0 ????"
realloc     → malloc(64) at 0xH1
copy        → free(0xH0)
```

### Memory Diagram

```
Before realloc:
 Heap @0xH0:
  [H][e][l][l][o]['\0'][?][?]...[?]

After realloc:
 Heap @0xH1:
  [H][e][l][l][o]['\0'][?][?]...[?][?]
```

---

# 6. `read_string`

### Purpose

Read input char-by-char into dynamic buffer.

### Key Variables

| Variable      | Meaning                      |
| ------------- | ---------------------------- |
| `ch`          | next character from input    |
| `length`      | current string length        |
| `buffer`      | dynamic char array (heap)    |
| `buffer_size` | current capacity (heap size) |

### Heap/Stack Interaction

Stack frame:

```
Stack Frame: read_string
[offset +32] ← return addr
[offset +24] ← buffer_size (size_t)
[offset +16] ← buffer (char *)
[offset +8]  ← length (size_t)
[offset +0]  ← ch (char)
```

Heap evolves via `ft_realloc_str`.

### Condition `length + 1 >= buffer_size`

This ensures:

* `buffer[length] = ch` is valid
* `buffer[length+1] = '\0'` later is valid

---

# 7. Token Functions

---

# 7. `is_Delimiter`

```c
int	is_Delimiter(char c, char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (c == delim[i])
			return (1);
		i++;
	}
	return (0);
}
```

### Purpose

* Checks whether character `c` belongs to the set of delimiter characters in `delim`.
* In this program: `delim = " \t\n"` (space, tab, newline).

### Logic

* Loop over `delim` until `'\0'`.
* If any `delim[i] == c` → return `1` (true).
* If loop finishes → return `0` (false).

### Example

Given:

```c
char *delim = " \t\n";
is_Delimiter(' ', delim)   → 1
is_Delimiter('\t', delim) → 1
is_Delimiter('A', delim)   → 0
```

### Stack Frame (B2)

```
Stack Frame: is_Delimiter
[offset +12] ← return addr
[offset +8]  ← delim (char *)
[offset +4]  ← c (char)
[offset +0]  ← i (int)
```

Heap: none.

---

# 8. `count_tokens_in_str`

```c
int	count_tokens_in_str(char *str, char *delim)
{
	int		count;
	char	*start;
	char	*current;

	if (!str || !delim)
		return (0);
	count = 0;
	start = str;
	current = str;
	while (*current)
	{
		if (is_Delimiter(*current, delim))
		{
			if (current > start)
				count++;
			start = current + 1;
		}
		current++;
	}
	if (current > start)
		count++;
	return (count);
}
```

### Purpose

Count how many **words/tokens** there are in the string `str`, using delimiters given by `delim`.

Your requirement (which this satisfies):

> `"Hello 42 from Zain"` → `"Hello"`, `"42"`, `"from"`, `"Zain"`
> Each separated by spaces, so **4 tokens**. Numbers like `42` are treated like normal words because we only care about characters between delimiters.

### Core Idea

* `start` → pointer to the first character of the **current word** (candidate).
* `current` → pointer scanning each character.
* Whenever we hit a delimiter:

  * If `current > start`, then the region `[start, current)` contains at least one character → we found a word → `count++`.
  * Move `start` to `current + 1` (start after the delimiter).
* After the loop, we handle the last word **if the string does not end with a delimiter**.

### Important Pointer Comparison

```c
if (current > start)
    count++;
```

This is how we avoid:

* Counting **empty tokens** when there are multiple delimiters in a row (e.g. `"Hello   42"`).
* Counting something when there's nothing between two delimiters (e.g. `"   "` should give 0 tokens).

### Example Trace: `"Hello 42 from Zain"`

Let’s assume `str` is:

```text
index: 0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15
char : 'H'  'e'  'l'  'l'  'o'  ' '  '4'  '2'  ' '  'f'  'r'  'o'  'm'  ' '  'Z'  'a' ...
```

Initial:

* `start = &str[0]` (points to `'H'`)
* `current = &str[0]`
* `count = 0`

Walk:

1. `current` moves over `'H','e','l','l','o'` → not delimiters.

2. At index 5: `current` points to `' '`:

   * `is_Delimiter(' ', delim) == 1`
   * `current > start` → yes (we passed over characters) → `count++` → `count = 1`
   * `start = current + 1` → now `start = &str[6]` (`'4'`)

3. Move `current` to `'4'`,`'2'`, then space at index 8:

   * `is_Delimiter(' ', delim)` → 1
   * `current > start` → yes (`'4','2'` between) → `count++` → `count = 2`
   * `start = &str[9]` (`'f'`)

4. Move `current` through `'f','r','o','m'`, then space at index 13:

   * `current > start` → yes → `count++` → `count = 3`
   * `start = &str[14]` (`'Z'`)

5. Continue over `'Z','a','i','n'` until `*current == '\0'`.

After loop exits: `current` points at `'\0'`.

Final check:

```c
if (current > start)
    count++;
```

* `current` at `'\0'`, `start` at `'Z'` → `current > start` → yes.
* So `count++` → `count = 4`.

✅ **Tokens = 4**.

### Stack Frame (B2)

```
Stack Frame: count_tokens_in_str
[offset +24] ← return addr
[offset +20] ← delim (char *)
[offset +16] ← str (char *)
[offset +12] ← count (int)
[offset +8]  ← start (char *)
[offset +4]  ← current (char *)
```

Heap: none here.

---

# 9. `split_string`

```c
char	**split_string(char *str, char *delim)
{
	int		i;
	int		j;
	int		len;
	int		words;
	int		start;
	char	**result;

	if (!str || !delim)
		return (NULL);
	words = count_tokens_in_str(str, delim);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < words)
	{
		while (str[i] && is_Delimiter(str[i], delim))
			i++;
		if (str[i] && !is_Delimiter(str[i], delim))
		{
			len = 0;
			start = i;
			while (str[i] && !is_Delimiter(str[i], delim))
			{
				len++;
				i++;
			}
			result[j] = (char *)malloc(sizeof(char) * (len + 1));
			if (!result[j])
				return (NULL);
			ft_strncpy(result[j], &str[start], len);
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}
```

### Purpose

Split `str` into an array of C-strings (`char *`), using delimiters to detect word boundaries.

### Steps

1. Check `str` & `delim` not `NULL`.

2. Count how many words: `words = count_tokens_in_str(str, delim);`.

3. Allocate an array of pointers:

   ```c
   result = malloc(sizeof(char *) * (words + 1));
   ```

   * `result[0..words-1]` → token pointers.
   * `result[words]` → `NULL` terminator.

4. Use index `i` to walk `str`, and `j` to fill tokens into `result`.

### Inner Logic

* Skip delimiters:

  ```c
  while (str[i] && is_Delimiter(str[i], delim))
      i++;
  ```

* If we are at the start of a token:

  ```c
  if (str[i] && !is_Delimiter(str[i], delim))
  {
      len = 0;
      start = i;
      while (str[i] && !is_Delimiter(str[i], delim))
      {
          len++;
          i++;
      }
      ...
  }
  ```

  Here:

  * `start` holds the index of the first character of the token.
  * `len` counts characters until next delimiter or `'\0'`.

* Allocate and copy:

  ```c
  result[j] = malloc(len + 1);
  ft_strncpy(result[j], &str[start], len);
  result[j][len] = '\0'; // ensured by ft_strncpy
  j++;
  ```

* After loop: `result[j] = NULL;` → marks end.

### Example Memory Layout: `"Hello 42"`

Let’s assume:

```c
str = "Hello 42"
delim = " \t\n"
words = 2
```

#### Heap: Result Pointer Array

```text
result (char **)
  index: 0         1         2
         ↓         ↓         ↓
       [ ? ]     [ ? ]     [ NULL ]
```

#### After processing `"Hello"`:

* `len = 5`, `start` at index 0.
* `malloc(6)` for `result[0]`.

Token 0 in heap:

```text
result[0] → [ 'H','e','l','l','o','\0' ]
             0   1   2   3   4   5
```

#### After processing `"42"`:

* `len = 2`, `start` at index for `'4'`.
* `malloc(3)` for `result[1]`.

Token 1:

```text
result[1] → [ '4','2','\0' ]
             0   1   2
```

Final:

```text
result:
index  value
0      pointer to "Hello"
1      pointer to "42"
2      NULL
```

### Stack Frame (B2)

```
Stack Frame: split_string
[offset +36] ← return addr
[offset +32] ← delim (char *)
[offset +28] ← str (char *)
[offset +24] ← result (char **)
[offset +20] ← words (int)
[offset +16] ← start (int index)
[offset +12] ← len (int)
[offset +8]  ← j (int)
[offset +4]  ← i (int)
```

Heap:

* One block for `result` (array of `char *`).
* One block for each token string.

---

# 10. `print_split_result`

```c
void	print_split_result(char **result)
{
	int	i;

	if (!result)
	{
		ft_putstr("Result is NULL\n");
		return;
	}
	i = 0;
	while (result[i])
	{
		ft_putstr(result[i]);
		ft_putstr("\n");
		i++;
	}
}
```

### Purpose

Print each token on its own line.

### Notes

* Stops when `result[i] == NULL`.
* Uses `ft_putstr` for each token.

### Stack Frame (B2)

```
Stack Frame: print_split_result
[offset +12] ← return addr
[offset +8]  ← result (char **)
[offset +4]  ← i (int)
```

Heap: doesn’t allocate; just reads pointers and strings.

---

# 11. `free_split_result`

```c
void	free_split_result(char **result)
{
	int	i;

	if (!result)
		return;
	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}
```

### Purpose

Free all dynamic memory associated with the token array.

### Memory order

1. Free each `result[i]` (each word).
2. Free `result` itself.

Order is important to **not** lose pointers.

---

# 12. `main`

```c
int	main(void)
{
	char	*input;
	char	**tokens;
	int		token_count;
	char	*delim;

	delim = " \t\n";

	input = read_string();
	if (!input)
		return (1);

	token_count = count_tokens_in_str(input, delim);
	ft_putstr("Tokens = ");
	ft_putnbr(token_count);
	ft_putstr("\n");

	tokens = split_string(input, delim);
	if (!tokens)
	{
		free(input);
		return (1);
	}

	print_split_result(tokens);

	free_split_result(tokens);
	free(input);
	return (0);
}
```

### Overall Flow

1. `delim = " \t\n"` initializes the delimiters to **space, tab, newline**.
2. `input = read_string();`

   * reads *one full line* into a dynamically growing heap buffer.
3. If `input == NULL` → exit with error code `1`.
4. `token_count = count_tokens_in_str(input, delim);`

   * counts how many words using your logic (each group of non-delimiter chars).
5. Print:

   ```c
   Tokens = <number>
   ```

   using `ft_putnbr` (recursion).
6. `tokens = split_string(input, delim);`

   * returns an array of pointers where each is a token string.
7. If `tokens == NULL`:

   * free `input` and exit.
8. Print the token list.
9. Free everything:

   * `free_split_result(tokens);`
   * `free(input);`
10. Return `0` on success.

### Example Run: `"Hello 42 from Zain"`

Input from user:

```text
Hello 42 from Zain↵
```

Output:

```text
Please Enter Your String:
Tokens = 4
Hello
42
from
Zain
```

---

# 13. Defense / Deep Questions (with expected ideas)

You can use these in a peer evaluation.

1. **Explain how `ft_putnbr` prints digits in correct order using recursion.**

   * Talk about **descent** (dividing by 10) and **ascent** (printing `% 10`).

2. **Why is `num` a `long` instead of `int` in `ft_putnbr`?**

   * To avoid overflow when negating `INT_MIN`.

3. **Why do we use both `/ 10` and `% 10` instead of only one?**

   * `/ 10` to move towards more significant digits. `% 10` to extract digit to print.

4. **Show a call stack diagram for `ft_putnbr(-123)` including the `'-'` printing.**

5. **In `read_string`, what is the difference between `length` and `buffer_size`?**

   * `length` is used bytes (string length); `buffer_size` is total allocated capacity.

6. **Why do we check `if (length + 1 >= buffer_size)` instead of `length >= buffer_size`?**

   * Reserve one extra position for `'\0'` at the end.

7. **Show the heap and stack when the user enters `"Hi"`.**

   * Stack: `read_string` frame with `length`, `ch`, etc.
   * Heap: buffer with `[ 'H','i','\0', ... ]`.

8. **Explain how `count_tokens_in_str` avoids counting empty tokens between multiple spaces.**

9. **Draw a memory diagram of `result` and its tokens for input `"Hello 42"`.**

10. **What possible memory leak can happen in `split_string`?**

    * If one `malloc` for `result[j]` fails after some previous tokens were allocated, the function returns `NULL` but does not free already allocated `result[0..j-1]`.

11. **Why do we need `result[words] = NULL;`?**

    * So that loops like `while (result[i])` know when to stop.

12. **What happens if user types only `'\n'` (empty line) and presses enter?**

    * `read_string` returns `""` (empty string).
    * `count_tokens_in_str` returns `0`.
    * `split_string` allocates list with `words = 0` → array size `1` with only `result[0] = NULL`.

13. **Explain carefully why the line `if (num >= 10) ft_putnbr(num / 10);` “acts like a loop but only prints in the unfolding stage”.**

    * During calls, it just pushes stack frames and reduces the number.
    * Printing only happens when stack unwinds, at `ft_putchar((num % 10) + '0')`.

---
