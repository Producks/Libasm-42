#include <stdio.h>
#include <errno.h>

size_t _ft_write(int fd, const void *buf, size_t count); // link with asm library so the function exist.
size_t _ft_strlen(const char *s);


void	test_strlen();
void	test_write();

int main(void)
{
	int ret = _ft_write(1, NULL, 6);
	perror("BOZO");
	printf("%d\n", ret);
	// printf("%ld\n", _ft_strlen("BOZO"));
	// printf("%ld\n", _ft_strlen(NULL));
	return 0;
}