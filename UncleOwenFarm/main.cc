#include <iostream>
#include "Android.h"

using namespace std;

int main(int argc, char const *argv[]) {

	Android android("HC-2", 280);

    cout << android << endl;
	
	Android android2("HC-2", 340);

    cout << android2 << endl;



	return 0;
}
