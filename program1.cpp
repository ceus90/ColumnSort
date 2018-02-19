#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <cctype>
#include <ctime>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


void main()
{
	srand(time(NULL));
	short int value = 0;
	std::ofstream myfile;
	myfile.open("test.txt", std::ofstream::out | std::ofstream::app);
	if (myfile.is_open())
	{
		for (int i = 0; i <= 100000; ++i) {
			value = rand();
			cout << value << "\n";
			myfile << value << "\n";
		}
		myfile.close();
	}

	else cout << "No such file";
	getchar();
}