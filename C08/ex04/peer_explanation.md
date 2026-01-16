````markdown
# 🧩 Exercise04: — `ft_strs_to_tab`

This exercise transforms an array of C-strings (`char **av`) into an array of structures, each containing:

- the string length
- the original string
- a duplicated copy of the string

This is a foundational 42 exercise that connects **strings**, **structs**, **dynamic memory**, **error handling**, and **sentinel termination**.

---

## 📁 Structure Definition (`ft_stock_str.h`)

We are given a header containing the structure type:

```c
typedef struct s_stock_str
{
    int  size;   // length of the string
    char *str;   // original string pointer
    char *copy;  // heap-allocated copy of the string
}   t_stock_str;
````

So for a single string `"cat"`, a `t_stock_str` contains:

| Field | Value                            |
| ----- | -------------------------------- |
| size  | 3                                |
| str   | pointer → "cat" (original)       |
| copy  | pointer → "cat" (heap duplicate) |

---

## 🎯 Goal of the Exercise

Write the function:

```c
t_stock_str *ft_strs_to_tab(int ac, char **av);
```

that:

1. Allocates an array of `t_stock_str` of size `ac + 1`
2. For each index `i < ac`:

   * compute length of `av[i]`
   * set `str = av[i]`
   * set `copy = heap duplicate of av[i]`
3. Add a **sentinel element** at index `ac` where `str = 0`
4. Return a pointer to the first element of the array
5. Return `NULL` on allocation failure (full cleanup if needed)

---

## 🧱 Helper Functions

### `ft_strlen`

Classic loop that counts characters until `'\0'`

```c
int ft_strlen(char *str)
{
    int len = 0;
    while (str[len])
        len++;
    return (len);
}
```

### `ft_strdup`

Duplicates `src` to dynamically allocated memory:

```c
char *ft_strdup(char *src)
{
    int     i;
    int     len;
    char    *dst;

    if (!src)
        return (NULL);

    len = ft_strlen(src);
    dst = (char *)malloc(sizeof(char) * (len + 1));
    if (!dst)
        return (NULL);
    i = 0;
    while (i < len)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}
```

📌 **Important memory note:**
`ft_strdup` returns a pointer to **heap-allocated memory**, and therefore must later be `free()`d by the caller.

---

## 🧱 Main Function: `ft_strs_to_tab`

Full implementation:

```c
t_stock_str *ft_strs_to_tab(int ac, char **av)
{
    int         i;
    t_stock_str *arr;

    if (!av || ac < 0)
        return (NULL);

    arr = (t_stock_str *)malloc(sizeof(t_stock_str) * (ac + 1));
    if (!arr)
        return (NULL);

    i = 0;
    while (i < ac)
    {
        arr[i].size = ft_strlen(av[i]);
        arr[i].str  = av[i];
        arr[i].copy = ft_strdup(av[i]);
        if (!arr[i].copy)
        {
            while (--i >= 0)
                free(arr[i].copy);
            free(arr);
            return (NULL);
        }
        i++;
    }
    arr[i].size = 0;
    arr[i].str  = 0;
    arr[i].copy = 0;

    return (arr);
}
```

---

## 🧩 Sentinel Element Explained

The subject specifies:

> “The returned array should be allocated in memory and its last element’s `str` set to 0.”

This creates a **sentinel** like `'\0'` in strings.

### Sentinel pattern:

* Strings end with `'\0'`
* Our struct array ends with `.str == 0`

So functions like `ft_show_tab` can do:

```c
int i = 0;
while (arr[i].str != 0)
    ...
```

No need to store or pass `ac`.

---

## 🧠 Memory Model

Assume:

```
ac = 3
av = ["cat", "dog", "42"]
```

After `ft_strs_to_tab(ac, av)`:

### Heap layout:

```
arr (heap):
+----------------------------------------------+
| [0] size=3 str=ptrA copy=ptrB                |
| [1] size=3 str=ptrC copy=ptrD                |
| [2] size=2 str=ptrE copy=ptrF                |
| [3] size=0 str=NULL copy=NULL                |  <- sentinel
+----------------------------------------------+

ptrB → "cat\0"  (heap)
ptrD → "dog\0"  (heap)
ptrF → "42\0"   (heap)
```

Notes:

* `arr` is a heap array of structs
* `.str` pointers refer to **original strings**, not copies
* `.copy` pointers refer to **malloc duplicates**

---

## 💡 Why `.str = av[i]` is NOT malloc

A common beginner confusion:

> “Should `.str` be duplicated using malloc?”

Answer: **No.**

Reason:

* `.str` represents the **original** string
* `.copy` represents a **new independent buffer**
* Two mallocs per string would waste memory and be semantically wrong

---

## 🔥 Error Handling Philosophy

This line is crucial:

```c
if (!arr[i].copy)
{
    while (--i >= 0)
        free(arr[i].copy);
    free(arr);
    return (NULL);
}
```

We clean **all previously allocated `copy` fields** before exiting.

### ⚠ Why not just `free(arr)`?

Because:

* `free(arr)` frees only the struct array
* each `arr[i].copy` is a separate allocation
* if we don’t free them → **memory leak**

So a proper cleanup frees:

1. Every successfully `malloc`ed `copy`
2. Then the `arr` block itself

---

## ❓ Q&A (based on real peer questions)

### **Q: Is `arr[i].str` stored on the stack or heap?**

**A:** Neither guaranteed — it simply **points to `av[i]`**.
Where `av[i]` lives depends on context:

* In `main(int ac, char **av)`: typically string literals are in the **read-only data segment**
* If user allocated memory: possibly on the **heap**

`arr[i].str = av[i]` does **not copy the data**, just the pointer.

---

### **Q: Is this function returning a pointer to struct?**

**A:** Yes. It returns `t_stock_str *`, which is a pointer to the **first element** of a struct array on the **heap**.

---

### **Q: Why add `ac + 1` instead of just `ac`?**

Because the last struct is a **sentinel** (`.str = 0`), similar to `'\0'` terminating a C string.

---

### **Q: Why not just `free(arr)` if something fails?**

Because each `arr[i].copy` is a separate allocation. To avoid leaks, you must:

1. `free(arr[i].copy)` for all previously allocated copies
2. `free(arr)` at the end

---

## 🏁 Conclusion

This exercise teaches several important C programming concepts:

* Struct definitions with `typedef`
* Pointers to arrays of structs
* Dynamic allocation of arrays and strings
* Safe `malloc` + error handling
* Sentinel termination design patterns
* Separation of ownership (`str` vs `copy`)
* Proper cleanup to avoid memory leaks

Understanding this well makes the next exercise (`ft_show_tab`) almost trivial, because it simply iterates over the sentinel-terminated array and displays the fields.

---

```

