# 🧩 `ft_strcpy` — Peer Explanation (ex00)

> **Goal:** Reproduce the behavior of the C standard library function `strcpy()`, which copies a string (including its null terminator) from one memory location to another.

---

## 📜 Code Reference

```c
#include <unistd.h>

char *ft_strcpy(char *dest, char *src){
	int i;

	i = 0;
	while (src[i] != '\0'){
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

#include <stdio.h>

int main(void){
	char src[] = "Hello, 42!";
	char dest[20];

	ft_strcpy(dest, src);
	printf("Copied string: %s\n", dest);

	return (0);
}
```

---

## ⚙️ Function: `ft_strcpy`

### 💡 Purpose

The function **copies the contents of one string (`src`) into another (`dest`)**,
including the **null terminator `'\0'`** that marks the end of the string.

This means after the call:

```c
ft_strcpy(dest, src);
```

`dest` contains an identical copy of `src`.

---

### 🧠 Step-by-Step Breakdown

1. **Function signature**

   ```c
   char *ft_strcpy(char *dest, char *src);
   ```

   * `src`: the source string (to be copied).
   * `dest`: the destination memory (where we copy it).
   * Returns a pointer to the beginning of `dest` for convenience.

2. **Index initialization**

   ```c
   i = 0;
   ```

   Start at the first character of both strings.

3. **Copy loop**

   ```c
   while (src[i] != '\0'){
       dest[i] = src[i];
       i++;
   }
   ```

   * Copies one character at a time.
   * Stops **when it reaches the null terminator** in `src`.

4. **Add null terminator**

   ```c
   dest[i] = '\0';
   ```

   Ensures the copied string in `dest` is properly terminated — this is critical.

5. **Return**

   ```c
   return (dest);
   ```

   Returns the start address of `dest`, allowing function chaining like:

   ```c
   printf("%s", ft_strcpy(dest, src));
   ```

---

### 🧩 Example Trace

**Input:**

```c
src = "Hello"
```

| Step | i | src[i] | dest[i] after copy |
| ---- | - | ------ | ------------------ |
| 0    | 0 | 'H'    | 'H'                |
| 1    | 1 | 'e'    | 'e'                |
| 2    | 2 | 'l'    | 'l'                |
| 3    | 3 | 'l'    | 'l'                |
| 4    | 4 | 'o'    | 'o'                |
| 5    | 5 | '\0'   | stop & add '\0'    |

**Result:**
`dest = "Hello"`

---

### 🧩 Output Example

**Input Code:**

```c
char src[] = "42Vienna";
char dest[20];
ft_strcpy(dest, src);
printf("%s\n", dest);
```

**Output:**

```
42Vienna
```

---

### ❓ Discussion

* **Why use `src[i] != '\0'`?**
  Because `'\0'` marks the end of the string in C. Without it, we’d overrun memory.

* **What happens if `dest` is smaller than `src`?**
  Undefined behavior — memory corruption may occur. The function assumes `dest` is large enough.

* **Why return `dest` instead of `void`?**
  It matches the standard `strcpy()` behavior. It’s often used like:

  ```c
  char name[20];
  printf("%s", ft_strcpy(name, "Zain"));
  ```

* **Why copy the null terminator?**
  Without it, the destination string wouldn’t be valid — printing it would continue past the intended end.

---

### 🧠 Analogy

Imagine copying a word letter-by-letter from one notepad (`src`) to another (`dest`).
You stop when you reach the end mark (`'\0'`), and finally draw that same “end mark” in the new notepad to show the word is complete.

---

### ✅ Key Concepts Summary

| Concept         | Explanation                     |
| --------------- | ------------------------------- |
| `src`           | Pointer to the original string  |
| `dest`          | Pointer to destination memory   |
| Loop condition  | Continue until `'\0'`           |
| Null terminator | Ensures valid end of the string |
| Return value    | Pointer to start of `dest`      |

---

### ⚠️ Common Mistakes

| Mistake                                        | Problem                                             |
| ---------------------------------------------- | --------------------------------------------------- |
| Forgetting to copy `'\0'`                      | The destination won’t be a proper C string          |
| Using `dest = src`                             | Just copies the pointer, not the string             |
| Not allocating enough memory                   | Causes buffer overflow                              |
| Using `write()` instead of `printf()` for test | `write()` can’t print multiple chars without a loop |

---

### 🧩 Testing Variations

**Case 1 — Normal string**

```
src = "C is fun"
→ dest = "C is fun"
```

**Case 2 — Empty string**

```
src = ""
→ dest = ""
```

**Case 3 — Spaces and punctuation**

```
src = "Hi 42!"
→ dest = "Hi 42!"
```

---

> 🏁 **Commit Suggestion:**
>
> ```
> Added peer_explanation.md for ex00 (ft_strcpy)
> Includes step-by-step logic, beginner Q&A, and memory safety notes.
> ```

---

