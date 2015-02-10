#include<stdio.h>			/* �v���v���Z�b�T�錾*/
#include<stdlib.h>			/* atoi���g������*/
#include<string.h>

#define STACK_SIZE 50			/* �X�^�b�N�̑傫���𕶎��萔�Ō��߂Ă���*/
#define QUEUE_SIZE 50			/* �҂��s��̑傫���𕶎��萔�Ō��߂Ă���*/

/* �֐��̃v���g�^�C�v�錾*/
void push(int *p_sp, int i_digit, int i_st_val[]);	/* push*/
int pop(int *p_sp, int i_st_val[]);			/* pop*/
void enq(int *p_tail, int i_digit, int i_qu_val[]);	/* enq*/
int deq(int *p_tail, int i_qu_val[]);			/* deq*/

/* �X�^�b�N�C�҂��s��A�ϐ����̏�ԕ\���֐�*/
int status(int x, int i_sp, int i_tail, int i_st_val[], int i_qu_val[]);

/* push,enq�ɓn�����l���͊֐�*/
int digitin(int *i_stop);

/* �ӎv���胋�[�`���Byes��no�������߂�Ƃ��Ɏg���B*/
int yesorno(void);

/* pop,deq�̒l��push,enq�Ɏg���Ƃ��ɁApush,enq�̂ǂ�����s�������߂�֐�*/
int pushorenq(void);

void main(void) {

	int x = 0;			/* �ϐ���*/
	int i_index;			/* �z�񏉊����p�̃J�E���^*/
	int i_stop;			/* ���l���͎��̎��������f�p�t���O*/
	int i_temp;			/* pop, enq�̕Ԃ�l��ޔ����Ă����ϐ�*/
	int i_com;			/* �R�}���h���͗p�ϐ�*/
	int i_st_val[STACK_SIZE];	/* �X�^�b�N�p�z��*/
	int i_qu_val[QUEUE_SIZE];	/* �҂��s��p�z��*/
	int i_sp = STACK_SIZE;		/* �X�^�b�N�|�C���^*/
	int i_tail = 0;			/* �҂��s��̍Ō�����Ǘ�����*/
	int i_flag = -1;		/* ����I���Ǘ��t���O*/
	char c_buf[10];			/* �R�}���h���͗p�o�b�t�@*/

	/* �X�^�b�N�Ƒ҂��s��̔z���0�������āA����������B*/
	for(i_index = 0; i_index <= STACK_SIZE; i_index++)
		i_st_val[i_index] = 0;
	for(i_index = 0; i_index <= QUEUE_SIZE; i_index++)
		i_qu_val[i_index] = 0;

	while(i_flag) {			/* i_flag�͏I����v�������܂ł�����-1*/

	i_stop = 0;

	printf("�R�}���h(1:PUSH 2:POP 3:ENQ 4:DEQ 5:Quit):");
	fgets(c_buf, sizeof(c_buf), stdin);

	/* ���l�^�ɕϊ��ł��Ȃ����́���������͂��ꂽ�Ƃ��C�����ł͂����B*/
	if(atoi(c_buf) == 0) {
		printf("�s���ȓ��͂ł�: %s\n", c_buf);
		continue;
		}
	/* ��������͂��ꂽ�Ƃ��C�����ł����؂�o���B*/
	sscanf(c_buf, "%d", &i_com);

	/* �����ɂ���ď���������B*/
	switch(i_com) {

	case 1:				/* push���I�����ꂽ��*/
		if(i_sp == 0)
			printf("�X�^�b�N����t�ł��B\n");
		else {
			printf("����push���܂����H:");
			i_temp = digitin(&i_stop);
			/* digitin�̏����ŁA�������t���O���������ꍇ�C������Ȃ�*/
			if(i_stop == 1)
				break;
			else
				push(&i_sp, i_temp, i_st_val);
		}
		break;
	case 2:				/* pop���I�����ꂽ��*/

	if(i_sp == STACK_SIZE)
		printf("�X�^�b�N�͋�ł��B\n");
	else {
		i_temp = pop(&i_sp, i_st_val);

		printf("���̒l�����Ɋi�[���܂����H(yes=0,no=1):");
		if(yesorno() == 1)
			x = i_temp;

		printf("���̒l��push�܂���enq���܂����H(yes=0,no=1):");
		if(yesorno() == 1) {
			if(pushorenq() == 1)
				enq(&i_tail, i_temp, i_qu_val);
			else
				push(&i_sp, i_temp, i_st_val);
		}
	}

		break;
	case 3:				/* enq���I�����ꂽ��*/
		if(i_tail == QUEUE_SIZE)
			printf("�҂��s�񂪈�t�ł��B\n");
		else {
			printf("����enq���܂����H:");
			i_temp = digitin(&i_stop);
			
			/* digitin�̏����ŁA�������t���O���������ꍇ�C������Ȃ�*/
			if(i_stop == 1)
				break;
			else
				enq(&i_tail, i_temp, i_qu_val);
		}
		break;
	case 4:				/* deq���I�����ꂽ��*/

	if(i_tail == 0)
		printf("�҂��s��͋�ł��B\n");
	else {
		i_temp = deq(&i_tail, i_qu_val);

		printf("���̒l�����Ɋi�[���܂����H(yes=0,no=1):");
		if(yesorno() == 1)
			x = i_temp;

		printf("���̒l��push�܂���enq���܂����H(yes=0,no=1):");
		if(yesorno() == 1) {
			if(pushorenq() == 1)
				enq(&i_tail, i_temp, i_qu_val);
			else
				push(&i_sp, i_temp, i_st_val);
		}
	}
		break;
	case 5:				/* �I�����v�����ꂽ�Ƃ�*/
		printf("�I�����܂����B\n");
		i_flag++;
		exit(0);
	default:
	/*1-5�ɂȂ������̏ꍇ�C�����ł͂������B*/
		printf("�s���ȓ��͂ł�: %d\n", i_com);
		}

	if(status(x, i_sp, i_tail, i_st_val, i_qu_val) == 0)	/* �֐�status������ɏ������I��������0��Ԃ��B*/
		printf("��������\n");
	else {
		printf("�ُ�I��\n");				/* �֐�status��0��Ԃ��Ȃ������Ƃ��A�ُ�I���Ƃ���B*/
		exit(0);
		}
	}
}

