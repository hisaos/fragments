#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INDEX 50				/* �ő�f�[�^�� */
#define MAX_VALUE 9999				/* �f�[�^���e�͈͂̍ő� */
#define MIN_VALUE 0				/* �f�[�^���e�͈͂̍ŏ� */

/* �֐��̃v���g�^�C�v�錾 */
void indata(void);					/* �f�[�^���͊֐� */
void sort(int array[], int array_len[], int index);	/* �f�[�^�\�[�g�֐� */
void outdata(int array[], int array_len[], int count);	/* �f�[�^�o�͊֐� */

int main(void) {

  indata();					/* main�Ŏ��s�����֐���indata�̂� */
  
  return 0;
}

void indata(void) {

  int data;					/* ���̓f�[�^�i�[�ϐ� */
  int index = 0;				/* ���̓f�[�^���Ǘ��ϐ� */
  int flg = 1;					/* ���͏I���Ǘ��t���O�i���1�j */
  int array[MAX_INDEX];				/* �f�[�^�i�[�z�� */
  int array_len[MAX_INDEX];			/* �f�[�^���i�[�z�� */
  char line[20];				/* �f�[�^���̓o�b�t�@ */

  while(flg) {

  fgets(line, sizeof(line), stdin);		/* �f�[�^���͂���уf�[�^���擾 */ 
  array_len[index] = strlen(line);

  if (atoi(line) == 0) {			/* ��������͂����ꍇ�C�����ł͂��� */
      printf("invalid input: %s\n", line);
      continue;
    }

  if (sscanf(line, "%d", &data) == 1) {			/* ���͂��������^�f�[�^�𐮐��^�� */
    if(data >= MIN_VALUE && data <= MAX_VALUE) {	/* �f�[�^�����e�͈͓��ɂ��邩�`�F�b�N */
      array[index] = data;				/* �`�F�b�N�ɂƂ������f�[�^��z��Ɋi�[ */
      printf(".%d\n", array[index]);
    }

    else if(data == -1) {			/* -1�����͂��ꂽ��f�[�^���͏I�� */
      printf("end of data.\n");
      array[index] = 0;
      index--;					/* index�́A���Ƀf�[�^���i�[�����ꏊ�� */
      break;					/* �w���Ă���̂ŁA���͏I������-1���� */
    }

    else {
      printf("invalid input: %d\n", data);	/* ��̃`�F�b�N�ŋ��e�͈͊O���������̃��b�Z�[�W */
      continue;					/* while���̓��ɖ߂�Bindex�ɂ͕ω������B */
    }
  }

    if(index >= MAX_INDEX - 1) {		/* 50�ڂ̃f�[�^��ł����ނƁA�����Ńf�[�^���`�F�b�N�� */
      printf("too many digits.\n");		/* ���������� */
      break;					/* ���͏I����Abreak�ŒE�o */
    }

    else 					/* ���[�v�E�o�`�F�b�N��S���ʉ߂���Ƃ����֗���B */
      index++;					/* �����֗���ƁCindex��1�����Ĕz��̎��̗v�f�Ɋi�[���鏀�������� */
  }

  sort(array, array_len, index);		/* sort�Ƀf�[�^�z��A�f�[�^���z��A�f�[�^����n���ČĂ� */

}

void sort(int array[], int array_len[], int index)

{
  int i, j, temp, temp_len;		/* i,j���Q�d���[�v�p�̃J�E���^ */
  					/* temp,temp_len�͂��ꂼ��f�[�^�{�̂ƃf�[�^���̃\�[�g�Ɏg���ꎞ�ϐ� */
   for(j = index; j > 0; j--) {		/* �o�u���\�[�g�̖{�� */
    for(i = 0; i < j; i++) {
      if(array[i] > array[i + 1]) {
	temp = array[i + 1];			/* �f�[�^�{�̂����� */
	array[i + 1] = array[i];
	array[i] = temp;

	temp_len = array_len[i + 1];		/* �����Y���ŁA�f�[�^������������ */
	array_len[i + 1] = array_len[i];
	array_len[i] = temp_len;
      }
    }
  }
  outdata(array, array_len, index);		/* �\�[�g�ς݃f�[�^�z��A�f�[�^���z��A�f�[�^����n���āA */
}						/* �o�͊֐�outdata���Ă� */

void outdata(int array[], int array_len[], int count) {

  int lcount;		/* �f�[�^�z��̓Y�����J�E���^�����s�J�E���^ */
  int tcount;		/* �E�����ɂ��邽�߂̋󔒕����}���Ɏg���J�E���^ */

  for(lcount = 0; lcount <= count; lcount++) {
    for(tcount = 0; tcount <= 5 - array_len[lcount]; tcount++)		/* 5����array_len[lcount]�� */
      printf("\x20");							/* �������������󔒂����� */
    printf("%d ", array[lcount]);					/* ���ꂩ��f�[�^�{�̂��o�� */

    if(lcount % 10 == 9) 	/* �f�[�^�Y�����̈�̈ʂ�9�̂Ƃ��ɏo�͌�A���s���� */
      printf("\n");
  }
}

