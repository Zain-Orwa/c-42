# 🧩 Exercise 03 : `ft_div_mod`

### 📁 Directory

`ex03/`

### 📄 File to turn in

`ft_div_mod.c`

### ⚙️ Allowed functions

None

---

## 🧠 Objective

Create a function that divides two integers `a` and `b`,
then stores the **quotient** in one variable and the **remainder** in another variable.
The function must receive two pointers to store these results.

---

## 📘 Final Code

```c
void ft_div_mod(int a, int b, int *div, int *mod)
{
	*div = a / b;
	*mod = a % b;
}
```

---

### 🧩 Testing Code

```c
#include <stdio.h>

void ft_div_mod(int a, int b, int *div, int *mod);

int main(void)
{
	int a = 45;
	int b = 5;
	int *div = &a;
	int *mod = &b;

	printf("Before ft_div_mod:\n");
	printf("Pointer 'div' points to address %p that has the value %d stored\n", div, *div);
	printf("Pointer 'mod' points to address %p that has the value %d stored\n", mod, *mod);

	ft_div_mod(a, b, div, mod);

	printf("\nAfter ft_div_mod:\n");
	printf("Pointer 'div' remains pointing to address %p, but now that has the value %d stored\n", div, *div);
	printf("Pointer 'mod' remains pointing to address %p, but now that has the value %d stored\n", mod, *mod);

	return (0);
}
```

---

## 🔍 Explanation

This exercise combines **arithmetic operations** with **pointers**, showing how to return multiple results from a single function.

---

### 🧩 Step 1: Understanding the prototype

```c
void ft_div_mod(int a, int b, int *div, int *mod);
```

This function:

* Takes two **integer values** (`a` and `b`)
* Takes two **pointers** (`div` and `mod`) that will be used to store the results

💬 *Why pointers?*
Because C functions can only return one value normally.
Using pointers allows us to **return multiple results** by directly modifying variables in the caller function’s memory.

---

### 🧩 Step 2: Performing the operations

Inside the function:

```c
*div = a / b;
*mod = a % b;
```

* `a / b` performs **integer division** and assigns the result to the variable pointed to by `div`.
* `a % b` calculates the **remainder** of that division and assigns it to the variable pointed to by `mod`.

💬 *Why do we use the `*` operator here?*
Because `div` and `mod` are pointers — we use `*` to **dereference** them and access the memory location they point to.
That’s where we actually store the computed values.

---

### 🧩 Step 3: What happens in memory

Before the function call:

```
a  = 45
b  = 5
v1 = 0   (div points here)
v2 = 0   (mod points here)
```

After calling:

```c
ft_div_mod(a, b, div, mod);
```

we get:

```
*div = 45 / 5 = 9
*mod = 45 % 5 = 0
```

So now:

```
v1 = 9
v2 = 0
```

💬 *Did the addresses change?*
No — both pointers `div` and `mod` still point to the same variables in memory;
only the **values inside those addresses** changed.

---

### 🧩 Step 4: Output Example

✅ Expected terminal output:

```
Before ft_div_mod:
Pointer 'div' points to address 0x7ffee23b999c that has the value 0 stored
Pointer 'mod' points to address 0x7ffee23b9998 that has the value 0 stored

After ft_div_mod:
Pointer 'div' remains pointing to address 0x7ffee23b999c, but now that has the value 9 stored
Pointer 'mod' remains pointing to address 0x7ffee23b9998, but now that has the value 0 stored
```

---

### 🧩 Step 5: Visualization

#### Memory before the function:

```
┌────────────┬──────────────┬──────────────┐
│ Variable   │ Address      │ Value        │
├────────────┼──────────────┼──────────────┤
│ a          │ 0x7ff...a001 │ 45           │
│ b          │ 0x7ff...a002 │ 5            │
│ v1 (div)   │ 0x7ff...a003 │ 0            │
│ v2 (mod)   │ 0x7ff...a004 │ 0            │
└────────────┴──────────────┴──────────────┘
```

#### Memory after the function:

```
┌────────────┬──────────────┬──────────────┐
│ Variable   │ Address      │ Value        │
├────────────┼──────────────┼──────────────┤
│ a          │ 0x7ff...a001 │ 45           │
│ b          │ 0x7ff...a002 │ 5            │
│ v1 (div)   │ 0x7ff...a003 │ 9            │
│ v2 (mod)   │ 0x7ff...a004 │ 0            │
└────────────┴──────────────┴──────────────┘
```

💬 *What if `b` was zero?*
Division by zero is undefined and causes a runtime error.
In real applications, you should always check if `b != 0` before dividing —
but since 42’s subject doesn’t require that, we keep it minimal and clean.

---

### 🧩 Step 6: Summary

| Concept                    | Description                                                     |
| -------------------------- | --------------------------------------------------------------- |
| **Pointer**                | Stores the address of another variable                          |
| **Dereference (`*`)**      | Accesses or modifies the value at that address                  |
| **Integer division (`/`)** | Gives the quotient                                              |
| **Modulo (`%`)**           | Gives the remainder                                             |
| **Goal of `ft_div_mod()`** | Return both the quotient and remainder using pointers           |
| **Result**                 | The function stores the results directly in memory via pointers |

---

✅ **Peer Ready Summary:**
The `ft_div_mod()` function demonstrates how pointers can be used to **return multiple results** from one function by modifying variables directly in memory.
It cleanly stores both the division and modulo results without returning anything explicitly — a foundational skill for efficient C programming.

