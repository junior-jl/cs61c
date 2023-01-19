#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{
	//char mystr[10] = {'H', 'i', '\0', '1', '3', '!', 'a', 'x', '#', ' '};
	char mystr[10] = "Hello\0!ax";
	int n = 10;
	int i;
	for (i = 0; i < n; i++)
		printf("%c", *(mystr + i));
	printf("\n");	
	for (i = 0; i < strlen(mystr); i++)
    	(*(mystr + i))++;
	for (i = 0; i < n; i++)
		printf("%c", *(mystr + i));
	return 0;
}