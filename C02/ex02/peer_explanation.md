# 🧩 `ft_str_is_alpha` — Peer Explanation (ex02)

> **Goal:** Return `1` if the string contains only letters (`A–Z` or `a–z`), otherwise return `0`.
> The function should also return `1` if the string is empty.

---

## 📜 Code Reference

```c
int	ft_str_is_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= 'a' && str[i] <= 'z')))
			return (0);
		i++;
	}
	return (1);
}
```

---

## ⚙️ Function Logic (Step by Step)

### 1️⃣ Initialize the counter

```c
i = 0;
```

Start scanning from the beginning of the string.

---

### 2️⃣ Loop through all characters

```c
while (str[i] != '\0')
```

This continues until we reach the *null terminator*, marking the end of the string.

---

### 3️⃣ Check each character

```c
if (!((str[i] >= 'A' && str[i] <= 'Z')
   || (str[i] >= 'a' && str[i] <= 'z')))
   return (0);
```

* The condition checks **if the current character is NOT alphabetic**.
* If it’s anything else (like a digit, space, punctuation), the function **immediately returns 0**.
* Using the **logical NOT (`!`)** is a neat way to avoid writing a long “if invalid” condition.

---

### 4️⃣ End of loop → all letters ✅

If the loop finishes without returning `0`, that means every character was alphabetic.

```c
return (1);
```

---

### 5️⃣ Empty string behavior

If the string is empty (`str[0] == '\0'`), the loop never executes —
so the function directly returns `1`.
This satisfies the 42 rule: *“It should return 1 if `str` is empty.”*

---

## 🧠 Example Trace

| Input String | Loop Steps               | Return |
| ------------ | ------------------------ | ------ |
| `"String"`   | All letters → no failure | `1`    |
| `" String"`  | Space `' '` fails check  | `0`    |
| `"1tring"`   | Digit `'1'` fails check  | `0`    |
| `""`         | Empty → skip loop        | `1`    |

---

### 🧩 Test Example (from your code)

```c
#include <stdio.h>

int	main(void)
{
	char *str1 = " String";
	char *str2 = "String";
	char *str3 = "1tring";

	printf("%s is alpha? %d\n", str1, ft_str_is_alpha(str1));
	printf("%s is alpha? %d\n", str2, ft_str_is_alpha(str2));
	printf("%s is alpha? %d\n", str3, ft_str_is_alpha(str3));
	return (0);
}
```

**Output:**

```
 String is alpha? 0
String is alpha? 1
1tring is alpha? 0
```

---

## 💬 Q&A Inside Context

**Q: Why do we compare `'A' <= str[i] <= 'Z'` and `'a' <= str[i] <= 'z'`?**
Because ASCII letters are grouped together — `'A'` through `'Z'` and `'a'` through `'z'` are consecutive integer values.

---

**Q: Why use `return (0)` immediately?**
It’s faster and cleaner — no need to finish the loop once you already know the string isn’t valid.

---

**Q: Why return 1 for an empty string?**
By definition in 42’s standard, an empty string *contains only alphabetical characters* (since there are none that violate the rule).

---

**Q: Why not use `<ctype.h>` functions like `isalpha()`?**
Because 42 forbids library functions here — you must manually check ASCII ranges.

---

## ✅ Summary

| Concept      | Description                                        |
| ------------ | -------------------------------------------------- |
| Return type  | `int` (1 or 0)                                     |
| Input        | Pointer to `char` string                           |
| Empty string | Returns 1                                          |
| Logic        | Check all chars are between `'A'-'Z'` or `'a'-'z'` |
| Early exit   | Returns 0 when any invalid char found              |

---

## 🧩 Edge Cases

| Input       | Expected | Reason                  |
| ----------- | -------- | ----------------------- |
| `"42"`      | `0`      | Digits not allowed      |
| `"hello"`   | `1`      | All lowercase           |
| `"HELLO"`   | `1`      | All uppercase           |
| `"Hello42"` | `0`      | Mixed letters + numbers |
| `""`        | `1`      | Empty string            |

---

> 🏁 **Commit suggestion:**
>
> ```
> Added ft_str_is_alpha with explanation and test examples.
> Includes edge cases and ASCII range logic.
> ```

---


