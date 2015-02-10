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
		cout << "にゃあ。我輩は" << name << "である。" << endl;
}

};

int main()

{

	kneco x("ジジ");
	x.scream();

	kneco y;
	y.setname("ミィ");
	y.scream();
}

