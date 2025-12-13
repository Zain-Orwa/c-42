# ✅ Exercise 03 : ft_sort_params`

> **Goal:** Write a program that prints its command-line arguments **sorted in ASCII order**, **excluding `argv[0]`**, **one argument per line**, using only `write`.

---

## 📌 1) What the exercise is asking

When you run:

```bash
./a.out zebra banana apple
```

Your program receives:

* `argv[0] = "./a.out"` (program name)
* `argv[1] = "zebra"`
* `argv[2] = "banana"`
* `argv[3] = "apple"`

You must **sort** only:

```
argv[1] .. argv[argc - 1]
```

Then print them:

```
apple
banana
zebra
```

---

## 🧠 2) Where `argc` and `argv` come from (important for this exercise)

* The **OS** (through the shell) starts your program and **calls `main(argc, argv)`**.
* `argc` is the **count of strings** in `argv`.
* `argv` is a **list of pointers to strings** (`char *argv[]`).

So `argc` doesn’t represent a string — it represents **how many strings exist**.

---

## 🧩 3) Memory model of `argv` (like your picture)

Example:

```bash
./a.out zebra banana apple
```

```
argv (char **)
 |
 v
+---------+      +------------------+
| argv[0] | ---> | "./a.out\0"      |
+---------+      +------------------+
| argv[1] | ---> | "zebra\0"        |
+---------+      +------------------+
| argv[2] | ---> | "banana\0"       |
+---------+      +------------------+
| argv[3] | ---> | "apple\0"        |
+---------+      +------------------+
| argv[4] | ---> NULL
+---------+
```

✅ Sorting means: **rearrange the pointers** in `argv[1..]`
❌ Not moving characters in memory.

---

## 🔤 4) ASCII order (what “sorted” means)

Sorting by ASCII means comparing characters by their numeric values:

* `'A'` comes before `'a'`
* `'0'` comes before `'A'`
* etc.

So `"Apple"` will come before `"banana"`.

---

## 🧠 5) `ft_strcmp` — why we return “negative/positive” even with `unsigned char`

Your function:

```c
return ((unsigned char)*s1 - (unsigned char)*s2);
```

### ✅ Why cast to `unsigned char`?

Because plain `char` can be signed on some systems. If a character has a value above 127, it might become negative, which breaks comparisons.

Casting ensures both are treated as **0..255**, consistent.

### ✅ Why can the result still be negative?

Because you subtract two numbers:

* if `*s1 < *s2` → result negative
* if `*s1 > *s2` → result positive
* if equal → 0

Even though each character is converted to an unsigned value, **the subtraction result is an `int`**, so it can be negative.

---

## 🔁 6) The “two-layer” idea (your biggest confusion earlier)

### ✅ Layer 1: Sorting layer (works with whole strings)

In sorting, we compare:

```c
argv[j] and argv[j + 1]
```

These are **char*** (pointers to whole strings).

### ✅ Layer 2: Character layer (inside `ft_strcmp`)

Inside `ft_strcmp`, we do character-by-character using:

```c
*s1 and *s2
```

So your mental picture “`argv[i][j]` compares characters” is correct **conceptually**, but it belongs **inside `ft_strcmp`**, not in the bubble-sort loops.

---

## 🔄 7) Why `argc` is used in BOTH loops

This was your question: “why not only one loop?”

### ✅ Inner loop uses `argc` for safety

We compare:

```c
argv[j] vs argv[j + 1]
```

So we must ensure `j + 1` is valid.

That’s why:

```c
while (j < argc - 1)
```

If you allow `j == argc - 1`, then `argv[j + 1]` becomes `argv[argc]` which is **NULL** → crash.

### ✅ Outer loop uses `argc` for correctness

Bubble sort needs **multiple passes**.
One pass only pushes the largest element to the end.

So the outer loop repeats the scanning process enough times so all elements settle into place.

---

## 🫧 8) Sorting method used: Bubble Sort (pointer swapping)

### The sorting logic:

```c
if (ft_strcmp(argv[j], argv[j + 1]) > 0)
    ft_swap(&argv[j], &argv[j + 1]);
```

This says:

> If left string comes after right string in ASCII → swap them.

### `ft_swap` swaps pointers, not letters

```c
void ft_swap(char **a, char **b)
```

Because `argv[j]` is a `char *`.
So `&argv[j]` is a `char **`.

---

## 🧪 9) Full trace example (the one we did)

Input:

```
zebra, banana, apple
```

Start:

```
[1] zebra
[2] banana
[3] apple
```

### Pass 1

* compare zebra vs banana → swap
* compare zebra vs apple → swap

Now:

```
[1] banana
[2] apple
[3] zebra
```

### Pass 2

* compare banana vs apple → swap
* compare banana vs zebra → no swap

Final:

```
[1] apple
[2] banana
[3] zebra
```

---

## 🖨️ 10) Printing phase (after sorting)

In `main`:

```c
i = 1;
while (i < argc)
{
    ft_putstr(argv[i]);
    i++;
}
```

✅ Starts from `1` to skip `argv[0]`
✅ One argument per line
✅ Uses only `write` ✅

---

## ✅ 11) Final code (your submitted version)

```c
#include <unistd.h>
#include <stdio.h>

void ft_putstr(char *str){
	while (*str)
		write(1, str++, 1);
	write(1, "\n", 1);
}

int ft_strcmp(char *s1, char *s2){
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void ft_swap(char **a, char **b){
	char *temp;

	temp = *a;
	*a   = *b;
	*b   = temp;
}

void ft_sort_params(int argc, char *argv[]){
	int i;
	int j;

	i = 1;
	while (i < argc - 1)
	{
		j = 1;
		while (j < argc - 1)
		{
			if (ft_strcmp(argv[j], argv[j + 1]) > 0)
				ft_swap(&argv[j], &argv[j + 1]);
			j++;
		}
		i++;
	}
}

int main(int argc, char *argv[]){
	int i;

	ft_sort_params(argc, argv);

	i = 1;
	while (i < argc)
	{
		ft_putstr(argv[i]);	
		i++;
	}
	return (0);
}
```

---

## Common Mistakes Checklist

* Trying `argv[i][j]` in the sort loop (wrong level — that’s inside `ft_strcmp`)
* Swapping characters instead of swapping pointers
* Using `int *` in `swap` instead of `char **`
* Loop bounds wrong → accessing `argv[argc]` (NULL) → crash
* Printing `argv[0]` (must skip it)

---

## Peer Evaluation Q&A

**Q: Why is `argv[0]` excluded?**
A: It’s the program name/path, not a user argument.

**Q: Why do we swap `char*` pointers instead of copying strings?**
A: Copying strings would require moving characters and more code. Swapping pointers is simple and efficient.

**Q: Why does `argc` appear in both loops?**
A: Outer loop = number of passes (correctness). Inner loop = bounds safety (`argv[j+1]` must exist).

**Q: Are we comparing characters or strings?**
A: Sorting compares *strings* (pointers). Character-by-character comparison happens *inside* `ft_strcmp`.

**Q: Who sets `argc/argv`?**
A: The OS (via the shell) builds them and calls `main(argc, argv)`.

---


