/*�Y���z����\������v���O�����̖�������*/
/*�ڔ����̐擪�|�C���^�𓮓I�Ɋm�ۂ����z��ւƏ��ԂɊi�[����@�\�̂�*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void datain(int *num);
void copy(char *text);

typedef struct {	/*���̍\���͓̂��I�Ƀ|�C���^�z����m�ۂ��邽�߂ɕK�v*/
  char *text;
}SUFF;  

int main() {
  
  int i;		/*int�^�J�E���g�ϐ�*/
  int num = 0;		/*��������ێ�����*/
  char *text;		/*���I�Ɋm�ۂ����z��text�ɓǂݍ��񂾃e�L�X�g�̖{�̂�����*/
  SUFF *suff;		/*�|�C���^�z���text���Ŋe�ڔ����̐擪���w��*/

  datain(&num);		/*���I�Ɋm�ۂ���z��̃T�C�Y�����肷�邽�߂Ƀe�L�X�g�̕������𐔂��グ��B*/

  text = (char *)malloc(num);	/*�z��text���m��*/
  copy(text);			/*text�ɓǂݍ��񂾕�������i�[����*/

  suff = (SUFF *)malloc(num);	/*�|�C���^�z��suff���m��*/

  for(i = 0; i <= num; i++)	/*suff�̊e�v�f�ɐڔ����̐擪�̃A�h���X���i�[*/
    suff[i].text = (text+i);

  return 0;
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

