#Exercise 03 : 🔁ft_recursive_power — Peer Explanation

---

## 📌 Exercise Goal

Write a **recursive** function that computes `nb` raised to the power `power`.

The exercise requires:

* No overflow handling
* Negative power → return 0
* 0^0 must return 1
* Must use **recursion** (not loops)

---

## 🧠 Key Idea: What Is Recursion?

Recursion means:

> A function **calls itself** with a smaller/simpler version of the same problem,
> until it reaches a **base case**.

Example of recursion pattern:

```
function(x):
    if x is simple → return value
    else → return something + function(x - 1)
```

For exponentiation:

```
nb^power = nb × nb^(power - 1)
```

So the recursion naturally fits.

---

## 🧱 Final Code (your version)

```c
#include <unistd.h>
#include <stdio.h>

int ft_recursive_power(int nb, int power){
	if (power == 0) return (1);
	if (power < 0) return (0);
	
	return (nb * ft_recursive_power(nb, power - 1));
}

int main(void)
{
    printf("2^4  = %d\n", ft_recursive_power(2, 4));   // 16
    printf("5^0  = %d\n", ft_recursive_power(5, 0));   // 1
    printf("0^0  = %d\n", ft_recursive_power(0, 0));   // 1 (by subject)
    printf("3^-2 = %d\n", ft_recursive_power(3, -2));  // 0 (by subject)
    return 0;
}
```

---

## 🧩 Explanation of the Logic

### 1. Base Case 1 — Power = 0

```c
if (power == 0) return (1);
```

This covers:

* Math rule: any number^0 = 1
* Subject rule: 0^0 must return 1

This is the **foundation** of the recursion.

---

### 2. Base Case 2 — Negative Power

```c
if (power < 0) return (0);
```

Subject says:

> “A power lower than 0 returns 0.”

So we stop the recursion immediately.

---

### 3. Recursive Case

```c
return (nb * ft_recursive_power(nb, power - 1));
```

This is the heart of recursion.

For example:

```
ft_recursive_power(2, 4)
= 2 * ft_recursive_power(2, 3)
= 2 * (2 * ft_recursive_power(2, 2))
= 2 * 2 * ft_recursive_power(2, 1)
= 2 * 2 * 2 * ft_recursive_power(2, 0)
= 2 * 2 * 2 * 1
= 16
```

Each call reduces the exponent by 1 until `power == 0`.

---

## 🔍 Visual Call Stack Diagram

Example: `ft_recursive_power(2, 3)`

```
ft_recursive_power(2, 3)
    → returns 2 * ft_recursive_power(2, 2)
        → returns 2 * ft_recursive_power(2, 1)
            → returns 2 * ft_recursive_power(2, 0)
                → power == 0 → returns 1

Unwinding:
ft_recursive_power(2,0) = 1
ft_recursive_power(2,1) = 2 * 1 = 2
ft_recursive_power(2,2) = 2 * 2 = 4
ft_recursive_power(2,3) = 2 * 4 = 8
```

The value flows back **up** the recursion tree.

---

## 🧪 Program Output

```
2^4  = 16
5^0  = 1
0^0  = 1
3^-2 = 0
```

Matches exactly what the subject requires.

---

## ❓ Peer Evaluation Q&A

**Q: Why does the function stop when `power == 0`?**
A: Because this is the smallest valid exponent, and mathematically `nb^0 = 1`.

---

**Q: Why must negative power return 0?**
A: That’s what the subject requires. Normally negative powers produce fractions, but this exercise doesn’t handle that.

---

**Q: Why no loop?**
A: This exercise explicitly requires a **recursive** solution, so every reduction must happen through function calls.

---

**Q: Does this handle overflow?**
A: No. Overflow causes undefined behavior, which the subject explicitly accepts.

---

**Q: Does this handle 0^0?**
A: Yes — because `power == 0` returns 1 automatically.

---

# 📘 Comparison: Iterative vs Recursive Power Functions

## 🔄 1. Iterative Version (Loop-based)

### ✔ How it works

* Starts with `result = 1`
* Multiplies `result` by `nb` in a loop
* Decreases `power` until it reaches 0
* Returns the final accumulated value

### ✔ Advantages

* Very fast
* No function-call overhead
* No risk of stack overflow
* Easy to understand and debug

### ✔ Disadvantages

* Less elegant for mathematical recursion
* Requires managing loop counters manually

---

## 🔁 2. Recursive Version (Function calling itself)

### ✔ How it works

* Defines base cases:

  * `power == 0` → return 1
  * `power < 0` → return 0
* Each call reduces the power:

  ```
  nb^power = nb * nb^(power - 1)
  ```

### ✔ Advantages

* Matches the mathematical definition directly
* Code is shorter and expressive
* Natural example for learning recursion

### ✔ Disadvantages

* **Slower** due to many function calls
* Uses more memory (stack frames)
* Large `power` values may cause stack overflow

---

## ⚖️ Conclusion

| Aspect       | Iterative               | Recursive                       |
| ------------ | ----------------------- | ------------------------------- |
| Speed        | ⭐️ Faster               | Slower (call overhead)          |
| Memory usage | Low                     | High (stack frame per call)     |
| Elegance     | Straightforward         | Very elegant mathematically     |
| Safety       | No stack overflow       | Possible stack overflow         |
| Use-case     | Practical program logic | Learning recursion, clear logic |

Both solve the same problem — the difference is *how* they get there.

---

# 🧠 Memory Diagram — Recursive Call Stack

Example: **ft_recursive_power(2, 4)**

Each call waits for the next call to finish.

```
Call Stack (top = most recent):

-----------------------------------------
ft_recursive_power(2, 0) → returns 1
-----------------------------------------
ft_recursive_power(2, 1) → returns 2 * 1 = 2
-----------------------------------------
ft_recursive_power(2, 2) → returns 2 * 2 = 4
-----------------------------------------
ft_recursive_power(2, 3) → returns 2 * 4 = 8
-----------------------------------------
ft_recursive_power(2, 4) → returns 2 * 8 = 16
-----------------------------------------
main()
```

### Key Point

The stack **grows downward** until it hits the base case, then **unwinds upward** as each call returns.

---

# 🌳 Visual Recursion Tree (nb = 3, power = 4)

We illustrate:

```
3^4 = 3 * 3^3
3^3 = 3 * 3^2
3^2 = 3 * 3^1
3^1 = 3 * 3^0
3^0 = 1
```

### Recursion Tree Diagram

```
ft_recursive_power(3, 4)
│
└── 3 * ft_recursive_power(3, 3)
        │
        └── 3 * ft_recursive_power(3, 2)
                │
                └── 3 * ft_recursive_power(3, 1)
                        │
                        └── 3 * ft_recursive_power(3, 0)
                                │
                                └── 1  ← base case
```

### Unwind phase (results returning upward)

```
ft_recursive_power(3, 0) = 1
ft_recursive_power(3, 1) = 3 * 1 = 3
ft_recursive_power(3, 2) = 3 * 3 = 9
ft_recursive_power(3, 3) = 3 * 9 = 27
ft_recursive_power(3, 4) = 3 * 27 = 81
```

Final answer: **81**

---

