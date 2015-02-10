#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INDEX 15000 	/*���͂��鐮���̍ő��*/
#define SORT_METHODS 2		/*�I���ł��鐮��@�̐�*/

void indata(long ar[], int ar_len[], int *index);		/*�t�@�C�����͊֐�*/
void bubble_sort(int left, int index ,long ar[], int ar_len[]);	/*�o�u���\�[�g�֐�*/
void quick_sort(int left, int right, long ar[], int ar_len[]);	/*�N�C�b�N�\�[�g�֐�*/
int pivot(int left, int right, long ar[]);			/*�N�C�b�N�\�[�g�̎��v�f����֐�*/
int swap(int i1, int i2, long ar[], int ar_len[]);		/*�l�����֐�*/
void outdata(long ar[], int ar_len[], int index);		/*���ʏo�͊֐�*/

int main(int argc, char* argv[]) {

/*main�͐������i�[����z��̐錾�A�\�[�g���W���[���̃G���g���|�C���g�i�[�A*/
/*����@�̑I�������A����@�I���ɑ΂���G���[�����A�e�֐��̌Ăяo�����s���B*/

  int index = 0;					/*indata�œ��͂��ꂽ�����̌���ێ�*/
  int num;						/*����@�̑I���Ɏg��*/
  void (*sel[SORT_METHODS]) (int ,int ,long*, int*);	/*�\�[�g�֐��̃G���g���|�C���g���i�[����void�^�z��*/
  char line[10];					/*����@��Θb�����Ō��肷��ꍇ�A�R���\�[���œ��͂��ꂽ��������i�[����*/
  char sort_name[SORT_METHODS][20];		/*���ʏo�͌�ɏ�����������@��\�����邽�߁A����@�̖��̂��i�[���Ă���*/
  long ar[MAX_INDEX];				/*���͂��������Q���i�[����z��*/
  int ar_len[MAX_INDEX];			/*ar�Ɋi�[���鐮���̕��������L�^����z��*/

/*����@�̖��̂�z��sort_name�Ɋi�[*/
  strcpy(sort_name[0],"bubble sort");
  strcpy(sort_name[1],"quick sort");

/*sel[0]��bubble_sort�Asel[1]��quick_sort�̃G���g���|�C���g���i�[*/
  sel[0] = bubble_sort;
  sel[1] = quick_sort;

/*��Ƀt�@�C������̓ǂݍ��݂��ς܂��Ă���*/
  indata(ar, ar_len, &index);

/*����@�����肷�鏈��*/
/*�������������ꍇ*/
  if(argc > 1) {
    num = atoi(*++argv);			/*������argv����Ƃ��ė���atoi����num�Ɋi�[*/
    if(num >= 0 && num <= SORT_METHODS-1)	/*������0��1�Ȃ�A�\�[�g���s*/
      (*sel[num])(0, index, ar, ar_len);
    else {					/*������0��1�ȊO�Ȃ�A�v���O�������I��*/
      printf("0����%d�܂ł̒l����͂��Ă��������",SORT_METHODS-1);
      exit(0);
    }
  }
/*�������Ȃ������ꍇ�̑Θb����*/
  else {
    printf("10000���x�̐����𐮗񂵂܂��B����@��I�����Ă��������B\n");
    while(1) {
      printf("0:bubble sort\n");
      printf("1:quick sort\n");
      num = atoi(fgets(line, sizeof(line), stdin));	/*fgets�œ��͂������ʂ�atoi����num�Ɋi�[*/
      if(num >= 0 && num <= SORT_METHODS-1) {		/*���͂�0��1�Ȃ�A�\�[�g�����s���ă��[�v�E�o*/
        (*sel[num])(0, index, ar, ar_len);
        break;
      }
/*���͂�0��1�ȊO�Ȃ�A�G���[���b�Z�[�W���o���āA�ē��͂�����*/
      else {
        printf("0����%d�܂ł̒l����͂��Ă��������\n",SORT_METHODS-1);
        continue;
      }
    }
  }

/*����I����Aoutdata���Ă�Ō��ʂ�[���ɏo��*/
  outdata(ar, ar_len, index);
/*�I����������@���o�͂��āA�I���B*/
  printf("%s�Ő��񂳂�܂����B\n",sort_name[num]);

  return 0;
}

