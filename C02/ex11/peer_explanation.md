# 🧩 **Peer Explanation — `ft_putstr_non_printable` (Exercise 11)**

## 1️⃣ Overview

This function prints a string to the screen, **but with one rule**:

* If a character is **printable** (ASCII 32–126), print it normally.
* If a character is **non-printable** (ASCII 0–31 or 127), print it as:

```
\xxy   →   \0a, \07, \1f, etc.
```

Where `xx` is the **lowercase hexadecimal** value of the character.

Example from the subject:

```
Original:  Coucou\nTu vas bien ?
Output:    Coucou\0aTu vas bien ?
```

---

## 2️⃣ The Code (with separated declarations)

```c
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr_non_printable(char *str)
{
	int         i;
	const char *hex_digit;
	unsigned char c;

	hex_digit = "0123456789abcdef";
	i = 0;

	while (str[i] != '\0')
	{
		if (str[i] >= 32 && str[i] <= 126)
		{
			ft_putchar(str[i]);
		}
		else
		{
			c = (unsigned char)str[i];
			ft_putchar('\\');
			ft_putchar(hex_digit[c / 16]);
			ft_putchar(hex_digit[c % 16]);
		}
		i++;
	}
}
```

---

## 3️⃣ Line-by-Line Explanation

### ### 🔹 **`ft_putchar`**

A simple wrapper around `write`, required by the subject.

Used to avoid repeating `write(1, ...)` over and over.

---

### 🔹 **Variable declarations**

We separate declaration from assignment (as 42 prefers clean style):

```c
int         i;
const char *hex_digit;
unsigned char c;
```

* `i` → loop index
* `hex_digit` → lookup table for converting numbers → hex characters
* `c` → used to safely handle negative `char` values (important!)

Assignment occurs later:

```c
hex_digit = "0123456789abcdef";
i = 0;
```

---

### 🔹 **Printable check**

```c
if (str[i] >= 32 && str[i] <= 126)
	ft_putchar(str[i]);
```

Printable ASCII range:

* 32 = SPACE
* ...
* 126 = `~`

Everything in this range is printed as is.

---

### 🔹 **Non-printable conversion**

```c
c = (unsigned char)str[i];
ft_putchar('\\');
ft_putchar(hex_digit[c / 16]);
ft_putchar(hex_digit[c % 16]);
```

#### Why cast to `unsigned char`?

Because:

* On some systems, `char` is **signed**.
* Values like `'\n'` (10) are fine.
* But values ≥128 would become **negative**.
* Division and modulo on negative values gives **wrong hex digits**.

So:

```
(unsigned char)str[i] → ensures 0–255 range
```

#### How hex conversion works:

Example: newline (`'\n'`) = 10 decimal = `0x0a`

* High nibble → `10 / 16 = 0` → `'0'`
* Low nibble  → `10 % 16 = 10` → `'a'`

Becomes:

```
\0a
```

Exactly what the subject wants.

---

## 4️⃣ Mini Memory Diagram

For string:

```
"Coucou\n"
```

ASCII of `'\n'` = 10 = `0x0A`

Output becomes:

```
C o u c o u \ 0 a
```

---

## 5️⃣ Common Beginner Questions (Inserted Here)

### **Q1 — What are non-printable characters?**

Anything with ASCII:

```
0–31 or 127
```

Examples:

* `\n` → 10
* `\t` → 9
* `\r` → 13
* `\0` → 0
* DEL → 127

---

### **Q2 — Why not print them directly?**

Because many of them are **control characters**, not visible on screen.

Example:

* `\n` = newline
* `\t` = tab
* `\a` = “bell”
* `\r` = carriage return

Displaying them as hex makes output **predictable and safe**.

---

### **Q3 — Why use a lookup table `"0123456789abcdef"`?**

Because converting numbers to hex manually is slower and uglier.

Indexing into this string is instant:

```
hex_digit[10] → 'a'
hex_digit[15] → 'f'
```

---

### **Q4 — Why do we divide and modulo by 16?**

Hexadecimal is **base-16**.

A byte (0–255) splits into:

```
High nibble →  value / 16
Low nibble  →  value % 16
```

That produces **two hex digits**.

---

## 6️⃣ Summary

* Printable ASCII → print directly
* Non-printable → print as `\` + two lowercase hex digits
* Use `unsigned char` to avoid negative indexing
* Use a lookup table to generate hex quickly
* Declare variables separately for clean style

---

