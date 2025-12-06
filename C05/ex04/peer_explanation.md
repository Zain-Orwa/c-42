# 🧮 Exercise 04: `ft_fibonacci` – Peer Explanation

---

## 📌 **What This Exercise Is About**

The goal is to create a **recursive function** that returns the **n-th Fibonacci number**, where the sequence starts at index **0** like this:

```
Index: 0  1  2  3  4  5  6  7  ...
Value: 0, 1, 1, 2, 3, 5, 8, 13, ...
```

### Requirements

* Must use **recursion** (not loops).
* Must return **–1** when the index is negative.
* Overflow **does not need** to be handled.
* Prototype:

```c
int ft_fibonacci(int index);
```

---

# 🧠 **How the Code Works**

Here is the function:

```c
int ft_fibonacci(int index){
	if (index < 0) return (-1);
	if (index == 0) return (0);
	if (index == 1) return (1);

	return (ft_fibonacci(index - 1) + ft_fibonacci(index - 2));
}
```

Let’s break it down step-by-step.

---

## 🧱 **1. Base Cases (Stops the recursion)**

### ❗ Negative index → invalid

```c
if (index < 0)
    return (-1);
```

### 🎯 Index 0

```c
if (index == 0)
    return (0);
```

### 🎯 Index 1

```c
if (index == 1)
    return (1);
```

These three conditions prevent infinite recursion and define the start of the Fibonacci sequence.

---

## 🔁 **2. Recursive Case (Keeps the function calling itself)**

```c
return ft_fibonacci(index - 1) + ft_fibonacci(index - 2);
```

This reflects the Fibonacci rule:

> F(n) = F(n − 1) + F(n − 2)

The function keeps calling itself with smaller values until it reaches the base cases.

---

# 📊 **Visual: How the Stack Works (index = 4)**

We compute:

```
F(4) = F(3) + F(2)
```

Break it down:

```
F(4)
├── F(3)
│   ├── F(2)
│   │   ├── F(1) = 1
│   │   └── F(0) = 0
│   └── F(1) = 1
└── F(2)
    ├── F(1) = 1
    └── F(0) = 0
```

Now combine:

```
F(2) = 1 + 0 = 1
F(3) = F(2) + F(1) = 1 + 1 = 2
F(4) = F(3) + F(2) = 2 + 1 = 3
```

Every time the function calls itself, a **new stack frame** is created.
When a branch reaches a base case, it returns upward and the tree starts collapsing.

---

# 🧪 **Example Output**

```c
Index 0: 0
Index 1: 1
Index 2: 1
Index 3: 2
Index 4: 3
Index 5: 5
Index 6: 8
Index 7: 13
Index 8: 21
Index 9: 34
Index -1: -1
Index -5: -1
```

---

# ❗ **Common Mistakes**

| Mistake                                    | Why it’s wrong                             |
| ------------------------------------------ | ------------------------------------------ |
| Forgetting the `index < 0` check           | Required by the subject                    |
| Starting Fibonacci with 1,1 instead of 0,1 | 42 specifies index 0 → 0                   |
| Using loops                                | Only recursion is allowed                  |
| Missing base cases                         | Causes infinite recursion → stack overflow |

---

# 📝 **Peer Evaluation Q&A**

### **Q: Why do we need base cases?**

Base cases stop the recursion. Without them, the function calls itself forever and crashes.

---

### **Q: Why does recursive Fibonacci run slowly?**

Because it recomputes the same values many times.
Example: `F(6)` calculates `F(4)` **three times**.
(But optimizing is NOT required for this exercise.)

---

### **Q: Why return –1 for negative indexes?**

The subject explicitly requires it.
Negative Fibonacci positions are undefined.

---

### **Q: How does the stack "go back" and produce the final number?**

Each recursive call waits.
When a base case returns, the waiting call receives the value, adds it, and returns to its caller.
This continues until the very first call (F(index)) receives its final sum.

---

### **Q: Why is recursion required instead of loops?**

This exercise tests:

* understanding of recursion
* thinking in terms of breaking a problem into smaller subproblems
* tracking call stacks mentally

---

Nice, let’s extend it 👇

---

## 1️⃣ Stack / Call View for Indices 0 → 9

First, a quick reminder of the function:

```c
int ft_fibonacci(int index){
	if (index < 0) return (-1);
	if (index == 0) return (0);
	if (index == 1) return (1);

	return (ft_fibonacci(index - 1) + ft_fibonacci(index - 2));
}
```

### 🧮 Summary Table (what happens for each index)

