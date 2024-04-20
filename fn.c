#include <stdio.h>
#include <stdlib.h>

/*********************************************************/
// int *p, *d
// A[3] - объявление массива с 3 элементами
// p = A - указатель на массив А
//
// B[1][3] - объявление двумерного массива с размерами 1 строка 3 столбца
// d = B[0] - присвоение указателя на первую строку двумерного массива
//
//
//
//

/*********************************************************/
// printf("%d", A[0][0]);
int main()
{

    int A[1][3] = {1, 2, 3};
    int *p = A[0];
    int *d = &A[0][0];
    if (p == d)
    {
        printf("YEAHS");
    }
    else
    {
        printf("\nNOOPE");
    }
    if (*(p + 3) == *(A + 3))
    {
        printf("\nYEAHS2");
    }
    else
    {
        printf("\nNOOPE2");
    }

    return 0;
}