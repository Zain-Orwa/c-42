````markdown
# peer_explanation.md — C11 ex05: do-op

---

## ✅ Goal of the exercise

Build a program named **`do-op`** that:

- Is executed with **3 arguments**: `value1 operator value2`
  - Example: `./do-op 42 "+" 21`
- Prints the result of the operation.
- Uses an **array of pointers to functions** to select the correct operation.
- If the operator is invalid → print `0` (and newline).
- If `argc != 4` → print nothing.
- If division by `0` → print: `Stop : division by zero`
- If modulo by `0` → print: `Stop : modulo by zero`

Allowed function: **`write`**

---

## 🧠 What you learn from this exercise

This exercise is mainly about:

1. **Function pointers**
2. Using them inside an **array**
3. Selecting a function dynamically based on input
4. Handling **special error cases** before calling the function

---

## 📌 Program structure

Your program is split into logical files:

- `op_main.c`  
  Contains `main` and the array of function pointers.

- `do_op_ops.c`  
  Contains the operation functions:
  - `op_add`, `op_sub`, `op_mul`, `op_div`, `op_mod`

- `get_operator.c`  
  Maps an operator character to an index:
  - `+ -> 0`, `- -> 1`, `* -> 2`, `/ -> 3`, `% -> 4`
  Also checks operator validity.

- `utils.c`  
  Contains helper functions:
  - `ft_atoi`, `ft_putnbr`, `ft_putstr`, etc.

---

## 🔥 The key idea: Function pointers

### ✅ What is a function pointer?

A **function pointer** is a variable that stores the **address of a function** in memory.

Like:

- `int *p;` stores the address of an `int`
- `int (*f)(int,int);` stores the address of a function that returns `int` and takes `(int,int)`

So this:

```c
int (*f)(int, int);
````

means:

> `f` can point to any function that looks like:
> `int something(int, int);`

---

## ✅ Why we need function pointers in this exercise

We have 5 operators, each needs a different function:

* `+` → add
* `-` → sub
* `*` → mul
* `/` → div
* `%` → mod

Instead of writing 5 big `if` or `switch`, we do:

### ✅ Build an array of operation functions:

```c
int (*ops[5])(int, int);

ops[0] = &op_add;
ops[1] = &op_sub;
ops[2] = &op_mul;
ops[3] = &op_div;
ops[4] = &op_mod;
```

Now we can select the correct function by index.

---

## ✅ How we call a function through a function pointer

This line is the whole point:

```c
ft_putnbr(ops[i](a, b));
```

Breakdown:

* `ops[i]` → gives you a **function pointer**
* `ops[i](a, b)` → calls that function with `(a, b)`
* result is printed

It’s exactly like:

```c
ft_putnbr(op_add(a, b));
```

but selected dynamically.

---

## 🧩 Why we must validate before calling

### Invalid operator

If we do:

```c
i = get_operator_index(argv[2][0]);
ft_putnbr(ops[i](a, b));
```

and operator is invalid → `i = -1`
Then `ops[-1]` is **out of bounds** → crash.

So we first verify:

```c
if (!is_valid_operator_str(argv[2]))
    return (ft_putstr("0\n"), 0);
```

Then we safely know `i` will be from `0..4`.

---

## ⚠️ Division/modulo by 0 must be handled BEFORE calling ops[i]

Because:

* `op_div(a, 0)` and `op_mod(a, 0)` causes undefined behavior.
* So we must catch these cases before:

```c
if (i == 3 && b == 0)
    return (ft_putstr("Stop : division by zero\n"), 0);
if (i == 4 && b == 0)
    return (ft_putstr("Stop : modulo by zero\n"), 0);
```

Only if safe → call the function.

---

## 🧠 Memory diagram: function pointer array

Imagine memory like this:

### Stack (inside main)

```
+----------------------------------+
| ops (array of 5 function ptrs)   |
|----------------------------------|
| ops[0] -> address of op_add      |
| ops[1] -> address of op_sub      |
| ops[2] -> address of op_mul      |
| ops[3] -> address of op_div      |
| ops[4] -> address of op_mod      |
+----------------------------------+

| a = ft_atoi(argv[1])             |
| b = ft_atoi(argv[3])             |
| i = get_operator_index(...)      |
+----------------------------------+
```

### Text segment (where code lives)

```
+--------------------------+
| op_add code              |
+--------------------------+
| op_sub code              |
+--------------------------+
| op_mul code              |
+--------------------------+
| op_div code              |
+--------------------------+
| op_mod code              |
+--------------------------+
```

So `ops[0]` contains the address pointing into the code section where `op_add` exists.

---

## 🧠 What happens when calling ops[i](a,b)

Example command:

```bash
./do-op 25 "/" 5
```

Step-by-step:

1. `argv[2][0]` is `'/'`
2. `get_operator_index('/')` returns `3`
3. `ops[3]` points to `op_div`
4. Call:

```c
ops[3](25, 5)
```

This is the same as:

```c
op_div(25, 5)
```

Returns: `5`

---

## ✅ Important behavior of ft_atoi (why some “weird tests” work)

Example test:

```bash
./do-op 42amis - ---20toto12
```

* `ft_atoi("42amis")` → reads digits then stops → `42`
* `ft_atoi("---20toto12")`:

  * signs: `---` means negative (odd number of '-')
  * reads digits `20` then stops
  * result: `-20`

So operation: `42 - (-20) = 62`

---

## ✅ Summary of the solution logic (main flow)

1. If `argc != 4` → stop
2. Create operation pointer array `ops`
3. Validate operator string:

   * must be **one character only**
   * must be one of `+ - * / %`
4. Convert numbers using `ft_atoi`
5. Find operator index using `get_operator_index`
6. Handle division/mod by zero
7. Call function pointer: `ops[i](a, b)`
8. Print result + newline

---

## 🔁 What function pointer patterns you’ve used so far (so far in C11)

In C11 exercises, you’ve used function pointers in different ways:

### 1) Passing a function as parameter

Example: `ft_foreach`, `ft_any`, `ft_count_if`

```c
void ft_foreach(int *tab, int length, void (*f)(int));
```

Meaning:

* You give `ft_foreach` a function `f`
* It calls `f` on each element

### 2) Returning a result after applying a function

Example: `ft_map`

* takes function pointer
* applies to each value
* stores result in new array

### 3) Storing multiple functions in an array

This exercise (do-op) is the first time you used:

✅ **array of function pointers**

That means:

* you can choose between many functions at runtime
* without switch/if chains
* and it scales well when operations grow

---

## ✅ Common mistakes (and how you avoided them)

* ❌ calling `ops[-1]` when operator is invalid
* ❌ printing error but still dividing by 0
* ❌ accepting operators like `^` without subject requirement
* ✅ validating operator string length (`str[1] == '\0'`)
* ✅ checking zero division before calling function

---

## ✅ Final note

This exercise teaches a powerful real-world technique:

> using function pointer arrays to build a dispatcher

This is used everywhere:

* calculators
* command handlers
* system calls wrappers
* interpreters
* menu-based programs

---

```
```