| index | result F(index) | max recursion depth | total function calls |
| ----- | --------------- | ------------------- | -------------------- |
| 0     | 0               | 1                   | 1                    |
| 1     | 1               | 2                   | 1                    |
| 2     | 1               | 3                   | 3                    |
| 3     | 2               | 4                   | 5                    |
| 4     | 3               | 5                   | 9                    |
| 5     | 5               | 6                   | 15                   |
| 6     | 8               | 7                   | 25                   |
| 7     | 13              | 8                   | 41                   |
| 8     | 21              | 9                   | 67                   |
| 9     | 34              | 10                  | 109                  |

> “Total function calls” means how many times `ft_fibonacci` is executed in total for that index (including all recursive calls).

---

### 🔹 Index 0

**Call:**

* `ft_fibonacci(0)`

  * hits `if (index == 0)` → returns `0`

**Stack:**

Top of stack → `ft_fibonacci(0)`
Then it returns, stack is empty.

---

### 🔹 Index 1

**Call:**

* `ft_fibonacci(1)`

  * hits `if (index == 1)` → returns `1`

**Stack:**

Top of stack → `ft_fibonacci(1)`
Then it returns, stack is empty.

---

### 🔹 Index 2

**Calls (depth-first):**

1. `ft_fibonacci(2)`

   * not `< 0`, not `0`, not `1`
   * returns `ft_fibonacci(1) + ft_fibonacci(0)`

2. `ft_fibonacci(1)` → base case → `1`

3. `ft_fibonacci(0)` → base case → `0`

4. `ft_fibonacci(2)` returns `1 + 0 = 1`

**Stack evolution (top at right):**

1. `[...]` → `f(2)`
2. `f(2)` calls `f(1)` → stack: `f(2)  f(1)`
3. `f(1)` returns `1` → stack: `f(2)`
4. `f(2)` calls `f(0)` → stack: `f(2)  f(0)`
5. `f(0)` returns `0` → stack: `f(2)`
6. `f(2)` returns `1` → stack empty

---

### 🔹 Index 3

We compute:

```text
F(3) = F(2) + F(1)
```

**Call tree:**

```text
f(3)
├── f(2)
│   ├── f(1) = 1
│   └── f(0) = 0
└── f(1) = 1
```

So:

* `f(2)` returns `1`
* `f(1)` returns `1`
* `f(3)` returns `1 + 1 = 2`

Maximum depth: calls chain `f(3) → f(2) → f(1)` → depth 3 + root = 4 levels total.

---

### 🔹 Index 4 (full tree + stack idea)

```text
F(4) = F(3) + F(2)
```

**Call tree:**

```text
f(4)
├── f(3)
│   ├── f(2)
│   │   ├── f(1) = 1
│   │   └── f(0) = 0
│   └── f(1) = 1
└── f(2)
    ├── f(1) = 1
    └── f(0) = 0
```

**Bottom-up evaluation:**

* `f(1)` returns `1`
* `f(0)` returns `0`
* each `f(2)` returns `1 + 0 = 1`
* `f(3)` returns `f(2) + f(1) = 1 + 1 = 2`
* `f(4)` returns `f(3) + f(2) = 2 + 1 = 3`

**Stack max depth:**

Longest chain:

```text
f(4) → f(3) → f(2) → f(1)
```

So depth = 4 + root level = 5.

---

### 🔹 Indices 5 → 9 (pattern)

From here, the tree grows a lot, but the pattern is **always the same**:

```text
f(n) calls f(n-1) and f(n-2)
```

Each of those calls again calls `(n-1, n-2)` and `(n-2, n-3)`, etc.

**Key facts for 5–9:**

* **Max depth** is always `index + 1`
  (because you can go down like `n, n-1, n-2, ..., 1, 0`).
* **Number of calls** grows very fast (exponential).
* Each diagonal path down the left side looks like:

```text
f(n) → f(n-1) → f(n-2) → ... → f(1) → f(0)
```

Some mini-trees:

#### Index 5

```text
f(5)
├── f(4)
│   ├── f(3)
│   └── f(2)
└── f(3)
    ├── f(2)
    └── f(1)
```

(And each `f(3)` and `f(2)` expands like before.)

Result: `5`
Total calls: `15`

---

#### Index 6

```text
f(6) = f(5) + f(4)
```

Both `f(5)` and `f(4)` expand into their own trees.
Result: `8`
Total calls: `25`

---

#### Index 7

```text
f(7) = f(6) + f(5)
```

Result: `13`
Total calls: `41`

---

#### Index 8

```text
f(8) = f(7) + f(6)
```

Result: `21`
Total calls: `67`

---

#### Index 9

```text
f(9) = f(8) + f(7)
```

Result: `34`
Total calls: `109`

> You can imagine the tree now has **hundreds of nodes**. That’s why Fibonacci recursion is a classic example of an **expensive** recursive algorithm.

---

## 2️⃣ Recursive vs Iterative – Side-by-Side

### 🔁 Recursive version (yours)