void indata(long ar[], int ar_len[], int *index) {

/*indata�́A���炩���ߗp�ӂ��ꂽ�A�����Q��ۑ����Ă���t�@�C��"longdata.txt"�ɃA�N�Z�X���A*/
/*�����ƁA�����̕����������ꂼ��z��ar[],ar_len[]�Ɋi�[����B*/

  FILE* frp;		/*longdata.txt�p�̃t�@�C���|�C���^*/
  int add = 0;		/*fgets�œǂ񂾍s��sscanf�Ő����P���ɂ��Ċi�[����Ƃ��ɁA�s�̂ǂ�����ǂނ������肷��J�[�\��*/
  char data[10];	/*fgets�œǂ񂾍s����sscanf�Ő����P���ɂ��Đ؂�o���Ƃ��g���o�b�t�@*/
  char line[80];	/*fgets��longdata.txt����ǂ�ł���Ƃ��ɁA�s���i�[����o�b�t�@*/

  frp = fopen("longdata.txt", "r");	/*longdata.txt��ǂݏo�����[�h�ŊJ��*/

/*�t�@�C���̏I���ɒB����܂Ń��[�v*/
  while(fgets(line, sizeof(line), frp) != NULL) {

/*line+add�̈ʒu�œǂ߂Ȃ��Ȃ�܂Ń��[�v*/
    while(sscanf((line+add), "%s" ,&data) == 1) {
      add = add + strlen(data) + 1; 	/*�ǂ񂾐����̕������{�󔒂P�����������J�[�\�������炷*/
      ar[*index] = atoi(data);		/*data�Ɋi�[����Ă��鐮���������atoi�ŕϊ����āAar[]�Ɋi�[*/
      ar_len[*index] = strlen(data);	/*�����̕������������Ɋi�[����*/
      (*index)++;			/*ar[]�Aar_len[]�̓Y�������P�i�߂�*/
    }
    add = 0;	/*���[�v��E�o������add=0�Ƃ��āA�܂����̍s�̐擪����sscanf�Ő�����؂�o��*/
  }
  fclose(frp);	/*�t�@�C����ǂݐs��������longdata.txt�����*/
}

void bubble_sort(int left, int index, long ar[], int ar_len[]) {

/*bubble_sort�̓t�@�C��������͂��ꂽ�����̌�index,*/
/*�������i�[���ꂽ�z��ar�A�e�����̕��������i�[���ꂽ�z��ar_len��*/
/*main����󂯎��A�o�u���\�[�g�ɂ����ar,ar_len�̐�����s���B*/
/*����left�͔z�񒆂Ń\�[�g����͈͂̍��[���w�肷�邪�֐��̃f�B�X�p�b�`���s�����߂ɓ����ꂽ�_�~�[�����ɓ������B*/

  int count_in, count_ex;
/*count_in�̓o�u���\�[�g�̓������[�v�Acount_ex�͊O���̃��[�v�̃J�E���^�B*/

  for(count_ex = index; count_ex > 0; count_ex--) {
    for(count_in = left; count_in < count_ex; count_in++) {
      if(ar[count_in] > ar[count_in + 1])			/*�E�̗v�f��荶�̗v�f���傫����΁A�������s*/
	swap(count_in, count_in+1, ar, ar_len);		/*�z��̗v�f�Ԃ̌����͕ʊ֐�swap�ōs���B*/
    }
  }
}

void quick_sort(int left, int right, long ar[], int ar_len[]) {

/*quick_sort�͐������i�[���ꂽ�z��ar�A�e�����̕��������i�[���ꂽ�z��ar_len��*/
/*�Ăяo�����̊֐�����󂯎��A�z�񒆂̍��[left�A�E�[right�Ŏw�肳���͈͂ɑ΂���*/
/*�N�C�b�N�\�[�g�ɂ��ar,ar_len�̐�����s���B*/

  int p_index, p_val;		/*p_index�͎��v�f�̓Y�����ԍ��Ap_val�͎��v�f���̂��̂��i�[����B*/
  int l_edge = left;		/*�����͈͂̎��v�f��荶�͈̔͂𒲍�����J�[�\��*/
  int r_edge = right;		/*�����͈͂̎��v�f���܂ށA���v�f���E�͈̔͂𒲍�����J�[�\��*/

  p_index = pivot(left, right, ar);	/*�z�񒆂̎��v�f�̗v�f�ԍ������߂�*/

  if(p_index != -1) {		/*p_index��-1�Ȃ�΁Apivot�Œ��ׂ��͈͂͂��ׂē��������������Ă���̂Ń\�[�g���X�L�b�v*/
    p_val = ar[p_index];	/*���v�f��p_val�Ɋi�[*/

    while(1) {	/*�z��̕������s�����[�v*/

/*l_edge�͏�������͈͂̍��[����A���v�f���傫�ȗv�f��������܂ŉE�ɂ����B*/
/*r_edge�͏�������͈͂̉E�[����A���v�f��菬���ȗv�f��������܂ō��ɂ����B*/
      while(ar[l_edge] < p_val) l_edge++;
      while(ar[r_edge] >= p_val) r_edge--;

/*l_edge��r_edge���E�Ȃ�A���͈̔͂ł̃\�[�g�͏I���B*/
      if(l_edge > r_edge) break;

/*�\�[�g���I����Ă��Ȃ��Ȃ�A���̎��_�ł�l_edge��r_edge�̈ʒu�ɂ���v�f����������B*/
      swap(r_edge, l_edge, ar, ar_len);

/*������Al_edge�Ar_edge�̗��������炵�āA���[�v����B*/
      l_edge++;
      r_edge--;
    }
/*�����͈͂̕�����A�����������͈̔͂ƉE�͈̔͂ɂ��Ă��ꂼ��quick_sort���ċA�Ăяo�����ă\�[�g��i�߂�*/
    quick_sort(left, l_edge - 1, ar, ar_len);
    quick_sort(l_edge, right, ar, ar_len);
  }
}

