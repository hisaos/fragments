#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void datain(int *num);
void copy(char *text);



int main() {
  
  int i,j;
  int num = 0;
  char *text;
  FILE *fwp;

  datain(&num);
  printf("\n number of letters: %d\n" ,num);
 
  text = (char *)malloc(num);

  copy(text);

  fwp = fopen("testtxt.txt","w");
  
  for(j = 0; j <= num; j++) {
    for(i = j; *(text+i); i++)
      fprintf(fwp,"%c",*(text+i));
    fprintf(fwp,"\n");
  }

  return 0;
}

void datain(int *num) {

  FILE* frp;		/*�f�[�^�t�@�C���|�C���^*/
  char line[80];	/*fgets�Ńt�@�C������ǂ�ł���Ƃ��ɁA�s���i�[����o�b�t�@*/
  int i;		/*�t�@�C���̕������𐔂��郋�[�v�Ŏg���J�E���^�B*/
  char *str;		/*�t�@�C���̕������𐔂��郋�[�v�Ŏg���ǂݍ��񂾍s�������|�C���^�B*/

  frp = fopen("esslf10.txt", "r");	/*�f�[�^�t�@�C����ǂݏo�����[�h�ŊJ��*/

/*�t�@�C���̏I���ɒB����܂Ń��[�v*/
  while(fgets(line, sizeof(line), frp) != NULL) {
    str = line;
    for(i = 0; str[i]; i++)
      (*num)++;
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

