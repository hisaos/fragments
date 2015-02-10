#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INDEX 15000 	/*入力する整数の最大個数*/
#define SORT_METHODS 2		/*選択できる整列法の数*/

void indata(long ar[], int ar_len[], int *index);		/*ファイル入力関数*/
void bubble_sort(int left, int index ,long ar[], int ar_len[]);	/*バブルソート関数*/
void quick_sort(int left, int right, long ar[], int ar_len[]);	/*クイックソート関数*/
int pivot(int left, int right, long ar[]);			/*クイックソートの軸要素決定関数*/
int swap(int i1, int i2, long ar[], int ar_len[]);		/*値交換関数*/
void outdata(long ar[], int ar_len[], int index);		/*結果出力関数*/

int main(int argc, char* argv[]) {

/*mainは整数を格納する配列の宣言、ソートモジュールのエントリポイント格納、*/
/*整列法の選択処理、整列法選択に対するエラー処理、各関数の呼び出しを行う。*/

  int index = 0;					/*indataで入力された整数の個数を保持*/
  int num;						/*整列法の選択に使う*/
  void (*sel[SORT_METHODS]) (int ,int ,long*, int*);	/*ソート関数のエントリポイントを格納するvoid型配列*/
  char line[10];					/*整列法を対話処理で決定する場合、コンソールで入力された文字列を格納する*/
  char sort_name[SORT_METHODS][20];		/*結果出力後に処理した整列法を表示するため、整列法の名称を格納しておく*/
  long ar[MAX_INDEX];				/*入力した整数群を格納する配列*/
  int ar_len[MAX_INDEX];			/*arに格納する整数の文字数を記録する配列*/

/*整列法の名称を配列sort_nameに格納*/
  strcpy(sort_name[0],"bubble sort");
  strcpy(sort_name[1],"quick sort");

/*sel[0]にbubble_sort、sel[1]にquick_sortのエントリポイントを格納*/
  sel[0] = bubble_sort;
  sel[1] = quick_sort;

/*先にファイルからの読み込みを済ませておく*/
  indata(ar, ar_len, &index);

/*整列法を決定する処理*/
/*引数があった場合*/
  if(argc > 1) {
    num = atoi(*++argv);			/*引数をargvからとって来てatoiしてnumに格納*/
    if(num >= 0 && num <= SORT_METHODS-1)	/*引数が0か1なら、ソート実行*/
      (*sel[num])(0, index, ar, ar_len);
    else {					/*引数が0か1以外なら、プログラムを終了*/
      printf("0から%dまでの値を入力してください｡",SORT_METHODS-1);
      exit(0);
    }
  }
/*引数がなかった場合の対話処理*/
  else {
    printf("10000個程度の整数を整列します。整列法を選択してください。\n");
    while(1) {
      printf("0:bubble sort\n");
      printf("1:quick sort\n");
      num = atoi(fgets(line, sizeof(line), stdin));	/*fgetsで入力した結果をatoiしてnumに格納*/
      if(num >= 0 && num <= SORT_METHODS-1) {		/*入力が0か1なら、ソートを実行してループ脱出*/
        (*sel[num])(0, index, ar, ar_len);
        break;
      }
/*入力が0か1以外なら、エラーメッセージを出して、再入力させる*/
      else {
        printf("0から%dまでの値を入力してください｡\n",SORT_METHODS-1);
        continue;
      }
    }
  }

/*整列終了後、outdataを呼んで結果を端末に出力*/
  outdata(ar, ar_len, index);
/*選択した整列法を出力して、終了。*/
  printf("%sで整列されました。\n",sort_name[num]);

  return 0;
}

void indata(long ar[], int ar_len[], int *index) {

/*indataは、あらかじめ用意された、整数群を保存してあるファイル"longdata.txt"にアクセスし、*/
/*整数と、整数の文字数をそれぞれ配列ar[],ar_len[]に格納する。*/

  FILE* frp;		/*longdata.txt用のファイルポインタ*/
  int add = 0;		/*fgetsで読んだ行をsscanfで整数１個ずつにして格納するときに、行のどこから読むかを決定するカーソル*/
  char data[10];	/*fgetsで読んだ行からsscanfで整数１個ずつにして切り出すとき使うバッファ*/
  char line[80];	/*fgetsでlongdata.txtから読んでくるときに、行を格納するバッファ*/

  frp = fopen("longdata.txt", "r");	/*longdata.txtを読み出しモードで開く*/

/*ファイルの終わりに達するまでループ*/
  while(fgets(line, sizeof(line), frp) != NULL) {

/*line+addの位置で読めなくなるまでループ*/
    while(sscanf((line+add), "%s" ,&data) == 1) {
      add = add + strlen(data) + 1; 	/*読んだ整数の文字数＋空白１文字分だけカーソルをずらす*/
      ar[*index] = atoi(data);		/*dataに格納されている整数文字列をatoiで変換して、ar[]に格納*/
      ar_len[*index] = strlen(data);	/*整数の文字数も同時に格納する*/
      (*index)++;			/*ar[]、ar_len[]の添え字を１つ進める*/
    }
    add = 0;	/*ループを脱出したらadd=0として、また次の行の先頭からsscanfで整数を切り出す*/
  }
  fclose(frp);	/*ファイルを読み尽くしたらlongdata.txtを閉じる*/
}

