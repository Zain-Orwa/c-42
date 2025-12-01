```md
# 🧮 C05 – Exercise 00: `ft_iterative_factorial`  

# 1. 📘 What is a factorial?

A **factorial** is a mathematical operation applied to a positive integer `n`.

It is written as:

```

n!   →   "n factorial"

```

### ✔ Definition
```

n! = n × (n - 1) × (n - 2) × … × 3 × 2 × 1

````

### ✔ Examples
| n | n! | Explanation |
|---|----|-------------|
| 0 | 1 | by definition: 0! = 1 |
| 1 | 1 | 1 = 1 |
| 3 | 6 | 3 × 2 × 1 |
| 4 | 24 | 4 × 3 × 2 × 1 |
| 5 | 120 | 5 × 4 × 3 × 2 × 1 |

``````
### ✔ Special rules in mathematics
- `0! = 1`  
- Factorial is **not defined** for negative numbers  
  → in this exercise: return `0` when input is negative

---

# 2. 🎯 Goal of the exercise

We must write an **iterative** (loop-based) factorial function:

- no recursion  
- no external functions  
- handle:
  - negative → return `0`
  - zero → return `1`
  - positive → calculate factorial by multiplying numbers one by one

  ``````

Prototype:

```c
int ft_iterative_factorial(int nb);
````

---

# 3. ✔ Your main version (using i++)

Here is your code:

```c
int ft_iterative_factorial(int nb){
	int i;
	int fact;

	if (nb < 0)
		return (0);

	if (nb == 0)
		return (1);

	i = 1;
	fact = 1;

	while (i <= nb){
		fact *= i;
		i++;
	}
	return (fact);
}
```

---

# 4. 🧠 Explanation step-by-step (i++ version)

### 4.1 Input check

```c
if (nb < 0)
	return (0);
```

* factorial of a negative number doesn’t exist
* required by subject → return `0`

---

### 4.2 Handle `0!`

```c
if (nb == 0)
	return (1);
```

* defined by math
* if nb = 0 → factorial is 1

---

### 4.3 Initialize variables

```c
i = 1;
fact = 1;
```

* `fact` holds the final result
* `i` is our counter, starting at **1** (smallest number in the product)

---

### 4.4 Loop (i++ version)

```c
while (i <= nb){
	fact *= i;
	i++;
}
```

This calculates:

```
fact = 1 × 1 × 2 × 3 × … × nb
```

For `nb = 4`:

```
i = 1 → fact = 1
i = 2 → fact = 1 × 2 = 2
i = 3 → fact = 2 × 3 = 6
i = 4 → fact = 6 × 4 = 24
```

---

### 4.5 Return

```c
return (fact);
```

Done. 🎉

---

# 5. ✔ Your second version (using i--)

(This is also completely valid)

```c
int ft_iterative_factorial(int nb){
	int i;
	int fact;

	if (nb < 0)
		return (0);

	if (nb == 0)
		return (1);

	i = nb;
	fact = 1;

	while (i >= 1){
		fact *= i;
		i--;
	}
	return (fact);
}
```

---

# 6. 🔍 Comparing the two versions (i++ vs i--)

| Aspect            | i++ version                | i-- version                           |
| ----------------- | -------------------------- | ------------------------------------- |
| Starting point    | `i = 1`                    | `i = nb`                              |
| Loop direction    | ascending                  | descending                            |
| Mathematical view | builds result bottom → top | builds result top → bottom            |
| Logic complexity  | beginner friendly          | also correct, slightly different flow |
| Final result      | same for all nb ≥ 0        | same                                  |

### Example for nb = 4

**i++ version:**

```
1 × 2 × 3 × 4 = 24
```

**i-- version:**

```
4 × 3 × 2 × 1 = 24
```

Both are mathematically identical because multiplication is **commutative**.

---

# 7. ❓ Q&A (for peer evaluation)

### ✔ Q1: Why return 0 for negative numbers?

Because factorial is undefined for negatives and the subject requires returning `0`.

---

### ✔ Q2: Why return 1 for `nb == 0`?

Because `0! = 1` is defined in mathematics and needed in combinatorics.

---

### ✔ Q3: Why do we initialize `fact = 1`?

Multiplication identity rule:

```
1 × x = x
```

So starting from 1 builds the correct result.

---

### ✔ Q4: Which version is better — i++ or i--?

Both are correct.
**i++** is slightly easier to understand for beginners,
but **i--** is equally valid and sometimes used when thinking “start from nb and go down”.

Performance is identical.

---

# 8. 🧨 Final note

For the Piscine peer-eval:

* Explain the two loops (i++ and i--)
* Know the special cases (`nb < 0` and `0!`)

```

