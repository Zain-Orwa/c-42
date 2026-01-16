Absolutely — here is a **complete `peer_explanation.md`** for **Exercise 05: `ft_show_tab`**, written in the same clean, structured GitHub-friendly format we’ve been using.
This explanation **includes all relevant connections** to the previous exercise (`ft_strs_to_tab`), because `ft_show_tab` depends on that data structure.

You can copy/paste this directly into your repository as `peer_explanation.md`.

---

````markdown
# 🧩 Exercise — `ft_show_tab`

This exercise builds on the previous task `ft_strs_to_tab`. Instead of constructing the array of structures, now we must **display** it.

---

# 📌 Subject Summary

We are asked to implement:

```c
void ft_show_tab(struct s_stock_str *par);
````

The array passed in must come from `ft_strs_to_tab()`, and the output format must be exactly:

1. `str` followed by a newline
2. `size` followed by a newline
3. `copy` followed by a newline

The array ends when `.str == 0` (a “sentinel” element).

Only the function `write()` is allowed, so we must implement our own utilities.

---

# 📁 Required Structure (from Exercise 04)

The header file provides the structure:

```c
typedef struct s_stock_str
{
	int   size;   // length of the string
	char *str;    // pointer to the original string
	char *copy;   // pointer to a heap-allocated duplicate
} t_stock_str;
```

Because this is already defined, we must not modify the struct — only use it.

---

# 🎯 Goal of This Exercise

✔ Use the data created by `ft_strs_to_tab()`
✔ Iterate until `.str == 0` (sentinel)
✔ Display each field using only `write()`
✔ Follow the exact formatting

Example display for one entry:

```
hello
5
hello
```

---

# 🧩 Data Flow Concept (Very Important)

To understand `ft_show_tab`, you need to recall what `ft_strs_to_tab()` returns:

For `ac = 3` and `av = {"cat", "dog", "42"}`, `ft_strs_to_tab` produces:

| Index | size | str   | copy  |
| ----- | ---- | ----- | ----- |
| 0     | 3    | "cat" | "cat" |
| 1     | 3    | "dog" | "dog" |
| 2     | 2    | "42"  | "42"  |
| 3     | 0    | NULL  | NULL  |

→ The last one is the **sentinel**: `.str == NULL`

So `ft_show_tab` must display index `0`, `1`, `2` and then stop at index `3`.

---

# 🧠 Sentinel Termination Pattern

This exercise uses the **same pattern** as C-strings:

* Strings end with: `'\0'`
* Our struct array ends with: `.str == 0`

This allows:

```c
while (par[i].str != 0)
    ...
```

No need for the original `ac`.

---

# 🧱 Implementation Breakdown

Since only `write()` is allowed, we must implement:

* `ft_putchar` → print 1 character
* `ft_putstr` → print a C-string
* `ft_putnbr` → print an integer (with recursion)
* `ft_show_tab` → orchestrates everything

---

# 📌 Utility Functions

### `ft_putchar`

```c
void ft_putchar(char c)
{
    write(1, &c, 1);
}
```

---

### `ft_putstr`

```c
void ft_putstr(char *str)
{
    if (!str)
        return;
    while (*str)
        write(1, str++, 1);
}
```

Handles `NULL` safely.

---

### `ft_putnbr`

We cannot use `printf()`, so we print digits recursively:

```c
void ft_putnbr(int nbr)
{
    long num = nbr;

    if (num < 0)
    {
        ft_putchar('-');
        num = -num;
    }
    if (num >= 10)
        ft_putnbr(num / 10);
    ft_putchar((num % 10) + '0');
}
```

Key details:

* We convert to `long` to avoid overflow on `INT_MIN`
* We handle negative sign before recursion
* We split the number into leading and trailing digits

---

# 🖨 ft_show_tab: Core Logic

```c
void ft_show_tab(struct s_stock_str *par)
{
    int i = 0;

    if (!par)
        return;
    while (par[i].str)
    {
        ft_putstr(par[i].str);
        ft_putchar('\n');
        ft_putnbr(par[i].size);
        ft_putchar('\n');
        ft_putstr(par[i].copy);
        ft_putchar('\n');
        i++;
    }
}
```

### Ordered Output Guarantee

For each element, it prints in this exact order:

1. original string (`str`)
2. size (`int`)
3. duplicated string (`copy`)

Each followed by a newline.

This matches the subject specification.

---

# 🧩 Example Walkthrough

Given:

```c
av = {"hello", "42", "world"}
```

`ft_strs_to_tab(3, av)` produces:

| Index | size | str     | copy    |
| ----- | ---- | ------- | ------- |
| 0     | 5    | "hello" | "hello" |
| 1     | 2    | "42"    | "42"    |
| 2     | 5    | "world" | "world" |
| 3     | 0    | NULL    | NULL    |

`ft_show_tab(arr)` prints:

```
hello
5
hello
42
2
42
world
5
world
```

Then stops at `.str == 0`.

---

# 🛑 Common Mistakes & Clarifications

✔ **Q: Can we print `copy` instead of `str`?**

Yes — both contain same content initially.
But `.copy` is guaranteed heap memory, `.str` simply points to the original.

---

✔ **Q: Why sentinel instead of passing `ac`?**

Because sentinel termination lets you iterate without knowing size, just like strings.

---

✔ **Q: Why do we need `ft_putnbr` recursion?**

Because only `write()` is allowed — we cannot convert int to string using `printf()` or `itoa()`.

---

# 🧹 Memory Considerations

`ft_show_tab` **does not free** anything — by design.

Memory ownership rules:

* `arr[i].str` → does **not** need freeing (not allocated by us)
* `arr[i].copy` → **must** be freed eventually
* `arr` array → must be freed

So a proper cleanup after usage:

```c
int i = 0;
while (arr[i].str)
{
    free(arr[i].copy);
    i++;
}
free(arr);
```

Cleanup is **not required** for this exercise, but knowing it is important.

---

# 🎓 Key Takeaways

This exercise reinforces:

* Using sentinel termination (like `'\0'`)
* Printing integers via recursive decomposition
* Safe use of `write()`
* Modular function design
* Clear separation of **display logic** vs **memory allocation logic**

Together with `ft_strs_to_tab`, this is a complete pipeline:

```
argv[]  → ft_strs_to_tab → struct[] → ft_show_tab → terminal
```

Understanding this pipeline is essential for handling more advanced projects later.

---

```
Perfect — here is a **single combined `peer_explanation.md`** covering **Exercise 04 (`ft_strs_to_tab`) and Exercise 05 (`ft_show_tab`)**, plus a **visual memory map section**.

