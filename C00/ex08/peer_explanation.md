# 🧩 `ft_print_combn` — Peer Explanation (ex08)

> Print all **strictly increasing** `n`-digit combinations (`0..9`) in **lexicographic order**, separated by `", "`, stopping cleanly at the last combination.

---

## 🧠 Overview

The program builds combinations step by step using four helper functions:

1. `ft_putchar` → outputs one character
2. `print_combination` → prints the current array of digits
3. `is_last_combination` → checks if we reached the final combo
4. `increment_combination` → generates the next valid combo

The main function `ft_print_combn` orchestrates the logic:
initialize, print, check, separate, and increment.

---

## 🧩 Full Code Reference

```c
#include <unistd.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

void print_combination(int digits[], int n){
	int i = 0;
	while (i < n){
		ft_putchar(digits[i] + '0');
		i++;
	}
}

int is_last_combination(int digits[], int n){
	int i = 0;
	while (i < n){
		if (digits[i] != 9 - (n - 1 - i))
			return (0);
		i++;
	}
	return (1);
}

void increment_combination(int digits[], int n){
	int i = n - 1;
	int max;

	while (i >= 0){
		max = 9 - (n - 1 - i);
		if (digits[i] < max){
			digits[i]++;
			while (++i < n)
				digits[i] = digits[i - 1] + 1;  // reset suffix minimally
			return;
		}
		i--;
	}
}

void ft_print_combn(int n){
	int digits[10];
	int i = 0;

	while (i < n){
		digits[i] = i;   // minimal start: 0..n-1
		i++;
	}
	while (1){
		print_combination(digits, n);
		if (is_last_combination(digits, n))
			return;
		ft_putchar(',');
		ft_putchar(' ');
		increment_combination(digits, n);
	}
}

int main(void){
	ft_print_combn(2);
	return (0);
}
```

---

## ⚙️ `ft_putchar`

```c
void ft_putchar(char c){
	write(1, &c, 1);
}
```

### 💡 Explanation

* A minimal wrapper around the `write()` system call.
* Sends **1 byte** to **stdout** (file descriptor `1`).
* Used instead of `printf()` to meet 42’s low-level output requirement.

### ❓ Discussion

* **Why use `&c`?**
  Because `write()` needs a **pointer** to memory; `&c` is the address of that character.
* **Why not `printf`?**
  The 42 norm enforces learning low-level I/O before high-level libs.

---

## ✨ `print_combination`

```c
void print_combination(int digits[], int n){
	int i = 0;
	while (i < n){
		ft_putchar(digits[i] + '0');
		i++;
	}
}
```

### 💡 Explanation

* Prints exactly the first **`n`** digits of the array.
* Converts integers `0–9` into ASCII characters by adding `'0'`.

### ❓ Discussion

* **What about the rest of `digits[10]`?**
  They’re ignored; only the first `n` elements are printed.
* **Why add `'0'`?**
  Because `'0'` in ASCII = 48. Adding it converts the int to its visual digit.

---

## 🧮 `is_last_combination`

```c
int is_last_combination(int digits[], int n){
	int i = 0;
	while (i < n){
		if (digits[i] != 9 - (n - 1 - i))
			return (0);
		i++;
	}
	return (1);
}
```

### 💡 Explanation

* Checks if the array matches the **final pattern** for that `n`.
* The last possible digits follow this rule:

  ```
  max(i) = 9 - (n - 1 - i)
  ```

  Examples:

  | n | Last Combination |
  | - | ---------------- |
  | 1 | 9                |
  | 2 | 8 9              |
  | 3 | 7 8 9            |
* If any digit mismatches → return 0.
  If all digits match → return 1.

### ❓ Discussion

* **Why use `9 - (n - 1 - i)`?**
  It gives the **maximum allowed digit** for position `i` while keeping later digits strictly larger.
* **Can some digits match while others don’t?**
  Yes. It loops through all; a mismatch anywhere returns `0`.
* **When all match?**
  The combo equals the final `[9-(n-1), 9-(n-2), ..., 9]`.

---

## 🔁 `increment_combination`

```c
void increment_combination(int digits[], int n){
	int i = n - 1;
	int max;

	while (i >= 0){
		max = 9 - (n - 1 - i);
		if (digits[i] < max){
			digits[i]++;
			while (++i < n)
				digits[i] = digits[i - 1] + 1;
			return;
		}
		i--;
	}
}
```

### 💡 Explanation

This function acts like an **odometer** for increasing sequences:

1. Start from the **rightmost digit** (`i = n - 1`).
2. Calculate its **max allowed value** (`9 - (n - 1 - i)`).
3. If it’s not max, increment it by `1`.
4. **Reset** all following digits to the smallest possible increasing tail.
5. If a digit is already max, move **left** and repeat (carry logic).

### 🔍 Example (n = 3)

