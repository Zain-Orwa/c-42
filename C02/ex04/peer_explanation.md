# 🧩 `ft_str_is_lowercase` — Peer Explanation (ex04)

> **Goal:** Return `1` if the given string contains only lowercase letters (`a–z`), otherwise return `0`.
> If the string is empty, return `1`.

---

## 📜 Code Reference

```c
int	ft_str_is_lowercase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 'a' && str[i] <= 'z'))
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

Start reading the string from its first character.

---

### 2️⃣ Loop until the null terminator

```c
while (str[i] != '\0')
```

Each character will be examined until the end of the string.

---

### 3️⃣ Check if each character is lowercase

```c
if (!(str[i] >= 'a' && str[i] <= 'z'))
	return (0);
```

* The ASCII values for lowercase letters are from **97 (`'a'`) to 122 (`'z'`)**.
* The `!` negation means: if the character is **not** between `'a'` and `'z'`, return `0`.

This causes **early exit** as soon as one invalid character is found.

---

### 4️⃣ If the loop ends → all characters valid ✅

If all characters pass the test, return `1`.

---

### 5️⃣ Empty string case

If `str[0] == '\0'`, the loop never runs, and the function returns `1` —
this matches the 42 rule: *“It should return 1 if the string is empty.”*

---

## 🧠 Example Trace

| Input        | Explanation                 | Output |
| ------------ | --------------------------- | ------ |
| `"abcdefg"`  | All lowercase letters       | `1`    |
| `" abcdefg"` | Starts with space → invalid | `0`    |
| `"abcdefg1"` | Ends with a digit → invalid | `0`    |
| `""`         | Empty → valid by rule       | `1`    |

---

### 🧩 Test Example

```c
#include <stdio.h>

int	main(void)
{
	char *str1 = "abcdefg";
	char *str2 = " abcdefg";
	char *str3 = "abcdefg1";
	char *str4 = "";

	printf("%s is_lower? %d\n", str1, ft_str_is_lowercase(str1));
	printf("%s is_lower? %d\n", str2, ft_str_is_lowercase(str2));
	printf("%s is_lower? %d\n", str3, ft_str_is_lowercase(str3));
	printf("%s is_lower? %d\n", str4, ft_str_is_lowercase(str4));

	return (0);
}
```

**Output:**

```
abcdefg is_lower? 1
 abcdefg is_lower? 0
abcdefg1 is_lower? 0
 is_lower? 1
```

---

## 💬 Q&A Inside Context

**Q: Why check `'a' <= str[i] <= 'z'` instead of using `<ctype.h>` functions like `islower()`?**
Because the project forbids using standard library helpers — we must work directly with ASCII values.

---

**Q: Why return early with `return (0)`?**
It’s efficient and simple — once one character is invalid, no need to check the rest.

---

**Q: Why return 1 for an empty string?**
Because, by 42’s rule, an empty string “contains only lowercase letters” (since there are none that violate the rule).

---

**Q: What happens with uppercase letters like `'A'`?**
They fail the lowercase check (`'A'` < `'a'`), so the function returns `0`.

---

## ✅ Summary

| Concept           | Description                                    |
| ----------------- | ---------------------------------------------- |
| Input             | Pointer to `char` (string)                     |
| Return            | `1` = all lowercase, `0` = any other character |
| ASCII range       | `'a'` → `'z'` (97–122)                         |
| Empty string      | Returns `1`                                    |
| Allowed functions | None                                           |
| Time complexity   | O(n) — checks each character once              |

---

### 🧩 Edge Cases

| Input          | Output | Reason                       |
| -------------- | ------ | ---------------------------- |
| `"lowercase"`  | `1`    | All lowercase                |
| `"LOWERCASE"`  | `0`    | Uppercase not allowed        |
| `"lower Case"` | `0`    | Space and uppercase break it |
| `"123abc"`     | `0`    | Digits not allowed           |
| `""`           | `1`    | Empty string valid           |

---

> 🏁 **Commit suggestion:**
>
> ```
> Added ft_str_is_lowercase with detailed explanation, examples, and ASCII logic.
> Includes test cases and reasoning for empty string behavior.
> ```

---