void bubble_sort(int left, int index, long ar[], int ar_len[]) {

/*bubble_sortはファイルから入力された整数の個数index,*/
/*整数が格納された配列ar、各整数の文字数が格納された配列ar_lenを*/
/*mainから受け取り、バブルソートによってar,ar_lenの整列を行う。*/
/*引数leftは配列中でソートする範囲の左端を指定するが関数のディスパッチを行うために入れられたダミー引数に等しい。*/

  int count_in, count_ex;
/*count_inはバブルソートの内側ループ、count_exは外側のループのカウンタ。*/

  for(count_ex = index; count_ex > 0; count_ex--) {
    for(count_in = left; count_in < count_ex; count_in++) {
      if(ar[count_in] > ar[count_in + 1])			/*右の要素より左の要素が大きければ、交換実行*/
	swap(count_in, count_in+1, ar, ar_len);		/*配列の要素間の交換は別関数swapで行う。*/
    }
  }
}

void quick_sort(int left, int right, long ar[], int ar_len[]) {

/*quick_sortは整数が格納された配列ar、各整数の文字数が格納された配列ar_lenを*/
/*呼び出し元の関数から受け取り、配列中の左端left、右端rightで指定される範囲に対して*/
/*クイックソートによるar,ar_lenの整列を行う。*/

  int p_index, p_val;		/*p_indexは軸要素の添え字番号、p_valは軸要素そのものを格納する。*/
  int l_edge = left;		/*処理範囲の軸要素より左の範囲を調査するカーソル*/
  int r_edge = right;		/*処理範囲の軸要素を含む、軸要素より右の範囲を調査するカーソル*/

  p_index = pivot(left, right, ar);	/*配列中の軸要素の要素番号を求める*/

  if(p_index != -1) {		/*p_indexが-1ならば、pivotで調べた範囲はすべて同じ数字が入っているのでソートをスキップ*/
    p_val = ar[p_index];	/*軸要素をp_valに格納*/

    while(1) {	/*配列の分割を行うループ*/

/*l_edgeは処理する範囲の左端から、軸要素より大きな要素を見つけるまで右にずれる。*/
/*r_edgeは処理する範囲の右端から、軸要素より小さな要素を見つけるまで左にずれる。*/
      while(ar[l_edge] < p_val) l_edge++;
      while(ar[r_edge] >= p_val) r_edge--;

/*l_edgeがr_edgeより右なら、その範囲でのソートは終了。*/
      if(l_edge > r_edge) break;

/*ソートが終わっていないなら、その時点でのl_edgeとr_edgeの位置にある要素を交換する。*/
      swap(r_edge, l_edge, ar, ar_len);

/*交換後、l_edge、r_edgeの両方をずらして、ループする。*/
      l_edge++;
      r_edge--;
    }
/*調査範囲の分割後、分割した左の範囲と右の範囲についてそれぞれquick_sortを再帰呼び出ししてソートを進める*/
    quick_sort(left, l_edge - 1, ar, ar_len);
    quick_sort(l_edge, right, ar, ar_len);
  }
}

int pivot(int left, int right, long ar[]) {

/*pivotは、quick_sortから呼ばれ、quick_sortから渡される引数leftとrightにより指定される*/
/*配列中のクイックソートを行う範囲における軸要素を指定する関数*/
/*最初に見つけた２種類の数のうち、大きいほうを軸要素とする。*/
/*quick_sortには、軸要素の添え字番号p_indexが返される。*/

  int cursor = left;	/*ar[cursor]と範囲内の先頭の値ar[left]との大小を比較する*/
  int p_index;		/*軸要素の添え字番号。範囲内の値がすべて同じだった場合、-1となる*/

/*範囲内の先頭の値ar[left]とar[cursor]が異なる値になるまで、cursorをずらしていく*/
  while(ar[cursor] == ar[left] && cursor <= right) cursor++;

/*ループを脱出後、p_indexを決定*/
  if(cursor > right) p_index = -1;				/*cursorがrightを超えていたとき、全部同じ数だから-1*/
  else if(ar[cursor] > ar[left]) p_index = cursor;	/*ar[cursor]>ar[left]ならcursor*/
  else p_index = left;						/*ar[cursor]<=ar[left]ならleftとし、*/

  return p_index;	/*quick_sortにp_indexを返す*/
}

int swap(int i1, int i2, long ar[], int ar_len[]) {
/*swapは呼び出し元のソート関数からソート対象の配列arと文字数を格納してある配列ar_lenを受け取り*/
/*ar[i1]とar[i2]、ar_len[i1]とar_len[i2]をそれぞれ交換する関数*/

  int temp;		/*値を一時退避しておく変数*/

  temp = ar[i2];		/*配列要素自体の交換*/
  ar[i2] = ar[i1];
  ar[i1] = temp;

  temp = ar_len[i2];		/*配列要素の文字数の交換*/
  ar_len[i2] = ar_len[i1];
  ar_len[i1] = temp;

  return 0;
}

void outdata(long ar[], int ar_len[], int index) {

/*outdataは配列ar[]、文字数を格納した配列ar_len[]、配列の要素数indexを受け取り*/
/*ar[]の先頭から順に、１行１０個ずつ、かつar_len[]に格納された文字数の情報を利用して右詰にしながら*/
/*整数群を整列した結果を表示する関数*/

  int lcount;		/*配列の何個目まで表示したか保持する*/
  int tcount;		/*数字の表示を右詰にするスペースを入れるループに使うカウンタ*/

/*lcountがindexになるまで、配列の内容を表示しつづけるループ*/
  for(lcount = 0; lcount <= index; lcount++) {
    for(tcount = 0; tcount <= 5-ar_len[lcount]; tcount++)	/*5-ar_len[]個の空白を入れて、表示を右詰にする*/
      printf("\x20");
    printf("%d ", ar[lcount]);
    if(lcount % 10 == 9) 	/*数字を表示してからlcountの１の位が9だったら、改行する*/
      printf("\n");
  }
  printf("\n");			/*表示終了後にも改行する*/
}

