#include<iostream>
#include<string>

using namespace std;

class kneco

{
	string name;
public:
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

	kneco x;
	x.scream();

	x.setname("�W�W");
	x.scream();
}

