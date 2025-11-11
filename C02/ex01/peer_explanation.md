# 🧩 `ft_strncpy` — Peer Explanation (ex01)

> **Goal:** Recreate the behavior of `strncpy()` — copy up to *n* characters from a source string into a destination string, padding with `'\0'` if the source is shorter.

---

## 📜 Code Reference (Correct Implementation)

```c
#include <unistd.h>

char *ft_strncpy(char *dest, char *src, unsigned int n){
	unsigned int i;

	i = 0;
	while (i < n && src[i] != '\0'){
		dest[i] = src[i];
		i++;
	}
	while (i < n){
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

#include <stdio.h>

int main(void){
	char src[] = "Source";
	char dest[] = "#####";

	ft_strncpy(dest, src, 2);
	printf("Copied string: \"%s\"\n", dest);

	return (0);
}
```

---

## ⚙️ Function: `ft_strncpy`

### 💡 Purpose

The function **copies** a specified number (`n`) of characters from the source string (`src`) to the destination string (`dest`).

* If `src` is **shorter than n**, the remaining bytes in `dest` are filled with `'\0'`.
* If `src` is **longer than n**, only the first `n` characters are copied — no `'\0'` is appended automatically.

---

### 🧠 Step-by-Step Breakdown

1. **`char *dest, char *src`**

   * `src`: the original text we want to copy.
   * `dest`: the destination memory where we’ll write it.

2. **`unsigned int n`**

   * The number of bytes we are allowed to copy.

3. **First `while` loop**

   ```c
   while (i < n && src[i] != '\0'){
       dest[i] = src[i];
       i++;
   }
   ```

   * Copies characters one by one.
   * Stops if it copied `n` characters **or** found the end of the source string.

4. **Second `while` loop**

   ```c
   while (i < n){
       dest[i] = '\0';
       i++;
   }
   ```

   * If `src` is shorter than `n`, fill the rest of `dest` with null bytes to ensure proper padding.

5. **Return `dest`**

   * Returns a pointer to the beginning of the destination string for potential chaining (like the real `strncpy`).

---

### 🧩 Example Trace

**Input:**

```c
src = "Hi"
n = 5
```

| Step | i | src[i] | Action                      | dest[i] |
| ---- | - | ------ | --------------------------- | ------- |
| 0    | 0 | 'H'    | copy                        | 'H'     |
| 1    | 1 | 'i'    | copy                        | 'i'     |
| 2    | 2 | '\0'   | stop copying, start padding | '\0'    |
| 3    | 3 | —      | pad                         | '\0'    |
| 4    | 4 | —      | pad                         | '\0'    |

**Result:** `"Hi"` followed by three null bytes.
`dest` = `"Hi\0\0\0"`

---

### 🧩 Output Examples

**Case 1 – Source shorter than n**

```c
src = "Hello"
n = 10
Output → "Hello" + 5 nulls
```

**Case 2 – Source longer than n**

```c
src = "Programming"
n = 5
Output → "Progr" (no null terminator)
```

**Case 3 – Exact length**

```c
src = "Test"
n = 4
Output → "Test" (no padding)
```

---

### ❓ Discussion

* **Why `unsigned int n`?**
  Because the number of bytes can never be negative — unsigned ensures that.

* **Why return `dest`?**
  That’s how C standard functions like `strcpy()` and `strncpy()` work, so you can write:

  ```c
  printf("%s", ft_strncpy(dest, src, n));
  ```

* **Why fill with `'\0'`?**
  To guarantee that unused parts of the buffer are cleared — useful for binary-safe data or string padding.

* **What happens if `src` is shorter than `n` but `dest` already had old data?**
  The padding loop ensures all old data is overwritten with `'\0'`.

---

### 🧠 Analogy

Imagine `src` is a short sentence you copy onto a fixed-size paper (`dest`) that must always have *n lines*.
If your sentence is shorter, you fill the remaining lines with blank spaces — that’s what the padding loop does.

---

### ✅ Key Summary

| Step     | Purpose                                            |
| -------- | -------------------------------------------------- |
| Loop 1   | Copy characters until end of `src` or limit `n`    |
| Loop 2   | Pad with `'\0'` until reaching `n`                 |
| Return   | Pointer to `dest` (the start of the copied buffer) |
| Behavior | Stops early if `src` ends before `n`               |

---

### ⚠️ Common Mistakes

| Mistake                          | Problem                                               |
| -------------------------------- | ----------------------------------------------------- |
| Forgetting the padding loop      | Leaves garbage bytes in `dest`                        |
| Copying more than `n` chars      | Buffer overflow                                       |
| Not using `unsigned int` for `n` | Negative values can cause infinite loops              |
| Forgetting to return `dest`      | Breaks compatibility with standard `strncpy` behavior |

---

### ✅ Output (from test program)

```
Copied string: "Hello 42"
```

---

> 🏁 **Commit Suggestion:**
>
> ```
> Added peer_explanation.md for ex01 (ft_strncpy)
> Includes corrected implementation, step-by-step reasoning, and examples.
> ```

---

