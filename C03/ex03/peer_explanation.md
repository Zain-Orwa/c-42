# 🧩 **Exercise03: ft_strncat — Peer Explanation**

*(with index version vs pointer version comparison)*

---

# ✅ **1. What ft_strncat does**

The function:

```c
char *ft_strncat(char *dest, char *src, unsigned int nb);
```

**Appends at most `nb` characters** from `src` to the end of `dest`,
adds a final `'\0'`, and returns `dest`.

---

# 🧪 **2. The Two Versions We Compare**

## 🟦 **A) Index-Based Version (yours)**

```c
char *ft_strncat(char *dest, char *src, unsigned int nb){
	unsigned int i = ft_strlen(dest);
	unsigned int j = 0;

	while (j < nb && src[j] != '\0'){
		dest[i++] = src[j++];
	}
	dest[i] = '\0';
	return (dest);
}
```

## 🟩 **B) Pointer-Based Version**

```c
char *ft_strncat(char *dest, char *src, unsigned int nb){
	char *ptr;

	ptr = dest;
	while (*ptr)
		ptr++;
	while (*src && nb--)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}
```

---

# 🔍 **3. How Each Version Works**

## 🟦 **A) Index Version — Explanation**

### **Step 1: Find the end of dest**

```c
i = ft_strlen(dest);
```

* `i` is now the index of the **null terminator** in `dest`.
* This is where we start writing.

### **Step 2: Copy characters**

```c
while (j < nb && src[j] != '\0')
```

* Stop when we copied `nb` characters OR when `src` ends.

### **Step 3: Add new null terminator**

```c
dest[i] = '\0';
```

### **Step 4: Return dest**

* Because `dest` always points to the start.

---

## 🟩 **B) Pointer Version — Explanation**

### **Step 1: Move pointer to end of dest**

```c
ptr = dest;
while (*ptr)
    ptr++;
```

`ptr` now points to the existing `'\0'`.

### **Step 2: Copy characters**

```c
while (*src && nb--)
    *ptr++ = *src++;
```

* Copies the character, then moves `ptr` and `src` to the next byte.

### **Step 3: Add null terminator**

```c
*ptr = '\0';
```

### **Step 4: Return dest**

* Even though we modified `ptr`,
  **we must return the original pointer (`dest`)**.

---

# 🤔 **4. Important Question You Asked:**

## ❓ **Why do we return `dest`, not `ptr`?**

### 🟩 Short answer:

Because **ptr moved** — it no longer points to the beginning of the string.

### 🟦 Longer explanation:

In pointer version:

```c
ptr = dest;
ptr++;  // ptr now moved forward
```

If you return `ptr`, you return a pointer that now points somewhere **inside** the string (usually the end of dest).
That would break the output.

So:

* `dest` → always points to the beginning → correct return value
* `ptr` → points to the end → wrong return value

---

# ⚠️ **5. Is the pointer version dangerous?**

### ✔️ Safe:

Using `ptr` to *walk and write* inside `dest`.

### ❌ Not safe:

Returning `ptr` (because you lose the beginning of the string).

But just modifying `ptr` during the copy is **not dangerous at all**.

---

# 🔍 **6. Differences Between the Two Versions**

| Topic                     | Index Version              | Pointer Version            |
| ------------------------- | -------------------------- | -------------------------- |
| How they find end of dest | `i = ft_strlen(dest);`     | `while (*ptr) ptr++;`      |
| How they copy             | `dest[i++] = src[j++]`     | `*ptr++ = *src++`          |
| Loop condition            | `j < nb && src[j] != '\0'` | `*src && nb--`             |
| Memory access             | Uses `dest[i]`, `src[j]`   | Uses pointers directly     |
| Does pointer move?        | No                         | Yes (`ptr++`, `src++`)     |
| Return value              | `dest`                     | `dest` (important!)        |
| Beginner friendliness     | Easier                     | More professional, shorter |

Both produce **identical output**.

---

# 🔥 **7. Why the pointer version is common in professional C**

* shorter
* no explicit indexing
* pointer arithmetic is faster and idiomatic
* common in coding interviews
* matches how real `strncat` is implemented

But both are 100% correct.

---

# 🧨 **8. Common Mistakes (that students make)**

| Mistake                               | Why it's wrong                                  |
| ------------------------------------- | ----------------------------------------------- |
| ❌ Forgetting `dest[i] = '\0'`         | Leaves garbage after string; undefined behavior |
| ❌ Copying without checking for `'\0'` | Reads past src into memory garbage              |
| ❌ Returning the moved pointer (`ptr`) | Loses start of string                           |
| ❌ Using `nb--` incorrectly            | Might copy too many characters                  |
| ❌ Not ensuring dest is big enough     | Causes buffer overflow                          |
| ❌ Modifying src                       | Forbidden — src must stay unchanged             |

---

# 📝 **9. Summary**

**Both versions achieve the same logic:**

1. Go to the end of dest
2. Copy characters from src
3. Stop after nb characters or at null terminator
4. Add new '\0'
5. Return dest

---

# 🎤 **10. Peer Evaluation Q&A**

**Q1: What does ft_strncat return?**
➡️ `dest` — the beginning of the final string.

**Q2: Why can't we return ptr?**
➡️ Because ptr moved to the end; dest always stays at beginning.

**Q3: When do we stop copying?**
➡️ When we reach `nb` characters OR `src` ends.

**Q4: What happens if dest is too small?**
➡️ Overflow — undefined behavior. Caller must ensure enough space.

**Q5: Does src change?**
➡️ No. Only read from src.

**Q6: Which version is better for exam?**
➡️ Pointer version is cleaner and more "C-style", but both are accepted.

**Q7: What if nb = 0?**
➡️ Nothing is copied, but dest is still valid.

**Q8: Why do we need to add final '\0'?**
➡️ Because concatenation overwrites the old one.

**Q9: Can dest and src overlap?**
➡️ No. Undefined behavior (same as real strncat).

**Q10: Does the function handle empty src?**
➡️ Yes — loop stops immediately.

---

