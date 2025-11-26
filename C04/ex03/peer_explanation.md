````markdown
# Exercise 03 — `ft_atoi`

> **Goal:** Re-implement the standard `atoi()`  
> Convert the *initial* part of a string to an `int`, following the 42 subject rules.

---

## 🧾 Exercise Summary

| Item                  | Details                          |
|-----------------------|----------------------------------|
| Exercise              | `ex03`                          |
| Function name         | `ft_atoi`                       |
| Prototype             | `int ft_atoi(char *str);`       |
| Allowed functions     | None                            |
| File to turn in       | `ft_atoi.c`                     |

---

## 🔍 What `ft_atoi` Must Do (According to the Subject)

Given a `char *str`, we must:

1. **Skip leading whitespace**  
   - Any number of spaces and ASCII whitespace (like `\t`, `\n`, etc., `9–13`).

2. **Handle an arbitrary number of `+` and `-` signs**  
   - Count how many `-` signs we see.
   - If the number of `-` signs is **odd** → result is **negative**.  
   - If it is **even** → result is **positive**.

3. **Convert the following digits (base 10) into an `int`**  
   - Read digits `0–9` one by one.  
   - Stop at the first non-digit (letter, symbol, `\0`, etc.).

4. **Return the integer built so far**  
   - Ignore everything after the digit sequence.  
   - Overflow/underflow: **undefined** (you don’t need to handle it).

Example from the subject:

- Input: `" ---+--+1234ab567"`  
- Output: `-1234`

Reason:
- After whitespace, signs are: `---+--+` → there are **5** `-` → odd → negative.  
- Digits: `1234` → result is `1234` → apply sign → `-1234`.

---

## 🧠 Core Logic of Any `ft_atoi` Implementation

No matter which of your 3 versions we use, the **algorithm** is always:

1. **Initialize**
   ```c
   result = 0;
   sign or minus_count = something;
````

2. **Skip whitespace**

   ```c
   while (current_char is space or ASCII 9–13)
       move forward;
   ```

3. **Process signs**

   ```c
   while (current_char is '+' or '-')
   {
       if (current_char == '-')
           flip or count negativity;
       move forward;
   }
   ```

4. **Convert digits**

   ```c
   while (current_char is between '0' and '9')
   {
       result = result * 10 + (current_char - '0');
       move forward;
   }
   ```

5. **Apply final sign**

   ```c
   if (minus_count is odd) or (sign == -1)
       result = -result;

   return result;
   ```

---

## 🧩 Version 1 — With Helper Functions and Indexes

### Code (simplified formatting)

```c
int is_space(char *space){
    return (*space == ' ');
}

int num_posi_sign(char *posi){
    return (*posi == '+');
}

int num_nega_sign(char *minu){
    return (*minu == '-');
}

int is_num(char *num){
    return (*num >= '0' && *num <= '9');
}

int is_alph(char *alph){
    return ((*alph >= 'A' && *alph <= 'Z') || (*alph >= 'a' && *alph <= 'z'));
}

