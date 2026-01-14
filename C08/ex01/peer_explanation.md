````markdown
# Ex01: ft_boolean.h – peer_explanation.md

## 🧠 Goal of the exercise

You **only write the header file `ft_boolean.h`**.

The Moulinette / exam will compile your header together with a **given `main.c`** (you do *not* submit this file).  
Your header must provide:

- a custom “boolean” type `t_bool`
- macros to check if a number is even  
- constants/macros for `TRUE`, `FALSE`, `SUCCESS`
- messages `EVEN_MSG` and `ODD_MSG`

So the test program can decide whether the number of arguments is **even or odd** and print the correct message.

---

## 📂 Files involved

### ✅ Your file

```c
/* ft_boolean.h */

#ifndef FT_BOOLEAN_H
# define FT_BOOLEAN_H

# include <unistd.h>

# define EVEN(nbr) ((nbr) % 2 == 0)
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define EVEN_MSG "I have an even number of arguments.\n"
# define ODD_MSG  "I have an odd number of arguments.\n"

typedef int	t_bool;

#endif
````

### 📎 Given test file (approximate from subject)

```c
/* main.c – provided by the subject */

#include "ft_boolean.h"

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

t_bool	ft_is_even(int nbr)
{
	return (EVEN(nbr) ? TRUE : FALSE);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (ft_is_even(argc - 1) == TRUE)
		ft_putstr(EVEN_MSG);
	else
		ft_putstr(ODD_MSG);
	return (SUCCESS);
}
```

You don’t submit `main.c`, but understanding it is crucial.

---

## 🧱 How `main.c` and `ft_boolean.h` work together

### 1. Preprocessing stage – `#include` and `#define`

When you compile:

```bash
cc main.c -o ft_boolean
```

the **preprocessor** runs first.

1. `#include "ft_boolean.h"`

   → The compiler literally copies the *contents* of `ft_boolean.h` into `main.c` at that line.
   After preprocessing, the compiler sees **one big file** that contains:

   * macros `EVEN`, `TRUE`, `FALSE`, `SUCCESS`, `EVEN_MSG`, `ODD_MSG`
   * `typedef int t_bool;`
   * the code for `ft_putstr`, `ft_is_even`, and `main`.

2. `#define` macros

   Anywhere the compiler sees:

   * `EVEN(x)` → replaced by `((x) % 2 == 0)`
   * `TRUE`    → replaced by `1`
   * `FALSE`   → replaced by `0`
   * `SUCCESS` → replaced by `0`
   * `EVEN_MSG` / `ODD_MSG` → replaced by the literal strings.

   Example inside `ft_is_even`:

   ```c
   t_bool	ft_is_even(int nbr)
   {
       return (EVEN(nbr) ? TRUE : FALSE);
   }
   ```

   After macro expansion, the compiler *actually* sees:

   ```c
   t_bool	ft_is_even(int nbr)
   {
       return (((nbr) % 2 == 0) ? 1 : 0);
   }
   ```

   So the **header gives the “vocabulary”** that the `.c` file uses.

### 2. Compilation & linking stages

* After preprocessing, the compiler checks types:

  * `t_bool` is known as `int` thanks to `typedef int t_bool;`
  * `ft_is_even` returns a `t_bool`, so effectively an `int`.
* The compiler can now generate machine code.
* The linker then builds the final executable `ft_boolean`.

So the “communication” between header and main is:

* main **includes** the header
* macros & typedefs from the header **influence** how functions in main are compiled and behave.

---

## 🔍 Line-by-line explanation of `ft_boolean.h`

```c
#ifndef FT_BOOLEAN_H
#define FT_BOOLEAN_H
```

* **Include guard** – ensures the header’s contents are only included **once** per compilation unit.
* Avoids “redefinition” errors if the header is included multiple times.

```c
#include <unistd.h>
```

* Gives access to the `write` function used in `ft_putstr` (in `main.c`).

```c
#define EVEN(nbr) ((nbr) % 2 == 0)
```

* Macro that checks if a number is even.
* `(nbr) % 2` → remainder of dividing by 2.
* If remainder is 0 → number is even.
* Entire macro evaluates to either `1` (true) or `0` (false) as an `int`.
* Extra parentheses **protect** against precedence bugs when you pass expressions:

  ```c
  EVEN(argc - 1)  // becomes (((argc - 1) % 2) == 0)
  ```

```c
#define TRUE 1
#define FALSE 0
```

* Just constants representing boolean values.
* Still of type `int` (because macro substitution).

