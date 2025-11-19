## 1. Big Picture – What does this program do?

For each call to `ft_print_memory` it prints **one line** that looks like a memory dump:

```text
00007fffd6e86a4b0:  426f 6e6a 6f75 7220 6c65 7320 616d 696e Bonjour les amin
^^^^^^^^^^^^^^^^^   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ ^^^^^^^^^^^^^^^^
 address of data     16 bytes of hex (grouped by 2)          ASCII / dots
```

So each line has **three columns**:

1. **Address column** – the address of the first byte, printed in hexadecimal.
2. **Hex column** – 16 bytes from memory, in hex, with a space every 2 bytes and padding on the right if fewer than 16 bytes.
3. **ASCII column** – the same bytes printed as characters; non-printable bytes become `.`.

Your version prints **only the first 16 bytes** of each string you pass to `ft_print_memory` (that’s fine for learning).

---

## 2. Helper 1 – `ft_putchar`

```c
void	ft_putchar(char c)
{
	write(1, &c, 1);
}
```

* Tiny wrapper around the low-level `write` system call.
* Always writes **1 byte** to file descriptor `1` (standard output).
* You reuse this everywhere so you don’t have to type `write(1, &c, 1)` all the time.

> Mental model: “I give `ft_putchar` one character, it pushes it out to the terminal.”

---

## 3. Helper 2 – `print_byte_hex`

```c
void	print_byte_hex(unsigned char byte)
{
	unsigned char	high_nibble;
	unsigned char	low_nibble;

	high_nibble = byte / 16;
	low_nibble = byte % 16;

	if (high_nibble < 10)
		ft_putchar('0' + high_nibble);
	else
		ft_putchar('a' + (high_nibble - 10));

	if (low_nibble < 10)
		ft_putchar('0' + low_nibble);
	else
		ft_putchar('a' + (low_nibble - 10));
}
```

### What is the goal?

Take **one byte** (0–255) and print it as **two hexadecimal digits**, e.g.:

* `byte = 65` (0x41) → prints `4` then `1`
* `byte = 255` (0xFF) → prints `f` then `f`

### How?

* A byte has 8 bits → you split it into two **nibbles** (4 bits each):

  * `high_nibble = byte / 16`  → top 4 bits (0–15).
  * `low_nibble  = byte % 16`  → bottom 4 bits (0–15).

Each nibble (0–15) must be converted to a character:

* 0–9 → `'0' + nibble` → `'0'`..`'9'`
* 10–15 → `'a' + (nibble - 10)` → `'a'`..`'f'`

So you:

1. Convert and print `high_nibble`.
2. Convert and print `low_nibble`.

> This is the core building block: “Given any byte, I can show what it looks like in hex.”

---

## 4. Helper 3 – `print_address_hex`

```c
void	print_address_hex(void *addr)
{
	unsigned char	*addr_ptr;
	int				i;

	addr_ptr = (unsigned char *)&addr;
	i = (int)(sizeof(addr) - 1);

	while (i >= 0)
	{
		print_byte_hex(addr_ptr[i]);
		i--;
	}
	ft_putchar(':');
}
```

### Goal

Print something like:

```text
00007fffd6e86a4b0:
```

– the address of the first byte, as 16 hex digits, followed by `:`.

### The trick

* Parameter `addr` is a **pointer** (`void *`).
* The pointer itself is stored as **8 bytes** on a 64-bit system.
* `&addr` is “address of the pointer variable”.
* You cast that to `unsigned char *`:

```c
addr_ptr = (unsigned char *)&addr;
```

Now `addr_ptr[i]` lets you see the raw bytes that store the pointer’s value.

Because the machine is **little-endian**, the least significant byte is at the lowest index.
So to print the address in the “normal” big-endian order, you start from the end:

```c
i = sizeof(addr) - 1;   // usually 7
while (i >= 0)
{
    print_byte_hex(addr_ptr[i]);
    i--;
}
```

Finally you print a colon:

```c
ft_putchar(':');
```

> Mental picture: “The pointer `addr` is stored as 8 bytes in memory. I look at those 8 bytes from right to left and print each one in hex.”

---

## 5. Helper 4 – `print_16_bytes_hex`

