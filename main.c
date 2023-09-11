#include <stdio.h>

//Prototypes for assembly functions from libasm.a
size_t _ft_strlen(const char *s);
size_t _ft_write(int fd, const void *buf, size_t count);
char 	*_ft_strcpy(char *dest, const char *src);

//Prototypes for test functions
void	test_strlen(void);
void	test_strcpy(void);
void	test_write(void);

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
	switch(argv[1][0])
	{
		case '0':
			test_strlen();
			break;
		case '1':
			test_strcpy();
			break;
		case '2':
			test_write();
			break;
		default:
			puts("Invalid input");
			break;
	}
	return 0;
}

void	test_strlen(void)
{
	printf("ft_strlen result when passing " PNK "Hello, world!" RESET " = " GRN "%ld\n" RESET, _ft_strlen("Hello, world!"));
	printf("ft_strlen result when passing " PNK "\"\"" RESET " = " GRN "%ld\n" RESET, _ft_strlen(""));
	printf("ft_strlen result when passing a " RED "NULL ptr" RESET " = " GRN "%ld\n" RESET, _ft_strlen(NULL));
}

void	test_strcpy(void)
{
	char	destination[20];
	char	src[] = "Hello, world!";
	char *result = _ft_strcpy(destination, src);
	if (!result)
		puts("NULL");
	else
		printf("%s\n", result);
}

void	test_write(void)
{
	int ret = 0;

	_ft_write(1, "Using ft_write to write this on the STDIN!\n-----\n", 49);

	printf("Passing " RED "invalid fd" RESET " to ft_write\n");
	ret = _ft_write(69, "BOZO", 40000);
	printf("The return after passing an " RED "invalid fd" RESET " = " GRN "%d" RESET "\n", ret);
	perror("Libasm");
	_ft_write(1, "----\n", 6);

	printf("Passing " RED "NULL ptr" RESET " to ft_write\n");
	ret = _ft_write(1, NULL, 4);
	perror("Libasm:");
	printf("The return after passing a " RED "NULL ptr" RESET " = " GRN "%d" RESET "\n", ret);
}