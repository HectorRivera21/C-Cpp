#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE* ptr = fopen("randomInts.txt", "r");
    int num;

    if (NULL == ptr)
	{
		printf("file no open \n");
		return 0;
	}
    while(!feof(ptr))
    {
        fscanf(ptr,"%d",&num);
        if(num > 0)
        {
            printf("%d is Positive\n", num);
        }
        else if(num == 0)
        {   
            printf("%d is Neutral\n", num);
        }
        else if(num<0){
            printf("%d is Negative\n", num);
        }
        
    }
    fclose(ptr);
    return 0;
}