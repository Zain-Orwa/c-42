/* ft_tail.h */
#ifndef FT_TAIL_H
#define FT_TAIL_H

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>

#define BUFFER_SIZE 29000

typedef struct s_tail_program_context
{
	char	*prog_name;
	int		bytes_to_read;
	int		c_option_status;          /* 0 = not found; 1 = found valid; -1 = error */
	int		parsed_targets_count;     /* how many file targets after the parsing */
	int		should_print_headers;     /* 0/1 (true when the targets count > 1) */
	char	*marked_option_positions; /* malloc(argc) --> mark "-c" and its number */
	int		exit_status;
}	t_tail;

/* ft_utils.c */
size_t ft_strlen(const char *str);
void	 ft_putstr(const char *str);
int		 ft_strcmp(char *s1, char *s2);
int		 ft_atoi(char *str);

/* initialize_context.c */
void	initialize_tail_program_context(t_tail *context, int argc, char **argv);

/* ft_error.c */
void	display_error(const char *program_name, const char *file_name);

/* parse.c */
void	parse_c_option_from_arguments(t_tail *context, int argc, char **argv);
void	parse_targets_from_arguments(t_tail *context, int argc, char **argv);

/* process.c */
void	process_files(t_tail *context, int argc, char **argv);

#endif


