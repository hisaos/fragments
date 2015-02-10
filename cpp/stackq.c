#include<stdio.h>			/* プリプロセッサ宣言*/
#include<stdlib.h>			/* atoiを使うため*/
#include<string.h>

#define STACK_SIZE 50			/* スタックの大きさを文字定数で決めておく*/
#define QUEUE_SIZE 50			/* 待ち行列の大きさを文字定数で決めておく*/

/* 関数のプロトタイプ宣言*/
void push(int *p_sp, int i_digit, int i_st_val[]);	/* push*/
int pop(int *p_sp, int i_st_val[]);			/* pop*/
void enq(int *p_tail, int i_digit, int i_qu_val[]);	/* enq*/
int deq(int *p_tail, int i_qu_val[]);			/* deq*/

/* スタック，待ち行列、変数ｘの状態表示関数*/
int status(int x, int i_sp, int i_tail, int i_st_val[], int i_qu_val[]);

/* push,enqに渡す数値入力関数*/
int digitin(int *i_stop);

/* 意思決定ルーチン。yesかnoかを決めるときに使う。*/
int yesorno(void);

/* pop,deqの値をpush,enqに使うときに、push,enqのどちらを行うか決める関数*/
int pushorenq(void);

void main(void) {

	int x = 0;			/* 変数ｘ*/
	int i_index;			/* 配列初期化用のカウンタ*/
	int i_stop;			/* 数値入力時の取り消し判断用フラグ*/
	int i_temp;			/* pop, enqの返り値を退避しておく変数*/
	int i_com;			/* コマンド入力用変数*/
	int i_st_val[STACK_SIZE];	/* スタック用配列*/
	int i_qu_val[QUEUE_SIZE];	/* 待ち行列用配列*/
	int i_sp = STACK_SIZE;		/* スタックポインタ*/
	int i_tail = 0;			/* 待ち行列の最後尾を管理する*/
	int i_flag = -1;		/* 操作終了管理フラグ*/
	char c_buf[10];			/* コマンド入力用バッファ*/

	/* スタックと待ち行列の配列に0を代入して、初期化する。*/
	for(i_index = 0; i_index <= STACK_SIZE; i_index++)
		i_st_val[i_index] = 0;
	for(i_index = 0; i_index <= QUEUE_SIZE; i_index++)
		i_qu_val[i_index] = 0;

	while(i_flag) {			/* i_flagは終了を要求されるまでずっと-1*/

	i_stop = 0;

	printf("コマンド(1:PUSH 2:POP 3:ENQ 4:DEQ 5:Quit):");
	fgets(c_buf, sizeof(c_buf), stdin);

	/* 数値型に変換できないもの＝文字を入力されたとき，ここではじく。*/
	if(atoi(c_buf) == 0) {
		printf("不正な入力です: %s\n", c_buf);
		continue;
		}
	/* 数字を入力されたとき，ここでそれを切り出す。*/
	sscanf(c_buf, "%d", &i_com);

	/* 数字によって処理が分岐。*/
	switch(i_com) {

	case 1:				/* pushが選択された時*/
		if(i_sp == 0)
			printf("スタックが一杯です。\n");
		else {
			printf("何をpushしますか？:");
			i_temp = digitin(&i_stop);
			/* digitinの処理で、取り消しフラグが立った場合，代入しない*/
			if(i_stop == 1)
				break;
			else
				push(&i_sp, i_temp, i_st_val);
		}
		break;
	case 2:				/* popが選択された時*/

	if(i_sp == STACK_SIZE)
		printf("スタックは空です。\n");
	else {
		i_temp = pop(&i_sp, i_st_val);

		printf("この値をｘに格納しますか？(yes=0,no=1):");
		if(yesorno() == 1)
			x = i_temp;

		printf("この値をpushまたはenqしますか？(yes=0,no=1):");
		if(yesorno() == 1) {
			if(pushorenq() == 1)
				enq(&i_tail, i_temp, i_qu_val);
			else
				push(&i_sp, i_temp, i_st_val);
		}
	}

		break;
	case 3:				/* enqが選択された時*/
		if(i_tail == QUEUE_SIZE)
			printf("待ち行列が一杯です。\n");
		else {
			printf("何をenqしますか？:");
			i_temp = digitin(&i_stop);
			
			/* digitinの処理で、取り消しフラグが立った場合，代入しない*/
			if(i_stop == 1)
				break;
			else
				enq(&i_tail, i_temp, i_qu_val);
		}
		break;
	case 4:				/* deqが選択された時*/

	if(i_tail == 0)
		printf("待ち行列は空です。\n");
	else {
		i_temp = deq(&i_tail, i_qu_val);

		printf("この値をｘに格納しますか？(yes=0,no=1):");
		if(yesorno() == 1)
			x = i_temp;

		printf("この値をpushまたはenqしますか？(yes=0,no=1):");
		if(yesorno() == 1) {
			if(pushorenq() == 1)
				enq(&i_tail, i_temp, i_qu_val);
			else
				push(&i_sp, i_temp, i_st_val);
		}
	}
		break;
	case 5:				/* 終了が要求されたとき*/
		printf("終了しました。\n");
		i_flag++;
		exit(0);
	default:
	/*1-5にない数字の場合，ここではじかれる。*/
		printf("不正な入力です: %d\n", i_com);
		}

	if(status(x, i_sp, i_tail, i_st_val, i_qu_val) == 0)	/* 関数statusが正常に処理を終了したら0を返す。*/
		printf("準備完了\n");
	else {
		printf("異常終了\n");				/* 関数statusが0を返せなかったとき、異常終了とする。*/
		exit(0);
		}
	}
}

