# 🔢 Exercise 00: `ft_strcmp`
---
## 🧠 Objective
Reproduce exactly the behavior of the standard C library function `strcmp` (see `man 3 strcmp`).

The function must:
- Compare two null-terminated strings lexicographically.
- Return:
  - **Negative value** if `s1` < `s2`
  - **Zero** if `s1` is identical to `s2`
  - **Positive value** Physiological if `s1` > `s2`
- The comparison is done using **unsigned char** values (important for characters > 127).
- No library functions allowed (not even `<string.h>`).

---
## 📘 Final Code (Norm-compliant + clean)
```c
int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
```

### Alternative version (more verbose, easier for beginners)
```c
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
```

Both versions are perfectly valid and pass the 42 tests.

---
## 🔍 What You’re Learning
| Concept                  | Description                                                                          |
|--------------------------|--------------------------------------------------------------------------------------|
| Pointer arithmetic       | Moving through strings character by character                                        |
| String termination       | The importance of `'\0'` (null terminator)                                           |
| Lexicographical order    | How strings are compared byte-by-byte like in a dictionary                           |
| Unsigned casting         | Why we cast to `unsigned char` before subtracting (correct behavior for ASCII > 127) |
| Short-circuit evaluation | How `while (*s1 && ...)` stops at the first difference or end of string              |

---
## 🧩 Line-by-Line Breakdown
| Line                                    | Explanation                                                                                                  |
|----------------------------------------|---------------------------------------------------------------------------------------------------------------|
| `while (*s1 && (*s1 == *s2))`          | Keep looping as long as both characters exist (`*s1 != '\0'`) AND they are equal                              |
| `s1++; s2++;`                          | Move both pointers forward to the next character                                                              |
| `return ((unsigned char)*s1 - (unsigned char)*s2);` | When loop exits: either one string ended or a difference was found → return the difference as int|

**Key point:** The subtraction works because:
- If `*s1 > *s2` → positive result
- If `*s1 < *s2` → negative result
- If both are `'\0'` → zero

Casting to `unsigned char` prevents issues with signed char (especially on some architectures where char is signed by default).

---
## 🧪 Expected Output (Test examples)
```c
ft_strcmp("abc", "abc")    → 0
ft_strcmp("abc", "abd")    → negative (usually -1)
ft_strcmp("abd", "abc")    → positive (usually 1)
ft_strcmp("abc", "ab")     → positive ('\0' vs 'c')
ft_strcmp("ab", "abc")     → negative
ft_strcmp("", "")          → 0
ft_strcmp("Hello", "Hello World") → negative
```

---
## 💡 How It Works – Step by Step
1. Start at the beginning of both strings.
2. While characters are equal AND we haven’t reached the end of the first string:
   - Move to the next character in both strings.
3. When we stop:
   - Either the characters are different → return their difference.
   - Or we reached the end of one/both strings → return 0 or the difference involving `'\0'`.

**Example: "abc" vs "abd"**
- a == a → continue
- b == b → continue
- c vs d → 'c' = 99, 'd' = 100 → return 99 - 100 = **-1**

---
## 💥 Common Mistakes
| Mistake                                          | Why It’s Wrong / Fails Tests                                                        |
|--------------------------------------------------|-------------------------------------------------------------------------------------|
| Forgetting `(unsigned char)` cast                | Wrong result for characters with ASCII > 127 (signed char overflow)                 |
| Using `strlen` or library functions              | Forbidden – “Allowed functions: None”                                               |
| Comparing with `>` or `<` instead of subtraction | Works for most cases but not required by man strcmp (must return actual difference) |
| Not handling empty strings correctly             | `ft_strcmp("", "a")` must return negative                                           |
| Returning only -1 / 0 / 1                        | Some Moulinette tests expect the actual difference (e.g., 'a' vs 'z' = -25)         |
| Infinite loop                                    | Forgetting to increment pointers inside the loop                                    |

---
## 💡 ASCII Reminder (Important!)
| Character | Decimal (unsigned) |
|-----------|--------------------|
| `'A'`     | 65                 |
| `'Z'`     | 90                 |
| `'a'`     | 97                 |
| `'z'`     | 122                |
| `'0'`     | 48                 |

Uppercase comes before lowercase → `"Z" < "a"` → `ft_strcmp("Z", "a")` returns **negative**

---
## 🧠 Mini-Logic Recap
| Case                        | What happens                                 | Return value |
|-----------------------------|----------------------------------------------|--------------|
| Identical strings           | Loop runs until `'\0'`, both become `'\0'`   | 0            |
| s1 shorter than s2          | Reaches `'\0'` on s1 first                   | negative     |
| s2 shorter than s1          | Reaches `'\0'` on s2 first                   | positive     |
| First difference at position i | `*s1 > *s2` → positive, otherwise negative | difference  |

---
## 🧩 Summary
| Concept                | Key Takeaway                                              |
|------------------------|------------------------------------------------------------|
| Pointer iteration      | Use `*s++` to walk through strings                        |
| Comparison logic       | Compare until difference or end                           |
| Return value           | `(unsigned char)*s1 - (unsigned char)*s2`                 |
| Edge cases             | Empty strings, different lengths, non-printable chars    |
| Norm compliance        | No forbidden functions, clean and readable               |

✅ **End Result:**  
Your `ft_strcmp` behaves **exactly** like the real `strcmp` in every situation – including edge cases with empty strings and extended ASCII.

---
# 🧩 Peer Evaluation Q&A
### 🧠 Q1: What does `ft_strcmp` return when strings are equal?
**A:** 0

### 🧠 Q2: Why do we cast to `(unsigned char)` before subtracting?
**A:** Because `char` might be signed on some systems. Without the cast, characters > 127 could give wrong (negative) differences.

 due to sign extension.

### 🧠 Q3: What happens if one string is a prefix of the other (e.g., "abc" vs "abcd")?
**A:** Returns negative because after "abc", s1 has `'\0'`, s2 has `'d'` → `0 - 'd'` = negative

### 🧠 Q4: Is this loop safe? Can it read beyond string bounds?
**A:** Yes, it's safe. The condition `*s1 && (*s1 == *s2)` guarantees we never dereference past the end of s1, and we only read s2 as long as s1 has characters.

### 🧠 Q5: Why not just return -1, 0, or 1?
**A:** The real `strcmp` returns the actual difference between characters. Some 42 tests check for the exact difference (not just the sign).

### 🧠 Q6: Can I use array indexing instead of pointers?
**A:** Yes! The alternative version with `i` and `s1[i]` is also perfectly fine and often easier to read for beginners.

### 🧠 Q7: What does `while (*s1 && *s1 == *s2)` really mean?
**A:** Continue looping while:
   - Current char in s1 is not null (`*s1 != '\0'`)
   - AND both characters are equal

### 🧠 Q8: How does it handle uppercase vs lowercase?
**A:** Correctly using ASCII values: `'A'` (65) < `'a'` (97), so `"Apple" < "banana"` → negative return

### 🧠 Q9: Is the function allowed to crash on NULL pointers?
**A:** The original `strcmp` has undefined behavior on NULL. Since the subject doesn't specify, most 42 testers don’t pass NULL, so no need to check.

### 🧠 Q10: Best practice for this exercise?
**A:** Write the shortest, cleanest version with `(unsigned char)` cast. It’s only 5 lines and passes everything. Save the longer version for learning/teaching. 

You’ve now mastered one of the most classic C string functions! 🚀
