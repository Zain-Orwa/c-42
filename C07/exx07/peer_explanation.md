# 🧵 Ex07: Dynamic Line Reader & Word Counter — Peer Explanation

---

## 📌 Goal of the Program

This program:

1. **Prompts the user** to enter a line of text.
2. **Reads** the entire line from `stdin` using a dynamically growing buffer (no fixed size).
3. **Counts** how many “words” are in that line.

   * A *word* is any sequence of non-whitespace characters separated by:

     * space `' '`
     * tab `'\t'`
     * newline `'\n'`
4. Prints:

   * The line the user typed.
   * The number of words found.

---

## 🧰 Utility Functions

### `ft_putchar`

```c
void	ft_putchar(char c)
{
	write(1, &c, 1);
}
```

Low-level wrapper over `write` to print a single character to stdout.

---

### `ft_putstr`

```c
void	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}
```

* Checks for `NULL` input.
* Prints the string character by character with `ft_putchar`.

---

### `ft_putnbr`

```c
void	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}
```

* Uses a `long` to safely handle `INT_MIN`.
* Prints the sign if negative.
* Uses **recursion** to print higher digits first (`nb / 10`), then the last digit (`nb % 10`).

---

### `ft_strncpy`

```c
char	*ft_strncpy(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
```

* Copies at most `size` characters from `src` to `dst`.
* Stops earlier if the source ends.
* Ensures the destination is **null-terminated**.

Here it’s used to move the old buffer contents into a newly allocated, larger buffer.

---

## 📦 Dynamic String Reading

### `ft_realloc_str`

```c
char	*ft_realloc_str(char *str, size_t *size)
{
	char	*new_str;
	size_t	new_size;

	if (*size == 0)
		new_size = 32;
	else
		new_size = *size * 2;
	new_str = (char *)malloc(new_size);
	if (!new_str)
		return (NULL);
	if (str)
	{
		ft_strncpy(new_str, str, (int)(*size));
		free(str);
	}
	*size = new_size;
	return (new_str);
}
```

**Purpose:** Grow the buffer when more space is needed.

* If current size is `0`, it starts with **32 bytes**.
* Otherwise, it **doubles** the size (`*size * 2`) — classic dynamic array strategy.
* Allocates the new buffer.
* Copies old contents with `ft_strncpy`.
* Frees the old buffer.
* Updates `*size` to the new capacity.
* Returns the new pointer.

This function **abstracts** away the resizing logic from the reading function.

---

### `read_string`

```c
char	*read_string(void)
{
	char	ch;
	size_t	length;
	char	*buffer;
	size_t	buffer_size;

	buffer = NULL;
	buffer_size = 0;
	length = 0;
	ft_putstr("Please Enter Your String:\n");
	while (1)
	{
		if (read(0, &ch, 1) <= 0 || ch == '\n')
			break ;
		if (length + 1 >= buffer_size)
		{
			buffer = ft_realloc_str(buffer, &buffer_size);
			if (!buffer)
				return (NULL);
		}
		buffer[length] = ch;
		length++;
	}
	if (buffer)
		buffer[length] = '\0';
	return (buffer);
}
```

Step-by-step:

1. **Initialization**

   * `buffer = NULL`, `buffer_size = 0`, `length = 0`.
   * Prints prompt.

2. **Reading loop**

   * Reads **one character at a time** from `stdin` using `read(0, &ch, 1)`.
   * If:

     * `read` returns `<= 0` (EOF or error), or
     * character is newline `'\n'`
       → break the loop.

3. **Ensure capacity**

   * Before writing a character, it checks:

     ```c
     if (length + 1 >= buffer_size)
     ```

     * `+1` leaves room for the final `'\0'`.
     * If full, calls `ft_realloc_str` to grow the buffer.

4. **Append character**

   * Stores the character at `buffer[length]`, then increments `length`.

5. **Null termination**

   * After reading is done:

     ```c
     if (buffer)
         buffer[length] = '\0';
     ```
   * Ensures the string is a valid C string.

6. **Return**

   * Returns `buffer` (or `NULL` if allocation failed).

So `read_string` returns a **dynamically allocated** string of exactly the input length (plus `'\0'`), with *no artificial size limit*.

---

## 📚 Word Counting Logic

### `count_words_in_string`

```c
int	count_words_in_string(char *str)
{
	int		count;
	char	*start;
	char	*current;

	if (!str)
		return (0);
	count = 0;
	start = str;
	current = str;
	while (*current)
	{
		if (*current == ' ' || *current == '\t' || *current == '\n')
		{
			if (current > start)
				count++;
			start = current + 1;
		}
		current++;
	}
	/* Count last word if string doesn't end with space/tab/newline */
	if (current > start)
		count++;
	return (count);
}
```

