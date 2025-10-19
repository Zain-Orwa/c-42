# 🔢 Exercise 06: `ft_print_comb2`

### 📁 Directory

`ex06/`

### 📄 File to turn in

`ft_print_comb2.c`

### ⚙️ Allowed functions

`write`

---

## 🧠 Objective

Write a function that displays **all different combinations of two two-digit numbers**, ranging from `00 01` to `98 99`.

* Each pair must be separated by a comma and a space.
* The pairs must appear in **ascending order**.
* There must be **no trailing comma or space** after the last pair.

---

## 📘 Final Code

```c
#include <unistd.h>

void ft_putchar(char c){
    write(1, &c, 1);
}

void print_combination(short a, short b){
    ft_putchar(a / 10 + '0');
    ft_putchar(a % 10 + '0');
    ft_putchar(' ');
    ft_putchar(b / 10 + '0');
    ft_putchar(b % 10 + '0');  
    
    if (!(a == 98 && b == 99)){
        ft_putchar(',');
        ft_putchar(' ');
    }
}

void ft_print_comb2(void){
    short a;
    short b;
    
    a = 0;
    while (a <= 99){
        b = a + 1;
        while (b <= 99){
            print_combination(a, b);    
            b++;        
        }
        a++;
    }
}

int main(){
    ft_print_comb2();
    return (0);
}
```

---

## 🔍 What You’re Learning

| Concept                      | Description                                                    |
| ---------------------------- | -------------------------------------------------------------- |
| Nested loops                 | How to generate combinations efficiently                       |
| Integer division and modulus | Splitting a two-digit number into tens and ones                |
| ASCII arithmetic             | Converting numeric digits into printable characters            |
| Conditional formatting       | Avoiding a trailing comma and space after the last combination |
| Function modularity          | Organizing printing logic into a helper function               |

---

## 🧩 Line-by-Line Breakdown

| Line                         | Explanation                                          |
| ---------------------------- | ---------------------------------------------------- |
| `ft_putchar()`               | Prints one character using the `write()` system call |
| `print_combination(a, b)`    | Handles printing both numbers and their separator    |
| `ft_putchar(a / 10 + '0')`   | Prints the tens digit of `a`                         |
| `ft_putchar(a % 10 + '0')`   | Prints the ones digit of `a`                         |
| `ft_putchar(' ')`            | Prints a space between the two numbers               |
| `if (!(a == 98 && b == 99))` | Prevents printing a separator after the final combo  |
| `a = 0; while (a <= 99)`     | Loops through all numbers from 00 to 99              |
| `b = a + 1; while (b <= 99)` | Ensures `b` is always greater than `a`               |
| `print_combination(a, b)`    | Prints each valid pair                               |
| `b++`, `a++`                 | Moves to the next combination                        |

---

## 🧪 Expected Output

```bash
00 01, 00 02, 00 03, ..., 98 99
```

✅ Starts with `00 01`
✅ Ends with `98 99`
✅ No comma or space after the last pair

---

## 💡 How It Works

1. Two numbers (`a` and `b`) are generated, both ranging from `00` to `99`.
2. The inner loop ensures `b` is always **greater** than `a` — avoiding duplicates and reversed pairs.
3. Each pair is printed as two digits (using division and modulus).
4. After each combination, `, ` is printed — **except** after the final pair `98 99`.

---

## 💥 Common Mistakes

| Mistake                          | Why It’s Wrong                                           |
| -------------------------------- | -------------------------------------------------------- |
| Forgetting `+ '0'`               | Causes ASCII codes instead of characters to print        |
| Letting `b` start from 0         | Produces duplicates (`00 00`, `01 00`, etc.)             |
| Using `printf()`                 | Forbidden in 42 — only `write()` is allowed              |
| Printing separator after `98 99` | Fails output format tests                                |
| Forgetting to handle two digits  | Single-digit numbers must be printed as `00`, `01`, etc. |

---

## 💡 ASCII Reminder

| Character | Decimal Value |
| --------- | ------------- |
| `'0'`     | 48            |
| `'1'`     | 49            |
| ...       | ...           |
| `'9'`     | 57            |

Adding `'0'` to an integer digit converts it into its printable ASCII form.

---

## 🧠 Mini-Logic Recap

| Step | What Happens                                        |
| ---- | --------------------------------------------------- |
| 1    | Start `a` at `0`                                    |
| 2    | Set `b = a + 1`                                     |
| 3    | Print both `a` and `b` as two digits                |
| 4    | Add `, ` unless at the end (`98 99`)                |
| 5    | Increment `b`, then `a` until all pairs are printed |

Total valid pairs printed: **4950 combinations**
(`C(100, 2)` = 100 choose 2)

---

## 🧩 Summary

| Concept          | Key Takeaway                       |
| ---------------- | ---------------------------------- |
| Range logic      | Loops from 0 → 99                  |
| Combination rule | `a < b`                            |
| Output format    | `00 01, 00 02, ..., 98 99`         |
| Helper function  | Simplifies printing logic          |
| Modularity       | Improves readability and structure |

✅ **End Result:**
Your program correctly prints every ascending pair of two-digit numbers, formatted perfectly.

---

# 🧩 Peer Evaluation Q&A

### 🧠 **Q1:** What does `ft_print_comb2()` do?

**A:** It prints all pairs of two-digit numbers from `00 01` to `98 99` in ascending order.

---

### 🧠 **Q2:** Why use `b = a + 1`?

**A:** To ensure `b` is always greater than `a`, preventing duplicates or reversed pairs.

---

### 🧠 **Q3:** Why add `'0'` after dividing and taking modulus?

**A:** Because `'0'` converts an integer digit into its ASCII printable character.

---

### 🧠 **Q4:** Why is there no comma after `98 99`?

**A:** The condition `!(a == 98 && b == 99)` prevents printing one after the final combination.

---

### 🧠 **Q5:** Why use `short` instead of `int`?

**A:** It’s efficient and well-suited for the 0–99 range while complying with 42’s style expectations.

---

### 🧠 **Q6:** What is the purpose of the helper function `print_combination()`?

**A:** It isolates the printing logic, making the main loop cleaner and more modular.

---

### 🧠 **Q7:** How does the program print leading zeros (like `07`)?

**A:** By printing both digits separately — tens (`/ 10`) and ones (`% 10`) — even if the tens digit is `0`.

---

### 🧠 **Q8:** Why is the output considered ascending?

**A:** Because for every pair `(a, b)`, `a` is always smaller than `b`, and both increase together.

---

### 🧠 **Q9:** How many total pairs are there?

**A:** 4950 combinations (from `00 01` to `98 99`).

---

### 🧠 **Q10:** What’s the exact output of this program?

**A:**

```
00 01, 00 02, 00 03, ..., 98 99
```
