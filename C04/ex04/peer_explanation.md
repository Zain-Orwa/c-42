# **peer_explanation.md — ft_putnbr_base**

---

# 🧩 **Exercise 04 — ft_putnbr_base**

*Print an integer using any base representation*

---

## 📘 **1. Exercise Goal**

The goal of `ft_putnbr_base` is to print an integer (`int nbr`) using **any base system** chosen by the user.
The base system is provided as a **string of characters**, where:

* the **length** of the string defines the base (binary, octal, decimal, hex, custom…)
* the **characters** inside represent the digits of that base

### Examples of valid bases:

| Base String          | Meaning                | Base Length |
| -------------------- | ---------------------- | ----------- |
| `"01"`               | binary                 | 2           |
| `"01234567"`         | octal                  | 8           |
| `"0123456789"`       | decimal                | 10          |
| `"0123456789ABCDEF"` | hexadecimal            | 16          |
| `"poneyvif"`         | custom octal-like base | 8           |

The function must:

* Validate the base
* Handle negative numbers
* Print digits using `write()`
* Use **recursion** to print multi-digit numbers from most significant to least significant

---

## 📌 **2. Code of the Function**

```c
void ft_putchar(char c){
	write(1, &c, 1);
}

int ft_strlen(char *str){
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int validate_base(char *base){
	int i;
	int j;
	int base_len;

	base_len = ft_strlen(base);
	if (base_len <= 1)
		return (0);

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);

		j = i + 1;
		while (base[j] != '\nu0000')
		{
			if (base[i] == base[j])
				return (0);
			j++;	
		}
		i++;
	}
	return (1);
}

void ft_putnbr_base(int nbr, char *base){
	int  base_len;
	long long_nbr;

	if (!validate_base(base))
		return;

	long_nbr = (long)nbr;
	if (long_nbr < 0){
		ft_putchar('-');
		long_nbr = -long_nbr;
	}

	base_len = ft_strlen(base);

	if (long_nbr >= base_len)
		ft_putnbr_base(long_nbr / base_len, base);

	ft_putchar(base[long_nbr % base_len]);
}
```

---

# 🧠 **3. Why This Function Exists**

### ❓ How is this different from `ft_putnbr`?

`ft_putnbr` prints a number *only* in decimal (base 10) using the characters `'0'`–`'9'`.

`ft_putnbr_base` prints the same number in **ANY base**:

* binary
* octal
* hex
* your own custom alphabet of characters
* even ASCII-art digit sets

This allows you to control:

* how the number is represented
* what symbols represent the digits
* which base is used

---

# 🔤 **4. Why `base` is a string (`char *base`) instead of an integer**

This is one of the most important conceptual points.

### If the base was an int (like `2`, `8`, `10`, `16`), we would only know:

* the numeric base
* but we would NOT know what characters to use

Hexadecimal example:

```c
16
```

But do we print:

* `0–9 A–F`
* or `0–9 a–f`
* or `🌟😂🔥💀`
* or `ponEYVIF`?

We have no way to know.

### With a string, we know both:

1. The **base length**
2. The **characters** used to represent digits

Example:

```c
"0123456789ABCDEF"
```

* Length = 16
* Characters = exactly what to print for each digit

This makes the function extremely flexible:

```c
ft_putnbr_base(42, "01");            // binary
ft_putnbr_base(42, "poneyvif");      // custom base-8
ft_putnbr_base(42, "XO");            // X/O style
ft_putnbr_base(42, "@#$%");          // weird base-4
```

---

# 🧪 **5. Base Validation Logic**

A base is valid ONLY when:

* length ≥ 2
* contains no `'+'` or `'-'`
* contains no duplicates

### 🔍 Why do we use `j = i + 1`?

**Q1 Answer**

`i` loops over each character.
`j` checks all characters *after* `i`.

This prevents:

* comparing a character to itself
* repeating comparisons we already performed

Analogy:

> To check if a guest list has duplicates:
>
> * Check guest 0 vs 1,2,3
> * Check guest 1 vs 2,3
> * Check guest 2 vs 3

This is exactly what `j = i + 1` represents.

---

# 🔢 **6. Why We Still Need `base_len` Even After Validating**

**Q2 Answer**

`validate_base` only answers the question:

> “Is this base valid?” → yes/no

But inside `ft_putnbr_base` we need:

```c
if (long_nbr >= base_len)
```

and:

```c
ft_putchar(base[long_nbr % base_len]);
```