This follows your preferred style: structured, clean, technical, with diagrams and zero renaming of your conventions.

You can paste this directly as `peer_explanation.md` at project level, or inside your `ex04`/`ex05` folders.

---
``````

# 🧩 Exercises 04 & 05 — `ft_strs_to_tab` + `ft_show_tab`


char **av  →  ft_strs_to_tab  →  t_stock_str[]  →  ft_show_tab  →  terminal output

````

Exercise 04 builds the **data structure**, Exercise 05 prints it using the **allowed `write()`** function.

---

# 📦 Exercise 04 — `ft_strs_to_tab`

## 🎯 Goal

Implement:

```c
t_stock_str *ft_strs_to_tab(int ac, char **av);
````

which transforms:

* input: `ac` (number of strings), `av` (array of strings like `argv`)
* output: an **array of `t_stock_str`** allocated on the **heap**

---

## 📁 Required Structure (`ft_stock_str.h`)

Given:

```c
typedef struct s_stock_str
{
	int   size;   // length of the string
	char *str;    // pointer to the original string
	char *copy;   // pointer to a heap-allocated copy
} t_stock_str;
```

> **Important semantic point:**
>
> * `.str` → pointer to the original
> * `.copy` → new allocation using malloc

---

## 🧱 Implementation Summary

### Helpers required:

#### `ft_strlen`

Iterates until `'\0'` and returns length.

```c
int ft_strlen(char *str);
```

#### `ft_strdup`

Allocates `len + 1` bytes, copies characters, adds `'\0'`, returns pointer.

```c
char *ft_strdup(char *src);
```

### `ft_strs_to_tab` core logic:

1. Validate `ac` and `av`
2. Allocate array: `malloc(sizeof(t_stock_str) * (ac + 1))`
3. For each `i < ac`:

   * `size = ft_strlen(av[i])`
   * `str = av[i]`
   * `copy = ft_strdup(av[i])`
4. Add **sentinel element** at `arr[ac]`:

   * `size = 0`
   * `str = 0`
   * `copy = 0`
5. On error, free all `copy`'s + the array

### 🧯 Memory Ownership Rules

| Field  | Memory Owner               | Must Free? |
| ------ | -------------------------- | ---------- |
| `str`  | **caller** (or OS if argv) | ❌ no       |
| `copy` | `ft_strs_to_tab`           | ✔ yes      |
| array  | `ft_strs_to_tab`           | ✔ yes      |

---

## 🧩 Sentinel Termination Pattern

This exercise uses the same pattern as C-strings:

* Strings end with `'\0'`
* Our struct array ends with `.str == 0`

This allows:

```c
while (arr[i].str)
	i++;
