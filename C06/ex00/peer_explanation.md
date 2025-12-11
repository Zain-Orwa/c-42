# 🧩 **Peer Explanation — Exercise 00: `ft_print_program_name`**

---

## 📌 **1. Goal of the Exercise**

The task is simple:

> **Write a program that prints its own name**, followed by a newline.
> No more, no less.

You're only allowed to use the function:

```c
write
```

The program must contain a `main()`—because unlike previous exercises, this is a **real program**, not a library function.

---

## 📁 **2. File Structure**

* Turn-in directory: `ex00/`
* File to submit: `ft_print_program_name.c`
* Allowed functions: `write`

---

## 🧠 **3. Core Concepts You Must Understand**

### ### 3.1 What is `argv`?

When a program starts, the OS calls your `main` like this:

```c
int main(int argc, char *argv[])
```

* `argc` = number of arguments.
* `argv` = array (list) of strings (char pointers).

  * `argv[0]` → always the **name of the program**.
  * `argv[1]` → first argument.
  * `argv[2]` → second argument.
  * etc.

For this exercise, we only care about:

```
argv[0]
```

because it is literally the program name.

Example:

```bash
$ ./a.out
argv[0] = "./a.out"
```

---

### 3.2 What does `(void)argc;` mean?

You aren’t using `argc`.
If you don’t use a function parameter, the compiler may warn you:

```
unused parameter 'argc'
```

To silence that warning **correctly**, we write:

```c
(void)argc;
```

This simply tells the compiler:
“I know I'm not using `argc`, don’t warn me.”

---

### 3.3 What is `ft_putchar`?

A small wrapper around `write`.

```c
void ft_putchar(char c)
{
    write(1, &c, 1);
}
```

* `1` = file descriptor for **stdout**
* `&c` = address of the character
* `1` (last one) = number of bytes to write
  → we are printing exactly one character.

---

## 🔎 **4. Code Explanation Line by Line**

### ✔ Final code (your submitted version)

```c
#include <unistd.h>
#include <stdio.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

int main(int argc, char *argv[]){
	int i;

	(void)argc;	

	i = 0;
	while (argv[0][i] != '\0')
	{
		ft_putchar(argv[0][i]);
		i++;
	}
	ft_putchar('\n');

	return (0);
}
```

---

### 🧵 Step-by-step explanation

#### **1. Headers**

```c
#include <unistd.h>
#include <stdio.h>
```

* `unistd.h` needed for `write`.
* `stdio.h` is not needed, but it does no harm.
  (If you want to be “pure”, you can remove it.)

---

#### **2. `ft_putchar`**

```c
void ft_putchar(char c){
    write(1, &c, 1);
}
```

* Reusable function for printing one character using only `write`.

---

#### **3. main function**

```c
int main(int argc, char *argv[])
```

* `argc` counts the arguments.
* `argv` is a list of C-strings.

  * `argv[0]` is the program name.

---

#### **4. Silence unused variable**

```c
(void)argc;
```

Because we never use `argc`.

---

#### **5. Loop over characters of `argv[0]`**

```c
i = 0;
while (argv[0][i] != '\0')
{
	ft_putchar(argv[0][i]);
	i++;
}
```

* `argv[0]` is a string.
* Strings end with the null terminator `'\0'`.
* We print character by character until we reach it.

---

### **6. Print newline**

```c
ft_putchar('\n');
```

Required by the subject.

---

### **7. Return success**

```c
return (0);
```

Program ends normally.

---

## 🧪 **5. Example Output**

If the program is compiled and run like this:

```bash
$ gcc ft_print_program_name.c
$ ./a.out
```

Output will be:

```
./a.out
```

If you rename the binary:

```bash
$ mv a.out hello42
$ ./hello42
```

Output:

```
./hello42
```

The program automatically prints whatever its current filename is.

---

## 🔍 **6. Memory Diagram (Stack View)**

At program start, memory looks like this:

```
 main frame
 ┌──────────────────────────┐
 │ argc = 1                 │
 │ argv →  ┌──────────────┐ │
 │         │ argv[0] ----┼──────────→ "./a.out\0"
 │         └──────────────┘ │
 │ i (local variable)       │
 └──────────────────────────┘
```

Inside the loop:

```
argv[0] = "./a.out"

Iteration 0: print '.'
Iteration 1: print '/'
Iteration 2: print 'a'
Iteration 3: print '.'
Iteration 4: print 'o'
Iteration 5: print 'u'
Iteration 6: print 't'
Iteration 7: sees '\0' → stop.
```

Then print newline.

---

## 🎯 **7. Key Takeaways for the Exam**

* `argv[0]` always holds the program’s own name.
* You must print char-by-char using `write`.
* Strings end with `'\0'` → loop until you reach it.
* `(void)argc;` prevents warnings.
* No `printf` allowed.

---

## 📘 **8. Clean 42-Style Version Without Extra Includes**

If you want the cleanest official version:

```c
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	main(int argc, char *argv[])
{
	int	i;

	(void)argc;
	i = 0;
	while (argv[0][i])
	{
		ft_putchar(argv[0][i]);
		i++;
	}
	ft_putchar('\n');
	return (0);
}
```

---

