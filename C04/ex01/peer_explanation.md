````markdown
# 📘 Exercise XX — ft_putstr (Pointer Version)

## 🧾 Function Prototype
```c
void ft_putstr(char *str);
````

---

## 🎯 Goal of the Function

The purpose of `ft_putstr` is simple:

> **Print a string to standard output, one character at a time**,
> without using any allowed library functions except `write`.

---

# 🧠 Final Solution (Pointer Version)

```c
#include <unistd.h>

void	ft_putstr(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr != '\0')
	{
		write(1, ptr, 1);
		ptr++;
	}
}
```

---

# 🧩 How This Pointer Version Works

### 1️⃣ `ptr = str;`

We create a pointer `ptr` and make it point to the **first character** in the string.

Memory example (`"Hello"`):

```
str → ['H']['e']['l']['l']['o']['\0']
ptr → ['H']['e']['l']['l']['o']['\0']
```

Both point to the same place at the start.

---

### 2️⃣ `while (*ptr != '\0')`

`*ptr` means "the character stored at the memory location `ptr` is pointing to."

The loop continues as long as the character is NOT the null terminator.

So it prints:

```
'H' → 'e' → 'l' → 'l' → 'o'
```

And stops when it reaches `'\0'`.

---

### 3️⃣ `write(1, ptr, 1);`

This is the **critical detail**.

* `ptr` is the **address of the current character**
* `write(1, ptr, 1)`
  → writes ONE byte starting at the address stored in `ptr`

So this prints **exactly one character** at a time.

👉 **Important:**
You MUST use `ptr`, not `&ptr`.

* `ptr` → points to a character in the string
* `&ptr` → points to the pointer variable itself (wrong by 1 level)

---

### 4️⃣ `ptr++;`

We move the pointer one byte forward in memory.

Pointer movement looks like:

```
ptr → 'H'
ptr → 'e'
ptr → 'l'
ptr → 'l'
ptr → 'o'
ptr → '\0'  (loop stops)
```

This is exactly how pointer arithmetic works in C:
incrementing a `char *` moves to the **next character**.

---

# 🧠 Why Use Pointers Here?

Pointers make the function:

* compact
* fast
* idiomatic for low-level C
* free from indexing (`str[i]`)

They also avoid doing extra arithmetic such as `str[i]`, `str[i + 1]`, etc.

You literally walk through the string the same way C walks through memory.

---

# ⚠️ Common Mistake (Your Original Error)

You originally wrote:

```c
write(1, &ptr, 1);
```

This prints **1 byte of the pointer address**, NOT the character.

Explanation:

* `ptr` → address of the character (correct)
* `&ptr` → address of the pointer variable itself (wrong)

So always write:

```c
write(1, ptr, 1);
```

Never use `&ptr` here.

---

# 📝 Summary (Copy/Paste Notes)

* `ptr = str;` → start at the first character.
* `*ptr` → read the current character.
* `write(1, ptr, 1);` → print the current character.
* `ptr++` → move pointer to next character.
* Stop when `*ptr == '\0'`.

This is the cleanest and most correct pointer-based implementation.

---


