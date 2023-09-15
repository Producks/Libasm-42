NAME = libasm.a
SRCS = $(wildcard *.s)
OBJS = $(SRCS:.s=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.s
	nasm -felf64 $<

clean:
	@rm -f $(OBJS)

fclean:clean
	@rm -f $(NAME)

bonus:all

re:fclean all

.PHONY: all clean fclean re