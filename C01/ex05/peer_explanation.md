# 🧩 `ft_putstr` — Peer Explanation (ex05)

> **Goal:** Display a string of characters on the standard output using only the `write()` function.

---

## 📜 Code Reference

```c
#include <unistd.h>

void ft_putstr(char *str){
	int i;

	i = 0;
	while (str[i]){
		write(1, &str[i], 1);
		i++;
	}
}

int main(void){
	char *str = "print a string!";
	ft_putstr(str);
	return (0);
}
```

---

## ⚙️ Function: `ft_putstr`

### 💡 Purpose

`ft_putstr` takes a pointer to a string (`char *str`) and prints each character one by one using `write()`.
It’s a minimal replacement for `printf("%s", str);`, but implemented manually.

---

### 🧠 Step-by-Step Breakdown

1. **`int i;`**
   Creates an index variable to iterate over the characters in the string.

2. **`i = 0;`**
   Start at the beginning of the string.

3. **`while (str[i])`**
   The loop continues until it reaches the **null terminator** (`'\0'`),
   which marks the end of every C string.

4. **`write(1, &str[i], 1);`**

   * `1` → standard output (stdout).
   * `&str[i]` → address of the current character.
   * `1` → write a single byte.
     This prints one character each time the loop runs.

5. **`i++;`**
   Move to the next character.

When `str[i]` becomes `'\0'`, the `while` condition fails, and the function ends.

---

### 🧩 Example Trace

| Step | `i` | `str[i]` | Output | Description        |
| ---- | --- | -------- | ------ | ------------------ |
| 1    | 0   | `'p'`    | p      | write prints `'p'` |
| 2    | 1   | `'r'`    | r      | writes `'r'`       |
| 3    | 2   | `'i'`    | i      | …                  |
| ...  | …   | …        | …      | …                  |
| n    | 14  | `'!'`    | !      | last visible char  |
| n+1  | 15  | `'\0'`   | —      | loop ends          |

Output:

```
print a string!
```

---

### ❓ Common Questions (with Answers)

* **Why `write(1, &str[i], 1)` and not `write(1, str, 1)`?**
  Because we want to print **one character at a time**, so we pass the address of the current character (`&str[i]`).

* **What happens if `str` is empty (`""`)?**
  The condition `str[i]` is immediately false (`'\0'`), so nothing prints — no crash, no output.

* **Why use `write()` and not `printf()`?**
  42’s rule: only use allowed system calls. `write()` gives low-level control and teaches how text output works under the hood.

* **What’s `'\0'`?**
  It’s the **null terminator**, a byte with value 0 marking the end of a C string.

* **Why no newline at the end?**
  Because the exercise doesn’t request it — if you want a newline, you’d call `write(1, "\n", 1);` after the loop.

---

### 🧩 Key Concept Summary

| Concept           | Description                                           |
| ----------------- | ----------------------------------------------------- |
| String Terminator | Every string ends with `'\0'`                         |
| Pointer           | `char *str` stores the address of the first character |
| Write             | Low-level I/O function from `<unistd.h>`              |
| File Descriptor 1 | Standard Output                                       |
| Loop              | Iterates until `str[i] == '\0'`                       |

---

### 🧠 Analogy

Think of the string as a **line of tiles**, each holding one character.
The loop walks over the tiles one by one and sends each to the screen via `write()` until it reaches the “end-of-tiles” marker (`'\0'`).

---

### ✅ Output Example

**Input:**

```c
ft_putstr("Hello 42!");
```

**Output:**

```
Hello 42!
```

---

> 🏁 **Commit suggestion:**
>
> ```
> Added peer_explanation.md for ex05 (ft_putstr)
> Includes explanation, example trace, and pointer discussion.
> ```

---

