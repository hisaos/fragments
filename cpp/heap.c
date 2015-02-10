#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INDEX 50
#define MAX_VALUE 9999
#define MIN_VALUE 0

void heap_sort(int array[], int index);
void delete_max(int array[], int index);
void insert(int array[], int* index);
void outdata(int array[], int index);

int main() {

  int array[MAX_INDEX];
  int index = 0;  
  
    insert(array, &index);
    heap_sort(array, index);
    outdata(array, index);

    return 0;
}

void insert(int array[], int* index) {

  int temp;
  int count;
  int digit;
  int cursor;
  char buff[80];

  while(1) {

    fgets(buff, sizeof(buff), stdin);
    
    if(sscanf(buff, "%d") == 0) {
      printf("invalid input: %s\n", buff);
      continue;
    }

    digit = atoi(buff);
    
    if(digit == -1) {
      printf("end of input.\n");
      (*index)--;
      break;
    }

    if(digit < MIN_VALUE || digit > MAX_VALUE) {
      printf("invalid input: %d\n", digit);
      continue;
    }
    
    array[*index] = digit;
    cursor = (*index);
    
    while(array[cursor] > array[(cursor -1) / 2] && cursor > 0) {
    
      temp = array[cursor];
      array[cursor] = array[(cursor -1) / 2];
      array[(cursor -1) / 2] = temp;
      
      cursor = (cursor -1) / 2;
    }

    (*index)++;

    if(*index == MAX_VALUE) {
      printf("too many digits.\n");
      break;
    }
  }  
  outdata(array, *index);
}    

void deletemax(int array[], int index) {

  int temp;
  int s;
  int cursor;

  temp = array[0];
  array[0] = array[index];
  array[index] = temp;

  cursor = 0;

  while(1) {

    if(2*cursor +1> index -1)
      break;
    
    for(s = 1; s <= 2; s++) {
      if(array[cursor] < array[2*cursor +s] && 2*cursor +s > index -1) {
	printf("check: %d", s);
	temp = array[cursor];
	array[cursor] = array[2*cursor +s];
	array[2*cursor +s] = temp;
	
	cursor = 2*cursor +s;
	continue;
      } 
    }
  }
}

void heap_sort(int array[], int index) {

  int cursor;

  for(cursor = index; cursor >= 0; cursor--) {
    deletemax(array, cursor);
  }
}

void outdata(int array[], int index) {

  int count;

  for(count = 0; count <= index; count++) {

    printf("%d ", array[count]);

    if(count % 10 == 9)
      printf("\n");
  }
}
