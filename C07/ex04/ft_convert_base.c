/* ft_convert_base.c */
#include <stdlib.h>

/* Function prototypes from ft_convert_base2.c */
int		ft_atoi_base(char *str, char *base);
char	*ft_itoa_base(int nbr, char *base);

/*----------------- ft_convert_base -----------------*/
char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		to_int;
	char	*result;

	/* FIXED: Added NULL check for nbr */
	if (!nbr)
		return (NULL);

	to_int = ft_atoi_base(nbr, base_from);
	result = ft_itoa_base(to_int, base_to);
	return (result);
}

