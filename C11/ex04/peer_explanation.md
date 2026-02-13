# 📘 peer_explanation.md — ft_is_sort

---

## 🧠 Goal of the Exercise

We must detect whether an array is **sorted** using a comparison function provided by the caller.

Prototype:

```c
int ft_is_sort(int *tab, int length, int (*f)(int, int));
```

Return values:

| Return | Meaning                                   |
| ------ | ----------------------------------------- |
| 1      | array is sorted (ascending OR descending) |
| 0      | array is not sorted                       |

Important: we do NOT know how to compare numbers — the function `f` decides.

---

## 🔁 What “sorted” means here

The array is considered sorted if it is entirely:

* Ascending: `1 2 3 4 5`
* Descending: `5 4 3 2 1`
* Equal allowed: `1 2 2 3 3 4`

So equality **does not break sorting**.

---

## 🧩 The Comparison Function (3‑state logic)

The function `f(a, b)` returns a **sign**, not a boolean:

| f(a,b) | Meaning |
| ------ | ------- |
| < 0    | a < b   |
| 0      | a == b  |
| > 0    | a > b   |

Example implementation:

```c
int compare(int a, int b)
{
    return (a - b);
}
```

⚠️ Better safe version (no overflow):

```c
int compare(int a, int b)
{
    if (a > b) return 1;
    if (a < b) return -1;
    return 0;
}
```

---

## 🧠 How ft_is_sort works (core idea)

We track two possibilities at the same time:

| Flag | Meaning                   |
| ---- | ------------------------- |
| asc  | still possibly ascending  |
| desc | still possibly descending |

Start both as true.
Every comparison removes one possibility.

At the end:

```c
return (asc || desc);
```

---

## 🔄 Pair Comparison — The Neighbor Rule

We never inspect a single element alone.
We compare neighbors:

```
tab[i]  vs  tab[i+1]
```

### ❓ Question: Why `i < length - 1` ?

Because we access `tab[i+1]`.

Memory diagram (length = 5):

```
Index:   0   1   2   3   4
Value:  [1] [2] [3] [4] [5]
```

If `i = 4` → `tab[i+1] = tab[5]` ❌ outside array

So the last safe `i` is 3.

Condition that stops there:

```
i < length - 1
```

---

## 🧠 Loop Decision Logic

```
cmp = f(tab[i], tab[i+1])
```

| cmp | Effect            |
| --- | ----------------- |
| > 0 | breaks ascending  |
| < 0 | breaks descending |
| = 0 | keeps both valid  |

So equal numbers are neutral.

---

## ❓ Question: Why not simple `if ... else` ?

Because we have **3 states**, not 2.

Wrong logic:

```c
if (cmp > 0)
    asc = 0;
else
    desc = 0;
```

Problem:

For `5 5` → cmp = 0
This would incorrectly kill `desc`.

But `[5,5,5]` is sorted both ways.

Correct logic:

```c
if (cmp > 0)
    asc = 0;
else if (cmp < 0)
    desc = 0;
```

Now equality changes nothing.

---

## 🧠 Else‑if vs Nested if (difference between the two solutions)

Uncommented version:

```c
if (f(tab[i], tab[i + 1]) > 0)
    asc = 0;
else
{
    if (f(tab[i], tab[i + 1]) < 0)
        desc = 0;
}
```

Commented version:

```c
if (f(tab[i], tab[i + 1]) > 0)
    asc = 0;
else if (f(tab[i], tab[i + 1]) < 0)
    desc = 0;
```

### Differences

| Aspect         | Nested if        | else‑if                          |
| -------------- | ---------------- | -------------------------------- |
| Function calls | May call f twice | Calls f once logically path‑wise |
| Readability    | Slightly heavier | Cleaner                          |
| Efficiency     | Slightly worse   | Better                           |
| Behavior       | Same result      | Same result                      |

Important: Best solution stores cmp once.

---

## ❓ Question: Why return 1 when `length <= 1` ?

Because a set with 0 or 1 element cannot be unsorted.

Mathematical truth: **vacuously sorted**.

Examples:

```
[]  -> sorted
[42] -> sorted
```

---

## ⚠️ Difference between the two versions (return condition)

Version A:

```c
if (!tab || length <= 1)
    return (1);
```

Version B:

```c
if (!tab || length <= 0)
    return (0);
```

### Behavioral Difference

| Case            | Version A | Version B  |
| --------------- | --------- | ---------- |
| NULL + length=0 | sorted    | not sorted |
| NULL + length>0 | sorted    | not sorted |
| one element     | sorted    | not sorted |

Version A follows mathematical definition.
Version B follows strict defensive programming.

---

## 🔬 Mechanism — How the function pointer works

Call:

```c
ft_is_sort(tab, length, &compare);
```

Memory view:

```
main
  │
  │ passes address of compare
  ▼
ft_is_sort
  │
  │ calls f(a,b)
  ▼
compare(a,b)
  │
  ▼
returns sign
```

So inside the loop:

```
f(tab[i], tab[i+1])
```

means:

```
compare(tab[i], tab[i+1])
```

---

## 🧠 Full Logical Flow Diagram

```
Start
  │
  ├─ length <= 1 → sorted
  │
  ▼
Initialize asc = 1, desc = 1
  │
  ▼
Loop pairs
  │
  ├─ cmp > 0 → not ascending
  │
  ├─ cmp < 0 → not descending
  │
  └─ cmp = 0 → neutral
  │
  ▼
If asc OR desc → sorted
Else → not sorted
```

---

## 🧪 Example Walkthrough

Array:

```
1 2 2 3
```

Steps:

| Pair | cmp | asc | desc |
| ---- | --- | --- | ---- |
| 1,2  | <0  | 1   | 0    |
| 2,2  | 0   | 1   | 0    |
| 2,3  | <0  | 1   | 0    |

Result → sorted

---

## 🧾 Final Understanding

This exercise teaches:

* Function pointers as behavior injection
* Three‑state comparison logic
* Bidirectional sorting detection
* Edge‑case reasoning (empty arrays)
* Safe array traversal

The algorithm does NOT sort.
It verifies order consistency.

---

## 🏁 Key Insight

Sorting check = eliminate impossible directions until one survives.

