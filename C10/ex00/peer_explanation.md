## 📌 Project: C10 / ex00 — `ft_display_file`

This program prints the content of a file to **stdout** using only low-level UNIX functions:

* `open()` to open the file
* `read()` to read bytes into a buffer
* `write()` to output bytes to the terminal
* `close()` to release the file descriptor

It also prints specific error messages to **stderr** (fd = 2), following the exercise requirements.

---

## ✅ Final Code (Reference)

```c
/* ft_display_file.c */
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int ft_strlen(char *str){
	int len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void ft_putstr(char *str){
		write(2, str, ft_strlen(str));
}

int ft_display_file(char *file_name){
	int     fd;
	char    buffer[BUFFER_SIZE];
	ssize_t	bytes_read;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (1);

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
		write(1, buffer, bytes_read);
	if (bytes_read < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int main(int argc, char *argv[]){
	if (argc < 2)
	{
		ft_putstr("File name missing.\n");
		return (1);
	}

	if (argc > 2)
	{
		ft_putstr("Too many arguments.\n");
		return (1);
	}

	if (ft_display_file(argv[1]) != 0)
	{
		ft_putstr("Cannot read file.\n");
		return (1);
	}

	return (0);
}
```

---

## 🎯 Goal of the Exercise

* If the user runs the program without a filename → print:

  * `File name missing.`
* If the user passes too many arguments → print:

  * `Too many arguments.`
* If the file can’t be opened or read → print:

  * `Cannot read file.`
* Otherwise → display file content to **stdout**

---

## 🧠 Key Idea: Files are not “strings”

A file can contain **any bytes**, including `'\0'`.
So using `ft_putstr()` to print file content is risky because `ft_putstr()` relies on `ft_strlen()`, which stops at `'\0'`.

✅ **Rule**:

* **Text strings** → `ft_putstr()` / `ft_strlen()`
* **File bytes** → `write(1, buffer, bytes_read)`

---

## 🔍 Main Function Explanation + Questions

### ✅ Argument validation

```c
if (argc < 2)
{
	ft_putstr("File name missing.\n");
	return (1);
}
if (argc > 2)
{
	ft_putstr("Too many arguments.\n");
	return (1);
}
```

### ❓ Question: “When I run `./prog -f mydb.db` is argc 2 or 3?”

* `argc` counts **everything separated by spaces**
* Example: `./prog -f mydb.db`

  * `argv[0] = "./prog"`
  * `argv[1] = "-f"`
  * `argv[2] = "mydb.db"`
  * ✅ `argc = 3`

### ❓ Question: “Why do we check argc before using argv[1]?”

Because if `argc < 2`, then `argv[1]` is **NULL** and calling:

```c
open(argv[1], O_RDONLY);
```

could crash or behave unpredictably.

---

## ✅ The Important Part: Calling a function inside `if`

```c
if (ft_display_file(argv[1]) != 0)
{
	ft_putstr("Cannot read file.\n");
	return (1);
}
```

### ❓ Question: “If the function is inside if, how will it print my file?”

Because the function runs **first**, then `if` checks its return value.

### ❓ Question: “So calling it inside if still prints content?”

✅ Yes.

Execution steps:

1. `ft_display_file(argv[1])` executes
2. Inside it, the file is read + written (content printed)
3. Function returns `0` or `1`
4. `if` checks the returned value

So the `if` is **only for catching errors**, not for printing.

---

## 📂 `ft_display_file()` Explanation + Questions

### Opening the file

```c
fd = open(file_name, O_RDONLY);
if (fd < 0)
	return (1);
```

### ❓ Question: “Do we need argv[1] to be 0 to open file?”

No.

* `argv[1]` is a **string**
* Example: `"notes.txt"`
* `open()` takes that string path

The “0” refers to return values convention:

* `0` = success
* non-zero = error

---

## 📌 How open/read/write works (Diagram)

### Step 1: open()

```
file_name = "notes.txt"
      |
      v
open("notes.txt", O_RDONLY)  ---> returns fd (e.g., 3)
```

* `fd` is like a “handle” to the file in the OS
* `fd = -1` means open failed

---

### Step 2: read() + write() loop

```c
while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	write(1, buffer, bytes_read);
```

### ❓ Question: “Why not read once only?”

Because files can be bigger than the buffer.
We read in chunks until `read()` returns `0`.

### ❓ Question: “Why is this ‘elegant’ loop better?”

Because it guarantees:

* we **only write if bytes_read > 0**
* no fake initialization (like `bytes_read = 1`)
* fewer lines and harder to forget checks

### Read loop behavior

```
read() returns:
  >0  => got data, keep going
   0  => EOF (end of file), stop
  -1  => error
```

---

## 🧾 Buffer and Output Flow (Diagram)

```
[ File on Disk ]
       |
       | read(fd, buffer, 1024)
       v
[ buffer[] in RAM ]  -----> write(1, buffer, bytes_read) -----> Terminal (stdout)
```

* `buffer` is raw bytes, NOT a string
* `bytes_read` tells us exactly how many bytes are valid

---

## 🧠 Memory Layout (Stack) for `ft_display_file`

When `ft_display_file()` is called, it creates a stack frame like:

```
Stack Frame: ft_display_file
+---------------------------+
| bytes_read (ssize_t)      |
+---------------------------+
| buffer[1024] (char array) |
+---------------------------+
| fd (int)                  |
+---------------------------+
| file_name pointer         |
+---------------------------+
```

### Important notes

* `buffer` lives on the stack (fixed size)
* `file_name` is a pointer to a string in `argv[]`
* `fd` is just an integer (file descriptor)

---

## ✅ Why we close(fd)

```c
close(fd);
```

### ❓ Question: “Why close twice in error case sometimes?”

Because if `read()` fails after opening, we must still release the descriptor.

In this version:

* If `read()` fails (`bytes_read < 0`) → close then return
* If success → close at end

---

## ✅ About `ft_putstr` and writing to fd=2

```c
void ft_putstr(char *str){
	write(2, str, ft_strlen(str));
}
```

### ❓ Question: “Why is it writing to 2?”

* `1` = stdout (normal output)
* `2` = stderr (errors)

This exercise wants errors printed separately from normal output.

### ❓ Question: “In your earlier version you used a loop in ft_putstr, is that needed?”

No. One `write()` is enough if you already know the length.

---

## ✅ Common Mistakes (What usually fails ex00)

* Using `ft_putstr()` to print file content (fails with binary or `\0`)
* Not looping `read()` (only prints first chunk)
* Wrong buffer type: `char *buffer[BUFFER_SIZE]` (array of pointers)
* Returning `1` from a `void` function
* Forgetting `close(fd)`

---

## 🧪 Quick Tests

```bash
./ft_display_file
# File name missing.

./ft_display_file a b
# Too many arguments.

./ft_display_file nofile
# Cannot read file.

./ft_display_file myfile.txt
# prints file content
```

---

## Peer Evaluation Q&A

### Q1) Why don’t we use `ft_putstr()` for file content?

Because file data may contain `'\0'` and is not guaranteed to be a valid C-string.

### Q2) What does `read()` return and how do we use it?

* `> 0`: number of bytes read → write them
* `0`: end of file → stop loop
* `-1`: error → handle it

### Q3) Why does the function still display content even inside `if (...)`?

Because function calls execute first. The `if` only checks the return value after.

### Q4) Why use `write(2, ...)` for error messages?

So errors go to stderr and don’t mix with file content output (stdout).

---

