# 📝 **Peer Explanation — Exercise 04: ft_strstr**

---

## 🔍 **What ft_strstr must do**

This function searches for the first occurrence of a string (`to_find`) inside another string (`str`) — exactly like the real `strstr`.

* If `to_find` is empty → return the original `str`.
* If we find a full match → return a pointer to where the match starts in `str`.
* If not found → return `0` (NULL).

The goal is to move through `str` and check whether `to_find` fully matches at each possible position.

---

# ⭐ **Final Correct Code (for reference)**

```c
char *ft_strstr(char *str, char *to_find)
{
    int i;
    int j;

    if (to_find[0] == '\0')
        return (str);

    i = 0;
    while (str[i] != '\0')
    {
        j = 0;
        while (to_find[j] != '\0' && str[i + j] == to_find[j])
            j++;

        if (to_find[j] == '\0')
            return (&str[i]);

        i++;
    }

    return (0);
}
```

---

# 🧠 **Step-by-Step Logic Explanation**

---

## **1️⃣ Handle empty to_find**

```c
if (to_find[0] == '\0')
    return (str);
```

If `to_find` is `""`, the man page says: return `str`, because an empty word is “found” at the beginning.

---

## **2️⃣ Outer Loop — Move through str**

```c
i = 0;
while (str[i] != '\0')
{
    ...
    i++;
}
```

Here:

* `i` is the index of **where we try to match** inside `str`.
* For every character in `str`, we *attempt* a match starting at that position.

---

## **3️⃣ Inner Loop — Compare characters**

```c
j = 0;
while (to_find[j] != '\0' && str[i + j] == to_find[j])
    j++;
```

This is the heart of `ft_strstr`.

We compare:

```
str[i + j]      against      to_find[j]
```

We keep increasing `j` as long as characters match.

If all characters of `to_find` match, the inner loop will stop because:

```
to_find[j] == '\0'
```

Not because of a mismatch.

If there is a mismatch before finishing `to_find`, the inner loop stops early.

---

## **4️⃣ Full Match Detection**

```c
if (to_find[j] == '\0')
    return (&str[i]);
```

This condition decides whether we found the complete word.

* If `j` reached the end of `to_find`, all characters matched.
* So we return a pointer to the **start** of the match (`&str[i]`).

If `to_find[j] != '\0'`, it means we did **not** match completely → continue with next `i`.

---

## **5️⃣ No Match Anywhere**

If the outer loop finishes (`str[i] == '\0'`), we never found a full match.

```c
return (0);
```

That means the word is not in the string.

---

# 🎯 **Why We Use `str[i + j]` — The Key Concept**

This was the biggest question you asked, and here is the clear explanation:

---

## 🧩 **Mathematical Formula Behind `i + j`**

The formula:

```
index = starting_position (i) + offset (j)
```

`i =` The position in `str` where we start checking.
`j =` How far into `to_find` we have matched so far.

So:

* When `j = 0` → `str[i + 0]` → first character to check.
* When `j = 1` → `str[i + 1]` → second character to check.
* When `j = 2` → `str[i + 2]` → third character, etc.

This allows us to test:

```
str[i]     against to_find[0]
str[i + 1] against to_find[1]
str[i + 2] against to_find[2]
...
```

WITHOUT ever modifying `i` inside the inner loop.

### 🎉 Result:

❌ Without `+ j`, we would always compare the same character in `str`.
✔ With `i + j`, we walk forward inside `str` WHILE keeping the starting index unchanged.

---

# 🧠 **Notebook Analogy (rewritten but same meaning)**

Your analogy was excellent. Here it is cleaned and structured:

---

### **“Is adding i + j inside the condition affecting i outside?”**

**No.**

Adding `i + j` does **not** change `i`.
It only calculates an imaginary position for comparison.

Think of it like this:

* `i` is a person standing at a spot in a hallway.
* `j` is how many steps the person *mentally imagines* forward.
* The person (i) never moves inside the inner loop.
* But with each step `j`, they **look ahead** at the next character to compare.

So:

> “Adding `j` to `i` lets `i` imagine moving to the next characters for comparison.
> `i` stays still, but `j` allows us to check all characters of `to_find`.
> Without adding `j`, we would compare only the first character and never move forward.”

And your conclusion:

> “Finally I got it!”

---

# 📘 **How We Control Returning or Not Returning the Address**

These were the three cases you wrote, rewritten clearly:

---

## **1️⃣ Full Match**

* Inner loop increases `j` until it reaches the end of `to_find`.
* That means every character matched.
* Condition:

