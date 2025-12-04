# 🧮Exercise 02 : ft_iterative_power

---

## 📌 Exercise Goal

Implement an **iterative** function that computes `nb` raised to the power `power`, following the Piscine rules:

* Any **negative power returns 0**
* **0 power 0 returns 1**
* No recursion
* No overflow handling
* Only loops and basic arithmetic

---

## 🧠 Concept Overview

Power means multiplying a number by itself a certain number of times:

```
nb^power = nb × nb × nb × ... (power times)
```

Examples:

| nb | power | result | reason                    |
| -- | ----- | ------ | ------------------------- |
| 2  | 4     | 16     | 2×2×2×2                   |
| 5  | 0     | 1      | any number^0 = 1          |
| 0  | 0     | 1      | subject decision          |
| 3  | -2    | 0      | negative power → return 0 |

The problem is solved **iteratively**, not recursively.
We start with `result = 1` and multiply until `power` reaches zero.

---

## 🧱 Code (your final version)

```c
#include <stdio.h>
#include <unistd.h>

int ft_iterative_power(int nb, int power){
	int result;

	if (power < 0) return (0);
	if (power == 0)	return (1);

	result = 1;
	while (power > 0)
	{
		result *= nb;
		power--;
	}

	return (result);
}

int main(void){
    printf("2^4  = %d\n", ft_iterative_power(2, 4));   // 16
    printf("5^0  = %d\n", ft_iterative_power(5, 0));   // 1
    printf("0^0  = %d\n", ft_iterative_power(0, 0));   // 1 (by subject)
    printf("3^-2 = %d\n", ft_iterative_power(3, -2));  // 0 (by subject)
    return 0;
}
```

---

## 🔍 Line-by-Line Explanation

### 1. Handle invalid power

```c
if (power < 0) return (0);
```

* Subject rule: **any power lower than 0 → return 0**
* Negative powers would normally mean fractions (like 2^-1 = 1/2), but we don’t handle that in this exercise.

---

### 2. Handle power = 0

```c
if (power == 0) return (1);
```

* Math rule: any number^0 = 1
* Subject also says **0^0 returns 1**
* So this covers both cases cleanly.

---

### 3. Initialize result

```c
result = 1;
```

Why 1?
Because in multiplication, **1 is the neutral element**.
Starting at 1 allows multiplying safely:

* For `power = 4`:
  1 → 2 → 4 → 8 → 16
* For `power = 1`:
  1 → 2
* For `power = 0`:
  We already returned 1 before the loop.

---

### 4. Iterative multiplication

```c
while (power > 0)
{
    result *= nb;
    power--;
}
```

This loop runs exactly **power** times.

Every iteration multiplies `result` by `nb`, reducing `power` until it reaches 0.

Example for `nb = 2`, `power = 4`:

| iteration | result | power |
| --------- | ------ | ----- |
| start     | 1      | 4     |
| i1        | 2      | 3     |
| i2        | 4      | 2     |
| i3        | 8      | 1     |
| i4        | 16     | 0     |

When `power` hits 0 → the loop stops.

---

### 5. Return the final result

```c
return (result);
```

Whatever the multiplication produced is the final answer.

---

## 🧪 Output of the Test Main

```
2^4  = 16
5^0  = 1
0^0  = 1
3^-2 = 0
```

Everything matches the subject expectations.

---

## ❓ Peer Evaluation Q&A

**Q: Why do we check negative power first?**
A: Because the subject explicitly says negative powers return 0. This condition takes priority.

---

**Q: Why start `result = 1` instead of 0?**
A: Multiplying by 0 would always produce 0. Multiplication identity must be 1.

---

**Q: Why does 0^0 return 1 here?**
A: Because the subject requires it, and it is covered automatically by `power == 0`.

---

**Q: Why use a loop instead of recursion?**
A: The exercise name says *iterative*, and recursion is forbidden.

---

**Q: What happens with overflow (e.g., 50^10)?**
A: The subject says **do not handle overflow**, so the integer wraps normally.

---


