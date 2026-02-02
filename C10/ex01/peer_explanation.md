# 🐱 `ft_cat` — Peer Explanation

## 🎯 Goal of the Exercise

Recreate a simplified version of the UNIX `cat` command using only system calls (`read`, `write`, `open`, `close`) and respecting 42 restrictions.

The program must:

* Read from files passed as arguments.
* If argument is `-`, read from **standard input**.
* If no arguments are provided, behave like `cat -`.
* Handle multiple files sequentially.
* Never crash on errors.
* Return a proper exit status.

---

# 🧩 High-Level Architecture

The program is divided into clear responsibilities:

| Function           | Responsibility                        |
| ------------------ | ------------------------------------- |
| `main`             | Parse arguments and drive the program |
| `process_argument` | Decide where input comes from         |
| `ft_cat_file`      | Read data and send to output          |
| `write_all`        | Guarantee full writing of data        |
| `display_error`    | Print formatted errors                |
| `ft_strlen`        | Helper to measure string length       |

---

# 🧠 Mental Model of the Program

Think of the program like a **water pipeline system**:

```
File (or STDIN)
      ↓
   read()  --->  buffer (bucket)
      ↓
 write_all()  ---> screen (STDOUT)
```

* `ft_cat_file` is the **pump** that keeps moving data.
* `write_all` ensures nothing spills on the way.

---

# 🔧 Function by Function Breakdown

---

## 1️⃣ `ft_strlen`

```c
static size_t ft_strlen(const char *str)
{
    const char *start = str;
    while (*str)
        str++;
    return (size_t)(str - start);
}
```

### Purpose

Counts characters in a string so we can safely use `write()` without relying on `printf`.

### Why Needed?

The exercise forbids `printf`.
To print messages, we must know string length manually.

### Analogy

Like counting how many steps from your house to the store by walking until the end.

---

## 2️⃣ `display_error`

```c
static void display_error(char *program_name, char *file_name)
{
    int saved_errno = errno;
    char *error_msg = strerror(saved_errno);

    write(2, program_name, ft_strlen(program_name));
    write(2, ": ", 2);
    write(2, file_name, ft_strlen(file_name));
    write(2, ": ", 2);
    write(2, error_msg, ft_strlen(error_msg));
    write(2, "\n", 1);
}
```

### Purpose

Print errors in the classic UNIX format:

```
ft_cat: filename: No such file or directory
```

### Why Pass `program_name`?

> **Question:** Why do we need `program_name`?

Because errors should look professional and match real tools.
Without it we would only print:

```
file.txt: No such file or directory
```

### Why Save `errno`?

System calls may change `errno`, so we store it before doing anything else.

---

## 3️⃣ `write_all` — The Unsung Hero

```c
static int write_all(int fd, char *buffer, ssize_t length)
{
    ssize_t total_written = 0;
    ssize_t bytes_written;

    while (total_written < length)
    {
        bytes_written = write(fd,
                              &buffer[total_written],
                              length - total_written);

        if (bytes_written <= 0)
            return (-1);

        total_written += bytes_written;
    }
    return (0);
}
```

---

### Why Do We Need `write_all`?

> **Question:** Why not just call `write()` once?

Because `write()` does **not guarantee** to write everything.

---

### Partial Writes Problem

Example:

* You ask to write 10 bytes.
* `write()` may return 6.

Without `write_all`, the remaining 4 bytes would be lost.

---

### Memory Diagram

Imagine a buffer:

```
[ H ][ e ][ l ][ l ][ o ]
```

We want to send 5 bytes.

#### Possible behavior:

| Call | Asked | Actually Written | Remaining |
| ---- | ----- | ---------------- | --------- |
| 1    | 5     | 3                | 2         |
| 2    | 2     | 2                | 0         |

`write_all` loops until nothing remains.

---

### Pointer Arithmetic Question

> **Question:** Why `buffer + total_written`?

Because we must continue where we stopped.

```
buffer[0..9]  → first chunk
buffer[10..19] → second chunk
```

`buffer + total_written` jumps to the correct starting point.