void push(int *p_sp, int i_digit, int i_st_val[]) {		/* push�̐錾*/
	(*p_sp)--;		/* push����O�ɁA�X�^�b�N�|�C���^��1������*/
	i_st_val[*p_sp] = i_digit;
	printf("%d ��push����܂����B\n", i_st_val[*p_sp]);
}

int pop(int *p_sp, int i_st_val[]) {				/* pop�̐錾*/

	int i_pop;		/* i_pop�ɂ�pop�����l�����āC�Ԃ��l�ɂ���*/

	printf("%d ��pop����܂����B\n", i_st_val[*p_sp]);
	i_pop = i_st_val[*p_sp];
	i_st_val[*p_sp] = 0;
	(*p_sp)++;		/* pop������C�X�^�b�N�|�C���^�̒l��1���₷*/

	return i_pop;
}

void enq(int *p_tail, int i_digit, int i_qu_val[]) {		/* enq�̐錾*/
	/* �Ō���̈ʒu������ɂ��Ă���A�l����*/
	(*p_tail)++;
	i_qu_val[*p_tail] = i_digit;
	printf("%d ��enq����܂����B\n", i_qu_val[*p_tail]);
}

int deq(int *p_tail, int i_qu_val[]) {				/* deq�̐錾*/

	int i_index;		/* deq���ꂽ��C�҂��s����X�V���鎞�Ɏg���J�E���^*/
	int i_deq;		/* deq�����l�����āC�Ԃ��l�ɂ���ϐ�*/

	printf("%d ��deq����܂����B\n", i_qu_val[1]);
	i_deq = i_qu_val[1];		/* �҂��s��̈�ԑO�ɂ���l��deq���ꂽ�l�Ƃ��āA���*/
	for(i_index = 2; i_index <= *p_tail; i_index++) {	/* �҂��s����X�V����*/
		i_qu_val[i_index - 1] = i_qu_val[i_index];	/* ��납��O�ɃR�s�[���Ă���*/
	}
	i_qu_val[*p_tail] = 0;			/* �X�V�I����C�Ō���̒l��0�̑���ɂ���ď���*/
	(*p_tail)--;				/* �Ō���̈ʒu���X�V*/

	return i_deq;
}

