# 🧠 Rush00 — Peer Explanation

## 🎯 Goal of the project

We must implement:

```c
void rush(int x, int y);
```

Where:

* `x` = width (columns)
* `y` = height (rows)

The function prints a rectangle using only `write()`.

Example:

```
rush(5, 3)

o---o
|   |
o---o
```

Important rule:
The evaluator **changes `main`** during correction.
So `rush()` must work correctly for any values.

---

## 🧩 Core Idea — This project is NOT drawing

This project is actually:

> **A coordinate classification engine**

We don't “draw lines”.
We **analyze each position in a grid** and decide what character belongs there.

---

## 📐 Grid Mental Model

We scan the rectangle cell by cell:

```
(row, col)

(1,1) (1,2) (1,3) ...
(2,1) (2,2) (2,3) ...
...
(y,1)       ... (y,x)
```

Each cell belongs to one category:

| Type            | Meaning                  |
| --------------- | ------------------------ |
| Top-Left        | first row + first column |
| Top-Right       | first row + last column  |
| Bottom-Left     | last row + first column  |
| Bottom-Right    | last row + last column   |
| Horizontal edge | top or bottom row        |
| Vertical edge   | left or right column     |
| Inside          | everything else          |

---

## ❗ Important Special Cases

| Case             | Output          |
| ---------------- | --------------- |
| x <= 0 or y <= 0 | print nothing   |
| x == 1           | vertical line   |
| y == 1           | horizontal line |
| x == 1 && y == 1 | single corner   |

---

## 🏗 Architecture

```
main → rush → identify_cell_type → get_cell_char → ft_putchar → write
```

Each function has a single responsibility.

---

## 1️⃣ ft_putchar — low level printer

Prints one character only.

```c
void ft_putchar(char c)
{
	write(1, &c, 1);
}
```

We print the rectangle by calling this many times.

---

## 2️⃣ identify_cell_type — geometry brain

Returns **where we are**, not what to print.

We use constants instead of raw numbers:

```c
#define CELL_TOP_LEFT 0
#define CELL_TOP_RIGHT 1
#define CELL_BOTTOM_LEFT 2
#define CELL_BOTTOM_RIGHT 3
#define CELL_HORIZONTAL_EDGE 4
#define CELL_VERTICAL_EDGE 5
#define CELL_INSIDE 6
```

### Why not return a character?

Because characters change between rush00 → rush04
But geometry never changes.

So we separate:

```
meaning  != appearance
```

---

### Implementation

```c
int identify_cell_type(int row, int col, int width, int height)
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

---

### Why `if` and not `else if`?

Because each condition returns immediately:

> Early return keeps code flat and readable, nesting is unnecessary.

---

## 3️⃣ get_cell_char — style layer

Now we translate **meaning → character**

For Rush00:

| Type       | Char  |   |
| ---------- | ----- | - |
| Corners    | `o`   |   |
| Horizontal | `-`   |   |
| Vertical   | `     | ` |
| Inside     | space |   |

```c
char get_cell_char(int type)
{
	if (type == CELL_TOP_LEFT
	 || type == CELL_TOP_RIGHT
	 || type == CELL_BOTTOM_LEFT
	 || type == CELL_BOTTOM_RIGHT)
		return ('o');
	if (type == CELL_HORIZONTAL_EDGE)
		return ('-');
	if (type == CELL_VERTICAL_EDGE)
		return ('|');
	return (' ');
}
```

### Why group corners?

They all print the same character → avoids duplicated code.

---

## 4️⃣ rush — the engine

We scan rows first, columns second:

```
for each row
    for each column
        classify
        translate
        print
    newline
```

### Implementation

```c
void rush(int width, int height)
{
	int row;
	int col;

	if (width <= 0 || height <= 0)
		return ;

	row = 1;
	while (row <= height)
	{
		col = 1;
		while (col <= width)
		{
			ft_putchar(get_cell_char(
				identify_cell_type(row, col, width, height)));
			col++;
		}
		ft_putchar('\n');
		row++;
	}
}
```

---

## 🔍 Why prototypes are needed

```c
void ft_putchar(char c);
void rush(int x, int y);
```

Because:

> The compiler compiles each `.c` file separately and must know the function signature before linking.

---

## 🧠 Key Learning Concepts

### Separation of concerns

We separated:

| Layer    | Responsibility |
| -------- | -------------- |
| Geometry | where are we   |
| Style    | what symbol    |
| Engine   | traversal      |
| IO       | printing       |

This makes Rush01-04 trivial later.

---

### Traversal principle

Rows outside, columns inside → guarantees correct newline placement.

---

### Early return pattern

Avoids nesting and improves readability.

---

### Compiler vs Linker

Prototype helps the **compiler**
Object files connected by the **linker**

---

## 🧪 Output size reasoning

Total characters printed:

```
(width × height) + height newlines
```

Example:

```
4 × 3 + 3 = 15 characters
```

---

## 🏁 Final Understanding

The rush project is not about ASCII art.

It is about:

> Transforming coordinates → semantic position → character → output

Once understood, every Rush version becomes just a different **character mapping table**.

---

## 💡 Big Takeaway

We didn’t write a rectangle printer.

We wrote a **rendering engine**.

And that is why the same logic works for Rush00 → Rush04.

---