int ft_atoi(char *str){
    int i;
    int result;
    int minus_sign;

    i = 0;
    while (str[i] != '\0' && is_space(&str[i]))
        i++;

    minus_sign = 0;
    while (str[i] != '\0' && (num_posi_sign(&str[i]) || num_nega_sign(&str[i]))){
        if (num_nega_sign(&str[i]))
            minus_sign++;
        i++;
    }

    result = 0;
    while (str[i] != '\0' && is_num(&str[i])){
        result = result * 10 + (str[i] - '0');
        i++;
    }

    if (minus_sign % 2 != 0)
        result *= -1;

    return (result);
}
```

### How It Works

1. **Whitespace skipping**

   ```c
   while (str[i] != '\0' && is_space(&str[i]))
       i++;
   ```

   * Uses `is_space(&str[i])` → checks only `' '`.
   * **Important**: This version only treats `' '` as whitespace, not `\t`, `\n`, etc., so it’s slightly weaker than the subject’s full whitespace definition.

2. **Sign handling**

   ```c
   minus_sign = 0;
   while (str[i] != '\0' && (num_posi_sign(&str[i]) || num_nega_sign(&str[i]))){
       if (num_nega_sign(&str[i]))
           minus_sign++;
       i++;
   }
   ```

   * Accepts **any number** of `+` and `-`.
   * Every time we see `'-'` → increment `minus_sign`.
   * At the end:

     ```c
     if (minus_sign % 2 != 0)
         result *= -1;
     ```

     If `minus_sign` is odd → negative; else → positive.

3. **Digit conversion**

   ```c
   result = 0;
   while (str[i] != '\0' && is_num(&str[i])){
       result = result * 10 + (str[i] - '0');
       i++;
   }
   ```

   * `result * 10` shifts the number one decimal place.
   * `(str[i] - '0')` converts a digit char to its integer value.

4. **Extras**

   * `is_alph` is defined but **never used** → dead code.
   * Uses helpers for readability, but they take `char *` instead of `char`, so we must always call them with `&str[i]`.

### Pros / Cons

* ✅ Readable, modular (helpers describing intent).
* 🔶 Does **not** handle all whitespace according to the subject.
* 🔶 Slightly over-engineered for this small function (many small helpers, unused `is_alph`).

---

## 🧩 Version 2 — Classic Index Version (Sign as `+1/-1`)

```c
int ft_atoi(char *str){
    int i;
    int sign;
    int result;

    i = 0;
    sign = 1;
    result = 0;

    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;

    while (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return (result * sign);
}
```

### How It Works

1. **Whitespace**

   ```c
   while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
       i++;
   ```

   * Handles:

     * `' '` (space)
     * `\t` (9), `\n` (10), `\v` (11), `\f` (12), `\r` (13)

   ✅ This matches the subject’s “arbitrary amount of white space (isspace)” rule.

2. **Sign**

   ```c
   sign = 1;
   while (str[i] == '+' || str[i] == '-')
   {
       if (str[i] == '-')
           sign *= -1;
       i++;
   }
   ```

   * Starts with `sign = 1` (positive).
   * Each `-` multiplies `sign` by `-1`.
   * If we see `---+--+`:

     * `-` → sign = -1
     * `-` → sign = +1
     * `-` → sign = -1
     * `+` → sign unchanged
     * `-` → sign = +1
     * `-` → sign = -1
     * `+` → unchanged → final `sign = -1`.

   This is logically equivalent to “odd number of `-` → negative”.

3. **Digits**

   Same logic as before:

   ```c
   while (str[i] >= '0' && str[i] <= '9')
   {
       result = result * 10 + (str[i] - '0');
       i++;
   }
   ```

4. **Final result**

   ```c
   return (result * sign);
   ```

   Simple and clear.

### Pros / Cons

* ✅ Matches subject whitespace rules.
* ✅ Very readable and classic style.
* ✅ No unused helpers; everything is local to this function.
* Overall, this is a **very good 42-style solution**.

---

## 🧩 Version 3 — Pointer Version (`char *` Walk)

```c
int ft_atoi(char *str){
    int result;
    int minus_count;

    result = 0;
    minus_count = 0;

    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;

    while (*str == '+' || *str == '-')
    {
        if (*str == '-')
            minus_count++;
        str++;
    }

    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }

    return ((minus_count % 2) ? -result : result);
}
```

### How It Works

1. **Pointer instead of index**

   * We never use `i`.
   * `str` itself is moved forward step by step:

     * `str++` moves to the next character.
   * `*str` is the current character.

2. **Whitespace**

   ```c
   while (*str == ' ' || (*str >= 9 && *str <= 13))
       str++;
   ```

   Same as version 2, but pointer style.

3. **Signs**

   ```c
   while (*str == '+' || *str == '-')
   {
       if (*str == '-')
           minus_count++;
       str++;
   }
   ```

   * We count how many `-` appear.
   * At the end:

     ```c
     return ((minus_count % 2) ? -result : result);
     ```

     If `minus_count` is odd → negative.
     If even → positive.

4. **Digits**

   ```c
   while (*str >= '0' && *str <= '9')
   {
       result = result * 10 + (*str - '0');
       str++;
   }
   ```

   Same logic, but pointer version.

### Pros / Cons

* ✅ Clean pointer style — good to train pointer thinking.
* ✅ Matches subject whitespace & sign rules.
* ✅ No indexes, less variables.
* 🔶 Beginners may find pointer arithmetic less intuitive at first.

---

## ⚖️ Comparison of the Three Versions

| Version | Index / Pointer  | Whitespace Handling  | Sign Handling             | Pros                                 | Cons                                  |
| ------- | ---------------- | -------------------- | ------------------------- | ------------------------------------ | ------------------------------------- |
| 1       | Index (`i`)      | Only `' '` (space)   | `minus_sign % 2`          | Many helpers, explicit names         | Not full whitespace; unused `is_alph` |
| 2       | Index (`i`)      | `' '` and ASCII 9–13 | `sign` multiplied by `-1` | Very clear, compact, subject-correct | Slightly more variables               |
| 3       | Pointer (`*str`) | `' '` and ASCII 9–13 | `minus_count % 2`         | Pointer practice, minimal variables  | Less obvious to absolute beginners    |

**Best choice for the repo (pedagogically):**

* Keep **all three** as examples in your notes if you want,
* But for the *main* `ft_atoi.c`, version **2 or 3** is more faithful to the subject.
* Version **2** = best compromise: readable + subject-correct.
* Version **3** = best to show pointer style.

---

## 🧪 Example Input / Output

Using version 2 or 3:

```c
ft_atoi(" ---+--+1234ab567")  // -1234
ft_atoi("   42")             // 42
ft_atoi("   +++10")          // 10
ft_atoi("   --10")           // 10   (two '-')
ft_atoi("   -+-10")          // -10  (odd number of '-')
ft_atoi("abc123")            // 0    (no digits at beginning)
ft_atoi("   \t\n  7abc")     // 7
```

---

## 🧾 Peer Evaluation Q&A (Deep Dive)

### Q1: Why do we multiply `result` by 10 each time?

Because we are building a **base-10** number from left to right.

Example: `"123"`

1. `result = 0`
2. Read `'1'`: `result = 0 * 10 + 1 = 1`
3. Read `'2'`: `result = 1 * 10 + 2 = 12`
4. Read `'3'`: `result = 12 * 10 + 3 = 123`

Multiplying by 10 shifts the previous digits “one place to the left”.

---

### Q2: Why do we use `str[i] - '0'` (or `*str - '0'`)?

Characters `'0'` to `'9'` are consecutive in ASCII:

* `'0'` → 48
* `'1'` → 49
* …
* `'9'` → 57

So:

```c
'3' - '0' = 51 - 48 = 3
```

This converts the digit character to its numeric value.

---

### Q3: Why do we allow **multiple** `+` and `-` signs?

Because the subject explicitly says:

> “The string can be followed by an arbitrary amount of `+` and `-` signs…”

So all of these must be valid:

* `"---+--+1234ab567"`
* `"++10"`
* `"--+--42"`

The final sign is determined by the **parity** (even/odd) of `-` signs:

* Even number of `-` → positive
* Odd number of `-` → negative

In code:

* Version 1 & 3: `minus_count % 2`
* Version 2: `sign *= -1` every time we see `'-'`.

---

### Q4: Why does version 2 and 3 check `(str[i] >= 9 && str[i] <= 13)`?

ASCII control characters:

* `9`  → `\t` (tab)
* `10` → `\n` (newline)
* `11` → `\v` (vertical tab)
* `12` → `\f` (form feed)
* `13` → `\r` (carriage return)

Together with `' '` (space, 32), these are the usual **whitespace characters** that `isspace()` would detect.

So:

```c
while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
    i++;