```
to_find[j] == '\0'
```

So we return:

```
&str[i]
```

---

## **2️⃣ Partial Match but Fail Before End**

* Some characters match → `j` becomes non-zero.
* Then mismatch → inner loop stops early.
* `to_find[j]` is NOT `'\0'` → so no return.
* We move to next `i` and reset `j = 0`.

This is how we avoid false returns.

---

## **3️⃣ No Match at All**

* For every `i`, either:

  * first character doesn’t match → inner loop doesn’t run
  * or partial match fails before finishing `to_find`
* So we never return inside the loop.
* When `str[i] == '\0'` → outer loop ends → we return `0`.

This covers every scenario.

---

# 📚 **Full Q&A (All questions we discussed)**

---

### **Q1: Why don’t we use `while (str[i] == to_find[j] && to_find[j])`?**

Because `str[i]` never changes inside the loop → we would compare the **same character** against the entire `to_find`.

---

### **Q2: Does `i + j` modify `i`?**

No.
`i + j` is just an index calculation.

---

### **Q3: What if j runs until the end and we didn’t match anything?**

Impossible.
`j` only increments while characters match.
If no characters match, `j` stays 0 and the full-match check fails.

---

### **Q4: Where do we prevent false return?**

Here:

```c
if (to_find[j] == '\0')
    return (&str[i]);
```

We only return when we’ve matched the entire `to_find`.

---

### **Q5: What if to_find is empty?**

Return the full string:

```c
if (to_find[0] == '\0')
    return (str);
```

---

### **Q6: Mathematically, what is i + j?**

`i + j = starting index + offset index`

It always points at the correct next character to test.

---

### **Q7: What happens if str ends before to_find?**

The inner loop ends when `str[i + j] == '\0'`,
and since `to_find[j] != '\0'`, we do **not** return,
and eventually outer loop ends → return `0`.

---

# 🎉 **Conclusion**

This exercise teaches:

* nested loops
* pointer returns
* substring search logic
* exact order of conditions
* how to control returning only when full match happens
* the deep concept of `i + j` as “base + offset”

You now fully understand:

* how strstr works
* how each loop behaves
* how match/no-match logic is controlled
* and especially the meaning of `i + j`

---

## 🔁 Bonus: Indexing vs Pointer Version of `ft_strstr`

We’ll compare them **concept by concept**, not just line-by-line noise.
I’ll show what each part does in the indexing version, then the equivalent part in the pointer version, and how they differ.

---

## 1️⃣ Function signature & parameters

### Indexing

```c
char *ft_strstr(char *str, char *to_find){
    int i;
    int j;
    ...
}
```

* `str`  → the big string (haystack).
* `to_find` → the word we search (needle).
* `i`, `j` are **integer indexes** into `str` and `to_find`.

### Pointer

```c
char    *ft_strstr(char *str, char *to_find)
{
    char *s;        // pointer for walking through str
    char *find;     // pointer for walking through to_find
    ...
}
```

* Still the same `str` and `to_find`.
* Instead of `i` and `j`, we have **extra pointers**:

  * `s` walks inside `str` (starting from the current candidate position).
  * `find` walks inside `to_find`.

👉 **Difference:**
Indexing version moves integers `i`, `j` and computes positions with `str[i + j]`.
Pointer version moves **addresses themselves** (`s++`, `find++`).

---

## 2️⃣ Empty `to_find` check

### Indexing

```c
if (to_find[0] == '\0')
    return (str);
```

### Pointer

```c
if (*to_find == '\0')
    return (str);
```

Same logic:

* If the first char is `'\0'` → `to_find` is empty.
* In both cases, we return the full `str`.

👉 **Difference:**
Indexing uses array notation `to_find[0]`, pointer version uses `*to_find`.
But both mean “the first character”.

---

## 3️⃣ Outer loop — walking through `str`

### Indexing

```c
i = 0;
while (str[i] != '\0')
{
    ...
    i++;
}
```

* `i` starts at 0.
* For each `i`, we **try** to see if `to_find` starts at `str[i]`.
* After each attempt, we increase `i` and move one step to the right.

### Pointer

```c
while (*str)
{
    s = str;
    find = to_find;
    ...
    str++;
}
```

* Here `str` itself is the walking pointer.
* At each iteration:

  * `s` is set to the current `str` (candidate start).
  * `find` is reset to `to_find`.
* After each attempt, `str++` moves to the next character.

👉 **Difference in style:**

* Indexing:
  `i` moves: `str[i]`, `str[i+1]`, `str[i+2]`, …
  Original `str` pointer never changes.

