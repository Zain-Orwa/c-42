/* process.c */
#include "ft_tail.h"

static int	write_all(int fd, char *buffer, ssize_t length)
{
	ssize_t	bytes_written;
	ssize_t	total_written;

	total_written = 0;
	while (total_written < length)
	{
		bytes_written = write(fd, &buffer[total_written], length - total_written);
		if (bytes_written <= 0)
			return (-1);
		total_written += bytes_written;
	}
	return (0);
}

static int	open_file(t_tail *context, char *file_name)
{
	int	fd;

	if (ft_strcmp(file_name, "-") == 0)
		return (0);  // stdin is file descriptor 0

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		display_error(context->prog_name, file_name);
		context->exit_status = 1;
	}
	return (fd);
}

static char	*allocate_tail_buffer(t_tail *context)
{
	char	*buffer;

	if (context->bytes_to_read <= 0)
		return (NULL);  // Don't allocate for 0 or negative

	buffer = (char *)malloc(context->bytes_to_read);
	if (!buffer)
		context->exit_status = 1;
	return (buffer);
}

static void	copy_to_tail_buffer(t_tail *context, char *buffer, char *read_chunk,
                 ssize_t bytes_read, size_t *current_position)
{
	size_t	i;
	size_t	buffer_size;

	if (context->bytes_to_read <= 0)  // ADD THIS CHECK
		return;

	buffer_size = (size_t)context->bytes_to_read;
	i = 0;
	while (i < (size_t)bytes_read)
	{
		buffer[*current_position] = read_chunk[i];
		*current_position = (*current_position + 1) % buffer_size;
		i++;
	}
}

static void	print_tail_buffer(char *buffer, size_t current_position,
	size_t total_read, size_t bytes_to_read)
{
	size_t	bytes_to_print;
	size_t	start_index;
	size_t	first_part;

	if (bytes_to_read == 0)  // ADD THIS
		return;

	if (total_read < bytes_to_read)
	{
		bytes_to_print = total_read;
		start_index = 0;
	}
	else
	{
		bytes_to_print = bytes_to_read;
		start_index = current_position;
	}
	first_part = bytes_to_read - start_index;
	if (first_part > bytes_to_print)
		first_part = bytes_to_print;
	write_all(1, &buffer[start_index], (ssize_t)first_part);
	if (bytes_to_print > first_part)
		write_all(1, buffer, (ssize_t)(bytes_to_print - first_part));
}

static void	read_file(t_tail *context, int fd, char *buffer, char *file_name)
{
	char	read_chunk[BUFFER_SIZE];
	ssize_t	bytes_read;
	size_t	total_read;
	size_t	current_position;

	total_read = 0;
	current_position = 0;
	while ((bytes_read = read(fd, read_chunk, BUFFER_SIZE)) > 0)
	{
		copy_to_tail_buffer(context, buffer, read_chunk,
			bytes_read, &current_position);
		total_read += (size_t)bytes_read;
	}
	if (bytes_read < 0)
	{
		display_error(context->prog_name, file_name);
		context->exit_status = 1;
		return;
	}

	if (context->bytes_to_read > 0)  // ADDED GUARD
	{
		print_tail_buffer(buffer, current_position,
			total_read, (size_t)context->bytes_to_read);
	}
}

static void	print_header(t_tail *context, char *file_name, int is_first)
{
	if (!context->should_print_headers)
		return;
	if (!is_first)
		write(1, "\n", 1);
	write(1, "==> ", 4);
	write(1, file_name, ft_strlen(file_name));
	write(1, " <==\n", 5);
}

static void	ft_tail_file(t_tail *context, char *file_name)
{
	int		fd;
	char	*buffer;

	fd = open_file(context, file_name);
	if (fd < 0)
		return;

	if (context->bytes_to_read <= 0)
		return ((void)close(fd));

	buffer = allocate_tail_buffer(context);
	if (!buffer)
		return ((void)close(fd));

	read_file(context, fd, buffer, file_name);
	free(buffer);

	if (fd != 0)
		close(fd);
}

void	process_files(t_tail *context, int argc, char **argv)
{
	int	i;
	int	is_first;

	i = 1;
	is_first = 1;

	// If no files provided, read from stdin
	if (context->parsed_targets_count == 0)
	{
		ft_tail_file(context, "-");  // Use "-" convention for stdin
		return;
	}

	while (i < argc)
	{
		if (context->marked_option_positions[i] == 0)
		{
			print_header(context, argv[i], is_first);
			ft_tail_file(context, argv[i]);
			is_first = 0;
		}
		i++;
	}
}

