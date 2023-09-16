NAME = libasm.a
BONUS_NAME = libasm.a
SRCS = 	ft_strlen.s \
		ft_strcpy.s \
		ft_strcmp.s \
		ft_write.s	\
		ft_read.s	\
		ft_strdup.s
SRCS_BONUS = ft_atoi_base_bonus.s \
			 ft_list_push_front_bonus.s \
			 ft_list_size_bonus.s \
			 ft_list_sort_bonus.s \
			 ft_list_remove_if_bonus.s
OBJS = $(SRCS:.s=.o)
BONUS_OBJS = $(SRCS_BONUS:.s=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^
	gcc -Wall -Werror -Wextra main.c libasm.a

dumb: $(OBJS) $(BONUS_OBJS)
	ar rcs libasm.a $^
	gcc -D BONUS_FLAG=1 -Wall -Werror -Wextra main.c libasm.a

%.o: %.s
	nasm -felf64 $<

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean:clean
	@rm -f $(NAME) $(BONUS_NAME)

bonus: dumb

re:fclean all

.PHONY: all clean fclean re bonus