/* ��ԊǗ��֐�status�̐錾*/
int status(int x, int i_sp, int i_tail, int i_st_val[], int i_qu_val[]) {

	int i_index;		/* �X�^�b�N�A�҂��s����ꗗ�\������Ƃ������J�E���^*/

	printf("�X�^�b�N�C�҂��s��C�ϐ����̏��:\n\n");
	printf("�X�^�b�N:\n");
	
	/* �X�^�b�N�̕\��*/
	for(i_index = i_sp; i_index <= STACK_SIZE - 1; i_index++)
		printf("\t| %d |\n", i_st_val[i_index]);
	printf("\n�҂��s��:\n\t�Ō�� ");
	
	/* �҂��s��̕\��*/
	for(i_index = i_tail; i_index >= 1; i_index--) {
		printf("| %d ", i_qu_val[i_index]);
	}
	printf("| �擪\n\n");

	/* �ϐ����̕\��*/
	printf("x = %d\n\n", x);

	return 0;
}

/* ���p���l���͊֐�digitin�̐錾*/
int digitin(int *i_stop) {

	int i_digit;		/* ���͂��ꂽ���l���i�[���āCmain�ɕԂ��ϐ�*/
	int i_flag = -1;	/* �����̓��͂��͂������߂Ƀt���O���K�v*/
	char c_buf[10];		/* �������͗p�o�b�t�@*/
	
	while(i_flag) {
	
	printf("�i���͂��������ꍇ�́A\'s\'�܂���\'S\'����́j");
	fgets(c_buf, sizeof(c_buf), stdin);		/* �W�����͂��琔�l����͂���*/

	/* ���͎���������*/
	if(c_buf[0] == 's' || c_buf[0] == 'S') {
		printf("���͎͂�������܂���\n");
		(*i_stop)++;
		i_flag++;
		}
	/* sscanf�ŁA���l�^�Ŏ��o������̂��Ȃ������ꍇ�s�����͂Ƃ���*/
	else if(sscanf(c_buf, "%d", &i_digit) == 0)
		printf("�s���ȓ��͂ł�: %s\n", c_buf);
	else
		i_flag++;
	}

	return i_digit;
}

/* ���p�ӎv����֐�yesorno�̐錾*/
int yesorno(void) {

	int i_flag = -1;	/* �����̓��͂��͂������߂Ƀt���O���K�v*/
	int i_decide = 0;	/* �ԓ���main�ɕԂ����߂ɑ�����Ă����ϐ�*/
	int i_choice;		/* switch�Ŏg����ԓ��𐔒l�ŕ\���ϐ�*/
	char c_buf[5];		/* �������͗p�o�b�t�@*/

	while(i_flag) {
		fgets(c_buf, sizeof(c_buf), stdin);	/* �W�����͂��琔�l����͂���*/
		i_choice = atoi(c_buf);			/* c_buf�͕����^�Ȃ̂ŁA�����^�ɕϊ�*/

		switch(i_choice) {
			case 0:
				i_decide++;
				i_flag++;
				break;
			case 1:
				i_flag++;
				break;
			/* �s���ȓ��͂������ꍇ�Ai_flag���X�V�����C�������J��Ԃ�����*/
			default:
				printf("�s���ȓ��͂ł�: %s\n", c_buf);
		}
	}
	return i_decide;
}

/* push��enq�̕�������肷�鋤�p�ӎv����֐�pushorenq�̐錾*/
int pushorenq(void) {

	int i_flag = -1;	/* �����̓��͂��͂������߂Ƀt���O���K�v*/
	int i_choice;		/* �ԓ��𐔒l�ŕ\���B*/
	char c_buf[5];		/* �������͗p�o�b�t�@*/

	printf("push��enq�A�ǂ���ł����H(push=0,enq=1):");
	while(i_flag) {
		fgets(c_buf, sizeof(c_buf), stdin);
		i_choice = atoi(c_buf);

		switch(i_choice) {
			case 0:
			case 1:
				i_flag++;
				break;
			
			/* �s���ȓ��͂������ꍇ��i_flag���X�V�����C�������J��Ԃ�����*/
			default:
				printf("�s���ȓ��͂ł�: %s\n", c_buf);
		}
	}
	return i_choice;
}

