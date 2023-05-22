#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab9fun.c"

int main()
{
	FILE* ptr = fopen("input9.txt", "r");
	int num;
	int i = 0;
	int avg;
	int sum = 0;

	if (NULL == ptr)
	{
		printf("file no open \n");
		return 0;
	}
	printf("The values read from the file are: \n\n");
	fseek(ptr, 0, SEEK_END);
	if (ftell(ptr) == 0)
	{
		fclose(ptr);
		avg = average(sum, i);
		printf("\nThe average is: %d ", avg);
		return 0;
	}
	fseek(ptr, 0, SEEK_SET);
	while (!feof(ptr))
	{
		i = i + 1;
		fscanf(ptr, "%d", &num);
		printf("%d: ", i);
		printf("%d \n", num);
		sum = sum + num;
	}
	fclose(ptr);
	avg = average(sum, i);

	printf("\nThe average is: %d ", avg);
	return 0;
}