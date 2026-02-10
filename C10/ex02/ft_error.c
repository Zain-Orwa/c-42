/* ft_error.c */
#include "ft_tail.h"

void	display_error(const char *program_name, const char *file_name)
{
	int		saved_errno;
	char	*error_msg;

	saved_errno = errno;
	error_msg = strerror(saved_errno);
	write(2, program_name, ft_strlen(program_name));
	write(2, ": ", 2);
	write(2, file_name, ft_strlen(file_name));
	write(2, ": ", 2);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
}

