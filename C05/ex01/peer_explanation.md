```md
# 🧮 C05 – Exercise 01: `ft_recursive_factorial`  
### Peer Explanation – Clear, structured, Piscine-ready  

---

# 1. 📘 What is a factorial? (Mathematical intuition)

The **factorial** of a number `n` (written `n!`) is defined as:

```
n! = n × (n - 1) × (n - 2) × … × 3 × 2 × 1

```
### Examples  
| n | n! | Explanation |
|---|----|-------------|
| 0 | 1 | Defined by math: 0! = 1 |
| 1 | 1 | 1 × 1 |
| 3 | 6 | 3 × 2 × 1 |
| 5 | 120 | 5 × 4 × 3 × 2 × 1 |

Factorial is **undefined for negative inputs** → in this exercise: return `0`.

```

---

# 2. 🌀 What is recursion?

A recursive function is a function that **calls itself**.

It works by dividing a big problem into smaller versions of the same problem.

For factorial:

```

n! = n × (n - 1)!

```

So factorial naturally fits recursion because:

- each step reduces the problem (`nb - 1`)
- the function keeps calling itself until it reaches the **base case**

---

# 3. 🧱 Base cases in recursion

A recursive function *must* have a condition that stops recursion.

In factorial, we use two base cases:

1. **Negative input → invalid → return 0**
```

if (nb < 0) return (0);

```

2. **Zero → return 1**
```

if (nb == 0) return (1);

````

Without these, recursion would continue forever → **infinite recursion** → crash.

---

# 4. ✔ Your function

```c
int ft_recursive_factorial(int nb){
 if (nb < 0) return (0);
 if (nb == 0) return (1);

 return (nb * ft_recursive_factorial(nb - 1));
}
````

---

# 5. 🧠 Step-by-step explanation

### 🔹 Step 1 — Handle invalid input

```c
if (nb < 0) return (0);
```

No factorial for negative numbers → subject requires returning 0.

---

### 🔹 Step 2 — Base case: stop recursion at 0

```c
if (nb == 0) return (1);
```

Mathematically:

```
0! = 1
```

This also prevents infinite recursion.

---

### 🔹 Step 3 — Recursive step

```c
return (nb * ft_recursive_factorial(nb - 1));
```

Meaning:

```
nb! = nb × (nb - 1)!
```

The function keeps calling itself with smaller values until it hits 0.

---

# 6. 🔍 Example: nb = 5 (step-by-step recursion trace)

```
ft_recursive_factorial(5)
= 5 × ft_recursive_factorial(4)
= 5 × (4 × ft_recursive_factorial(3))
= 5 × (4 × (3 × ft_recursive_factorial(2)))
= 5 × 4 × 3 × ft_recursive_factorial(1)
= 5 × 4 × 3 × (1 × ft_recursive_factorial(0))
= 5 × 4 × 3 × 1 × 1
= 120
```

The recursion ends when we hit:

```
ft_recursive_factorial(0) → return 1
```

After that, the call stack starts unwinding and multiplying backwards.

---

# 7. 🧪 The main program (for testing)

```c
int main(){
	int nb = 5;
	
	printf("%d\n", ft_recursive_factorial(nb));

	return (0);
}
```

Output:

```
120
```

---

# 8. ❓ Peer Evaluation Q&A

### ✔ Q1: Why do we return 0 for negative numbers?

Because factorial is not defined for negatives; subject requires returning `0`.

---

### ✔ Q2: Why is `0!` equal to 1?

Mathematical rule.
Also essential to create the **base case** for recursion.

---

### ✔ Q3: What is the recursive step doing?

It expresses factorial as:

```
n! = n × (n - 1)!
```

and calls the function again with `nb - 1`.

---

### ✔ Q4: What happens if you remove the base case?

The function calls itself forever → stack overflow (infinite recursion).

---

### ✔ Q5: Is recursion better than iteration?

Not always:

