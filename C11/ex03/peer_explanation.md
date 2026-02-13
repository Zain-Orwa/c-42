````md
# 🧠 peer_explanation.md — ex03 `ft_count_if`

---

## ✅ Goal of the exercise

Implement:

```c
int	ft_count_if(char **tab, int length, int (*f)(char *));
````

This function counts **how many elements** in the array `tab` make the function `f` return **non-zero**.

* If `f(tab[i]) != 0` → element is “true” → **count it**
* If `f(tab[i]) == 0` → element is “false” → **don’t count it**

---

## 🧩 Function prototype explained

| Part                 | Meaning                                                         |
| -------------------- | --------------------------------------------------------------- |
| `char **tab`         | Array of strings (`tab[i]` is a `char *`)                       |
| `int length`         | Number of elements to check in `tab`                            |
| `int (*f)(char *)`   | Pointer to a function that takes a string and returns an `int`  |
| return value (`int`) | How many elements produced a non-zero result when passed to `f` |

---

## 🔥 Key concept: function pointer

`f` is not a normal variable — it is a pointer to a function.

So when you write:

```c
f(tab[i])
```

you are **calling** the function that was passed in as argument, using `tab[i]` as its parameter.

This is how we can make `ft_count_if` work with **any condition**:

* “is the string empty?”
* “does it start with A?”
* “is length > 3?”
* etc.

---

## 🧠 Your implementation (submission function)

```c
int	ft_count_if(char **tab, int length, int (*f)(char *))
{
	int	i;
	int	count;

	// Pointer and length guards
	if (!tab || !f || length <= 0)
		return (0);
	
	i = 0;
	count = 0;
	while (i < length)
	{
		// If the function returns anything other than 0, increment count
		if (f(tab[i]) != 0)
			count++;
		i++;
	}
	return (count);
}
```

---

## 🪓 Step-by-step logic

| Step | What happens                                                     |
| ---- | ---------------------------------------------------------------- |
| 1    | If `tab` is `NULL`, `f` is `NULL`, or `length <= 0` → return `0` |
| 2    | Initialize `i = 0`, `count = 0`                                  |
| 3    | Loop while `i < length`                                          |
| 4    | Call `f(tab[i])`                                                 |
| 5    | If result is not `0` → `count++`                                 |
| 6    | Move to next element: `i++`                                      |
| 7    | Return `count`                                                   |

---

## ⚠️ Important edge cases

| Case                         | Expected behavior | Your code does         |
| ---------------------------- | ----------------- | ---------------------- |
| `tab == NULL`                | return `0`        | ✅ yes                  |
| `f == NULL`                  | return `0`        | ✅ yes                  |
| `length <= 0`                | return `0`        | ✅ yes                  |
| `tab[i] == NULL` inside loop | depends on `f`    | ⚠️ passed to `f` as-is |

### Note about `tab[i] == NULL`

If any element is `NULL`, and `f` doesn’t handle it, it can crash.
Your implementation **does not protect** against that (which is fine unless the subject requires it).
A safe pattern (optional) would be:

```c
if (tab[i] && f(tab[i]) != 0)
	count++;
```

---

## ⏱️ Complexity

| Metric | Value       |
| ------ | ----------- |
| Time   | `O(length)` |
| Space  | `O(1)`      |

---

## 🧪 Test section (NOT for submission)

You wrote a `main()` to validate the function. That’s perfect for learning, but in 42 you usually submit **only** `ft_count_if.c` with the required function.

Your test uses:

* `is_long_word()` → returns `1` if string length > 3
* array: `{"Hi", "Hello", "C", "Code"}`
* expected count: `"Hello"`, `"Code"` → **2**

---

## ✅ What the Moulinette / peer will look for

| Checkpoint                     | Why it matters                                   |
| ------------------------------ | ------------------------------------------------ |
| Correct prototype              | Must match subject exactly                       |
| Correct counting rule (`!= 0`) | Non-zero means “true” in C                       |
| Iteration follows array order  | Must check elements from index 0 to length-1     |
| No forbidden functions         | Subject says allowed functions: none             |
| Clean, simple loop             | This exercise expects a straightforward solution |

---

## 💬 Peer Evaluation Q&A

**Q1: Why do we check `f(tab[i]) != 0` instead of `== 1`?**
Because in C, “true” is **any non-zero value**, not only `1`.

**Q2: What is `int (*f)(char *)` exactly?**
It’s a *pointer to a function* that takes a `char *` and returns an `int`.

**Q3: What happens if `length` is bigger than the real array size?**
Undefined behavior (you read outside the array). The caller must pass the correct `length`.

**Q4: Why return 0 for invalid inputs?**
Because if you can’t safely evaluate conditions, the safest count is “nothing matched”.

**Q5: Does `ft_count_if` modify the array?**
No. It only reads `tab[i]` and calls `f` on it.

---

## ✅ Final summary

`ft_count_if` is a generic “counter” that applies a condition function `f` to each string in `tab`, and returns how many results were **non-zero**. Your loop logic is correct, clear, and matches the subject’s behavior.

```
```

