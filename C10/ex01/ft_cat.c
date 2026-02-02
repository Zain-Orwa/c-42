#include <fcntl.h>
#include <errno.h>
#include <libgen.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 29000

static int g_exit_status = 0;

static size_t ft_strlen(const char *str){
	const char *start;

	start = str;
	while (*str)
		str++;

	return (size_t)(str - start);
}

static void display_error(char *program_name, char *file_name){
	int saved_errno;
	char *error_msg;


	saved_errno = errno;
	error_msg   = strerror(saved_errno);

	write(2, program_name, ft_strlen(program_name));
	write(2, ": ", 2);
	write(2, file_name, ft_strlen(file_name));
	write(2, ": ", 2);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
}

static int write_all(int fd, char *buffer, ssize_t length){
	ssize_t bytes_written;
	ssize_t total_written;

	bytes_written = 0;
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

static void ft_cat_file(int fd, char *program_name, char *file_name){
	char    buffer[BUFFER_SIZE];
	ssize_t bytes_read;

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (write_all(1, buffer, bytes_read) < 0)
		{
			display_error(program_name, file_name);
			g_exit_status = 1;
			break;
		}
	}

	if (bytes_read < 0)
	{
		display_error(program_name, file_name);
		g_exit_status = 1;
	}

	return;
}

static void process_argument(char *arg, char *program_name){
	int fd;

	if (arg[0] == '-' && arg[1] == '\0')
		fd = 0; //STDIN
	else
		fd = open(arg, O_RDONLY);

	if (fd < 0)
	{
		display_error(program_name, arg);
		g_exit_status = 1;
		return;
	}

	ft_cat_file(fd, program_name, arg);

	if (fd != 0)
		  close(fd);

	return;
}

int main(int argc, char **argv){
	int  i;
	char *program_name;

	program_name = basename(argv[0]);

	if (argc == 1)
	{
		process_argument("-", program_name);
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			process_argument(argv[i], program_name);
			i++;
		}
	}

	return (g_exit_status);
}


