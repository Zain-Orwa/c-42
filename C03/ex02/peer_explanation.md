# 🧵 Exercise 02 — `ft_strcat`

## 1️⃣ Goal of the exercise

Re-implement the behavior of `strcat`:

> **Append** the string `src` to the end of the string `dest`,
> then **return `dest`**.

* No library functions allowed (`<string.h>` is forbidden).
* You must work with **C strings** (null-terminated, `'\0'`).
* The caller must make sure `dest` has **enough space**.

Prototype:

```c
char *ft_strcat(char *dest, char *src);
```

---

## 2️⃣ Final code (index version you use)

```c
#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *str){
	int i;

	i = 0;
	while (str[i])
		i++;

	return (i);
}

char *ft_strcat(char *dest, char *src){
	int i;
	int j;

	i = ft_strlen(dest); 
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';	
	return (dest);
}

/*char    *ft_strcat(char *dest, const char *src)
{
    char *ptr = dest;

    while (*ptr)               // go to end of dest
        ptr++;
    while (*src)               // copy src
    {
        *ptr = *src;
        ptr++;
        src++;
    }
    *ptr = '\0';               // final '\0'
    return (dest);
}*/


int main(){

	char dest[20] = "Hello";
	char src[] = " World";

	ft_strcat(dest, src);
	printf("%s\n", dest);  // -> Hello World

	return 0;

}
```

We’ll call:

* **Top version** → **index version** (`i` and `j`)
* **Commented version** → **pointer version** (`ptr` and `src`)

---

## 3️⃣ How the index version works (step by step)

### 3.1 `ft_strlen`

```c
int ft_strlen(char *str){
	int i;

	i = 0;
	while (str[i])
		i++;

	return (i);
}
```

* Start with `i = 0`.
* `while (str[i])` means: “loop until we hit the `'\0'` byte”.
* Every iteration moves `i` one step to the right.
* When the loop stops, `i` is:

  * The **length** of the string.
  * Also the **index of the `'\0'`**.

Example:
`"Hello"` → indices: `H=0, e=1, l=2, l=3, o=4, '\0'=5` → `ft_strlen("Hello") == 5`.

---

### 3.2 `ft_strcat` — main logic

```c
char *ft_strcat(char *dest, char *src){
	int i;
	int j;

	i = ft_strlen(dest); 
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';	
	return (dest);
}
```

#### Step 1 – Find where to start writing

```c
i = ft_strlen(dest);
```

* `i` is now the **index of the `'\0'`** at the end of `dest`.
* That is exactly where we want to **start appending**.

For `dest = "Hello"` → `i = 5`.

#### Step 2 – Walk through `src`

```c
j = 0;
while (src[j] != '\0')
{
    dest[i] = src[j];
    i++;
    j++;
}
```

* `j` runs from `0` to `len(src) - 1`.
* Each iteration:

  * Copy the current character: `dest[i] = src[j];`
  * Move one step in `dest`: `i++`
  * Move one step in `src`: `j++`

You are *evaluating positions* by index:

* Current character in `src` → `src[j]`
* Corresponding position in `dest` → `dest[i]`

#### Step 3 – Add the new `'\0'`

```c
dest[i] = '\0';
```

* After the loop, `i` points **one past** the last copied character.
* We put the final terminator there.
* Now `dest` is a valid C string that holds the concatenation.

#### Step 4 – Return the correct pointer

```c
return (dest);
```

* You must return **the original `dest` pointer**, not `&dest[i]`, not `src`.

---

### 3.3 Tiny trace: `"Hello"` + `" World"`

Initial:

* `dest = "Hello\0................"`
* `src  = " World\0"`

1. `i = ft_strlen(dest);` → `i = 5`
2. `j = 0`; `src[j] = ' '`

Loop:

| Iteration | `src[j]` | Write to `dest[i]` | New `dest` content | `i` | `j` |
| --------: | -------- | ------------------ | ------------------ | --- | --- |
|         1 | `' '`    | dest[5] = ' '      | `"Hello "`         | 6   | 1   |
|         2 | `'W'`    | dest[6] = 'W'      | `"Hello W"`        | 7   | 2   |
|         3 | `'o'`    | dest[7] = 'o'      | `"Hello Wo"`       | 8   | 3   |
|         4 | `'r'`    | dest[8] = 'r'      | `"Hello Wor"`      | 9   | 4   |
|         5 | `'l'`    | dest[9] = 'l'      | `"Hello Worl"`     | 10  | 5   |
|         6 | `'d'`    | dest[10] = 'd'     | `"Hello World"`    | 11  | 6   |
|         7 | `'\0'`   | loop stops         |                    |     |     |

Then `dest[11] = '\0';` → `"Hello World\0"`

---

## 4️⃣ Pointer version vs index version

### 4.1 Pointer version recap

```c
/*char    *ft_strcat(char *dest, const char *src)
{
    char *ptr = dest;

    while (*ptr)               // go to end of dest
        ptr++;
    while (*src)               // copy src
    {
        *ptr = *src;
        ptr++;
        src++;
    }
    *ptr = '\0';               // final '\0'
    return (dest);
}*/
```

