# 🧠 Rush03 — Peer Explanation

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

ABBBC
B   B
ABBBC
```

---

## 💡 What Rush03 verifies

Rush03 checks if you truly understood the Rush concept:

> The algorithm never changes — only the character mapping changes.

If you modified the loops or classification logic, you misunderstood the exercise.

---

## 📐 Thinking in coordinates

We do NOT draw lines.

We evaluate every coordinate:

```
(current_row, current_col)
```

Grid example:

```
(1,1) (1,2) (1,3) ... (1,width)
(2,1) (2,2) (2,3) ...
...
(height,1) ... (height,width)
```

Each position gets a meaning → then a character.

---

## 🏷 Cell types

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

A corner also satisfies edge conditions.

Example `(1,1)`:

* horizontal edge ✔
* vertical edge ✔
* corner ✔

But our program must output only one meaning.

We enforce priority:

```
Corner > Edge > Inside
```

Because `identify_cell_type` returns immediately.

---

## 🧠 identify_cell_type — Geometry brain

Determines the role of a coordinate.

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

### Why simple `if`

Each condition exits immediately → no nested logic → clearer.

---

## 🎨 get_cell_char — Rush03 mapping

Now we convert meaning → character.

### Rush03 character rules

| Cell type     | Output |
| ------------- | ------ |
| left corners  | `A`    |
| right corners | `C`    |
| edges         | `B`    |
| inside        | space  |

```c
static char get_cell_char(int cell_type)
{
	if (cell_type == CELL_TOP_LEFT || cell_type == CELL_BOTTOM_LEFT)
		return ('A');
	if (cell_type == CELL_TOP_RIGHT || cell_type == CELL_BOTTOM_RIGHT)
		return ('C');
	if (cell_type == CELL_HORIZONTAL_EDGE || cell_type == CELL_VERTICAL_EDGE)
		return ('B');
	return (' ');
}
```

---

## 🏗 rush — the engine

Traversal never changes.

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

## 🔗 Why ft_putchar is declared

```c
void ft_putchar(char c);
```

Each `.c` file is compiled separately.
The compiler must know the function signature before linking.

---

## 📏 Output size

```
(width × height) + height newlines
```

Example:

```
5 × 3 + 3 = 18 characters
```

---

## 📘 What changed from Rush02

| Rush   | Corner logic                          |
| ------ | ------------------------------------- |
| Rush02 | top corners same, bottom corners same |
| Rush03 | left corners same, right corners same |

The engine stayed identical.

---

## 🧠 Key understanding

We separated responsibilities:

| Function           | Responsibility |
| ------------------ | -------------- |
| identify_cell_type | geometry       |
| get_cell_char      | appearance     |
| rush               | traversal      |
| ft_putchar         | output         |

---

## 🏁 Final conclusion

Rush03 proves:

> We built a rectangle rendering engine — not a drawing program.

Only the symbol mapping changed.

---


