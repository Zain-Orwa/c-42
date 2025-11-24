# 🧠 How the Pointer Version of `ft_strlen` Works

Here is the function again:

```c
int	ft_strlen(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr != '\0')
		ptr++;
	return (ptr - str);
}
```

Now let’s break it down step by step.

---

## 1️⃣ `char *ptr;`

We declare a pointer `ptr` that will be used to *walk through the string*.

---

## 2️⃣ `ptr = str;`

We make both pointers point to the **same place in memory**:

```
str → ['H']['e']['l']['l']['o']['\0']
ptr → ['H']['e']['l']['l']['o']['\0']
```

At this moment:

* `str` stays at the **start** of the string.
* `ptr` is our **walker pointer**.

We keep `str` unchanged because we will need its original address at the end.

---

## 3️⃣ The loop: `while (*ptr != '\0') ptr++;`

`*ptr` means: “the character at the memory location pointed to by `ptr`.”

The loop simply says:

> “As long as this character is not the null terminator, move forward to the next character.”

So it walks like this:

* Start at `H`
* Then `e`
* Then `l`
* Then `l`
* Then `o`
* Stop when you reach `'\0'`

During the loop:

```
ptr moves → H → e → l → l → o → '\0'
str stays → H
```

---

## 4️⃣ When the loop stops, `ptr` points to the `'\0'`

Example memory for `"Hello"`:

| Index | Char |
| ----- | ---- |
| 0     | 'H'  |
| 1     | 'e'  |
| 2     | 'l'  |
| 3     | 'l'  |
| 4     | 'o'  |
| 5     | '\0' |

After the loop:

```
str → index 0 ('H')
ptr → index 5 ('\0')
```

---

## 5️⃣ `return (ptr - str);`

This is pointer arithmetic.
Subtracting pointers gives the **number of bytes between them**.

Example:

```
ptr = address_of(str[5])
str = address_of(str[0])
ptr - str = 5
```

This is exactly the length of `"Hello"`.

So:

* `ptr - str` = number of characters before `'\0'`
* That is the **string length**

---

# 🧩 Why does this work?

Because in C, pointers are not just memory addresses —
you can subtract them when they point inside the same array.

Pointer subtraction:

> `(ptr - str)`
> → How many positions (bytes) `ptr` has moved from `str`.

So the distance between the start and the null terminator
**is the length of the string**.

---

# ✅ Summary (copy/paste friendly notes)

* `str` points to the start of the string.
* `ptr` also starts there.
* `ptr` walks character by character until it reaches `'\0'`.
* `str` remains at the beginning.
* The difference `(ptr - str)` equals the number of characters before `'\0'`.
* This equals the length of the string.

The pointer version works because pointer arithmetic counts how far we walked in memory.

---