So we still need `base_len` for **mathematics**.

---

# 🌍 **7. Custom Bases (e.g., `"poneyvif"`)**

**Q5 Answer**

You can choose **any characters you want** for your base, as long as:

* no duplicates
* length ≥ 2
* no `+` or `-`

There are NO other rules.

So `"poneyvif"` is valid.
You could also use:

* `"ABCDEFGH"`
* `"XO"`
* `"0123456789abcdef"`
* `"*-+"` (INVALID → contains `+`)
* `"/|\-"` (INVALID → contains `-`)
* `"aa"` (INVALID → duplicates)

---

# 🔁 **8. Understanding the Recursion**

### The exact recursion logic:

```c
if (long_nbr >= base_len)
	ft_putnbr_base(long_nbr / base_len, base);

ft_putchar(base[long_nbr % base_len]);
```

### When does recursion stop?

When:

```
long_nbr < base_len
```

Because the number fits into one digit.

### Does recursion skip printing?

No.
It simply **waits** until all deeper calls finish.

Analogy:

> You want to print “42”.
>
> You must print the tens digit (4) before the ones digit (2).
> So you temporarily pause printing “42” and first print “4”.
> After finishing, you return and print “2”.

### Detailed trace of printing `42` in base 10:

```
ft_putnbr_base(42):

   42 >= 10 → deeper call with 4
       ft_putnbr_base(4)
           4 < 10 → print '4'
           return
   now print '2'
```

Output:
`42`

---

# 🔬 **9. What does “return to Call 1” mean?**

(This was your deepest confusion.)

**Q7 Answer**

When one recursive call starts another call:

```
Call 1 → Call 2
```

Call 1 is **paused**, not erased.

When Call 2 finishes, the CPU returns to the exact place Call 1 left off.

In our example:

```
Call 1: ft_putnbr_base(42)
   paused here:
        ft_putnbr_base(4);   <-- waiting
        ft_putchar(...);     <-- will continue here
```

Call 2 happens (`ft_putnbr_base(4)` prints `'4'`).
When Call 2 ends:

* Call 1 resumes
* prints `'2'`
* finishes

Think of function calls as **stacked layers**.
The topmost must finish before the lower one continues.

### Analogy

You are reading a book.
You come across a term you don't understand → open another book to check it.
After finishing that book, you close it and resume the exact page in the first book.

---

# 👥 **10. Does a recursive call “copy the function”?**

**Q8 Answer**

No.
The function **code** is not copied.

But each call creates a new **stack frame**, which contains:

* its own parameters
* its own local variables
* its own return address

Analogy:

> Many people can read the same book at the same time.
> The book is one copy (function code).
> But each person has their own notebook (stack frame) for notes.

---

# 🧮 **11. Why We Convert to Long**

Handling `INT_MIN`:

```
nbr = -2147483648
```

We cannot do:

```
nbr = -nbr;
```

Because `+2147483648` does not fit in `int`.

So we convert to `long`:

```c
long_nbr = (long)nbr;
long_nbr = -long_nbr;   // safe
```

---

# 🔚 **12. Summary**

* `ft_putnbr_base` prints an integer in ANY base using `write()`
* The base is a **string**, giving both the base length and digit symbols
* The base is validated for:

  * length ≥ 2
  * no duplicates
  * no `+` or `-`
* Recursion ensures digits print in the correct order
* `long` protects us from `INT_MIN` overflow
* Custom bases like `"poneyvif"` are allowed
* Recursion does NOT copy the function, only stack frames

---

# 🎯 **13. What You Should Understand After This Exercise**

* How base conversion works
* How recursion controls order of printing
* Why modulo gives the last digit
* Why division removes the last digit
* How to validate input
* Why base must be a string
* How stack frames behave in recursion

---

***Section2***

1. **Comparison with `ft_putnbr` and `itoa`**
2. **Common mistakes and how to fix them**

They follow the same formatting style as the rest of the peer_explanation you already have.

---

# ✅ **1.Comparison with `ft_putnbr` and `itoa`**

## 🔍 **Comparison with `ft_putnbr`**

`ft_putnbr(int nb)` prints an integer **only in decimal (base 10)** using the digits `'0'` to `'9'`.

