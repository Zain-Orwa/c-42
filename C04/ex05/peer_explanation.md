````md
# 🧮 C04 – Exercise 05: `ft_atoi_base`  
### Peer Explanation – Indexing version + Pointer bonus

---

## 1. What the exercise wants

We have to re-implement `atoi`, but with **any base** given as a string.

```c
int ft_atoi_base(char *str, char *base);
````

* `str`  → the number written in some base (binary, hex, poneyvif, …).
* `base` → the characters that represent the digits of that base

  * e.g. `"01"` (base 2), `"0123456789ABCDEF"` (base 16), `"poneyvif"` (base 8).

The function must:

1. **Validate the base**

   * base length must be **≥ 2**
   * no `'+'`, `'-'`, spaces, or control whitespaces (`\t\n\v\f\r`)
   * no **duplicate characters**

2. Work like `ft_atoi`:

   * skip leading whitespaces
   * read all `'+'` / `'-'` signs and compute final sign
   * convert all valid digits until the first **invalid** character
   * return the integer result (with sign).

If the base is **invalid**, we must return `0`.

---

## 2. File overview

```c
void ft_putchar(char c);           // only for printing in tests
int  ft_strlen(char *str);         // length of a string
int  validate_base(char *base);    // checks whether base is valid
int  get_base_index(char c, char *base); // returns position of a digit in base
int  ft_atoi_base(char *str, char *base); // main function
int  main(void);                   // tests (not part of the exercise file)
```

> In the real `ft_atoi_base.c` you will only submit the **helpers + ft_atoi_base**.
> `ft_putchar` and `main` are only for testing.

---

## 3. Helper functions

### 3.1 `ft_strlen`

```c
int ft_strlen(char *str){
	int len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
```

* Classic length function.
* **Loop idea:** increment `len` until we hit the null terminator (`'\0'`).

We use it:

* to know `base_len` (needed for the conversion),
* and in `validate_base` to quickly reject bases of size `0` or `1`.

---

### 3.2 `validate_base`

```c
int validate_base(char *base){
	int i;
	int j;
	int base_len;

	base_len = ft_strlen(base);
	if (base_len <= 1)
		return (0);

	i = 0;
	while (base[i])
	{
		if (base[i] == ' ' || (base[i] == '+' || base[i] == '-')
				|| (base[i] >= 9 && base[i] <= 13))
			return (0);

		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
```

**Step-by-step:**

1. `base_len = ft_strlen(base);`

   * if length is `0` or `1` → **invalid** (cannot represent a number).

2. Loop over every character `base[i]`:

   * if it is a **space** `' '`
   * or a sign `'+'` or `'-'`
   * or a control whitespace: ASCII 9–13 (`'\t' '\n' '\v' '\f' '\r'`)
     → immediately return `0` (invalid base).

3. Check for **duplicates**:

   * inner loop `j = i + 1` → compare `base[i]` with all following chars
   * if we find the same char twice → invalid → return `0`.

If we pass all checks, we return `1` for a **valid base**.

---

### 3.3 `get_base_index`

```c
int get_base_index(char c, char *base){
	int i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}
```

* Looks for character `c` **inside** the `base` string.
* If found → returns its **index**, which is the digit value of `c` in that base.

  * Example: `get_base_index('A', "0123456789ABCDEF")` → `10`.
* If not found → returns `-1` → this means **“not a valid digit”**.

---

## 4. `ft_atoi_base` – indexing version

```c
int ft_atoi_base(char *str, char *base){
	int i;
	int sign;
	int result;
	int base_len;
	int digit_value;

	if (!validate_base(base))
		return (0);

	i = 0;
	sign = 1;
	result = 0;
	base_len = ft_strlen(base);

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;

	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}

	/* convert digits */
	while (str[i] != '\0')
	{
		digit_value = get_base_index(str[i], base);
		if (digit_value == -1)
			break;
		result = result * base_len + digit_value;
		i++;
	}

	return (result * sign);
}
```

### 4.1 Early base check

```c
if (!validate_base(base))
	return (0);
```

* If the base doesn’t follow the rules, don’t even try to parse the number.
* Returning `0` is exactly what the subject wants for invalid arguments.

---

### 4.2 Initialization

```c
i = 0;
sign = 1;
result = 0;
base_len = ft_strlen(base);
```

* `i`      → position in `str`.
* `sign`   → starts as `+1`; every `'-'` flips it (`sign = -sign`).
* `result` → accumulator, starts at `0`.
* `base_len` → how many digits the base has (2 for binary, 10 for decimal, 16 for hex, …).

---

### 4.3 Skip leading whitespaces

```c
while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	i++;
```

* Same family as `ft_atoi`:

  * `' '` (space)
  * `'\t'` `'\n'` `'\v'` `'\f'` `'\r'` (ASCII 9–13).
* We advance `i` until we reach the first non-whitespace character.

---

### 4.4 Handle signs

```c
while (str[i] == '+' || str[i] == '-')
{
	if (str[i] == '-')
		sign = -sign;
	i++;
}
```

* We accept **multiple signs** in a row (`---+--+42` style).
* For each `'-'` we flip the sign:

  * one `'-'` → `sign = -1`
  * two `'-'` → back to `+1`
  * three `'-'` → `-1` again
    → same logic as normal `ft_atoi`.

---

### 4.5 Convert digits

```c
while (str[i] != '\0')
{
	digit_value = get_base_index(str[i], base);
	if (digit_value == -1)
		break;
	result = result * base_len + digit_value;
	i++;
}
```

* For each character:

  1. `digit_value = get_base_index(str[i], base);`

     * if the char doesn’t exist in `base` → returns `-1` → we **stop** the loop.
  2. If valid:

     * we **shift** the old result to the left in this base:
       `result = result * base_len`
     * then add the new digit: `+ digit_value`.

**Example:** `"2A"` in hex `"0123456789ABCDEF"`

* `base_len = 16`
* `'2'` → value `2`
  `result = 0 * 16 + 2 = 2`
* `'A'` → value `10`
  `result = 2 * 16 + 10 = 32 + 10 = 42`

So `ft_atoi_base("2A", "0123456789ABCDEF")` → `42`.

---

### 4.6 Apply sign

```c
return (result * sign);
```

* If we saw an odd number of `'-'` signs → `sign = -1`.
* If even (or zero) `'-'` → `sign = 1`.

So the final value is `result` with the correct sign.

---

## 5. Quick look at the `main` tests

The `main` covers:

1. Decimal `"   ---+--+42"` in base `"0123456789"`
2. Binary `"   +++101010"` in base `"01"`
3. Hex `"   2A"` in base `"0123456789ABCDEF"`
4. Octal `"   52"` in base `"01234567"`
5. Custom `"   vn"` in base `"poneyvif"`
6. Negative hex `"   -2A"`
7. Zero `"0"`
8. Input with invalid tail `"2AZZZ"` (stops at `Z`)
   9–13. Various invalid bases → must return `0`

Good coverage: whitespace, signs, different bases, invalid bases, and stopping at first invalid digit.

---

## 6. Peer evaluation Q&A

### Q1. What happens if the base is invalid?

```c
if (!validate_base(base))
	return (0);
```

* `validate_base` returns `0` → we directly return `0` from `ft_atoi_base`.
* No parsing is done at all.

---

### Q2. Why do we check for spaces and ASCII 9–13?

* To match the behavior of `ft_atoi`: skip all **standard whitespaces**:

  * `' '` (space)
  * `'\t'` (9), `'\n'` (10), `'\v'` (11), `'\f'` (12), `'\r'` (13).

---

### Q3. Why don’t we stop after the first sign?

Because the subject of `ft_atoi` in 42 allows **multiple signs**.
We must support strings like:

```c
"---+--+42"
```

So we loop while we see `+` or `-` and update the `sign` accordingly.

---

### Q4. Why do we stop when `get_base_index` returns `-1`?

That means the current character is **not part of the base**,
so from this point the rest of the string is **ignored**, just like classical `atoi` stops on the first non-digit.

Example:

```c
ft_atoi_base("2AZZZ", "0123456789ABCDEF");
```

* `2` and `A` are valid
* `Z` is not in the base → stop there
  → we convert only `"2A"`.

---

### Q5. Why is `base_len` stored in a variable?

```c
base_len = ft_strlen(base);
```

* To **avoid calling `ft_strlen` inside the loop** again and again.
* This keeps the complexity of the digit loop **O(n)** instead of adding an extra unnecessary loop each step.

---

### Q6. What is the time complexity of `ft_atoi_base`?

* `validate_base` is roughly **O(B²)** because of the duplicate check (`B` = base length).
* Conversion of `str` is **O(N × B)** in the worst case if you count the digit search `get_base_index` (linear in base length).
* For typical small bases (2, 8, 10, 16) this is perfectly fine.

---

## 7. Bonus: pointer version of `ft_atoi_base`

Here is a **pointer-style** implementation that does exactly the same logic,
but instead of an index `i`, we walk directly with a `char *ptr`.

```c
int	ft_atoi_base_ptr(char *str, char *base)
{
	int		sign;
	int		result;
	int		base_len;
	int		digit_value;
	char	*ptr;

	if (!validate_base(base))
		return (0);
	sign = 1;
	result = 0;
	base_len = ft_strlen(base);
	ptr = str;

	/* skip whitespaces */
	while (*ptr == ' ' || (*ptr >= 9 && *ptr <= 13))
		ptr++;

	/* handle signs */
	while (*ptr == '+' || *ptr == '-')
	{
		if (*ptr == '-')
			sign = -sign;
		ptr++;
	}

	/* convert digits */
	while (*ptr != '\0')
	{
		digit_value = get_base_index(*ptr, base);
		if (digit_value == -1)
			break;
		result = result * base_len + digit_value;
		ptr++;
	}
	return (result * sign);
}
```

> Note: this version **reuses** the same helpers:
> `ft_strlen`, `validate_base`, `get_base_index`.

---

## 8. Comparison: indexing vs. pointer version

| Aspect             | Indexing version                        | Pointer version                               |
| ------------------ | --------------------------------------- | --------------------------------------------- |
| Position tracking  | Uses an `int i` and accesses `str[i]`   | Uses a `char *ptr` and accesses `*ptr`        |
| Initialization     | `i = 0;`                                | `ptr = str;`                                  |
| Move to next char  | `i++;`                                  | `ptr++;`                                      |
| Readability        | Very clear for beginners                | More “classic C style” once you’re used to it |
| Risk of off-by-one | Need to be careful with `i` vs `str[i]` | Slightly simpler: you always look at `*ptr`   |
| Performance        | Practically the same for this exercise  | Practically the same                          |
| Style              | Feels close to array logic              | Feels close to pointer arithmetic / parsing   |


