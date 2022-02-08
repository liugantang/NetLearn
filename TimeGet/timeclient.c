#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("hello client\n");
	for (;;)
	{
		sleep(1);
		printf("client is running\n");
	}
	return 0;
}
