# 🧩 **Peer Explanation — `ft_strlcpy` (Exercise 10)**

> **Goal:** Reproduce the behavior of `strlcpy`
> **Prototype:**

```c
unsigned int ft_strlcpy(char *dest, char *src, unsigned int size);
```

---

# ## 1️⃣ Overview

`ft_strlcpy` copies a string safely into a destination buffer with three rules:

1. **Copy at most `size - 1` characters**
2. **Always NUL-terminate `dest` (if size > 0)**
3. **Return the full length of `src`**, regardless of how many characters were copied

This protects the destination from overflow while still telling the caller whether truncation happened.

---

# ## 2️⃣ Source Code (Exercise Version)

```c
int ft_strlen(char *str){
	int   i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

unsigned int ft_strlcpy(char *dest, char *src, unsigned int size){
	unsigned int i;

	i = 0;
	if (size > 0){
		while (src[i] != '\0' && i < size - 1){
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}
```

---

# ## 3️⃣ Function Breakdown + Deep Questions

---

# ### 🔹 **`ft_strlen`**

Counts characters until it finds `'\0'`.

Nothing unusual here — needed because `strlcpy` must return the length of `src`.

---

# ### 🔹 **`ft_strlcpy` — copying loop**

Relevant part:

```c
i = 0;
if (size > 0){
	while (src[i] != '\0' && i < size - 1){
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
```

---

# ## 🔍 **Explanation of the Copying Logic**

* We stop copying when:

  * we reach the end of `src`, OR
  * we run out of space (`i == size - 1`)

* After stopping, we ALWAYS write:

```c
dest[i] = '\0';
```

This ensures the destination string **always stays valid**.

---

# ## ❓ Student Questions + Answers

---

### **Q1 — “Do we stop at the last character of the word? For example in `letter` do we stop at `'r'`?”**

**Answer:**
We stop at **whichever condition triggers first**:

* If `src` ends → yes, we stop at `'r'` because `src[i] == '\0'`
* If the destination buffer is small → we stop earlier at `i == size - 1`

So:
**We do NOT stop because a character is “last.”
We stop because the loop condition tells us to stop.**

---

### **Q2 — “You said we stop at `i = 6`. When we insert the null terminator, does it overwrite index 6? Or does the null automatically go to index 7 after the last character?”**

**Answer:**
There is **NO automatic behavior**.
C NEVER puts the null terminator “after” the last character for you.

The statement:

```c
dest[i] = '\0';
```

ALWAYS writes exactly at **index `i`**.

If `i == 6`, then:

```
dest[6] = '\0'
```

There is no magic “i = 7.”

---

### **Q3 — “So the null terminator overwrites the last copied character position?”**

**Answer:**
Yes — EXACTLY that.

Example:
If size = 6 and you copy `"letter"`:

```
i goes: 0 1 2 3 4
dest:   l e t t e
```

When `i == 5`, the loop ends (because `i < size - 1` is false).
Then:

```
dest[5] = '\0'
```

`'\0'` replaces whatever was at index 5.

---

### **Q4 — “So the null terminator does NOT go after the end of the real string?”**

**Answer:**
Correct.

The string “ends” **exactly where you place `'\0'`**.
Nothing is automatic in C.

---

### **Q5 — “Does the function always return the number of characters copied?”**

**Answer:**
No.

It returns:

```c
return ft_strlen(src);
```

This is the **full length of src**, even if the copying was truncated.

This is how the caller knows whether truncation happened.

---

# ## 4️⃣ Memory Diagram Example

Let:

```
src  = "letter"
size = 7
```

```
Index: 0 1 2 3 4 5 6
src:   l e t t e r \0
dest:  l e t t e r \0
                ↑  
             dest[i] = '\0'
```

Let:

```
size = 4
```

```
Index: 0 1 2 3
src:   l e t t e r...
dest:  l e t t \0
             ↑
         dest[i] = '\0'
```

Perfectly matches the logic.

---

# ## 5️⃣ Return Value Behavior Summary

| Situation              | Copied into `dest` | Return Value  |
| ---------------------- | ------------------ | ------------- |
| Dest buffer big enough | full string        | length of src |
| Dest buffer too small  | truncated string   | length of src |
| size == 0              | nothing            | length of src |

---

# ## 6️⃣ Final Summary

* `strlcpy` copies safely with `size - 1` rule
* Always null terminates when `size > 0`
* Return value = length of the source
* `'\0'` ALWAYS overwrites the current index `i`
* C NEVER adds a null terminator automatically
* This function is used to avoid buffer overflow and detect truncation

---

