/* initialize_context.c */
#include "ft_tail.h"

static void	initialize_marked_option_positions(t_tail *context, int argc)
{
	int	i;

	context->marked_option_positions = (char *)malloc(argc);
	if (!context->marked_option_positions)
	{
		context->exit_status = 1;
		return;
	}
	i = 0;
	while (i < argc)
	{
		context->marked_option_positions[i] = 0;
		i++;
	}
}

void	initialize_tail_program_context(t_tail *context, int argc, char **argv)
{
	context->prog_name = basename(argv[0]);  // Use basename
	context->bytes_to_read = 0;
	context->c_option_status = 0;
	context->parsed_targets_count = 0;
	context->should_print_headers = 0;
	context->exit_status = 0;
	initialize_marked_option_positions(context, argc);
}

