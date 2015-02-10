#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>  /* UCHAR_MAX (>= 255) */

#define N 1000
#define GRAM 3

typedef struct {
  unsigned char *text[];
}SUFF;  

void datain(int *num);
void copy(char *text);
void radixsort(int n ,int length ,SUFF *a[] ,SUFF *work[]);
void cmnnum(int n, int c_arr[], SUFF *p_let[]);
void cntnum(int n, int c_arr[], SUFF *p_let[]);

int main() {
  int i, n;
  int c_arr[N];
  int num = 0;
  char *text;
  SUFF *suff,*p_let,*work;

  datain(&num);
  printf("\n number of letters: %d\n" ,num);
  text = (char *)malloc(num);

  copy(text);
  /*
  p_let = (SUFF *)malloc(num);*/
  work = (SUFF *)malloc(num);
  suff = (SUFF *)malloc(num);

  for(i = 0; i <= num; i++)
    suff[num-i].text = (text+i);
/*
  for (n = 0; *(suff[]) < N; n++) {
    if (scanf("%s%*[^ \t\n]", suff[n]) != 1) break;
      p_let[n] = suff[n];
  }
*/
  radixsort(n, num, &suff, &work);
  cmnnum(n, c_arr, &suff);
  cntnum(n, c_arr, &suff);

  return EXIT_SUCCESS;
}

void datain(int *num) {

  FILE* frp;		/*�f�[�^�t�@�C���|�C���^*/
  char line[80];	/*fgets�Ńt�@�C������ǂ�ł���Ƃ��ɁA�s���i�[����o�b�t�@*/
  int i;		/*�t�@�C���̕������𐔂��郋�[�v�Ŏg���J�E���^�B*/
  char *str;		/*�t�@�C���̕������𐔂��郋�[�v�Ŏg���ǂݍ��񂾍s�������|�C���^�B*/

  frp = fopen("testtxt.txt", "r");	/*�f�[�^�t�@�C����ǂݏo�����[�h�ŊJ��*/

/*�t�@�C���̏I���ɒB����܂Ń��[�v*/
  while(fgets(line, sizeof(line), frp) != NULL) {
    str = line;
    for(i = 0; str[i]; i++)
      if(str[i] != '\n' && str[i] != ' ') (*num)++;
  }
  fclose(frp);	/*�ǂݐs��������t�@�C�������*/
}

void copy(char *text) {

  FILE* frp;		/*�f�[�^�t�@�C���|�C���^*/
  char line[80];	/*fgets�Ńt�@�C������ǂ�ł���Ƃ��ɁA�s���i�[����o�b�t�@*/
  int i;		/*�t�@�C���̕������𐔂��郋�[�v�Ŏg���J�E���^�B*/
  char *str;		/*�t�@�C���̕������𐔂��郋�[�v�Ŏg���ǂݍ��񂾍s�������|�C���^�B*/

  frp = fopen("testtxt.txt", "r");	/*�ǂݏo�����[�h�ŊJ��*/

/*�t�@�C���̏I���ɒB����܂Ń��[�v*/
  while(fgets(line, sizeof(line), frp) != NULL) {
    str = line;
    for(i = 0; str[i]; i++) {
      if(str[i] != '\n' && str[i] != ' ') {
        *(text) = str[i];
        text++;
      }
    }
  }
  fclose(frp);	/*�ǂݐs��������t�@�C�������*/
}

void radixsort(int n ,int length ,SUFF *a[] ,SUFF *work[]) {
  int i, j;
  static int count[UCHAR_MAX + 1];

  for (j = length - 1; j >= 0; j--) {
    for (i = 0; i <= UCHAR_MAX; i++) count[i] = 0;
    for (i = 0; i < n; i++) count[a[i][j]]++;
    for (i = 1; i <= UCHAR_MAX; i++) count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) work[--count[a[i][j]]] = a[i];
    for (i = 0; i < n; i++) a[i] = work[i];
  }
}

void cmnnum(int n, int c_arr[], SUFF *p_let[]) {

  int i;
  int count = 0;
  char c1,c2;

  /*���ʕ����������߂�B*/
  for (i = 0; i < n; i++) {
    if(i == n - 1) {		/*�Ō�̒P��̋��ʕ������͂O�Ƃ���B*/
      c_arr[n] = 0;
      break;
    }

    sscanf(*(p_let[i].text),"%c",&c1);
    sscanf(*(p_let[i+1].text),"%c",&c2);
    while(c1 == c2) {
      count++;
      if(sscanf((p_let[i].text)+count,"%c",&c1) != 1) break;
      if(sscanf((p_let[i+1].text)+count,"%c",&c2) != 1) break;
    }
    c_arr[i] = count;		/*���ʂ����ʕ������\�Ɋi�[�B*/
    count = 0;
  }
}

void cntnum(int n, int c_arr[], SUFF *p_let[]) {

  /*���ʕ��������w��̐��ȉ��ɂȂ�܂ł̒P�ꐔ�𐔂���B*/

  int i,j = 0;
  int count = 0;
  int gc_arr[N];
  static unsigned char *res[N], g_let[N][GRAM];

  for (i = 0; i < n; i++)
    gc_arr[i] = 0;

  for (i = 0; i < n; i++) {

    count = 0;

    if(c_arr[i] >= GRAM) {		/*���ʕ�������GRAM�ȏ�*/
      for(count = 0; count <= GRAM-1; count++)
        sscanf((p_let[i]+count) ,"%c" ,&g_let[j][count]);
      res[j] = g_let[j];
      gc_arr[j]++;
      }

    else if(c_arr[i-1] >= GRAM && i >= 1) {	/*���ʕ�������GRAM����*/
      gc_arr[j]++;
      printf("%s\t%d\n" ,res[j] ,gc_arr[j]);
      j++;					/*�A�����r�؂��̂ł����C���N�������g����*/
    }

    else if(strlen(p_let[i]) >= GRAM) {		/*�P�����o�ꂷ�镶����GRAM�ȏ�̒P����J�E���g����*/
      for(count = 0; count <= GRAM-1; count++)
        sscanf((p_let[i]+count) ,"%c" ,&g_let[j][count]);
      res[j] = g_let[j];
      gc_arr[j]++;
      printf("%s\t%d\n" ,res[j] ,gc_arr[j]);
      j++;					/*�����C���N�������g����*/
    }
  }
}
