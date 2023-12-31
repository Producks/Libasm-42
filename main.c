#include <stdio.h>
#include <fcntl.h> // For open
#include <unistd.h> // For close
#include <stdlib.h> // For malloc and free

//Prototypes for assembly functions from libasm.a
size_t 	ft_strlen(const char *s);
char 		*ft_strcpy(char *dest, const char *src);
int			ft_strcmp(const char *s1, const char *s2);
size_t 	ft_write(int fd, const void *buf, size_t count);
size_t	ft_read(int fd, void *buf, size_t count);
char 		*ft_strdup(const char *s);

typedef struct s_list
{
	void	*data;
	struct s_list	*next;
} t_list;

//Bonus prototypes
int 		ft_atoi_base(char *str, char *base);
void		ft_list_push_front(t_list **begin_list, void *data);
int			ft_list_size(t_list *begin_list);
void		ft_list_sort(t_list **begin_list, int (*cmp)());
t_list	*ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

//Prototypes for test functions
void	test_strlen(void);
void	test_strcpy(void);
void	test_strcpm(void);
void	test_write(void);
void	test_read(void);
void	test_strdup(void);

//Bonus test functions
void	test_ft_atoi_base();
void	test_ft_list_push_front(void);
void	test_ft_list_size(void);
void	test_ft_list_sort(void);
void	test_ft_list_remove_if(void);

//Bonus utils
t_list *generate_linked_list(void);
void		print_list(t_list *begin);
void		free_list(t_list **begin);
t_list	*generate_node(char number);
t_list	*generate_shuffled_list(void);
void		free_content(void *data);

// Print stuff
void	print_color_meaning(void);
void	print_settings(void);

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

#ifndef BONUS_FLAG
	#define BONUS_FLAG 0
#endif

