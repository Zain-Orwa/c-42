## 🧩 **Exercise 04 — ft_ultimate_div_mod**

---

### 📘 **Objective**

Create a function `ft_ultimate_div_mod` that divides two integers — using pointers — and stores the **result** (quotient) and **remainder** back into the same variables.

> **Prototype:**
>
> ```c
> void ft_ultimate_div_mod(int *a, int *b);
> ```

This function takes two pointers:

* `a` → points to the **dividend** (the number to be divided)
* `b` → points to the **divisor** (the number we divide by)

After the function:

* `*a` will hold the **quotient**
* `*b` will hold the **remainder**

---

### 🧠 **Concepts Involved**

| Concept              | Explanation                                                                         |
| -------------------- | ----------------------------------------------------------------------------------- |
| **Pointers**         | Used to access and modify values stored in another variable’s memory address.       |
| **Dereferencing**    | The `*` operator allows access to the actual value stored at the pointer’s address. |
| **Integer Division** | The `/` operator gives the quotient of a division (e.g., `42 / 8 = 5`).             |
| **Modulo Operation** | The `%` operator gives the remainder of a division (e.g., `42 % 8 = 2`).            |

---

### 🧱 **Function Code**

```c
void ft_ultimate_div_mod(int *a, int *b)
{
    int div;
    int mod;

    div = *a / *b;
    mod = *a % *b;
    *a = div;
    *b = mod;
}
```

---

### 🪄 **How It Works — Step by Step**

Let’s assume:

```c
int x = 42;
int y = 8;
ft_ultimate_div_mod(&x, &y);
```

| Step | Action                   | Explanation                                        |
| ---- | ------------------------ | -------------------------------------------------- |
| 1️⃣  | `*a / *b`                | Takes the values pointed by `a` and `b` → `42 / 8` |
| 2️⃣  | Store quotient in `div`  | `div = 5`                                          |
| 3️⃣  | Store remainder in `mod` | `mod = 2`                                          |
| 4️⃣  | Assign results back      | `*a = div;` → `x = 5` and `*b = mod;` → `y = 2`    |

---

### 🧪 **Test Example (for local testing only)**

```c
#include <stdio.h>

void ft_ultimate_div_mod(int *a, int *b)
{
    int div;
    int mod;

    div = *a / *b;
    mod = *a % *b;
    *a = div;
    *b = mod;
}

int main(void)
{
    int x = 42;
    int y = 8;

    printf("Before division: x = %d, y = %d\n", x, y);
    ft_ultimate_div_mod(&x, &y);
    printf("After division:  x = %d, y = %d\n", x, y);

    return (0);
}
```

🖥️ **Output:**

```
Before division: x = 42, y = 8
After division:  x = 5, y = 2
```

---

### 💬 **Inline Q&A**

**Q1:** Why use pointers here instead of returning two values?

> Because C functions can only return **one value**, but by passing variables by reference (pointers), we can modify both directly in memory.

**Q2:** Why do we use `*a` and `*b` instead of `a` and `b`?

> `a` and `b` are **addresses**, not values. To access the actual integers they point to, we must **dereference** them with `*`.

**Q3:** What happens if `b` is zero?

> Division by zero is **undefined behavior** in C — the program may crash or produce garbage results. Always ensure `*b != 0`.

**Q4:** Why store the values in temporary variables (`div` and `mod`)?

> Because if we assign directly to `*a` before computing the remainder, we’d lose the original dividend (`*a`), making the modulo calculation incorrect.

---

### ⚙️ **Memory Visualization**

```
Before:
+------+      +------+
|  a  | ---> |  42  |
+------+      +------+
|  b  | ---> |   8  |
+------+      +------+

After:
+------+      +------+
|  a  | ---> |   5  |   ← Quotient
+------+      +------+
|  b  | ---> |   2  |   ← Remainder
+------+      +------+
```

---

### 🧾 **Final Notes**

✅ No `#include <stdio.h>` in the final submission — only use it for testing.
✅ No allowed external functions — division and modulo are direct operators.
✅ Follow **42 Norm**: function name, indentation, and variable naming are perfect.

---

### 🧑‍⚖️ **Peer Evaluation Q&A (Integrated)**

| 🔹 Question                                | 💬 Answer                                                         |
| ------------------------------------------ | ----------------------------------------------------------------- |
| What’s the prototype of the function?      | `void ft_ultimate_div_mod(int *a, int *b);`                       |
| What does the function do?                 | Divides `*a` by `*b`, stores quotient in `*a`, remainder in `*b`. |
| Why do we use `*` before variables?        | To dereference pointers and access the actual stored values.      |
| What’s the output if `a = 42` and `b = 8`? | `a = 5`, `b = 2` after function call.                             |
| Why create temporary variables?            | To avoid overwriting `*a` before computing `%`.                   |
| What happens if divisor is 0?              | Undefined behavior — division by zero is illegal.                 |

---

### 🧠 **In Short**

> **Pointers let the function modify two numbers at once.**
> The first (`*a`) becomes the **result**, and the second (`*b`) becomes the **remainder**.
> That’s all — clean, simple, and powerful.

---

