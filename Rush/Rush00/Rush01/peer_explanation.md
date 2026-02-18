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

## 💡 What Rush01 really checks

Rush01 is not a new algorithm.

> The engine is identical to Rush00.
> Only the character mapping changes.

So if you rewrote loops or classification → you misunderstood the project.

---

## 📐 How we think about the rectangle

We don’t draw lines.
We scan coordinates.

Each printed character corresponds to:

```
(current_row, current_col)
```

Example grid:

```
(1,1) (1,2) (1,3) ... (1,width)
(2,1) (2,2) (2,3) ...
...
(height,1) ... (height,width)
```

Every position must be classified.

---

## 🏷 Cell types

We defined constants:

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

## 🔑 Important concept — Priority

A corner logically belongs to edges too.

Example `(1,1)`:

* first row → horizontal edge
* first column → vertical edge
* also → corner

But our program must choose ONE final meaning.

So we enforce:

```
Corner > Edge > Inside
```

Because `identify_cell_type` returns immediately once matched.

---

## 🧠 identify_cell_type — geometry logic

This function decides **where we are**.

```c
static int identify_cell_type(int current_row, int current_col, int width, int height)
{
	if (current_row == 1 && current_col == 1)
		return (CELL_TOP_LEFT);
	if (current_row == 1 && current_col == width)
		return (CELL_TOP_RIGHT);
	if (current_row == height && current_col == 1)
		return (CELL_BOTTOM_LEFT);
	if (current_row == height && current_col == width)
		return (CELL_BOTTOM_RIGHT);
	if (current_row == 1 || current_row == height)
		return (CELL_HORIZONTAL_EDGE);
	if (current_col == 1 || current_col == width)
		return (CELL_VERTICAL_EDGE);
	return (CELL_INSIDE);
}
```

### Why we use simple `if`

Each condition returns immediately → no nesting → clearer logic.

---

## 🎨 get_cell_char — Rush01 mapping

Now we translate meaning → character.

### Rush01 characters

| Cell Type       | Output |
| --------------- | ------ |
| top-left        | `/`    |
| top-right       | `\`    |
| bottom-left     | `\`    |
| bottom-right    | `/`    |
| horizontal edge | `*`    |
| vertical edge   | `*`    |
| inside          | space  |

⚠ Important:
Backslash in C must be escaped → `'\\'`

```c
static char get_cell_char(int cell_type)
{
	if (cell_type == CELL_TOP_LEFT || cell_type == CELL_BOTTOM_RIGHT)
		return ('/');
	if (cell_type == CELL_TOP_RIGHT || cell_type == CELL_BOTTOM_LEFT)
		return ('\\');
	if (cell_type == CELL_HORIZONTAL_EDGE || cell_type == CELL_VERTICAL_EDGE)
		return ('*');
	return (' ');
}
```

---

## 🏗 rush — the engine

The traversal never changes.

```
row loop outside
column loop inside
newline after each row
```

```c
void rush(int x, int y)
{
	int current_row;
	int current_col;
	int cell_type;
	char cell_char;

	if (x <= 0 || y <= 0)
		return;

	current_row = 1;
	while (current_row <= y)
	{
		current_col = 1;
		while (current_col <= x)
		{
			cell_type = identify_cell_type(current_row, current_col, x, y);
			cell_char = get_cell_char(cell_type);
			ft_putchar(cell_char);
			current_col++;
		}
		ft_putchar('\n');
		current_row++;
	}
}
```

---

## 🔗 Why we declare ft_putchar

```c
void ft_putchar(char c);
```

Because each `.c` file is compiled separately.

The compiler must know the function signature before linking object files.

---

## 📏 Output size rule

Total characters printed:

```
(width × height) + height newlines
```

Example:

```
5 × 3 + 3 = 18 characters
```

---

## 📘 Key understanding

### Separation of roles

| Function           | Responsibility |
| ------------------ | -------------- |
| identify_cell_type | geometry       |
| get_cell_char      | appearance     |
| rush               | traversal      |
| ft_putchar         | output         |

---

### Important realization

We did NOT rewrite the rectangle printer.

We only changed the symbol mapping.

---

## 🏁 Final conclusion

Rush01 proves:

> The rush project is a coordinate → meaning → character renderer.

All rushes share the same engine.
Only the character set changes.

---


