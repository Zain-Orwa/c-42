# 🔡 Exercise 02: `ft_print_reverse_alphabet`

### 📁 Directory

`ex02/`

### 📄 File to turn in

`ft_print_reverse_alphabet.c`

### ⚙️ Allowed functions

`write`

---

## 🧠 Objective

Create a function that displays all lowercase letters of the English alphabet **in reverse order**, starting from `'z'` and ending at `'a'`, on a single line.

---

## 🔍 What You’re Learning

| Concept                  | Description                                    |
| ------------------------ | ---------------------------------------------- |
| Loop control (decrement) | How to count backward using `letter--`         |
| ASCII values             | Understanding that `'z'` > `'a'` (122 → 97)    |
| Function reuse           | Using your `ft_putchar()` function from `ex00` |
| Logical comparison       | Using `>=` to set a descending loop limit      |
| Modularity               | Keeping your printing logic clean and reusable |

---

## 📘 Code Breakdown

```c
#include <unistd.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

void ft_print_reverse_alphabet(void){
	char letter = 'z';

	while (letter >= 'a'){
		ft_putchar(letter);
		letter--;
	}
}

int main(void){
	ft_print_reverse_alphabet();
	return (0);
}
```

---

## 🧩 Line-by-Line Explanation

| Line                           | Explanation                                                |
| ------------------------------ | ---------------------------------------------------------- |
| `#include <unistd.h>`          | Gives access to the `write()` system call                  |
| `ft_putchar()`                 | Prints a single character using file descriptor 1 (stdout) |
| `char letter = 'z';`           | Initialize with the last lowercase letter                  |
| `while (letter >= 'a')`        | Loop continues until the letter is before `'a'`            |
| `ft_putchar(letter);`          | Prints the current letter                                  |
| `letter--;`                    | Decrements the ASCII value → moves one letter back         |
| `ft_print_reverse_alphabet();` | Executes the reverse print sequence in main()              |

---

## ❓ Why This Matters

* Reinforces **loop logic**, but now in reverse.
* Strengthens understanding of **ASCII ordering** and how characters behave as numbers.
* Builds on previous exercises — reusing `ft_putchar()` keeps your code **consistent and modular**.
* Helps train you to **control direction of iteration**, crucial for advanced logic later (arrays, strings, linked lists).

---

## 💡 ASCII Visualization

| Character | ASCII Value |
| --------- | ----------- |
| `'a'`     | 97          |
| `'b'`     | 98          |
| ...       | ...         |
| `'z'`     | 122         |

Loop:
`'z' (122) → 'y' (121) → 'x' (120) → ... → 'a' (97)`

---

## 💥 Common Mistakes

| Mistake                          | Why It’s Wrong                                                |
| -------------------------------- | ------------------------------------------------------------- |
| Forgetting `letter--`            | Infinite loop — `letter` never changes                        |
| Using `'a' <= letter`            | Reversed condition → doesn’t stop properly                    |
| Printing directly with `write()` | Allowed, but breaks modular style (should reuse `ft_putchar`) |
| Starting from `'A'`              | Prints uppercase alphabet instead                             |
| Missing `<unistd.h>`             | Compiler won’t recognize `write()`                            |

---

## 🧠 Memory Trick

Think of the alphabet as a **countdown** from `'z'` to `'a'`.
Each iteration removes one letter from the end, like popping elements from a list in reverse order.

---

## 🧩 Summary

| Concept      | Key Takeaway                                      |
| ------------ | ------------------------------------------------- |
| ASCII logic  | `'z'` > `'a'`, so decrementing works              |
| Loop control | `while (letter >= 'a')`                           |
| Modularity   | Reuses your function from `ex00`                  |
| Output       | One continuous line: `zyxwvutsrqponmlkjihgfedcba` |

✅ **End Result:**
The program prints all lowercase letters from `z` to `a` on a single line.

---

# 🧩 Peer Evaluation Q&A

### 🧠 **Q1:** What does `ft_print_reverse_alphabet()` do?

**A:** It prints all lowercase letters in reverse order — from `'z'` down to `'a'`.

---

### 🧠 **Q2:** Why is the comparison `>= 'a'` instead of `<= 'z'`?

**A:** Because we start from `'z'` and move backward.
We want the loop to stop **after** `'a'` is printed.

---

### 🧠 **Q3:** What does `letter--` mean in this context?

**A:** It decrements the ASCII value of `letter` by one, moving from `'z'` to `'y'`, then `'y'` to `'x'`, and so on.

---

### 🧠 **Q4:** Why use `ft_putchar()` again here?

**A:** To maintain consistency and modularity — 42 projects value reusability.
It also proves you understood your previous function.

---

### 🧠 **Q5:** What is the ASCII difference between `'z'` and `'a'`?

**A:** `'z'` is **122**, `'a'` is **97** — so there are **25 increments** between them.

---

### 🧠 **Q6:** What happens if we replace `letter--` with `letter++`?

**A:** The loop would go infinite because `letter` would move away from `'a'` instead of toward it.

---

### 🧠 **Q7:** Why use `(void)` in the prototype?

**A:** It clearly states that the function doesn’t take any parameters (C convention).

---

### 🧠 **Q8:** Can we start from `'A'` and end at `'Z'` instead?

**A:** Yes, but you’d need to change both your start and end conditions to match uppercase ASCII values (65 → 90).

---

### 🧠 **Q9:** What’s the output of this program?

**A:**

```
zyxwvutsrqponmlkjihgfedcba
```

---

### 🧠 **Q10:** Why can we compare characters with `>=` or `<=`?

**A:** Because characters in C are stored as integers — comparisons work the same way as with numbers.

---

✅ **Peer Ready:**
Clean, modular, and logically correct.
Explains ASCII, loops, and function reuse — perfect for 42 correction and GitHub upload.

---


