/* main.c */
#include "ft_tail.h"

int	main(int argc, char **argv)
{
	t_tail	context;

	initialize_tail_program_context(&context, argc, argv);
	if (context.exit_status != 0)
		return (context.exit_status);

	parse_c_option_from_arguments(&context, argc, argv);
	if (context.exit_status != 0){
		free(context.marked_option_positions);
		return (context.exit_status);
	}

	parse_targets_from_arguments(&context, argc, argv);
	process_files(&context, argc, argv);


	free(context.marked_option_positions);
	return (context.exit_status);
}

