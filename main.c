#include <stdio.h>
#include <fcntl.h> // For open
#include <unistd.h> // For close
#include <stdlib.h> // For malloc
#include <string.h>

//Prototypes for assembly functions from libasm.a
size_t 	_ft_strlen(const char *s);
char 		*_ft_strcpy(char *dest, const char *src);
int			_ft_strcmp(const char *s1, const char *s2);
size_t 	_ft_write(int fd, const void *buf, size_t count);
size_t	_ft_read(int fd, void *buf, size_t count);
char 		*_ft_strdup(const char *s);

//Prototypes for test functions
void	test_strlen(void);
void	test_strcpy(void);
void	test_strcpm(void);
void	test_write(void);
void	test_read(void);
void	test_strdup(void);

void	print_color_meaning(void);

//Colors
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define PNK   "\x1B[38;5;206m"
#define RESET "\x1B[0m"

int main(int argc, char **argv)
{
	if (argc != 2){
		puts("Wrong number of arguments\n");
		return 1;
	}
	switch(argv[1][0]){
		case '0':
			test_strlen();
			break;
		case '1':
			test_strcpy();
			break;
		case '2':
			test_strcpm();
			break;
		case '3':
			test_write();
			break;
		case '4':
			test_read();
			break;
		case '5':
			test_strdup();
			break;
		case 'c':
			print_color_meaning();
			break;
		default:
			puts("Invalid input");
			break;
	}
	return 0;
}

void	test_strlen(void)
{
	printf("Result from " MAG "ft_strlen " RESET "when passing " PNK "Hello, world!" RESET " = " GRN "%ld\n" RESET, _ft_strlen("Hello, world!"));
	printf("Result from " MAG "ft_strlen " RESET "when passing " PNK "\"\"" RESET " = " GRN "%ld\n" RESET, _ft_strlen(""));
	printf("Result from " MAG "ft_strlen " RESET "when passing a " RED "NULL ptr" RESET " = " GRN "%ld\n" RESET, _ft_strlen(NULL));
}

void	test_strcpy(void)
{
	char	destination[20];
	char	src[] = "Hello, world!";
	char *result;

	result = _ft_strcpy(destination, src);
	printf("Result from " MAG "ft_strcpy " RESET "copying "PNK "Hello, World!" RESET " to " PNK "destination" RESET " = " GRN "%s\n" RESET, destination);

	result = _ft_strcpy(destination, "Hi");
	printf("Result from " MAG "ft_strcpy " RESET "coying over " PNK "destination " RESET "with " PNK "Hi" RESET " = " GRN "%s\n" RESET, result);

	result = _ft_strcpy(NULL, "Sending a NULL ptr!😈\n");
	if (result == NULL)
		printf("Result from " MAG "ft_strcpy " RESET "with a " RED "NULL ptr " RESET "sent to it = " GRN "%s" RESET "\n", result);
	else
		puts("This should never print since NULL was sent!");
}

void	test_strcpm(void)
{
	int result = 0 ;

	result = _ft_strcmp("Bozo", "Bozo");
	printf("Result from " MAG "ft_strcmp " RESET "comparing " PNK "Bozo " RESET "and " PNK "Bozo" RESET " = " GRN "%d" RESET "\n", result);

	result = _ft_strcmp("Bozo69", "Bozo");
	printf("Result from " MAG "ft_strcmp " RESET "comparing " PNK "Bozo69 " RESET "and " PNK "Bozo" RESET " = " GRN "%d" RESET "\n", result);

	result = _ft_strcmp("Bozo", "Bozo69");
	printf("Result from " MAG "ft_strcmp " RESET "comparing " PNK "Bozo " RESET "and " PNK "Bozo69" RESET " = " GRN "%d" RESET "\n", result);

	result = _ft_strcmp(NULL, "Sending a NULL ptr!😈\n");
	printf("Result from " MAG "ft_strcmp " RESET "being sent a " RED "NULL ptr" RESET " = " GRN "%d" RESET "\n", result);
}

void	test_write(void)
{
	int result = 0;

	_ft_write(1, "Using ft_write to write this on the STDIN!\n-----\n", 49);

	printf("Passing " RED "invalid fd" RESET " to " MAG "ft_write" RESET "\n");
	result = _ft_write(69, "BOZO", 40000);
	printf("The return after passing an " RED "invalid fd" RESET " = " GRN "%d" RESET "\n", result);
	perror("Libasm");
	_ft_write(1, "----\n", 6);

	printf("Passing " RED "NULL ptr" RESET " to " MAG "ft_write" RESET "\n");
	result = _ft_write(1, NULL, 4);
	perror("Libasm:");
	printf("The return after passing a " RED "NULL ptr" RESET " = " GRN "%d" RESET "\n", result);
}

#define BUFFER_SIZE 10

void	test_read(void)
{
	char 	buffer[BUFFER_SIZE];
	int		result = 0;
	int		fd = open("Makefile", O_RDONLY);

	if (fd == -1){
		puts("Bozo stop messing with my file");
		return;
	}

	result = _ft_read(fd, buffer, BUFFER_SIZE - 1);
	buffer[result] = '\0';
	printf("Result from " MAG "ft_read " RESET "when " PNK "Makefile " RESET "is being read at BUFFER_SIZE = " GRN "%d" RESET "\n", result);
	printf("Printing buffer:\n%s\n-----\n", buffer);

	close(fd);
	result = _ft_read(fd, buffer, BUFFER_SIZE - 1);
	buffer[result] = '\0';
	printf("Result from " MAG "ft_read " RESET "when " RED "closed fd " RESET "is being read at BUFFER_SIZE = " GRN "%d" RESET "\n", result);
	printf("Printing buffer:\n%s\n", buffer);
	perror("Libasm");
	printf("-----\n");

	// DANGEROUS TEST, can't check bound checking so will uncoment during correction
	// printf("Please enter your favorite meal here:");
	// fflush(stdout);
	// result = _ft_read(0, buffer, BUFFER_SIZE - 1);
	// buffer[result] = '\0';
	// printf("Result from " MAG "ft_read " RESET "when " PNK "STDIN " RESET "is being read at BUFFER_SIZE = " GRN "%d" RESET "\n", result);
	// printf("Printing buffer:\n%s\n-----\n", buffer);
}

void	test_strdup(void)
{
	char *result = _ft_strdup("Hi!");
	printf("Result from " MAG "ft_strdup " RESET "when " PNK "Hi! " RESET "is being passed = " GRN "%s" RESET "\n", result);
	free(result);

	result = _ft_strdup("");
	printf("Result from " MAG "ft_strdup " RESET "when " PNK "\"\" " RESET "is being passed = " GRN "%s" RESET "\n", result);
	free(result);

	result = _ft_strdup(NULL);
	if (!result)
		printf("Result from " MAG "ft_strdup " RESET "when " RED "NULL ptr " RESET "is being passed = " GRN "%s" RESET "\n", result);
	else
		puts("Shouldn't cone here!");
}

void	print_color_meaning(void)
{
	printf(MAG "██ Is the asm version of the function being called" RESET "\n");
	printf(PNK "██ Is the argument being passed to the function" RESET "\n");
	printf(RED "██ Is an invalid or erroneous argument being passed to the function" RESET "\n");
	printf(GRN "██ Is the result from the function" RESET "\n");
}