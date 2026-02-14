/* do_op.h */
#ifndef DO_OP_H
#define DO_OP_H

#include <unistd.h>

/* Character utilities */
int		is_white_space(char c);
int		is_digit(char c);
int		is_operator(char c);

/* String to number conversion */
int		ft_atoi(char *str);

/* Output functions */
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int nbr);

/* Mathematical operations */
int		op_add(int a, int b);
int		op_sub(int a, int b);
int		op_mul(int a, int b);
int		op_div(int a, int b);
int		op_mod(int a, int b);

/* Operator handling */
int		get_operator_index(char c);
int		is_valid_operator_str(char *str);

#endif /* DO_OP_H */

