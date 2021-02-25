#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int compares = 0, swaps = 0;

union 
{
  int i;
  unsigned char uc[sizeof (int)];
} u;

void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
  swaps++;
}

int cmp(int a, int b) // comparation #4 |a| > |b|
{
  compares++;
  if ((a == INT_MIN) && (b == INT_MIN))
    return 0;
  
  if (a == INT_MIN)
    return 1;
  
  if (b == INT_MIN)
    return 0;
  
  return (abs(a) > abs(b));
}

int rand_int(void)
{
  for (int i = 0; i < sizeof u.uc; i++)
    u.uc[i] = rand();
  
  return u.i;
}

void gen_arr(int *a, int n, int arg)
{                                   
  if (arg == 1) //sorted
  {
    for (int i = 0; i < n; i++)
      a[i] = i;
    return;
  }
  
  if (arg == 2) //reversed sorted
  {
    for (int i = 0; i < n; i++)
      a[i] = n - i;
      return;
  }
  
  for (int i = 0; i < n; i++) //random
    a[i] = rand_int();
}

void bubbleSort(int *arr, int n) 
{ 
  int swapped = 1; 
  for (int i = 0; i < n - 1; i++)
  { 
    swapped = 0; 
    for (int j = 0; j < n - i - 1; j++) 
    { 
      if (cmp(arr[j], arr[j+1])) // |arr[j]| > |arr[j+1]| 
      {
        swap(&arr[j], &arr[j+1]); 
        swapped = 1; 
      }
    } 

    // array is sorted
    if (swapped == 0) 
    break; 
  } 
} 

void quick_sort(int *arr, int left, int right) //qsort
{
  int i = left, j = right;
  int pivot = arr[(left + right)/2];

  while (i <= j)
  {
    while ((arr[i] != pivot) && !cmp(arr[i], pivot))
      i++;
    while ((arr[j] != pivot) && cmp(arr[j], pivot))
      j--;
    if (i <= j)
    {
      if (cmp(arr[i], arr[j]))
        swap(&arr[i], &arr[j]);

      i++;
      j--;
    }
  }

  if (left < j)
    quick_sort(arr, left, j);
  if (i < right)
    quick_sort(arr, i, right);
}

void check(int *a, int n) // check if sorted correctly
{
  for (int i = 0; i < n - 1; i++)
    if (cmp(a[i], a[i + 1]))
    {
      printf("sorted incorrectly\n");
      return;
    }
  printf("sorted correctly\n");
}


int main(void)
{
  srand(time(NULL));
  int n, arg;
  scanf("%d%d", &n, &arg); // scanf size and type of array
  
  int *a = (int*)calloc(n, sizeof(int));
  int *b = (int*)calloc(n, sizeof(int));
  
  gen_arr(a, n, arg);
  for (int i = 0; i < n; i++)
  {
    // printf("%d ", a[i]);
    b[i] = a[i];
  }
  // printf("\n");
  
  bubbleSort(a, n);
  printf("\n%d %d\n", compares, swaps); // bubbleSort results
  check(a, n);
  
  // for (int i = 0; i < n; i++)
  // {
  //   printf("%d ", a[i]);
  // }
  // printf("\n");
  
  
  compares = 0;
  swaps = 0;
  
  quick_sort(b, 0, n - 1);
  printf("%d %d\n", compares, swaps); //  quick_sort results
  check(b, n);
  
  // for (int i = 0; i < n; i++)
  // {
  //   printf("%d ", b[i]);
  // }
  // printf("\n");
  
  free(a);
  free(b);
  
  return 0;
}