This function uses **two pointers**: `start` and `current`.

* `start` → points to the **beginning of a potential word**.
* `current` → walks through each character of the string.

### 1. Guard against NULL

```c
if (!str)
	return (0);
```

If no string is given, there are 0 words.

---

### 2. Initialization

```c
count = 0;
start = str;
current = str;
```

Both pointers start at the beginning of the string.

---

### 3. Scanning the string

```c
while (*current)
{
	if (*current == ' ' || *current == '\t' || *current == '\n')
	{
		if (current > start)
			count++;
		start = current + 1;
	}
	current++;
}
```

We loop until we hit `'\0'`.

Inside the loop:

* If `*current` is a **separator** (space, tab, newline):

  * We check: `current > start`

    * This means: “Did we see **at least one non-separator** character since the last `start`?”
    * If yes → we just finished a word → `count++`.
  * Then we move `start` to the **character after** the separator:

    ```c
    start = current + 1;
    ```
* Regardless, we increment `current` to scan the next character.

This avoids using a `flag` like `in_word` and relies only on pointer positions.

---

### 4. Counting the last word

```c
if (current > start)
	count++;
```

Imagine the string:

* `"Hello 42 from Zain"` → doesn’t end with space.
* The last word `"Zain"` is not followed by a separator.
* The loop ends when `*current == '\0'`, but we haven’t counted the last word yet.

Here:

* `current` points at `'\0'`
* `start` still points at `'Z'` of `"Zain"`

Because `current > start`, we know there’s a word that started at `start` and reached the end of the string → so we count one last word.

If the string **ends with whitespace**, e.g. `"Hello 42 "`, then:

* After the last space, we set `start` to point at `'\0'`.
* At the end,

  * `current` also points at `'\0'`.
  * So `current > start` is false → no extra word is added.
    This correctly avoids counting empty “words” caused by trailing spaces.

---

## ✅ Behavior on Different Inputs

Let’s test mentally:

1. `"Hello 42 from Zain"`

   * Words: `Hello`, `42`, `from`, `Zain` → **4**

2. `"   Hello   world   "`

   * Leading spaces → ignored (no word before first non-space)
   * Multiple spaces between words → still count only real words
   * Trailing spaces → ignored
   * Result: **2**

3. `"one\ttwo\nthree"`

   * Separated by tab and newline → still handled
   * Result: **3**

4. `""` (empty string) or `NULL`

   * Result: **0**

---

## 🏁 Main Function Overview

```c
int	main(void)
{
	char	*line;
	int		words;

	line = read_string();
	if (!line)
	{
		ft_putstr("Error: could not read string or empty input.\n");
		return (1);
	}
	words = count_words_in_string(line);
	ft_putstr("You entered: \"");
	ft_putstr(line);
	ft_putstr("\"\n");
	ft_putstr("Number of words: ");
	ft_putnbr(words);
	ft_putchar('\n');
	free(line);
	return (0);
}
```

Flow:

1. `line = read_string();`

   * Reads one full line from stdin into a dynamically allocated buffer.
2. If reading failed → print error and exit.
3. `words = count_words_in_string(line);`

   * Counts words separated by space/tab/newline.
4. Prints the line and the word count.
5. Frees the dynamically allocated `line`.

---

## 📝 Peer Evaluation Q&A

### **Q: How does the program avoid a fixed maximum input size?**

By starting with `buffer_size = 0` and calling `ft_realloc_str` whenever `length + 1 >= buffer_size`, the buffer grows as needed (32 → 64 → 128 → …). There is no predefined limit other than available memory.

---

### **Q: Why are both `start` and `current` pointers needed in `count_words_in_string`?**

* `current` walks over every character.
* `start` marks where a potential word begins.
* When we hit a separator, the distance between `start` and `current` tells us if there was at least one character → if yes, that’s one word.

This replaces the typical `in_word` boolean flag with pointer logic.

---

### **Q: Does the function treat multiple spaces as multiple words?**

No. Multiple spaces only cause multiple times where `*current` is a separator, but `current > start` is false after the first space, so no extra empty “words” are counted.

---

### **Q: Are numbers like `"42"` counted as words?**

Yes. The function doesn’t care what the characters are, only whether they are separated by spaces/tabs/newlines. `"Hello 42 from Zain"` → **4 words**.

---

### **Q: What happens if the user just presses Enter?**

* `read_string` sees `'\n'` immediately and returns either `NULL` or an empty string depending on behavior (here `buffer` stays `NULL` → we print the error).
* `count_words_in_string` isn’t called in that case.

---

