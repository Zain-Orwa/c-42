
# 📘 **HEX DUMP MODULE — FULL DOCUMENTATION (WORD-FRIENDLY)**

*(Copy & paste this into Word/Google Docs → Export as PDF)*

---

# TITLE:

## **Understanding Bytes, Memory, Hexadecimal, and Custom Hex Dump Functions in C**

### Author: *Zain’s Programming Notes*

### Module: Low-Level Memory & Hexadecimal Processing

### Language: C

### Level: 42 Piscine / Systems Programming

---

# ------------------------------------------------------------

# 📍 **Chapter 1 — Understanding Bytes, Bits, and Nibbles**

# ------------------------------------------------------------

## 1.1 Introduction

Modern computers store everything as **binary**, but humans inspect memory more easily using **hexadecimal**. Writing your own hex dump tool trains your understanding of:

* raw memory access
* pointer casting
* endianness
* ASCII
* nibble splitting

These skills are foundational for:

* debugging
* reverse engineering
* systems programming
* understanding compilers
* network packets
* binary protocols
* `ft_print_memory` (42 School)

---

## 1.2 What is a Byte?

```
1 byte = 8 bits
```

### Diagram:

```
[ b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 ]
```

Each bit is 0 or 1.
Together, they represent values from 0 to 255.

---

## 1.3 What is a Nibble?

A **nibble** is **4 bits**.

```
BYTE = [ high nibble | low nibble ]
```

### Diagram:

```
HIGH NIBBLE (4 bits)          LOW NIBBLE (4 bits)
[ b7 b6 b5 b4 ]               [ b3 b2 b1 b0 ]
```

Each nibble encodes **0–15**:

```
0–9  →  0–9
10–15 → a–f
```

That is exactly why:

```
1 byte = 2 hex digits
```

---

## 1.4 Why Hexadecimal?

Binary is too long, decimal is awkward for byte boundaries.
Hex lines up exactly with bits:

```
1 hex digit = 4 bits
2 hex digits = 1 byte
8 hex digits = 4 bytes (32-bit int)
16 hex digits = 8 bytes (64-bit pointer)
```

---

# ------------------------------------------------------------

# 📍 **Chapter 2 — ASCII Mapping and Hex Printing**

# ------------------------------------------------------------

## 2.1 Mapping Nibbles to Characters

| Nibble Value | Hex Digit | ASCII Code |
| ------------ | --------- | ---------- |
| 0–9          | 0–9       | 48 + value |
| 10           | a         | 97         |
| 11           | b         | 98         |
| 12           | c         | 99         |
| 13           | d         | 100        |
| 14           | e         | 101        |
| 15           | f         | 102        |

### Formula:

```
If nibble < 10:
    '0' + nibble
Else:
    'a' + (nibble - 10)
```

---

## 2.2 Diagram: Converting a Byte to Hex

Suppose the byte is 0xAF.

```
Byte: 0xAF
Binary: 1010 1111
        |    |
      high  low
     nibble nibble

High nibble: 1010 = 10 = 'a'
Low nibble : 1111 = 15 = 'f'
```

Output:

```
af
```

---

# ------------------------------------------------------------

# 📍 **Chapter 3 — Function 1: print_byte_hex()**

# ------------------------------------------------------------

## 3.1 Purpose

Convert **one byte** (0–255) into **two hexadecimal characters**.

## 3.2 High-Level Behavior

* Take a raw byte
* Split into high/low nibbles
* Convert each nibble to hex using ASCII
* Print the result

---

## 3.3 Byte → Hex Flowchart

```
         +---------------------+
         |   Input: 1 byte     |
         +----------+----------+
                    |
                    v
         +---------------------+
         | high = byte / 16    |
         | low  = byte % 16    |
         +----------+----------+
                    |
    +---------------+------------------+
    |                                  |
    v                                  v
Convert high nibble                Convert low nibble
(ASCII '0'..'9' or 'a'..'f')       (ASCII '0'..'9' or 'a'..'f')

```

---

## 3.4 Final Code

