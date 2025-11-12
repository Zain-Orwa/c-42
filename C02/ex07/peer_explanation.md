# 🧩 Exercise 07 — `ft_strupcase`

> **Goal:**
> Write a function that converts all lowercase letters in a string to uppercase.
>
> Other characters (digits, symbols, spaces, punctuation) remain unchanged.
>
> The function returns the **same string pointer** after modification.

---

## 📜 Code Reference

```c
char	*ft_strupcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
	return (str);
}
```

---

## ⚙️ Step-by-Step Explanation

### 1️⃣ Loop through the string

```c
while (str[i] != '\0')
```

Runs until the null terminator (`'\0'`) is reached — checking every character.

---

### 2️⃣ Detect lowercase letters

```c
if (str[i] >= 'a' && str[i] <= 'z')
```

Lowercase letters in ASCII range from **97 (`'a'`) to 122 (`'z'`)**.
Only these characters are transformed.

---

### 3️⃣ Convert to uppercase

```c
str[i] -= 32;
```

Subtracting 32 from a lowercase letter’s ASCII value turns it uppercase:

| Example | ASCII Before | ASCII After | Result |
| ------- | ------------ | ----------- | ------ |
| `'a'`   | 97           | 65          | `'A'`  |
| `'z'`   | 122          | 90          | `'Z'`  |

---

### 4️⃣ Leave others unchanged

Characters like digits, punctuation, or already-uppercase letters don’t match the condition,
so they are left as-is.

---

### 5️⃣ Return the original pointer

```c
return (str);
```

The same memory address is returned — the modification happens **in place**.

---

## 🧠 Example Trace

| Input String      | Explanation                        | Output          |
| ----------------- | ---------------------------------- | --------------- |
| `"hello world!"`  | All lowercase → converted          | `HELLO WORLD!`  |
| `"Already UPPER"` | Uppercase remains unchanged        | `ALREADY UPPER` |
| `"42school"`      | Letters uppercased, digits ignored | `42SCHOOL`      |
| `""`              | Empty string → nothing to change   | `""`            |

---

## 🧩 Test Example

```c
#include <stdio.h>

int	main(void)
{
	char str1[] = "hello world!";
	char str2[] = "Already UPPER";
	char str3[] = "42school";
	char str4[] = "";

	printf("%-18s => %s\n", "\"hello world!\"", ft_strupcase(str1));
	printf("%-18s => %s\n", "\"Already UPPER\"", ft_strupcase(str2));
	printf("%-18s => %s\n", "\"42school\"", ft_strupcase(str3));
	printf("%-18s => %s\n", "\"\"", ft_strupcase(str4));

	return (0);
}
```

---

### 🖥️ Output

```
"hello world!"     => HELLO WORLD!
"Already UPPER"    => ALREADY UPPER
"42school"         => 42SCHOOL
""                 => 
```

---

## 💬 Q & A — Common Questions

**Q:** Why subtract 32 instead of using a library function?
**A:** Because in ASCII, lowercase and uppercase letters are exactly 32 positions apart.
No external functions are allowed in 42 exercises.

---

**Q:** Why return the same pointer instead of a new one?
**A:** 42 requires in-place modification — `str` is updated directly in memory, saving space and time.

---

**Q:** What happens to numbers and symbols?
**A:** They stay unchanged because they’re outside the `'a'` – `'z'` range.

---

**Q:** What if the string is empty?
**A:** The loop never runs; the function simply returns the same empty string pointer.

---

## ✅ Summary

| Concept               | Description                                     |
| --------------------- | ----------------------------------------------- |
| **Purpose**           | Convert lowercase letters to uppercase          |
| **Input**             | `char *str`                                     |
| **Output**            | Same string pointer after in-place modification |
| **Logic**             | Subtract 32 from lowercase ASCII values         |
| **Other characters**  | Unchanged                                       |
| **Empty string**      | Returns same pointer                            |
| **Allowed functions** | None                                            |
| **Complexity**        | O(n)                                            |

---

## 🧩 Edge Cases

| Input      | Output     | Explanation                  |
| ---------- | ---------- | ---------------------------- |
| `"abcXYZ"` | `"ABCXYZ"` | Mix of lower & upper letters |
| `"123"`    | `"123"`    | Digits remain same           |
| `"hello!"` | `"HELLO!"` | Symbols untouched            |
| `""`       | `""`       | Empty string unchanged       |

---

