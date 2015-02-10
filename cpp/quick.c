#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INDEX 50
#define MAX_VALUE 9999
#define MIN_VALUE 0

void indata(int array[], int array_len[], int *index);
int quick_sort(int array[], int array_len[], int left, int right, int index);
void outdata(int array[], int array_len[], int index);

int main(void) {

  int array[MAX_INDEX];
  int array_len[MAX_INDEX];
  int index = 0;

  indata(array, array_len, &index);
  printf("%d\n",index);
  quick_sort(array, array_len, 0, index, index);
  outdata(array, array_len, index);

  return 0;
}

void indata(int array[], int array_len[], int *index) {

  int data = 0;
  int flg = 0;
  char line[80];
  
  printf("データを入力してください。\n");
  printf("データはひとつずつ、入力の度にEnterを。\n");
  printf("データ入力終了時は、-1を入力してください。\n");

  while(flg != 1) {

  fgets(line, sizeof(line), stdin);
  array_len[*index] = strlen(line);

  if(atoi(line) == 0) {
    printf("invalid input: %s\n", line);
    continue;
  }

  if (sscanf(line, "%d", &data) == 1) {
 
    if(data == -1) {
      printf("end of data.\n");
      array[*index] = 0;
      (*index)--;
      break;
    }

    else if(data < MIN_VALUE || data > MAX_VALUE) {
      printf("invalid input: %d\n", data);
      continue;
    }

    else {
      array[*index] = data;
    }
  }
   
    if(*index >= MAX_INDEX - 1) {
      printf("too many digits.\n");
      flg++;
    }
    else 
      (*index)++;

  }
}

int quick_sort(int array[], int array_len[], int left, int right, int index) {

  int flg = 0;
  int pivot, temp, temp_len;
  int left_edge = left;
  int right_edge = right;

  pivot = (array[left] + array[left + 1]) / 2;

  while(left < right) {
    
    printf("left: %d, right: %d\n",left, right);
    outdata(array, array_len, index);

    if(array[left] >= pivot && array[right] < pivot) {

      flg = 1;

      temp = array[left];
      array[left] = array[right];
      array[right] = temp;

      temp_len = array_len[left];
      array_len[left] = array_len[right];
      array_len[right] = temp_len;

      left++;
      right--;
    }

    else if(array[left] < pivot)
      left++;
    
    else if(array[right] >= pivot)
      right--;

    }

  printf("pivot: %d, left: %d, right: %d\n",pivot ,left, right);

  if(flg) {
   quick_sort(array, array_len, left_edge, left, index);
   quick_sort(array, array_len, left + 1, right_edge, index);
  }

  return 0;
}

void outdata(int array[], int array_len[], int index) {

  int lcount;
  int tcount;
    
  for(lcount = 0; lcount <= index; lcount++) {
    for(tcount = 0; tcount <= 5 - array_len[lcount]; tcount++)
      printf("\x20");

    printf("%d ", array[lcount]);
    
    if(lcount % 10 == 9) 
      printf("\n");
  }
  printf("\n");

}


