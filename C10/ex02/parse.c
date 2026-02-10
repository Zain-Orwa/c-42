/* parse.c */
#include "ft_tail.h"

static void	set_parse_error(t_tail *context, char *msg)
{
	ft_putstr(msg);
	context->c_option_status = -1;
	context->exit_status = 1;
}

static int	is_numeric_argument_after_c(char *number_to_check)
{
	if (!number_to_check || *number_to_check == '\0')
		return (0);
	while (*number_to_check)
	{
		if (*number_to_check < '0' || *number_to_check > '9')
			return (0);
		number_to_check++;
	}
	return (1);
}

void	parse_c_option_from_arguments(t_tail *context, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-c") == 0)
		{
			if (context->c_option_status == 1)
				return (set_parse_error(context, "ft_tail: duplicate -c option.\n"));
			if (i + 1 >= argc || !is_numeric_argument_after_c(argv[i + 1]))
				return (set_parse_error(context,
						"ft_tail: invalid or missing number after -c.\n"));
			context->bytes_to_read = ft_atoi(argv[i + 1]);
			context->marked_option_positions[i] = 1;
			context->marked_option_positions[i + 1] = 1;
			context->c_option_status = 1;
			return;
		}
		i++;
	}
	if (context->c_option_status == 0)
	{
		context->bytes_to_read = 10;
		context->c_option_status = 1;
	}
}

void	parse_targets_from_arguments(t_tail *context, int argc, char **argv)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (i < argc)
	{
		if (context->marked_option_positions[i] == 0)
			count++;
		i++;
	}
	context->parsed_targets_count = count;
	context->should_print_headers = (count > 1);
	(void)argv;
}

