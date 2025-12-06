# 🧮 Exercise 05: `ft_sqrt` — Peer Explanation

---

## 📌 **Goal of the Exercise**

This function must:

* Return the **integer square root** of `nb`, **only if** the square root is a perfect integer.
* Return **0** when:

  * `nb` is **negative**
  * `nb` is **0 or 1** → still correct to return 0 and 1
  * The square root is **irrational** (not a perfect square)

### Required Prototype

```c
int ft_sqrt(int nb);
```

### Allowed functions

**None** — you must implement it using basic arithmetic and loops.

---

# 🧠 How the Code Works

Here is the solution:

```c
int ft_sqrt(int nb){
	int i;
	
	if (nb <= 0)
		return (0);

	i = 0;
	while (i <= 46340 && i * i <= nb)
	{
		if (i * i == nb)
			return (i);

		i++;
	}
	return (0);
}
```

Let’s break it down.

---

## 🧱 1. Handling invalid or trivial inputs

```c
if (nb <= 0)
    return (0);
```

* Negative numbers have **no real square root** → return `0`
* `0` → sqrt is `0`, but returning `0` matches the rule
* Square root logic continues normally for positive `nb`

---

## 🔢 2. Looping through integers to find a perfect square

```c
i = 0;
while (i <= 46340 && i * i <= nb)
```

### Why start at 0?

Because:

```
0 * 0 = 0
```

This handles the case `nb == 0`.

### Why check `i * i <= nb`?

We stop once `i^2` passes the number, because after that square roots only become bigger.

### Why limit `i <= 46340`?

Because:

```
46340^2 = 2147395600   (still fits in an int)
46341^2 = 2147488281   (overflows 32-bit signed int)
```

So 46340 is the **safe maximum** integer where `i * i` will not overflow.

---

## 🎯 3. Detecting the perfect square

Inside the loop:

```c
if (i * i == nb)
	return (i);
```

If we find an exact match, we immediately return the integer square root.

Examples:

* `nb = 25` → `5 * 5 == 25`
* `nb = 121` → `11 * 11 == 121`
* `nb = 8` → never matches → return `0`

---

## ❌ 4. Not a perfect square → return 0

```c
return (0);
```

If the loop finishes without finding `i*i == nb`, the number is **not** a perfect square.

Example:
`8 → 0`
`50 → 0`
`2147395601 → 0` (one above 46340²)

---

# 🔍 Visual Explanation (Example: `nb = 25`)

We want integer `i` such that:

```
i * i == 25
```

Loop runs:

```
i = 0 → 0
i = 1 → 1
i = 2 → 4
i = 3 → 9
i = 4 → 16
i = 5 → 25  ✔ match
```

Return → **5**

---

# 🔍 Visual Explanation (Example: `nb = 8`) — Not a Square

```
i = 0 → 0
i = 1 → 1
i = 2 → 4
i = 3 → 9  (now i*i > 8 → stop)
```

No match → return **0**

---

# 🧪 Example Output

Given the test main:

```
ft_sqrt(0) = 0
ft_sqrt(1) = 1
ft_sqrt(4) = 2
ft_sqrt(9) = 3
ft_sqrt(25) = 5
ft_sqrt(8) = 0
ft_sqrt(-4) = 0
ft_sqrt(100) = 10
ft_sqrt(121) = 11
```

---

# ⚠️ Common Mistakes

| Mistake                             | Why it’s wrong                                  |
| ----------------------------------- | ----------------------------------------------- |
| Forgetting overflow guard (`46340`) | Leads to integer overflow when squaring numbers |
| Returning `i` even when imperfect   | The exercise requires returning **0**           |
| Starting loop at 1                  | Breaks the case for `nb = 0`                    |
| Using floating-point math           | Forbidden + inaccurate for this task            |
| Using `sqrt()` from math            | Not allowed                                     |

---

# 📝 Peer Evaluation Q&A

### **Q: Why not use `sqrt()` from `<math.h>`?**

Because **no external functions** are allowed. You must compute it manually.

---

### **Q: Why return 0 for irrational roots (like √8)?**

The subject requires returning **0** if the number does **not** have an integer square root.

---

### **Q: Why the magic number 46340?**

It’s the largest integer where:

```
i * i does not overflow a 32-bit signed int
```

---

### **Q: Why check `i * i <= nb`?**

Because once `i²` is larger than `nb`, the perfect square can not appear after it.

---

### **Q: Why is this loop efficient enough for 42?**

Worst case: loop runs from `0` to `46340` → ~46k iterations.
This is totally fine in C.

---


# 1️⃣ **A Faster (Educational) Binary Search Version of `ft_sqrt`**

⚠️ **NOT allowed for the exercise**, but excellent to understand efficiency.

