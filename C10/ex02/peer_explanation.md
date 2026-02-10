# peer_explanation.md — C10 ex02 — `ft_tail` (option `-c` only)

## 📌 Exercise Summary

We must implement a program called **`ft_tail`** that behaves like the system command **`tail`**, under strict constraints:

* Only handle option: **`-c`** (bytes)
* No need to support `+` or `-` signs for the number after `-c`
* Tests will be done with `-c`
* Allowed functions: `open`, `read`, `write`, `close`, `malloc`, `free`, `strerror`, `basename`
* Submission includes a `Makefile` with rules: `all`, `clean`, `fclean`

---

## ✅ What “tail -c N” does (real behavior)

`tail -c N file` prints the **last N bytes** of the file.

**Example (real case):**

* You have a log file `server.log`
* You want the most recent bytes quickly:

  * `tail -c 200 server.log` prints the last 200 bytes (usually the newest messages).

---

## 🧠 `-c` vs `-n`

* `-c N`: last **N bytes**
* `-n N`: last **N lines**

In this exercise, we only implement **`-c`**.

---

## Default behavior in this project

If user does **not** provide `-c`, we set:

* `bytes_to_read = 10` (default bytes for our implementation)
* This matches our exercise scope (all tests are with `-c`, but we keep a reasonable default)

---

## 🧱 High-Level Architecture (Step-by-step build)

We built this project bottom-up, starting from `main`, then adding small, testable pieces.

### Two big phases

1. **Parsing phase** (figure out the settings and targets)
2. **Processing phase** (open files, read, store last bytes, print)

We separated these into two files:

* `parse.c` → parsing args
* `process.c` → opening/reading/printing

---

## 🧩 Central Context Struct (No global variables)

We store the program state in a single struct (in heap + stack mix), passed everywhere:

* prevents global variables
* makes parsing/processing consistent
* keeps the program modular

### Why the “marked positions” array exists

We allocate an array sized `argc`:

* `marked_option_positions[i] == 1` means:

  * `argv[i]` is part of an option (like `-c` or the number after it)
* later we can **skip those** and treat the rest as file targets

### Q: “Is `marked_option_positions` heap memory that contains all arguments?”

**Answer:** Not exactly.

* `argv` holds the actual argument strings.
* `marked_option_positions` is just a **mask array** on the heap:
  it stores **0/1 markers**, not the strings.

**Why we need it:**
Because `-c` can appear anywhere (`./ft_tail file1 -c 5 file2`).
So we mark `-c` and its number so we can ignore them when collecting file targets.

---

## 🧠 malloc vs calloc (initializing to zero)

### Q: “Is it better to use `calloc` so it’s already zeroed?”

**Answer:** Yes, `calloc` is convenient.

### Q: “But 42 is strict; should we use `malloc` only?”

**Answer:** Using `malloc` is fine and common in 42.
We simply do:

* `malloc(argc)`
* then a loop to set all values to zero

This is acceptable and keeps control explicit.

---

## 🔍 Parsing `-c` option (and detecting duplicates)

We parse `-c` by scanning all arguments:

* if we find `-c`, we validate:

  * there must be an argument after it
  * it must be numeric (digits only)
* we convert it to an integer (`bytes_to_read`)
* we mark both positions in the mask array

### Q: “How does `c_option_status == 1` detect duplicate `-c`?”

**Answer:**

* First time we see a valid `-c`, we set `c_option_status = 1`.
* If we see `-c` again later, we detect:

  * `if (context->c_option_status == 1)` → duplicate → error.

### 42 line limit improvement

### Q: “My function becomes >25 lines; should errors be in another function?”

**Answer:** Yes.

We created a small helper like:

* `set_parse_error(context, "message")`

so the main parsing function stays short.

---

## 🎯 Parsing file targets (count + headers decision)

After marking `-c` and its number, we count targets:

* any `argv[i]` where `marked_option_positions[i] == 0` is a file target

This gives:

