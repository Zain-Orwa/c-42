# 🧩 Exercise 01 : `ft_ultimate_ft`

### 📁 Directory

`ex01/`

### 📄 File to turn in

`ft_ultimate_ft.c`

### ⚙️ Allowed functions

None

---

## 🧠 Objective

Create a function that takes a **pointer to pointer to pointer... (nine levels deep)** to an integer and sets that integer’s value to **42**.
Yes — this is a test of your understanding of **how pointers to pointers actually connect through memory**.

---

## 📘 Final Code

```c
void ft_ultimate_ft(int *********nbr)
{
	// With this instruction, we access the final integer value
	// through nine levels of indirection and set it to 42.
	*********nbr = 42;
}
```

---

### 🧩 Testing Code Example

```c
#include <stdio.h>

void ft_ultimate_ft(int *********nbr){
    *********nbr = 42;    
}

int main(void)
{
	int number = 1024;
	int *ptr1 = &number;
	int **ptr2 = &ptr1;
	int ***ptr3 = &ptr2;
	int ****ptr4 = &ptr3;
	int *****ptr5 = &ptr4;
	int ******ptr6 = &ptr5;
	int *******ptr7 = &ptr6;
	int ********ptr8 = &ptr7;
	int *********ptr9 = &ptr8;

	printf("'number' is at address %p and has value %d\n", &number, number);
	printf("'ptr1' points to address %p and dereferencing it gives value %d\n", ptr1, *ptr1);
	printf("'ptr9' points to address %p but connects all the way down to 'number' value %d\n", ptr9, *********ptr9);

	ft_ultimate_ft(ptr9);

	printf("\nAfter ft_ultimate_ft:\n");
	printf("'ptr9' still points to address %p, but that address now holds value %d\n", ptr9, *********ptr9);
	printf("'number' now has the value %d stored at the same address %p\n", number, &number);

	return (0);
}
```

---

## 🔍 Explanation

Let’s break it down clearly.

---

### 🧩 Step 1: Understanding the prototype

```c
void ft_ultimate_ft(int *********nbr);
```

This means:

* The function takes a variable that points nine times before reaching an integer.
* Inside the function, we must **navigate through all those layers** to modify the original value.

So:

```
*********nbr  →  the actual integer value
********nbr   →  pointer to that integer
*******nbr    →  pointer to pointer to that integer
...
nbr           →  pointer to pointer ... (9 layers total)
```

💬 *Why use so many pointers?*
This is just a learning challenge — it trains your understanding of **indirection levels** and how pointers “point to” one another.
In real life, you’ll rarely (if ever) go beyond 2 or 3 levels, but you must conceptually master this.

---

### 🧩 Step 2: How the pointers connect in memory

The chain looks like this in your test program:

```
number  → [ 1024 ]
  ↑
ptr1    → [ address of number ]
  ↑
ptr2    → [ address of ptr1 ]
  ↑
ptr3    → [ address of ptr2 ]
  ↑
ptr4    → [ address of ptr3 ]
  ↑
ptr5    → [ address of ptr4 ]
  ↑
ptr6    → [ address of ptr5 ]
  ↑
ptr7    → [ address of ptr6 ]
  ↑
ptr8    → [ address of ptr7 ]
  ↑
ptr9    → [ address of ptr8 ]  ← we pass THIS one to the function
```

So when the function executes:

```c
*********nbr = 42;
```

it walks through the entire chain until it finally reaches `number` — and replaces `1024` with `42`.

---

### 🧩 Step 3: What happens before and after

Before calling the function:

```
number = 1024
*********ptr9 = 1024
```

After calling `ft_ultimate_ft(ptr9)`:

```
number = 42
*********ptr9 = 42
```

💬 *Why does `ptr9` still point to the same address?*
Because we didn’t change any pointer itself — we only changed **the value at the very end of the chain**.
The pointer chain remains exactly intact; only the target value changes.

---

### 🧩 Step 4: Inside the function

```c
*********nbr = 42;
```

Here’s what happens step by step when dereferencing:

| Dereference    | Meaning                       | Points To  |
| -------------- | ----------------------------- | ---------- |
| `nbr`          | Pointer to pointer... 9 times | → `ptr8`   |
| `*nbr`         | Pointer to pointer... 8 times | → `ptr7`   |
| `**nbr`        | Pointer to pointer... 7 times | → `ptr6`   |
| `***nbr`       | Pointer to pointer... 6 times | → `ptr5`   |
| `****nbr`      | Pointer to pointer... 5 times | → `ptr4`   |
| `*****nbr`     | Pointer to pointer... 4 times | → `ptr3`   |
| `******nbr`    | Pointer to pointer... 3 times | → `ptr2`   |
| `*******nbr`   | Pointer to pointer... 2 times | → `ptr1`   |
| `********nbr`  | Pointer to an int             | → `number` |
| `*********nbr` | Actual int value              | = 42       |

💬 *Why nine stars?*
Because each level removes one layer of indirection until you finally reach the integer value.

---

### 🧩 Step 5: Output Example

✅ Expected terminal output from your test:

```
'number' is at address 0x7ffeeff0dabc and has value 1024
'ptr1' points to address 0x7ffeeff0dabc and dereferencing it gives value 1024
'ptr9' points to address 0x7ffeeff0d9e8 but connects all the way down to 'number' value 1024

After ft_ultimate_ft:
'ptr9' still points to address 0x7ffeeff0d9e8, but that address now holds value 42
'number' now has the value 42 stored at the same address 0x7ffeeff0dabc
```

---

### 🧩 Step 6: What you learn

* How **indirection** works in memory.
* How to **trace connections** through multiple pointer levels.
* That modifying the **dereferenced value** changes the original, no matter how deep the pointer chain goes.

💬 *Is this practical?*
Not really — but it’s an essential conceptual foundation for more complex pointer uses (like arrays of strings, memory management, and data structures).

---

### 🧩 Step 7: Memory Diagram

```
┌─────────────┐
│  number=42  │ ←───────────────┐
└─────────────┘                 │
      ↑                         │
┌─────────────┐                 │
│   *ptr1     │─────────────────┘
└─────────────┘
      ↑
┌─────────────┐
│  **ptr2     │
└─────────────┘
      ↑
┌─────────────┐
│  ***ptr3    │
└─────────────┘
      ↑
     ...
      ↑
┌─────────────┐
│ *********ptr9 │
└─────────────┘
```

Each pointer level stores the **address** of the previous one, leading down to the same single integer variable in memory.

---

### 🧩 Step 8: Summary

| Concept                        | Description                                                           |
| ------------------------------ | --------------------------------------------------------------------- |
| **Pointer**                    | A variable storing an address of another variable                     |
| **Pointer to Pointer**         | A variable storing the address of another pointer                     |
| **Dereference Operator (`*`)** | Used to access the value pointed to                                   |
| **Goal**                       | Change the original integer by dereferencing through 9 pointer levels |
| **Result**                     | The original variable `number` becomes `42`                           |

---

✅ **Peer Ready Summary:**
This exercise demonstrates mastery of **multi-level pointer indirection**.
The function doesn’t change any pointer, only the final integer’s value, proving that even deep pointer chains are just multiple references leading to the same memory address.

