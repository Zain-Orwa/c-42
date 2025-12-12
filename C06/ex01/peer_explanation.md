##Exercise 01 : ft_print_params

---

## Overview

* Write a **program** (so you need `main`) that prints **all command-line arguments**, **one per line**, **in the same order**.
* Print **everything except `argv[0]`**.
* Allowed function: `write`.

When you run:

```bash
./a.out test1 test2 test3
```

Your program must output:

```text
test1
test2
test3
```

---

## What `argc` and `argv` really are (and why only `main` gets them)

The **OS** creates your process and passes arguments **only once**, at program entry. In C, that entry point is `main`. So:

* `argc` and `argv` are **only provided to `main`**.
* Other functions can “use them” only if you **explicitly pass them** as parameters.

---

## The memory layout idea (what exists in memory)

### 1) Process memory map (high-level)

```
Text/Code (your compiled instructions)
Data/BSS (globals/statics)
Heap (malloc/free)
...
Stack (function calls, local variables, return addresses)
```

### 2) What the OS prepares for your program (conceptual)

When you run:

```bash
./a.out test1 test2 test3
```

The OS sets up memory so that `main` can receive:

* `argc = 4`
* `argv` points to an array of pointers:

```
argv ---> +--------------------+
          | argv[0] -> "./a.out" |
          | argv[1] -> "test1"   |
          | argv[2] -> "test2"   |
          | argv[3] -> "test3"   |
          | argv[4] -> NULL      |  <-- important terminator
          +--------------------+
```

And each string is a **null-terminated char array**:

```
"test1"  ->  't' 'e' 's' 't' '1' '\0'
```

### 3) Why `argv[argc] == NULL`

This is the “end marker” for the list of argument pointers. That’s why loops like `while (argv[i])` work.

---

## Important: `NULL` vs `'\0'` (the exact reason your warning happened)

* `NULL` is for **pointers** (meaning “points to nothing”).
* `'\0'` is a **character** (byte value 0, meaning “end of string”).

So:

* `argv[i]` has type `char *` → compare to `NULL` (or just use it as a condition).
* `argv[i][j]` has type `char` → compare to `'\0'` (or just use it as a condition).

Correct patterns:

```c
while (argv[i] != NULL)     // iterating arguments
while (argv[i][j] != '\0')  // iterating characters inside one argument
```

---

# Solution 1 explanation (index-based)

```c
void ft_putchar(char c){
    write(1, &c, 1);
}

int main(int argc, char *argv[]){
    int i;
    int j;

    (void)argc;

    i = 1;
    while (argv[i] != NULL)
    {
        j = 0;
        while (argv[i][j])
        {
            ft_putchar(argv[i][j]);
            j++;
        }
        ft_putchar('\n');
        i++;
    }
    return (0);
}
```

## What it does

* Starts at `i = 1` to **skip `argv[0]`**.
* Outer loop: goes argument by argument until it hits `NULL`.
* Inner loop: prints each character of `argv[i]` until it hits `'\0'`.
* Prints `'\n'` after each argument.

## Why `(void)argc;` is used

You’re not using `argc`. Some compilers warn about unused parameters. Casting to void explicitly says:

> “Yes, I know this exists, and I intentionally don’t use it.”

## Memory diagram during printing (conceptual)

Let’s say we are printing `argv[2] == "test2"`:

* `i = 2`
* `j` moves across characters

```
argv[2] --->  't'  'e'  's'  't'  '2'  '\0'
              ^ 
              |
            &argv[2][0]  (j = 0)

then j = 1 points to 'e', etc...
```

This solution is extremely explicit and beginner-friendly because:

* You see clearly “argument index” (`i`)
* You see clearly “character index” (`j`)

---

# Solution 2 explanation (pointer-walking)

```c
void ft_putsrt(char *str){
    while (*str)
        write(1, str++, 1);
    write(1, "\n", 1);
}

int main(int argc, char *argv[]){
    (void)argc;
    while (*(++argv))
        ft_putsrt(*argv);
}
```

## What it does

This version uses **pointer arithmetic** instead of indices.

### Inside `ft_putsrt`

