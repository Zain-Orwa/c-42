/* op_main.c */
#include "do_op.h"

int main(int argc, char **argv)
{ 
	int i; 
	int a; 
	int b; 
	int (*ops[5])(int, int); 

	if (argc != 4) 
		return(0); 
	ops[0] = &op_add; 
	ops[1] = &op_sub; 
	ops[2] = &op_mul; 
	ops[3] = &op_div; 
	ops[4] = &op_mod; 
	if (!is_valid_operator_str(argv[2])) 
		return (ft_putstr("0\n"), 0); 
	a = ft_atoi(argv[1]); 
	b = ft_atoi(argv[3]); 
	i = get_operator_index(argv[2][0]); 
	if (i == 3 && b == 0) 
		return (ft_putstr("Stop : division by zero\n"), 0); 
	if (i == 4 && b == 0) 
		return (ft_putstr("Stop : modulo by zero\n"), 0); 
	ft_putnbr(ops[i](a, b)); 
	ft_putstr("\n"); 
	return(0);
}