| Feature                     | `ft_putnbr` | `ft_putnbr_base`                     |
| --------------------------- | ----------- | ------------------------------------ |
| Base                        | Always 10   | Any base (length 2–∞)                |
| Digit symbols               | `'0'`–`'9'` | Defined by the user via `char *base` |
| Negative handling           | Yes         | Yes                                  |
| Recursion                   | Yes         | Yes                                  |
| Output method               | `write()`   | `write()`                            |
| Flexibility                 | ❌ Limited   | ✔ Very flexible                      |
| Can print hex, binary, etc. | ❌ No        | ✔ Yes                                |

### Summary:

**`ft_putnbr_base` is a general version of `ft_putnbr`.**
If you pass `"0123456789"` as the base, `ft_putnbr_base` behaves almost exactly like `ft_putnbr`.

---

## 🔍 **Comparison with `itoa`**

`itoa()` is a non-standard function (not in the C standard library).
It converts an integer into a **string** (null-terminated), but:

* It only supports bases up to 36.
* Digits above 9 must be represented with `'A'`–`'Z'` or `'a'`–`'z'`.
* It does **not** print; it returns a `char *`.

### Example prototype (varies by system):

```c
char *itoa(int value, char *str, int base);
```

### Key differences:

| Feature                   | `itoa`               | `ft_putnbr_base`                              |
| ------------------------- | -------------------- | --------------------------------------------- |
| Output                    | Returns a string     | Prints characters to stdout                   |
| Maximum base              | 36                   | Unlimited (as long as `base` string is valid) |
| Digit set                 | Fixed (`0–9`, `A–Z`) | Custom per user string                        |
| Base type                 | integer              | string                                        |
| Standard?                 | ❌ No                 | Not standard either, but 42 requires it       |
| Handling of invalid bases | Behavior varies      | Strict validation (length, duplicates, +, -)  |

### Summary:

**`ft_putnbr_base` is more flexible than `itoa`** because you can use *any* character set to represent digits. But it **does not return a string**—it only prints.

---

# ✅ **2.Common Mistakes and How to Fix Them**


---

## ❌ **Mistake 1 — Not validating the base**

```c
ft_putnbr_base(42, "");
ft_putnbr_base(42, "0");
ft_putnbr_base(42, "112");
ft_putnbr_base(42, "01+");
```

**Symptoms:**

* Wrong output
* Infinite recursion
* Crashes

**Fix:**
Always check:

```c
if (!validate_base(base))
    return;
```

---

## ❌ **Mistake 2 — Using `int` instead of `long`**

If you do:

```c
int n = nbr;
if (n < 0)
    n = -n;  // ❌ INT_MIN overflow
```

This causes **undefined behavior** for `-2147483648`.

**Fix:**
Use long:

```c
long long_nbr = (long)nbr;
if (long_nbr < 0)
    long_nbr = -long_nbr;
```

---

## ❌ **Mistake 3 — Printing digits in reverse order**

Beginners often do:

```c
ft_putchar(base[n % base_len]);
ft_putnbr_base(n / base_len, base);
```

This prints least significant digits first → **wrong order**.

**Correct order:**

```c
if (long_nbr >= base_len)
    ft_putnbr_base(long_nbr / base_len, base);

ft_putchar(base[long_nbr % base_len]);
```

---

## ❌ **Mistake 4 — Forgetting to print `-` for negative numbers**

**Fix:**

```c
if (long_nbr < 0)
{
    ft_putchar('-');
    long_nbr = -long_nbr;
}
```

---

## ❌ **Mistake 5 — Using the base length before validating the base**

If you do:

```c
int base_len = ft_strlen(base);
if (!validate_base(base))
    return;
```

You compute base_len for invalid bases (not harmful but wrong order).

**Cleaner version:**

```c
if (!validate_base(base))
    return;

base_len = ft_strlen(base);
```

---

## ❌ **Mistake 6 — Not understanding why `j = i + 1`**

Some students incorrectly do:

```c
j = 0;  // ❌ inefficient
```

Or:

```c
j = i;  // ❌ always compares with itself
```

**Correct logic:**
You only want to compare with characters *after* the current character.

---

## ❌ **Mistake 7 — Forgetting that the base is a “digit alphabet”**

Some confuse `base` with “numeric base”.

**Correct concept:**
`char *base` is a **mapping** from digit value → symbol.

Example:

```c
base[10] = 'A'
```

in hex.

---

## ❌ **Mistake 8 — Confusing recursion with loops or thinking recursion copies the function**

**Fix:**
Understand that recursion:

* does NOT copy the function
* creates a new stack frame
* pauses the caller until the callee returns

Analogy:
One book, many readers; each has their own notebook.

---

