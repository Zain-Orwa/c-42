# 🧩 `ft_strlen` — Peer Explanation (ex06)

> **Goal:** Create a function that counts and returns the number of characters in a C string (excluding the null terminator `\0`).

---

## 📜 Code Reference

```c
#include <unistd.h>

int ft_strlen(char *str){
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int main(void){
	char *str = "strlen is counting";
	printf("Number of chars in string: %d\n", ft_strlen(str));
	return (0);
}
```

---

## ⚙️ Function: `ft_strlen`

### 💡 Purpose

`ft_strlen` walks through the string until it finds the **null terminator** (`'\0'`), counting how many visible characters it passes.
It then returns that count as an `int`.

---

### 🧠 Step-by-Step Breakdown

1. **`int i;`**
   Declare a counter variable.

2. **`i = 0;`**
   Initialize it to 0 before counting.

3. **`while (str[i])`**
   The loop continues **as long as the current character isn’t `'\0'`**.
   In C, any non-zero value (any visible character) is considered `true`.
   Once `str[i] == '\0'`, the loop stops.

4. **`i++;`**
   Move to the next character in the string.

5. **`return (i);`**
   Return the total count of characters.

---

### 🔍 Example Trace

| Step | `i` | `str[i]` | Action                   | Counted? |
| ---- | --- | -------- | ------------------------ | -------- |
| 0    | 0   | `'s'`    | not `\0` → keep counting | ✅        |
| 1    | 1   | `'t'`    | not `\0` → keep counting | ✅        |
| 2    | 2   | `'r'`    | …                        | ✅        |
| …    | …   | …        | …                        | …        |
| 17   | 17  | `'g'`    | not `\0` → count         | ✅        |
| 18   | 18  | `'\0'`   | loop stops               | ❌        |

Returned value → `18`.

---

### 🧩 Output Example

**Input:**

```c
char *str = "strlen is counting";
printf("%d\n", ft_strlen(str));
```

**Output:**

```
18
```

---

### ❓ Discussion

* **Why does `while (str[i])` work without comparison to `\0`?**
  Because in C, `'\0'` has value 0 → false.
  Any other character (non-zero) is true, so the loop runs until it finds `'\0'`.

* **What if the string is empty ("")?**
  Then `str[0] == '\0'` immediately, so the loop never runs and the function returns `0`.

* **Why return `int` instead of `size_t`?**
  The exercise specification explicitly says to return `int`.
  The real `strlen()` in the C standard library returns `size_t` to handle very large strings, but for 42’s Piscine scale, `int` is fine.

* **What’s the role of `\0`?**
  It marks the **end of the string in memory**.
  Without it, functions like `ft_strlen` wouldn’t know where to stop reading.

---

### 🧠 Analogy

Imagine you’re counting letters on a road sign: you keep moving right until you hit the **blank space** that means “end of text.”
That blank space is your `'\0'`.

---

### ✅ Key Concept Summary

| Concept         | Meaning                                  |
| --------------- | ---------------------------------------- |
| `char *str`     | Pointer to first character of the string |
| `'\0'`          | End-of-string marker                     |
| Counting logic  | Loop continues while character ≠ `\0`    |
| Return value    | Number of visible characters             |
| Time complexity | **O(n)** — must inspect each char once   |

---

> 🏁 **Commit suggestion:**
>
> ```
> Added peer_explanation.md for ex06 (ft_strlen)
> Includes line-by-line explanation, logic trace, and key C string concepts.
> ```

---

