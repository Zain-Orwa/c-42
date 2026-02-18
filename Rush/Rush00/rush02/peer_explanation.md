# 🧠 Rush02 — Peer Explanation

## 🎯 Goal

Implement:

```c
void rush(int x, int y);
```

Where:

* `x` → width (columns)
* `y` → height (rows)

The program prints a rectangle using only `write`.

Example:

```
rush(5,3)

ABBBA
B   B
CBBBC
```

---

## 💡 What this exercise really tests

Rush02 checks if you understood:

> The algorithm never changes — only the character mapping changes.

We are not drawing rectangles.

We are **classifying coordinates and translating them into symbols**.

---

## 📐 Grid Thinking (Coordinate System)

We scan the rectangle cell-by-cell:

```
(row, col)

(1,1) (1,2) (1,3) ...
(2,1) (2,2) (2,3) ...
...
(y,1)       ... (y,x)
```

Each position belongs to a category.

---

## 🏷 Cell Types

| Type            | Meaning                  |
| --------------- | ------------------------ |
| TOP_LEFT        | first row + first column |
| TOP_RIGHT       | first row + last column  |
| BOTTOM_LEFT     | last row + first column  |
| BOTTOM_RIGHT    | last row + last column   |
| HORIZONTAL_EDGE | top or bottom row        |
| VERTICAL_EDGE   | left or right column     |
| INSIDE          | middle                   |

We define constants:

```c
#define CELL_TOP_LEFT         0
#define CELL_TOP_RIGHT        1
#define CELL_BOTTOM_LEFT      2
#define CELL_BOTTOM_RIGHT     3
#define CELL_HORIZONTAL_EDGE  4
#define CELL_VERTICAL_EDGE    5
#define CELL_INSIDE           6
```

---

## 🔍 Important Concept — Corners vs Edges

A corner is also mathematically an edge.

Example `(1,1)`:

* top row ✔
* left column ✔
* corner ✔

But we assign **priority**:

```
Corner > Edge > Inside
```

So `(1,1)` becomes **corner only**.

---

## 🧠 identify_cell_type — Geometry Brain

This function decides *where we are*, not what to print.

```c
static int identify_cell_type(int row, int col, int width, int height)
{
	if (row == 1 && col == 1)
		return (CELL_TOP_LEFT);
	if (row == 1 && col == width)
		return (CELL_TOP_RIGHT);
	if (row == height && col == 1)
		return (CELL_BOTTOM_LEFT);
	if (row == height && col == width)
		return (CELL_BOTTOM_RIGHT);
	if (row == 1 || row == height)
		return (CELL_HORIZONTAL_EDGE);
	if (col == 1 || col == width)
		return (CELL_VERTICAL_EDGE);
	return (CELL_INSIDE);
}
```

### Why `if` instead of `else if`

Early return stops execution → avoids nesting → clearer code.

---

## 🎨 get_cell_char — Style Layer (Rush02)

We now translate meaning → character.

### Rush02 Mapping

| Type           | Character |
| -------------- | --------- |
| Top corners    | A         |
| Bottom corners | C         |
| Edges          | B         |
| Inside         | space     |

```c
static char get_cell_char(int type)
{
	if (type == CELL_TOP_LEFT || type == CELL_TOP_RIGHT)
		return ('A');
	if (type == CELL_BOTTOM_LEFT || type == CELL_BOTTOM_RIGHT)
		return ('C');
	if (type == CELL_HORIZONTAL_EDGE || type == CELL_VERTICAL_EDGE)
		return ('B');
	return (' ');
}
```

---

## 🏗 rush — The Engine

The engine scans rows first, columns second.

```
for each row
    for each column
        classify
        translate
        print
    newline
```

```c
void rush(int x, int y)
{
	int row;
	int col;

	if (x <= 0 || y <= 0)
		return;

	row = 1;
	while (row <= y)
	{
		col = 1;
		while (col <= x)
		{
			ft_putchar(get_cell_char(
				identify_cell_type(row, col, x, y)));
			col++;
		}
		ft_putchar('\n');
		row++;
	}
}
```

---

## 🔗 Why function prototypes are needed

```c
void ft_putchar(char c);
```

Because:

> The compiler compiles each `.c` separately and must know the function signature before linking.

---

## 🧪 Output Size

Total characters printed:

```
(x * y) + y newlines
```

Example:

```
5 × 3 + 3 = 18 characters
```

---

## 📘 Key Lessons Learned

### 1️⃣ Separate logic from appearance

Geometry never changes
Characters change every rush

### 2️⃣ Priority classification

Corner overrides edge

### 3️⃣ Rows outside, columns inside

Controls newline placement

### 4️⃣ Early return improves readability

Avoids nested conditions

### 5️⃣ Rush is a rendering engine

We map coordinates → meaning → character → output

---

## 🏁 Final Understanding

Rush02 proves the algorithm is universal.

We didn’t rewrite the program —
we only changed the character table.

---


