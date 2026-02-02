/* ft_display_file.c */
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

size_t ft_strlen(const char *str){
	const char *start;

	start = str;
	while (*str)
		str++;
	return (size_t)(str - start);
}

void ft_putstr(char *str){
		write(2, str, ft_strlen(str));
}

int ft_display_file(char *file_name){
	int     fd;
	char    buffer[BUFFER_SIZE];
	ssize_t	bytes_read;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (1);

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
		write(1, buffer, bytes_read);
	if (bytes_read < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int main(int argc, char *argv[]){
	if (argc < 2){
		ft_putstr("File name missing.\n");
		return (1);
	}

	if (argc > 2){
		ft_putstr("Too many arguments.\n");
		return (1);
	}

	if (ft_display_file(argv[1]) != 0){
		 ft_putstr("Cannot read file.\n");
		return (1);
	}

	return (0);
}




