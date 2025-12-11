**Exercise 08 : The Ten Queens**

## 1. Problem recap in *your* code’s language
We want:

* A 10×10 chessboard.
* Put 10 queens so that **no two queens attack each other**:

  * not in the same **row**
  * not in the same **column**
  * not on the same **diagonal**
* Print **every** valid configuration as a line of 10 digits:

  * index = column (0 → 9)
  * digit = row of the queen in that column
* Return how many solutions exist.

You’re solving it with **backtracking + recursion**:

* `board[col] = row` means:
  “In column `col`, the queen sits in row `row`”.
* You fill columns from left to right (`col = 0 → 9`).
* At each column, you try rows `0..9`, check if it’s safe, place, recurse.

---

## 2. Quick tour of each function

### `ft_putchar`

```c
void ft_putchar(char c){
	write(1, &c, 1);
}
```

Tiny wrapper to print a single character to stdout.

---

### `print_solutiion`

```c
void print_solutiion(int *board){
	int i = 0;
	while (i < 10){
		ft_putchar(board[i] + '0');
		i++;
	}
	ft_putchar('\n');
}
```

* `board` is an array of 10 ints: each element is a row index (0–9).
* `board[i] + '0'` converts a digit `0..9` to the corresponding ASCII character.
* Example: `board = {0,2,5,7,9,1,3,4,6,8}`
  Printed as: `0257913468`.

---

### `ft_abs`

```c
int ft_abs(int num){
	if (num < 0)
		return (-num);
	return (num);
}
```

Just the absolute value helper, used for diagonal checks.

---

### `is_safe`

```c
int is_safe(int *board, int col, int row){
	int i;
	int row_diff;
	int col_diff;

	i = 0;
	while (i < col){
		// same row?
		if (board[i] == row)
			return (0);

		// difference in rows and columns compared
		row_diff = ft_abs(board[i] - row); // |row_i - row|
		col_diff = col - i;                // col - i  (always ≥ 1)

		// same diagonal?
		if (row_diff == col_diff)
			return (0);
		i++;
	}
	return (1);
}
```

**Idea**: you are about to put a queen at `(col, row)`.
You only need to compare against *previously placed* queens in columns `0..col-1`.

For each previous column `i`:

* Position of the existing queen: `(i, board[i])`
* Same row attack?

  * `board[i] == row` → same row → NOT safe.
* Diagonal attack? (classic chess rule):

  * Two positions are on the same diagonal if
    `|row1 - row2| == |col1 - col2|`.
  * Here `row_diff = |board[i] - row|`
    `col_diff = col - i` (positive since `i < col`).
  * If equal → same diagonal → NOT safe.

If no conflict found: return `1` (safe).

---

### `ft_backtrack` — **THE recursive heart**

```c
void ft_backtrack(int *board, int col, int *solutions){
	int row;

	if (col == 10)
	{
		print_solutiion(board);
		*solutions = *solutions + 1;
        return;          // ⚠️ This `return` is needed (see explanation below)
	}

	row = 0;
	while (row < 10)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;
			ft_backtrack(board, col + 1, solutions);
		}
		row++;
	}
}
```

Let’s break this in two parts: **base case** and **recursive step**.

---

## 3. Where exactly does the recursion happen?

### 3.1 Base case

```c
if (col == 10)
{
	print_solutiion(board);
	*solutions = *solutions + 1;
    return;
}
```

Meaning:

* We successfully placed queens in columns `0..9` (10 columns total).
* So `board[0..9]` is a **complete valid solution**.
* We:

  1. Print it.
  2. Increment the shared counter `*solutions`.
  3. **Return** to the previous recursion level (very important!).

> ⚠ **Bug in your original code**
> Without the `return;` here, the function will continue into the `while (row < 10)` using `col == 10`, and then do `board[col] = row;` → `board[10] = row;` which is **out of bounds** for `board[10]`.
> That’s undefined behavior. So the correct version must have `return;` after counting the solution.

---

### 3.2 Recursive step

