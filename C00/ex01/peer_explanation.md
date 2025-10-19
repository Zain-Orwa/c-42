# 🔠 Exercise 01: `ft_print_alphabet`

### 📁 Directory

`ex01/`

### 📄 File to turn in

`ft_print_alphabet.c`

### ⚙️ Allowed functions

`write`

---

## 🧠 Objective

Create a function that prints the lowercase alphabet (`a` → `z`) in ascending order on a single line, using only the `write()` system call.

---

## 🔍 What You’re Learning

| Concept                     | Description                                                       |
| --------------------------- | ----------------------------------------------------------------- |
| Loop control                | How to iterate through characters in order                        |
| ASCII sequence              | Each letter is represented by a numeric code in ASCII             |
| Function composition        | How to call one custom function (`ft_putchar`) from another       |
| `char` arithmetic           | Characters can be incremented like integers (`letter++`)          |
| Function with no parameters | Using `(void)` means no arguments are taken                       |
| Low-level output            | Using `write()` instead of higher-level functions like `printf()` |

---

## 📘 Code Breakdown

```c
#include <unistd.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

void ft_print_alphabet(void){
	char letter;

	letter = 'a';
	while (letter <= 'z'){
		ft_putchar(letter);
		letter++;
	}
}

int main(void){
	ft_print_alphabet();
	return (0);
}
```

---

## 🧩 Line-by-Line Explanation

| Line                    | Explanation                                               |
| ----------------------- | --------------------------------------------------------- |
| `#include <unistd.h>`   | Includes access to the `write()` system call              |
| `ft_putchar()`          | Helper function to print one character                    |
| `ft_print_alphabet()`   | Function that prints all letters from `a` to `z`          |
| `char letter;`          | Declares a character variable to store the current letter |
| `letter = 'a';`         | Initializes with the first lowercase letter               |
| `while (letter <= 'z')` | Loops until `letter` passes `'z'`                         |
| `ft_putchar(letter);`   | Prints the current letter                                 |
| `letter++;`             | Moves to the next character in the ASCII table            |
| `ft_print_alphabet();`  | Executes the alphabet printing in main()                  |

---

## ❓ Why This Matters

* Strengthens understanding of **loops**, **ASCII**, and **custom function calls**.
* Shows how **characters are just small integers** that can be incremented.
* Reinforces writing **clean, modular code** (splitting functionality into smaller functions).
* Builds your base for later exercises (`ft_print_reverse_alphabet`, `ft_print_numbers`, etc.).

---

## 💡 ASCII Reminder

| Character | ASCII Value |
| --------- | ----------- |
| `'a'`     | 97          |
| `'b'`     | 98          |
| `'c'`     | 99          |
| ...       | ...         |
| `'z'`     | 122         |

Characters are stored as numbers — `'a' + 1` equals `'b'`.

---

## 💥 Common Mistakes

| Mistake                           | Why It’s Wrong                                          |
| --------------------------------- | ------------------------------------------------------- |
| Forgetting to initialize `letter` | Loop starts with garbage value                          |
| Using `<=` incorrectly            | Must stop *after* `'z'`, not before                     |
| Missing helper function prototype | `ft_putchar()` must be defined before use (or declared) |
| Using `printf()` or `putchar()`   | Not allowed — must use `write()`                        |
| Forgetting `<unistd.h>`           | Compiler won’t recognize `write()`                      |

---

## 🧠 Memory Trick

Visualize the alphabet as **a line of boxes** labeled `'a'` → `'z'`.
Each loop iteration moves one step to the right, printing each box’s content.

---

## 🧩 Concept Summary

| Concept       | Key Idea                                |
| ------------- | --------------------------------------- |
| ASCII         | Characters are numeric                  |
| Loop          | Move through characters with `letter++` |
| Modularity    | Reuse your `ft_putchar()` from ex00     |
| Low-level I/O | Print directly with `write()`           |

✅ **End Result:** Prints `abcdefghijklmnopqrstuvwxyz` on a single line.

---

# 🧩 Peer Evaluation Q&A

### 🧠 **Q1:** What does `ft_print_alphabet()` do?

**A:** It prints all lowercase letters from `'a'` to `'z'` in order using a `while` loop and `ft_putchar()`.

---

### 🧠 **Q2:** Why do we use `ft_putchar()` here?

**A:** It follows 42’s modular principle — reusing existing code (from ex00) to keep logic clean and consistent.

---

### 🧠 **Q3:** Why does the loop condition use `letter <= 'z'`?

**A:** Because `'z'` is the final lowercase letter in ASCII; the loop continues until we reach and print it.

---

### 🧠 **Q4:** What does `letter++` actually do?

**A:** It increases the ASCII value of `letter` by 1 — moving from `'a'` to `'b'`, `'b'` to `'c'`, and so on.

---

### 🧠 **Q5:** What is the purpose of `(void)` in the function header?

**A:** It indicates the function takes no parameters (a C convention for clarity).

---

### 🧠 **Q6:** Why can we compare characters using `<=` and `>=`?

**A:** Because characters are stored as numbers (ASCII codes), so numeric comparison works normally.

---

### 🧠 **Q7:** How does `write(1, &c, 1)` work again?

**A:**

* `1` → file descriptor (stdout)
* `&c` → address of the character
* `1` → number of bytes to print

---

### 🧠 **Q8:** What happens if we start with `'A'` instead of `'a'`?

**A:** The function would print uppercase letters from `A` to `Z` (ASCII 65–90).

---

### 🧠 **Q9:** Why not print directly inside the loop with `write()`?

**A:** You could, but using `ft_putchar()` makes the code **more readable and reusable**.

---

### 🧠 **Q10:** What is the output of this program?

**A:**

```
abcdefghijklmnopqrstuvwxyz
```