* Pointer:
  `str` itself moves: first it points to `str[0]`, then `str[1]`, etc.
  `s` is a temporary pointer for the inner comparison.

The **algorithm is identical**, they just move different things.

---

## 4️⃣ Inner loop — matching characters

### Indexing version

```c
j = 0;
while (to_find[j] != '\0' && str[i + j] == to_find[j])
    j++;
```

* Start with `j = 0` (first char of `to_find`).
* Compare `str[i + j]` with `to_find[j]`.
* If they match, increase `j` and continue.
* Stop when:

  * a mismatch happens, or
  * we reached the end of `to_find`.

### Pointer version

```c
s = str;
find = to_find;

while (*find && *s == *find)
{
    s++;
    find++;
}
```

* `s` starts at the candidate position in `str`.
* `find` starts at the beginning of `to_find`.
* Compare `*s` with `*find`.
* If equal, `s++` and `find++` move to next char.
* Stop when:

  * a mismatch happens, or
  * we reached the end of `to_find` (`*find == '\0'`).

👉 **Key correspondence:**

* `str[i + j]`  ↔  `*s`
* `to_find[j]`  ↔  `*find`
* `i` fixed, `j` grows  ↔  `str` fixed for this attempt, `s` moves.

Mathematically:

```text
s == &str[i]       →    *(s + j) == str[i + j]
```

So both inner loops are doing the **same comparisons**, just written differently.

---

## 5️⃣ Full match check

### Indexing

```c
if (to_find[j] == '\0')
    return (&str[i]);
```

* If we ended the inner loop because `to_find[j] == '\0'`,
  it means all characters of `to_find` matched.
* Return the **address of the start of the match**: `&str[i]`.

### Pointer

```c
if (*find == '\0')
    return (str);
```

* If we ended the inner loop because `*find == '\0'`,
  we matched the whole `to_find`.
* Return the current `str` (the start of this attempt).

👉 **Difference:**

* Indexing version: “start” is `&str[i]`.
* Pointer version: “start” is simply `str`.

But at that moment those two are **the same address**:

```c
str (pointer version)   ==   &str[i] (index version)
```

Because in the pointer version, the outer loop has already advanced `str` by `i` positions.

---

## 6️⃣ No match found → return 0

### Indexing

```c
return (0);
```

### Pointer

```c
return (0);
```

Same: if we finish the outer loop (reach `'\0'` in `str`) with no full match, we return `0` (NULL).

---

## 7️⃣ Main function tests

### Indexing main

```c
char str[]   = "Hello World";
char find1[] = "World";
char find2[] = "lo Wo";
char find3[] = "xyz";
char find4[] = "";

printf("%s\n", ft_strstr(str, find1));
printf("%s\n", ft_strstr(str, find2));
printf("%s\n", ft_strstr(str, find3));
printf("%s\n", ft_strstr(str, find4));
```

### Pointer main

```c
char str[]   = "Hello World";
char find1[] = "World";
char find2[] = "lo Wo";
char find3[] = "xyz";
char find4[] = "";

printf("%s\n", ft_strstr(str, find1));  // → World
printf("%s\n", ft_strstr(str, find2));  // → lo World, till the end of the string.
printf("%s\n", ft_strstr(str, find3));  // → (null)
printf("%s\n", ft_strstr(str, find4));  // → Hello World
```

Behavior (for both versions):

* `"World"` is found → prints `World`.
* `"lo Wo"` is found → prints `lo World` (from the `l`).
* `"xyz"` not found → function returns `0` → `printf("%s", 0)` is **undefined**,
  but many libs print `(null)`.
* `""` (empty string) → returns full `str` → prints `Hello World`.

👉 **Important note for your notes:**

For real safe code, when testing:

```c
char *res = ft_strstr(str, find3);
if (res)
    printf("%s\n", res);
else
    printf("Not found\n");
```

But for the Piscine exercise they usually ignore this detail.

---

## 🧮 Small “Mental Model” Summary

You can think of them like this:

### Indexing version

* `i` = “where I start in the big string”
* `j` = “how deep I am into the word”
* I check `str[i + j]` with `to_find[j]`.

### Pointer version

* `str` = “current starting point in the big string”
* `s` = “current comparing position inside `str`”
* `find` = “current comparing position inside `to_find`”
* I check `*s` with `*find`.

They are *the same algorithm* written in two dialects:

* **Array dialect** → indexes `i`, `j`.
* **Pointer dialect** → moving pointers `str`, `s`, `find`.

---

## 💡 Which one should you use in an exam?

