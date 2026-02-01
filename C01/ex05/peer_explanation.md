# 🧩 `ft_putstr` — Peer Explanation (ex05)

> **Goal:** Display a string on standard output using `write()`, but this time **in one system call** instead of character-by-character.

---

## 📜 Code Reference

```c
#include <unistd.h>

int ft_strlen(char *str){
	char *start;

	start = str;
	while (*str)
		str++;
	return (str - start);
}

void ft_putstr(char *str){
	write(1, str, ft_strlen(str));
}
```

---

## ⚙️ Function Overview

This version of `ft_putstr` relies on a helper function `ft_strlen` to compute the **length of the string**, then writes the **entire string at once** using `write()`.

Compared to the previous implementation, this approach is **more efficient** and closer to how real-world C libraries behave.

---

## 🧠 Function: `ft_strlen`

### 💡 Purpose

`ft_strlen` calculates the number of characters in a string **without counting the null terminator**.

---

### 🔍 How It Works

```c
char *start;
start = str;
```

* `start` stores the **initial address** of the string.
* `str` will be moved forward to traverse the string.

```c
while (*str)
	str++;
```

* The loop advances the pointer until it reaches `'\0'`.
* `*str` checks the **character value**, not the address.

```c
return (str - start);
```

* Pointer subtraction gives the **number of characters walked**.
* This is valid because both pointers belong to the same array (the string).

---

### 🧠 Mental Model

If `str` starts at address `1000` and ends at `1014`, then:

```
1014 - 1000 = 14 characters
```

No counter variable needed — the pointer movement itself is the counter.

---

## ⚙️ Function: `ft_putstr`

### 💡 Purpose

Print the entire string to standard output using **a single `write()` call**.

---

### 🔍 Implementation Breakdown

```c
write(1, str, ft_strlen(str));
```

* `1` → file descriptor for **stdout**
* `str` → pointer to the first character
* `ft_strlen(str)` → number of bytes to write

Instead of printing one character at a time, the whole string is sent to the kernel **in one operation**.

---

## 📊 Comparison with Previous Version

| Aspect          | Old Version            | New Version            |
| --------------- | ---------------------- | ---------------------- |
| Writes          | One per character      | One total write        |
| System calls    | Many                   | One                    |
| Performance     | Slower (more syscalls) | Faster (less overhead) |
| Helper function | None                   | `ft_strlen`            |
| Style           | Simple loop            | Modular & reusable     |

---

## ❓ Common Questions (Answered)

### ❓ Why is this version better?

Because **system calls are expensive**. Reducing many `write()` calls into one improves performance and scalability.

---

### ❓ What happens if `str` is empty (`""`)?

* `ft_strlen` returns `0`
* `write(1, str, 0)` writes nothing
* No crash, no output — perfectly safe

---

### ❓ Why not include the `'\0'`?

C strings use `'\0'` only as a **marker**, not as printable content. Writing it would be incorrect.

---

### ❓ Why separate `ft_strlen` instead of counting inside `ft_putstr`?

* Reusability
* Cleaner logic
* Matches how libc is structured
* Encourages modular thinking (important for later projects)

---

## 🧠 Key Concepts Recap

| Concept            | Explanation                            |
| ------------------ | -------------------------------------- |
| Pointer arithmetic | `str - start` computes character count |
| Null terminator    | Stops traversal, not printed           |
| `write()`          | Low-level syscall, writes raw bytes    |
| File descriptor 1  | Standard output                        |
| Efficiency         | Fewer syscalls = better performance    |

---

## 🧠 Analogy

Think of the string as a **package**:

* Old version: shipping **one letter at a time**
* New version: shipping the **entire box at once**

Same result — far less effort.

---

## ✅ Example

```c
ft_putstr("Hello 42!");
```

**Output:**

```
Hello 42!
```

---

## 🏁 Final Notes (42 Exam Mindset)

* This implementation is **correct, efficient, and idiomatic**
* Shows understanding of:

  * pointers
  * memory layout
  * system calls
* Very exam-safe and library-ready

---
Perfect catch — that comparison **must** exist 👍
Here is a **clean, explicit comparison section** you can **append to the peer_explanation.md** (or replace the earlier table if you want it more formal).

---

## 🔁 Old vs New `ft_putstr` — Direct Comparison

### 🧩 Old Implementation (character-by-character)

```c
void ft_putstr(char *str){
	int i = 0;

	while (str[i]){
		write(1, &str[i], 1);
		i++;
	}
}
```

### 🧩 New Implementation (single write)

```c
int ft_strlen(char *str){
	char *start = str;

	while (*str)
		str++;
	return (str - start);
}

void ft_putstr(char *str){
	write(1, str, ft_strlen(str));
}
```

---

## 📊 Technical Comparison Table

| Aspect               | Old Version                 | New Version                     |
| -------------------- | --------------------------- | ------------------------------- |
| Write strategy       | One `write()` per character | One `write()` for entire string |
| Number of syscalls   | `n` (length of string)      | `1`                             |
| Performance          | Slower (syscall-heavy)      | Faster (syscall-efficient)      |
| Pointer usage        | Index-based (`str[i]`)      | Pointer arithmetic              |
| Helper functions     | None                        | `ft_strlen`                     |
| Modularity           | Low                         | High                            |
| Reusability          | Limited                     | `ft_strlen` reusable elsewhere  |
| Library-style design | Educational                 | libc-like                       |
| Scalability          | Poor for long strings       | Good for long strings           |
| Exam readiness       | Acceptable                  | Strong                          |

---

## 🧠 Conceptual Difference (Very Important)

### Old Version

* Focuses on **learning loops and array indexing**
* Easy to understand
* Useful for beginners
* But inefficient at scale

### New Version

* Focuses on **memory, pointers, and system efficiency**
* Teaches how **real C libraries work**
* Shows understanding beyond beginner level
* Preferred in real-world and advanced 42 projects

---

## ⚠️ Subtle but Critical Detail

* The **old version** implicitly counts characters during output
* The **new version** **separates concerns**:

  * One function counts
  * One function outputs

This separation is a core C design philosophy.

---

## 🧠 Examiner’s Perspective (42)

> If both versions are correct, **the second one demonstrates deeper understanding**:
>
> * fewer syscalls
> * better abstraction
> * better performance
> * cleaner responsibility split

This is exactly the kind of refactor examiners like to see.

---

## 🏁 Final Verdict

* ✅ **Old version**: correct, simple, educational
* ✅ **New version**: correct, efficient, professional

**Same output — very different quality.**

---

