# 🧮 Exercise 07 — `ft_find_next_prime`

**Find the next prime number greater or equal to `nb`**

---

## 📌 File: `ft_find_next_prime.c`

Allowed functions: **None**

Your task:
Create a function that returns the **next prime number** that is **≥ nb**.
If `nb` itself is prime ⇒ return `nb`.

Prototype:

```c
int ft_find_next_prime(int nb);
```

---

# 🔍 Full Code (for reference)

```c
int ft_is_prime(int nb){
    int i;

    if (nb <= 1)
        return (0);

    i = 2;
    while (i <= nb / i)
    {
        if (nb % i == 0)
            return (0);
        i++;
    }
    return (1);
}

int ft_find_next_prime(int nb){
    if (nb <= 2)
        return (2);

    while (!ft_is_prime(nb))
        nb++;

    return (nb);
}
```

---

# 🧠 Explanation

We break the exercise into two logical parts:

---

# 1️⃣ Understanding `ft_is_prime`

This helper function checks if a number is prime.

### 🔸 **Numbers ≤ 1 are NOT prime**

```c
if (nb <= 1)
    return (0);
```

---

### 🔸 **Why `i <= nb / i` instead of `i * i <= nb`?**

Both mean the same thing:

* A divisor only needs to be checked up to `sqrt(nb)`
* `nb / i` avoids overflow that can happen with `i * i`

For example:
If `i = 5` and `nb = 31`, check:

```
5 <= 31 / 5 → 5 <= 6 → true → still under sqrt(31)
```

This is a safe way of checking primes with no risk of `i * i` exceeding int range.

---

### 🔸 **If any divisor divides nb → NOT prime**

```c
if (nb % i == 0)
    return (0);
```

If we find a divisor, we stop early.

---

### 🔸 **No divisor found → prime**

```c
return (1);
```

---

# 2️⃣ Understanding `ft_find_next_prime`

This is the main function for the exercise.

### 🔸 Case 1: nb ≤ 2

The smallest prime number is **2**.

```c
if (nb <= 2)
    return (2);
```

Even for negative values (ex: -50), the answer must be **2**.

---

### 🔸 Case 2: nb > 2

We loop until we find a prime.

```c
while (!ft_is_prime(nb))
    nb++;
```

This means:

* If `nb` is not prime → increase it by 1
* Check again
* Continue until a prime is found
* Finally return that prime

Examples:

* nb = 6 → check 6 → not prime → check 7 → prime → return 7
* nb = 13 → check 13 → it IS prime → return 13
* nb = 25 → 25 no → 26 no → 27 no → 28 no → 29 yes → return 29

---

# 👀 Visual Flow Example

Let’s trace `ft_find_next_prime(25)`:

| Step | nb | Is it prime? | Action    |
| ---- | -- | ------------ | --------- |
| 1    | 25 | no           | nb++ → 26 |
| 2    | 26 | no           | nb++ → 27 |
| 3    | 27 | no           | nb++ → 28 |
| 4    | 28 | no           | nb++ → 29 |
| 5    | 29 | YES          | return 29 |

---

# 🧪 Output from main()

```c
printf("What is the next prime of -3? %d\n", ft_find_next_prime(-3));
printf("What is the next prime of 6? %d\n", ft_find_next_prime(6));
printf("What is the next prime of 13? %d\n", ft_find_next_prime(13));
printf("What is the next prime of 25? %d\n", ft_find_next_prime(25));
printf("What is the next prime of 84? %d\n", ft_find_next_prime(84));
```

Expected results:

| Input | Next Prime |
| ----- | ---------- |
| -3    | 2          |
| 6     | 7          |
| 13    | 13         |
| 25    | 29         |
| 84    | 89         |

---

# 🎓 Peer Evaluation Q&A

### **Q: Why do we return 2 for all numbers ≤ 2?**

Because **2 is the first prime number**.

---

### **Q: Why do we use nb++ instead of starting always from 2?**

Because the exercise requires the **next prime greater or equal to nb**, not the next prime starting from zero.

---

### **Q: What happens if nb is already prime?**

The while condition fails immediately:
`!ft_is_prime(nb)` → false → we return nb.

---

### **Q: Why does ft_is_prime stop at nb / i?**

It avoids overflow and still covers all possible divisors up to sqrt(nb).

---

