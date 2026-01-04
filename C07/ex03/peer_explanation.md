# 🧵 ft_strjoin — Peer Explanation

## 📌 Overview

The goal of `ft_strjoin` is to **concatenate multiple strings** stored in an array (`strs`) into **one newly allocated string**, inserting a **separator string (`sep`)** between each element.

This function is similar in spirit to `str.join()` in higher-level languages, but must be implemented **manually in C**, respecting memory allocation rules.

---

## 📄 Prototype

```c
char *ft_strjoin(int size, char **strs, char *sep);
```

---

## 🧠 Parameters Explained

| Parameter | Meaning                            |
| --------- | ---------------------------------- |
| `size`    | Number of strings inside `strs`    |
| `strs`    | Array of strings to concatenate    |
| `sep`     | Separator inserted between strings |

---

## ⚠️ Special Rule (Important)

> If `size == 0`, the function **must return a malloc’ed empty string** (`""`).

This is explicitly required by the subject.

---

## 🧱 High-Level Strategy

We solve the problem in **four clear steps**:

1. **Handle the edge case** (`size == 0`)
2. **Calculate total memory needed**
3. **Allocate memory**
4. **Copy strings and separators**

This separation keeps the code readable and safe.

---

## 🔹 Step 1 — String Length Helper

```c
int ft_strlen(char *str)
```

### Purpose

Counts how many characters are in a string **excluding** `'\0'`.

### Why needed?

We must know **exact sizes** before allocating memory.
Using `strlen` from the library is forbidden, so we reimplement it.

---

## 🔹 Step 2 — Calculate Total Length

```c
int calculate_total_length(int size, char **strs, char *sep)
```

### Logic

* Sum the length of **each string**
* Add the length of `sep` **(size - 1) times**
* Do **not** add a separator after the last string

### Formula

```
total =
  sum(strlen(strs[i])) +
  (size - 1) * strlen(sep)
```

### Why this matters

* Allocating **too little** → buffer overflow ❌
* Allocating **too much** → memory waste ❌

This function guarantees **exact allocation**.

---

## 🔹 Step 3 — Handle `size == 0`

```c
if (size == 0)
{
    joined_str = malloc(1);
    joined_str[0] = '\0';
    return (joined_str);
}
```

### Why allocate 1 byte?

* Even an empty string needs space for `'\0'`
* Returning `NULL` would **fail the subject**

---

## 🔹 Step 4 — Memory Allocation

```c
joined_str = malloc(sizeof(char) * total_len);
```

⚠️ Important note:

* `total_len` does **not** include `'\0'`
* We add `'\0'` manually after copying

---

## 🔹 Step 5 — Concatenation Logic

### Key Variables

| Variable | Role                                   |
| -------- | -------------------------------------- |
| `i`      | Index of current string                |
| `j`      | Index inside current string            |
| `pos`    | Current write position in `joined_str` |

### Copy Process

1. Copy `strs[i]` character by character
2. If not the last string → copy `sep`
3. Move to the next string

This avoids extra separators at the end.

---

## ✨ Final Null-Termination

```c
joined_str[pos] = '\0';
```

Without this:

* The string is **not valid**
* `printf`, `strcmp`, etc. break

---

## 🧪 Example

### Input

```c
strs = ["Hello", "42", "Network"]
sep  = " | "
```

### Output

```text
Hello | 42 | Network
```

---

## ⛔ Common Mistakes (Peer Warnings)

| Mistake                            | Why It’s Wrong             |
| ---------------------------------- | -------------------------- |
| Forgetting `size == 0`             | Automatic failure          |
| Adding separator after last string | Output mismatch            |
| Forgetting `'\0'`                  | Undefined behavior         |
| Using `static`                     | Not required, bad practice |
| Allocating wrong size              | Memory errors              |

---

## 🧠 Key Takeaways

* `ft_strjoin` tests **memory planning**, not just concatenation
* Always calculate before allocating
* Manual indexing gives full control
* Clean separation of concerns = fewer bugs

---

## ✅ Peer Evaluation Q&A

**Q: Why not allocate inside the loop?**
A: Allocation must happen **once**, after knowing total size.

**Q: Why use `pos` instead of recalculating indexes?**
A: It avoids repeated computations and keeps logic simple.

**Q: Is returning an empty malloc’ed string mandatory?**
A: Yes — the subject explicitly requires it.

---

## 🏁 Conclusion

`ft_strjoin` is a **core Piscine exercise** that validates:

* String traversal
* Dynamic memory management
* Edge-case handling
* Clean algorithmic thinking

A correct solution is **simple, precise, and predictable** — exactly what this implementation achieves.

---

