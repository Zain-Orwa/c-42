# 🧠 peer_explanation.md — ex02 `ft_any`

---

## 🎯 Goal of the Exercise

Implement the function **`ft_any`**, which answers a simple question:

👉 **“Does ANY element in this string array satisfy a condition?”**

* If at least one element makes function `f` return **non-zero**,
  → return **1**
* Otherwise
  → return **0**

This is the C equivalent of the logical idea:

> “Is there at least one match?”

---

## ✅ Required Prototype

```c
int ft_any(char **tab, int (*f)(char *));
```

### Meaning of the parameters

| Parameter | Type             | Meaning                         |
| --------: | ---------------- | ------------------------------- |
|     `tab` | `char **`        | Array of strings                |
|       `f` | `int (*)(char*)` | Function that tests each string |

Important detail from the subject:

> “The array will be delimited with a null pointer.”

That means:

```c
char *array[] = {"Hello", "World", NULL};
```

The loop must stop when it reaches `NULL`.

---

## 🧩 Your Implementation

```c
int	ft_any(char **tab, int (*f)(char *))
{
	if (!tab || !f)
		return (0);

	while (*tab)
	{
		if (f(*tab) != 0)
			return (1);
		tab++;
	}

	return (0);
}
```

---

## 🔍 Step-by-Step Logic

### 1. Safety checks

```c
if (!tab || !f)
	return (0);
```

* If no array OR no function pointer → nothing to test
* Returning `0` is safe and logical

---

### 2. Iterate over the array

```c
while (*tab)
```

This works because:

* `tab` is a pointer to strings
* `*tab` is the current string
* When `*tab == NULL`, we reached the end

---

### 3. Apply function `f`

```c
if (f(*tab) != 0)
	return (1);
```

* We call the function `f` on each string
* If it returns anything other than `0` → condition satisfied
* Immediately return `1`

This is called **early exit** and is optimal.

---

### 4. If nothing matched

```c
return (0);
```

* We tested all strings
* None of them satisfied `f`

---

## 🧠 Function Pointer Concept

Parameter:

```c
int (*f)(char *)
```

means:

* `f` is a pointer to a function
* that receives a `char *`
* and returns an `int`

Example from your test:

```c
int has_letter_z(char *str)
```

This function matches the required signature, so it can be passed to `ft_any`.

---

## 🧪 Test Function Explained

```c
int	has_letter_z(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == 'Z')
			return (1);
		i++;
	}
	return (0);
}
```

* Returns `1` if the string contains `'Z'`
* Otherwise returns `0`

This is exactly the kind of function `ft_any` expects.

---

## 🧪 Example from Your `main`

### Case 1

```c
char *strs[] = {"Hello", "World", "From", "Zebra", NULL};
```

* `"Zebra"` contains `'Z'`
* So `ft_any(strs, has_letter_z)` returns **1**

Output:

```
Test 1: Found a 'Z'!
```

---

### Case 2

```c
char *strs_no_z[] = {"Apple", "Banana", "Cherry", NULL};
```

* None contain `'Z'`
* Function returns **0**

Output:

```
Test 2: No 'Z' found.
```

---

## 🧩 Important Concepts Demonstrated

This exercise trains:

* Working with **arrays of strings**
* Understanding **NULL-terminated arrays**
* Using **function pointers**
* Early return logic
* Generic testing functions

---

## ⏱ Complexity

* **Time:** `O(n)` — checks each string once
* **Space:** `O(1)` — no extra memory used

---

## ⚠️ Common Mistakes

| Mistake                 | Problem          | Your Code             |
| ----------------------- | ---------------- | --------------------- |
| Not stopping at `NULL`  | Infinite loop    | ✅ uses `while (*tab)` |
| Forgetting to check `f` | Segfault         | ✅ checks `!f`         |
| Continuing after match  | Unnecessary work | ✅ early `return (1)`  |
| Returning wrong values  | Logic error      | ✅ returns `1` or `0`  |

---

## 📝 Peer Evaluation Questions

**Q1: Why don’t we need the array length?**
Because the array is terminated by a `NULL` pointer.

**Q2: What does `tab++` do?**
Moves the pointer to the next string in the array.

**Q3: Why return 1 on first match?**
Because the goal is “ANY match”, not “ALL matches”.

**Q4: What happens if `tab` is NULL?**
Function safely returns `0`.

**Q5: Is this similar to a real function?**
Yes – similar to JavaScript’s `.some()` or Python’s `any()`.


### Final Thought

`ft_any` is a very elegant example of how C can implement **generic logic** using function pointers.
Small function, big concept 👍

---