Binary search finds the integer square root in **O(log n)** time instead of **O(n)**.

### ✅ **Educational version using binary search**

```c
int	ft_sqrt_binary(int nb)
{
	int low;
	int high;
	int mid;
	long sq;  // use long to avoid overflow

	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);

	low = 1;
	high = nb / 2;

	while (low <= high)
	{
		mid = (low + high) / 2;
		sq = (long)mid * mid;

		if (sq == nb)
			return (mid);
		else if (sq < nb)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (0);
}
```

### Why this is faster:

Instead of checking:

```
1, 2, 3, 4, 5, 6, ...
```

Binary search checks:

```
middle → half → quarter → eighth ...
```

Which reduces the number of steps dramatically.

---

# 2️⃣ **Step-by-Step Visualization (choose nb = 25)**

This will show how your actual loop-based version works.

Your code:

```c
while (i <= 46340 && i * i <= nb)
```

We evaluate `i * i` at each step:

```
nb = 25

i = 0 → 0 * 0 = 0   <= 25 → continue
i = 1 → 1 * 1 = 1   <= 25 → continue
i = 2 → 2 * 2 = 4   <= 25 → continue
i = 3 → 3 * 3 = 9   <= 25 → continue
i = 4 → 4 * 4 = 16  <= 25 → continue
i = 5 → 5 * 5 = 25  MATCH! → return 5
```

### Visual "track" of the loop:

```
+-----+---------+----------+
|  i  |  i * i  |  Action  |
+-----+---------+----------+
|  0  |    0    | continue |
|  1  |    1    | continue |
|  2  |    4    | continue |
|  3  |    9    | continue |
|  4  |   16    | continue |
|  5  |   25    | return 5 |
+-----+---------+----------+
```

Loop stops → function exits.

---

# Step-by-step Visualization (choose nb = 8 → NOT a square)

```
i = 0 → 0 <= 8 → continue
i = 1 → 1 <= 8 → continue
i = 2 → 4 <= 8 → continue
i = 3 → 9 > 8 → STOP LOOP
```

Since loop ends without finding a match → return `0`.

Table:

```
+-----+---------+----------+
|  i  |  i * i  |  Action  |
+-----+---------+----------+
|  0  |    0    | continue |
|  1  |    1    | continue |
|  2  |    4    | continue |
|  3  |    9    | STOP     |
+-----+---------+----------+
```

Return → **0**

---

# 3️⃣ **Rewrite in 42 GitHub-ready Style (your preferred formatting)**

Exactly same format you liked from previous explanations.

---

# 🧮 Exercise 05: `ft_sqrt` — Peer Explanation (Refined GitHub Style)

---

## 📌 Overview

`ft_sqrt` returns:

* The **integer square root** of `nb`, *only if it is perfect*
* `0` if:

  * `nb < 0`
  * the square root is irrational (not a whole number)

### Prototype

```c
int ft_sqrt(int nb);
```

---

## 🧠 Logic Breakdown

### 1. Invalid or trivial cases

```c
if (nb <= 0)
	return (0);
```

Negative numbers cannot have real square roots → return 0.
Zero returns 0 by definition.

---

### 2. Loop through possible roots

```c
while (i <= 46340 && i * i <= nb)
```

* `46340` is the largest integer whose square fits in a 32-bit `int`
* We stop early if `i*i` becomes larger than nb

---

### 3. Found a perfect square

```c
if (i * i == nb)
	return (i);
```

Immediate return.

---

### 4. Otherwise → irrational → return 0

```c
return (0);
```

---

## 🔍 Example Outputs

```
ft_sqrt(0) = 0
ft_sqrt(1) = 1
ft_sqrt(4) = 2
ft_sqrt(9) = 3
ft_sqrt(25) = 5
ft_sqrt(8) = 0
ft_sqrt(-4) = 0
ft_sqrt(100) = 10
ft_sqrt(121) = 11
```

---

# 🧱 Visual Examples

## Perfect square: nb = 25

```
i = 0 → 0
i = 1 → 1
i = 2 → 4
i = 3 → 9
i = 4 → 16
i = 5 → 25 → MATCH → return 5
```

## Not a perfect square: nb = 8

```
i = 0 → 0
i = 1 → 1
i = 2 → 4
i = 3 → 9 → loop stops
return 0
```

---

# ❓ Peer Evaluation Q&A

### **Q: Why do we stop at 46340?**

To avoid integer overflow when doing `i * i`.

### **Q: Why return 0 for irrational roots?**

The subject requires this behavior.

### **Q: Why use `i * i <= nb`?**

Once `i²` is larger than `nb`, the root cannot be `i` or anything higher.

### **Q: Could this be faster?**

