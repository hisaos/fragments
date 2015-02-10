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
		cout << "‚¦‚­‚¹‚ê‚ñ‚Æ" << endl;
		break;

	case 1:
		cout << "‚Ó‚Ÿ‚¢‚ñ" << endl;
		break;

	case 2:
		cout << "‚Ì[‚Ü‚é" << endl;
		break;

	case 3:
		cout << "‚È‚Á‚Æ‚»‚£‚¤‚¥‚é" << endl;
		break;

	case 4:
		cout << "‚Æ‚£‚Î‚Ÿ‚Á‚Ç..." << endl;
		break;
	
	}

}
