# 🧩 Exercise 00 : `ft_ft`

### 📁 Directory

`ex00/`

### 📄 File to turn in

`ft_ft.c`

### ⚙️ Allowed functions

None

---

## 🧠 Objective

Create a function that takes a **pointer to an integer** and sets the value of that integer to **42**.

---

## 📘 Final Code

```c
void ft_ft(int *nbr)
{
	*nbr = 42;
}
```

---

## 🔍 Explanation

| Concept      | Description                                                                            |
| ------------ | -------------------------------------------------------------------------------------- |
| `int *nbr`   | A **pointer** that holds the memory address of an integer variable                     |
| `*nbr`       | The **dereferenced value** of that pointer — the actual integer stored at that address |
| `*nbr = 42;` | Changes the value stored in that memory address to 42                                  |

---

## 🧩 Example to Visualize

```c
int main(void)
{
	int n;
	int *ptr;

	n = 5;          // initial value
	ptr = &n;       // ptr now points to n’s address
	ft_ft(ptr);     // changes n’s value to 42

	// now n == 42
}
```

### 💡 Memory Representation

| Variable | Value        | Memory Address | Points To |
| -------- | ------------ | -------------- | --------- |
| `n`      | 42           | `0x7ffee...`   | —         |
| `ptr`    | `0x7ffee...` | `0x7ffee...`   | `n`       |

---

## 🧠 Step-by-Step Logic

| Step | What Happens                                                                          |
| ---- | ------------------------------------------------------------------------------------- |
| 1️⃣  | `main()` defines an integer `n` and initializes it.                                   |
| 2️⃣  | `ptr = &n;` → `ptr` now holds the address of `n`.                                     |
| 3️⃣  | Function `ft_ft(ptr)` is called.                                                      |
| 4️⃣  | Inside `ft_ft`, the pointer `nbr` receives the same address as `ptr`.                 |
| 5️⃣  | `*nbr = 42;` modifies the content stored at that address — i.e., changes `n` to `42`. |

---

## 🧩 Why It’s Called `ft_ft`

Because you’re **"setting a value" through a pointer** — it’s the first step into understanding how to manipulate variables indirectly through memory.

---

## 🧠 Key Concept: Dereferencing

👉 **Dereferencing** means:

> Accessing or modifying the actual data located at a memory address stored in a pointer.

So when you write:

```c
*nbr = 42;
```

It doesn’t assign 42 to the pointer itself, but rather to the **integer it points to**.

---

## 💬 Common Mistakes

| Mistake                                          | Why It’s Wrong                                                          |
| ------------------------------------------------ | ----------------------------------------------------------------------- |
| Writing `nbr = 42;`                              | ❌ Changes the pointer’s address, not the value it points to             |
| Forgetting `*` before `nbr`                      | ❌ You’d only reassign where the pointer points, not the actual variable |
| Declaring without pointer: `void ft_ft(int nbr)` | ❌ Would only modify a copy, not the original variable in memory         |

---

## 🧩 Summary

| Concept           | Description                                                |
| ----------------- | ---------------------------------------------------------- |
| **Pointer**       | A variable that stores the **address** of another variable |
| **Dereferencing** | Accessing the **value** stored at that address             |
| **Goal**          | Change a variable indirectly via its pointer               |
| **Result**        | The variable becomes 42                                    |

✅ **Output after `ft_ft`:**
`n` now holds the value **42**.

---

## 🧩 Peer Evaluation Q&A

### 🧠 Q1: What does the function do?

**A:** It sets the integer pointed to by `nbr` to 42.

---

### 🧠 Q2: Why do we pass a pointer?

**A:** So the function can modify the **original variable** in memory, not just a copy.

---

### 🧠 Q3: What’s the difference between `nbr` and `*nbr`?

**A:** `nbr` stores the memory address, while `*nbr` accesses the value stored there.

---

### 🧠 Q4: What happens if we remove the `*`?

**A:** The code would assign 42 to the pointer variable itself (invalid), not to the integer it points to.

---

### 🧠 Q5: Why is 42 used here?

**A:** It’s a symbolic number in programming culture — from *The Hitchhiker’s Guide to the Galaxy* — representing “the answer to everything.”


