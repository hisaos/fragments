#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INDEX 50
#define MAX_VALUE 9999
#define MIN_VALUE 0

void indata(int *n, int *p);

/*
int sort(int array, int max_index);
int outdata(int array, int count);
*/
int main() {

  int n;
  int p;
  int i;

  indata(&n, &p);
/*
  sort(array, n);
  outdata(array, n);
*/
  printf("%d\n", p);
  printf("%d\n", n);

  for(i=0; i<=n; i++) {
    printf("%d ", p);
    if(i % 10 == 9)
      printf("\n");
    
  }

  return 0;
}

void indata(int *n, int *p) {

  int data = 0;
  int i,j;
  int index = 0;
  int flg = 0;
  int array[MAX_INDEX];
  char line[80];
  
  for(i=0; i<=MAX_INDEX; i++)
    array[i] = 0;

  while(flg != 1) {

  fgets(line, sizeof(line), stdin);
  
  if (sscanf(line, "%d", &data) == 1) {
    if(data >= MIN_VALUE && data <= MAX_VALUE) {
      array[index] = data;
      printf(".%d\n", array[index]);
    }

    else if(data == -1) {
      printf("end of data.\n");
      array[index] = 0;
      index--;
      break;
    }

    else {
      printf("invalid input: %d\n", data);
      continue;
    }
  }

    if(index >= MAX_INDEX - 1) {
      printf("too many digits.\n");
      flg++;
    }

    else 
      index++;
  }

  *n = index;
  p = array;
  printf("%p\n", &p);

  for(j=0; j<=index; j++) {
    printf("%d ", p[j]);
    if(j % 10 == 9)
      printf("\n");
    
  }

}