---

### Type Question

> **Question:** Why `ssize_t` for length?

Because `read()` and `write()` return `ssize_t`.
Using the same type prevents overflow and mismatch.

---

### Infinite Loop Trap

> **Question:** What if `write()` returns 0?

Then the loop would never progress → infinite loop.
That’s why we check `<= 0`.

---

## 4️⃣ `ft_cat_file`

```c
static void ft_cat_file(int fd, char *program_name, char *file_name)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (write_all(1, buffer, bytes_read) < 0)
        {
            display_error(program_name, file_name);
            g_exit_status = 1;
            break;
        }
    }

    if (bytes_read < 0)
    {
        display_error(program_name, file_name);
        g_exit_status = 1;
    }
}
```

---

### Purpose

This is the **engine** of the program.

* Read chunks from input.
* Send them to output.

---

### Invisible Cursor Concept

> **Question:** How does it continue reading where it stopped?

The OS keeps a hidden file cursor.

Example with a 60,000 byte file and 29,000 buffer:

```
read → bytes 0..28999
read → bytes 29000..57999
read → bytes 58000..59999
read → 0 (EOF)
```

We don’t manage the cursor — the OS does.

---

### Why Pass `bytes_read` to `write_all`?

> **Question:** Why not pass BUFFER_SIZE?

Because the last read may return less than buffer size.
We must write **exactly what was read**, not the whole buffer.

---

## 5️⃣ `process_argument`

```c
static void process_argument(char *arg, char *program_name)
{
    int fd;

    if (arg[0] == '-' && arg[1] == '\0')
        fd = 0;
    else
        fd = open(arg, O_RDONLY);

    if (fd < 0)
    {
        display_error(program_name, arg);
        g_exit_status = 1;
        return;
    }

    ft_cat_file(fd, program_name, arg);

    if (fd != 0)
        close(fd);
}
```

---

### Why Do We Need This Function?

> **Question:** Why not let `ft_cat_file` open files?

**Separation of concerns.**

* `process_argument` → opens/closes and chooses source
* `ft_cat_file` → only reads and writes

---

### The Dash (`-`) Convention

> **Question:** Where does the dash come from?

From the user:

```
./ft_cat -
```

Dash means: **read from standard input.**

---

### Why Not Exit on Error?

> **Question:** Why `return` instead of `exit(1)`?

Because with multiple files we must continue processing others.

Example:

```
./ft_cat good.txt bad.txt ok.txt
```

We skip bad.txt but still print ok.txt.

---

## 6️⃣ `main`

```c
int main(int argc, char *argv[])
{
    int i;
    char *program_name;

    program_name = basename(argv[0]);

    if (argc == 1)
        process_argument("-", program_name);
    else
    {
        i = 1;
        while (i < argc)
            process_argument(argv[i++], program_name);
    }

    return (g_exit_status);
}
```

---

### Responsibilities

1. Determine program name
2. Handle “no arguments” case
3. Loop through arguments
4. Return final status

---

### Why Start at `i = 1`?

> **Question:** Why not from 0?

Because:

* `argv[0]` is the program name
* real arguments start at `argv[1]`

---

### Why Return `g_exit_status`?

> **Question:** Why not always return 0?

To tell the shell whether **any error happened**.

---

# 🧪 Example Usages

### Read a file

```
./ft_cat file.txt
```

### Read from stdin

```
./ft_cat -
```

### Mix both

```
./ft_cat file1 - file2
```

### No arguments (same as `-`)

```
./ft_cat
```

---

# 🧠 Final Understanding Summary

* `main` drives the program
* `process_argument` opens sources
* `ft_cat_file` pumps data
* `write_all` guarantees delivery
* `display_error` reports problems

---

# 🏁 Conclusion

This implementation faithfully mimics UNIX `cat` behavior while respecting 42 restrictions.

Key lessons learned:

* System calls can behave unexpectedly
* Partial writes must be handled
* Separation of concerns leads to clean design
* Global exit status allows graceful multi-file processing

---

## 🎉 End Result



