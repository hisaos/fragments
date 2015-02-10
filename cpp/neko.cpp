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
		cout << "にゃあ。我輩は" << name << "である。" << endl;
}

};

int main()

{

	kneco x;
	x.scream();

	x.setname("ジジ");
	x.scream();
}