```c
int ft_fibonacci(int index){
	if (index < 0) return (-1);
	if (index == 0) return (0);
	if (index == 1) return (1);

	return (ft_fibonacci(index - 1) + ft_fibonacci(index - 2));
}
```

### 🔂 Iterative version (alternative, NOT for this exercise, just for comparison)

```c
int ft_fibonacci_iterative(int index)
{
	int a;
	int b;
	int i;
	int temp;

	if (index < 0)
		return (-1);
	if (index == 0)
		return (0);
	if (index == 1)
		return (1);
	a = 0;          // F(0)
	b = 1;          // F(1)
	i = 2;
	while (i <= index)
	{
		temp = a + b; // next Fibonacci
		a = b;
		b = temp;
		i++;
	}
	return (b);      // F(index)
}
```

### ⚖️ Comparison

| Aspect            | Recursive                                  | Iterative                                          |
| ----------------- | ------------------------------------------ | -------------------------------------------------- |
| Logic             | Mirrors math formula `F(n)=F(n−1)+F(n−2)`  | Uses a loop and two variables `a`, `b`             |
| Time complexity   | Exponential (~`O(φ^n)`)                    | Linear `O(n)`                                      |
| Memory (stack)    | `O(n)` call stack                          | `O(1)` extra memory                                |
| Code length       | Short and elegant                          | Slightly longer, but still simple                  |
| Risk              | Big `index` → stack overflow, huge runtime | Handles large `index` safely (until int overflows) |
| For this exercise | ✔ Required                                 | ❌ Not accepted (subject wants recursion)           |

---

## 3️⃣ Performance Explanation

### ⏱ Time Complexity

Each call to `ft_fibonacci(n)` makes **2 recursive calls**, except at the base cases.
Roughly:

```text
T(n) ≈ T(n-1) + T(n-2) + constant
```

This behaves like the Fibonacci sequence itself → **exponential growth**.

* The number of calls is approximately **proportional to `F(n+1)`**.
* More precisely (for this implementation):

```text
calls(n) = 2 * F(n+1) - 1
```

For example:

* `index = 5` → `calls = 15`
* `index = 9` → `calls = 109`
* `index = 30` → already tens of millions of calls

So for **large `index`**, the recursive version becomes **very slow**.

---

### 🧵 Space / Memory Complexity

* Each recursive call adds a frame on the **call stack**.
* Maximum depth for `index = n` is `n + 1` (from `n` down to `0`).
* So the **space complexity** is `O(n)`.

For the iterative version:

* It only uses a fixed number of variables (`a`, `b`, `temp`, `i`).
* **Space complexity:** `O(1)`.

---

# 1️⃣ Step-by-step Stack Trace for `ft_fibonacci(7)`

Function:

```c
int ft_fibonacci(int index){
	if (index < 0) return (-1);
	if (index == 0) return (0);
	if (index == 1) return (1);

	return (ft_fibonacci(index - 1) + ft_fibonacci(index - 2));
}
```

We call:

```c
ft_fibonacci(7);
```

## 🌲 Call / Return Sequence

I’ll use `f(n)` instead of `ft_fibonacci(n)` to keep it short.

### 🔻 Going down + coming back up

```text
CALL  f(7)
  CALL  f(6)
    CALL  f(5)
      CALL  f(4)
        CALL  f(3)
          CALL  f(2)
            CALL  f(1)  -> base case, returns 1
            CALL  f(0)  -> base case, returns 0
          RETURN f(2) = 1 + 0 = 1
          CALL  f(1)  -> base case, returns 1
        RETURN f(3) = f(2) + f(1) = 1 + 1 = 2
        CALL  f(2)
          CALL  f(1)  -> base case, returns 1
          CALL  f(0)  -> base case, returns 0
        RETURN f(2) = 1 + 0 = 1
      RETURN f(4) = f(3) + f(2) = 2 + 1 = 3
      CALL  f(3)
        CALL  f(2)
          CALL  f(1)  -> base case, returns 1
          CALL  f(0)  -> base case, returns 0
        RETURN f(2) = 1 + 0 = 1
        CALL  f(1)  -> base case, returns 1
      RETURN f(3) = 1 + 1 = 2
    RETURN f(5) = f(4) + f(3) = 3 + 2 = 5
    CALL  f(4)
      CALL  f(3)
        CALL  f(2)
          CALL  f(1)  -> 1
          CALL  f(0)  -> 0
        RETURN f(2) = 1
        CALL  f(1)  -> 1
      RETURN f(3) = 2
      CALL  f(2)
        CALL  f(1)  -> 1
        CALL  f(0)  -> 0
      RETURN f(2) = 1
    RETURN f(4) = 3
  RETURN f(6) = f(5) + f(4) = 5 + 3 = 8
  CALL  f(5)
    CALL  f(4)
      CALL  f(3)
        CALL  f(2)
          CALL  f(1)  -> 1
          CALL  f(0)  -> 0
        RETURN f(2) = 1
        CALL  f(1)  -> 1
      RETURN f(3) = 2
      CALL  f(2)
        CALL  f(1)  -> 1
        CALL  f(0)  -> 0
      RETURN f(2) = 1
    RETURN f(4) = 3
    CALL  f(3)
      CALL  f(2)
        CALL  f(1)  -> 1
        CALL  f(0)  -> 0
      RETURN f(2) = 1
      CALL  f(1)  -> 1
    RETURN f(3) = 2
  RETURN f(5) = f(4) + f(3) = 3 + 2 = 5
RETURN f(7) = f(6) + f(5) = 8 + 5 = 13
```

