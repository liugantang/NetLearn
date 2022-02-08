#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("hello server!\n");
	for (;;)
	{
		sleep(1);
		printf("server is running\n");
	}
	return 0;
}