# 🧠 peer_explanation.md — ex01 `ft_map`

---

## 📌 Goal of the Exercise

Implement **`ft_map`**:

* You receive an **array of ints** (`tab`)
* You apply a **function `f`** to **each element in order**
* You return a **NEW array** containing the results

This is the C version of the “map” idea: **transform a list into a new list**.

---

## ✅ Required Prototype

```c
int *ft_map(int *tab, int length, int (*f)(int));
```

### What each parameter means

| Parameter | Type           | Meaning                                         |
| --------: | -------------- | ----------------------------------------------- |
|     `tab` | `int *`        | input array (original values)                   |
|  `length` | `int`          | number of elements in `tab`                     |
|       `f` | `int (*)(int)` | function that transforms one `int` into another |

Return value:

* `int *` → a pointer to the **new allocated array**
* `NULL` → if input is invalid or allocation fails

---

## 🧩 How Your Implementation Works

### Your `ft_map` (core logic)

```c
int	*ft_map(int *tab, int length, int (*f)(int))
{
	int	i;
	int	*result;

	if (!tab || !f || length <= 0)
		return (NULL);
	result = (int *)malloc(sizeof(int) * length);
	if (!result)
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = f(tab[i]);
		i++;
	}
	return (result);
}
```

### Step-by-step

1. **Input validation**

   * `!tab` → no array provided
   * `!f` → no function provided
   * `length <= 0` → no valid size to map
     → return `NULL`

2. **Allocate a new array**

   * `malloc(sizeof(int) * length)`
   * This creates space for `length` integers on the heap

3. **Loop through the array**

   * For each index `i`:

     * call `f(tab[i])`
     * store the result in `result[i]`

4. **Return the new array**

   * Caller owns this memory and must `free()` it.

---

## 🧠 Why We Need `malloc` Here

Because the function must return an array of results, and local arrays like:

```c
int result[length];
```

would be destroyed when the function returns (stack memory ends).
So we allocate on the **heap** using `malloc`, which survives after the function returns.

---

## 🔥 Function Pointer: The Key Concept

`int (*f)(int)` means:

* `f` is a pointer to a function
* the function takes **one `int`**
* and returns **one `int`**

Example from your test:

```c
int double_it(int n)
{
	return (n * 2);
}
```

So inside `ft_map`, this works:

```c
result[i] = f(tab[i]);
```

Because `f` behaves like a normal function.

---

## 🧪 What Your Test Demonstrates

Input:

```c
int array[] = {1, 2, 3, 4, 5};
```

Mapping with:

```c
double_it
```

Output should be:

```
2 4 6 8 10
```

And you correctly `free(new_array)` afterward ✅

---

## ⚠️ Common Mistakes (and how your code avoids them)

| Mistake                 | What happens                   | Your code          |
| ----------------------- | ------------------------------ | ------------------ |
| Returning a local array | dangling pointer               | ✅ uses `malloc`    |
| Not checking `malloc`   | crash / undefined behavior     | ✅ checks `!result` |
| Not checking `length`   | weird allocation / loop issues | ✅ `length <= 0`    |
| Forgetting `free`       | memory leak                    | ✅ freed in `main`  |

---

## ⏱️ Complexity

* **Time:** `O(length)` (one pass)
* **Memory:** `O(length)` (new array)

---

## 🧾 Peer Evaluation Q&A

**Q1: Why do we return a new array instead of modifying `tab`?**
Because the exercise asks to “return an array of all the return values.” Also it matches the “map” idea: original stays unchanged.

**Q2: Who frees the returned array?**
The **caller**. (`ft_map` allocates, caller must `free`.)

**Q3: What does `int (*f)(int)` exactly mean?**
A pointer to a function that takes one `int` and returns one `int`.

**Q4: Why return `NULL` for invalid input?**
So the caller can detect failure safely and avoid using invalid memory.

**Q5: What if `length` is 0?**
Your function returns `NULL` (because `length <= 0`). That’s a safe and consistent choice.

---
