````md
# 🧪 Exercise 01 — `ft_strncmp`

---

## 1️⃣ Goal of the exercise

Reproduce the behavior of the standard C function `strncmp`.

> Compare **at most `n` characters** of two strings and tell if:
> - they are equal,
> - the first string is "smaller",
> - or the first string is "greater" (in lexicographical / ASCII order).

---

## 2️⃣ Prototype

```c
int ft_strncmp(char *s1, char *s2, unsigned int n);
````

### Parameters

* `s1` — first string to compare
* `s2` — second string to compare
* `n`  — maximum number of characters to compare

### Return value

* `0`  → the first `n` characters of both strings are equal
* `< 0` → `s1` is "less than" `s2`
* `> 0` → `s1` is "greater than" `s2`

More precisely, it returns:

```c
(unsigned char)s1[i] - (unsigned char)s2[i]
```

for the first position `i` where the characters differ, or where one string ends.

---

## 3️⃣ Final implementation (pointer version)

```c
int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	while (n && *s1 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
```

---

## 4️⃣ How the algorithm works (step by step)

### 🔁 The loop

```c
while (n && *s1 && *s1 == *s2)
```

We continue comparing while:

1. `n` is not zero
2. `*s1` is not `'\0'` (so we didn’t reach the end of `s1`)
3. the current characters are equal (`*s1 == *s2`)

Inside the loop:

```c
s1++;
s2++;
n--;
```

* `s1++` and `s2++` move both pointers to the **next characters**.
* `n--` decreases how many characters we are still allowed to compare.

So the loop consumes characters **one by one** until:

* we used up `n` characters, or
* we hit a different character, or
* we hit the end of `s1` (or `s2`, via the equality test).

### 🧱 After the loop

Two cases:

#### 1. We compared `n` characters

```c
if (n == 0)
    return (0);
```

If `n` becomes 0, it means we successfully compared `n` characters and all were equal → result is 0.

#### 2. We stopped early (difference or end of a string)

```c
return ((unsigned char)*s1 - (unsigned char)*s2);
```

* Here `*s1` and `*s2` are the **first characters that differ**,
  or one of them is `'\0'` (end of string).
* The subtraction gives:

  * `< 0` if `*s1 < *s2`
  * `> 0` if `*s1 > *s2`
  * (0 is impossible here, because if the chars were equal, we would still be in the loop.)

We cast to `unsigned char` to avoid problems on systems where `char` is signed and may be negative for characters with ASCII code ≥ 128.

---

## 5️⃣ Examples

Assume ASCII order.

### Example 1 — Equal in the first `n` chars

```c
ft_strncmp("Hello", "HelloWorld", 5) → 0
```

We only compare 5 characters: `"Hello"` vs `"Hello"` → equal.

---

### Example 2 — Difference before `n`

```c
ft_strncmp("abc", "abd", 3)
```

Comparison:

* `'a'` vs `'a'` → equal
* `'b'` vs `'b'` → equal
* `'c'` vs `'d'` → different → loop stops

Return:

```c
'c' - 'd' = 99 - 100 = -1  (negative)
```

So `s1 < s2`.

---

### Example 3 — Difference after `n`

```c
ft_strncmp("abc", "abd", 2)
```

We only compare 2 characters:

* `'a'` vs `'a'` → equal
* `'b'` vs `'b'` → equal

Now we used 2 characters → `n` becomes 0 → function returns 0, **even though the 3rd char is different**.
That’s exactly how `strncmp` is supposed to work.

---

### Example 4 — One string shorter

```c
ft_strncmp("abc", "abcdef", 6)
```

* Compare `'a'` vs `'a'` → equal
* `'b'` vs `'b'` → equal
* `'c'` vs `'c'` → equal
* next: `'\0'` vs `'d'` → difference

Return:

```c
'\0' - 'd' = 0 - 100 = -100  (negative)
```

So `"abc"` is considered smaller.

---

## 6️⃣ Common mistakes

* ❌ Forgetting to stop when `n == 0`

  * You must **not** compare more than `n` characters.
* ❌ Returning `*s2 - *s1` instead of `*s1 - *s2`

  * This inverts the sign of the result and no longer matches the real `strncmp`.
* ❌ Not handling `n == 0` correctly

  * If `n` is 0, you must **immediately return 0** (no access to `s1[0]` or `s2[0]`).
* ❌ Forgetting to cast to `unsigned char`

  * Can give weird negative values with non-ASCII/extended characters.

---

## 7️⃣ Suggested tests (for your `main`)

Try to compare your `ft_strncmp` with the real `strncmp` on a system where you can use `<string.h>`:

```c
#include <stdio.h>
#include <string.h>

printf("Mine: %d | Real: %d\n",
    ft_strncmp("abc", "abd", 3),
    strncmp("abc", "abd", 3));
```

Test with:

* Same strings, different `n` values
* One empty string
* `n = 0`
* One string shorter than the other
* Strings that only differ after many equal chars

---

## 8️⃣ Peer Evaluation Q&A

**Q1.** What is the difference between `strcmp` and `strncmp`?
➡️ `strcmp` compares until a difference or `'\0'`. `strncmp` does the same but **at most `n` characters**.

**Q2.** What happens when `n` is 0?
➡️ The function returns `0` immediately (no characters are compared).

**Q3.** Why do we use `unsigned char` in the return expression?
➡️ To avoid issues on systems where `char` is signed; it ensures comparisons use the characters’ numeric values from 0 to 255, like the real `strncmp`.

**Q4.** When does the loop stop?
➡️ When `n == 0`, or we reach `'\0'` in `s1`, or the current characters `*s1` and `*s2` are different.

**Q5.** If the function returns a negative value, what does that mean?
➡️ It means `s1` is lexicographically **smaller** than `s2` at the first differing position.

**Q6.** What the differences between these two versions?

* **Version A** = pointer version (uncommented)
* **Version B** = index version (commented)

I’ll write them both in the *correct* form (same sign in the return):

```c
/* 👉 Version A: pointer version */
int ft_strncmp(char *s1, char *s2, unsigned int n)
{
	while (n && *s1 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
```

```c
/* 👉 Version B: index version */
int ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;

	if (i == n)
		return (0);

	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
```

---

## 1️⃣ Where they differ (surface level)

### a) How they walk through the strings

* **Version A (pointers)**
  Moves the *pointers themselves*:

  ```c
  s1++;
  s2++;
  n--;
  ```

* **Version B (index)**
  Keeps the base address fixed and moves an **index**:

  ```c
  i++;
  ```

So in A we always look at the "current char":

```c
*s1, *s2
```

In B we always look at:

```c
s1[i], s2[i]
```

But in C:

> `s1[i]` is exactly the same as `*(s1 + i)`

So both are just “go to the next character”.

---

### b) How they use `n`

* **Version A**: `n` means **how many characters are left** to compare.

  * Starts with `n`
  * Each loop: `n--`
  * Loop condition: `while (n && …)` → “while we still have characters left to compare”

* **Version B**: `i` means **how many characters we already compared**.

  * Starts with `i = 0`
  * Each loop: `i++`
  * Loop condition: `while (i < n && …)` → “while we haven’t compared `n` characters yet”

So:

* Version A uses a **countdown** (n → n-1 → … → 0)
* Version B uses a **count up** (0 → 1 → … → n)

Those are two ways to express the same limit: “don’t compare more than `n` characters”.

---

### c) The loop conditions

**Version A:**

```c
while (n && *s1 && *s1 == *s2)
```

Meaning:

1. `n` is not 0 (still allowed to compare more characters)
2. `*s1` is not `'\0'`
3. current characters are equal

Because the characters are equal, `*s2` is also not `'\0'` in any iteration of the loop.

**Version B:**

```c
while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
```

Meaning:

1. we did not yet compare `n` characters
2. `s1[i]` is not `'\0'`
3. `s2[i]` is not `'\0'`
4. current characters are equal

So B checks both `s1[i]` and `s2[i]` separately, A only checks `*s1`, but because of the equality condition `*s1 == *s2`, they are effectively equivalent: if `*s1` is `'\0'`, then `*s2` must also be `'\0'` to stay in the loop.

---

### d) After the loop

* **Version A:**

  ```c
  if (n == 0)
      return (0);
  return ((unsigned char)*s1 - (unsigned char)*s2);
  ```

* **Version B:**

  ```c
  if (i == n)
      return (0);
  return ((unsigned char)s1[i] - (unsigned char)s2[i]);
  ```

Again, same idea:

* In A: if `n` reached 0 → we compared exactly `n` equal characters → return 0.
* In B: if `i` reached `n` → we compared exactly `n` equal characters → return 0.

Otherwise, we stopped the loop because:

* characters differ, or
* one string ended

And both return the difference between the first non-matching pair.

---

## 2️⃣ Why they give the same result (logic level)

Let’s follow a concrete example.

### Example: `"abc"` vs `"abd"`, `n = 3`

#### Version A (pointer)

Start:

* `s1 → 'a'`, `s2 → 'a'`, `n = 3`

Loop:

1. `n && *s1 && *s1 == *s2`
   → `3 && 'a' && 'a' == 'a'` → true
   → increment pointers, `n--` →
   `s1 → 'b'`, `s2 → 'b'`, `n = 2`

2. Again: `2 && 'b' && 'b' == 'b'` → true
   → `s1 → 'c'`, `s2 → 'd'`, `n = 1`

3. Next: `1 && 'c' && 'c' == 'd'` → false
   → exit loop with `n = 1`

`n` is not 0, so:

```c
return ( (unsigned char)*s1 - (unsigned char)*s2 );
// 'c' - 'd' = -1
```

#### Version B (index)

Start:

* `i = 0`, `n = 3`

Loop:

1. Condition: `i < n && s1[i] && s2[i] && s1[i] == s2[i]`
   → `0 < 3 && 'a' && 'a' && 'a' == 'a'` → true
   → `i = 1`

2. `1 < 3 && 'b' && 'b' && 'b' == 'b'` → true
   → `i = 2`

3. `2 < 3 && 'c' && 'd' && 'c' == 'd'` → false
   → exit with `i = 2`

`i != n`, so:

```c
return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 'c' - 'd' = -1
```

👉 Same final characters compared, same result.

---

### Example: they are equal for first `n` chars

`ft_strncmp("Hello", "HelloWorld", 5)`

* **Version A** will run the loop 5 times, `n` becomes 0 → returns 0.
* **Version B** will run the loop 5 times, `i` becomes `n` (5) → returns 0.

Again same behavior.

---

### Example: `n = 0`

* **Version A**

  * Condition: `while (n && ...)` → `n` is 0 → loop doesn’t run.
  * Immediately `if (n == 0) return 0;`

* **Version B**

  * Condition: `while (i < n && ...)` → `i = 0`, `n = 0` → `0 < 0` is false → no loop.
  * `if (i == n)` → `0 == 0` → return 0.

Same: `n = 0` ⇒ must always return 0.

---

## 3️⃣ Summary in one sentence

* **Version A** compares up to `n` chars by moving the **pointers** and counting down `n` (remaining chars).
* **Version B** compares up to `n` chars by keeping the pointers fixed, moving an **index** `i` and counting up (already compared chars).

Even though they *look* different, they:

* stop in the same situations, and
* finally compare the same pair of characters (or `'\0'` vs something), and
* use the same return expression.