```c
void	print_16_bytes_hex(void *ptr, unsigned int size)
{
	unsigned char	*byte_ptr;
	int				bytes_to_print;
	int				i;

	byte_ptr = (unsigned char *)ptr;
	if (size < 16)
		bytes_to_print = (int)size;
	else
		bytes_to_print = 16;

	i = 0;
	while (i < 16)
	{
		if (i % 2 == 0)
			ft_putchar(' ');

		if (i < bytes_to_print)
		{
			print_byte_hex(byte_ptr[i]);
		}
		else
		{
			ft_putchar(' ');
			ft_putchar(' ');
		}
		i++;
	}
}
```

### Goal

Print the **hex column** for up to 16 bytes starting at `ptr`:

* Maximum 16 bytes.
* A space before every **pair** of bytes.
* If there are fewer than 16 bytes left (last line), pad the rest with spaces.

Example layout (conceptually):

```text
 426f 6e6a 6f75 7220 6c65 7320 616d 696e
 ^   ^
 |   |
space every 2 bytes
```

### Step-by-step

1. Convert `ptr` to a byte pointer:

   ```c
   byte_ptr = (unsigned char *)ptr;
   ```

2. Decide how many real bytes you actually have:

   ```c
   if (size < 16)
       bytes_to_print = size;
   else
       bytes_to_print = 16;
   ```

3. Loop `i` from 0 to 15:

   ```c
   while (i < 16)
   {
       if (i % 2 == 0)
           ft_putchar(' ');
       ...
       i++;
   }
   ```

   * At each even index (`i % 2 == 0`), you print a **space** → this creates ` 426f 6e6a ...`.

4. Inside the loop:

   * If `i < bytes_to_print`:

     * You still have real data → print the hex for `byte_ptr[i]`.
   * Else:

     * We’ve passed the end of the real bytes on this line → print two spaces to “fake” that missing byte so the ASCII column still lines up.

> Mental model: “I always go from 0 to 15. Real data? print hex. No data? print spaces. And I sprinkle spaces every two bytes to match the subject format.”

---

## 6. Helper 5 – `print_printable_chars`

```c
void	print_printable_chars(void *ptr, unsigned int size)
{
	unsigned char	*byte_ptr;
	int				chars_to_print;
	int				i;

	byte_ptr = (unsigned char *)ptr;
	if (size < 16)
		chars_to_print = (int)size;
	else
		chars_to_print = 16;

	i = 0;
	while (i < chars_to_print)
	{
		if (byte_ptr[i] >= 32 && byte_ptr[i] < 127)
			ft_putchar(byte_ptr[i]);
		else
			ft_putchar('.');
		i++;
	}
}
```

### Goal

Print the **ASCII column**:

* Printable ASCII (codes 32–126) → print the character.
* Everything else (control characters like `\n`, `\t`, `\a`, etc.) → print `.`.
* Only for the bytes that actually exist on this line (up to 16).

### How

1. Again, cast the generic pointer to bytes:

   ```c
   byte_ptr = (unsigned char *)ptr;
   ```

2. Decide how many characters exist: min(size, 16).

3. Loop over those:

   ```c
   if (byte_ptr[i] >= 32 && byte_ptr[i] < 127)
       ft_putchar(byte_ptr[i]);
   else
       ft_putchar('.');
   ```

> Result: the right column shows readable text, but non-printable bytes appear as dots, just like the subject.

---

## 7. Core function – `ft_print_memory`

```c
void	*ft_print_memory(void *addr, unsigned int size)
{
	/* Match original: if size == 1 (empty string ""), print nothing */
	if (size == 1)
		return (addr);

	print_address_hex(addr);
	print_16_bytes_hex(addr, size);
	ft_putchar(' ');
	print_printable_chars(addr, size);
	ft_putchar('\n');	
	return (addr);
}
```

### What does it do?

For **each call**, it prints **one full line** (address + 16-byte hex + ASCII):

1. **Special case**:

   ```c
   if (size == 1)
       return (addr);
   ```

   * In your tests, `empty[] = ""` has `sizeof(empty) == 1` (only the `'\0'`).
   * You chose to treat “size 1” as “nothing to display”, so you just return.

2. Otherwise, you:

   ```c
   print_address_hex(addr);        // left column
   print_16_bytes_hex(addr, size); // middle column
   ft_putchar(' ');
   print_printable_chars(addr, size); // right column
   ft_putchar('\n');
   ```

3. And finally return the original address (as the subject requires).