* `parsed_targets_count`
* `should_print_headers = 1` if `count > 1`

### Q: “If no `-c` is found, how do we use default 10?”

**Answer:** After scanning:

* if `c_option_status == 0`, then:

  * `bytes_to_read = 10`
  * treat as valid (so processing can continue)

---

## 🧩 static vs non-static

### Q: “Why is this function not static? Is it because we use it outside the file?”

**Answer:** Exactly.

* `static` function: visible only in that `.c` file
* non-`static` function: can be used from other `.c` files (through header prototypes)

So we keep helpers `static`, and exported API functions non-static.

---

# 🏁 Processing Phase (the real `tail -c` logic)

We process each target file:

1. Print header (only if multiple files)
2. Open file
3. Read bytes in chunks
4. Keep only last N bytes in a circular buffer
5. Print final buffer in correct order

---

## 🧾 Headers (multi-file output)

When multiple targets exist, we print:

```
==> file1 <==
(output)

==> file2 <==
(output)
```

We also print a blank line between file sections (typical tail style).

---

## 🧠 Why we need a circular buffer (Ring Buffer)

We cannot read the entire file into memory (not allowed / inefficient).

Instead, we keep only the last `N` bytes:

* Buffer size = `bytes_to_read` (N)
* Every new byte overwrites the oldest byte
* At the end, buffer contains exactly the last N bytes

### Q: “So here we always overwrite the buffer?”

**Answer:** Yes — intentionally.

That’s the entire ring buffer idea:

* newest bytes replace oldest bytes

---

## 🔍 “chunk”, `bytes_read`, and OS file position

### Q: “Do we copy BUFFER_SIZE or only N bytes?”

**Answer:** We copy only `bytes_read`.

* `read(fd, read_chunk, BUFFER_SIZE)` returns `bytes_read`
* we process exactly `bytes_read` bytes from `read_chunk`

### Q: “If OS doesn’t fill the entire buffer, will it automatically continue?”

**Answer:** No.

* We must call `read()` again in a loop.

### Q: “How does `read()` know where to continue?”

**Answer:** The OS keeps an internal file position per file descriptor.
Each `read()` advances it automatically.

### Q: “Is end-of-file decided by OS?”

**Answer:** Yes.

* OS knows file size (for regular files)
* when current position reaches the file size, `read()` returns `0`.

---

## 🔒 Security question

### Q: “Can someone trick OS by lying about file size? Is it a vulnerability?”

**Answer:** Not the way you think for regular files.

* file size and offsets are kernel-managed
* vulnerabilities usually come from the program mis-handling buffers (overflow), not from “lying to OS about file size.”

---

# 🧠 The ring-buffer variables (why we need them)

In the ring reading logic we used:

* `read_chunk[BUFFER_SIZE]` → temporary chunk read from file
* `bytes_read` → how many bytes read this iteration
* `total_read` → total bytes processed so far
* `current_position` → index inside circular buffer where next byte will be written

### Q: “Is `total_read` the size of the file?”

**Answer:** It becomes the total bytes we actually processed.
For a regular file, it ends equal to file size (in bytes).

### Q: “Is `read_chunk` the whole file?”

**Answer:** No.
`read_chunk` is just a temporary bucket for each `read()` call.

---

# 🧠 The modulo line (wrapping the index)

### Q: “Explain this line:”

```c
current_position = (current_position + 1) % bytes_to_read;
```

**Meaning:**
Increase index by 1, and when it reaches N, wrap to 0.

Example (`N=5`):

```
0 → 1 → 2 → 3 → 4 → 0 → 1 → ...
```

### Q: “So we zero current_position when we reach full bytes_to_read?”

**Answer:** Yes.
It resets to 0 only when it reaches the end.

### Q: “Is wrap controlled by looping `i < bytes_to_read`?”

**Answer:** No.

* `i < bytes_read` controls chunk processing
* `% bytes_to_read` controls wrap around

---

