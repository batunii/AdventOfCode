#include <stdio.h>
#include <string.h>
#include <strings.h>
int main(int argc, char *argv[])
{
	printf("Hello World");

	FILE *file_ptr;
	char str_buff[50];

	file_ptr = fopen("input4.txt", "r");

	while(fgets(str_buff, 50, file_ptr) != NULL)
	{
		printf("%s",str_buff);
	}

}
