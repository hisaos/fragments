/*基数ソート及び共通文字数の測定、特定のＮ字列が何回現れるかを求める*/
/*ファイルから読み込んだデータをスペース、タブ、改行文字のどれかで区切って*/
/*単語単位とし、ソートを行う形式になっている*/
/*文字定数GRAMを変更することで1-gram,2-gram,3-gramをそれぞれ求められる*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N 1000
#define GRAM 3

void radixsort(int n ,int length ,unsigned char *a[] ,unsigned char *work[]);
void cmnnum(int n, int c_arr[], unsigned char *p_let[]);
void cntnum(int n, int c_arr[], unsigned char *p_let[]);

int main() {

  int i, n;		/*カウンタ変数*/
  int c_arr[N];		/*共通文字数表を格納する配列*/
  static unsigned char *p_let[N], *work[N], let[N][256];
  /*p_letは各単語の格納されているアドレスを指すポインタ、workはソートモジュール内で使う作業領域、
  letへ実際に各単語が格納される。格納できる単語は255字以内のものを１０００個まで。*/

  for (n = 0; n < N; n++) {		/*入力文字列から単語を切り出す部分*/
    if (scanf("%s%*[^ \t\n]", let[n]) != 1) break;
      p_let[n] = let[n];
  }

  radixsort(n, 255, p_let, work);
  cmnnum(n, c_arr, p_let);
  cntnum(n, c_arr, p_let);

  return 0;
}

void radixsort(int n ,int length ,unsigned char *p_let[] ,unsigned char *work[]) {
  int i, j;
  static int count[UCHAR_MAX + 1];

  for (j = length - 1; j >= 0; j--) {
    for (i = 0; i <= UCHAR_MAX; i++) count[i] = 0;
    for (i = 0; i < n; i++) count[p_let[i][j]]++;
    for (i = 1; i <= UCHAR_MAX; i++) count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) work[--count[p_let[i][j]]] = p_let[i];
    for (i = 0; i < n; i++) p_let[i] = work[i];
  }
}

void cmnnum(int n, int c_arr[], unsigned char *p_let[]) {

  int i;
  int count = 0;
  char c1,c2;

  /*共通文字数を求める。*/
  for (i = 0; i < n; i++) {
    if(i == n - 1) {		/*最後の単語の共通文字数は０とする。*/
      c_arr[n] = 0;
      break;
    }

    sscanf(p_let[i],"%c",&c1);
    sscanf(p_let[i+1],"%c",&c2);
    while(c1 == c2) {
      count++;
      if(sscanf((p_let[i]+count),"%c",&c1) != 1) break;
      if(sscanf((p_let[i+1]+count),"%c",&c2) != 1) break;
    }
    c_arr[i] = count;		/*結果を共通文字数表に格納。*/
    count = 0;
  }
}

void cntnum(int n, int c_arr[], unsigned char *p_let[]) {

  /*共通文字数が指定の数以下になるまでの単語数を数える。*/

  int i,j = 0;
  int count = 0;
  int gc_arr[N];
  static unsigned char *res[N], g_let[N][GRAM];

  for (i = 0; i < n; i++)
    gc_arr[i] = 0;

  for (i = 0; i < n; i++) {

    count = 0;

    if(c_arr[i] >= GRAM) {		/*共通文字数がGRAM以上*/
      for(count = 0; count <= GRAM-1; count++)
        sscanf((p_let[i]+count) ,"%c" ,&g_let[j][count]);
      res[j] = g_let[j];
      gc_arr[j]++;
      }

    else if(c_arr[i-1] >= GRAM && i >= 1) {	/*共通文字数がGRAM未満*/
      gc_arr[j]++;
      printf("%s\t%d\t" ,res[j] ,gc_arr[j]);
      j++;					/*連続が途切れるのでｊをインクリメントする*/
      if((j % 10) == 0) printf("\n");
    }

    else if(strlen(p_let[i]) >= GRAM) {		/*１個だけ登場する文字列長GRAM以上の単語をカウントする*/
      for(count = 0; count <= GRAM-1; count++)
        sscanf((p_let[i]+count) ,"%c" ,&g_let[j][count]);
      res[j] = g_let[j];
      gc_arr[j]++;
      printf("%s\t%d\t" ,res[j] ,gc_arr[j]);
      j++;					/*ｊをインクリメントする*/
      if((j % 10) == 0) printf("\n");
    }
  }
}