```c
row = 0;
while (row < 10)
{
	if (is_safe(board, col, row))
	{
		board[col] = row;
		ft_backtrack(board, col + 1, solutions); // ← recursion
	}
	row++;
}
```

This loop does:

1. Try placing a queen in **column `col`** at **row = 0..9**.
2. For each `row`:

   * Check if it’s safe with `is_safe`.
   * If safe:

     * Set `board[col] = row` (we place the queen).
     * **Recursive call**: solve the rest of the board starting at `col + 1`.
3. When the recursive call returns:

   * We are back in the current column,
   * We continue trying the next `row` value (backtracking).

So recursion happens in:

```c
ft_backtrack(board, col + 1, solutions);
```

Each call handles **one column**, and delegates the remaining columns to deeper calls.

---

### 3.3 Smaller example (4 queens) – recursion tree idea

Imagine we had 4 queens instead of 10, and call:

```c
ft_backtrack(board, 0, &solutions);
```

The recursion tree conceptually looks like this:

* Level 0: `col = 0`

  * Try `row = 0,1,2,3` (only some are safe)
* For each safe `(0, row0)`:

  * Level 1: `col = 1`

    * Try rows `0..3`, respecting conflicts with column 0.
* For each pair `(0,row0), (1,row1)` safe:

  * Level 2: `col = 2`

    * Try rows `0..3`.
* …
* Level 4: `col = 4` → base case reached → full solution → print.

Backtracking = when a path fails at some column, we return to the previous column and try another row there.

---

## 4. Why `solutions` uses a pointer and `&solutions`

### In `ft_ten_queens_puzzle`:

```c
int ft_ten_queens_puzzle(void){
	int board[10];
	int solutions;

	solutions = 0;
	ft_backtrack(board, 0, &solutions);

	return (solutions);
}
```

Key points:

* `solutions` is a normal `int` on the stack of `ft_ten_queens_puzzle`.

* You pass **its address** into `ft_backtrack`:

  ```c
  &solutions
  ```

* In `ft_backtrack`, parameter type is `int *solutions`, so inside the function:

  * `solutions` (parameter) = pointer → points to the original `solutions` variable.
  * `*solutions` = the actual integer stored in `ft_ten_queens_puzzle`.

So in `ft_backtrack`:

```c
*solutions = *solutions + 1;
```

means:

> “Go to the integer in `ft_ten_queens_puzzle` and increment it by 1.”

All recursive calls receive **the same pointer**, so they all increment the same counter.

#### Why not just use a normal `int` parameter?

If you wrote:

```c
void ft_backtrack(int *board, int col, int solutions);
```

then `solutions` would be a **copy** in each call. Incrementing it inside would not affect other calls or the original variable. You’d need to return counts and sum them:

```c
int ft_backtrack(..., int col){
    if (col == 10)
        return 1;

    int count = 0;
    ...
        count += ft_backtrack(..., col + 1);
    ...
    return count;
}
```

That’s also valid, but your design chooses:

* `void` function
* shared global-like counter via pointer.

This pointer approach:

* avoids having to manage `return` values,
* makes it clear we’re counting solutions as a side effect.

---

## 5. Memory & recursion diagrams (stack + variables)

Let’s visualize the memory when the program runs.

### 5.1 Global picture (stack & heap)

Your program uses only **stack** (no `malloc`):

```text
+-------------------------+
|        Stack            |
|  (grows downward)       |
+-------------------------+
|  main frame             |
|-------------------------|
|  ft_ten_queens_puzzle   |
|   frame                 |
|-------------------------|
|  ft_backtrack(col=0)    |
|-------------------------|
|  ft_backtrack(col=1)    |
|-------------------------|
|  ...                    |
|-------------------------|
|  ft_backtrack(col=9)    |
+-------------------------+

(no heap usage)
```

---

### 5.2 Inside `ft_ten_queens_puzzle` frame

```text
Stack frame of ft_ten_queens_puzzle
+-----------------------------+
| return address to main      |
| saved registers, etc.       |
+-----------------------------+
| int board[10];              |  <- array of 10 ints on stack
| int solutions;              |  <- one integer counter
+-----------------------------+

board: 10 contiguous ints, e.g.
[ board[0] ][ board[1] ] ... [ board[9] ]
```

