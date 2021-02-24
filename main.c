#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
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

int cmp(int a, int b) // comparation #4 |a| <= |b|
{
  return (abs(a) <= abs(b));
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
      a[i] = n - i;
    return;
  }
  
  if (arg == 2)//reversed sorted
  {
    for (int i = 0; i < n; i++)
      a[i] = i;
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
      compares++;
      if (cmp(arr[j], arr[j+1]) == 0) // |arr[j]| > |arr[j+1]| 
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

void sort4(int *arr, int left, int right) //qsort
{
  int i = left, j = right;
  int pivot = arr[(left + right)/2];

  while (i <= j)
  {
    while (arr[i] < pivot) i++;
      while (arr[j] > pivot) j--;
        if (i <= j)
        {
          compares++;
          if (arr[i] > arr[j])
            swap(&arr[i], &arr[j]);
    
          i++;
          j--;
        }
  }

  if (left < j)
    sort4(arr, left, j);
  if (i < right)
    sort4(arr, i, right);
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
  
  // printf("%d %d %d", cmp(1, 0), cmp(-2, 3), cmp(3, -3));
  
  bubbleSort(a, n);
  printf("%d %d\n", compares, swaps); // bubbleSort results
  
  // for (int i = 0; i < n; i++)
  // {
  //   printf("%d ", a[i]);
  // }
  // printf("\n");
  
  
  compares = 0;
  swaps = 0;
  
  sort4(b, 0, n);
  printf("%d %d\n", compares, swaps); //  sort4 results
  
  // for (int i = 0; i < n; i++)
  // {
  //   printf("%d ", a[i]);
  // }
  // printf("\n");
  
  return 0;
}