Yes — using **binary search** (shown above), but not allowed in the exercise.

---


Nice, let’s power-up `ft_sqrt` properly 😎
I’ll give you:

1. Memory diagram for `ft_sqrt`
2. Loop vs binary-search comparison
3. Animation-style explanation script (for your YouTube video)
4. Cheat sheet + generator for perfect squares up to 46340²

---

## 1️⃣ Memory Diagram for `ft_sqrt`

Code:

```c
int ft_sqrt(int nb){
	int i;
	
	if (nb <= 0)
		return (0);

	i = 0;
	while (i <= 46340 && i * i <= nb)
	{
		if (i * i == nb)
			return (i);
		i++;
	}
	return (0);
}
```

Let’s track a **single call**: `ft_sqrt(25)`.

### Stack & Variables

When `ft_sqrt(25)` is called:

**Stack frame for `ft_sqrt`:**

| Variable | Value |
| -------- | ----- |
| nb       | 25    |
| i        | ?     |

---

### Step-by-step evolution

#### 1. Enter function

```c
nb = 25
i  = (uninitialized yet)
```

Check:

```c
if (nb <= 0)  // 25 <= 0 ? → false
```

So we skip the early return.

---

#### 2. Initialize `i`

```c
i = 0;
```

Memory:

| Variable | Value |
| -------- | ----- |
| nb       | 25    |
| i        | 0     |

---

#### 3. First loop check

Condition:

```c
while (i <= 46340 && i * i <= nb)
```

* `i <= 46340` → `0 <= 46340` → true
* `i * i <= nb` → `0 * 0 <= 25` → `0 <= 25` → true

So we enter the loop.

Inside loop:

```c
if (i * i == nb)  // 0 * 0 == 25 ? → false
i++;              // i becomes 1
```

Memory after first iteration:

| Variable | Value |
| -------- | ----- |
| nb       | 25    |
| i        | 1     |

---

#### 4. Second iteration

Check condition again:

* `1 <= 46340` → true
* `1 * 1 <= 25` → true

Inside:

```c
if (1 * 1 == 25) → false
i++;  // i = 2
```

Memory:

| Variable | Value |
| -------- | ----- |
| nb       | 25    |
| i        | 2     |

---

#### 5. Third iteration

* `2 <= 46340` → true
* `2 * 2 = 4 <= 25` → true

Inside:

```c
if (4 == 25) → false
i++;  // i = 3
```

Memory:

| nb | i |
| -- | - |
| 25 | 3 |

---

#### 6. Fourth iteration

* `3 <= 46340` → true
* `3 * 3 = 9 <= 25` → true

Inside:

```c
if (9 == 25) → false
i++;  // i = 4
```

Memory:

| nb | i |
| -- | - |
| 25 | 4 |

---

#### 7. Fifth iteration

* `4 <= 46340` → true
* `4 * 4 = 16 <= 25` → true

Inside:

```c
if (16 == 25) → false
i++;  // i = 5
```

Memory:

| nb | i |
| -- | - |
| 25 | 5 |

---

#### 8. Sixth iteration

* `5 <= 46340` → true
* `5 * 5 = 25 <= 25` → true

Inside:

```c
if (5 * 5 == 25) → true
return (5);
```

* The function returns `5`
* The `ft_sqrt` stack frame is popped from the stack
* Control goes back to `main`, with value `5`

No more code in `ft_sqrt` after that point is executed.

---

## 2️⃣ Loop Version vs Binary Search Version

### A. Your loop version (linear search)

```c
int ft_sqrt(int nb){
	int i;
	
	if (nb <= 0)
		return (0);
	i = 0;
	while (i <= 46340 && i * i <= nb)
	{
		if (i * i == nb)
			return (i);
		i++;
	}
	return (0);
}
```

### B. Binary search version (educational)

```c
int	ft_sqrt_binary(int nb)
{
	int  low;
	int  high;
	int  mid;
	long sq;

	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	low = 1;
	high = nb / 2;
	while (low <= high)
	{
		mid = (low + high) / 2;
		sq = (long)mid * mid;
		if (sq == nb)
			return (mid);
		else if (sq < nb)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (0);
}
```

### C. Comparison Table

| Aspect           | Linear Loop Version          | Binary Search Version                        |
| ---------------- | ---------------------------- | -------------------------------------------- |
| Strategy         | Try all `i` from 0 up to √nb | Repeatedly cut search range in half          |
| Time complexity  | O(√n)                        | O(log n)                                     |
| Steps for nb=10⁶ | ~1000 iterations             | ~20 iterations                               |
| Implementation   | Very simple                  | Slightly more complex                        |
| Overflow safety  | Uses 46340 limit             | Uses `long` for `mid * mid`                  |
| 42 subject       | ✅ fully valid                | ❌ overkill / not required (but good to know) |

