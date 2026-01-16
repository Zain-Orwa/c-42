````markdown
# 🧩 Exercise — `ft_point.h`

This exercise introduces how to define and use a `struct` in C, how to expose it through a header, and how to work with pointers to structs via function calls.

---

## 📁 Project Requirements

The subject says:

> Create a file `ft_point.h` that will compile the following main.

Allowed functions: **None**  
Files to turn in: **ft_point.h**

So the objective is purely about type definition and pointer usage — no output or printing is required.

---

## 📌 Final Code (for context)

### **Header: `ft_point.h`**
```c
#ifndef FT_POINT_H
#define FT_POINT_H

typedef struct s_point
{
	int x;
	int y;
}	t_point;

void set_point(t_point *point);

#endif /* FT_POINT_H */
````

### **Source: `ft_point.c`**

```c
#include "ft_point.h"

void set_point(t_point *point)
{
	point->x = 42;
	point->y = 21;
}

int main(void)
{
	t_point point;

	set_point(&point);

	return (0);
}
```

---

# 🧱 1. Header vs Source (`.h` vs `.c`)

A common question was:

> “Should `set_point` be inside the `.h` or `.c` file?”

### ✔ **Rule**

* The **struct definition** + **function prototype** belong in the **header**
* The **function implementation** belongs in the **source file**

This prevents **multiple definition** linker errors and allows other code to reuse the type cleanly.

---

# 🧱 2. Understanding `typedef struct`

We wrote:

```c
typedef struct s_point
{
	int x;
	int y;
}	t_point;
```

This creates **two names** for the same type:

| Form             | Meaning         |
| ---------------- | --------------- |
| `struct s_point` | raw struct name |
| `t_point`        | typedef alias   |

### ❓ *Question asked:*

> “Which one should we use later — `s_point` or `t_point`? Can we use both?”

### ✔ **Answer**

* In most of your C code, you write **`t_point`**:

  ```c
  t_point p;
  ```
* You *can* still use:

  ```c
  struct s_point p;
  ```

Both are valid. `t_point` exists to avoid the repetitive `struct` keyword.

---

# 🧱 3. Function Parameter: Why `t_point *point`

Subject prototype:

```c
void set_point(t_point *point);
```

### ❓ *Question asked:*

> “Why do we take a pointer instead of just a struct?”

### ✔ **Reason**

Passing a pointer allows the function to **modify the original struct**, not a copy.

Because `main` has:

```c
t_point point;
set_point(&point);
```

We pass `&point` → the **address** of the struct.

---

# 🧱 4. Understanding `&` vs `*` vs `->`

These were common conceptual questions. Let's define each:

### 🔹 `&` — address-of operator

Used when calling a function that expects a pointer:

```c
set_point(&point);
```

This turns a **normal variable** into a **pointer**.

---

### 🔹 `*` — pointer declarator (in definitions)

Used in the **function parameter** to signal we receive an address:

```c
void set_point(t_point *point)
```

Inside the function, `point` now **holds an address**.

---

### 🔹 `->` — struct member access via pointer

Used to access fields through the pointer:

```c
point->x = 42;
```

Equivalent manual dereference is:

```c
(*point).x = 42;
```

`->` exists because `(*point).x` without parentheses becomes `*point.x` due to precedence.

---

# 🧱 5. Reference Syntax vs C Pointers

One attempted function was:

```c
void set_point(t_point &point);
```

This is **C++ syntax** (reference), **not C**.

### ✔ **Why it's invalid in C**

C does **not** support references — only **pointers**.

So correct C form is:

```c
void set_point(t_point *point);
```

---

# 🧱 6. When to Use `&` and When Not To

### ❓ *Question asked:*

> “So sending a struct or normal variable to a function we have to use `&`?”

### ✔ **Short rule**

* Use `&` **only** if you have a **normal variable**
* Do **not** use `&` if you already have a **pointer**

Examples:

```c
int a = 10;
int *p = &a;

foo(&a);  // correct
foo(p);   // correct (p is already a pointer)
```

Same for structs:

```c
t_point point;
t_point *ptr = &point;

set_point(&point); // correct
set_point(ptr);    // correct (ptr is already a pointer)
```

---

# 🧱 7. Dereferencing Normal Variables vs Structs

Another conceptual question was:

> “Is dereferencing structs different from dereferencing normal variables?”

### ✔ **Conceptually:**

No — **both** mean “use what is stored at that memory address”.

### ✔ **Syntactically:**

Yes — structs need member access:

| Target       | Syntax             |
| ------------ | ------------------ |
| normal value | `*p`               |
| struct       | `(*p).x` or `p->x` |

So the struct version adds a field access.

---

# 🧱 8. Memory Model (Simple Diagram)

When running:

```c
t_point point;
set_point(&point);
```

Memory looks like:

```
Stack:
+-----------------+
| point.x (42)    |
| point.y (21)    |
+-----------------+

`&point` gives address of the first byte of this block
```

Inside `set_point`, `point` is a pointer storing that address.

---

# 🧱 9. What This Exercise *Actually Teaches*

Conceptually, this tiny exercise teaches a lot:

✔ defining C structs
✔ using `typedef` to simplify type usage
✔ understanding header exposure
✔ pointer-to-struct usage
✔ passing structs by pointer to modify them
✔ using `&`, `*`, and `->` correctly
✔ difference between C pointers and C++ references

These are foundational C skills used everywhere later (e.g., `libft`, `BSQ`, `so_long`, system programming).

---

# 🏁 Final Summary

* `ft_point.h` defines the **type** and **prototype**
* `ft_point.c` implements the **logic**
* We use `set_point(&point)` to pass the **address**
* Inside the function, `->` writes to the original struct
* C uses **pointers**, not **references**
* Correct usage of `&`, `*`, and `->` is essential

---

# 📝 End

This peer explanation integrates all conceptual questions asked during the solving process and organizes them in a learning-friendly way.

```

---

