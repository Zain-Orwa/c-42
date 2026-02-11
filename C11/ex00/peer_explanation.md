## 🧠 peer_explanation.md — C11 / Chapter III / ex00 — `ft_foreach`

---

### ✅ Goal of the exercise

You must create **`ft_foreach`** that:

* Takes an **array of `int`**
* Takes its **length**
* Takes a **function pointer** `f`
* Applies `f` to **each element**, **in array order** (from index `0` to `length - 1`)

Prototype:

```c
void	ft_foreach(int *tab, int length, void (*f)(int));
```

---

### 📌 Key idea: function pointers (the “callback”)

`void (*f)(int)` means:

* `f` is a **pointer to a function**
* That function takes **one `int` argument**
* And returns **nothing (`void`)**

So `f(tab[i])` means: “call the function `f` on the current array element”.

---

### 🔍 Parameters meaning

```text
+---------+------------------+-------------------------------------------+
| Name    | Type             | Meaning                                   |
+---------+------------------+-------------------------------------------+
| tab     | int *            | Pointer to the first element of the array |
| length  | int              | Number of elements to process             |
| f       | void (*)(int)    | Function to apply to each element         |
+---------+------------------+-------------------------------------------+
```

---

### 🧩 How your `ft_foreach` works (step-by-step)

Your code:

```c
void ft_foreach(int *tab, int length, void(*f)(int))
{
    int i;

    i = 0;
    while (i < length)
    {
        f(tab[i]);
        i++;
    }
}
```

What happens:

1. Start at `i = 0`
2. While `i < length`:

   * Read `tab[i]`
   * Call the function: `f(tab[i])`
   * Move to next index

This guarantees **order is preserved**.

---

### 🧪 Your test setup (helpers + demo)

You included these helpers to *test* `ft_foreach`:

* `ft_putchar` → prints 1 character
* `ft_putnbr` → prints an integer (handles negatives, and `INT_MIN`)
* `main` → creates an array and calls `ft_foreach(array, size, &ft_putnbr)`

So you’re using `ft_putnbr` as the callback function.

---

### ⚠️ Note about your demo output

In `main` you do:

```c
ft_putchar('[');
ft_foreach(array, size, &ft_putnbr);
ft_putchar(']');
```

`ft_putnbr` prints numbers **without separators**, so the output becomes something like:

```
[42-12307892147483647-2147483648]
```

That’s not wrong for the exercise — it’s just how your demo prints.
If you wanted readability, you’d print separators inside the callback (or use a different callback).

---

### 🧷 Common edge cases (good to know)

In many real projects you’d protect against:

* `tab == NULL`
* `f == NULL`
* `length <= 0`

But 42 often tests basic logic here, so your loop logic is the main point.

A “safer” version would start with:

```c
if (!tab || !f || length <= 0)
    return;
```

(Only add this if allowed/expected in your pool rules.)

---

## 🧑‍⚖️ Peer Evaluation Q&A

**Q1: What does `void (*f)(int)` mean exactly?**
A: It means `f` points to a function that takes one `int` and returns `void`.

**Q2: Why do we pass `&ft_putnbr`?**
A: Because `ft_putnbr` matches the required signature: it takes an `int` and returns `void`. Passing it lets `ft_foreach` call it on every element.

**Q3: Does `ft_foreach` modify the array?**
A: No. It only reads `tab[i]` and sends the value to `f`.

**Q4: In what order are elements processed?**
A: From index `0` up to `length - 1`, because `i` increments forward.

**Q5: What happens if `length` is 0 or negative?**
A: The loop condition `i < length` fails immediately, so nothing is called.

**Q6: Why is this useful in real code?**
A: It lets you reuse the same “loop over array” logic while changing behavior by passing different functions (print, transform, check, etc.).

---

