````md
# ex02 — ft_ultimate_range

## 🎯 Goal

Implement the function `ft_ultimate_range` which allocates and fills an
array of integers containing all values between `min` and `max`.

Rules given by the subject:
- `min` is **included**
- `max` is **excluded**
- The function returns the **size of the array**
- The allocated array is returned through a **pointer to pointer**
- Only `malloc` is allowed

Prototype:
```c
int ft_ultimate_range(int **range, int min, int max);
````

---

## 🧠 Key difference from `ft_range`

Unlike `ft_range`, this function **does not return the array directly**.

* The array is returned via the parameter `int **range`
* The return value is used to indicate:

  * the size of the array
  * or an error status

This design separates **data output** from **status reporting**.

---

## 📏 Return value meaning

The function must return:

| Return value | Meaning                      |
| ------------ | ---------------------------- |
| `size > 0`   | Number of elements allocated |
| `0`          | `min >= max`, no allocation  |
| `-1`         | Allocation failed            |

---

## 🧩 Behavior when `min >= max`

If:

```c
min >= max
```

Then:

* `*range` must be set to `NULL`
* The function returns `0`

No memory allocation is performed.

---

## 🧮 How many elements to allocate?

The number of elements is:

```
size = max - min
```

Examples:

* `ft_ultimate_range(&arr, 3, 7)` → size = 4 → `[3, 4, 5, 6]`
* `ft_ultimate_range(&arr, -2, 3)` → size = 5 → `[-2, -1, 0, 1, 2]`

---

## 🧠 Pointer-to-pointer explanation

The parameter `int **range` allows the function to modify
the caller’s pointer.

Inside the function:

```c
*range = malloc(...)
```

After the function returns, the caller’s pointer points to
the newly allocated array.

This technique is commonly used in C APIs to return allocated data.

---

## 🧪 Memory model example

For:

```c
int *arr;
int size = ft_ultimate_range(&arr, 5, 8);
```

Memory result:

```
arr --> [ 5 ][ 6 ][ 7 ]
size = 3
```

---

## ⏱ Complexity

Let `n = max - min`

* Time complexity: `O(n)`
* Space complexity: `O(n)` (heap allocation)

---

## 🧠 Responsibility

The function allocates memory using `malloc`.

👉 The **caller is responsible for calling `free()`** on `*range`.

---

## ✅ Implementation

```c
#include <stdlib.h>

int ft_ultimate_range(int **range, int min, int max)
{
    int size;
    int i;

    if (min >= max)
    {
        *range = NULL;
        return 0;
    }

    size = max - min;
    *range = (int *)malloc(sizeof(int) * size);
    if (!*range)
        return -1;

    i = 0;
    while (i < size)
    {
        (*range)[i] = min + i;
        i++;
    }

    return size;
}
```

---

## 🧪 Example usage

```c
int *arr;
int size;

size = ft_ultimate_range(&arr, 3, 7);
/* arr contains: 3, 4, 5, 6 */
/* size == 4 */

free(arr);
```

---

## 📝 Peer Evaluation Q&A

**Q: Why use `int **range` instead of `int *range`?**
A: To allow the function to assign a new allocated array to the caller’s pointer.

---

**Q: Why return `0` when `min >= max`?**
A: Because there are no valid values to store, and no allocation should occur.

---

**Q: Why return `-1` on malloc failure?**
A: To clearly signal an allocation error, distinct from an empty range.

---

**Q: Who frees the allocated memory?**
A: The caller.

---

## ⭐ Bonus — Two valid ways to assign the range pointer

There are **two equivalent and valid ways** to implement `ft_ultimate_range`
when assigning the allocated array to the caller’s pointer.

Both approaches produce **identical behavior**.
The difference is **style and clarity**, not correctness.

---

### 🔹 Method 1 — Assign directly to `*range`

```c
*range = malloc(sizeof(int) * size);
if (!*range)
    return -1;

(*range)[i] = min + i;
````

**Characteristics**

* Allocates memory and assigns it to the caller’s pointer in one step
* Uses `(*range)[i]` to write values
* More explicit about pointer-to-pointer mechanics

**Pros**

* Clearly shows how `int **range` works
* Good for learning and understanding pointer indirection

**Cons**

* Slightly harder to read due to parentheses
* More verbose when accessing elements

---

### 🔹 Method 2 — Use a temporary pointer (`arr`)

```c
int *arr;

arr = malloc(sizeof(int) * size);
if (!arr)
    return -1;

*range = arr;

arr[i] = min + i;
```

**Characteristics**

* Uses a local pointer for allocation and filling
* Assigns the pointer to `*range` once
* Uses normal array indexing (`arr[i]`)

**Pros**

* Cleaner and more readable
* Avoids repeated `(*range)` syntax
* Common in real-world C code

**Cons**

* Slightly less explicit about pointer-to-pointer mechanics

---

### ✅ Conclusion

Both implementations are **100% correct** and acceptable.

| Aspect           | Direct `*range` | Temporary `arr` |
| ---------------- | --------------- | --------------- |
| Correctness      | ✅               | ✅               |
| Readability      | Medium          | High            |
| Pointer clarity  | High            | Medium          |
| Real-world style | Medium          | High            |

In practice, the **temporary pointer (`arr`) version is often preferred**
for readability, while the direct `*range` version is excellent for
learning how pointer-to-pointer assignment works.

---

```

