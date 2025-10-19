# ➕➖ Exercise 04: `ft_is_negative`

### 📁 Directory

`ex04/`

### 📄 File to turn in

`ft_is_negative.c`

### ⚙️ Allowed functions

`write`

---

## 🧠 Objective

Write a function that displays **‘N’** if the integer passed as a parameter is negative, or **‘P’** if it’s positive or zero.

---

## 🔍 What You’re Learning

| Concept             | Description                                           |
| ------------------- | ----------------------------------------------------- |
| Conditional logic   | Using `if` and `else` to make decisions in code       |
| Integer comparison  | Understanding how integers are evaluated in C         |
| Function parameters | Passing values into functions and checking them       |
| Function modularity | Reusing `ft_putchar()` for clean, consistent code     |
| Low-level output    | Using the `write()` system call instead of `printf()` |

---

## 📘 Code Breakdown

```c
#include <unistd.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

void ft_is_negative(int n){
	if (n < 0)
		ft_putchar('N');
	else
		ft_putchar('P');
}

int main(void){
	ft_is_negative(-222);
	ft_putchar('\n');
	ft_is_negative(222);
	ft_putchar('\n');
	return (0);
}
```

---

## 🧩 Line-by-Line Explanation

| Line                    | Explanation                               |
| ----------------------- | ----------------------------------------- |
| `#include <unistd.h>`   | Gives access to the `write()` system call |
| `ft_putchar()`          | Prints a single character using `write()` |
| `ft_is_negative(int n)` | Function that checks if `n` is negative   |
| `if (n < 0)`            | Condition is true for negative numbers    |
| `ft_putchar('N');`      | Prints **N** (Negative)                   |
| `else ft_putchar('P');` | Prints **P** (Positive or zero)           |
| `ft_is_negative(-222);` | Example call with negative number         |
| `ft_is_negative(222);`  | Example call with positive number         |

---

## ❓ Why This Matters

* Teaches **decision making** in code.
* Builds the base for later logic exercises where branching is needed.
* Reinforces **clean, modular design** using helper functions.
* Strengthens understanding of **integer evaluation** (negative, zero, positive).

---

## 💡 Output Example

```bash
N
P
```

If you pass `-222`, output is `N`.
If you pass `222`, output is `P`.

---

## 💥 Common Mistakes

| Mistake                 | Why It’s Wrong                                    |
| ----------------------- | ------------------------------------------------- |
| Forgetting the `else`   | Would print both `N` and `P` for negative numbers |
| Using `printf()`        | Not allowed — only `write()` can be used          |
| Writing `'n'` and `'p'` | Must be uppercase letters as per subject          |
| Not handling zero       | Zero should print **P** (not negative)            |

---

## 🧠 Memory Trick

Think like a gatekeeper:

* If the number is **less than zero**, say “No → N”.
* If it’s **zero or more**, say “Positive → P”.

Simple, binary decision — **negative or not**.

---

## 🧩 Summary

| Concept           | Key Idea                            |
| ----------------- | ----------------------------------- |
| Conditional logic | `if (n < 0)` then `'N'`, else `'P'` |
| Zero handling     | Zero counts as positive             |
| Modularity        | Uses `ft_putchar()` for output      |
| Output            | Prints only one character each time |

✅ **End Result:**
The program prints either `N` or `P` based on the sign of the integer.

---

# 🧩 Peer Evaluation Q&A

### 🧠 **Q1:** What does `ft_is_negative()` do?

**A:** It prints `'N'` if the integer `n` is negative, otherwise it prints `'P'`.

---

### 🧠 **Q2:** Why is zero considered positive here?

**A:** The subject says *“If n is positive or null, display 'P'”* — so 0 is treated as non-negative.

---

### 🧠 **Q3:** Why use `if (n < 0)` instead of `if (n <= 0)`?

**A:** Because zero should **not** be treated as negative — only numbers strictly less than zero should print `'N'`.

---

### 🧠 **Q4:** Why is `ft_putchar()` used instead of `write()`?

**A:** For modularity — reusing your `ft_putchar()` function from `ex00` keeps the code organized and consistent.

---

### 🧠 **Q5:** What happens if you pass `0` to the function?

**A:** It prints `'P'`, because zero is not negative.

---

### 🧠 **Q6:** How does `write(1, &c, 1)` behave here?

**A:**

* `1` → standard output (terminal)
* `&c` → address of the character to print
* `1` → number of bytes to write

---

### 🧠 **Q7:** Could we simplify it using the ternary operator?

**A:** Yes, for example:

```c
write(1, (n < 0) ? "N" : "P", 1);
```

But 42’s style prefers simple `if/else` for clarity.

---

### 🧠 **Q8:** What are the expected outputs for these examples?

| Input | Output |
| ----- | ------ |
| `-5`  | N      |
| `0`   | P      |
| `123` | P      |

---