> Important: **this version does not loop over multiple lines**.
> It always prints only the first 16 bytes starting at `addr`.
> In `main`, you call it multiple times with different strings, which is why you still see several lines.

---

## 8. Test code – `main`

```c
int	main(void)
{
	char	empty[] = "";

	char	str[] = "Bonjour les amin----";
	char	str1[] = "ches\t\n\tc  est fo----";
	char	str2[] = "u\ttout\tce qu on ----";
	char	str3[] = "peut faire avec\t----";
	char	str4[] = "\n\tprint_memory\n\n----";
	char	str5[] = "\n\tlol.lol\n \0";

	ft_print_memory((void *)empty, sizeof(empty));
	ft_print_memory((void *)str, sizeof(str));
	ft_print_memory((void *)str1, sizeof(str1));
	ft_print_memory((void *)str2, sizeof(str2));
	ft_print_memory((void *)str3, sizeof(str3));
	ft_print_memory((void *)str4, sizeof(str4));
	ft_print_memory((void *)str5, sizeof(str5));

	return (0);
}
```

### What are these strings?

* `empty[] = ""`

  * Size is 1 (`'\0'` only).
  * `ft_print_memory` returns immediately → no line printed.

* The other strings are crafted to:

  * Have **at least 16 characters**, often exactly 16 real characters + `"----"` to fill.
  * Include some **control characters**:

    * `\t` (tab), `\n` (newline), `\a` (bell), etc.
  * This way you can see the **difference**:

    * In the **hex column**: special bytes like `0a`, `09`, `07`.
    * In the **ASCII column**: those appear as `.` instead of literal control characters.

For each string:

```c
ft_print_memory((void *)strX, sizeof(strX));
```

* `addr` → address of the first character.
* `size` → includes the `\0` terminator (because of `sizeof`), but your code only uses up to 16 bytes anyway.

> So: one call = one line. Several calls = several lines stacked, like in the screenshot.

---

## 9. How to explain this to a peer / in a video

You can present it in **layers**:

1. **Layer 1 – Basic tools**

   * `ft_putchar`
   * `print_byte_hex` (nibbles, base 16).

2. **Layer 2 – Address column**

   * Explain that a pointer itself lives in memory.
   * Show a diagram: pointer variable → 8 bytes → print from last to first.

3. **Layer 3 – Hex column**

   * Show an array of bytes indexed 0..15.
   * Show how `bytes_to_print` = min(size, 16).
   * Show padding spaces for unused positions.

4. **Layer 4 – ASCII column**

   * Show ASCII table: 32..126 printable.
   * Non-printable → dot.

5. **Layer 5 – Putting it together**

   * One call to `ft_print_memory` = one row of the dump.
   * In the official subject, you’d add a loop to move the address by +16 each line.
     (You don’t need to change your code now; just mention the idea.)

---

# ❓ **Q&A: Why does the code check `size == 1` instead of `size == 0`?**

### **Q: The subject says → “If `size == 0`, nothing should be displayed.”

So why does the program check:**

```c
if (size == 1)
    return (addr);
```

### **A: Because an empty string in C always has size 1, not 0.**

When you write:

```c
char empty[] = "";
```

In memory, this array still contains **one byte** — the null terminator:

```
[ '\0' ]
```

Therefore:

| Expression      | Result                        |
| --------------- | ----------------------------- |
| `strlen(empty)` | **0** (no visible characters) |
| `sizeof(empty)` | **1** (because of the `'\0'`) |

`ft_print_memory` receives the **array size**, not the string length.

So when you call:

```c
ft_print_memory(empty, sizeof(empty));
```

You are actually calling:

```c
ft_print_memory(empty, 1);
```

### ✔️ But the subject wants **empty string = print nothing**

Even though C gives it **size = 1**.

So the correct way to detect the “empty string” case is:

```c
if (size == 1)
    return (addr);
```

This prevents printing one line that contains the single byte `00` from the null character.

---

# 🧠 **Final Short Explanation to Include in Notes**

> In C, an empty string `""` has size **1** because of the null terminator (`'\0'`).
> The subject requires that “if size == 0, nothing should be displayed,” but in practice, this case never naturally happens when passing string arrays.
> To match the expected behavior (do not print anything for `""`), we check for `size == 1`, which represents an empty string in memory.

---