So finally:

```text
ft_fibonacci(7) = 13
```

---

## 🧱 How the Stack Looks (One Example Moment)

Pick this line from above:

```text
CALL f(2)
  CALL f(1)
    -> returns 1
  CALL f(0)
    -> returns 0
RETURN f(2) = 1
```

The **stack** during this small part:

1. Before `f(2)` starts:

```text
[f(7), f(6), f(5), f(4), f(3)]
```

2. When we call `f(2)`:

```text
[f(7), f(6), f(5), f(4), f(3), f(2)]
```

3. Inside `f(2)` → call `f(1)`:

```text
[f(7), f(6), f(5), f(4), f(3), f(2), f(1)]
```

4. `f(1)` hits base case and returns `1` → frame for `f(1)` removed:

```text
[f(7), f(6), f(5), f(4), f(3), f(2)]
```

5. `f(2)` now calls `f(0)`:

```text
[f(7), f(6), f(5), f(4), f(3), f(2), f(0)]
```

6. `f(0)` returns `0` → frame removed:

```text
[f(7), f(6), f(5), f(4), f(3), f(2)]
```

7. `f(2)` computes `1 + 0 = 1`, returns `1`:

```text
[f(7), f(6), f(5), f(4), f(3)]
```

This push / pop pattern repeats for the whole tree.

---

# 2️⃣ Memoized Fibonacci in C (Fast Recursive Version)

> ⚠️ This is **for learning only**.
> The original 42 subject does **not** require (or expect) memoization.

### 🧩 Idea of Memoization

* Normal recursive Fibonacci recomputes the same values many times.
* Memoization = **remember results** the first time you compute them.
* Next time you need `F(n)`, you **return from the table** instead of recursing again.

Result:

* Time complexity goes from **exponential** to **linear** `O(n)`.
* Still uses recursion, but much faster.

---

## ✅ Simple Memoized Version (with a static array)

We’ll:

* Use a `static` array `memo[]` to store computed Fibonacci values.
* Use a special value (e.g. `-2`) to mean “not computed yet”.

```c
#include <unistd.h>

/*
** Memoized recursive Fibonacci.
** - Keeps the same behavior for negative index: returns -1.
** - Uses a static array to avoid recomputing previous results.
*/

int	ft_fibonacci_memo(int index)
{
	static int	memo[47];
	static int	is_init = 0;
	int			i;
	int			result;

	/* Initialize memo array once with a sentinel (-2 = not computed) */
	if (!is_init)
	{
		i = 0;
		while (i < 47)
		{
			memo[i] = -2;
			i++;
		}
		is_init = 1;
	}

	if (index < 0)
		return (-1);
	if (index == 0)
		return (0);
	if (index == 1)
		return (1);

	/* If we already computed F(index), just return it */
	if (index < 47 && memo[index] != -2)
		return (memo[index]);

	/* Otherwise, compute it recursively */
	result = ft_fibonacci_memo(index - 1) + ft_fibonacci_memo(index - 2);

	/* Store the result for future calls (if index is in range) */
	if (index < 47)
		memo[index] = result;

	return (result);
}
```

### Why array size 47?

* `int` overflows around Fib(47) depending on platform,
  so 0–46 are safe for 32-bit `int`.
* For learning, 47 is a nice safe limit. You can change it if you want.

---

## 🧪 Example `main` Using Both Versions

```c
#include <stdio.h>
#include <unistd.h>

int ft_fibonacci(int index);
int ft_fibonacci_memo(int index);

int main(void)
{
	int i;

	printf("Normal recursive:\n");
	i = 0;
	while (i <= 10)
	{
		printf("F(%d) = %d\n", i, ft_fibonacci(i));
		i++;
	}

	printf("\nMemoized recursive:\n");
	i = 0;
	while (i <= 10)
	{
		printf("F(%d) = %d\n", i, ft_fibonacci_memo(i));
		i++;
	}
	return (0);
}
```

Both will print the same values, but for bigger indices like `30`, `35`, `40` you will notice:

* `ft_fibonacci(40)` is very slow 🐌
* `ft_fibonacci_memo(40)` is much faster ⚡

---

