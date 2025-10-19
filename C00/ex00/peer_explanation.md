# 💻 Exercise 00: `ft_putchar`

### 📁 Directory

`ex00/`

### 📄 File to turn in

`ft_putchar.c`

### ⚙️ Allowed functions

`write`

---

## 🧠 Objective

Create your first function that displays a single character on the standard output using the low-level system call `write()`.

---

## 🔍 What You’re Learning

| Concept                   | Description                                     |
| ------------------------- | ----------------------------------------------- |
| `char` data type          | How to handle a single character                |
| `void` return type        | Function performs an action but returns nothing |
| System call `write()`     | Direct communication with the terminal          |
| `<unistd.h>`              | Header that declares `write()`                  |
| `&` (address-of operator) | Passes variable’s memory address                |
| File descriptors          | Integer references to I/O streams               |
| Function definition       | How to structure and prototype a C function     |

---

## 📘 Code Breakdown

```c
#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int main(void)
{
	ft_putchar('a');
	return (0);
}
```

### 🧩 Line-by-Line Explanation

| Line                      | Explanation                                            |
| ------------------------- | ------------------------------------------------------ |
| `#include <unistd.h>`     | Imports `write()` — a low-level system call for output |
| `void ft_putchar(char c)` | Function takes a `char` and returns nothing            |
| `write(1, &c, 1);`        | Sends 1 byte from the address of `c` to FD 1 (stdout)  |
| `ft_putchar('a');`        | Calls the function and prints `'a'` on screen          |
| `return (0);`             | Ends the program successfully                          |

---

## ❓ Why This Matters

* Trains you to think **low-level** — directly communicating with the OS.
* You start **building your own libc** (later exercises re-create `printf`, `puts`, etc.).
* This teaches how **C talks to the kernel** without higher-level libraries like `stdio.h`.

---

## 💡 Tips to Remember

🧠 Think of `write()` as a message to the OS:

> “Hey OS! Please write 1 byte from this address to the terminal.”

| Argument | Meaning                        |
| -------- | ------------------------------ |
| `1`      | File descriptor for **stdout** |
| `&c`     | Address of the character       |
| `1`      | Number of bytes to write       |

Mnemonic: **1 → &c → 1** → “Write 1 byte from &c to stdout.”

---

## 💥 Common Mistakes

| Mistake              | Why It’s Wrong                                 |
| -------------------- | ---------------------------------------------- |
| `'c'` instead of `c` | `'c'` is a literal character, not the variable |
| `write(1, c, 1)`     | Missing `&` → you must send the memory address |
| Missing `<unistd.h>` | Compiler doesn’t recognize `write()`           |

---

## 🧠 Memory Trick

Imagine you’re building a tiny printer robot:

* “Where to write?” → File descriptor `1`
* “What to write?” → The address `&c`
* “How much?” → Just `1` byte

---

## 🧩 File Descriptors — Core Concept

Everything in Unix/Linux is treated as a file — even your terminal.

| FD | Description                |
| -- | -------------------------- |
| 0  | Standard Input (`stdin`)   |
| 1  | Standard Output (`stdout`) |
| 2  | Standard Error (`stderr`)  |
| 3+ | Any additional opened file |

Each program gets its **own file descriptor table**, managed by the **kernel**.
That means every running process has its private I/O channels.

---

## 🔧 Try It Yourself

### 1️⃣ Write to `stderr`

```c
write(2, &c, 1);
```

### 2️⃣ Print multiple characters

Call `ft_putchar()` in a loop:

```c
for (char ch = 'A'; ch <= 'Z'; ch++)
	ft_putchar(ch);
```

### 3️⃣ Test interleaving

Compile and run two programs:

```bash
./A & ./B
```

Each prints different letters — you’ll see mixed output because the OS interleaves writes.

---

## 🧾 Summary

| Concept          | Key Point                                  |
| ---------------- | ------------------------------------------ |
| `write()`        | Direct channel from your code to the OS    |
| File descriptors | 0 = input, 1 = output, 2 = error           |
| Each process     | Has its own FD table                       |
| `ft_putchar`     | First step toward system-level programming |

✅ **End Result:** You now know how to print directly to the terminal without `printf()`.
Welcome to low-level C — you’ve just touched the kernel.

---

# 🧩 Peer Evaluation Q&A

### 🧠 **Q1:** What does `write()` do?

**A:** It sends bytes directly to a file descriptor.
In `write(1, &c, 1)`, it writes **1 byte** (the address of `c`) to **stdout (FD 1)**.

---

### 🧠 **Q2:** Why is `&c` used instead of `c`?

**A:** Because `write()` needs a memory address, not the value.
`c` gives the value of the character, while `&c` gives its address in memory.

---

### 🧠 **Q3:** What is a file descriptor?

**A:** It’s a number that represents an open file or stream.

* 0 → stdin
* 1 → stdout
* 2 → stderr

Every process gets these three by default.

---

### 🧠 **Q4:** Why can’t we use `printf()` here?

**A:** `printf()` is a higher-level function from `<stdio.h>`.
`write()` is lower-level, closer to the system — it’s what `printf()` uses internally.

---

### 🧠 **Q5:** What does `<unistd.h>` provide?

**A:** It declares POSIX system calls like `read()`, `write()`, `close()`, etc.
Without it, `write()` would cause a compiler error.

---

### 🧠 **Q6:** What happens if two programs both use `write()` at the same time?

**A:** Each process has its own FD table, so they don’t conflict — unless both write to the same file.
If that happens, output order can mix unless synchronization (like file locks) is used.

---

### 🧠 **Q7:** What’s the return type `void` mean here?

**A:** The function doesn’t return any value — it only performs an action (printing).

---

### 🧠 **Q8:** What would happen if you wrote `write(1, "a", 1);` instead?

**A:** It would still print `'a'`, but it directly passes a string literal (not a variable).
`&c` is more flexible because it works with variable input.

---

### 🧠 **Q9:** What’s the difference between stdout and stderr?

**A:**

* `stdout` → normal output (FD 1)
* `stderr` → error output (FD 2)
  You can redirect them separately in the shell.

---

### 🧠 **Q10:** How can you test if your code works properly?

**A:**

* Compile: `cc ft_putchar.c -o ft_putchar`
* Run: `./ft_putchar`
* You should see the character printed on the screen.

---

### 🧠 **Q11:** Bonus question — What does “Everything is a file” mean?

**A:**
In Unix philosophy, everything (even devices, terminals, sockets) is accessed through file descriptors — just like reading/writing a file.

---