```

No need to use `ac` later.

---

# 📢 Exercise 05 — `ft_show_tab`

## 🎯 Goal

Implement:

```c
void ft_show_tab(struct s_stock_str *par);
```

which prints, for each element:

1. `str` followed by `\n`
2. `size` followed by `\n`
3. `copy` followed by `\n`

until sentinel (`par[i].str == 0`).

---

## 🔨 Allowed Functions

Only the low-level:

```c
write()
```

So we implement:

| Function     | Purpose                              |
| ------------ | ------------------------------------ |
| `ft_putchar` | print 1 char                         |
| `ft_putstr`  | print string                         |
| `ft_putnbr`  | print `int` in decimal (recursively) |

All three call `write()`.

---

## 🧠 Printing the Structure

### `ft_putstr`

```c
void ft_putstr(char *str)
{
	if (!str)
		return;
	while (*str)
		write(1, str++, 1);
}
```

### `ft_putnbr`

Uses recursion:

```c
void ft_putnbr(int nbr)
{
	long num = nbr;

	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	if (num >= 10)
		ft_putnbr(num / 10);
	ft_putchar((num % 10) + '0');
}
```

### `ft_show_tab`

```c
void ft_show_tab(struct s_stock_str *par)
{
	int i = 0;

	if (!par)
		return;
	while (par[i].str)
	{
		ft_putstr(par[i].str);
		ft_putchar('\n');
		ft_putnbr(par[i].size);
		ft_putchar('\n');
		ft_putstr(par[i].copy);
		ft_putchar('\n');
		i++;
	}
}
```

---

# 🧩 Step-by-Step Example

Given:

```c
av = {"hello", "42", "world"}
ac = 3
```

`ft_strs_to_tab(ac, av)` produces an array:

| idx | size | str     | copy    |
| --- | ---- | ------- | ------- |
| 0   | 5    | "hello" | "hello" |
| 1   | 2    | "42"    | "42"    |
| 2   | 5    | "world" | "world" |
| 3   | 0    | NULL    | NULL    |

Then `ft_show_tab` prints:

```
hello
5
hello
42
2
42
world
5
world
```

---

# 🧠 Visual Memory Map (Important Section)

Assume the program:

```c
int main(int ac, char **av)
{
	t_stock_str *arr = ft_strs_to_tab(ac, av);
	ft_show_tab(arr);
	...
}
```

### 🧱 Before `ft_strs_to_tab`

```
Stack:
+---------------+
| ac            |
| av → pointers |
+---------------+

RODATA (read-only segment):
"hello\0"
"42\0"
"world\0"
```

### 🧱 After `ft_strs_to_tab`

#### Heap layout:

```
arr:
+----------------------------------------------+
| [0] size=5 str=R1 copy=H1                    |
| [1] size=2 str=R2 copy=H2                    |
| [2] size=5 str=R3 copy=H3                    |
| [3] size=0 str=NULL copy=NULL                |
+----------------------------------------------+

H1 → "hello\0"
H2 → "42\0"
H3 → "world\0"

R1,R2,R3 → point to original strings in RODATA
```

Key observations:

✔ `str` and `copy` point to **different memory regions**
✔ `copy` is always **heap**
✔ Sentinel always sits at `arr[ac]`

---

# ❓ Common Questions from Peers

### **Q: Why `.str = av[i]` and not `ft_strdup`?**

* `.str` represents the original string
* `.copy` represents a new buffer you own
* Doing `ft_strdup` twice wastes memory and breaks ownership model

---

### **Q: Using `.copy` instead of `.str` in display would work?**

**Yes**, because `.copy` duplicates `.str`.
Both contain the same content initially.

---

### **Q: Why do we need a sentinel?**

So we can stop with:

```c
while (arr[i].str)
```

instead of needing the size `ac`.

---

### **Q: Do we need to free memory in `ft_show_tab`?**

No. `ft_show_tab` does not own the memory.
Cleanup belongs to main:

```c
int i = 0;
while (arr[i].str)
	free(arr[i++].copy);
free(arr);
```

---

# 🏁 Final Takeaways

Working through both exercises teaches:

✔ Struct usage
✔ Typedef patterns
✔ Pointer/array relationships
✔ Heap vs stack vs rodata memory
✔ Sentinel-terminated arrays
✔ Custom printing using `write()`
✔ Clean error handling and memory ownership

Together, they form a mini-pipeline:

```
Input strings → Struct array → Pretty printing
```

This is foundational for larger projects that require:

* dynamic memory
* formatted output
* managing data structures
* understanding memory lifetimes

---

```

