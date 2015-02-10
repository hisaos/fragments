#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INDEX 10
#define MAX_VALUE 9999
#define MIN_VALUE 0

struct listcell {
  int data;
  struct listcell* next;
};

void first_list(struct listcell* ptr);
void print_list(struct listcell* ptr);
int data_in(void);
void insert(int digit, struct listcell *ptr);
void delete(int digit, struct listcell *ptr);

int main(void) {
  
  struct listcell* head;
  int digit;
  int i_count;

  head->next = (struct listcell *)malloc(sizeof(struct listcell));
  
  first_list(head->next);
  print_list(head->next);
  
  printf("次に新たに１０個の整数をリストに挿入します。\n");
  for(i_count = 0; i_count < 10; i_count++) {
    digit = data_in();
    insert(digit, head);
    print_list(head->next);
  }
  
  printf("次に１０種の数をリストから削除します。\n");
  for(i_count = 0; i_count < 10; i_count++) {
    digit = data_in();
    delete(digit, head);
    print_list(head->next);
  }

  return 0;
}

void first_list(struct listcell* ptr) {

  int index = 0;
  int flg = 0;
  
  printf("データを入力してください。\n");
  printf("データはひとつずつ、入力の度にEnterを。\n");
 
  while(flg != 1) {
    ptr->data = data_in();
    
    if(index >= MAX_INDEX - 1) {
      printf("入力終了。\n");
      ptr->next = NULL;
      flg++;
    }
    
    else { 
      ptr->next = (struct listcell *)malloc(sizeof(struct listcell));
      ptr = ptr->next;
      index++;
    }
  }
}

int data_in(void) {

  int digit;
  char line[80];

  while(-1) {
    fgets(line, sizeof(line), stdin);

    if(atoi(line) == 0) {
      printf("invalid input: %s\n", line);
      continue;
    }
    
    if(sscanf(line, "%d", &digit) == 1) {
      if(digit < MIN_VALUE || digit > MAX_VALUE) {
        printf("invalid input: %d\n", digit);
        continue;
      }
      else
	break;
    }
  }
  return digit;
}

void print_list(struct listcell* ptr) {

  while(ptr != NULL) {
    printf("%d ",ptr->data);
    ptr = ptr->next;
  }
  printf("\n");
}

void insert(int digit, struct listcell* ptr) {

  struct listcell* nextnext;

  while((ptr->next)->data - digit < 0) {
    ptr = ptr->next;
    if(ptr->next == NULL)
      break;
  }
 
  nextnext = ptr->next;
  ptr->next = (struct listcell *) malloc(sizeof(struct listcell));
  (ptr->next)->data = digit;
  (ptr->next)->next = nextnext;
}

void delete(int digit, struct listcell* ptr) {

  struct listcell* neonext;

  while(ptr->next != NULL) {
    while((ptr->next)->data == digit) {
      neonext = (ptr->next)->next;
      free(ptr->next);
      ptr->next = neonext;
      
      if(ptr->next == NULL)
	break;
    }
    if(ptr->next == NULL)
      break;
    else
      ptr = ptr->next;
  }
}