```

is basically: “Skip all whitespace at the beginning”.

---

### Q5: What happens if the string starts with letters, like `"abc123"`?

Look at the algorithm:

1. Skip whitespace → none.
2. Check signs: the first char is `'a'` → not `'+'` nor `'-'` → we don’t enter the sign loop.
3. Check digits: `'a'` is not between `'0'` and `'9'` → we never enter the digit loop.

So `result` stays `0` and we return `0`.

This matches the behavior of the real `atoi`.

---

### Q6: Why don’t we check for `'\0'` in the digit loop in versions 2 and 3?

Example from version 3:

```c
while (*str >= '0' && *str <= '9')
{
    result = result * 10 + (*str - '0');
    str++;
}
```

If `*str` is `'\0'` (0):

* `0 >= '0'` (48)? → false
* So the loop stops automatically.

We don’t **need** an explicit `*str != '\0'` condition because the digit range already implies that.

---

### Q7: What about overflow / underflow?

The subject says:

> “You should not take care of overflow or underflow. Result can be undefined in that case.”

So if the number is too large/small to fit into `int`, we don’t care.
This is why we don’t check `INT_MAX` or `INT_MIN`.

---

### Q8: Why is version 3’s return line written like this?

```c
return ((minus_count % 2) ? -result : result);
```

This is the **ternary operator**:

* Condition: `minus_count % 2`

  * If odd → non-zero → true.
  * If even → zero → false.
* If true → `-result`
* If false → `result`

So it literally means:

```c
if (minus_count % 2 != 0)
    return -result;
else
    return result;
```

Just more compact.

---

### Q9: Why is version 1 slightly weaker than 2 and 3 for the subject?

Two main reasons:

1. **Whitespace**

   * Version 1 only uses `is_space` → checks `' '` only.
   * The subject expects **all** common whitespace characters.

2. **Dead code**

   * `is_alph` is never used.
   * Not a logical error, but not clean.

For a strict 42 style, you generally want the behavior to match the subject as close as possible → version 2 or 3 wins.

---

### Q10: Which version should I present in a defense if asked to explain in detail?

Best strategy:

1. **Show version 2 as your main implementation**

   * It is easy to explain: indices, `sign`, clear loops.
2. **Mention version 3**

   * As a pointer-based variant that does the same logic.
3. **Explain the idea of version 1**

   * Show that you understand helper functions, but also that you noticed the whitespace limitation and unused `is_alph`.

This demonstrates:

* You understand the **spec**
* You can reason about **different implementations**
* You can spot **limitations** and **clean code** issues.

---

```

