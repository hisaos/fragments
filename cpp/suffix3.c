/*添字配列を構成するプログラムの未完成版*/
/*接尾辞の先頭ポインタを動的に確保した配列へと順番に格納する機能のみ*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void datain(int *num);
void copy(char *text);

typedef struct {	/*この構造体は動的にポインタ配列を確保するために必要*/
  char *text;
}SUFF;  

int main() {
  
  int i;		/*int型カウント変数*/
  int num = 0;		/*文字数を保持する*/
  char *text;		/*動的に確保される配列textに読み込んだテキストの本体が入る*/
  SUFF *suff;		/*ポインタ配列はtext内で各接尾辞の先頭を指す*/

  datain(&num);		/*動的に確保する配列のサイズを決定するためにテキストの文字数を数え上げる。*/

  text = (char *)malloc(num);	/*配列textを確保*/
  copy(text);			/*textに読み込んだ文字列を格納する*/

  suff = (SUFF *)malloc(num);	/*ポインタ配列suffを確保*/

  for(i = 0; i <= num; i++)	/*suffの各要素に接尾辞の先頭のアドレスを格納*/
    suff[i].text = (text+i);

  return 0;
}

void datain(int *num) {

  FILE* frp;		/*データファイルポインタ*/
  char line[80];	/*fgetsでファイルから読んでくるときに、行を格納するバッファ*/
  int i;		/*ファイルの文字数を数えるループで使うカウンタ。*/
  char *str;		/*ファイルの文字数を数えるループで使う読み込んだ行をさすポインタ。*/

  frp = fopen("testtxt.txt", "r");	/*データファイルを読み出しモードで開く*/

/*ファイルの終わりに達するまでループ*/
  while(fgets(line, sizeof(line), frp) != NULL) {
    str = line;
    for(i = 0; str[i]; i++)
      if(str[i] != '\n' && str[i] != ' ') (*num)++;
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

