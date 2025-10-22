# 🧩 Exercise 00 : `ft_ft`

### 📁 Directory

`ex00/`

### 📄 File to turn in

`ft_ft.c`

### ⚙️ Allowed functions

None

---

## 🧠 Objective

Create a function that takes a **pointer to an integer** and assigns the value **42** to the integer that the pointer references.

---

## 📘 Final Code

```c
#include <unistd.h>
#include <stdio.h>

void ft_ft(int *nbr)
{
	*nbr = 42;
}

int main(void)
{
	int n = 5;
	int *nbr = &n;

	printf("Before ft_ft:\n");
	printf("Variable 'n' is stored at address %p and holds the value %d\n", &n, n);
	printf("Pointer 'nbr' points to the same address %p and dereferencing it gives the value %d\n", nbr, *nbr);

	ft_ft(nbr);

	printf("\nAfter ft_ft:\n");
	printf("Pointer 'nbr' still points to address %p, but now that memory holds the value %d\n", nbr, *nbr);
	printf("The variable 'n' now has the new value %d stored.\n", n);

	return (0);
}
```

---

## 🔍 Explanation

Let’s break down this simple pointer manipulation step by step — this is your **first real pointer exercise** in C.

---

### 🧩 Step 1: Understanding the function prototype

```c
void ft_ft(int *nbr);
```

The parameter `int *nbr` means the function **receives a pointer** to an integer.
That pointer stores the **memory address** of an integer variable defined elsewhere (in this case, `n` inside `main`).

> 💬 **Question:** Why do we use a pointer instead of a normal variable?
> Because if we passed the integer directly, the function would get a **copy** of the value — changing it wouldn’t affect the original.
> A pointer gives the function **direct access** to the original memory location, allowing us to modify the value stored there.

---

### 🧩 Step 2: What does `*nbr = 42;` do?

The `*` operator **dereferences** the pointer — it accesses the actual value stored at the memory address that `nbr` is pointing to.
So:

```c
*nbr = 42;
```

means:
➡️ “Go to the address stored inside `nbr`, and replace whatever value is there with 42.”

> 💬 **Question:** What is the difference between `nbr` and `*nbr`?
>
> * `nbr` → holds the **address** of `n`.
> * `*nbr` → accesses the **value** stored at that address.
>   Setting `*nbr = 42` modifies `n` itself.

---

### 🧩 Step 3: The `main()` function

In your test code:

```c
int n = 5;
int *nbr = &n;
```

* `n` is a normal integer variable that holds the value `5`.
* `nbr = &n` assigns to `nbr` the **address of `n`**.
  So `nbr` now points to the memory location of `n`.

> 💬 **Question:** What does `&n` mean?
> The `&` operator gives you the **memory address** of `n`.
> That’s what makes the connection between `n` and the pointer `nbr`.

---

### 🧩 Step 4: Before calling `ft_ft()`

When you print:

```c
printf("Variable 'n' is stored at address %p and holds the value %d\n", &n, n);
printf("Pointer 'nbr' points to the same address %p and dereferencing it gives the value %d\n", nbr, *nbr);
```

You’ll see that both `&n` and `nbr` print the **same address** (because `nbr` points to `n`),
and both `n` and `*nbr` show the same **value** — `5`.

That means:

* `&n == nbr`
* `n == *nbr`

---

### 🧩 Step 5: After calling `ft_ft(nbr);`

Inside the function:

```c
*nbr = 42;
```

changes the content of the memory address where `n` lives.

When you return to `main()`, that same memory address now stores `42`.

So, printing again:

```c
printf("Pointer 'nbr' still points to address %p, but now that memory holds the value %d\n", nbr, *nbr);
printf("The variable 'n' now has the new value %d stored.\n", n);
```

will output something like:

```
After ft_ft:
Pointer 'nbr' still points to address 0x7ffee7c8d9bc, but now that memory holds the value 42
The variable 'n' now has the new value 42 stored.
```

> 💬 **Question:** Did the pointer change after the function call?
> No — the pointer still points to the **same address**.
> Only the **value stored at that address** was modified.

---

### 🧩 Step 6: Memory Visualization

| Variable | Value        | Address      | Points To |
| -------- | ------------ | ------------ | --------- |
| `n`      | 42           | `0x7ffee...` | —         |
| `nbr`    | `0x7ffee...` | `0x7ffee...` | `n`       |

> 💬 **Question:** What happens if we remove the `*` in the assignment?
> If you wrote `nbr = 42;`, you’d try to assign an integer to a pointer —
> ❌ invalid logic — it would break the connection between the pointer and the variable `n`.
> The correct operation is always `*nbr = value;` when modifying the pointed variable.

---

### 🧩 Step 7: Why 42?

The number `42` is a symbolic tradition in programming — it comes from *The Hitchhiker’s Guide to the Galaxy*, where **42 is “the answer to life, the universe, and everything.”**
In the 42 curriculum, it’s used as a simple test value to confirm correct pointer behavior.

---

### 🧩 Step 8: Summary

| Concept                 | Description                                                    |
| ----------------------- | -------------------------------------------------------------- |
| **Pointer**             | A variable that stores the memory address of another variable  |
| **Dereferencing (`*`)** | Accesses the value stored at the address the pointer refers to |
| **Address-of (`&`)**    | Returns the memory address of a variable                       |
| **Goal of `ft_ft()`**   | Modify an integer indirectly using its pointer                 |
| **Result**              | The original variable is changed from 5 → 42                   |

✅ **Final Output Example:**

```
Before ft_ft:
Variable 'n' is stored at address 0x7ffee7c8d9bc and holds the value 5
Pointer 'nbr' points to the same address 0x7ffee7c8d9bc and dereferencing it gives the value 5

After ft_ft:
Pointer 'nbr' still points to address 0x7ffee7c8d9bc, but now that memory holds the value 42
The variable 'n' now has the new value 42 stored.
```

