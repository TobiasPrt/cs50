#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int rows = get_int("Height: ");
    int cols = 1;
    
    do
    {
    	for (int i = 0; i < rows-cols; ++i)
    	{
    		printf(".");
    	}

    	for (int i = 0; i < cols; ++i)
    	{
    		printf("#");
    	}

    	printf("..");

    	for (int i = 0; i < cols; ++i)
    	{
    		printf("#");
    	}
    	
    	printf("\n");
    	++cols;
    }
    while(cols < rows);

    printf("\n");
}