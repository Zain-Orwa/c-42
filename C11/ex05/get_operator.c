/* get_operator.c */
#include "do_op.h"

int get_operator_index(char c){ 
	if (c == '+') 
		return(0); 
	if (c == '-') 
		return(1); 
	if (c == '*') 
		return(2); 
	if (c == '/') 
		return(3); 
	if (c == '%') 
		return(4); 
	return (-1);
}

int is_valid_operator_str(char *str){ 
	if (!str) 
		return(0); 
	return (str[0] && is_operator(str[0]) && str[1] == '\0');
}

