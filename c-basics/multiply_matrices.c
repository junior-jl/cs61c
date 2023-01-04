/* Program to multiply matrices */
#include <stdio.h>



int main(void)
{
	printf("Enter the number of rows and columns of matrix A: ");
	int rows_a, columns_a;
	scanf("%d %d", &rows_a, &columns_a);
	printf("Enter the number of rows and columns of matrix B: ");
	int rows_b, columns_b;
	scanf("%d %d", &rows_b, &columns_b);
	if (columns_a != rows_b)
	{
		printf("Impossible to multiply.");
		return 1;
	}
	int matrix_a[rows_a][columns_a];
	int matrix_b[rows_b][columns_b];
	int matrix_result[rows_a][columns_b];
	
	int i, j;
	printf("Insira a matriz A:\n");
	for (i = 0; i < rows_a; i++)
	{
		for (j = 0; j < columns_a; j++)
		{
			printf("\nElement [%d][%d]: ", i+1, j+1);
			scanf("%d", &matrix_a[i][j]);
		}
	}
	printf("Insira a matriz B:\n");
	for (i = 0; i < rows_b; i++)
	{
		for (j = 0; j < columns_b; j++)
		{
			printf("\nElement [%d][%d]: ", i+1, j+1);
			scanf("%d", &matrix_b[i][j]);
		}
	}
	int aux = 0, result;
	for (i = 0; i < rows_a; aux == rows_a ? i++, aux = 0 : i)
	{
		result = 0;
		for (j = 0; j < columns_a; j++)
		{
			result += matrix_a[i][j]*matrix_b[j][aux];
		}
		matrix_result[i][aux] = result;
		++aux;
	}
	printf("Resultant Matrix: \n");
	for (i = 0; i < rows_a; i++)
	{
		for (j = 0; j < columns_b; j++)
		{
			printf("%d ", matrix_result[i][j]);
			
		}
		printf("\n");
	}
	return 0;
}