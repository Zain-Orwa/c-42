# 🧠 Exercise 04 — ft_convert_base

## 📌 Exercise Context (Subject Recap)

**Exercise 04 — ft_convert_base**

You must write a function that converts a number represented as a string (`nbr`) from one base (`base_from`) to another (`base_to`).

```c
char *ft_convert_base(char *nbr, char *base_from, char *base_to);
```

### Rules from the subject

* `nbr`, `base_from`, `base_to` **may not be writable**
* `nbr` follows the same rules as `ft_atoi_base`

  * skip whitespaces
  * handle multiple `+` / `-`
* The value **fits in an `int`**
* If a base is invalid → return `NULL`
* The returned string:

  * contains **no whitespaces**
  * contains **no '+'**
  * contains **at most one '-'**, at the beginning
* Allowed functions: `malloc`, `free`

---

## 🧩 High-Level Strategy

The exercise is intentionally split into **two logical phases**:

1. **Convert from base_from → integer**
   (`ft_atoi_base`)
2. **Convert integer → base_to string**
   (`ft_itoa_base`)

This separation of concerns is critical for clarity, correctness, and reuse.

```
nbr (string) ──► ft_atoi_base ──► int ──► ft_itoa_base ──► string
```

---

## 🧱 Base Validation (Why it matters)

A base is **invalid** if:

* length ≤ 1
* contains duplicates
* contains whitespace, `+`, `-`, or non-printable characters

### Robust validation used

```c
if (base[i] <= 32 || base[i] == 127 || base[i] == '+' || base[i] == '-')
    return (0);
```

**Why this is good:**

* `<= 32` → catches all ASCII whitespaces & control chars
* `127` → DEL character
* Explicit `+` / `-` rejection (required by subject)

This approach is shorter, clearer, and safer than checking ranges manually.

---

## 🔢 ft_atoi_base — From string to int

### Responsibilities

* Skip whitespaces
* Handle multiple `+` and `-`
* Convert characters using the given base
* Stop at the first invalid character

### Important detail (common bug)

```c
long long result;
```

⚠️ `result` **must be initialized to 0** before using:

```c
result = 0;
```

Otherwise, you get **undefined behavior**.

---

## 🔁 Why `/` is used and NOT `%`

During several sessions, we discussed this exact question:

> ❓ Can we count digits using modulo instead of division?

### Correct approach

```c
num = num / base_len;
count++;
```

### Why division works

* Each division by `base_len` **removes one digit**
* Counting divisions = counting digits

### Why modulo does NOT work

```c
num = num % base_len; // ❌ wrong
```

* `%` only extracts the **last digit**
* It does NOT reduce the number
* Leads to infinite loops or wrong counts

### Rule to remember

> `/` removes a digit — `%` extracts a digit

---

## 🔢 count_digit_in_base — Why it exists

### Purpose

`count_digit_in_base` answers **two critical questions**:

1. **How much memory do we need?**
2. **Where do we start writing digits?**

### Example

```c
nbr = 42
base = "01"   // base 2
```

Binary representation:

```
101010
```

Digit counting process:

| Step | num | num / 2 | count |
| ---- | --- | ------- | ----- |
| 1    | 42  | 21      | 1     |
| 2    | 21  | 10      | 2     |
| 3    | 10  | 5       | 3     |
| 4    | 5   | 2       | 4     |
| 5    | 2   | 1       | 5     |
| 6    | 1   | 0       | 6     |

Result: **6 digits**

---

## ✍️ How digit count helps writing RIGHT → LEFT

Because we know the total length, we can do:

```c
i = total_len - 1;
```

Then:

```c
result[i] = base[num % base_len];
num = num / base_len;
i--;
```

This allows us to:

* Extract digits from right to left
* Write safely inside allocated memory

> Counting digits is not only about `malloc` — it also enables correct indexing.

---

## 🔁 ft_itoa_base — From int to string

### Steps

1. Handle `nbr == 0`
2. Count digits
3. Allocate exact memory
4. Handle negative sign
5. Fill digits from right to left

### Important syntax fix caught

```c
result = (char *)malloc(sizeof(char) * (total_len + 1));
```

⚠️ Missing semicolon here **breaks compilation**.

---

## 🧠 Final Mental Model

* `ft_atoi_base` → **parse**
* `count_digit_in_base` → **measure**
* `ft_itoa_base` → **build**

Each function has **one job**.

---

## ✅ Peer Evaluation Checklist

* [x] Bases fully validated
* [x] No forbidden characters in output
* [x] One optional `-`, no `+`
* [x] Memory allocated exactly
* [x] Digits written safely
* [x] No forbidden functions used

---

## 🧩 Key Takeaway

> Base conversion is not about clever tricks — it is about **discipline**:
> validating input, controlling memory, and respecting data flow.

This exercise tests whether you truly understand **representation vs value**.

---

## 🧩 ASCII Diagrams — Data Flow & Memory Flow

### 1️⃣ Global Flow (Conceptual)

```
   nbr (char *)
        │
        ▼
 ┌──────────────┐
 │ ft_atoi_base │  ← parse characters, apply base_from
 └──────────────┘
        │
        ▼
     int value
        │
        ▼
 ┌────────────────┐
 │ count_digit... │  ← how many chars needed in base_to
 └────────────────┘
        │
        ▼
 ┌──────────────┐
 │ ft_itoa_base │  ← build string in base_to
 └──────────────┘
        │
        ▼
   result (char *)
```

---

### 2️⃣ Digit Counting Diagram (Why division works)

Example:

```
value = 42
base_len = 2
```

```
42 / 2 = 21   (count = 1)
21 / 2 = 10   (count = 2)
10 / 2 = 5    (count = 3)
 5 / 2 = 2    (count = 4)
 2 / 2 = 1    (count = 5)
 1 / 2 = 0    (count = 6)  ← stop
```

```
42 (decimal) = 101010 (binary)
               ^^^^^^
               6 digits
```

Each division removes **one digit** in that base.

---

### 3️⃣ Memory Layout During ft_itoa_base

For `42` in base `"01"`:

```
Indexes:  0   1   2   3   4   5   6
          ┌───┬───┬───┬───┬───┬───┬───┐
result →  │ ? │ ? │ ? │ ? │ ? │ ? │ �│
          └───┴───┴───┴───┴───┴───┴───┘
                      ↑
                start writing here
                i = total_len - 1
```

---

### 4️⃣ Right-to-Left Writing (Step-by-Step)

```
num = 42
base_len = 2
```

| Step | num | num % 2 | char | index |
| ---- | --- | ------- | ---- | ----- |
| 1    | 42  | 0       | '0'  | 5     |
| 2    | 21  | 1       | '1'  | 4     |
| 3    | 10  | 0       | '0'  | 3     |
| 4    | 5   | 1       | '1'  | 2     |
| 5    | 2   | 0       | '0'  | 1     |
| 6    | 1   | 1       | '1'  | 0     |

Final string:

```
101010
```

---

### 5️⃣ Why `%` Cannot Be Used for Counting

```
num = 42
42 % 2 = 0
 0 % 2 = 0
 0 % 2 = 0  ← infinite / useless
```

```
%  → extract digit
/  → remove digit
```

---

## 🧠 Diagram Summary

```
Counting digits → allocation → indexing → safe conversion
```

> Without counting first, you don't know **where to write** or **how much memory exists**.

