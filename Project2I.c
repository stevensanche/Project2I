#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int *AllocateArray(int N)
{
    int *i = (int*)malloc(N * sizeof(int));
    for (int j = 0; j < N; j++) {
        i[j] = rand() % (10 * N);

    }
    return i;
    /* Allocate an array with N integers.
     * The value of each element of the array should be a
     * random number between 0 and 10N.
     * Hint: use the rand() function and a modulo operator.
     */
}

int compare(const void *i, const void *j) {
    int numOne = *(const int*)i;
    int numTwo = *(const int*)j;

    if (numOne > numTwo) return 1;
    if (numOne < numTwo) return -1;
    else return 0;

    // you could also do //
    // return (*(const int*)i - *(const int*)j); //
} 

void SortArray(int *A, int N)

{
    qsort(A, N, sizeof(int), compare);
}


void DeallocateArray(int *A)
{
    free(A);
}


int main()
{
    int sizes[8] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 };

/* For fun:
 *  int sizes[11] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000,
 *                    256000, 512000, 1024000 }; 
 */

    for (int i = 0 ; i < 8 ; i++)
    {
        double alloc_time = 0., sort_time = 0., dealloc_time = 0.;
        struct timeval startTime;
        struct timeval endTime;

        gettimeofday(&startTime, 0);
        int *arr = AllocateArray(sizes[i]);
        gettimeofday(&endTime, 0);
        alloc_time = (double)(endTime.tv_sec - startTime.tv_sec) + (double)((endTime.tv_usec - startTime.tv_usec) / 1000000.);

        gettimeofday(&startTime, 0);
        SortArray(arr, sizes[i]);
        gettimeofday(&endTime, 0);
        sort_time = (double)(endTime.tv_sec - startTime.tv_sec) + (double)((endTime.tv_usec - startTime.tv_usec) / 1000000.);

        gettimeofday(&startTime, 0);
        gettimeofday(&endTime, 0);
        DeallocateArray(arr);
        dealloc_time = (double)(endTime.tv_sec - startTime.tv_sec) + (double)((endTime.tv_usec - startTime.tv_usec) / 1000000.);


        /* Call the three functions in a sequence. Also use
         * gettimeofday calls surrounding each function and set the 
         * corresponding variable (alloc_time, sort_time, dealloc_time).
         */

        printf("Timings for array of size %d\n", sizes[i]);
        printf("\tTime for allocation is %g, time per element = %g\n", alloc_time, alloc_time/sizes[i]);
        printf("\tTime for sort_time is %g, time per element = %g\n", sort_time, sort_time/sizes[i]);
        printf("\tTime for deallocation is %g\n", dealloc_time);
    }
}
