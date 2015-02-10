#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INDEX 50				/* 最大データ個数 */
#define MAX_VALUE 9999				/* データ許容範囲の最大 */
#define MIN_VALUE 0				/* データ許容範囲の最小 */

/* 関数のプロトタイプ宣言 */
void indata(void);					/* データ入力関数 */
void sort(int array[], int array_len[], int index);	/* データソート関数 */
void outdata(int array[], int array_len[], int count);	/* データ出力関数 */

int main(void) {

  indata();					/* mainで実行される関数はindataのみ */
  
  return 0;
}

void indata(void) {

  int data;					/* 入力データ格納変数 */
  int index = 0;				/* 入力データ数管理変数 */
  int flg = 1;					/* 入力終了管理フラグ（常に1） */
  int array[MAX_INDEX];				/* データ格納配列 */
  int array_len[MAX_INDEX];			/* データ長格納配列 */
  char line[20];				/* データ入力バッファ */

  while(flg) {

  fgets(line, sizeof(line), stdin);		/* データ入力およびデータ長取得 */ 
  array_len[index] = strlen(line);

  if (atoi(line) == 0) {			/* 文字を入力した場合，ここではじく */
      printf("invalid input: %s\n", line);
      continue;
    }

  if (sscanf(line, "%d", &data) == 1) {			/* 入力した文字型データを整数型に */
    if(data >= MIN_VALUE && data <= MAX_VALUE) {	/* データが許容範囲内にあるかチェック */
      array[index] = data;				/* チェックにとおったデータを配列に格納 */
      printf(".%d\n", array[index]);
    }

    else if(data == -1) {			/* -1が入力されたらデータ入力終了 */
      printf("end of data.\n");
      array[index] = 0;
      index--;					/* indexは、次にデータが格納される場所を */
      break;					/* 指しているので、入力終了時に-1する */
    }

    else {
      printf("invalid input: %d\n", data);	/* 上のチェックで許容範囲外だった時のメッセージ */
      continue;					/* while文の頭に戻る。indexには変化無し。 */
    }
  }

    if(index >= MAX_INDEX - 1) {		/* 50個目のデータを打ち込むと、ここでデータ個数チェックに */
      printf("too many digits.\n");		/* 引っかかる */
      break;					/* 入力終了後、breakで脱出 */
    }

    else 					/* ループ脱出チェックを全部通過するとここへ来る。 */
      index++;					/* ここへ来ると，indexが1増えて配列の次の要素に格納する準備をする */
  }

  sort(array, array_len, index);		/* sortにデータ配列、データ長配列、データ個数を渡して呼ぶ */

}

void sort(int array[], int array_len[], int index)

{
  int i, j, temp, temp_len;		/* i,jが２重ループ用のカウンタ */
  					/* temp,temp_lenはそれぞれデータ本体とデータ長のソートに使う一時変数 */
   for(j = index; j > 0; j--) {		/* バブルソートの本体 */
    for(i = 0; i < j; i++) {
      if(array[i] > array[i + 1]) {
	temp = array[i + 1];			/* データ本体を交換 */
	array[i + 1] = array[i];
	array[i] = temp;

	temp_len = array_len[i + 1];		/* 同じ添字で、データ長も交換する */
	array_len[i + 1] = array_len[i];
	array_len[i] = temp_len;
      }
    }
  }
  outdata(array, array_len, index);		/* ソート済みデータ配列、データ長配列、データ個数を渡して、 */
}						/* 出力関数outdataを呼ぶ */

void outdata(int array[], int array_len[], int count) {

  int lcount;		/* データ配列の添え字カウンタ兼改行カウンタ */
  int tcount;		/* 右揃えにするための空白文字挿入に使うカウンタ */

  for(lcount = 0; lcount <= count; lcount++) {
    for(tcount = 0; tcount <= 5 - array_len[lcount]; tcount++)		/* 5からarray_len[lcount]を */
      printf("\x20");							/* 引いた数だけ空白を入れる */
    printf("%d ", array[lcount]);					/* それからデータ本体を出力 */

    if(lcount % 10 == 9) 	/* データ添え字の一の位が9のときに出力後、改行する */
      printf("\n");
  }
}