void push(int *p_sp, int i_digit, int i_st_val[]) {		/* pushの宣言*/
	(*p_sp)--;		/* pushする前に、スタックポインタを1下げる*/
	i_st_val[*p_sp] = i_digit;
	printf("%d がpushされました。\n", i_st_val[*p_sp]);
}

int pop(int *p_sp, int i_st_val[]) {				/* popの宣言*/

	int i_pop;		/* i_popにはpopされる値を入れて，返し値にする*/

	printf("%d がpopされました。\n", i_st_val[*p_sp]);
	i_pop = i_st_val[*p_sp];
	i_st_val[*p_sp] = 0;
	(*p_sp)++;		/* popした後，スタックポインタの値を1増やす*/

	return i_pop;
}

void enq(int *p_tail, int i_digit, int i_qu_val[]) {		/* enqの宣言*/
	/* 最後尾の位置を一つ後ろにしてから、値を代入*/
	(*p_tail)++;
	i_qu_val[*p_tail] = i_digit;
	printf("%d がenqされました。\n", i_qu_val[*p_tail]);
}

int deq(int *p_tail, int i_qu_val[]) {				/* deqの宣言*/

	int i_index;		/* deqされた後，待ち行列を更新する時に使うカウンタ*/
	int i_deq;		/* deqされる値を入れて，返し値にする変数*/

	printf("%d がdeqされました。\n", i_qu_val[1]);
	i_deq = i_qu_val[1];		/* 待ち行列の一番前にある値をdeqされた値として、代入*/
	for(i_index = 2; i_index <= *p_tail; i_index++) {	/* 待ち行列を更新する*/
		i_qu_val[i_index - 1] = i_qu_val[i_index];	/* 後ろから前にコピーしていく*/
	}
	i_qu_val[*p_tail] = 0;			/* 更新終了後，最後尾の値を0の代入によって消去*/
	(*p_tail)--;				/* 最後尾の位置を更新*/

	return i_deq;
}

/* 状態管理関数statusの宣言*/
int status(int x, int i_sp, int i_tail, int i_st_val[], int i_qu_val[]) {

	int i_index;		/* スタック、待ち行列を一覧表示するときつかうカウンタ*/

	printf("スタック，待ち行列，変数ｘの状態:\n\n");
	printf("スタック:\n");
	
	/* スタックの表示*/
	for(i_index = i_sp; i_index <= STACK_SIZE - 1; i_index++)
		printf("\t| %d |\n", i_st_val[i_index]);
	printf("\n待ち行列:\n\t最後尾 ");
	
	/* 待ち行列の表示*/
	for(i_index = i_tail; i_index >= 1; i_index--) {
		printf("| %d ", i_qu_val[i_index]);
	}
	printf("| 先頭\n\n");

	/* 変数ｘの表示*/
	printf("x = %d\n\n", x);

	return 0;
}

/* 共用数値入力関数digitinの宣言*/
int digitin(int *i_stop) {

	int i_digit;		/* 入力された数値を格納して，mainに返す変数*/
	int i_flag = -1;	/* 文字の入力をはじくためにフラグが必要*/
	char c_buf[10];		/* 文字入力用バッファ*/
	
	while(i_flag) {
	
	printf("（入力を取り消す場合は、\'s\'または\'S\'を入力）");
	fgets(c_buf, sizeof(c_buf), stdin);		/* 標準入力から数値を入力する*/

	/* 入力取り消し処理*/
	if(c_buf[0] == 's' || c_buf[0] == 'S') {
		printf("入力は取り消されました\n");
		(*i_stop)++;
		i_flag++;
		}
	/* sscanfで、数値型で取り出せるものがなかった場合不正入力とする*/
	else if(sscanf(c_buf, "%d", &i_digit) == 0)
		printf("不正な入力です: %s\n", c_buf);
	else
		i_flag++;
	}

	return i_digit;
}

/* 共用意思決定関数yesornoの宣言*/
int yesorno(void) {

	int i_flag = -1;	/* 文字の入力をはじくためにフラグが必要*/
	int i_decide = 0;	/* 返答をmainに返すために代入しておく変数*/
	int i_choice;		/* switchで使われる返答を数値で表す変数*/
	char c_buf[5];		/* 文字入力用バッファ*/

	while(i_flag) {
		fgets(c_buf, sizeof(c_buf), stdin);	/* 標準入力から数値を入力する*/
		i_choice = atoi(c_buf);			/* c_bufは文字型なので、整数型に変換*/

		switch(i_choice) {
			case 0:
				i_decide++;
				i_flag++;
				break;
			case 1:
				i_flag++;
				break;
			/* 不正な入力だった場合、i_flagを更新せず，処理を繰り返させる*/
			default:
				printf("不正な入力です: %s\n", c_buf);
		}
	}
	return i_decide;
}

/* pushとenqの分岐を決定する共用意思決定関数pushorenqの宣言*/
int pushorenq(void) {

	int i_flag = -1;	/* 文字の入力をはじくためにフラグが必要*/
	int i_choice;		/* 返答を数値で表す。*/
	char c_buf[5];		/* 文字入力用バッファ*/

	printf("pushとenq、どちらですか？(push=0,enq=1):");
	while(i_flag) {
		fgets(c_buf, sizeof(c_buf), stdin);
		i_choice = atoi(c_buf);

		switch(i_choice) {
			case 0:
			case 1:
				i_flag++;
				break;
			
			/* 不正な入力だった場合はi_flagを更新せず，処理を繰り返させる*/
			default:
				printf("不正な入力です: %s\n", c_buf);
		}
	}
	return i_choice;
}

