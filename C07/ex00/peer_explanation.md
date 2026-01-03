`peer_explanation.md`

---

```md
# ex00 — ft_strdup

## 🎯 Goal

Reproduce the behavior of the standard C function `strdup()`.

The function `ft_strdup`:
- takes a string `src`
- allocates new memory on the heap
- copies the content of `src` into that memory
- returns a pointer to the duplicated string
- returns `NULL` if allocation fails or if `src` is `NULL`

Only `malloc` is allowed.

---

## 🧠 What is a C string?

A C string is a sequence of characters terminated by a null byte `'\0'`.

Example:

```

"Hi" → 'H' 'i' '\0'

```

The `'\0'` is mandatory and **must be copied**.

---

## 🧩 Strategy

To duplicate a string safely:

1. Measure the length of `src` (without counting `'\0'`)
2. Allocate `length + 1` bytes
3. Copy all characters
4. Add the terminating `'\0'`
5. Return the new pointer

---

## 🧪 Memory model

If `src = "Hi"`:

```

src (original memory):
[ H ][ i ][ \0 ]

dst (malloc'ed memory):
[ H ][ i ][ \0 ]

````

Same content, **different memory addresses**.

This is what makes the duplication valid.

---

## ⏱ Complexity

Let `n` be the length of `src`:

- Time complexity: `O(n)`
- Space complexity: `O(n)`

---

## 🧠 Responsibility

The caller of `ft_strdup` **must call `free()`** on the returned pointer.

---

## ✅ Implementation (single C file)

```c
#include <stdlib.h>
#include <stdio.h>

/*
    Counts the number of characters in a string.
    The terminating '\0' is NOT included.
*/
size_t ft_strlen(const char *str)
{
    size_t i = 0;

    while (str[i])
        i++;

    return i;
}

/*
    Duplicates a string into newly allocated memory.
*/
char *ft_strdup(char *src)
{
    char   *dst;
    size_t len;
    size_t i;

    if (!src)
        return NULL;

    len = ft_strlen(src);

    dst = (char *)malloc(len + 1);
    if (!dst)
        return NULL;

    i = 0;
    while (i < len)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';

    return dst;
}
````

---

## 🧪 Optional test `main`

Use this **only for local testing**
(do not submit it in the final exercise).

```c
#ifdef TEST
int main(void)
{
    char *src = "Hello 42!";
    char *dup = ft_strdup(src);

    if (!dup)
    {
        printf("ft_strdup failed\n");
        return 1;
    }

    printf("src : %s\n", src);
    printf("dup : %s\n", dup);
    printf("src address : %p\n", (void *)src);
    printf("dup address : %p\n", (void *)dup);

    free(dup);
    return 0;
}
#endif
```

Compile with:

```
cc -Wall -Wextra -Werror ft_strdup.c -DTEST && ./a.out
```

---

## 📝 Peer Evaluation Q&A

**Q: Why allocate `len + 1` bytes?**
A: The extra byte is required for the terminating `'\0'`.

**Q: Why is the returned string independent from `src`?**
A: Because it lives in heap memory allocated by `malloc`.

**Q: What happens if `malloc` fails?**
A: The function returns `NULL`.

**Q: Who frees the memory?**
A: The caller of `ft_strdup`.

---

```

---

If you want, next I can:
- adapt this **exactly to your GitHub style**
- generate the same structure for the **next exercise**
- or review it as if I were a **42 peer evaluator**  

Just tell me.
```

