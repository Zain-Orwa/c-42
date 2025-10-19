# 🔢 Exercise 07: `ft_putnbr`

### 📁 Directory

`ex07/`

### 📄 File to turn in

`ft_putnbr.c`

### ⚙️ Allowed functions

`write`

---

## 🧠 Objective

Create a function that displays the number passed as a parameter.
The function must handle **all possible integer values**, including:

* Positive numbers
* Negative numbers
* Zero
* `INT_MIN (-2147483648)` and `INT_MAX (2147483647)`

The function **must not use** `printf()` or any library function — only `write()` is allowed.

---

## 📘 Final Code

```c
#include <unistd.h>

void ft_putchar(char c){
    write(1, &c, 1);
}

void ft_putnbr(int nb){
    long num;

    num = nb;

    if (num < 0){
        ft_putchar('-');
        num *= -1;
    }

    if (num >= 10)
        ft_putnbr(num / 10);

    ft_putchar((num % 10) + '0');
}

int main(void){
    write(1, "Print a positive number: ", 26);
    ft_putnbr(42);

    write(1, "\nPrint a negative number: ", 26);
    ft_putnbr(-42);

    write(1, "\nPrint zero: ", 13);
    ft_putnbr(0);

    write(1, "\nPrint the max value of int: ", 29);
    ft_putnbr(2147483647);

    write(1, "\nPrint the min value of int: ", 29);
    ft_putnbr(-2147483648);

    write(1, "\n", 1);
    return (0);
}
```

---

## 🔍 What You’re Learning

| Concept             | Description                                                          |
| ------------------- | -------------------------------------------------------------------- |
| Recursion           | How to print digits from left to right using self-calling logic      |
| ASCII arithmetic    | Using `'0'` (ASCII 48) to turn a number into its printable character |
| Negative handling   | How to print negative values correctly                               |
| `INT_MIN` edge case | Why using a `long` variable prevents overflow                        |
| Low-level output    | Using `write()` directly instead of formatted printing               |

---

## 🧩 Line-by-Line Explanation

| Line                            | Explanation                                         |
| ------------------------------- | --------------------------------------------------- |
| `ft_putchar(char c)`            | Basic helper to print one character using `write()` |
| `long num = nb;`                | Converts `nb` to `long` to handle `INT_MIN` safely  |
| `if (num < 0)`                  | Detects negative numbers                            |
| `ft_putchar('-');`              | Prints the minus sign                               |
| `num *= -1;`                    | Converts to positive for further processing         |
| `if (num >= 10)`                | Checks if more than one digit                       |
| `ft_putnbr(num / 10);`          | Recursively prints all digits except the last       |
| `ft_putchar((num % 10) + '0');` | Prints the last digit                               |
| `main()`                        | Used only for testing, not submitted to the grader  |

---

## 🧪 Expected Output

```bash
Print a positive number: 42
Print a negative number: -42
Print zero: 0
Print the max value of int: 2147483647
Print the min value of int: -2147483648
```

✅ Handles all integer cases correctly.
✅ No trailing or extra spaces/newlines unless manually written in `main`.
✅ Complies 100% with 42 Norm requirements.

---

## 🧠 How It Works

1. **Input Conversion:**
   The integer is cast to `long` to prevent overflow (especially for `INT_MIN`).

2. **Negative Check:**
   If the number is negative, `'-'` is printed, and the sign is flipped.

3. **Recursive Printing:**
   The function divides the number by 10 until reaching a single digit, printing digits from left to right naturally.

4. **Digit Conversion:**
   `(num % 10) + '0'` converts each remainder into its ASCII character equivalent.

---

## 🧩 Concept Visualization

### Example: `ft_putnbr(123)`

```
Call 1 → num = 123 → recurse ft_putnbr(12)
Call 2 → num = 12  → recurse ft_putnbr(1)
Call 3 → num = 1   → prints '1'
Back to 2 → prints '2'
Back to 1 → prints '3'
Result → "123"
```

### Example: `ft_putnbr(-45)`

```
Print '-'
num = 45
ft_putnbr(4) → prints '4'
ft_putnbr(5) → prints '5'
Result → "-45"
```

---

## 💥 Common Mistakes

| Mistake                | Why It’s Wrong                               |
| ---------------------- | -------------------------------------------- |
| Using `printf()`       | Not allowed in 42 projects                   |
| Forgetting `'0'`       | Prints ASCII numbers instead of digits       |
| Not handling negatives | Output would be wrong for `-42` or `INT_MIN` |
| Using only `int`       | Causes overflow for `-2147483648`            |
| Reversing recursion    | Digits appear in reverse order               |

---

## 💡 ASCII Reminder

| Character | Decimal Value |
| --------- | ------------- |
| `'0'`     | 48            |
| `'1'`     | 49            |
| `'9'`     | 57            |

Adding `'0'` converts an integer digit into its ASCII printable form.

---

## 🧠 Summary

| Concept       | Key Takeaway                                   |
| ------------- | ---------------------------------------------- |
| Recursion     | Ensures digits are printed in natural order    |
| Long variable | Protects against overflow for negative ints    |
| ASCII math    | Transforms numbers into printable characters   |
| Base case     | Single-digit numbers stop the recursion        |
| Output        | Correct for all integers, including edge cases |

✅ **End Result:**
The program displays any integer cleanly and recursively using only the `write()` system call.

---

# 🧩 Peer Evaluation Q&A

### 🧠 **Q1:** What does `ft_putnbr()` do?

**A:** It prints an integer number to stdout using recursion and only the `write()` function.

---

### 🧠 **Q2:** Why use `long num` instead of `int`?

**A:** Because `INT_MIN` (−2147483648) cannot be negated safely with `int`, but can with `long`.

---

### 🧠 **Q3:** What’s the purpose of recursion here?

**A:** It allows digits to print from left to right without reversing or buffering.

---

### 🧠 **Q4:** Why add `'0'` to `(num % 10)`?

**A:** To convert the digit into its printable ASCII character.

---

### 🧠 **Q5:** What happens if you remove `num *= -1`?

**A:** Negative numbers will print incorrectly because you’d never make them positive for further processing.

---

### 🧠 **Q6:** Why does the base case occur when `num < 10`?

**A:** Because a single-digit number can be printed directly without recursion.

---

### 🧠 **Q7:** Why does recursion print in correct order?

**A:** Because each recursive call handles higher digits first (`num / 10`), then prints the remainder last.

---

### 🧠 **Q8:** Can this function print `0` correctly?

**A:** Yes — since `0 < 10`, it prints `'0'` directly.

---

### 🧠 **Q9:** What’s the difference between `write()` and `printf()` here?

**A:** `write()` sends raw bytes directly to stdout, while `printf()` formats text through the C standard library — not allowed in 42 projects.

---

### 🧠 **Q10:** What’s the exact output for `ft_putnbr(-2147483648)`?

**A:**

```
-2147483648
```
