# **peer_explanation.md — Exercise 02 → `ft_abs.h`**

---

## 🧾 **Exercise Summary**

The goal of this exercise is to create a macro called `ABS` that replaces its argument with its absolute value. The solution must be written in a header file named `ft_abs.h`, and **no functions or additional source files are allowed**.

---

## 📁 **Turn-in Requirements**

| Item                | Description      |
| ------------------- | ---------------- |
| Turn-in directory   | `ex02/`          |
| Files to submit     | `ft_abs.h`       |
| Allowed functions   | None             |
| Special norms check | `-R CheckDefine` |

---

## 🎯 **Main Objective**

### ► Create a macro of the form:

```c
#define ABS(Value)
```

which expands so that:

* If `Value < 0` → it returns `-(Value)`
* Otherwise → it returns `(Value)`

---

## 🧠 **Understanding Macros**

Macros in C are handled by the **preprocessor**, before compilation.
This means:

* They do **text substitution**, not function calls
* They do **not** perform type checking
* They can be **dangerous** if not parenthesized

---

## 🔍 **Correct Macro Implementation**

Final solution typically looks like:

```c
#ifndef FT_ABS_H
# define FT_ABS_H

# define ABS(Value) ((Value) < 0 ? -(Value) : (Value))

#endif
```

---

## ⚙️ **Why Parentheses Matter**

Without parentheses, expressions like:

```c
ABS(a + b)
```

become ambiguous due to operator precedence.

Correct expansion happens because we use:

* `(Value)` around the argument
* `((...))` around the full ternary

This makes the macro safe for usage in expressions.

---

## 🧪 **Testing Example**

Given:

```c
#include "ft_abs.h"
#include <stdio.h>

int main(){
    int Value = -200;
    printf("%d\n", ABS(Value));
    return (0);
}
```

### **Execution Flow:**

1. Preprocessor converts `ABS(Value)` into:

   ```
   ((Value) < 0 ? -(Value) : (Value))
   ```
2. `Value = -200`
3. Condition → `(-200 < 0)` true
4. Result → `-(Value)` → `200`
5. Printed output:

```
200
```

---

## 🔬 **Macro Expansion — Memory Perspective**

Since macros are not functions:

* They **do not exist at runtime**
* They **do not allocate stack frames**
* They **do not consume memory for parameters**
* There is **no return value register**

Instead, the preprocessor **rewrites the code** before compilation.

Example before preprocessing:

```c
printf("%d\n", ABS(-5));
```

After preprocessing (conceptual):

```c
printf("%d\n", ((-5) < 0 ? -(-5) : (-5)));
```

Only after this expansion does compilation and assembly generation occur.

---

## 📏 **Norminette Behavior (`-R CheckDefine`)**

Norminette with `-R CheckDefine` enforces:

✔ Balanced parentheses
✔ Proper spacing
✔ Proper parameter naming
✔ No double parentheses in parameter list
✔ Clean define format

Correct formatting is:

```c
# define ABS(Value) ((Value) < 0 ? -(Value) : (Value))
```

---

## ⚔️ **Macro vs Function — `ABS` vs `abs()`**

### **1. `abs()` Function**

* Located in `<stdlib.h>`
* Has type checking
* Debuggable
* Uses stack/registers
* Only handles `int`

### **2. `ABS` Macro**

* No type safety
* No debugging
* Works with many types (`int`, `float`, `expression`)
* No runtime cost
* Can double-evaluate expressions

Double-evaluation bug example:

```c
ABS(i++)
```

Expands to:

```c
((i++) < 0 ? -(i++) : (i++))
```

→ `i` increments **multiple times**.

---

## 🧩 **Macro Substitution Flow (Diagrams)**

### **Diagram 1 — Source Code**

```
┌────────────────────────────┐
│ printf("%d\n", ABS(-3));   │
└────────────────────────────┘
                │
                ▼
```

### **Diagram 2 — Preprocessor Text Replacement**

```
┌────────────────────────────────────────────────────┐
│ printf("%d\n", ((-3) < 0 ? -(-3) : (-3)));          │
└────────────────────────────────────────────────────┘
                │
                ▼
```

### **Diagram 3 — Compiler Generates Assembly**

```
mov eax, 3
push eax
call printf
```

Nothing about `ABS` exists in the generated machine code — it is replaced earlier.

---

## ❓ **Common Errors FAQ**

**Q1: Why do we use `(Value)` instead of just `Value`?**
➤ To ensure correct precedence when `Value` is an expression.

---

**Q2: Why do we wrap the whole macro in double parentheses?**
➤ So expressions like `2 * ABS(x)` work as intended.

---

**Q3: Why not just include `<stdlib.h>` and use `abs()`?**
➤ The exercise forbids functions and wants you to learn macros.

---

**Q4: Why is `unistd.h` unnecessary in the header?**
➤ The macro doesn't need system calls or I/O.

---

**Q5: Why does Norminette use `-R CheckDefine`?**
➤ It performs strict checks specifically for macros.

---

## 🗂 **Peer Evaluation — Q&A Style**

Below are typical peer evaluation questions and proper answers:

---

### **Q: What does the macro ABS do?**

**A:** It expands to a ternary expression that returns the absolute value of its input.

---

### **Q: Is ABS a function?**

**A:** No, it's a macro handled by the preprocessor, not at runtime.

---

### **Q: Why is ABS faster than abs()?**

**A:** It avoids a function call and is resolved at compile time.

---

### **Q: Why are parentheses necessary in the macro?**

**A:** To prevent precedence issues and support expressions as arguments.

---

### **Q: Does ABS allocate memory?**

**A:** No. Macros do not use the stack or heap; they are text substitutions.

---

### **Q: What happens if you pass `ABS(i++)`?**

**A:** `i` may be incremented multiple times, because macros evaluate arguments multiple times.

---

## 🧾 **Conclusion**

`ft_abs.h` teaches:

* Preprocessing behavior
* Macro safety patterns
* Expression handling
* Norminette macro rules
* Differences between compile-time vs runtime
* Low-level understanding of C compilation stages

While simple, this foundational exercise prepares you for:

* libft
* header-only libraries
* performance-critical code
* embedded C

---


