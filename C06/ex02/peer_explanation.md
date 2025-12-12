# Exercise 02 : ft_rev_params
---

## Overview

* Write a **program** that prints all command-line arguments **in reverse order**.
* Print **one argument per line**.
* Print **everything except `argv[0]`**.
* Allowed function: `write`.

Example:

```bash
./a.out test1 test2 test3
```

Output:

```text
test3
test2
test1
```

---

## Reminder: what `argc` and `argv` are (and why only `main` gets them)

* The **OS** passes command-line arguments **only at program entry**, and in C that entry point is `main`.
* So `argc` / `argv` are only “given for free” to `main`.
* Any other function can use them only if you **pass them explicitly**.

---

## Memory layout (what you’re iterating over)

When you run:

```bash
./a.out test1 test2 test3
```

You conceptually get:

```
argc = 4

argv ---> +--------------------------+
         | argv[0] -> "./a.out"      |
         | argv[1] -> "test1"        |
         | argv[2] -> "test2"        |
         | argv[3] -> "test3"        |
         | argv[4] -> NULL           |
         +--------------------------+
```

Each `argv[i]` points to a C-string:

```
argv[3] -> 't' 'e' 's' 't' '3' '\0'
```

Two important terminators:

* End of the **argument list**: `NULL` (pointer)
* End of each **string**: `'\0'` (character)

---

# Solution A (commented one) — reverse with indices

```c
void ft_putchar(char c){
    write(1, &c, 1);
}

int main(int argc, char *argv[]){
    int i;
    int j;

    i = argc - 1;
    while (i > 0)
    {
        j = 0;
        while (argv[i][j])
        {
            ft_putchar(argv[i][j]);
            j++;
        }
        ft_putchar('\n');
        --i;
    }
    return (0);
}
```

## What it does

### Outer loop (reverse arguments)

* Starts at `i = argc - 1` (last real argument index)
* Goes down until `i > 0` (stops before `argv[0]`)

So if `argc = 4`, indices are:

* `i = 3` → prints `argv[3]` (`test3`)
* `i = 2` → prints `argv[2]` (`test2`)
* `i = 1` → prints `argv[1]` (`test1`)
* stop when `i` becomes `0`

### Inner loop (characters of one argument)

* `j = 0`
* prints `argv[i][j]` until it hits `'\0'`

## Why this solution is good

* Very explicit: you clearly see **reverse order**
* Shows clearly:

  * `i` controls which argument
  * `j` controls which character inside that argument

---

# Solution B (your final one) — reverse by decreasing `argc`

```c
void ft_putstr(char *str){
    while (*str)
        write(1, str++, 1);
    write(1, "\n", 1);
}

int main(int argc, char *argv[]){
    while (--argc)
        ft_putstr(argv[argc]);
}
```

## What it does

This solution uses a clever fact:

* `argc` is the **count** of arguments
* The last argument is at index `argc - 1`

### The loop

```c
while (--argc)
```

This is **pre-decrement**, meaning:

* Decrease `argc` first
* Then test if it’s non-zero

Let’s trace with `argc = 4`:

| Step | `--argc` becomes | Condition true? | Printed   |
| ---- | ---------------- | --------------- | --------- |
| 1    | 3                | yes             | `argv[3]` |
| 2    | 2                | yes             | `argv[2]` |
| 3    | 1                | yes             | `argv[1]` |
| 4    | 0                | no (stop)       | (none)    |

So it prints exactly:

* `argv[3]`
* `argv[2]`
* `argv[1]`

And it automatically skips `argv[0]` because the loop stops at 0.

## Why `ft_putstr` is correct

```c
while (*str)
    write(1, str++, 1);
```

* `*str` is the current character
* stops at `'\0'`
* `str++` moves to the next character
* prints one byte at a time
* then prints newline

---

# Comparison (Solution A vs Solution B)

| Aspect                   | Solution A (i/j indices)     | Solution B (decrement argc)        |
| ------------------------ | ---------------------------- | ---------------------------------- |
| Clarity for beginners    | Very high                    | Medium (pre-decrement trick)       |
| Lines of code            | Longer                       | Shorter                            |
| Reverse order logic      | Explicit (`i = argc-1; i--`) | Implicit (`while (--argc)`)        |
| Risk of confusion        | Low                          | Higher (pre-decrement + stop at 0) |
| Uses `argc` meaningfully | Yes                          | Yes (very)                         |

Both are correct and use only `write`.

---

## Common mistakes this exercise targets

1. Printing `argv[0]` by accident.
2. Printing in normal order instead of reverse.
3. Using wrong stop condition:

   * `while (argc--)` is dangerous because it reaches `argv[0]` and then goes negative if not careful.
4. Confusing:

   * `NULL` (end of argv list)
   * `'\0'` (end of string)

---

# Memory diagram recap for reverse printing

You’re not changing strings; you’re just changing **which pointer you pick**:

```
argv[1] -> "test1\0"
argv[2] -> "test2\0"
argv[3] -> "test3\0"
```

Reverse printing means accessing pointers in this order:

```
argv[3], argv[2], argv[1]
```

Then for each selected pointer, you walk its chars until `'\0'`.

---

# Peer Evaluation Q&A

## Q1: Why does Solution B stop exactly at `argv[1]`?

Because `while (--argc)` stops when `argc` becomes `0`. The last printed index is `1`.

## Q2: Why not print `argv[0]`?

`argv[0]` is the program name/path. The subject wants only **given arguments**.

## Q3: Where does the reverse order come from?

* Solution A: `i` starts at `argc - 1` and decrements.
* Solution B: `argc` is decremented first, so it produces indices `argc-1 … 1`.

## Q4: Do we need `argc` at all?

Not strictly—because `argv` ends with `NULL`. But here reverse order is easiest with `argc`.

## Q5: Can other functions access `argv` automatically?

No. Only `main` receives `argc/argv` from the OS. Other functions need you to pass them.

---

