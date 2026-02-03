#include <fcntl.h>
#include <errno.h>
#include <libgen.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 29000

static int g_exit_status = 0;

static size_t ft_strlen(const char *str)
{
	const char *start;

	start = str;
	while (*str)
		str++;
	return (size_t)(str - start);
}

static void display_error(const char *program_name, const char *file_name)
{
	int   saved_errno;
	char *error_msg;

	/*
		Why save errno?
		Because other calls (even inside error printing) could change errno,
		so we copy it once and use the saved value.
	*/
	saved_errno = errno;
	error_msg = strerror(saved_errno);

	write(2, program_name, ft_strlen(program_name));
	write(2, ": ", 2);
	write(2, file_name, ft_strlen(file_name));
	write(2, ": ", 2);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
}

static int write_all(int fd, char *buffer, ssize_t length)
{
	ssize_t bytes_written;
	ssize_t total_written;

	total_written = 0;
	while (total_written < length)
	{
		bytes_written = write(fd, &buffer[total_written], length - total_written);

		/*
			Q: "bytes_written <= 0" vs "< 0" — which is better?
			- write() returns -1 on error.
			- write() returning 0 is very unusual for regular files, but can happen in odd cases.
			- Using <= 0 is a defensive "treat 0 as failure to make progress" rule (avoid infinite loops).
			- Using < 0 is the "pure error check".
			I keep <= 0 here because if it ever returns 0, the loop would otherwise never progress.
		*/
		if (bytes_written <= 0)
			return (-1);

		total_written += bytes_written;
	}
	return (0);
}

static void ft_cat_file(int fd, const char *program_name, const char *file_name)
{
	char    buffer[BUFFER_SIZE];
	ssize_t bytes_read;

	/*
		Q: "How can you read a file that hasn't been opened?"
		- If fd == 0, it's STDIN, already opened by the OS before main() starts.
		- If fd is from open(), then we opened it ourselves.
	*/
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
}

static void process_argument(const char *arg, const char *program_name)
{
	int fd;

	/*
		Q: "Can we open first then check '-' ?"
		No, because "-" is a special meaning (STDIN). If you open("-"), you try to open a real file named "-".
		So we must check "-" first.
	*/
	if (arg[0] == '-' && arg[1] == '\0')
	{
		fd = 0; /* STDIN */
		ft_cat_file(fd, program_name, arg);
		return;
	}

	fd = open(arg, O_RDONLY);
	if (fd < 0)
	{
		display_error(program_name, arg);
		g_exit_status = 1;
		return;
	}

	ft_cat_file(fd, program_name, arg);

	/* Don't close STDIN (fd 0). Here it's a real file, so fd != 0 anyway. */
	close(fd);
}

int main(int argc, char **argv)
{
	int         i;
	const char *program_name;

	/*
		Q: "If argv[0] exists, why store program_name?"
		- You don't have to.
		- But basename(argv[0]) makes errors nicer (no full path),
		  and storing it avoids repeating basename(...) everywhere.
	*/
	program_name = basename(argv[0]);

	/*
		Q: "If user gives no args, how should cat behave?"
		- Read from STDIN (same as passing "-").
	*/
	if (argc == 1)
	{
		process_argument("-", program_name);
		return (g_exit_status);
	}

	/*
		Q: "Can we loop with while (*argv) { ... argv++; } ?"
		Yes, but you must skip argv[0] first.
		Here we use index style: start at 1 so we don't process program name as a filename.
	*/
	i = 1;
	while (i < argc)
	{
		process_argument(argv[i], program_name);
		i++;
	}

	return (g_exit_status);
}

