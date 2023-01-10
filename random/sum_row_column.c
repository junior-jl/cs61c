#include <stdio.h>

void sum_rows_columns(int arr[5][5])
{
	int row_total = 0, column_total = 0;
	for (int i = 0; i < 5; i++)
	{
		row_total = 0, column_total = 0;
		for (int j = 0; j < 5; j++)
		{
			row_total += arr[i][j];
			column_total += arr[j][i];
		}
		printf("%d\t%d\n", row_total, column_total);
		
	}
}

int main(void)
{
	int test_array[5][5] = {{8,3,9,0,10}, {3,5,17,1,1}, {2,8,6,23,1}, {15,7,3,2,9}, {6,14,2,6,0}};
	printf("Row \tColumn \n");
	sum_rows_columns(test_array);
}