int pivot(int left, int right, long ar[]) {

/*pivot�́Aquick_sort����Ă΂�Aquick_sort����n��������left��right�ɂ��w�肳���*/
/*�z�񒆂̃N�C�b�N�\�[�g���s���͈͂ɂ����鎲�v�f���w�肷��֐�*/
/*�ŏ��Ɍ������Q��ނ̐��̂����A�傫���ق������v�f�Ƃ���B*/
/*quick_sort�ɂ́A���v�f�̓Y�����ԍ�p_index���Ԃ����B*/

  int cursor = left;	/*ar[cursor]�Ɣ͈͓��̐擪�̒lar[left]�Ƃ̑召���r����*/
  int p_index;		/*���v�f�̓Y�����ԍ��B�͈͓��̒l�����ׂē����������ꍇ�A-1�ƂȂ�*/

/*�͈͓��̐擪�̒lar[left]��ar[cursor]���قȂ�l�ɂȂ�܂ŁAcursor�����炵�Ă���*/
  while(ar[cursor] == ar[left] && cursor <= right) cursor++;

/*���[�v��E�o��Ap_index������*/
  if(cursor > right) p_index = -1;				/*cursor��right�𒴂��Ă����Ƃ��A�S��������������-1*/
  else if(ar[cursor] > ar[left]) p_index = cursor;	/*ar[cursor]>ar[left]�Ȃ�cursor*/
  else p_index = left;						/*ar[cursor]<=ar[left]�Ȃ�left�Ƃ��A*/

  return p_index;	/*quick_sort��p_index��Ԃ�*/
}

int swap(int i1, int i2, long ar[], int ar_len[]) {
/*swap�͌Ăяo�����̃\�[�g�֐�����\�[�g�Ώۂ̔z��ar�ƕ��������i�[���Ă���z��ar_len���󂯎��*/
/*ar[i1]��ar[i2]�Aar_len[i1]��ar_len[i2]�����ꂼ���������֐�*/

  int temp;		/*�l���ꎞ�ޔ����Ă����ϐ�*/

  temp = ar[i2];		/*�z��v�f���̂̌���*/
  ar[i2] = ar[i1];
  ar[i1] = temp;

  temp = ar_len[i2];		/*�z��v�f�̕������̌���*/
  ar_len[i2] = ar_len[i1];
  ar_len[i1] = temp;

  return 0;
}

void outdata(long ar[], int ar_len[], int index) {

/*outdata�͔z��ar[]�A���������i�[�����z��ar_len[]�A�z��̗v�f��index���󂯎��*/
/*ar[]�̐擪���珇�ɁA�P�s�P�O���A����ar_len[]�Ɋi�[���ꂽ�������̏��𗘗p���ĉE�l�ɂ��Ȃ���*/
/*�����Q�𐮗񂵂����ʂ�\������֐�*/

  int lcount;		/*�z��̉��ڂ܂ŕ\���������ێ�����*/
  int tcount;		/*�����̕\�����E�l�ɂ���X�y�[�X�����郋�[�v�Ɏg���J�E���^*/

/*lcount��index�ɂȂ�܂ŁA�z��̓��e��\�����Â��郋�[�v*/
  for(lcount = 0; lcount <= index; lcount++) {
    for(tcount = 0; tcount <= 5-ar_len[lcount]; tcount++)	/*5-ar_len[]�̋󔒂����āA�\�����E�l�ɂ���*/
      printf("\x20");
    printf("%d ", ar[lcount]);
    if(lcount % 10 == 9) 	/*������\�����Ă���lcount�̂P�̈ʂ�9��������A���s����*/
      printf("\n");
  }
  printf("\n");			/*�\���I����ɂ����s����*/
}

