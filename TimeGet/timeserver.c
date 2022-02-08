#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("hello server!\n");
	for (;;)
	{
		sleep(1000);
		printf("server is running");
	}
	return 0;
}