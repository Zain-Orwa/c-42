````markdown
# 🧩 Peer Explanation – `ft_putnbr`

## 🎯 Goal of the Exercise

The function must print any number that fits inside an **`int`**, without using anything except:

- `write`
- basic arithmetic
- recursion

Prototype:

```c
void	ft_putnbr(int nb);
````

The function must correctly handle:

* positive integers
* negative integers
* `0`
* **the edge case**: `-2147483648` (`INT_MIN`)

---

# ✅ Final Implementation (Pointer-free recursion)

```c
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	long	num;

	num = (long)nb;
	if (num < 0)
	{
		ft_putchar('-');
		num *= -1;
	}
	if (num >= 10)
		ft_putnbr(num / 10);
	ft_putchar((num % 10) + '0');
}
```

---

# 🧠 Step-By-Step Logic

## 1️⃣ Promote to a larger type: `long num = nb;`

Why do we do this?

* A signed 32-bit integer can store:
  **−2147483648 to +2147483647**
* But if you try to negate the smallest value:

```
-(-2147483648) = +2147483648  ← cannot fit in int
```

So we convert to `long` first:

```c
num = (long)nb;
```

Now `num` can safely become **+2147483648** if needed.

---

## 2️⃣ Handle negative numbers

```c
if (num < 0)
{
	ft_putchar('-');
	num *= -1;
}
```

* Print the minus sign.
* Convert the number to a positive one so the rest of the code is simple.

Example:
`nb = -42`

```
print '-'
num becomes 42
```

---

## 3️⃣ Recursive printing: “unpack the digits”

If the number has multiple digits:

```c
if (num >= 10)
	ft_putnbr(num / 10);
```

This recursive call prints all digits **before the last one**.

Then:

```c
ft_putchar((num % 10) + '0');
```

prints the **last digit**.

### 🧠 Example: printing 1234

```
ft_putnbr(1234)
 └→ ft_putnbr(123)
     └→ ft_putnbr(12)
         └→ ft_putnbr(1)
             prints '1'
         prints '2'
     prints '3'
 prints '4'
```

Output:

```
1234
```

---

# 🧨 Why This Version Correctly Handles INT_MIN

`INT_MIN = -2147483648`

Normal approach:

* multiply by `-1` ❌ **would overflow**

Your approach:

```c
long num = (long)nb;
num *= -1;
```

Now:

* num can store `2147483648` safely
* recursion prints it digit by digit
* no special case needed

This is a **perfectly valid alternative** to the classical Piscine solution.

---

# ⚠️ Important: The Warning You Saw

You tested your function like this:

```c
ft_putnbr(2147483648);
```

But this is **NOT allowed**, because:

* The function prototype takes **int**
* `2147483648` does **not** fit in an `int`
* C must convert it from `long` → `int`

Compiler warning:

> implicit conversion from 'long' to 'int' changes value from 2147483648 to -2147483648

### 🧠 What actually happens?

1. `2147483648` is too large for an `int`
2. C tries to convert it to `int`
3. This causes integer **wrap-around**
4. The actual `int` value passed to the function becomes **−2147483648**

So you're **not testing your function**, you're testing how C **wraps integers outside the valid range**.

This is why the warning appears —
the value literally **cannot** be represented in the parameter type.

---

# ✔️ Correct test values (must fit in int)

```c
ft_putnbr(0);
ft_putnbr(42);
ft_putnbr(-42);
ft_putnbr(2147483647);
ft_putnbr(-2147483648);
```

Anything outside:

```
< -2147483648  or  > 2147483647
```

will give warnings or undefined behavior.

---

# 📘 Summary for Peer Evaluation

* The solution uses recursion to print digits from left to right.
* `long` promotion allows safe handling of `INT_MIN`.
* No illegal library functions are used (only `write`).
* The logic works for all values that fit inside an `int`.
* The warning shown is due to the **test code**, not the function itself.
* The function prototype restricts inputs to **int range only**.

---