```c
void	print_byte_hex(unsigned char byte)
{
	unsigned char high_nibble = byte / 16;
	unsigned char low_nibble  = byte % 16;

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

---

# ------------------------------------------------------------

# 📍 **Chapter 4 — Function 2: print_string_hex()**

# ------------------------------------------------------------

## 4.1 Purpose

Print each character of a string as two hex digits.

## 4.2 Important Concept: Characters ARE Bytes

A `char` is guaranteed to be exactly **1 byte**.

```
str[i] → one byte → print in hex
```

---

## 4.3 Memory Diagram

For `"Hi"`:

```
Address     Byte     ASCII     Hex
0x1000      48        'H'      48
0x1001      69        'i'      69
0x1002       0       '\0'      00
```

---

## 4.4 Final Code

```c
void	print_string_hex(char *str)
{
	int i = 0;
	unsigned char byte;
	unsigned char high_nibble;
	unsigned char low_nibble;

	while (str[i] != '\0')
	{
		byte = (unsigned char)str[i];

		high_nibble = byte / 16;
		low_nibble  = byte % 16;

		if (high_nibble < 10)
			ft_putchar('0' + high_nibble);
		else
			ft_putchar('a' + (high_nibble - 10));

		if (low_nibble < 10)
			ft_putchar('0' + low_nibble);
		else
			ft_putchar('a' + (low_nibble - 10));

		i++;
	}
}
```

---

# ------------------------------------------------------------

# 📍 **Chapter 5 — Understanding Memory Layout of Integers**

# ------------------------------------------------------------

## 5.1 Integers Are Multiple Bytes

A typical 32-bit integer:

```
int n = 0x12345678;
```

Stored in memory as 4 bytes:

```
Memory (little endian):   78 56 34 12
Printed (big endian):     12 34 56 78
```

---

## 5.2 Diagram: Address and Bytes

```
Address:   0x2000  0x2001  0x2002  0x2003
Content:     78      56      34      12
              ^       ^       ^       ^
             b0      b1      b2      b3
```

When printing, we reverse to big-endian style:

```
12 34 56 78
```

---

# ------------------------------------------------------------

# 📍 **Chapter 6 — Function 3: print_int_hex()**

# ------------------------------------------------------------

## 6.1 Purpose

Print the **raw bytes** of an integer in hex.

---

## 6.2 Key Insight

To inspect the integer byte-by-byte, we treat its address as:

```
(unsigned char *)&n
```

This gives us **direct raw memory access**.

---

## 6.3 Final Code

```c
void print_int_hex(int n)
{
	int				i;
	unsigned char	*bytes;

	bytes = (unsigned char *)&n;
	i = sizeof(n) - 1;

	while (i >= 0)
	{
		print_byte_hex(bytes[i]);
		i--;
	}
}
```

---

# ------------------------------------------------------------

# 📍 **Chapter 7 — Raw Memory & dump16()**

# ------------------------------------------------------------

## 7.1 Purpose

Read **16 bytes** starting from any memory address and print them in hex.

---

## 7.2 Universal Byte Access

Casting to `unsigned char *` allows us to treat **any data** as raw bytes:

```
(int *) → (unsigned char *)
(char *) → (unsigned char *)
(double *) → (unsigned char *)
(void *) → (unsigned char *)
```

---

## 7.3 Memory Diagram

```
addr → [ B0 | B1 | B2 | ... | B15 ]
```

We print all 16 bytes, even if some are `0x00`.

---

## 7.4 Final Code

```c
void	dump16(void *addr)
{
	int				i;
	unsigned char	*byte;

	byte = (unsigned char *)addr;
	i = 0;
	while (i < 16)
	{
		print_byte_hex(byte[i]);
		if (i < 15)
			ft_putchar(' ');
		i++;
	}
}
```

---

# ------------------------------------------------------------

# 📍 **Chapter 8 — Endianness Diagram**

# ------------------------------------------------------------

## Big-Endian (Network Order)

```
Most Significant Byte First
[ 12 ][ 34 ][ 56 ][ 78 ]
```

## Little-Endian (Intel CPUs)

```
Least Significant Byte First
[ 78 ][ 56 ][ 34 ][ 12 ]
```

## Visual Summary

```
Logical Value:  12 34 56 78
Memory Order:
    Big Endian: 12 34 56 78
 Little Endian: 78 56 34 12
```

---

# ------------------------------------------------------------

# 📍 **Chapter 9 — Summary of Key Lessons**

# ------------------------------------------------------------

### ✔ A byte is always 8 bits

### ✔ A nibble is 4 bits = one hex digit

### ✔ `unsigned char` is the only safe byte type

### ✔ Hex printing uses ASCII offsets

### ✔ Integers must be read through `unsigned char *`

### ✔ Memory dump tools ignore types and read raw bytes

### ✔ Endianness controls byte order in memory

### ✔ `dump16()` works with *any* data type

---

# ------------------------------------------------------------

# 📍 **Chapter 10 — Optional Extensions**

# ------------------------------------------------------------

I can also generate **add-on chapters**:

### 🔹 Add ASCII printable section (like `xxd`)

### 🔹 Add address column (like `ft_print_memory`)

### 🔹 Add multi-line full-memory dump

### 🔹 Add diagrams for structs in memory

### 🔹 Add pointer memory visualizations

### 🔹 Add 64-bit pointer dump section

Just tell me:

👉 **“Add more chapters.”**

---

