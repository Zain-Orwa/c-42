###Exercise 02 : ft_iterative_power

## Key Requirements:
1. **Iterative** (not recursive)
2. Return `mb^power` (mb raised to the power)
3. Return `0` if power is negative
4. `0^0` should return `1` (special case defined in the problem)
5. Don't handle overflows
6. Function prototype: `int ft_iterative_power(int nb, int power)`

## Solution:

```c
int	ft_iterative_power(int nb, int power)
{
	int	result;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	result = 1;
	while (power > 0)
	{
		result *= nb;
		power--;
	}
	return (result);
}
```

## Explanation:

1. **Input validation**:
   - If `power < 0`, return `0` immediately

2. **Edge case handling**:
   - If `power == 0`, return `1` (this includes the special case `0^0 = 1`)

3. **Iterative calculation**:
   - Initialize `result` to `1`
   - Loop `power` times, multiplying `result` by `nb` each time
   - Decrement `power` in each iteration until it reaches `0`

4. **Return value**: The calculated power result

## Example outputs:
- `ft_iterative_power(2, 3)` → `8` (2³ = 8)
- `ft_iterative_power(5, 0)` → `1`
- `ft_iterative_power(0, 0)` → `1` (special case)
- `ft_iterative_power(3, -2)` → `0` (negative power)
- `ft_iterative_power(-2, 3)` → `-8` (handles negative base correctly)