```c
#define SUCCESS 0
```

* Used as the **return value of `main`**.
* `0` conventionally means “program succeeded”.

```c
#define EVEN_MSG "I have an even number of arguments.\n"
#define ODD_MSG  "I have an odd number of arguments.\n"
```

* Two constant strings used for output.
* Ending with `\n` ensures the output is followed by a newline.

```c
typedef int t_bool;
```

* Creates a new type name `t_bool` that is really just an `int`.
* Used for clarity: when you see `t_bool`, you know it behaves like a boolean.

```c
#endif
```

* Closes the include guard started with `#ifndef`.

---

## 🔧 Functions in `main.c`

### 1. `ft_putstr`

```c
void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}
```

* Prints a C-string to standard output (fd 1).
* `while (*str)` loops until the current character is `'\0'`.
* `write(1, str++, 1);`

  * `str` points to the current character.
  * `write` prints 1 byte (that character).
  * `str++` moves the pointer to the next character.

**Connection to header:**

* `#include <unistd.h>` from the header makes `write` available.
* `ft_putstr` later uses `EVEN_MSG` or `ODD_MSG` from the header as its `str` argument.

Example:

```c
ft_putstr(EVEN_MSG);
```

After macro expansion:

```c
ft_putstr("I have an even number of arguments.\n");
```

---

### 2. `ft_is_even`

```c
t_bool	ft_is_even(int nbr)
{
	return (EVEN(nbr) ? TRUE : FALSE);
}
```

* Parameter `nbr` is an `int`.
* Uses the macro `EVEN(nbr)` to test parity.
* Ternary operator:

  * if `EVEN(nbr)` is non-zero → returns `TRUE` (i.e., `1`)
  * else → returns `FALSE` (i.e., `0`)
* Return type is `t_bool` (alias for `int`).

**Connection to header:**

* Uses `t_bool`, `EVEN`, `TRUE`, `FALSE` – all defined in `ft_boolean.h`.

After macro expansion this function is effectively:

```c
int	ft_is_even(int nbr)
{
	return (((nbr) % 2 == 0) ? 1 : 0);
}
```

---

### 3. `main`

```c
int	main(int argc, char **argv)
{
	(void)argv;
	if (ft_is_even(argc - 1) == TRUE)
		ft_putstr(EVEN_MSG);
	else
		ft_putstr(ODD_MSG);
	return (SUCCESS);
}
```

Let’s break down every piece.

#### Parameters: `int argc, char **argv`

* `argc` = **argument count**

  * Number of strings passed to the program **including** the program name itself.
* `argv` = **argument vector**

  * Array of `char *`
  * `argv[0]` → name of the program (e.g., `"./ft_boolean"`)
  * `argv[1]`, `argv[2]`, … are actual user arguments.

```c
(void)argv;
```

* We don’t use `argv`, but we must still accept it because the subject gives us this main.
* Casting to `(void)` is a classic way to **silence “unused parameter” warnings**.

#### Why `argc - 1`?

The exercise wants:

> “I have an even/odd **number of arguments**.”

But the C runtime counts like this:

| launched command        | argc | user arguments | count of user arguments |
| ----------------------- | ---- | -------------- | ----------------------- |
| `./ft_boolean`          | 1    | (none)         | 0                       |
| `./ft_boolean hello`    | 2    | `hello`        | 1                       |
| `./ft_boolean hello 42` | 3    | `hello`, `42`  | 2                       |

So:

* `argc` = 1 + (number of user arguments)
* To get the **number of user arguments**, we do:

  ```c
  argc - 1
  ```

This value is what we want to check for even/odd.

#### Using `ft_is_even(argc - 1)`

```c
if (ft_is_even(argc - 1) == TRUE)
    ft_putstr(EVEN_MSG);
else
    ft_putstr(ODD_MSG);
```

Communication chain:

1. `main` calculates `argc - 1` (user argument count).
2. `main` calls `ft_is_even` and passes that number.
3. `ft_is_even` uses the macro `EVEN` to calculate parity and returns `TRUE` or `FALSE`.
4. Back in `main`, the `if` compares the result to `TRUE`:

   * if equal → print `EVEN_MSG`.
   * otherwise → print `ODD_MSG`.
5. `ft_putstr` prints the chosen message using `write`.
6. `main` returns `SUCCESS` (`0`) to the OS.

---

## 🧮 Step-by-step execution examples

### Example 1 – No extra arguments

Command:

```bash
./ft_boolean
```

Then:

* `argc = 1` (only `argv[0]` = program name)
* `argc - 1 = 0`

