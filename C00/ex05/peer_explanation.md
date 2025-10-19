# 🔢 Exercise 05: `ft_print_comb`

### 📁 Directory

`ex05/`

### 📄 File to turn in

`ft_print_comb.c`

### ⚙️ Allowed functions

`write`

---

## 🧠 Objective

Create a function that prints **all unique combinations of three different digits** (`0–9`) in **ascending order**, separated by a comma and a space, without repetition and without a trailing comma after the final combination (`789`).

---

## 📘 Final Code

```c
#include <unistd.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

void print_combo(char a, char b, char c){
	ft_putchar(a);
	ft_putchar(b);
	ft_putchar(c);

	if (!(a == '7' && b == '8' && c == '9')){
		ft_putchar(',');
		ft_putchar(' ');
	}
}

void ft_print_comb(void){
	char a;
	char b;
	char c;

	a = '0';
	while (a <= '7'){
		b = a + 1;
		while (b <= '8'){
			c = b + 1;
			while (c <= '9'){
				print_combo(a, b, c);
				c++;
			}
			b++;
		}
		a++;
	}
}

int main(){
	ft_print_comb();
	return (0);
}
```

---

## 🔍 What You’re Learning

| Concept                | Description                                                                |
| ---------------------- | -------------------------------------------------------------------------- |
| Nested loops           | How to generate all ordered 3-digit combinations                           |
| Character arithmetic   | Iterating through `'0'` to `'9'` as ASCII characters                       |
| Modularity             | Dividing logic into `ft_putchar()`, `print_combo()`, and `ft_print_comb()` |
| Conditional formatting | Avoiding the last comma and space using a condition                        |
| Iteration logic        | Enforcing `a < b < c` to ensure unique ascending combinations              |

---

## 🧩 Line-by-Line Breakdown

| Line                                       | Explanation                                             |
| ------------------------------------------ | ------------------------------------------------------- |
| `#include <unistd.h>`                      | Gives access to the `write()` system call               |
| `ft_putchar()`                             | Prints a single character to standard output            |
| `print_combo(a,b,c)`                       | Prints one valid 3-digit combination                    |
| `if (!(a == '7' && b == '8' && c == '9'))` | Skips the comma and space after the final combo (`789`) |
| `a = '0'`                                  | Start with `'0'` for the first digit                    |
| `while (a <= '7')`                         | Stop at `'7'` so `b` and `c` can still go up to `'9'`   |
| `b = a + 1`                                | Ensures `b` is always greater than `a`                  |
| `c = b + 1`                                | Ensures `c` is always greater than `b`                  |
| `print_combo(a, b, c)`                     | Prints each valid combination in ascending order        |

---

## 🧠 Logic in Plain Words

Each combination must satisfy:

```
a < b < c
```

So:

* If `a = '0'`, then `b` can start from `'1'` and `c` from `'2'`.
* The loops continue until we reach `'7'`, `'8'`, `'9'`.

That gives us all **120 unique combinations** from `012` to `789`.

---

## 🧪 Expected Output

```bash
012, 013, 014, 015, 016, 017, 018, 019, 023, 024, ..., 789
```

No comma or space after `789`.

---

## 💥 Common Mistakes

| Mistake                            | Why It’s Wrong                                            |
| ---------------------------------- | --------------------------------------------------------- |
| Printing after the last combo      | Causes an unwanted trailing comma and space               |
| Using `a <= '9'`                   | Will break the logic since `b` and `c` would exceed `'9'` |
| Missing `b = a + 1` or `c = b + 1` | Allows duplicates like `001` or unordered combos          |
| Forgetting `write()`               | Only `write()` is allowed; `printf()` is forbidden        |

---

## 💡 Concept Visualization

```
a = '0'
│
├─ b = '1'
│  ├─ c = '2' → 012
│  ├─ c = '3' → 013
│  ├─ ...
│  └─ c = '9' → 019
│
├─ b = '2'
│  ├─ c = '3' → 023
│  ├─ ...
│  └─ c = '9' → 029
│
└─ (and so on…)
```

The pattern continues until the last triplet: **789**

---

## 🧩 Summary

| Concept         | Key Takeaway                                 |
| --------------- | -------------------------------------------- |
| Ordering        | `a < b < c` ensures uniqueness               |
| ASCII Iteration | `'0'` through `'9'` are sequential integers  |
| Clean Output    | Avoid trailing comma after the final triplet |
| Function Design | Each function has one clear purpose          |
| Output Result   | `012, 013, ..., 789`                         |

✅ **End Result:**
A clean, modular function that prints all 3-digit combinations from 012 to 789.

---

# 🧩 Peer Evaluation Q&A

### 🧠 **Q1:** What does `ft_print_comb()` do?

**A:** It prints all possible combinations of three different digits (`0–9`) in ascending order, separated by commas and spaces.

---

### 🧠 **Q2:** Why does `a` stop at `'7'`?

**A:** Because after `'7'`, we can’t form a 3-digit combo — `'8'` and `'9'` would already be used.

---

### 🧠 **Q3:** Why use characters `'0'`, `'1'`, etc., instead of integers `0`, `1`?

**A:** Because we’re printing **characters**, not numeric values.
ASCII codes for `'0'` → 48, `'1'` → 49, etc.

---

### 🧠 **Q4:** How does the program ensure digits are unique?

**A:** Each inner loop starts from the previous digit + 1 → that guarantees `a < b < c`.

---

### 🧠 **Q5:** Why do we check `(a == '7' && b == '8' && c == '9')`?

**A:** To detect the final combo and **avoid printing a trailing comma and space**.

---

### 🧠 **Q6:** How many total combinations are printed?

**A:** 120 combinations (`C(10, 3)` = 10 choose 3).

---

### 🧠 **Q7:** What’s the purpose of `print_combo()`?

**A:** To separate printing logic from looping logic — making the code cleaner and reusable.

---

### 🧠 **Q8:** Could we print the comma before instead of after each combo?

**A:** Yes, but that requires skipping the comma before the first combo instead of after the last — both methods work if handled correctly.

---

### 🧠 **Q9:** Why use `write(1, &c, 1)`?

**A:** It directly tells the OS to print one byte (the character) to **stdout** (file descriptor 1).

---

### 🧠 **Q10:** What’s the output of this code?

**A:**

```
012, 013, 014, 015, 016, 017, 018, 019, 023, ..., 789
```

