````md
# ex01 — ft_range

## 🎯 Goal

Implement the function `ft_range` which returns an array of integers
containing all values between `min` and `max`.

Rules given by the subject:
- `min` is **included**
- `max` is **excluded**
- If `min >= max`, the function must return `NULL`
- Only `malloc` is allowed

Prototype:
```c
int *ft_range(int min, int max);
````

---

## 🧠 Understanding the problem

The function must:

1. Allocate an array of integers on the **heap**
2. Fill it with consecutive values starting from `min`
3. Stop **before** reaching `max`
4. Return a pointer to the allocated array

Example:

```c
ft_range(3, 7);
```

Expected result:

```
[3, 4, 5, 6]
```

---

## 📏 How many elements to allocate?

The number of elements is:

```
max - min
```

Examples:

* `ft_range(3, 7)` → `7 - 3 = 4` elements
* `ft_range(-2, 3)` → `3 - (-2) = 5` elements

If:

```c
min >= max
```

then there are **no valid values**, so the function returns `NULL`.

---

## 🧩 Memory model

For:

```c
ft_range(5, 8)
```

Memory layout:

```
index:  0  1  2
value:  5  6  7
```

Important:

* Array indices always start at `0`
* Stored values start at `min`

---

## ⏱ Complexity

Let `n = max - min`

* Time complexity: `O(n)`
* Space complexity: `O(n)` (heap allocation)

---

## 🧠 Responsibility

The function allocates memory using `malloc`.

👉 The **caller is responsible for calling `free()`** on the returned pointer.

---

## ✅ Implementation

```c
#include <stdlib.h>

int *ft_range(int min, int max)
{
    int *range;
    int size;
    int i;

    if (min >= max)
        return NULL;

    size = max - min;
    range = (int *)malloc(sizeof(int) * size);
    if (!range)
        return NULL;

    i = 0;
    while (i < size)
    {
        range[i] = min + i;
        i++;
    }

    return range;
}
```

---

## 🧪 Example usage

```c
int *arr = ft_range(3, 7);
/* arr contains: 3, 4, 5, 6 */
free(arr);
```

---

## 📝 Peer Evaluation Q&A

**Q: Why return `NULL` when `min >= max`?**
A: Because there are no valid integers between `min` and `max` in that case.

---

**Q: Why allocate `max - min` elements?**
A: Because `min` is included and `max` is excluded.

---

**Q: Why does indexing start from `0`?**
A: Array indices in C always start from `0`, even if the stored values start at `min`.

---

**Q: Who frees the allocated memory?**
A: The caller of `ft_range`.

---

```