Trace inside `main`:

1. `ft_is_even(argc - 1)` → `ft_is_even(0)`

2. Inside `ft_is_even(0)`:

   * `EVEN(nbr)` → `EVEN(0)` → `((0) % 2 == 0)` → `0 % 2` is `0` → `0 == 0` → `1`
   * ternary: `1 ? TRUE : FALSE` → `TRUE` → `1`
   * function returns `1`.

3. Back to `main`:

   ```c
   if (ft_is_even(0) == TRUE)
   ```

   → `if (1 == 1)` → condition true.

4. So it executes:

   ```c
   ft_putstr(EVEN_MSG);
   ```

   which prints:

   ```
   I have an even number of arguments.
   ```

5. `main` returns `SUCCESS` (`0`).

Result: **“even number of arguments”**, because `0` is even.

---

### Example 2 – One extra argument

Command:

```bash
./ft_boolean hello
```

Now:

* `argc = 2` (`argv[0] = "./ft_boolean"`, `argv[1] = "hello"`)
* `argc - 1 = 1`

Trace:

1. `ft_is_even(1)`
2. `EVEN(1)` → `(1 % 2 == 0)` → `1 % 2` is `1` → `1 == 0` → `0`
3. Ternary: `0 ? TRUE : FALSE` → `FALSE` → `0`
4. So `ft_is_even(1)` returns `0`.
5. `if (0 == TRUE)` → `if (0 == 1)` → false.
6. `else` branch: `ft_putstr(ODD_MSG);`

Output:

```
I have an odd number of arguments.
```

---

### Example 3 – Three extra arguments

Command:

```bash
./ft_boolean one two three
```

* `argc = 4`
* `argc - 1 = 3`

Trace:

1. `ft_is_even(3)` → `EVEN(3)` → `(3 % 2 == 0)` → `3 % 2` = `1` → `1 == 0` → `0` → `FALSE`.
2. Condition fails → odd message printed.

If we add a fourth argument:

```bash
./ft_boolean one two three four
```

* `argc = 5`, `argc - 1 = 4`
* `EVEN(4)` → `(4 % 2 == 0)` → true → prints even message.

---

## 🧪 Peer evaluation Q&A

**Q1. What does `typedef int t_bool;` do exactly?**
It creates a new type name `t_bool`, which is just an alias for `int`. So whenever we write `t_bool`, the compiler treats it as `int`. It is used to make it clear that this `int` is meant to hold a boolean value (`TRUE` or `FALSE`).

---

**Q2. Why do we need parentheses around `nbr` in `EVEN(nbr)`?**

```c
#define EVEN(nbr) ((nbr) % 2 == 0)
```

Without parentheses, passing expressions can break due to operator precedence:

```c
EVEN(argc - 1)
// with parentheses → (((argc - 1) % 2) == 0)
// without them → argc - 1 % 2 == 0   // which is parsed differently
```

The parentheses guarantee the macro behaves correctly for any expression.

---

**Q3. Why do we use `argc - 1` and not just `argc`?**

Because `argc` counts **all** arguments, including `argv[0]`, which is the program name.
The exercise wants to count only the **arguments given by the user**, so we subtract 1.

---

**Q4. Is there any real difference between `TRUE`/`FALSE` and `1`/`0`?**

At the machine level, no: they are all just integers.
But using `TRUE` and `FALSE` makes the code more **readable** and expresses clear intent that the variable represents a boolean state.

---

**Q5. How do `ft_putstr` and `ft_is_even` “communicate” with `main`?**

* `main` **calls** `ft_is_even` with `argc - 1`.
* `ft_is_even` computes the result using header macros, then **returns** `TRUE` or `FALSE` to `main`.
* Based on that result, `main` chooses which string to pass to `ft_putstr`.
* `ft_putstr` uses `write` (enabled by `#include <unistd.h>` in the header) to send characters to the terminal.

So the flow is:

```text
main → ft_is_even → (macros from header) → return TRUE/FALSE → main → ft_putstr → write → screen
```

---

**Q6. Why do we return `SUCCESS` instead of writing `return 0;` directly?**

`SUCCESS` is a macro for `0`. Using this name documents the meaning:
`0` is not just “some number”, it means “program finished successfully”.

---

That’s the full story of how `ft_boolean.h` + the given `main.c` cooperate:
the header provides **types and macros**, the implementation file uses them to build the program logic, and `argc - 1` ensures we are counting only the user’s arguments when deciding between `EVEN_MSG` and `ODD_MSG`.

```
```

