#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int main()

{
	
	srand((unsigned)time(NULL));
	
	int x;
	x = rand() % 5;
	
	switch(x) {

	case 0:
		cout << "����������" << endl;
		break;

	case 1:
		cout << "�ӂ�����" << endl;
		break;

	case 2:
		cout << "�́[�܂�" << endl;
		break;

	case 3:
		cout << "�Ȃ��Ƃ���������" << endl;
		break;

	case 4:
		cout << "�Ƃ��΂�����..." << endl;
		break;
	
	}

}
