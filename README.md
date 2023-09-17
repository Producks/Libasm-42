# Libasm-42
This project is an x86-64 assembly [NASM](https://www.nasm.us/) for the 42 school which is part of the specialization circle.
### Description
The project ask us to make a variety of functions to compile a library in 64 bits assembler.  
The functions must follow these rules:
- It need to be in 64 bits ASM
- It need to follow the calling convention
- It can't be inline ASM
- Our library need to compile with [NASM](https://www.nasm.us/)
- It need to use the Intel syntax, not the AT&T
### Mandatory Functions
- strlen `size_t ft_strlen(const char *s);`
- strcpy `char *ft_strcpy(char *dest, const char *src);`
- strcmp `int ft_strcmp(const char *s1, const char *s2);`
- write `size_t ft_write(int fd, const void *buf, size_t count);`
- read `size_t ft_read(int fd, void *buf, size_t count);`
- strdup  `char *ft_strdup(const char *s);`
### Bonus Functions
The list functions use this structure for the linked list
```
typedef struct s_list
{
	void	*data;
	struct s_list	*next;
} t_list;
```
- atoi_base `int ft_atoi_base(char *str, char *base);`
- list_push_front `void ft_list_push_front(t_list **begin_list, void *data);`
- list_size `int ft_list_size(t_list *begin_list);`
- list_sort `void ft_list_sort(t_list **begin_list, int (*cmp)());`
- list_remove_if `t_list *ft_list_remove_if(t_list**begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));`
### Useful resources
[Cheat sheet](https://ggbaker.ca/295/x86.html)  
[List of syscall on linux](https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/)  
[NASM resources](https://cs.lmu.edu/~ray/notes/nasmtutorial/)
