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
		cout << "えくせれんと" << endl;
		break;

	case 1:
		cout << "ふぁいん" << endl;
		break;

	case 2:
		cout << "のーまる" << endl;
		break;

	case 3:
		cout << "なっとそぅうぇる" << endl;
		break;

	case 4:
		cout << "とぅばぁっど..." << endl;
		break;
	
	}

}
