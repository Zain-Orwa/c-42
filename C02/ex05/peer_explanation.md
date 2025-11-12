# 🧩 `ft_str_is_uppercase` — Peer Explanation (ex05)

> **Goal:** Return `1` if the string contains only uppercase alphabetical characters (`A–Z`), and `0` otherwise.
> If the string is empty, it must return `1`.

---

## 📜 Code Reference

```c
int	ft_str_is_uppercase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 'A' && str[i] <= 'Z'))
			return (0);
		i++;
	}
	return (1);
}
```

---

## ⚙️ Function Logic (Step by Step)

### 1️⃣ Initialize

```c
i = 0;
```

Start checking characters from the beginning of the string.

---

### 2️⃣ Loop through each character

```c
while (str[i] != '\0')
```

The loop runs until it reaches the null terminator (`'\0'`), meaning the end of the string.

---

### 3️⃣ Check if each character is uppercase

```c
if (!(str[i] >= 'A' && str[i] <= 'Z'))
	return (0);
```

* Uppercase letters in ASCII range from **65 (`'A'`) to 90 (`'Z'`)**.
* If any character falls outside that range, return `0` immediately.

This makes the function efficient — it stops as soon as it finds a non-uppercase character.

---

### 4️⃣ End of loop → all uppercase ✅

If the loop finishes with no invalid characters, return `1`.

---

### 5️⃣ Empty string case

If the string is empty (`str[0] == '\0'`), the loop never runs.
That means the function automatically returns `1` — which matches 42’s specification:

> “It should return 1 if `str` is empty.”

---

## 🧠 Example Trace

| Input        | Explanation              | Output |
| ------------ | ------------------------ | ------ |
| `"ABCDEFGG"` | All uppercase letters    | `1`    |
| `"abcdefg"`  | All lowercase → invalid  | `0`    |
| `"abcdefg1"` | Contains digit → invalid | `0`    |
| `""`         | Empty string → valid     | `1`    |

---

### 🧩 Test Example

```c
#include <stdio.h>

int	main(void)
{
	char *str1 = "ABCDEFGG";
	char *str2 = "abcdefg";
	char *str3 = "abcdefg1";
	char *str4 = "";

	printf("%s is_upper? %d\n", str1, ft_str_is_uppercase(str1));
	printf("%s is_upper? %d\n", str2, ft_str_is_uppercase(str2));
	printf("%s is_upper? %d\n", str3, ft_str_is_uppercase(str3));
	printf("%s is_upper? %d\n", str4, ft_str_is_uppercase(str4));

	return (0);
}
```

**Output:**

```
ABCDEFGG is_upper? 1
abcdefg is_upper? 0
abcdefg1 is_upper? 0
 is_upper? 1
```

---

## 💬 Q&A Inside Context

**Q: Why do we use `'A'` and `'Z'` instead of 65 and 90?**
Using character literals makes the code more readable and self-explanatory — both represent the same ASCII values.

---

**Q: Why return 0 immediately when a wrong character is found?**
Because there’s no reason to continue checking — the condition has already failed.

---

**Q: Why return 1 for an empty string?**
Because by definition, an empty string contains *no invalid characters*, so it’s considered “valid.”

---

**Q: Could we use `isupper()` from `<ctype.h>`?**
No — according to the 42 rules, you must not use library helper functions.
This exercise tests your understanding of ASCII ranges.

---

## ✅ Summary

| Concept           | Description                                  |
| ----------------- | -------------------------------------------- |
| Input             | `char *` (string pointer)                    |
| Output            | `int` — `1` for all uppercase, `0` otherwise |
| ASCII range       | `'A'` (65) → `'Z'` (90)                      |
| Empty string      | Returns `1`                                  |
| Allowed functions | None                                         |
| Time complexity   | O(n) — checks each character once            |

---

### 🧩 Edge Cases

| Input      | Output | Reason             |
| ---------- | ------ | ------------------ |
| `"HELLO"`  | `1`    | All uppercase      |
| `"Hello"`  | `0`    | Contains lowercase |
| `"HELLO1"` | `0`    | Contains digit     |
| `"HELLO!"` | `0`    | Special char       |
| `""`       | `1`    | Empty string       |

---

