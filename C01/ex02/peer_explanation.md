# 🧩 Exercise 02 : `ft_swap`

### 📁 Directory

`ex02/`

### 📄 File to turn in

`ft_swap.c`

### ⚙️ Allowed functions

None

---

## 🧠 Objective

Create a function that swaps the values of **two integers** whose **addresses** are passed as parameters.
You’ll use pointers to access and modify the real variables in memory.

---

## 📘 Final Code

```c
void ft_swap(int *a, int *b)
{
	int temp;

	// Store temporarily the value pointed to by 'a'
	temp = *a;

	// Copy the value pointed to by 'b' into 'a'
	*a = *b;

	// Copy the saved value from 'temp' into 'b'
	*b = temp;
}
```

---

### 🧩 Testing Code

```c
#include <stdio.h>

void ft_swap(int *a, int *b);

int main(void)
{
	int v1 = 15;
	int v2 = 35;
	int *a = &v1;
	int *b = &v2;

	printf("Before ft_swap:\n");
	printf("Pointer 'a' points to address %p that has the value %d stored\n", a, *a);
	printf("Pointer 'b' points to address %p that has the value %d stored\n", b, *b);

	ft_swap(a, b);

	printf("\nAfter ft_swap:\n");
	printf("Pointer 'a' remains pointing to address %p, but now that has the value %d stored\n", a, *a);
	printf("Pointer 'b' remains pointing to address %p, but now that has the value %d stored\n", b, *b);

	return (0);
}
```

---

## 🔍 Explanation

This exercise introduces a key concept — **modifying variables indirectly through pointers**.
Let’s walk through each step and concept.

---

### 🧩 Step 1: Function prototype and parameters

```c
void ft_swap(int *a, int *b);
```

The parameters `int *a` and `int *b` are **pointers to integers**.
That means they store **the addresses** of the two variables you want to swap.

When you call `ft_swap(&v1, &v2)` —
you’re not sending the values `15` and `35`;
you’re sending **the memory locations** where those values are stored.

💬 *Why use pointers here?*
Because we want to **change the original variables**, not just local copies.
If we passed the values directly, the function would only swap temporary copies and have no effect outside.

---

### 🧩 Step 2: The swap logic

Inside the function:

```c
int temp;
temp = *a;
*a = *b;
*b = temp;
```

Here’s what happens step by step:

| Step | Expression   | Description                                               |
| ---- | ------------ | --------------------------------------------------------- |
| 1️⃣  | `temp = *a;` | Store the value of `a` (e.g., 15) temporarily             |
| 2️⃣  | `*a = *b;`   | Replace the value of `a` with the value of `b` (e.g., 35) |
| 3️⃣  | `*b = temp;` | Assign the saved value (15) into `b`                      |

💬 *Why use `*a` and not `a`?*
Because `a` is a pointer (it holds an address).
`*a` means **the value stored at that address** — that’s what we actually want to swap.

💬 *Would it work without `temp`?*
No. Without a temporary variable, one of the values would get overwritten before the swap completes.
`temp` is like a **temporary safe storage box** to hold one value during the exchange.

---

### 🧩 Step 3: What happens in memory

Before the swap:

```
v1 → [ 15 ]
v2 → [ 35 ]
a  → address of v1
b  → address of v2
```

During the swap:

1. `temp = *a;` → temp = 15
2. `*a = *b;` → v1 becomes 35
3. `*b = temp;` → v2 becomes 15

After the swap:

```
v1 → [ 35 ]
v2 → [ 15 ]
a  → still points to v1
b  → still points to v2
```

💬 *Did the pointers change?*
No — both `a` and `b` still point to the same memory addresses.
Only the **contents of those memory addresses** were exchanged.

---

### 🧩 Step 4: Output Example

✅ Expected output:

```
Before ft_swap:
Pointer 'a' points to address 0x7ffee4a1c98c that has the value 15 stored
Pointer 'b' points to address 0x7ffee4a1c988 that has the value 35 stored

After ft_swap:
Pointer 'a' remains pointing to address 0x7ffee4a1c98c, but now that has the value 35 stored
Pointer 'b' remains pointing to address 0x7ffee4a1c988, but now that has the value 15 stored
```

---

### 🧩 Step 5: Visualization

#### Before swap:

```
┌────────────┬──────────┐
│ Address    │ Value    │
├────────────┼──────────┤
│ &v1 (a)    │ 15       │
│ &v2 (b)    │ 35       │
└────────────┴──────────┘
```

#### After swap:

```
┌────────────┬──────────┐
│ Address    │ Value    │
├────────────┼──────────┤
│ &v1 (a)    │ 35       │
│ &v2 (b)    │ 15       │
└────────────┴──────────┘
```

---

### 🧩 Step 6: Summary

| Concept                 | Description                                                               |
| ----------------------- | ------------------------------------------------------------------------- |
| **Pointer**             | A variable storing the address of another variable                        |
| **Dereferencing (`*`)** | Accessing or modifying the value stored at that address                   |
| **Goal of `ft_swap()`** | Exchange the values of two variables in memory                            |
| **Result**              | The variables’ values are swapped, while their addresses remain unchanged |

✅ **Final check:**

* Uses no forbidden functions
* Norm-compliant
* Efficient (O(1) time, constant memory)
* Demonstrates solid understanding of pointers

---

✅ **Peer Ready Summary:**
The function correctly swaps two integers through their memory addresses, using pointers and a temporary variable.
It shows that changing values through pointers affects the **original variables**, not local copies — the foundation of all in-place operations in C.

