# 🧠 Rush01 — Peer Explanation

## 🎯 Goal

Implement:

```c
void rush(int x, int y);
```

Where:

* `x` → width (columns)
* `y` → height (rows)

The function prints a rectangle using only `write`.

Example:

```
rush(5,3)

/***\
*   *
\***/
```

---

## 💡 What Rush01 tests

Rush01 checks if you understood that:

> The algorithm stays identical — only the characters change.

If you rewrote the loops, you misunderstood the project.

---

## 🧠 Core Idea — Coordinate Classification

We do NOT draw lines.

We analyze every coordinate:

```
(row, col)
```

And decide its **role**, then translate that role into a character.

---

## 📐 Grid Mental Model

We scan the rectangle cell-by-cell:

```
(1,1) (1,2) (1,3) ... (1,x)
(2,1) (2,2) (2,3) ...
...
(y,1)       ... (y,x)
```

Each cell belongs to a category.

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

## 🔑 Important Concept — Priority

A corner is also an edge mathematically:

Example `(1,1)`:

* horizontal ✔
* vertical ✔
* corner ✔

But we force priority:

```
Corner > Edge > Inside
```

So `(1,1)` becomes only **corner**.

---

## 🧠 identify_cell_type — Geometry Brain

This function decides the position meaning.

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

### Why no `else if`?

Each `if` returns immediately → no nesting needed → clearer.

---

## 🎨 get_cell_char — Rush01 Style Mapping

Now we translate meaning → symbol.

### Rush01 character set

| Type            | Character |
| --------------- | --------- |
| TOP_LEFT        | `/`       |
| TOP_RIGHT       | `\`       |
| BOTTOM_LEFT     | `\`       |
| BOTTOM_RIGHT    | `/`       |
| HORIZONTAL_EDGE | `*`       |
| VERTICAL_EDGE   | `*`       |
| INSIDE          | space     |

⚠ Important:
Backslash in C must be escaped → `'\\'`

```c
static char get_cell_char(int type)
{
	if (type == CELL_TOP_LEFT || type == CELL_BOTTOM_RIGHT)
		return ('/');
	if (type == CELL_TOP_RIGHT || type == CELL_BOTTOM_LEFT)
		return ('\\');
	if (type == CELL_HORIZONTAL_EDGE || type == CELL_VERTICAL_EDGE)
		return ('*');
	return (' ');
}
```

---

## 🏗 rush — The Engine

The traversal never changes.

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

## 🔗 Function Prototypes

```c
void ft_putchar(char c);
```

Needed because each `.c` file is compiled separately.

Compiler checks signature → linker connects files.

---

## 📏 Output Size

Characters printed:

```
(x * y) + y newlines
```

Example:

```
5 × 3 + 3 = 18 characters
```

---

## 📘 Key Lessons

### Separation of concerns

| Layer              | Role      |
| ------------------ | --------- |
| identify_cell_type | geometry  |
| get_cell_char      | style     |
| rush               | traversal |
| ft_putchar         | IO        |

---

### Priority classification

Corners override edges.

---

### Same engine, different skin

Rush01 only changed characters — not logic.

---

## 🏁 Final Understanding

Rush01 confirms the rectangle printer is actually:

> A coordinate → semantic → character rendering system

---


