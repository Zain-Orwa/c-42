# 📚 **libft (C09 / ex00) — Full Peer Explanation**

---

## 🧩 **Exercise Goal**

Create a static library named `libft.a` containing these functions:

```c
void ft_putchar(char c);
void ft_swap(int *a, int *b);
void ft_putstr(char *str);
int  ft_strlen(char *str);
int  ft_strcmp(char *s1, char *s2);
```

Also create a script `libft_creator.sh` that compiles the `.c` files into `.o` files and arches them into `libft.a`.

---

# 📦 **What is a Static Library?**

A **static library** (`.a` file) is a **bundle of compiled object files** that get **copied into your program at link time**.

Build chain:

```
.c → .o → .a → executable
```

Meaning:

| File    | Meaning                                |
| ------- | -------------------------------------- |
| `.c`    | Source code (human readable)           |
| `.o`    | Object file (machine code, no linking) |
| `.a`    | Archive of `.o` files                  |
| `a.out` | Final linked executable                |

---

# 🗄️ **Why is it Called an “Archive”?**

Because `.a` libraries are literally **file archives** created by the `ar` (**archiver**) program.

### **Analogy**

* `.o` files = individual LEGO bricks
* `.a` file = plastic box holding all bricks
* `ar` = tool that packs the box
* `ranlib` = prints a table of contents on the box

So archiving here means **bundling**, **not deleting**.

---

# 🛠️ **Tools Involved**

| Tool         | Purpose                          |
| ------------ | -------------------------------- |
| `cc` / `gcc` | compiles `.c` → `.o`             |
| `ar`         | bundles `.o` → `.a`              |
| `ranlib`     | indexes the `.a` for fast lookup |
| `ld`         | linker used internally by `gcc`  |

---

# 📍 **Library Naming Convention**

Static library names follow the format:

```
lib<name>.a
```

Example in this exercise:

```
libft.a → -lft
```

Why: GCC expands:

```
-lft → libft.a
```

So if you had:

```
libkoko.a
```

You would use:

```
-lko
```

**Common confusion:**

> `-l` removes `lib` prefix and `.a` suffix, leaving only the middle.

---

# 🧠 **Headers Must Be Included per `.c` File**

Each `.c` file is compiled independently:

```
cc -c ft_putstr.c
```

The compiler **does not see other `.c` files or `main.c`**.
So each file must include its own headers.
Example: using `write()` → must include `<unistd.h>` inside that `.c`.

---

# ⚙️ **Compilation Steps (Detailed)**

### **Step 1 → Compile**

```
cc -c ft_putchar.c
...
```

This produces:

```
ft_putchar.o
ft_swap.o
ft_putstr.o
ft_strlen.o
ft_strcmp.o
```

### **Step 2 → Archive**

```
ar rc libft.a ft_putchar.o ... ft_strcmp.o
```

### **Step 3 → Index**

```
ranlib libft.a
```

---

# 🧪 **Linking With the Library**

To compile a program:

```
gcc -o my_lib main.c -L. -lft
```

Explained:

* `main.c` processed first (symbols needed)
* `-L.` → search current directory for libraries
* `-lft` → expands to `libft.a`

On macOS, **order matters**:

```
gcc main.c -L. -lft          ❌ may fail on macOS
gcc -o my_lib main.c -L. -lft ✔ correct order
```

---

# 🍎 **macOS Specific Notes (Mach-O)**

macOS uses **Mach-O** binary format.
If an archive contains invalid entries (like `/`), the linker errors:

```
ld: archive member '/' not a mach-o file in './libft.a'
```

Common causes:

* Wrong shebang (`#!bin/bash` instead of `#!/bin/bash`)
* CRLF line endings in `.sh` file
* Using GNU `ar` instead of `/usr/bin/ar`
* Adding `.c` files to archive instead of `.o` files
* Binary garbage inserted by comments in `.sh`

Correcting these fixes the issue.

---

# 🧰 **libft_creator.sh**

Working 42-style script:

```sh
#!/bin/sh

cc -Wall -Wextra -Werror -c ft_putchar.c ft_swap.c ft_putstr.c ft_strlen.c ft_strcmp.c
ar rc libft.a ft_putchar.o ft_swap.o ft_putstr.o ft_strlen.o ft_strcmp.o
ranlib libft.a
```

---

# 💾 **Function Implementations**

**ft_putchar.c**

```c
#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}
```

**ft_swap.c**

```c
void ft_swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
```

**ft_putstr.c**

```c
#include <unistd.h>

void ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}
```

**ft_strlen.c**

```c
int ft_strlen(char *str)
{
	int len = 0;
	while (str[len])
		len++;
	return (len);
}
```

**ft_strcmp.c**

```c
int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
```

---

# 🧪 **Test Program (main.c)**

```c
#include <unistd.h>

void ft_putchar(char c);
void ft_putstr(char *str);
void ft_swap(int *a, int *b);
int  ft_strlen(char *str);
int  ft_strcmp(char *s1, char *s2);

int main(void)
{
	int a = 10;
	int b = 20;
	char str[] = "Hello 42!";
	int len;

	ft_putstr("Before swap:\n");
	ft_putstr("a = ");
	ft_putchar(a / 10 + '0');
	ft_putchar(a % 10 + '0');
	ft_putchar('\n');

	ft_putstr("b = ");
	ft_putchar(b / 10 + '0');
	ft_putchar(b % 10 + '0');
	ft_putchar('\n');

	ft_swap(&a, &b);
	ft_putstr("\nAfter swap:\n");
	ft_putstr("a = ");
	ft_putchar(a / 10 + '0');
	ft_putchar(a % 10 + '0');
	ft_putchar('\n');

	ft_putstr("String: ");
	ft_putstr(str);
	ft_putchar('\n');

	len = ft_strlen(str);
	ft_putstr("Length: ");
	ft_putchar(len / 10 + '0');
	ft_putchar(len % 10 + '0');
	ft_putchar('\n');
}
```

---

# 🧾 **Build + Run**

```sh
rm -f *.o libft.a
sh libft_creator.sh
gcc -o my_lib main.c -L. -lft
./my_lib
```

---

# 🧱 **ASCII Build Diagram**

```
SOURCE           OBJECTS         ARCHIVE            EXECUTABLE
--------         --------        ---------          -----------
ft_putchar.c --> ft_putchar.o \
ft_swap.c    --> ft_swap.o     |--> libft.a ---> gcc + main.c ---> a.out
ft_putstr.c  --> ft_putstr.o  /
ft_strlen.c  --> ft_strlen.o
ft_strcmp.c  --> ft_strcmp.o
```

---

# 🧩 **Makefile (Optional)**

```make
NAME = libft.a
SRCS = ft_putchar.c ft_swap.c ft_putstr.c ft_strlen.c ft_strcmp.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
```

---

# ❓ **FAQ / Common Mistakes**

| Question                               | Answer                                                   |
| -------------------------------------- | -------------------------------------------------------- |
| Why include `<unistd.h>` in `.c` file? | Each `.c` compiles alone; main.c doesn’t provide headers |
| Why `-lft` for `libft.a`?              | `-l<name>` maps to `lib<name>.a`                         |
| Why error “not a mach-o file”?         | Archive contains invalid members or wrong `ar`           |
| Do I need `ranlib`?                    | Yes, to create symbol index (especially on macOS)        |
| Why `-L.`?                             | Tells linker to search current directory                 |
| Why order `main.c` before `-lft`?      | clang resolves symbols left-to-right                     |

---

# 🎯 **Final Takeaways**

By finishing this project, you learn:

✔ How `.c` becomes `.o`
✔ How `.o` becomes `.a`
✔ How libraries are linked
✔ How `gcc` resolves libraries
✔ Proper static library naming convention
✔ macOS linking differences (Mach-O)
✔ Script hygiene + shebang usage

This is foundational knowledge you will reuse in:

