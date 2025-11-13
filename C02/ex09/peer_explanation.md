# 🧩 Exercise 09 — `ft_strcapitalize`

> **Goal:**
> Transform a string so that **each word starts with an uppercase letter**,
> and all other characters inside a word become lowercase.
>
> A *word* = any sequence of **letters or digits**.
> Words are separated by any non-alphanumeric character.

---

## 📜 Code Reference (Your Implementation)

```c
int is_lower(char c){
    return (c >= 'a' && c <= 'z');
}

int is_upper(char c){
    return (c >= 'A' && c <= 'Z');
}

int is_number(char c){
    return (c >= '0' && c <= '9');
}

int is_alphanumeric(char c){
    return (is_lower(c) || is_upper(c) || is_number(c));
}

char  *ft_strcapitalization(char *str){
    int  i;

    i = 0;
    while (str[i] != '\0'){

        int prev_is_alnum = ((i > 0) && is_alphanumeric(str[i - 1]));

        if (is_lower(str[i]) && !prev_is_alnum)
            str[i] -= 32;

        if (is_upper(str[i]) && prev_is_alnum)
            str[i] += 32;

        i++;
    }

    return (str);
}
```

---

# ⚙️ How the Function Works — Step by Step

---

## 1️⃣ Understanding Words

A **word** begins when:

* A character is alphabetic (`a–z` or `A–Z`) **OR** numeric (`0–9`)
* AND the **previous** character is **not** alphanumeric.

Examples:

```
"hello"                → one word
"42mots"               → one word
"hello-world"          → two words
"cinq+et+un"           → three words
```

Your helper `is_alphanumeric()` expresses exactly this logic.

---

## 2️⃣ Loop Over Each Character

```c
while (str[i] != '\0')
```

We process one character at a time until the null terminator.

---

## 3️⃣ Determine Whether the Previous Character Was Alphanumeric

```c
int prev_is_alnum = ((i > 0) && is_alphanumeric(str[i - 1]));
```

### Why this line is important:

* When `i == 0`, we do **NOT** check `str[-1]` → this avoids undefined behavior.
* Thanks to short-circuit logic, `is_alphanumeric(str[i - 1])` runs **only if `i > 0` is true**.

### Meaning:

* If `i == 0` → `prev_is_alnum` becomes **0**
  → first char is always treated as “start of a word”
* If `i > 0` → we check the previous character correctly.

---

## 4️⃣ Capitalize the First Letter of Each Word

```c
if (is_lower(str[i]) && !prev_is_alnum)
    str[i] -= 32;
```

Logic:

* If current character is lowercase
* AND previous character is **not alphanumeric**
  → This is the **start of a new word**

So we uppercase it by subtracting **32** (ASCII difference between lower/upper).

Example:

```
"salut" → "Salut"
"42mots" → stays "42mots"
"hello-world" → "Hello-World"
```

---

## 5️⃣ Lowercase Uppercase Letters Inside a Word

```c
if (is_upper(str[i]) && prev_is_alnum)
    str[i] += 32;
```

Logic:

* If current character is uppercase
* AND previous character **is** alphanumeric
  → We are **inside a word**, not at the beginning.

So uppercase must be lowered (`HELLo` → `Hello`).

Examples:

```
"sALUt"     → "Salut"
"cHaTs"     → "Chats"
"42SCHOOL"  → "42school"
```

---

## 6️⃣ Return the Modified String

```c
return (str);
```

The function works **in-place**, modifying the original memory.

---

# 🧠 Example Trace

Input:

```
"salut, comment tu vas ? 42mots quarante-deux; cinquante+et+un"
```

Output:

```
"Salut, Comment Tu Vas ? 42mots Quarante-Deux; Cinquante+Et+Un"
```

Reason:

* Every new word → first letter uppercase
* All inside letters → lowercase
* Numbers (like 42) do not start a new word
  → “42mots” remains lowercase after the digits

---

# 🧪 Test Program

```c
#include <stdio.h>

int main(){
    char str[] =
        "salut, comment tu vas ? 42mots quarante-deux; cinquante+et+un";

    printf("Before: %s\n", str);
    printf("After : %s\n", ft_strcapitalization(str));

    return (0);
}
```

---

# 🖥️ Output

```
Before: salut, comment tu vas ? 42mots quarante-deux; cinquante+et+un
After : Salut, Comment Tu Vas ? 42mots Quarante-Deux; Cinquante+Et+Un
```

---

# 💬 Q&A Inside the Explanation

### **Q: Why is `prev_is_alnum` declared inside the loop?**

Because its value depends on `i`, and it must be recalculated for *every* character.

---

### **Q: Why check `i > 0`?**

To avoid accessing `str[-1]`, which is illegal.

---

### **Q: Why use `+= 32` and `-= 32`?**

Lowercase and uppercase letters differ by exactly **32** in ASCII.

---

### **Q: Why uppercase only lowercase letters at start of word?**

Because “start of a word” logic depends on the previous character being **non-alphanumeric**.

---

### **Q: Why lowercase uppercase letters inside words?**

Example:

```
"heLLo" → "Hello"
```

Only the first letter should be uppercase; the rest must be lowercase.

---

# ✅ Summary Table

| Feature           | Behavior                  |
| ----------------- | ------------------------- |
| Start of word     | Lowercase → uppercase     |
| Inside word       | Uppercase → lowercase     |
| Digits            | Count as alphanumeric     |
| Separators        | Any non-alphanumeric char |
| Empty string      | Returns empty string      |
| In-place          | Yes                       |
| Allowed functions | None                      |

---

# 🏁 Commit Suggestion

```
Added ft_strcapitalize (your version) with full explanation, 
helper functions, detailed word logic, and test program.
```

---

