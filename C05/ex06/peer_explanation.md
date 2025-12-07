# 🧮 Exercise 06 — `ft_is_prime`

**Check if a number is prime**

---

## 📌 **What the function should do**

You must determine whether the integer `nb` is a **prime number**.
A prime number is a number **greater than 1** that has **no divisors except 1 and itself**.

The function must return:

| Case | Meaning               |
| ---- | --------------------- |
| `1`  | `nb` **is** prime     |
| `0`  | `nb` **is NOT** prime |

Prototype:

```c
int ft_is_prime(int nb);
```

---

# 🧠 Code (for reference)

```c
int ft_is_prime(int nb){
    int i;

    if (nb <= 1)
        return (0);

    i = 2;
    while (i * i <= nb)
    {
        if (nb % i == 0)
            return (0);
        i++;
    }
    return (1);
}
```

---

# 🔍 Step-by-Step Explanation

## 1️⃣ **Numbers ≤ 1 are NOT prime**

```c
if (nb <= 1)
    return (0);
```

* `0`, `1`, and negative numbers can’t be prime.
* This immediately filters invalid cases.

---

## 2️⃣ **Start checking divisors from 2**

```c
i = 2;
```

Why `2`?
Because:

* `1` divides everything → not useful
* `2` is the **first real divisor** we want to test.

---

## 3️⃣ **Why check only up to `i * i <= nb`? (Optimization)**

This is the key idea.

Imagine `nb = 31`.

If a number has a divisor greater than its square root,
then the *matching* divisor must be below the square root.
So checking until `sqrt(nb)` is enough.

### Example:

* √31 ≈ 5.56
* So we only need to test `2, 3, 4, 5`.

That’s exactly what `i * i <= nb` means —
we avoid using `sqrt()` (which is not allowed).

---

## 4️⃣ **If a divisor is found → NOT prime**

```c
if (nb % i == 0)
    return (0);
```

If `i` divides `nb` **with no remainder**, then:

* `nb` has another divisor → not prime
* Stop immediately, no need to test further

---

## 5️⃣ **If loop ends with no divisors → PRIME**

```c
return (1);
```

If we checked every possible divisor and found none,
the number **must be prime**.

---

# 👀 Visual Example: Checking `31`

| i | i*i | Check          | Result    |
| - | --- | -------------- | --------- |
| 2 | 4   | 31 % 2 → 1     | continue  |
| 3 | 9   | 31 % 3 → 1     | continue  |
| 4 | 16  | 31 % 4 → 3     | continue  |
| 5 | 25  | 31 % 5 → 1     | continue  |
| 6 | 36  | 36 > 31 → stop | loop ends |

No divisors found → **prime → return 1**

---

# 👀 Visual Example: Checking `90`

| i | i*i | Check                                             |
| - | --- | ------------------------------------------------- |
| 2 | 4   | 90 % 2 = 0 → divisor found → immediately return 0 |

---

# 🧪 Testing (main function)

```c
int main(){
    printf("%d\n", ft_is_prime(31));  // Output: 1  (Prime)
    printf("%d\n", ft_is_prime(90));  // Output: 0  (Not prime)
    return 0;
}
```

---

# 🎓 Peer Evaluation Q&A

### **Q: Why do we stop at `i * i <= nb` instead of checking all numbers up to `nb`?**

Because any factor above √nb would have already been discovered as a smaller factor. This reduces time from **O(n)** to **O(√n)**.

---

### **Q: Why do we return `0` as soon as a divisor is found?**

Prime means *no divisors*. Once one divisor exists, the number is confirmed not prime — no need to check more.

---

### **Q: Why do we start from `2`?**

`1` is not considered a valid divisor for primality testing.

---

### **Q: Why must nb > 1?**

Prime numbers are **defined** as integers greater than 1.

---


