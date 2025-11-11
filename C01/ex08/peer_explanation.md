# 🧩 `ft_sort_int_tab` — Peer Explanation (ex08)

> **Goal:** Sort an array of integers in ascending order using only basic operations — no library functions allowed.

---

## 📜 Code Reference

```c
#include <unistd.h>

void ft_sort_int_tab(int *tab, int size){
	int i;
	int temp;
	int swapped;

	swapped = 1;
	while (swapped){
		swapped = 0;
		i = 0;
		while (i < size - 1){
			if (tab[i] > tab[i + 1]){
				temp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
		size--;
	}
}

int main(void){
	int tab[] = {4, -1, 5, 3, 9, 8, 7};
	int size = (int)(sizeof(tab) / sizeof(tab[0]));

	ft_sort_int_tab(tab, size);

	for (int i = 0; i < size; i++)
		printf("%d ", tab[i]);
	return (0);
}
```

---

## ⚙️ Function: `ft_sort_int_tab`

### 💡 Purpose

To reorder the array `tab[]` in **ascending order** — smallest to largest — by repeatedly swapping elements until the entire array is sorted.

---

### 🧠 Step-by-Step Breakdown

1. **`int *tab`**
   Pointer to the first element of the integer array.
   Each element can be accessed with `tab[i]`.

2. **`int size`**
   Number of integers inside the array.

3. **`int swapped = 1;`**
   A control flag.
   It starts as `1` (true) to enter the outer `while` loop.
   It’s reset to `0` at the start of each pass — if no swaps happen during that pass, the array is sorted.

4. **Outer `while (swapped)`**
   Runs as long as swaps occur — this ensures we make passes until the array is fully ordered.

5. **Inner `while (i < size - 1)`**
   Compares every adjacent pair of elements (`tab[i]` and `tab[i+1]`).

6. **`if (tab[i] > tab[i + 1])`**
   If two neighbors are **out of order**, swap them:

   ```c
   temp = tab[i];
   tab[i] = tab[i + 1];
   tab[i + 1] = temp;
   swapped = 1;
   ```

   That’s the classic **bubble sort** mechanism: larger numbers "bubble" to the end.

7. **`size--` after each pass**
   Each completed pass pushes the largest remaining number to the end — no need to recheck it again.

---

### 🔍 Example Trace

**Input Array:**

```
[4, -1, 5, 3, 9, 8, 7]
```

| Pass | Comparisons                                                | Array After Pass           |
| ---- | ---------------------------------------------------------- | -------------------------- |
| 1    | (4,-1) → swap → (5,3) → swap → (9,8) → swap → (8,7) → swap | [-1, 4, 3, 5, 8, 7, 9]     |
| 2    | (4,3) → swap, (8,7) → swap                                 | [-1, 3, 4, 5, 7, 8, 9]     |
| 3    | No swaps — done                                            | **[-1, 3, 4, 5, 7, 8, 9]** |

---

### 🧩 Output Example

**Input:**

```
{4, -1, 5, 3, 9, 8, 7}
```

**Output:**

```
-1 3 4 5 7 8 9
```

---

### ❓ Discussion

* **Why use `swapped`?**
  It tracks if a swap occurred.
  If no swaps happen in a full pass, the array is already sorted → stop looping.

* **Why decrease `size` each pass?**
  Because after every pass, the largest element is guaranteed to be at the end; we don’t need to compare it again.

* **Why `i < size - 1`?**
  We compare `tab[i]` with `tab[i+1]`, so `i` must stop before the last index.

* **Why no `return`?**
  The function’s type is `void`, and it modifies the array *in place* via the pointer.

---

### 🧠 Analogy

Think of it like **shaking a jar of mixed coins**:
Every shake makes heavier coins fall to the bottom — you keep shaking until no coins move.
That’s what the outer `while (swapped)` loop does.

---

### 🧩 Concept Table

| Concept         | Explanation                                      |
| --------------- | ------------------------------------------------ |
| Bubble sort     | Repeatedly swap adjacent elements until sorted   |
| In-place        | Uses no extra arrays; modifies the original one  |
| `swapped`       | Detects whether another pass is needed           |
| `size--`        | Optimizes each pass by skipping the last element |
| Time complexity | O(n²) — not optimal, but fine for this exercise  |

---

### 🧩 Visual Memory View

| Index | Before | After |
| ----- | ------ | ----- |
| 0     | 4      | -1    |
| 1     | -1     | 3     |
| 2     | 5      | 4     |
| 3     | 3      | 5     |
| 4     | 9      | 7     |
| 5     | 8      | 8     |
| 6     | 7      | 9     |

---

### 🧪 Testing Variations

**Case 1 — Already sorted:**

```
Input: [1, 2, 3, 4]
Output: [1, 2, 3, 4]
(No swaps made)
```

**Case 2 — Reverse order:**

```
Input: [5, 4, 3, 2, 1]
Output: [1, 2, 3, 4, 5]
(Maximum swaps)
```

**Case 3 — Negative numbers:**

```
Input: [-2, 7, 0, -5]
Output: [-5, -2, 0, 7]
```

---

### ✅ Key Summary

| Step                       | Action                       |
| -------------------------- | ---------------------------- |
| Compare each adjacent pair | `if (tab[i] > tab[i + 1])`   |
| Swap if out of order       | Use `temp`                   |
| Repeat until no swaps      | Controlled by `swapped` flag |
| Shrink comparison range    | `size--` per pass            |

---

> 🏁 **Commit Suggestion:**
>
> ```
> Added peer_explanation.md for ex08 (ft_sort_int_tab)
> Includes bubble sort logic, pointer reasoning, and trace examples.
> ```

---

