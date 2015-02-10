/*��\�[�g�y�ы��ʕ������̑���A����̂m���񂪉��񌻂�邩�����߂�*/
/*�t�@�C������ǂݍ��񂾃f�[�^���X�y�[�X�A�^�u�A���s�����̂ǂꂩ�ŋ�؂���*/
/*�P��P�ʂƂ��A�\�[�g���s���`���ɂȂ��Ă���*/
/*�����萔GRAM��ύX���邱�Ƃ�1-gram,2-gram,3-gram�����ꂼ�ꋁ�߂���*/

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

  int i, n;		/*�J�E���^�ϐ�*/
  int c_arr[N];		/*���ʕ������\���i�[����z��*/
  static unsigned char *p_let[N], *work[N], let[N][256];
  /*p_let�͊e�P��̊i�[����Ă���A�h���X���w���|�C���^�Awork�̓\�[�g���W���[�����Ŏg����Ɨ̈�A
  let�֎��ۂɊe�P�ꂪ�i�[�����B�i�[�ł���P���255���ȓ��̂��̂��P�O�O�O�܂ŁB*/

  for (n = 0; n < N; n++) {		/*���͕����񂩂�P���؂�o������*/
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

  /*���ʕ����������߂�B*/
  for (i = 0; i < n; i++) {
    if(i == n - 1) {		/*�Ō�̒P��̋��ʕ������͂O�Ƃ���B*/
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
    c_arr[i] = count;		/*���ʂ����ʕ������\�Ɋi�[�B*/
    count = 0;
  }
}

void cntnum(int n, int c_arr[], unsigned char *p_let[]) {

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
      printf("%s\t%d\t" ,res[j] ,gc_arr[j]);
      j++;					/*�A�����r�؂��̂ł����C���N�������g����*/
      if((j % 10) == 0) printf("\n");
    }

    else if(strlen(p_let[i]) >= GRAM) {		/*�P�����o�ꂷ�镶����GRAM�ȏ�̒P����J�E���g����*/
      for(count = 0; count <= GRAM-1; count++)
        sscanf((p_let[i]+count) ,"%c" ,&g_let[j][count]);
      res[j] = g_let[j];
      gc_arr[j]++;
      printf("%s\t%d\t" ,res[j] ,gc_arr[j]);
      j++;					/*�����C���N�������g����*/
      if((j % 10) == 0) printf("\n");
    }
  }
}
