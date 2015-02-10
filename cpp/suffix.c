#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void datain(int *num);
void copy(char *text);



int main() {
  
  int i,j;
  int num = 0;
  char *text;
  FILE *fwp;

  datain(&num);
  printf("\n number of letters: %d\n" ,num);
 
  text = (char *)malloc(num);

  copy(text);

  fwp = fopen("testtxt.txt","w");
  
  for(j = 0; j <= num; j++) {
    for(i = j; *(text+i); i++)
      fprintf(fwp,"%c",*(text+i));
    fprintf(fwp,"\n");
  }

  return 0;
}

void datain(int *num) {

  FILE* frp;		/*データファイルポインタ*/
  char line[80];	/*fgetsでファイルから読んでくるときに、行を格納するバッファ*/
  int i;		/*ファイルの文字数を数えるループで使うカウンタ。*/
  char *str;		/*ファイルの文字数を数えるループで使う読み込んだ行をさすポインタ。*/

  frp = fopen("esslf10.txt", "r");	/*データファイルを読み出しモードで開く*/

/*ファイルの終わりに達するまでループ*/
  while(fgets(line, sizeof(line), frp) != NULL) {
    str = line;
    for(i = 0; str[i]; i++)
      (*num)++;
  }
  fclose(frp);	/*読み尽くしたらファイルを閉じる*/
}

void copy(char *text) {

  FILE* frp;		/*データファイルポインタ*/
  char line[80];	/*fgetsでファイルから読んでくるときに、行を格納するバッファ*/
  int i;		/*ファイルの文字数を数えるループで使うカウンタ。*/
  char *str;		/*ファイルの文字数を数えるループで使う読み込んだ行をさすポインタ。*/

  frp = fopen("testtxt.txt", "r");	/*読み出しモードで開く*/

/*ファイルの終わりに達するまでループ*/
  while(fgets(line, sizeof(line), frp) != NULL) {
    str = line;
    for(i = 0; str[i]; i++) {
      if(str[i] != '\n' && str[i] != ' ') {
        *(text) = str[i];
        text++;
      }
    }
  }
  fclose(frp);	/*読み尽くしたらファイルを閉じる*/
}

