#include<iostream>
#include<string>

using namespace std;

class kneco

{
	string name;
public:
	kneco(){}

	kneco(string n)
		{
			name = n;
		}

	void setname(string n)
		{
			name = n;
		}

	void scream() const {
		cout << "�ɂႠ�B��y��" << name << "�ł���B" << endl;
}

};

int main()

{

	kneco x("�W�W");
	x.scream();

	kneco y;
	y.setname("�~�B");
	y.scream();
}

