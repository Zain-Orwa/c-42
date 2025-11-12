# 🧩 `ft_str_is_numeric` — Peer Explanation (ex03)

> **Goal:** Return `1` if the given string contains only digits (`0–9`), and `0` otherwise.
> If the string is empty, the function must return `1`.

---

## 📜 Code Reference

```c
int	ft_str_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
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

Start from the first character in the string.

---

### 2️⃣ Loop through all characters

```c
while (str[i] != '\0')
```

This continues until the end of the string (the null terminator `\0`).

---

### 3️⃣ Check if each character is a digit

```c
if (!(str[i] >= '0' && str[i] <= '9'))
	return (0);
```

* The **ASCII values** for digits `0–9` are **48–57**.
* This condition checks if the current character falls **outside** that range.
* If any non-digit is found (like `'A'`, `'-'`, or space), return `0` immediately.

---

### 4️⃣ End of loop → all digits ✅

If no invalid character was found, the function returns `1`.

---

### 5️⃣ Empty string case

If `str[0] == '\0'`, the loop never executes, and the function returns `1`.
That follows the 42 rule: *“It should return 1 if the string is empty.”*

---

## 🧠 Example Trace

| Input String | Checked Characters | Result |
| ------------ | ------------------ | ------ |
| `"1234"`     | All digits         | `1`    |
| `"A1R2"`     | `'A'` → invalid    | `0`    |
| `""`         | Empty → no check   | `1`    |

---

### 🧩 Test Example

```c
#include <stdio.h>

int	main(void)
{
	char *str1 = "1234";
	char *str2 = "A1R2";
	char *str3 = "";

	printf("%s is numeric? %d\n", str1, ft_str_is_numeric(str1));
	printf("%s is numeric? %d\n", str2, ft_str_is_numeric(str2));
	printf("%s is numeric? %d\n", str3, ft_str_is_numeric(str3));

	return (0);
}
```

**Output:**

```
1234 is numeric? 1
A1R2 is numeric? 0
 is numeric? 1
```

---

## 💬 Q&A Inside Context

**Q: Why use `'0'` and `'9'` instead of numbers `48` and `57`?**
Using character literals makes the code clearer. `'0'` is automatically converted to its ASCII code.

---

**Q: Why return early instead of using a flag variable?**
It’s cleaner and more efficient — once we know it’s not numeric, there’s no need to check the rest.

---

**Q: Why return `1` when empty?**
By definition in 42 projects, an empty string is considered *valid* for this type of test function (it doesn’t contain any invalid character).

---

**Q: Could we use `isdigit()`?**
No — the exercise forbids library functions (`<ctype.h>`). We must check ASCII ranges manually.

---

## ✅ Summary

| Concept           | Description               |
| ----------------- | ------------------------- |
| Return type       | `int` (1 or 0)            |
| Input             | `char *` (string pointer) |
| Loop              | Runs until `'\0'`         |
| Check             | ASCII range `'0'`–`'9'`   |
| Empty string      | Returns `1`               |
| Allowed functions | None                      |

---

### 🧩 Edge Cases

| Input    | Output | Reason                |
| -------- | ------ | --------------------- |
| `"42"`   | `1`    | All digits            |
| `"0042"` | `1`    | Leading zeros allowed |
| `"42a"`  | `0`    | Contains a letter     |
| `""`     | `1`    | Empty string          |
| `" 42"`  | `0`    | Space is not a digit  |

---

> 🏁 **Commit suggestion:**
>
> ```
> Added ft_str_is_numeric with explanation and ASCII logic reference.
> Includes edge cases, examples, and beginner Q&A.
> ```

---