---

## 3️⃣ Animation-style Explanation (Video Script)

Here’s a script you can almost read directly in a video, plus what to show on the screen.

---

### 🗣️ Voiceover Script + Visuals

**Scene 1 – Intro**

> “In this video, we’ll build our own `ft_sqrt` function.
> It takes an integer and returns its **integer square root**—but **only if** the number is a perfect square.
> Otherwise, it returns zero.”

**Visual:**
Show text `ft_sqrt(int nb)` and examples:

* `ft_sqrt(25) → 5`
* `ft_sqrt(8) → 0`
* `ft_sqrt(-4) → 0`

---

**Scene 2 – Idea**

> “The idea is simple:
> we try numbers starting from 0, square them, and check if any of them exactly matches our input.”

**Visual:**
Number line or table:

`i: 0 1 2 3 4 5 ...`
`i*i: 0 1 4 9 16 25 ...`

Circle `25` when reached.

---

**Scene 3 – Code Walkthrough (structure)**

Show the function on screen and highlight blocks while you talk.

```c
int ft_sqrt(int nb){
    int i;
    
    if (nb <= 0)
        return (0);

    i = 0;
    while (i <= 46340 && i * i <= nb)
    {
        if (i * i == nb)
            return (i);
        i++;
    }
    return (0);
}
```

**Voiceover:**

1. **Input check**

   > “First, we reject negative numbers and zero by returning 0 immediately.”

2. **Initialization**

   > “Then we start `i` at 0. This will be our candidate for the square root.”

3. **Loop condition**

   > “While `i` is not too big, and `i * i` is still less than or equal to `nb`, we keep testing.”

   Highlight: `i <= 46340 && i * i <= nb`

4. **Check for exact square**

   > “If at any point `i * i` is exactly equal to `nb`, we’ve found the integer square root, so we return `i`.”

5. **Increment**

   > “Otherwise, we increment `i` and try again.”

6. **End of loop**

   > “If the loop finishes without finding a match, that means `nb` is not a perfect square, so we return 0.”

---

**Scene 4 – Example Animation**

Pick `nb = 25`.

**Visual:** Show a table that fills step-by-step:

| Step | i | i*i | Match? |
| ---- | - | --- | ------ |
| 1    | 0 | 0   | No     |
| 2    | 1 | 1   | No     |
| 3    | 2 | 4   | No     |
| 4    | 3 | 9   | No     |
| 5    | 4 | 16  | No     |
| 6    | 5 | 25  | ✅ Yes  |

**Voiceover:**

> “For 25, we test 0, 1, 2, 3, 4… and finally 5.
> At `i = 5`, `i * i` equals 25, so we return 5 and stop.”

Then show `ft_sqrt(8)` example where the loop stops because `i*i > nb`.

---

**Scene 5 – Closing**

> “That’s it! We built our own square root function using just integers and a loop.
> No math library, no `sqrt()`, and fully compatible with the 42 subject.”

You can then tease a bonus: “In another video we can optimize this with binary search.”

---

## 4️⃣ Cheat Sheet for Perfect Squares (and How to Generate All Up to 46340²)

### A. Key Facts

* Largest `int` where `i * i` fits in 32-bit signed: **46340**
* `46340 * 46340 = 2147395600`
* Your check `i <= 46340` is exactly for this reason.

---

### B. First Perfect Squares (very useful to know by heart)

| n  | n²  |
| -- | --- |
| 0  | 0   |
| 1  | 1   |
| 2  | 4   |
| 3  | 9   |
| 4  | 16  |
| 5  | 25  |
| 6  | 36  |
| 7  | 49  |
| 8  | 64  |
| 9  | 81  |
| 10 | 100 |

More:

| n  | n²  |
| -- | --- |
| 11 | 121 |
| 12 | 144 |
| 13 | 169 |
| 14 | 196 |
| 15 | 225 |
| 16 | 256 |
| 17 | 289 |
| 18 | 324 |
| 19 | 361 |
| 20 | 400 |

And some “round” ones:

| n    | n²      |
| ---- | ------- |
| 30   | 900     |
| 40   | 1600    |
| 50   | 2500    |
| 100  | 10000   |
| 200  | 40000   |
| 300  | 90000   |
| 1000 | 1000000 |

You don’t need to memorize more for this project; you just need the **mechanism**.

---

### C. Generate ALL squares up to 46340² (helper program)

If you want a full cheat sheet, just let C print it for you:

```c
#include <stdio.h>

int main(void)
{
	int i;

	i = 0;
	while (i <= 46340)
	{
		printf("%d^2 = %d\n", i, i * i);
		i++;
	}
	return (0);
}
```

---

