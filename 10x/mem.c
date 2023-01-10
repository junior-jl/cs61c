
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   unsigned long long dword[2];
} array_t __attribute__ ((aligned (16) ));

const int size = 8;

void store_byte(array_t arr[size], unsigned long long values[size])
{
    for (int i = 0; i < size; i++)
    {
            arr[i].dword[0] = (values[i] << (i * 8));
            arr[i].dword[1] = (values[i] >> (i == 0 ? 63 : 64 - i * 8)); // Resolver aviso do compilador
    }
}

#define store_word store_byte
#define store_hword store_byte
#define store_dword store_byte
/* Obsolete... Only one function needed

void store_byte(array_t arr[size], unsigned long long values[size])
{
    for (int i = 0; i < size; i++)
    {
        arr[i].dword[0] = (values[i] << (i * 8));
    }
}

void store_hword(array_t arr[size], unsigned long long values[size])
{
    for (int i = 0; i < size; i++)
    {
            arr[i].dword[0] = (values[i] << (i * 8));
            arr[i].dword[1] = (values[i] >> (i == 0 ? 63 : 64 - i * 8)); // Resolver aviso do compilador
    }
}

void store_word(array_t arr[size], unsigned long long values[size])
{
    for (int i = 0; i < size; i++)
    {
            arr[i].dword[0] = (values[i] << (i * 8));
            arr[i].dword[1] = (values[i] >> (i == 0 ? 63 : 64 - i * 8)); // Resolver aviso do compilador
    }
}

void store_dword(array_t arr[size], unsigned long long values[size])
{
    for (int i = 0; i < size; i++)
    {
            arr[i].dword[0] = (values[i] << (i * 8));
            arr[i].dword[1] = (values[i] >> (i == 0 ? 63 : 64 - i * 8)); // Resolver aviso do compilador
    }
}

*/

array_t sb_data[8] =
       {
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 }
       };


array_t sb_expected_data[8] =
       {    // dword0              dword1
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000004200, 0x0000000000000000 },
          { 0x0000000000550000, 0x0000000000000000 },
          { 0x000000007F000000, 0x0000000000000000 },
          { 0x000000FF00000000, 0x0000000000000000 },
          { 0x0000D30000000000, 0x0000000000000000 },
          { 0x0096000000000000, 0x0000000000000000 },
          { 0x8100000000000000, 0x0000000000000000 }
       };


array_t sh_data[8] =
       {
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 }
       };


array_t sh_expected_data[8] =
       {
          { 0x0000000000007FFF, 0x0000000000000000 },
          { 0x000000000077F000, 0x0000000000000000 },
          { 0x000000006FE10000, 0x0000000000000000 },
          { 0x00000067D2000000, 0x0000000000000000 },
          { 0x0000800000000000, 0x0000000000000000 },
          { 0x00880F0000000000, 0x0000000000000000 },
          { 0x901E000000000000, 0x0000000000000000 },
          { 0x2D00000000000000, 0x0000000000000098 }
       };


array_t sw_data[8] =
       {
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 }
       };



array_t sw_expected_data[8] =
       {
          { 0x0000000089ABCDEF, 0x0000000000000000 },
          { 0x00000089ABCDEF00, 0x0000000000000000 },
          { 0x000089ABCDEF0000, 0x0000000000000000 },
          { 0x0089ABCDEF000000, 0x0000000000000000 },
          { 0x0123456700000000, 0x0000000000000000 },
          { 0x2345670000000000, 0x0000000000000001 },
          { 0x4567000000000000, 0x0000000000000123 },
          { 0x6700000000000000, 0x0000000000012345 }
       };


array_t sd_data[8] =
       {
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 },
          { 0x0000000000000000, 0x0000000000000000 }
       };


array_t sd_expected_data[8] =
       {
          { 0x08192A3B4C5D6E7F, 0x0000000000000000 },
          { 0x192A3B4C5D6E7F00, 0x0000000000000008 },
          { 0x2A3B4C5D6E7F0000, 0x0000000000000819 },
          { 0x3B4C5D6E7F000000, 0x000000000008192A },
          { 0x4C5D6E7F00000000, 0x0000000008192A3B },
          { 0x5D6E7F0000000000, 0x00000008192A3B4C },
          { 0x6E7F000000000000, 0x000008192A3B4C5D },
          { 0x7F00000000000000, 0x0008192A3B4C5D6E }
       };


void print_array_t(array_t arr[size])
{
    for (int i = 0; i < size; i++)
    {
        printf("%.16llX , %.16llX\n", arr[i].dword[0], arr[i].dword[1]);
    }
}

//int compare_array_t(array_t arr1[size], array_t arr2);
int test_store_byte ( ) {

// 00, 42, 55, 7f, FF, D3, 96, 81
unsigned long long arr_teste[] = {0x00, 0x42, 0x55, 0x7f, 0xFF, 0xD3, 0x96, 0x81};
store_byte(sb_data, arr_teste);
size_t s = sizeof(sb_expected_data)/sizeof(sb_expected_data[0]);
printf("Expected Array:\n\n");
print_array_t(sb_expected_data);
printf("Modified Array\n\n");
print_array_t(sb_data);
return memcmp(sb_data, sb_expected_data, s);

}

 // test_store_byte


int test_store_hword ( ) {

// 7fff, 77f0, 6fe1, 67d2, 8000, 880f, 901E, 982D
unsigned long long arr_teste[] = {0x7fff, 0x77f0, 0x6fe1, 0x67d2, 0x8000, 0x880f, 0x901E, 0x982D};
store_hword(sh_data, arr_teste);
size_t s = sizeof(sh_expected_data)/sizeof(sh_expected_data[0]);
printf("Expected Array:\n\n");
print_array_t(sh_expected_data);
printf("Modified Array\n\n");
print_array_t(sh_data);
return memcmp(sh_data, sh_expected_data, s);

} // test_store_hword


int test_store_word ( ) {

// 89ABCDEF, 01234567
unsigned long long arr_teste[] = {0x89ABCDEF, 0x89ABCDEF, 0x89ABCDEF, 0x89ABCDEF, 0x01234567, 0x01234567, 0x01234567, 0x01234567};
store_word(sw_data, arr_teste);
size_t s = sizeof(sw_expected_data)/sizeof(sw_expected_data[0]);
printf("Expected Array:\n\n");
print_array_t(sw_expected_data);
printf("Modified Array\n\n");
print_array_t(sw_data);
return memcmp(sw_data, sw_expected_data, s);

} // test_store_word


int test_store_dword ( ) {

// 08192A3B4C5D6E7F
unsigned long long arr_teste[] = {0x08192A3B4C5D6E7F, 0x08192A3B4C5D6E7F, 0x08192A3B4C5D6E7F, 0x08192A3B4C5D6E7F, 0x08192A3B4C5D6E7F, 0x08192A3B4C5D6E7F, 0x08192A3B4C5D6E7F, 0x08192A3B4C5D6E7F};
store_dword(sd_data, arr_teste);
size_t s = sizeof(sd_expected_data)/sizeof(sd_expected_data[0]);
printf("Expected Array:\n\n");
print_array_t(sd_expected_data);
printf("Modified Array\n\n");
print_array_t(sd_data);
return memcmp(sd_data, sd_expected_data, s);

} // test_store_dword

// ===================
// Main function
// ===================

int main() {
    printf("\nStore byte test (RETURN): %d\n", test_store_byte());
    printf("\nStore hword test (RETURN): %d\n", test_store_hword());
    printf("\nStore word test (RETURN): %d\n", test_store_word());
    printf("\nStore dword test (RETURN): %d\n", test_store_dword());
} // main

