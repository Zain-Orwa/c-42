# 🔢 Exercise 03: `ft_print_numbers`

### 📁 Directory

`ex03/`

### 📄 File to turn in

`ft_print_numbers.c`

### ⚙️ Allowed functions

`write`

---

## 🧠 Objective

Create a function that prints all digits from `0` to `9` in ascending order on a single line, using only the `write()` system call.

---

## 🔍 What You’re Learning

| Concept              | Description                                            |
| -------------------- | ------------------------------------------------------ |
| ASCII numeric values | Understanding that `'0'` to `'9'` correspond to 48–57  |
| Loops                | Using `while` to iterate through numbers               |
| Type conversion      | Printing integer digits by treating them as characters |
| Function modularity  | Reusing `ft_putchar()` for cleaner structure           |
| Low-level output     | Practicing system-level output control with `write()`  |

---

## 📘 Code Breakdown

```c
#include <unistd.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

void ft_print_numbers(void){
	int num = 48; // ASCII value of '0'

	while (num <= 57){ // ASCII value of '9'
		ft_putchar(num);
		num++;
	}
}

int main(void){
	ft_print_numbers();
	return (0);
}
```

---

## 🧩 Line-by-Line Explanation

| Line                  | Explanation                              |
| --------------------- | ---------------------------------------- |
| `#include <unistd.h>` | Gives access to `write()` system call    |
| `ft_putchar()`        | Prints a single character                |
| `int num = 48;`       | Initializes with ASCII value of `'0'`    |
| `while (num <= 57)`   | Loops until reaching `'9'` (ASCII 57)    |
| `ft_putchar(num);`    | Prints the current number as a character |
| `num++;`              | Moves to the next digit                  |
| `ft_print_numbers();` | Executes the function inside `main()`    |

---

## ❓ Why This Matters

* You learn how to **connect integer logic to ASCII representation**.
* Reinforces **loop logic and modular function usage**.
* Builds the foundation for manipulating **character sets** in C.
* Strengthens your understanding of **low-level character I/O** — a must for future 42 projects.

---

## 💡 ASCII Visualization

| Character | ASCII Value |
| --------- | ----------- |
| `'0'`     | 48          |
| `'1'`     | 49          |
| `'2'`     | 50          |
| `'3'`     | 51          |
| `'4'`     | 52          |
| `'5'`     | 53          |
| `'6'`     | 54          |
| `'7'`     | 55          |
| `'8'`     | 56          |
| `'9'`     | 57          |

So the loop runs through all values from 48 → 57, printing `'0'` → `'9'`.

---

## 💥 Common Mistakes

| Mistake                                   | Why It’s Wrong                                             |
| ----------------------------------------- | ---------------------------------------------------------- |
| Using `int num = 0;`                      | Prints unprintable characters (ASCII control codes)        |
| Using `'9' < num` instead of `num <= '9'` | The loop won’t execute correctly                           |
| Using `printf()`                          | Not allowed — must use `write()` only                      |
| Forgetting `<unistd.h>`                   | Compiler error: `implicit declaration of function ‘write’` |

---

## 🧠 Memory Trick

Think of `'0'` as the **starting ASCII gate (48)**.
Each time you increment `num`, the gate opens to the **next digit’s ASCII value**.

---

## 🧩 Summary

| Concept      | Key Takeaway                    |
| ------------ | ------------------------------- |
| ASCII logic  | `'0'` to `'9'` = 48 → 57        |
| Loop control | `while (num <= 57)`             |
| Modularity   | Reuse `ft_putchar()`            |
| Output       | Prints all digits: `0123456789` |

✅ **End Result:**
The program prints all digits from **0 to 9** continuously on a single line.

---

# 🧩 Peer Evaluation Q&A

### 🧠 **Q1:** What does `ft_print_numbers()` do?

**A:** It prints all digits from `'0'` to `'9'` in ascending order on one line.

---

### 🧠 **Q2:** Why is `num` initialized with 48 instead of 0?

**A:** Because `write()` prints characters based on **ASCII codes**, and `'0'` has an ASCII value of **48**.
If you used `0`, it would print a non-printable control character.

---

### 🧠 **Q3:** Why use `ft_putchar()` instead of `write()` directly?

**A:** For **code reusability** and consistency — `ft_putchar()` abstracts the logic for single-character printing.

---

### 🧠 **Q4:** What happens if you change `num++` to `num--`?

**A:** The loop becomes infinite because `num` starts at 48 and keeps decreasing — it will never reach 57.

---

### 🧠 **Q5:** What are the ASCII values for `'0'` and `'9'`?

**A:** `'0'` → 48, `'9'` → 57.

---

### 🧠 **Q6:** Why can integers be used in `ft_putchar()`?

**A:** Because `write()` treats any integer passed as a **character code**, printing its corresponding ASCII symbol.

---

### 🧠 **Q7:** What happens if we use `num < 57` instead of `<= 57`?

**A:** `'9'` (57) won’t be printed — the loop stops at `'8'`.

---

### 🧠 **Q8:** Why use `(void)` in the function header?

**A:** It indicates that the function takes no parameters — a clean C convention for clarity.

---

### 🧠 **Q9:** What is the output of this program?

**A:**

```
0123456789
```

---

### 🧠 **Q10:** How does `write(1, &c, 1)` actually work?

**A:**

* `1` → stdout (the terminal)
* `&c` → address of the character to print
* `1` → number of bytes to write

---

✅ **Peer Ready:**
Covers ASCII logic, loops, modularity, and system-level printing — exactly what 42 correction expects.
Ready for GitHub upload.

---
