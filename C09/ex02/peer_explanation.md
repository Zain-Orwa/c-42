# `ft_split` — Peer Explanation

## 🧩 **Goal of the Exercise**

Implement:

```c
char **ft_split(char *str, char *charset);
```

that:

* Splits the string `str` into **words**
* Uses each character of `charset` as a **separator**
* Returns an array of strings (`char **`)
* Ends the array with a `NULL` pointer (i.e., `result[words] = NULL`)
* Contains **no empty strings**
* Uses **malloc only**
* Does **not modify `str`**

---

# 🧠 **High-Level Idea**

We treat `charset` as a **set of delimiters**.
Example:

```c
str     = "Hello,,42;World"
charset = ",;"
```

Separators: `','` and `';'`

Result:

```
["Hello", "42", "World", NULL]
```

We do this by:

1. Counting how many words we will extract
2. Allocating an array of `char *` for those words + 1
3. Extracting each word:

   * find start index
   * measure length
   * allocate memory for that word
   * copy into newly allocated space
4. Store `NULL` at the end

---

# 📌 **Auxiliary Functions**

Two common helpers (not part of subject, but essential):

### `is_separation(char c, char *charset)`

Returns `1` if `c` is found in `charset`, else `0`.

### `count_words_in_str(char *str, char *charset)`

Counts transitions from "sep → word".

Example:

```
"  Hello  42 " → 2 words
```

---

# 🧩 **Your Final `ft_split` Implementation**

```c
/* ft_split: Split string by charset */
char **ft_split(char *str, char *charset){
    int   i;           // Index for scanning the original string
    int   j;           // Index for result array (current word position)
    int   word_len;    // Length of current word
    int   word_start;  // Starting index of current word in str
    int   words_count; // Total number of words found
    char **result;     // Result: array of strings (char** = pointer to string pointers)

    if (!str || !charset)
        return (NULL);

    // STEP 1: Count how many words we have in the input string
    words_count = count_words_in_str(str, charset);

    // STEP 2: Allocate the OUTER ARRAY (array of string pointers)
    result = (char**)malloc(sizeof(char*) * (words_count + 1));
    if (!result)
        return (NULL);

    i = 0;
    j = 0;

    // STEP 3: Extract each word
    while (j < words_count)
    {
        while (str[i] && is_separation(str[i], charset))
            i++;

        if (str[i] && !is_separation(str[i], charset))
        {
            word_start = i;
            word_len = 0;

            while (str[i] && !is_separation(str[i], charset)) {
                word_len++;
                i++;
            }

            // STEP 4: Allocate memory for this word
            result[j] = (char*)malloc(sizeof(char) * (word_len + 1));
            if (!result[j]) {
                while (j--)
                    free(result[j]);
                free(result);
                return (NULL);
            }

            // STEP 5: Copy the word
            ft_strncpy(result[j], &str[word_start], word_len);

            j++;
        }
    }

    // STEP 6: NULL-terminate
    result[j] = NULL;

    return (result);
}
```

---

# 🧱 **Memory Layout Explanation**

Assume:

```c
str = "Hello 42 Piscine";
charset = " "
```

### **Step 1: Count words**

Detected words = `3`

### **Step 2: Allocate outer array**

```
result
   │
   ▼
+----------+----------+----------+----------+
| result[0]| result[1]| result[2]| result[3]|
+----------+----------+----------+----------+
     │          │          │         │
     │          │          │         └───► NULL
     │          │          │
     │          │          └───► malloc for "Piscine\0"
     │          │
     │          └───► malloc for "42\0"
     │
     └───► malloc for "Hello\0"
```

### **Outer allocation**

```
result = malloc(sizeof(char*) * (words_count + 1));
```

`sizeof(char*)` ⇒ size of address (4 or 8 bytes depending on architecture)

---

# 🪵 **Inner Word Allocation**

For each word:

```
result[j] = malloc(sizeof(char) * (word_len + 1));
```

We add `+1` for `'\0'`.

Example:

Word `"Piscine"` has length `7` so:

```
malloc(8)
```

Memory after copy:

```
+---+---+---+---+---+---+---+----+
| P | i | s | c | i | n | e | \0 |
+---+---+---+---+---+---+---+----+
```

---

# 🧪 **Example Trace**

Input:

```c
str = "**Hello***42*Piscine**"
charset = "*"
```

Scanning:

```
**Hello***42*Piscine**
  ↑ word start
```

Extracted words:

```
result[0] = "Hello"
result[1] = "42"
result[2] = "Piscine"
result[3] = NULL
```

---

# ⚠️ **Edge Cases**

| Input            | Output                                 |
| ---------------- | -------------------------------------- |
| `("", ",")`      | `result = { NULL }`                    |
| `(",,,", ",")`   | `result = { NULL }`                    |
| `("Hello", "")`  | **undefined behavior** (charset empty) |
| `NULL, anything` | `NULL`                                 |
| `"Hello", NULL`  | `NULL`                                 |

Note: The subject never fully defines empty `charset` behavior, so checking `if (!charset)` is good.

---

# 🧼 **Memory Safety**

### ✔ Successful allocations:

* one outer `char **`
* `words_count` inner `char *`

### ✔ Failure cleanup logic:

```c
while (j--)
    free(result[j]);
free(result);
```

This avoids **memory leaks**, which is important for Moo**l**inette + Valgrind.

---

# 🛠 **Why `ft_strncpy` is useful**

* We know exact word length beforehand
* Avoids computing `strlen`
* Guarantees null termination

Example call:

```c
ft_strncpy(result[j], &str[word_start], word_len);
```

---

# 🧩 **Complexity Analysis**

Let:

* `n = strlen(str)`
* `m = words_count`

Operations:

* Counting words = `O(n)`
* Extracting words = `O(n)`
* Allocating `m` words = `O(m)`

Total:

```
Time:  O(n + m)  ≈  O(n)
Space: O(n + m) for words + array
```

---

# 🧾 **Conclusion**

This solution:

✔ Does not modify the input string
✔ Uses only `malloc` (as required)
✔ Does not produce empty strings
✔ Adds `NULL` terminator at the end
✔ Handles memory errors safely
✔ Works with multiple separators
✔ Maintains clarity and readability
✔ Matches the Piscine subject precisely

---

# 🧯 **Valgrind Test Recommendation**

Compile with debug flags:

```sh
gcc -g ft_split.c helpers.c main.c
```

Run:

```sh
valgrind --leak-check=full ./a.out
```

Expected result: **0 leaks** if cleanup works.

---

# 🎉 **Done**