# 🖨️ Printing: `write_all` vs `print_tail_buffer`

### Q: “Isn’t write_all enough? Why need print_tail_buffer?”

**Answer:**

* `write_all` only guarantees writing a contiguous block completely
* `print_tail_buffer` decides which part of the ring buffer to print and in which order (it may be split)

So:

* `print_tail_buffer` = logic
* `write_all` = safe writer

---

# 🧠 Why print twice? (first_part explained)

Because the circular buffer may be physically split:

* Part 1: from `start_index` to end of array
* Part 2: from index `0` onward

We compute:

* `start_index`: where the oldest byte starts
* `first_part`: how many bytes exist from `start_index` to the end without wrap

---

## 📌 Visual Example (N=5, file length=12)

Buffer size:

```
N = 5
```

File content (12 bytes):

```
A B C D E F G H I J K L
```

### After first 5 bytes (A–E)

```
index:   0   1   2   3   4
buffer: [A] [B] [C] [D] [E]
current_position = 0
```

### After next 5 bytes (F–J) overwrite A–E

```
index:   0   1   2   3   4
buffer: [F] [G] [H] [I] [J]
current_position = 0
```

### After last 2 bytes (K, L)

```
K -> index 0
L -> index 1
```

Final:

```
index:   0   1   2   3   4
buffer: [K] [L] [H] [I] [J]
current_position = 2   (because 12 % 5 = 2)
```

We want last 5 bytes of the file:

```
H I J K L
```

They are stored in memory as:

```
[K][L][H][I][J]
```

So:

* Start printing at `start_index = current_position = 2`
* First part = from index 2 to 4 → `H I J` (3 bytes)
* Then wrap and print index 0 to 1 → `K L` (2 bytes)

### That’s exactly what `first_part` means:

```
first_part = bytes_to_read - start_index
first_part = 5 - 2 = 3
```

Great idea 👍 — here is a **ready-to-paste Markdown explanation** written exactly in the style of a 42 “peer_explanation.md”, with diagrams and visuals like you asked.

You can copy this block directly into your GitHub notes.

---

# 🧠 Understanding `current_position`, `start_index`, and `first_part`

This section explains visually how the circular buffer printing logic works in our `ft_tail` implementation.

We focus on the case where:

* The file is **bigger than** `bytes_to_read`
* The buffer wraps around
* We need to print in **two parts**

---

## 🔹 Core Idea

Our goal:

> Print **only the last N bytes** of a file, using a fixed-size circular buffer.

Because the buffer is reused (overwritten), the final data might be **split in two places** inside the array.

---

# Example Setup

Let’s take:

```
bytes_to_read (N) = 5
```

And imagine a file containing **12 bytes**:

```
A B C D E F G H I J K L
```

---

# Step 1 – Reading into the Circular Buffer

We read the file byte by byte.
The buffer only holds 5 bytes, so it keeps overwriting old data.

---

### After first 5 bytes (A–E)

```
Indexes:  0  1  2  3  4
Buffer:  [A][B][C][D][E]
current_position = 0
```

---

### After next 5 bytes (F–J)

These overwrite A–E:

```
Indexes:  0  1  2  3  4
Buffer:  [F][G][H][I][J]
current_position = 0
```

---

### After final 2 bytes (K and L)

```
Write K → index 0
Write L → index 1
```

Now the buffer contains:

```
Indexes:  0  1  2  3  4
Buffer:  [K][L][H][I][J]
```

And:

```
total_read = 12
current_position = 2
```

Because:

```
12 % 5 = 2
```

---

# Step 2 – What Do We Need to Print?

We want the **last 5 bytes** of the file:

```
H I J K L
```

But in memory they are stored as:

```
[K][L][H][I][J]
```

So the correct order is:

```
from index 2 → 4  : H I J
then index 0 → 1 : K L
```

---

# 🔍 Mapping to the Code

Inside `print_tail_buffer`:

```c
bytes_to_print = bytes_to_read;   // = 5
start_index = current_position;   // = 2
```