Addresses (conceptually):

```text
&board[0]  -> 1000
&board[1]  -> 1004
...
&board[9]  -> 1036

&solutions -> 1040
```

When you call:

```c
ft_backtrack(board, 0, &solutions);
```

the arguments passed are:

* `board` decays to pointer: type `int *`, value `1000` (for example).
* `0`
* `&solutions` → pointer to 1040.

---

### 5.3 One frame of `ft_backtrack`

For a typical call:

```c
ft_backtrack(board, col, &solutions);
```

The stack frame looks like:

```text
Stack frame of ft_backtrack (for a specific col)
+-------------------------------+
| return address                |
| saved registers               |
+-------------------------------+
| int *board    = 1000         | -> same board array in ft_ten_queens_puzzle
| int col       = <value>      |
| int *solutions = 1040        | -> points to ft_ten_queens_puzzle::solutions
| int row;                     |
+-------------------------------+
```

All recursion levels share:

* The **same** `board` array.
* The **same** `solutions` integer (via the pointer).

What changes for each level:

* `col` (0…10)
* `row` (local loop variable, each call has its own copy).

---

### 5.4 Recursion “stack tower” example

Imagine we are exploring one specific path:

1. `main()` calls `ft_ten_queens_puzzle()`
2. `ft_ten_queens_puzzle()` calls `ft_backtrack(board, 0, &solutions)`
3. That call recursively goes deeper:

```text
Top of stack
+-----------------------------+
| ft_backtrack col=3          |  board[0]=2, board[1]=5, board[2]=7 (example)
+-----------------------------+
| ft_backtrack col=2          |  board[0]=2, board[1]=5
+-----------------------------+
| ft_backtrack col=1          |  board[0]=2
+-----------------------------+
| ft_backtrack col=0          |
+-----------------------------+
| ft_ten_queens_puzzle        |
+-----------------------------+
| main                        |
+-----------------------------+
Bottom of stack
```

Notice:

* Only one **real** `board` array exists (in `ft_ten_queens_puzzle`).
* Each `ft_backtrack` frame just has a pointer to it.

When `ft_backtrack(col=3)` assigns:

```c
board[3] = 9;
```

it writes directly into the array in `ft_ten_queens_puzzle`’s frame.

When `ft_backtrack(col=3)` returns, the value in `board[3]` remains, but the caller may overwrite it with another row later.

This is the essence of **backtracking**: reuse the same board, overwrite positions as we explore different paths.

---

## 6. What happens step-by-step for one solution (simplified)

Let’s pretend we find some solution. The flow is:

1. Start: `ft_backtrack(board, 0, &solutions)`
   `col = 0`, `solutions = 0`.

2. In column 0, we try rows `0..9`. Suppose `row=2` is safe:

   * `board[0] = 2`
   * Recurse: `ft_backtrack(board, 1, &solutions)`

3. In column 1, try rows. Suppose `row=5` is safe:

   * `board[1] = 5`
   * Recurse: `ft_backtrack(board, 2, &solutions)`

4. This continues until:

   ```c
   ft_backtrack(board, 10, &solutions);
   ```

5. Now `col == 10` (base case):

   * `print_solutiion(board);`
   * `*solutions = *solutions + 1;`  → increases the **same** `solutions` as in `ft_ten_queens_puzzle`.
   * `return;`  (back to `col = 9` call)

6. Back at `col = 9`:

   * The `while (row < 10)` loop continues to try other rows in column 9.
   * If none work, function returns to `col = 8`, etc.
   * This is the “back” in backtracking.

After exploring **all** possible combinations, eventually all recursion unwinds back to `ft_ten_queens_puzzle`, and `solutions` now holds the total count.

---

## 7. FAQ-style clarifications

### ❓ Why do we use `i < col` in `is_safe`?

Because:

* We only placed queens in columns `0..col-1`.
* Column `col` is the one we’re *trying* to fill now.
* There’s nothing beyond `col`, so no need to check them.

---

### ❓ How does `row_diff == col_diff` detect diagonal conflicts?

Two queens at `(c1, r1)` and `(c2, r2)` are on the same diagonal if:

```text
|r1 - r2| == |c1 - c2|
```

In your code:

* `board[i]` = row of the queen at column `i`.
* `row` = row we’re trying at column `col`.

So:

```c
row_diff = ft_abs(board[i] - row);  // |r1 - r2|
col_diff = col - i;                 // |c1 - c2| (positive because col > i)
```

If they are equal → same diagonal → not safe.

---

### ❓ Why does `board` not use `&` when passed?

In `ft_ten_queens_puzzle`:

```c
ft_backtrack(board, 0, &solutions);
```

* `board` is an array.
  In most expressions (including function calls) it **decays** to pointer-to-first-element: `&board[0]`.
* So writing `board` as argument already passes an `int *`.

For `solutions` we must **explicitly** take the address with `&solutions`, because `solutions` is just an `int`, not an array.

---

### ❓ Why did we need `return;` in the base case?

Once `col == 10`, we don’t want to:

* try any `row`, or
* write `board[col] = row` (which would be `board[10]`, out of bounds).

So we must exit `ft_backtrack` immediately after counting the solution. That’s what `return;` does.

---

## 1. Mini 4-Queens version (same logic as your 10-Queens)

I’ll just shrink your code to 4 columns/rows and **add the missing `return;`** in the base case (same fix applies to your 10-queens code):

```c
#include <unistd.h>

void    ft_putchar(char c) { write(1, &c, 1); }

int ft_abs(int x) { return (x < 0 ? -x : x); }

void print_solution(int *board)
{
    int i = 0;
    while (i < 4)
        ft_putchar(board[i++] + '0');
    ft_putchar('\n');
}

int is_safe(int *board, int col, int row)
{
    int i;
    int row_diff;
    int col_diff;

    i = 0;
    while (i < col)
    {
        if (board[i] == row)
            return (0);
        row_diff = ft_abs(board[i] - row);
        col_diff = col - i;
        if (row_diff == col_diff)
            return (0);
        i++;
    }
    return (1);
}

void ft_backtrack(int *board, int col, int *solutions)
{
    int row;

    if (col == 4)              // ✅ base case
    {
        print_solution(board);
        *solutions = *solutions + 1;
        return;                // IMPORTANT to avoid board[4] access
    }

    row = 0;
    while (row < 4)
    {
        if (is_safe(board, col, row))
        {
            board[col] = row;
            ft_backtrack(board, col + 1, solutions);  // recursion
        }
        row++;
    }
}

int ft_four_queens(void)
{
    int board[4];
    int solutions = 0;

    ft_backtrack(board, 0, &solutions);
    return (solutions);
}
```

Everything is the **same pattern** as your 10-queens puzzle, just `4` instead of `10`.

---

## 2. One full path: how we reach a solution

One known 4-queen solution is:

> `1302` → queens at
> column 0 → row 1
> column 1 → row 3
> column 2 → row 0
> column 3 → row 2

We’ll see how recursion walks there.

### 2.1 Start

We call:

```c
ft_backtrack(board, 0, &solutions);
```

* `col = 0`
* board is uninitialized yet; we’re about to fill it.

---

### 2.2 Frame: `col = 0`

Loop `row = 0..3`:

1. `row = 0`

   * `is_safe(board, 0, 0)`:

     * loop `while (i < col)` → `i < 0` → **no checks**, so safe.
   * `board[0] = 0`
   * recurse: `ft_backtrack(board, 1, &solutions)`
   * That entire branch (starting with queen at (0,0)) **eventually fails** (no full solution), so the recursion unwinds back to `col=0`, continuing the loop.

2. `row = 1`

   * `is_safe(board, 0, 1)`:

     * again `i < 0` → safe.
   * `board[0] = 1`
   * recurse: `ft_backtrack(board, 1, &solutions)`
     👉 **This is the branch that will give us the solution 1302.**

We’ll now follow this **successful branch** in detail.

---

### 2.3 Frame: `col = 1`, with `board[0] = 1`

Loop `row = 0..3`:

* Check each row in column 1 vs the existing queen at column 0.

1. `row = 0`
   `is_safe(board, 1, 0)`:

   * `i = 0 < col (1)`:

     * same row? `board[0] == 1`, `row = 0` → no.
     * `row_diff = |board[0] - row| = |1 - 0| = 1`
     * `col_diff = col - i = 1 - 0 = 1`
     * `row_diff == col_diff` → **same diagonal** → not safe.

2. `row = 1`
   Same row as column 0 → `board[0] == 1` → **not safe**.

3. `row = 2`
   `row_diff = |1 - 2| = 1`, `col_diff = 1` → diag → **not safe**.

4. `row = 3`
   `row_diff = |1 - 3| = 2`, `col_diff = 1` → different → **safe**.

So the **first safe** is `row = 3`:

* `board[1] = 3`
* recurse: `ft_backtrack(board, 2, &solutions)`

Now board looks like:

```text
board[0] = 1
board[1] = 3
board[2] = ?  (not set yet)
board[3] = ?  (not set yet)
```

---

### 2.4 Frame: `col = 2`, with board = `[1, 3, ?, ?]`

Loop `row = 0..3`:

We must be safe against queens at:

* `(0,1)` and `(1,3)`.

#### Try `row = 0`:

* Compare with column 0: `(0,1)`

  * same row? `1 == 0` → no
  * `row_diff = |1 - 0| = 1`
  * `col_diff = 2 - 0 = 2`
  * not diag.
* Compare with column 1: `(1,3)`

  * same row? `3 == 0` → no
  * `row_diff = |3 - 0| = 3`
  * `col_diff = 2 - 1 = 1`
  * not diag.

✅ So `(2,0)` is **safe**.

* `board[2] = 0`
* recurse: `ft_backtrack(board, 3, &solutions)`

Board now:

```text
board[0] = 1
board[1] = 3
board[2] = 0
board[3] = ?  (not set)
```

---

### 2.5 Frame: `col = 3`, board = `[1, 3, 0, ?]`

We must be safe vs columns 0,1,2.

#### Try `row = 0`:

Compare with each previous queen:

* vs col 0 (row 1):

  * same row? nope
  * `row_diff = |1 - 0| = 1`
  * `col_diff = 3 - 0 = 3` → not diag.
* vs col 1 (row 3):

  * same row? nope
  * `row_diff = |3 - 0| = 3`
  * `col_diff = 3 - 1 = 2` → not diag.
* vs col 2 (row 0):

  * same row? yes (`0 == 0`) → ❌ not safe.

#### Try `row = 1`:

* vs col 0 (row 1): same row → ❌.

#### Try `row = 2`:

* vs col 0 (1):

  * `row_diff = |1 - 2| = 1`, `col_diff = 3 - 0 = 3` → no diag.
* vs col 1 (3):

  * `row_diff = |3 - 2| = 1`, `col_diff = 3 - 1 = 2` → no diag.
* vs col 2 (0):

  * `row_diff = |0 - 2| = 2`, `col_diff = 3 - 2 = 1` → no diag.
* no conflicts → ✅ safe.

So:

* `board[3] = 2`
* recurse: `ft_backtrack(board, 4, &solutions)`

Now board is:

```text
board = [1, 3, 0, 2]    // full configuration
```

---

### 2.6 Frame: `col = 4` → base case

```c
if (col == 4)
{
    print_solution(board);
    *solutions = *solutions + 1;
    return;
}
```

* `col == 4` (N), so we hit the base case.
* `print_solution` prints: `1302`.
* `*solutions = *solutions + 1`:

  * `solutions` is a pointer, say it points to address `0x7ffc...`.
  * Dereference `*solutions` → we read the actual integer in `ft_four_queens`.
  * Add 1, write it back → **the shared counter increases**.
* `return;` → go back to the frame with `col = 3`.

Now one full solution is counted and printed.

Backtracking continues to try other `row` values for `col = 3`, then goes up to `col = 2`, etc., exploring all remaining branches until no more are left.

---

