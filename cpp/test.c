#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
  
  int i,j;
  char text[10];
  char *suff[10];

  strcpy(text,"bababacaba");

  for(i = 0; i < 10; i++) {
    suff[i] = &(text[i]);
    /*printf("%p\n",suff[i]);*/
  }

  for(j = 0; j < 10; j++) {
    for(i = j; i < 10; i++) {
      printf("%c",*(suff[i]));
    }
    printf("\n");
  }

  return 0;
}