* recursion is more elegant for factorial
* but iteration is faster and safer (no stack overflow)
* both versions produce the same result

Piscine wants you to understand **both**.

---

# 9. 📝 Summary

| Concept        | Explanation                                  |
| -------------- | -------------------------------------------- |
| Factorial      | Multiply all integers from n down to 1       |
| Recursion      | Function calling itself with a smaller value |
| Base cases     | Stop conditions: `nb < 0` and `nb == 0`      |
| Recursive step | `nb * ft_recursive_factorial(nb - 1)`        |
| Output         | Correct factorial for all nb ≥ 0             |

---

```
Below are **both items you requested**, written cleanly and in a peer-evaluation-friendly style.

---

# ✅ 1. Recursion Call-Stack Diagram (for `ft_recursive_factorial(5)`)

This diagram shows exactly **what happens in memory** during recursive calls.

Each time the function calls itself, a new “frame” is placed on the **call stack**.

---

## 📥 **Call stack during the descent (recursive calls going DOWN)**

```
ft_recursive_factorial(5)
    -> waiting for ft_recursive_factorial(4)

        ft_recursive_factorial(4)
            -> waiting for ft_recursive_factorial(3)

            ft_recursive_factorial(3)
                -> waiting for ft_recursive_factorial(2)

                ft_recursive_factorial(2)
                    -> waiting for ft_recursive_factorial(1)

                    ft_recursive_factorial(1)
                        -> waiting for ft_recursive_factorial(0)

                        ft_recursive_factorial(0)
                            return 1   <-- BASE CASE HIT
```

At this moment, recursion **stops going down**.
Now we go back up the stack.

---

## 📤 **Call stack during the ascent (solving and returning UP)**

```
ft_recursive_factorial(0) returns 1

ft_recursive_factorial(1)
    return 1 * 1 = 1

ft_recursive_factorial(2)
    return 2 * 1 = 2

ft_recursive_factorial(3)
    return 3 * 2 = 6

ft_recursive_factorial(4)
    return 4 * 6 = 24

ft_recursive_factorial(5)
    return 5 * 24 = 120
```

### 📌 Final Result:

```
5! = 120
```

This diagram shows clearly:

* The recursion **goes down** until the base case (`nb == 0`)
* Then it **unwinds back up**, multiplying the results step by step

This is one of the best explanations to give during the peer-eval.

---

# ✅ 2. Comparison Table: Iterative vs Recursive Factorial

A clean, professional table (42-style, rectangular formatting):

```
+---------------------------+-------------------------------+--------------------------------+
| Aspect                    | Iterative Version             | Recursive Version              |
+---------------------------+-------------------------------+--------------------------------+
| Method                    | Uses a loop (while/for)       | Function calls itself          |
| Start point               | Starts at 1 or nb             | Starts at nb and goes downward |
| How it builds result      | Repeated multiplication       | Multiplies as stack unwinds    |
| Base case                 | Not required (loop ends)      | Must have nb == 0              |
| Handling negative numbers | Return 0                      | Return 0                       |
| Speed                     | Faster (no call overhead)     | Slightly slower (stack usage)  |
| Memory usage              | Constant (O(1))               | Grows with input (O(n))        |
| Risk                      | None                          | Stack overflow if nb is large  |
| Code readability          | Very clear and simple         | More elegant mathematically    |
| 42 usage                  | Used in ex00                  | Used in ex01                   |
+---------------------------+-------------------------------+--------------------------------+
```

---

# 🎯 Final Summary for Evaluation

If the evaluator asks “What is the difference between iterative and recursive factorial?” you can answer:

**Iterative**

* Uses a loop
* Works bottom-up
* No stack growth
* More efficient

**Recursive**

* Uses self-calling
* Works top-down then unwinds
* Very clean mathematically
* Requires a base case
* Uses more memory

Both produce the **same result**, but recursion reflects the **true mathematical definition**.

---
