#include<iostream>
using namespace std;

class rocket {

	int f,v,h;

	public:

	rocket(int a,int b,int c){
		f = a;
		v = b;
		h = c;
		}

	rocket(){ 
		f = 100;
		v = 0;
		h = 0;
	}

	void accel(int n){
	
		if(n < 0){
			n = 0;
		}

		else if(n > f){
			n = f;
		}

		f -= n;
		v += n;
		h += v;
	}

	void report() const{
		cout << "�󋵕�" << endl;
		cout << "�R��" << f << endl;
		cout << "���x" << v << endl;
		cout << "���x" << h << endl;
		cout << endl;
	}
};

int main()
{
	rocket x;
	rocket y(277,31,48);
	int i;
	int b;

	cout << "���P�b�g�𑀏c���Ă��������B�����͂R�񂾂��ł��܂��B" << endl;
	cout << "���P�b�gx" << endl;
	x.report();
	cout << "���P�b�gy" << endl;
	y.report();

	for(i=0;i<3;i++) {
	cout << "x�̔R�����˗ʂ���́F" << endl;
	cin >> b;
	x.accel(b);
	x.report();
	
	cout << "y�̔R�����˗ʂ���́F" << endl;
	cin >> b;
	y.accel(b);
	y.report();
	}

}

