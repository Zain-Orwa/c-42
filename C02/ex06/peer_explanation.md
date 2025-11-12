# 🧩 Exercise 06 — `ft_str_is_printable`

> **Goal:**
> Create a function that returns `1` if a string contains **only printable ASCII characters** (`32–126`),
> and `0` if it contains **any non-printable character**.
>
> If the string is empty, it must return `1`.

---

## 📜 Code Reference

```c
int	ft_str_is_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 32 && str[i] <= 126))
			return (0);
		i++;
	}
	return (1);
}
```

---

## ⚙️ Step-by-Step Explanation

### 1️⃣ Initialization

```c
i = 0;
```

Start checking from the first character of the string.

---

### 2️⃣ Loop Through All Characters

```c
while (str[i] != '\0')
```

Iterates through every character until the null terminator (`'\0'`).

---

### 3️⃣ Check Printability

```c
if (!(str[i] >= 32 && str[i] <= 126))
	return (0);
```

* Printable ASCII range:

  * **32** = `' '` (space)
  * **126** = `'~'`
* Anything below 32 (`\t`, `\n`, etc.) or above 126 is non-printable.

If any character is outside this range → immediately return `0`.

---

### 4️⃣ If All Characters Pass ✅

When the loop ends normally, return `1`.

---

### 5️⃣ Empty String Case

If `str[0] == '\0'`, the loop never runs and the function returns `1`,
which follows the 42 rule: empty strings are considered valid.

---

## 🧠 Example Trace

| Input       | Explanation                         | Output |
| ----------- | ----------------------------------- | ------ |
| `"    "`    | All spaces (ASCII 32) → printable   | 1      |
| `"A!1$"`    | All visible ASCII chars → printable | 1      |
| `"Hello\n"` | `\n` = ASCII 10 → non-printable     | 0      |
| `"\tHi"`    | `\t` = ASCII 9 → non-printable      | 0      |
| `""`        | Empty string → valid by definition  | 1      |

---

## 🧩 Test Example

```c
#include <stdio.h>

int	main(void)
{
	char *str1 = "    ";
	char *str2 = "A!1$";
	char *str3 = "Hello\n";
	char *str4 = "";
	char *str5 = "\tHi";

	printf("%-12s => printable? %d\n", "\"    \"",     ft_str_is_printable(str1));
	printf("%-12s => printable? %d\n", "\"A!1$\"",    ft_str_is_printable(str2));
	printf("%-12s => printable? %d\n", "\"Hello\\n\"", ft_str_is_printable(str3));
	printf("%-12s => printable? %d\n", "\"\"",         ft_str_is_printable(str4));
	printf("%-12s => printable? %d\n", "\"\\tHi\"",    ft_str_is_printable(str5));

	return (0);
}
```

---

### 🖥️ Output

```
"    "       => printable? 1
"A!1$"       => printable? 1
"Hello\n"    => printable? 0
""           => printable? 1
"\tHi"       => printable? 0
```

---

## 💬 Q & A — Common Questions

**Q:** What is a printable character in C?
**A:** Any character you can see on the screen (space, letters, digits, symbols), not control chars like `\n` or `\t`.

---

**Q:** Why does ASCII 32 count as printable?
**A:** Because space is a visible character on screen.

---

**Q:** Why use `<= 126`?
**A:** 126 (`'~'`) is the last printable ASCII symbol before `DEL` (127).

---

**Q:** Why return `1` for an empty string?
**A:** Because it contains no invalid characters → it is valid by definition.

---

**Q:** Can we use `isprint()` from `<ctype.h>`?
**A:** No. 42 forbids standard library helpers — we must compare ASCII values directly.

---

## ✅ Summary

| Concept             | Description                                       |
| ------------------- | ------------------------------------------------- |
| **Input**           | `char *` (string pointer)                         |
| **Output**          | `1` = all printable, `0` = contains invalid chars |
| **ASCII Range**     | `32 → 126`                                        |
| **Empty String**    | Returns `1`                                       |
| **Allowed Funcs**   | None                                              |
| **Time Complexity** | O(n) — each character checked once                |

---

## 🧩 Edge Cases

| Input      | Output | Reason                            |
| ---------- | ------ | --------------------------------- |
| `"Hello!"` | 1      | All visible characters valid      |
| `"Hi\n"`   | 0      | Newline is non-printable          |
| `" "`      | 1      | Space is printable                |
| `"~"`      | 1      | Highest printable character (126) |
| `""`       | 1      | Empty string valid                |

---