| Step      | Action                                      | Result    |
| --------- | ------------------------------------------- | --------- |
| `[2,3,4]` | bump last → 5                               | `[2,3,5]` |
| `[2,3,9]` | carry left, bump middle → 4, reset → 5      | `[2,4,5]` |
| `[2,7,9]` | carry → `[2,8,9]` → carry again → `[3,4,5]` |           |

### ❓ Discussion

* **What does “reset” mean?**
  After bumping one index, every index to its right is set to `previous + 1` to keep strict order.
  Example: `[2,3,9] → bump middle → [2,4,5]`.
* **Why `< max` instead of `<=`?**
  Because `== max` means no room to increase; must carry left.
* **Does `i` inside `while (++i < n)` affect outer `i`?**
  Yes, it’s the same variable, but we `return` immediately afterward.
* **When can `i` reach 0?**
  During carries when all right digits are at max — at that point, the next combo doesn’t exist (caught earlier by `is_last_combination`).

---

## 🎬 `ft_print_combn`

```c
void ft_print_combn(int n){
	int digits[10];
	int i = 0;

	while (i < n)
		digits[i++] = i - 1;

	while (1){
		print_combination(digits, n);
		if (is_last_combination(digits, n))
			return;
		ft_putchar(',');
		ft_putchar(' ');
		increment_combination(digits, n);
	}
}
```

### 💡 Explanation

This function **controls the sequence generation**.

1. Initialize array as `[0, 1, 2, ..., n-1]`.
2. Print the current combination.
3. If it’s the last → `return`.
4. Otherwise print `", "` and get the next one.

### ❓ Discussion

* **Why use `while (1)`?**
  It’s an intentional infinite loop, stopped only when `is_last_combination()` returns true.
* **Why `return` and not `break`?**
  Both work, but `return` is cleaner—it ends the function explicitly.
* **What happens to unused digits in `digits[10]`?**
  They’re ignored; we only print and modify the first `n`.

---

## 🧪 `increment_combination_debug` (Optional Learning Tool)

> ⚠️ For understanding only — don’t submit with this in 42.

```c
#include <stdio.h>

static void dbg_print_array(const char *tag, int a[], int n){
    int i;
    printf("%s [", tag);
    for (i = 0; i < n; ++i){
        printf("%d", a[i]);
        if (i + 1 < n) printf(",");
    }
    printf("]\n");
}

void increment_combination_debug(int digits[], int n){
    int i = n - 1;
    int max;

    dbg_print_array("START", digits, n);

    while (i >= 0){
        max = 9 - (n - 1 - i);
        printf("Check i=%d (val=%d) max=%d\n", i, digits[i], max);

        if (digits[i] < max){
            digits[i]++;
            printf("  BUMP  i=%d -> %d\n", i, digits[i]);

            while (++i < n){
                digits[i] = digits[i - 1] + 1;
                printf("  RESET i=%d -> %d\n", i, digits[i]);
            }
            dbg_print_array("END  ", digits, n);
            return;
        }

        printf("  CARRY LEFT (i=%d at max)\n", i);
        i--;
    }

    printf("NO-NEXT: already at terminal combo\n");
}
```

### 🧩 Debug Driver Example

```c
int main(void){
    int n = 3;
    int digits[3] = {2,7,8};

    increment_combination_debug(digits, n);
    increment_combination_debug(digits, n);
    increment_combination_debug(digits, n);

    return 0;
}
```

### 🧠 Expected Output

```
START [2,7,8]
Check i=2 (val=8) max=9
  BUMP  i=2 -> 9
END   [2,7,9]

START [2,7,9]
Check i=2 (val=9) max=9
  CARRY LEFT (i=2 at max)
Check i=1 (val=7) max=8
  BUMP  i=1 -> 8
  RESET i=2 -> 9
END   [2,8,9]

START [2,8,9]
Check i=2 (val=9) max=9
  CARRY LEFT (i=2 at max)
Check i=1 (val=8) max=8
  CARRY LEFT (i=1 at max)
Check i=0 (val=2) max=7
  BUMP  i=0 -> 3
  RESET i=1 -> 4
  RESET i=2 -> 5
END   [3,4,5]
```

---

## ✅ Summary

| Function                | Purpose                                        |
| ----------------------- | ---------------------------------------------- |
| `ft_putchar`            | Outputs a single char                          |
| `print_combination`     | Prints only the first `n` digits               |
| `is_last_combination`   | Checks if combination == final pattern         |
| `increment_combination` | Generates next combo (with carry & reset)      |
| `ft_print_combn`        | Controls printing, separation, and termination |

---

### 🧭 Final Key Points

* `9 - (n - 1 - i)` defines the **max digit** allowed per position.
* “Reset” means restoring the **smallest valid increasing suffix**.
* `while (1)` is deliberate; the exit condition is manual.
* `return` ends the loop cleanly; no extra code runs after it.
* The debug version helps you **visualize carries and resets** perfectly.