## 3. Stack / memory diagrams for these moments

Let’s draw 3 “snapshots” of the stack.

### 3.1 Just entered `ft_four_queens`

```text
Stack (top at bottom here)

[ main frame ]
    ...
[ ft_four_queens frame ]
    board[4]      // e.g. uninitialized yet
    solutions = 0
```

Addresses (just conceptual):

```text
&board[0]  = 0x1000
&board[1]  = 0x1004
&board[2]  = 0x1008
&board[3]  = 0x100C
&solutions = 0x1010
```

When we call:

```c
ft_backtrack(board, 0, &solutions);
```

the parameters become:

* `board` parameter in `ft_backtrack`: `int *board = 0x1000`
* `col = 0`
* `solutions` parameter (pointer): `int *solutions = 0x1010`

---

### 3.2 While we’re at `col = 3`, board = `[1,3,0,?]`

Stack:

```text
Top
+------------------------------+
| ft_backtrack col=3           |
|   int *board = 0x1000        |
|   int col = 3                |
|   int *solutions = 0x1010    |
|   int row   (current row)    |
+------------------------------+
| ft_backtrack col=2           |
|   int *board = 0x1000        |
|   int col = 2                |
|   int *solutions = 0x1010    |
|   int row                    |
+------------------------------+
| ft_backtrack col=1           |
|   ...                        |
+------------------------------+
| ft_backtrack col=0           |
|   ...                        |
+------------------------------+
| ft_four_queens               |
|   board[0] = 1               |
|   board[1] = 3               |
|   board[2] = 0               |
|   board[3] = ?               |
|   solutions = 0              |
+------------------------------+
| main                         |
+------------------------------+
Bottom
```

Notice:

* There is **only one real `board` array**, in `ft_four_queens`.
* Every `ft_backtrack` frame has the *same pointer* `int *board = 0x1000`.
* Similarly, every frame has `int *solutions = 0x1010`, pointing to the same integer.

When `ft_backtrack(col=3)` does:

```c
board[3] = 2;
```

it writes into the array at address `0x100C` in `ft_four_queens`.

---

### 3.3 At the base case `col = 4`

Stack:

```text
Top
+------------------------------+
| ft_backtrack col=4           |
|  int *board = 0x1000         |
|  int col = 4                 |
|  int *solutions = 0x1010     |
|  int row (value doesn't      |
|           matter now)        |
+------------------------------+
| ft_backtrack col=3           |
| ft_backtrack col=2           |
| ft_backtrack col=1           |
| ft_backtrack col=0           |
+------------------------------+
| ft_four_queens               |
|  board = [1,3,0,2]           |
|  solutions = 0 (before)      |
+------------------------------+
| main                         |
+------------------------------+
```

Base case executes:

1. `print_solution(board);` → reads board[0..3] → prints `1302`.

2. `*solutions = *solutions + 1;`

   * `solutions` (param) = 0x1010.
   * `*solutions` accesses the value at 0x1010, which belongs to `ft_four_queens::solutions`.
   * If it was 0, now it becomes 1.

3. `return;`:

   * The top frame (`col = 4`) is popped off.
   * Execution resumes inside the `while (row < 4)` loop of the frame with `col = 3`.

Every time another solution is found, **the same process happens**, and `solutions` gets incremented each time — always via that pointer.

---

## 4. How this maps back to your 10-Queens version

Everything above scales directly to your code:

* Replace `4` with `10`.
* `ft_ten_queens_puzzle` plays the role of `ft_four_queens`.
* `ft_backtrack(board, 0, &solutions);` is identical.
* `is_safe` logic is the same, just with 10 rows/cols.
* The stack will have up to 11 nested `ft_backtrack` frames (for `col = 0..10`).
* The **pointer logic is identical**: all frames share:

  * the same `board[10]` (in `ft_ten_queens_puzzle`),
  * the same `solutions` integer via `int *solutions`.

Just don’t forget to keep this **crucial line** in your real code:

```c
if (col == 10)
{
    print_solutiion(board);
    *solutions = *solutions + 1;
    return;              // <- VERY important
}
```

