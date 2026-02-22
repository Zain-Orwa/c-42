# 📚 C12 – Chapter III

# 🧩 Exercise 00 – `ft_create_elem`

---

## 🧠 Objective

Create a function:

```c
t_list *ft_create_elem(void *data);
```

This function must:

* Allocate memory for a new `t_list` node
* Store `data` inside the node
* Set `next` to `NULL`
* Return the newly created node
* Return `NULL` if allocation fails

Allowed function:
`malloc`

---

# 🏗 Step 1 — Understanding the Structure

## 📌 The struct

```c
typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;
```

### What this means:

| Field  | Type              | Purpose                 |
| ------ | ----------------- | ----------------------- |
| `data` | `void *`          | Stores any type of data |
| `next` | `struct s_list *` | Points to the next node |

---

## 🧠 Why `void *`?

Because this list is **generic**.

It can store:

* `int *`
* `char *`
* `struct *`
* anything

Example:

```c
int a = 42;
t_list *node = ft_create_elem(&a);
```

Now:

```
node->data → address of a
```

---

# 🔧 Step 2 — What ft_create_elem Must Do

## Logical Steps:

1. Allocate memory for 1 node
2. If malloc fails → return NULL
3. Assign `data`
4. Set `next = NULL`
5. Return node

---

# 💻 Final Implementation

```c
t_list	*ft_create_elem(void *data)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}
```

---

# 🧠 Memory Visualization

Let’s say we do:

```c
int x = 10;
t_list *node = ft_create_elem(&x);
```

---

## 🗂 Stack Memory

```
x = 10
node → 0x1000
```

---

## 🧱 Heap Memory (malloc)

At address 0x1000:

```
+---------------------+
| data  →  &x         |
| next  →  NULL       |
+---------------------+
```

---

## 📊 Full Memory Diagram

```
STACK                         HEAP
-----                         -----
x = 10                        0x1000:
node ───────────────┐        +----------------+
                     └──────► | data → &x     |
                              | next → NULL   |
                              +----------------+
```

Important:

The node itself is on the heap.
The pointer `node` is on the stack.

---

# 🧠 Why next = NULL?

Because:

This node is alone.

```
[node] → NULL
```

It is the end of the list.

If we didn’t set it to NULL:

* It would contain garbage
* Traversing the list would cause undefined behavior

---

# 🚨 Why Check malloc?

```c
if (!node)
	return (NULL);
```

Because malloc can fail.

If we don’t check:

* Dereferencing `node->data` would crash.

---

# 📌 sizeof(t_list) vs sizeof(*node)

Both are valid:

```c
malloc(sizeof(t_list));
malloc(sizeof(*node));
```

42 usually accepts both.

---

# 🧠 Common Mistakes in This Exercise

❌ Forgetting to check malloc
❌ Forgetting to set `next = NULL`
❌ Allocating wrong size
❌ Writing:

```c
node = malloc(sizeof(node));
```

This is WRONG.

Because:

```
sizeof(node) → size of pointer (8 bytes)
```

But we need:

```
sizeof(t_list) → full struct size
```

---

# 🧩 How This Fits in Linked Lists

This function only creates **one node**.

It does NOT:

* Add to front
* Add to back
* Link nodes

It just creates:

```
[data | NULL]
```

Later exercises will connect them.

---

# 🎯 Concept Summary

| Concept               | What You Learned              |
| --------------------- | ----------------------------- |
| Struct self-reference | `struct s_list *next`         |
| Generic list          | `void *data`                  |
| Heap allocation       | `malloc(sizeof(t_list))`      |
| Safe coding           | Check allocation              |
| Linked list base      | Every list starts with a node |

---

# 🧠 Mental Model

Think of this function as:

> “Create one box. Put something inside it. Leave the arrow empty.”

```
[ DATA | → NULL ]
```

That’s it.

---

# 🔥 Why This Exercise Is Important

This is the foundation of:

* ft_list_push_front
* ft_list_size
* ft_list_last
* ft_list_push_back
* ft_list_clear
* ft_list_remove_if

If this function is wrong → everything breaks.

---

# 🧪 Small Test Example

```c
int main(void)
{
	int x = 42;
	t_list *node;

	node = ft_create_elem(&x);

	if (node)
		printf("%d\n", *(int *)node->data);

	return (0);
}
```

Output:

```
42
```

---

# 🏁 Final Understanding

This exercise teaches:

* How to allocate structures
* How pointers inside structures work
* How linked lists begin
* Why NULL termination matters
* Stack vs Heap memory difference

---