* `str` points to the first character of a string.
* `while (*str)` means: keep going until you reach `'\0'`.
* `write(1, str++, 1)` prints the byte at `str`, then moves `str` to the next character.

So `str` walks like:

```
str -> 't' -> 'e' -> 's' -> 't' -> '1' -> '\0' stop
```

### Inside `main`

This is the key line:

```c
while (*(++argv))
    ft_putsrt(*argv);
```

Step-by-step:

1. `++argv` moves the `argv` pointer from `argv[0]` to `argv[1]`.
2. `*(++argv)` means “take the pointer stored there” (so it becomes `argv[1]`, then `argv[2]`, etc.).
3. The loop stops when that pointer is `NULL`.

So `argv` itself is being moved:

```
argv initially -> &argv[0]
++argv         -> &argv[1]  (skip program name)
++argv         -> &argv[2]
++argv         -> &argv[3]
++argv         -> &argv[4]  and *argv == NULL => stop
```

## Important side-effect of this version

This modifies the local `argv` pointer inside `main` (that’s fine).
But after the loop, `argv` no longer points to the original `argv[0]`.

That’s not a bug here, just something to be aware of.

---

# Comparison of the two solutions (after understanding each one)

## Readability and learning value

| Aspect                        | Solution 1 (indices)                            | Solution 2 (pointers)                              |
| ----------------------------- | ----------------------------------------------- | -------------------------------------------------- |
| Beginner clarity              | Very clear (i/j show positions)                 | More compact but harder to “see” at first          |
| Shows difference NULL vs '\0' | Very explicit (`argv[i] != NULL`, `argv[i][j]`) | Implicit but correct (`*(++argv)`, `while (*str)`) |
| Uses pointer arithmetic       | Minimal                                         | Heavy (both for argv and for characters)           |
| Risk of confusion             | Low                                             | Higher (pre-increment, dereference, side effects)  |
| Common in 42 evaluations      | Very common                                     | Also common, considered “cleaner” by some          |

## Performance (practically)

Both are O(total characters) and use `write`. Performance difference is negligible here.

## Safety / correctness

Both are correct **if** arguments are normal C-strings (they are). Both stop properly because:

* The argument list ends at `NULL`.
* Each string ends at `'\0'`.

---

## Common mistakes this exercise targets

1. **Printing `argv[0]`** (should not print it).
2. Using `'\0'` instead of `NULL` for argument loop:

   * `argv[i] != '\0'` is a type mistake (pointer vs char).
3. Forgetting newline after each argument.
4. Trying to print `argv[i]` with `%s` (not allowed, because only `write`).
5. Confusing:

   * `argv[i]` (pointer to string)
   * `argv[i][j]` (character inside the string)

---

# Memory diagram recap (the “two-level” structure)

Think of it as **two layers**:

## Layer A: list of pointers (ends with NULL)

```
argv[0]  argv[1]  argv[2]  ...  argv[argc-1]  argv[argc]
  |        |        |                |           |
  v        v        v                v           v
"prog"   "a"      "b"              "z"         NULL
```

## Layer B: each pointer points to a C-string (ends with '\0')

```
argv[i] -> 't' 'e' 's' 't' '1' '\0'
```

So:

* End of list: `NULL`
* End of each string: `'\0'`

---

# Peer Evaluation Q&A

## Q1: Why does the loop use `argv[i] != NULL` and not `argv[i] != '\0'`?

Because `argv[i]` is a **pointer** (`char *`). The end of the pointer list is marked by **NULL**. `'\0'` is a **character** used to end strings.

## Q2: Why does `while (argv[i])` work?

Because in C, a pointer used in a condition is treated as:

* false if it is `NULL`
* true otherwise
  So `while (argv[i])` is shorthand for `while (argv[i] != NULL)`.

## Q3: Why do we skip `argv[0]`?

`argv[0]` is the program name/path (`./a.out`). The subject asks to print **only the given arguments**, not the executable name.

## Q4: Why are `argc` and `argv` only in `main`?

Because the OS passes command-line arguments **only at program entry**. In C, the official entry point is `main`. Other functions can access them only if you pass them explicitly.

## Q5: Is Solution 2 “better” than Solution 1?

---


