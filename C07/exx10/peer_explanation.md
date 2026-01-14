# Exx10: `ft_join_two_str` — Peer Explanation

## 📝 **Purpose**

The function:

```c
char *ft_join_str(char *str1, char *str2);
```

joins two C-strings into a **new dynamically allocated string**, inserting a single space between them:

```
"Hello" + "World" → "Hello World"
```

The function does **not modify the original inputs**, and the returned string must later be `free()`-d by the caller.

---

## 🔧 **Function Prototype**

```c
char *ft_join_str(char *str1, char *str2);
```

---

## 📌 **Parameters & Return**

| Parameter | Meaning                       |
| --------- | ----------------------------- |
| `str1`    | First null-terminated string  |
| `str2`    | Second null-terminated string |

| Return Value | Meaning                                                 |
| ------------ | ------------------------------------------------------- |
| `char *`     | Newly allocated string containing `str1 + space + str2` |
| `NULL`       | On allocation failure or invalid input                  |

---

## 🧠 **High-Level Logic**

1. Check inputs: if either `str1` or `str2` is `NULL`, return `NULL`.
2. Compute lengths of both strings.
3. Allocate memory for total length:

   ```
   total_len = len(str1) + 1(space) + len(str2) + 1('\0')
   ```
4. Copy `str1` into the new buffer.
5. Insert a space `' '` after `str1`.
6. Copy `str2` right after the space.
7. Null-terminate via `ft_strncpy`.

---

## 💻 **Code Fragment (Core Logic Only)**

```c
s1_len = ft_strlen(str1);
s2_len = ft_strlen(str2);

/* str1 + space + str2 + '\0' */
total_len = (size_t)s1_len + 1 + (size_t)s2_len;
joined_str = (char *)malloc(sizeof(char) * (total_len + 1));
if (!joined_str)
	return (NULL);

/* copy str1 */
ft_strncpy(joined_str, str1, s1_len);

/* add space after str1 */
joined_str[s1_len] = ' ';

/* copy str2 after the space */
ft_strncpy(joined_str + s1_len + 1, str2, s2_len);
```

---

## 📦 **Memory Layout Visualization**

Assume:

```
str1 = "How"
str2 = "Universe"
```

Lengths:

```
s1_len = 3
s2_len = 8
total_len = 3 + 1 + 8 = 12
```

Memory after joining:

| Index | Char | Explanation       |
| ----: | :--: | ----------------- |
|     0 |  'H' | start of str1     |
|     1 |  'o' |                   |
|     2 |  'w' | end of str1       |
|     3 |  ' ' | inserted space    |
|     4 |  'U' | start of str2     |
|     5 |  'n' |                   |
|     6 |  'i' |                   |
|     7 |  'v' |                   |
|     8 |  'e' |                   |
|     9 |  'r' |                   |
|    10 |  's' |                   |
|    11 |  'e' | end of str2       |
|    12 | '\0' | string terminator |

