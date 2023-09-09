#include <stdio.h>

size_t ft_strlen(const char *str); // link with asm library so the function exist.

int main(void)
{
	printf("%d\n", ft_strlen("Bozo"));
	return 0;
}