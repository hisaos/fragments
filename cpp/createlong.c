#include<stdio.h>
#include<stdlib.h>

int main() {

  int i;
  FILE* fwp;

  fwp = fopen("longdata.txt","w");

  for(i=0; i<1000; i++)
    fprintf(fwp, "%d %d %d %d %d %d %d %d %d %d\n",rand() ,rand() ,rand() ,rand() ,rand() ,rand() ,rand() ,rand() ,rand() ,rand());

  fclose(fwp);

  return 0;

}