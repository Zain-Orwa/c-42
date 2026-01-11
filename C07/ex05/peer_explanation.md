````markdown
# Exercise 05: `ft_split`
peer_explanation.md

---

## 🧩 1. Exercise Overview

**Goal:**  
Write a function that splits a string into an array of “words”, using a set of separator characters.

From the subject:

- Turn-in directory : `ex05/`
- File to turn in   : `ft_split.c`
- Allowed functions : `malloc`
- Prototype:

```c
char **ft_split(char *str, char *charset);
````

**Rules:**

* Every character in `charset` is treated as a separator.
* The result must be an **array of C-strings** (`char **`).
* The **last element** of the array must be `NULL` to mark the end.
* **No empty strings** should appear in the result.
* The input string `str` is not modifiable.
* Memory must be dynamically allocated with `malloc`.

---

## 🧠 2. High-Level Idea

We want to transform one string:

```txt
"hello,,,world,,test"
```

into something like:

```txt
result[0] -> "hello"
result[1] -> "world"
result[2] -> "test"
result[3] -> NULL
```

Conceptually the algorithm is:

1. **Scan** the string and **count** how many “words” there are.
   A word is a sequence of non-separator characters.
2. **Allocate** an array of `char *` (one pointer per word + 1 `NULL`).
3. Scan again:

   * Skip separators.
   * When a word starts:

     * Measure its length.
     * Allocate memory for that word.
     * Copy the characters into that new buffer.
4. Put a final `NULL` pointer after the last word.

---

## 🧱 3. Code Used in This Solution

```c
#include <stdio.h>
#include <stdlib.h>

