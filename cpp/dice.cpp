#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int main()

{
	int i;
	srand((unsigned)time(NULL));
	
	for(i = 0 ; i < 10 ; i++) {
	
		cout << ( rand() % 6 ) + 1 << endl;
	
	}

}