---

## What is `start_index`?

> **Where the oldest valid byte is located**

Here:

```
start_index = 2
```

That means:

👉 Printing must begin at index 2.

---

## What is `first_part`?

```c
first_part = bytes_to_read - start_index;
```

```
first_part = 5 - 2 = 3
```

---

### Meaning of `first_part`

> “How many bytes can I print from `start_index` until the end of the array without wrapping?”

From index 2 to index 4:

```
indexes 2, 3, 4  → 3 bytes
```

Which are:

```
H I J
```

---

# Step 3 – Printing Happens in Two Parts

### First Print

```c
write_all(1, &buffer[start_index], first_part);
```

Becomes:

```
write_all(1, &buffer[2], 3);
```

Output:

```
H I J
```

---

### Second Print (wrap-around)

Check:

```c
if (bytes_to_print > first_part)
```

```
5 > 3 → TRUE
```

So we print the remaining bytes from the beginning:

```c
write_all(1, buffer, bytes_to_print - first_part);
```

```
write_all(1, buffer, 2);
```

Output:

```
K L
```

---

# Final Combined Output

```
H I J   +   K L
=  H I J K L
```

Which is exactly the **last 5 bytes of the file**.

---

# 📌 Why Two Variables Are Needed

| Variable      | Role                                                 |
| ------------- | ---------------------------------------------------- |
| `start_index` | Where printing begins in the circular buffer         |
| `first_part`  | How many bytes can be printed before hitting the end |

---

## One-Sentence Summary

> `start_index` tells **where to start**,
> `first_part` tells **how far we can go before wrapping**.

---

# Visual Diagram

```
Buffer (size 5):

  index:   0   1   2   3   4
         +---+---+---+---+---+
values:  | K | L | H | I | J |
         +---+---+---+---+---+
                 ^
             start_index

first_part = 3  (from index 2 to 4)

Print order:

[2..4]  -> H I J
[0..1]  -> K L
```

---

# Conclusion

This mechanism ensures that:

* We never store more than N bytes
* We can process arbitrarily large files
* We always print data in the **correct logical order**, even when it wraps around

---

# ✅ Stdin discussion (idea vs constraints)

### Q: “I had a better idea: jump to end of file and read backwards N bytes”

**Answer:** That requires seeking (`lseek`) — but `lseek` is **not allowed** in this exercise.
So we must use the ring buffer approach.

### Q: “For stdin, can we do it live?”

**Answer:** Yes, ring buffer works perfectly for stdin:

* keep reading from fd=0
* store only last N bytes
* print at the end (when stdin closes)

---

# 🧪 Testing Notes (important)

* System `tail file` defaults to **lines**
* Our project focuses on `-c` bytes
  So in tests, compare against:
* `tail -c N file`

Also:

* `-c` position in argv differs between implementations
* but our project supports it anywhere (we intentionally built it that way)

---

# ✅ Peer Evaluation Q&A

### Q: Why store program name with `basename`?

To print cleaner errors:

```
ft_tail: file1: No such file or directory
```

### Q: Why save `errno` before calling `strerror`?

Because other calls might overwrite `errno`.
Saving it avoids wrong messages.

### Q: Why treat duplicate `-c` as error?

Because it’s ambiguous and simplifies requirements:

* one configuration only

### Q: Why not put `exit_status = 1` inside `display_error`?

Because `display_error` should only print.
State changes should remain in the calling logic (clean design, fewer side effects).

### Q: Why not use `switch` to simplify printing logic?

`switch` is for discrete values.
Here we need range comparisons (`<`, `>=`) and computed lengths, so `if/else` is correct.

---

## ✅ Final Result

This implementation:

* Parses `-c` anywhere in argv
* Marks option positions to detect true file targets
* Handles multi-file headers
* Implements `tail -c N` using a ring buffer
* Uses safe `write_all` to avoid partial write issues
* Stays compatible with 42 function restrictions and line limits

---

