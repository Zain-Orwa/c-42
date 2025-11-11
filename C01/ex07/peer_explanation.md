# 🧩 `ft_rev_int_tab` — Peer Explanation (ex07)

> **Goal:** Reverse a given array of integers so that the first element becomes last, the second becomes second-last, and so on — *in place* (no new array is created).

---

## 📜 Code Reference

```c
#include <unistd.h>

void ft_rev_int_tab(int *tab, int size){
	int i;
	int j;

	i = 0;
	j = size - 1;
	while (i < j){
		int temp = tab[i];
		tab[i] = tab[j];
		tab[j] = temp;
		i++;
		j--;
	}
}

int main(void){
	int size = 5;
	int tab[] = {1, 2, 3, 4, 5};

	ft_rev_int_tab(tab, size);

	for (int i = 0; i < size; i++)
		printf("%d ", tab[i]);
	return (0);
}
```

---

## ⚙️ Function: `ft_rev_int_tab`

### 💡 Purpose

To **reverse the order of integers in an array** using only pointer access and a simple swap algorithm.

---

### 🧠 Step-by-Step Breakdown

1. **`int *tab`**
   A pointer to the **first element** of the integer array.

2. **`int size`**
   The total number of elements in the array.

3. **`int i = 0;`**
   Start from the **leftmost** element.

4. **`int j = size - 1;`**
   Start from the **rightmost** element.

5. **`while (i < j)`**
   Continue swapping until the two indices meet in the middle.

6. **Swap logic:**

   ```c
   int temp = tab[i];
   tab[i] = tab[j];
   tab[j] = temp;
   ```

   * Store the left value in a temporary variable.
   * Replace the left element with the right.
   * Replace the right element with the stored left value.

7. **Increment and Decrement**

   ```c
   i++;
   j--;
   ```

   * Move `i` forward (right).
   * Move `j` backward (left).

When the two meet (`i >= j`), the array is fully reversed.

---

### 🔍 Example Trace

| Step | i | j | tab[i] | tab[j] | Action        | Array After Step |
| ---- | - | - | ------ | ------ | ------------- | ---------------- |
| 1    | 0 | 4 | 1      | 5      | swap 1 ↔ 5    | [5, 2, 3, 4, 1]  |
| 2    | 1 | 3 | 2      | 4      | swap 2 ↔ 4    | [5, 4, 3, 2, 1]  |
| 3    | 2 | 2 | 3      | 3      | stop (i == j) | [5, 4, 3, 2, 1]  |

---

### 🧩 Output Example

**Input Array:**

```
1 2 3 4 5
```

**After `ft_rev_int_tab(tab, 5)`**

```
5 4 3 2 1
```

---

### ❓ Discussion

* **Why `int *tab` instead of `int tab[]`?**
  Both forms are equivalent in function parameters — the array decays into a pointer to its first element.

* **Why `j = size - 1`?**
  Arrays are zero-indexed, so the last valid index is always one less than the size.

* **Why stop when `i < j` becomes false?**
  If `i` passes `j`, it means we’d start undoing our swaps — the array is already reversed.

* **Is this done in place?**
  Yes, no new array is created. We just swap values inside the same memory block.

* **Can this work with even or odd sizes?**
  ✅ Yes — for odd sizes, the middle element stays in place (no need to swap with itself).

---

### 🧠 Analogy

Imagine a row of people numbered 1–5.
`i` starts from the left, `j` from the right.
They keep swapping positions until they meet in the center.

---

### ✅ Key Concepts Summary

| Concept    | Description                                    |
| ---------- | ---------------------------------------------- |
| `int *tab` | Pointer to the start of the array              |
| `size`     | Number of elements in the array                |
| Swap       | Exchange two values using a temporary variable |
| Condition  | Loop until `i < j`                             |
| Effect     | Reverses array elements in place               |

---

### 🧩 Testing with Different Sizes

**Size = 4**

```
Input:  1 2 3 4
Output: 4 3 2 1
```

**Size = 6**

```
Input:  10 20 30 40 50 60
Output: 60 50 40 30 20 10
```

**Size = 1**

```
Input:  42
Output: 42  (no change)
```

---

### 🧩 Visual Memory View (before & after)

| Index | Before | After |
| ----- | ------ | ----- |
| 0     | 1      | 5     |
| 1     | 2      | 4     |
| 2     | 3      | 3     |
| 3     | 4      | 2     |
| 4     | 5      | 1     |

---

> 🏁 **Commit Suggestion:**
>
> ```
> Added peer_explanation.md for ex07 (ft_rev_int_tab)
> Includes swap logic, pointer reasoning, and full memory trace.
> ```

---