int main(int argc, char **argv)
{
	if (argc != 2){
		print_settings();
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
		case '6':
			test_ft_atoi_base();
			break;
		case '7':
			test_ft_list_push_front();
			break;
		case '8':
			test_ft_list_size();
			break;
		case '9':
			test_ft_list_sort();
			break;
		case 'a':
			test_ft_list_remove_if();
			break;
		case 'b':
			test_strlen();
			test_strcpy();
			test_strcpm();
			//test_write();
			test_read();
			test_strdup();
			test_ft_atoi_base();
			test_ft_list_push_front();
			test_ft_list_size();
			test_ft_list_sort();
			test_ft_list_remove_if();
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
	printf("Result from " MAG "ft_strlen " RESET "when passing " PNK "Hello, world!" RESET " = " GRN "%ld\n" RESET, ft_strlen("Hello, world!"));
	printf("Result from " MAG "ft_strlen " RESET "when passing " PNK "\"\"" RESET " = " GRN "%ld\n" RESET, ft_strlen(""));
	printf("Result from " MAG "ft_strlen " RESET "when passing a " RED "NULL ptr" RESET " = " GRN "%ld\n" RESET, ft_strlen(NULL));
}

void	test_strcpy(void)
{
	char	destination[20];
	char	src[] = "Hello, world!";
	char *result;

	result = ft_strcpy(destination, src);
	printf("Result from " MAG "ft_strcpy " RESET "copying "PNK "Hello, World!" RESET " to " PNK "destination" RESET " = " GRN "%s\n" RESET, destination);

	result = ft_strcpy(destination, "Hi");
	printf("Result from " MAG "ft_strcpy " RESET "coying over " PNK "destination " RESET "with " PNK "Hi" RESET " = " GRN "%s\n" RESET, result);

	result = ft_strcpy(destination, "");
	printf("Result from " MAG "ft_strcpy " RESET "coying over " PNK "destination " RESET "with " PNK "\"\"" RESET " = " GRN "%s\n" RESET, result);

	result = ft_strcpy(NULL, "Sending a NULL ptr!😈\n");
	if (result == NULL)
		printf("Result from " MAG "ft_strcpy " RESET "with a " RED "NULL ptr " RESET "sent to it = " GRN "%s" RESET "\n", result);
	else
		puts("This should never print since NULL was sent!");
}

void	test_strcpm(void)
{
	int result = 0 ;

	result = ft_strcmp("Bozo", "Bozo");
	printf("Result from " MAG "ft_strcmp " RESET "comparing " PNK "Bozo " RESET "and " PNK "Bozo" RESET " = " GRN "%d" RESET "\n", result);

	result = ft_strcmp("Bozo69", "Bozo");
	printf("Result from " MAG "ft_strcmp " RESET "comparing " PNK "Bozo69 " RESET "and " PNK "Bozo" RESET " = " GRN "%d" RESET "\n", result);

	result = ft_strcmp("Bozo", "Bozo69");
	printf("Result from " MAG "ft_strcmp " RESET "comparing " PNK "Bozo " RESET "and " PNK "Bozo69" RESET " = " GRN "%d" RESET "\n", result);

	result = ft_strcmp("", "Bozo");
	printf("Result from " MAG "ft_strcmp " RESET "comparing " PNK "\"\" " RESET "and " PNK "Bozo" RESET " = " GRN "%d" RESET "\n", result);

	result = ft_strcmp(NULL, "Sending a NULL ptr!😈\n");
	printf("Result from " MAG "ft_strcmp " RESET "being sent a " RED "NULL ptr" RESET " = " GRN "%d" RESET "\n", result);
}

void	test_write(void)
{
	int result = 0;

	int fd = open("test.txt", O_WRONLY);
	if (fd == -1){
		puts("Open fatal error");
		return;
	}

	ft_write(1, "Using ft_write to write this on the STDOUT!\n-----\n", 50);

	printf("Passing " RED "invalid fd" RESET " to " MAG "ft_write" RESET "\n");
	result = ft_write(69, "BOZO", 40000);
	printf("The return after passing an " RED "invalid fd" RESET " = " GRN "%d" RESET "\n", result);
	perror("Libasm");
	ft_write(1, "----\n", 6);

	printf("Passing " RED "NULL ptr" RESET " to " MAG "ft_write" RESET "\n");
	result = ft_write(1, NULL, 4);
	perror("Libasm:");
	printf("The return after passing a " RED "NULL ptr" RESET " = " GRN "%d" RESET "\n", result);
	ft_write(1, "----\n", 6);

	printf("Passing " PNK "test.txt fd" RESET " to " MAG "ft_write" RESET "\n");
	result = ft_write(fd, "BOZO.COM", 8);
	printf("The return after passing "PNK "BOZO.COM " RESET " = " GRN "%d" RESET "\n", result);
	close(fd);
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

	result = ft_read(fd, buffer, BUFFER_SIZE - 1);
	buffer[result] = '\0';
	printf("Result from " MAG "ft_read " RESET "when " PNK "Makefile " RESET "is being read at BUFFER_SIZE = " GRN "%d" RESET "\n", result);
	printf("Printing buffer:\n%s\n-----\n", buffer);

	close(fd);
	result = ft_read(fd, buffer, BUFFER_SIZE - 1);
	buffer[result] = '\0';
	printf("Result from " MAG "ft_read " RESET "when " RED "closed fd " RESET "is being read at BUFFER_SIZE = " GRN "%d" RESET "\n", result);
	printf("Printing buffer:\n%s\n", buffer);
	perror("Libasm");
	printf("-----\n");

	// DANGEROUS TEST, can't check bound checking so will uncoment during correction
	// printf("Please enter your favorite meal here:");
	// fflush(stdout);
	// result = ft_read(0, buffer, BUFFER_SIZE - 1);
	// buffer[result] = '\0';
	// printf("Result from " MAG "ft_read " RESET "when " PNK "STDIN " RESET "is being read at BUFFER_SIZE = " GRN "%d" RESET "\n", result);
	// printf("Printing buffer:\n%s\n-----\n", buffer);
}

void	test_strdup(void)
{
	char *result = ft_strdup("Hi!");
	if (!result)
		return;
	printf("Result from " MAG "ft_strdup " RESET "when " PNK "Hi! " RESET "is being passed = " GRN "%s" RESET "\n", result);
	free(result);

	result = ft_strdup("");
	printf("Result from " MAG "ft_strdup " RESET "when " PNK "\"\" " RESET "is being passed = " GRN "%s" RESET "\n", result);
	free(result);

	result = ft_strdup(NULL);
	if (!result)
		printf("Result from " MAG "ft_strdup " RESET "when " RED "NULL ptr " RESET "is being passed = " GRN "%s" RESET "\n", result);
	else
		puts("Shouldn't cone here!");
}

void	print_settings(void)
{
	printf("To access the correct test function, pass the correct parameter\n"
	"[0] ft_strlen\n"
	"[1] ft_strcpy\n"
	"[2] ft_strcmp\n"
	"[3] ft_write\n"
	"[4] ft_read\n"
	"[5] ft_strdup\n"
	"[6] ft_atoi_base\n"
	"[7] ft_list_push_front\n"
	"[8] ft_list_size\n"
	"[9] ft_list_sort\n"
	"[a] ft_list_remove_if\n"
	"[c] Print color meaning\n"
	);
}

void	print_color_meaning(void)
{
	printf(MAG "██ Is the asm version of the function being called" RESET "\n");
	printf(PNK "██ Is the argument being passed to the function" RESET "\n");
	printf(RED "██ Is an invalid or erroneous argument being passed to the function" RESET "\n");
	printf(GRN "██ Is the result from the function" RESET "\n");
}

/*
	BONUS
*/

void	test_ft_atoi_base(void)
{
	if (BONUS_FLAG != 1){
		puts("Compile with the bonus flag");
		return;
	}
	int result = ft_atoi_base("1000101", "01");
	printf("Result after " MAG "ft_atoi_base " RESET "is called with the number " PNK "0b1000101" RESET " and a base " PNK "01" RESET " = " GRN "%d" RESET "\n", result);

	result = ft_atoi_base("-42", "0123456789");
	printf("Result after " MAG "ft_atoi_base " RESET "is called with the number " PNK "-42" RESET " and a base " PNK "0123456789" RESET " = " GRN "%d" RESET "\n", result);

	result = ft_atoi_base("FF", "0123456789ABCDEF");
	printf("Result after " MAG "ft_atoi_base " RESET "is called with the number " PNK "0xFF" RESET " and a base " PNK "0123456789ABCDEF" RESET " = " GRN "%d" RESET "\n", result);

	result = ft_atoi_base("101", "011");
	printf("Result after " MAG "ft_atoi_base " RESET "is called with the number " PNK "101" RESET " and a base " RED "011" RESET " = " GRN "%d" RESET "\n", result);

	result = ft_atoi_base("101", "01\n");
	printf("Result after " MAG "ft_atoi_base " RESET "is called with the number " PNK "101" RESET " and a base " RED "01\\n" RESET " = " GRN "%d" RESET "\n", result);

	result = ft_atoi_base("101", NULL);
	printf("Result after " MAG "ft_atoi_base " RESET "is called with the number " PNK "101" RESET " and a base " RED "NULL ptr" RESET " = " GRN "%d" RESET "\n", result);
}

void	test_ft_list_push_front(void)
{
	if (BONUS_FLAG != 1){
		puts("Compile with the bonus flag");
		return;
	}
	t_list *begining = generate_linked_list();

	if (!begining){
		puts("FATAL ERROR");
		return;
	}
	printf("Content of the linked list before any modification:\n");
	print_list(begining);
	puts("----");

	printf("Result after " MAG "ft_list_push_front " RESET "is called with the number " PNK "69" RESET ":\n");
	int	*number = malloc(sizeof(int*));
	if (!number){
		puts("FATAL ERROR");
		free_list(&begining);
		return;
	}
	*number = 69;
	ft_list_push_front(&begining, (void*)number);
	print_list(begining);
	puts("----");

	int *number_two = malloc(sizeof(int*));
	if (!number){
		puts("FATAL ERROR");
		free_list(&begining);
		return;
	}
	*number_two = 42;
	printf("Result after " MAG "ft_list_push_front " RESET "is called with the number " PNK "42" RESET ":\n");
	ft_list_push_front(&begining, (void*)number_two);
	print_list(begining);
	puts("----");

	free_list(&begining);
	begining = NULL;
	number = malloc(sizeof(int*));
	if (!number){
		puts("FATAL ERROR");
		return;
	}
	*number = 69;
	printf("Result after " MAG "ft_list_push_front " RESET "is called with the number " PNK "69" RESET " and the head being" RED " NULL" RESET ":\n");
	ft_list_push_front(&begining, number);
	print_list(begining);
	free_list(&begining);
}

void	test_ft_list_size(void)
{
	if (BONUS_FLAG != 1){
		puts("Compile with the bonus flag");
		return;
	}
	t_list *begining = generate_linked_list();
	if (!begining){
		puts("FATAL ERROR");
		return;
	}

	int result = ft_list_size(begining);
	printf("Result after " MAG "ft_list_size " RESET "is called with a list size of " PNK "3" RESET " = " GRN "%d" RESET "\n", result);

	int *number = malloc(sizeof(int));
	if (!number){
		puts("Fatal ERROR");
		free_list(&begining);
		return;
	}
	*number = 69;
	ft_list_push_front(&begining, number);
	result = ft_list_size(begining);
	printf("Result after " MAG "ft_list_size " RESET "is called with a list size of " PNK "4" RESET " = " GRN "%d" RESET "\n", result);

	result = ft_list_size(NULL);
	printf("Result after " MAG "ft_list_size " RESET "is called with " RED "NULL" RESET " = " GRN "%d" RESET "\n", result);
	free_list(&begining);
}

void	test_ft_list_sort(void)
{
	if (BONUS_FLAG != 1){
		puts("Compile with the bonus flag");
		return;
	}
	t_list	*shuffled_list = generate_shuffled_list();
	if (!shuffled_list){
		puts("FATAL ERROR");
		return;
	}
	puts("Shuffled list before sorting:");
	print_list(shuffled_list);
	puts("-----");

	printf("Result after " MAG "ft_list_sort" RESET " is called on the" PNK " shuffled_list" RESET ":\n");
	ft_list_sort(&shuffled_list, ft_strcmp);
	print_list(shuffled_list);
	free_list(&shuffled_list);
	puts("-----");

	t_list *node = generate_node(50);
	if (!node){
		puts("Fatal error");
		return;
	}
	printf("Result after " MAG "ft_list_sort" RESET " is called on " PNK "1 node" RESET ":\n");
	ft_list_sort(&node, ft_strcmp);
	print_list(node);
	free_list(&node);
	puts("-----");

	t_list *sorted_list = generate_linked_list();
	if (!sorted_list){
		puts("Fatal error");
		return;
	}
	printf("Result after " MAG "ft_list_sort" RESET " is called on a " PNK "sorted list" RESET ":\n");
	ft_list_sort(&sorted_list, ft_strcmp);
	print_list(sorted_list);
	puts("-----");
	
	printf("Result after " MAG "ft_list_sort" RESET " is called with a " RED "NULL ptr" RESET ":\n");
	ft_list_sort(&sorted_list, NULL);
	print_list(sorted_list);
	free_list(&sorted_list);

	ft_list_sort(NULL, NULL);
}

void	test_ft_list_remove_if(void)
{
	if (BONUS_FLAG != 1){
		puts("Compile with the bonus flag");
		return;
	}
	t_list *list = generate_linked_list();
	int		*number = malloc(sizeof(int));

	puts("List generated:");
	print_list(list);
	puts("----");
	*number = 1;
	printf("Result after " MAG "ft_list_remove_if" RESET " is called with a data ref of" PNK " 1" RESET ":\n");
	ft_list_remove_if(&list, number, ft_strcmp, free_content);
	print_list(list);
	puts("----");

	printf("Result after " MAG "ft_list_remove_if" RESET " is called with a data ref of" PNK " 0" RESET ":\n");
	*number = 0;
	ft_list_remove_if(&list, (void*)number, ft_strcmp, free_content);
	print_list(list);
	puts("----");

	printf("Result after " MAG "ft_list_remove_if" RESET " is called with a " RED "NULL ptr" RESET ":\n");
	ft_list_remove_if(&list, NULL, NULL, NULL);
	print_list(list);

	free_list(&list);
	free(number);
}

/*
 BONUS UTILS
*/

t_list	*generate_linked_list(void)
{
	t_list *begin = generate_node(0);
	if (!begin)
		return NULL;

	t_list *node = generate_node(1);
	if (!node){
		free(begin->data), free(begin);
		return NULL;
	}
	begin->next = node;

	t_list *node_second = generate_node(2);
	if (!node_second){
		free_list(&begin);
		return NULL;
	}
	node->next = node_second;
	return begin;
}

void		print_list(t_list *begin)
{
	t_list *current;
	current = begin;
	while (current != NULL)
	{
		if (current->data != NULL)
		{
			printf("%d\n", *(char*)(current->data));
		}
		current = current->next;
	}
}

void	free_list(t_list **begin)
{
	t_list *current = *begin;
	t_list *tmp = NULL;

	while (current != NULL)
	{
		if (current->data != NULL)
			free(current->data);
		tmp = current->next;
		free(current);
		current = tmp;
	}
}

t_list	*generate_node(char number)
{
	t_list *node = malloc(sizeof(t_list));
	if (!node)
		return NULL;
	int *data = malloc(sizeof(int));
	if (!data){
		free(node);
		return NULL;
	}

	*data = number;
	node->data = data;
	node->next = NULL;
	return node;
}

t_list	*generate_shuffled_list(void)
{
	t_list *node_one = generate_node(0);
	t_list *node_two = generate_node(125);
	t_list *node_three = generate_node(42);
	t_list *node_four = generate_node(69);
	t_list *node_five = generate_node(1);
	if (!node_one || !node_two || !node_three || !node_four || !node_five){
		if (node_one)
			free(node_one);
		if (node_two)
			free(node_two);
		if (node_three)
			free(node_three);
		if (node_four)
			free(node_four);
		if (node_five)
			free(node_five);
		return NULL;
	}

	node_one->next = node_two;
	node_two->next = node_three;
	node_three->next = node_four;
	node_four->next = node_five;
	return node_one;
}

void	free_content(void *data)
{
	free(data);
}
