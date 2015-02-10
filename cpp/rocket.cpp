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
		cout << "状況報告" << endl;
		cout << "燃料" << f << endl;
		cout << "速度" << v << endl;
		cout << "高度" << h << endl;
		cout << endl;
	}
};

int main()
{
	rocket x;
	rocket y(277,31,48);
	int i;
	int b;

	cout << "ロケットを操縦してください。加速は３回だけできます。" << endl;
	cout << "ロケットx" << endl;
	x.report();
	cout << "ロケットy" << endl;
	y.report();

	for(i=0;i<3;i++) {
	cout << "xの燃料噴射量を入力：" << endl;
	cin >> b;
	x.accel(b);
	x.report();
	
	cout << "yの燃料噴射量を入力：" << endl;
	cin >> b;
	y.accel(b);
	y.report();
	}

}