/* function to find separations */
int is_separation(char c, char *charset){
	int i;
	
	i = 0;
	while (charset[i]){
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

/* function to count words in the array string */
int count_words_in_string(char *str, char *charset){
	int i;
	int count;

	if (!str || !charset)
		return (0);

	i = 0;
	count = 0;
	while (str[i]){
		while (str[i] && is_separation(str[i], charset))
			i++;

		if (str[i] && !is_separation(str[i], charset))
		{
			count++;
			while (str[i] && !is_separation(str[i], charset))
				i++;
		}
	}
	return (count);
}

/* function to copy from the string to the allocated memory */
char *ft_strncpy(char *dst, char *src, int size){
	int i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/* ft_split: Split string by charset */
char **ft_split(char *str, char *charset) {
    int   i;      // Index for scanning the original string
    int   j;      // Index for result array (current word position)
    int   len;    // Length of current word
    int   words;  // Total number of words found
    int   start;  // Starting index of current word in str
    char  **result; // Result: array of strings (char** = pointer to string pointers)

    if (!str || !charset)
        return (NULL);

    // STEP 1: Count how many words we have
    words = count_words_in_string(str, charset);

    // STEP 2: Allocate the OUTER ARRAY (array of string pointers)
    result = (char**)malloc(sizeof(char*) * (words + 1));
    if (!result)
        return (NULL);

    i = 0;  // Start scanning from beginning of str
    j = 0;  // Start filling result from index 0

    // STEP 3: Extract each word
    while (j < words) {
        // Skip any separator characters
        while (str[i] && is_separation(str[i], charset))
            i++;

        // If we found the beginning of a word
        if (str[i] && !is_separation(str[i], charset)) {
            start = i;  // Remember where word starts
            len = 0;    // Reset word length counter

            // Measure the word length
            while (str[i] && !is_separation(str[i], charset)) {
                len++;  // Count this character
                i++;    // Move to next character in str
            }

            // STEP 4: Allocate memory for THIS SPECIFIC WORD
            result[j] = (char*)malloc(sizeof(char) * (len + 1));
            if (!result[j])
                return (NULL);

            // STEP 5: Copy the word into the newly allocated memory
            ft_strncpy(result[j], &str[start], len);

            j++;  // Move to next slot in result array
        }
    }

    // STEP 6: NULL-terminate the array of pointers
    result[j] = NULL;

    return (result);
}
```

(The `main`, `print_split_result`, and `free_split_result` functions are **test helpers** and are not part of the official 42 submission, but they’re great for understanding and debugging.)


---

## 🔍 4. Helper Functions in Depth

### 4.1 `is_separation`

```c
int is_separation(char c, char *charset)
```

**Purpose:**
Checks whether character `c` is one of the separators in `charset`.

**Logic:**

* Loop over `charset` until `'\0'`.
* If any `charset[i]` equals `c`, return `1` (true).
* If loop ends, return `0`.

So if `charset = " ,.-"` then:

* `is_separation(' ', " ,.-")` → `1`
* `is_separation('a', " ,.-")` → `0`

**Analogy:**
Think of `charset` as a *blacklist*. This function answers:

> “Is `c` on the blacklist of separator characters?”

---

### 4.2 `count_words_in_string`

```c
int count_words_in_string(char *str, char *charset)
```

**Why do we need it?**
We must know exactly how many words to allocate space for in the result array.

**Key points:**

* If `str` or `charset` is `NULL` → returns `0`.
* Uses an index `i` to walk through `str`.
* First **skips separators**:

  ```c
  while (str[i] && is_separation(str[i], charset))
      i++;
  ```
* If we now sit at a non-separator character (`str[i] && !is_separation(...)`), that means a new word starts:

  * `count++`
  * Then we advance `i` until the end of this word.

**Important detail:**
Empty strings and “runs” of separators are skipped correctly, because new words are only counted when we *enter* a zone of non-separator characters.

---

### 4.3 `ft_strncpy`

```c
char *ft_strncpy(char *dst, char *src, int size)
```

This is a **simplified internal** `strncpy`:

* Assumes we already know exactly how many characters (`size`) to copy.
* Copies exactly `size` bytes from `src` to `dst`.
* Adds a `'\0'` at the end.

No padding with extra `'\0'` like the real `strncpy`, but it’s OK because the call site always passes the *exact* word length.

---

## 🧬 5. `ft_split` – Step-by-Step Walkthrough

### 5.1 Parameters and NULL checks

```c
if (!str || !charset)
    return (NULL);
```

* Protects against invalid usage.
* If either argument is `NULL`, we cannot split anything.

---

### 5.2 Count words and allocate the outer array

```c
words = count_words_in_string(str, charset);
result = (char**)malloc(sizeof(char*) * (words + 1));
if (!result)
    return (NULL);
```

* `words` is how many **substrings** we will have.
* `result` is a **pointer to pointers** (`char **`).
* Memory layout (conceptually):

```txt
result
  |
  +-- [0] -> (char *) for word 0
  +-- [1] -> (char *) for word 1
  ...
  +-- [words - 1] -> (char *) for last word
  +-- [words] -> NULL     (terminator)
```

We allocate `words + 1` so we have room for that final `NULL`.

---

### 5.3 Extracting words

We use two indices:

* `i` → walks through the original string.
* `j` → position in the `result` array.

#### 5.3.1 Skip separators

```c
while (str[i] && is_separation(str[i], charset))
    i++;
```

This moves `i` forward until we are either:

* At end of string (`str[i] == '\0'`), or
* At the start of a word (non-separator).

#### 5.3.2 Detect word start

```c
if (str[i] && !is_separation(str[i], charset)) {
    start = i;
    len = 0;
    ...
}
```

* `start` remembers where the word begins.
* `len` will measure how long it is.

#### 5.3.3 Measure word length

```c
while (str[i] && !is_separation(str[i], charset)) {
    len++;
    i++;
}
```

* This stops when:

  * We hit a separator, or
  * We hit the `'\0'` at the end.

Now we know exactly how many characters to copy.

#### 5.3.4 Allocate memory for this word

```c
result[j] = (char*)malloc(sizeof(char) * (len + 1));
if (!result[j])
    return (NULL);
```

For example, if the word is `"hello"`:

* `len = 5`
* `malloc(6)` bytes → `"hello\0"`

**Memory diagram (one word):**

```txt
result[j]  ─┐
            └─▶ [h][e][l][l][o]['\0']
```

#### 5.3.5 Copy the substring

```c
ft_strncpy(result[j], &str[start], len);
j++;
```

* `&str[start]` is the address of the first character of the word.
* `ft_strncpy` copies exactly `len` chars and appends `'\0'`.
* `j++` gets ready for the next word.

---

### 5.4 NULL-terminating the array of strings

After the `while (j < words)` loop:

```c
result[j] = NULL;
```

* `j` is now equal to `words`.
* We store `NULL` in the last slot.

So the overall structure is:

```txt
result
  |
  +-- result[0] -> "word0\0"
  +-- result[1] -> "word1\0"
  ...
  +-- result[words-1] -> "last\0"
  +-- result[words]   -> NULL
```

This is the standard 42 / C convention for “array of strings”.

---

## 🧪 6. Test Cases (from `main`)

The provided `main` tests many edge cases:

1. Basic split with one separator.
2. Multiple separators using charset `" !-"`.
3. Empty string `""`.
4. String containing only separators.
5. String with **no** separator → should return one word (the whole string).
6. Multiple consecutive separators → no empty strings.
7. Separators at the beginning and end.
8. Complicated charset like `"+-*/"`.

These tests verify:

* Word counting logic.
* No empty strings.
* Correct `NULL` termination.
* No crashes when there are no words.

---

## 🧹 7. Memory Management

Two important helper functions:

```c
void free_split_result(char **result)
{
	int	i;

	if (!result)
		return;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}
```

* Frees **each word** (`result[i]`) and then the **outer array** (`result`).
* This matches the two levels of `malloc`:

  * One for the array of pointers.
  * One per individual string.

**Note:**
In `ft_split`, if one `malloc` for a word fails, we simply `return (NULL)` without freeing previous words. This creates a **memory leak** in that rare error case.
For the exercise it’s usually accepted, but in production code we would:

* Free all `result[0..j-1]`.
* Free `result`.
* Return `NULL`.

---

## ⚖️ 8. Time & Space Complexity

* `count_words_in_string` scans the string once: **O(n)**.
* `ft_split` scans the string again, plus copies each character once: **O(n)**.

So overall time complexity is **O(n)** where `n` is `strlen(str)`.

Space complexity:

* Outer array: `O(words)`.
* Inner strings: `O(n)` total characters.

Total extra space: **O(n + words)**.

---

## ❓ 9. Deep Questions for Peer Evaluation

These are questions an evaluator can ask, with short expected answers.

### 9.1 Understanding pointers and memory

**Q1:**
Why do we allocate `sizeof(char*) * (words + 1)` for the outer array instead of `sizeof(char) * (words + 1)`?

**A:**
Because `result` is an array of **pointers to char** (`char *`), not an array of characters. Each element `result[j]` must be large enough to hold a pointer. On most systems a pointer is 8 bytes, not 1.

---

**Q2:**
For a string `"hello,,,world"`, can you draw the memory layout for `result` and the individual words?

**A (sketch):**

```txt
str:   [h][e][l][l][o][,][,][,][w][o][r][l][d]['\0']

result:
   result[0] ─▶ [h][e][l][l][o]['\0']
   result[1] ─▶ [w][o][r][l][d]['\0']
   result[2] ─▶ NULL
```

---

**Q3:**
Does `ft_split` modify the original string `str`?

**A:**
No. It only **reads** from `str` and allocates new buffers. All modifications happen in the new memory pointed to by `result[j]`.

---

### 9.2 Logic of counting words

**Q4:**
Why do we first skip separators before counting a word in `count_words_in_string`?

**A:**
Because we don't want to count separators as words, and we don't want empty strings when multiple separators appear in a row. We only increment the word count when we transition from a separator region into a non-separator region.

---

**Q5:**
What happens when the input string is `""` (empty string)? How many words, and what does `ft_split` return?

**A:**

* `count_words_in_string` returns `0`.
* We still allocate an array of size `1` (`words + 1`).
* `result[0]` is set to `NULL`.
* So `ft_split("")` returns a valid array whose first element is `NULL` → “empty list of words”.

---

### 9.3 `ft_strncpy` and boundaries

**Q6:**
Why doesn’t `ft_strncpy` check `src[i] != '\0'` inside the loop?

**A:**
Because we *already* measured the word’s length (`len`) by counting non-separator characters, so we know `src[start..start+len-1]` are valid characters of the word. We don’t need to check `'\0'` again, and we always append a `'\0'` ourselves at the end.

---

### 9.4 Error handling and robustness

**Q7:**
What happens if `malloc` for one of the words fails? Is that safe?

**A:**
The function returns `NULL`, but all words already allocated are leaked. For the exercise this is usually tolerated, but in real-world code we should free previously allocated words and the `result` array before returning.

---

### 9.5 Design alternatives

**Q8:**
Could we implement `ft_split` with only **one** allocation instead of many small ones?

**A (discussion):**

Yes, advanced implementations sometimes:

* Allocate one big block for all characters.
* Allocate an array of pointers pointing inside that block (or reuse parts of the original string by temporarily inserting `'\0'`).

But for this exercise:

* We must not modify `str`.
* Clarity is more important than extreme optimization.
* Separate `malloc` per word is easier to understand.

---

### 9.6 Double pointer intuition

**Q9:**
In simple words, what does `char **result` represent?

**A:**
A “list of strings”.

More precisely: `result` is the address of the **first element** of an array; each element is a `char *` pointing to a C-string.

---

**Q10:**
In memory terms, what is the difference between:

```c
char *s;
char **result;
```

**A:**

* `char *s` → a pointer to **characters** (a single string).
* `char **result` → a pointer to **pointers to characters** (an array of strings).

---

## ✅ 10. Things to Check During Peer Evaluation

When you evaluate this code, you can ask the author:

1. **Edge cases**

   * What does your function return for:

     * Empty string?
     * Only separators?
     * String with no separators?
   * Are there any empty strings in the result?

2. **Memory**

   * How many `malloc` calls happen for an input with `N` words?
   * How do you free everything correctly?

3. **API contract**

   * Why is the final element `result[words] = NULL` important?
   * Can the caller loop over the result without knowing the number of words beforehand?

4. **Complexity**

   * How many times is the input string scanned?
   * What is the time complexity?

---

```

