#include <stdlib.h>
#include <stdio.h>

typedef struct s_list
{
	void	*data;
	struct s_list	*next;
} t_list;

t_list *generate_linked_list(void);
void		print_list(t_list *begin);
void		free_list(t_list **begin);
t_list	*generate_node(int number);

void		ft_list_push_front(t_list **begin_list, void *data);

int	main(void)
{
	t_list *begining = NULL;
	int *test = malloc(sizeof(int));

	*test = 69;
	//begining = generate_linked_list();
	ft_list_push_front(&begining, test);
	begining->next = NULL;
	char *a = NULL;
	printf("?%s\n", a);
	// printf("%d\n", *test);
	// printf("%d\n", *(int*)begining->data);
	// return 0;
	// if (!begining){
	// 	puts("NULL");
	// 	return 0;
	// }
	print_list(begining);
	free_list(&begining);
}

// void	ft_list_push_front(t_list **begin_list, void *data)
// {
// 	t_list *node = malloc(sizeof(t_list));
// 	node->data = data;
// 	if (!begin_list)
// 		return;
// 	if (!*begin_list)
// 	{
// 		*begin_list = node;
// 		node->next = NULL;
// 	}
// 	else
// 	{
// 		node->next = *begin_list;
// 		*begin_list = node;
// 	}
// }

t_list	*generate_linked_list(void)
{
	t_list *begin = malloc(sizeof(t_list));
	int *content = malloc(sizeof(int));
	*content = 0;
	begin->data = (void*)content;

	t_list *node = malloc(sizeof(t_list));
	content = malloc(sizeof(int));
	*content = 1;
	node->data = content;

	begin->next = node;

	t_list *node_second = malloc(sizeof(t_list));
	content = malloc(sizeof(int));
	*content = 2;
	node_second->data = content;
	node_second->next = NULL;

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
			printf("%d\n", *(int*)(current->data));
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

t_list	*generate_node(int number)
{
	t_list *node = malloc(sizeof(t_list));
	int *data = malloc(sizeof(int));

	*data = number;
	node->data = data;
	node->next = NULL;
	return node;
}