* `ptr` starts at `dest`.
* First loop moves `ptr` until `*ptr == '\0'` → end of `dest`.
* Second loop copies characters from `src`:

  * `*ptr = *src;`
  * `ptr++`, `src++`.
* Finally `*ptr = '\0';`.

### 4.2 How they “evaluate the index”

You asked about **how the two versions evaluate the indexes**.

| Concept                   | Index version          | Pointer version       |
| ------------------------- | ---------------------- | --------------------- |
| Where is the end of dest? | `i = ft_strlen(dest);` | `while (*ptr) ptr++;` |
| Current char in dest      | `dest[i]`              | `*ptr`                |
| Current char in src       | `src[j]`               | `*src`                |
| Move forward in dest      | `i++`                  | `ptr++`               |
| Move forward in src       | `j++`                  | `src++`               |
| Final `'\0'` position     | `dest[i] = '\0';`      | `*ptr = '\0';`        |
| Return value              | `return (dest);`       | `return (dest);`      |

So:

* **Index version** computes addresses as “base + index”.
* **Pointer version** moves the pointer itself and always uses `*ptr`.

Both are correct.
For beginners, the index version is often easier to read.
For “C-style”, the pointer version is shorter and very common.

---

## 5️⃣ Common Mistakes

| Mistake                           | Why It Fails                                                                                                            |
| --------------------------------- | ----------------------------------------------------------------------------------------------------------------------- |
| Forgetting final `dest[i] = '\0'` | Resulting string has no terminator → undefined behavior / garbage printing.                                             |
| Returning `src` instead of `dest` | API is wrong: `strcat` **must** return `dest`, not `src`.                                                               |
| Using `dest++` and returning it   | You lose the original pointer → you can’t return the start of the string.                                               |
| Off-by-one on start index         | Starting at `i = ft_strlen(dest)` is correct; starting at `i = ft_strlen(dest) + 1` would skip a byte and leave a hole. |
| Modifying `src`                   | `src` is input-only → should be `const char *src`; you must not write to it.                                            |

---

## 6️⃣ Key takeaway: `dest` must be big enough

`ft_strcat` **never checks** the size of `dest`.
This is exactly how the real `strcat` behaves.

Example of danger:

```c
char dest[10] = "Hi";
ft_strcat(dest, " this is way too long");  // ❌ BUFFER OVERFLOW
```

* `dest` only has room for 10 characters including `'\0'`.
* We try to write much more → overwrite memory we don’t own.
* Result: **undefined behavior** (crash, weird bugs, memory corruption).

From the real man page of `strcat`:

> *"The strings may not overlap, and the dest string must have sufficient space."*

So in our implementation:

* We **don’t** check available space.
* It is the **caller’s responsibility** to allocate a big enough `dest`.

---

## 7️⃣ Summary

| Concept      | Key point                                        |
| ------------ | ------------------------------------------------ |
| Loop 1       | `ft_strlen(dest)` finds where to start writing.  |
| Loop 2       | Copy characters from `src` to `dest`.            |
| Final step   | Add the final `'\0'` terminator.                 |
| Return value | Always return `dest`.                            |
| Safety       | Assume `dest` is large enough; no checks inside. |

End result:
Your `ft_strcat` behaves like the real `strcat` — simple, correct, and Moulinette-ready.

---

## 8️⃣ Peer Evaluation Q&A

You can use this section directly during a peer eval.

**Q1. What does `ft_strcat` return?**
**A:** A pointer to `dest` (the concatenated string).

**Q2. Why do we add `'\0'` at the end?**
**A:** Because we overwrote the old terminator when we started appending. We must create a **new** terminator at the end of the combined string.

**Q3. Can `dest` and `src` overlap in memory?**
**A:** No. If they overlap, behavior is undefined (same rule as the real `strcat`).

**Q4. Is `src` modified?**
**A:** No. We only read from `src`. The more “correct” prototype is `const char *src`.

**Q5. What happens if `dest` is too small?**
**A:** Buffer overflow → undefined behavior (crash, random bugs). Caller must allocate enough space.

**Q6. Why not use `strlen` from `<string.h>`?**
**A:** The subject says “Allowed functions: None”. We must implement our own `ft_strlen`.

**Q7. Which version is nicer for an exam?**
**A:** Pointer version is shorter and very common in C.
But your index version is absolutely valid and great for explaining to beginners.

**Q8. Does it handle an empty `src`?**
**A:** Yes. If `src[0] == '\0'`, the `while (src[j] != '\0')` loop never runs, and `dest` is returned unchanged.

**Q9. Can `dest` be empty?**
**A:** Yes. Example: `char dest[20] = ""; ft_strcat(dest, "hello");` → result is `"hello"`.

**Q10. Most important thing to remember?**
**A:** Don’t forget the final `'\0'`. That’s the #1 source of bugs in all string exercises.

---


