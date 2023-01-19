#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int arr[] = {34, 56, 54, 32, 67, 89, 90, 32, 21};
	int len_arr = sizeof(arr)/sizeof(int);
	printf("Array: ");
	for (int i = 0; i < len_arr; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\nReversed Order: ");
	for ( ; len_arr > 0; len_arr--) 
	{
		printf("%d ", arr[len_arr - 1]);
	}
	printf("\n");
	return 0;
}
