#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{
	long int seed;
	int n_t = 500;
	
	cout << n_t << endl;
	seed = time(0);
	for (int j = 0; j < n_t; ++j) {
		srand48(seed);
		cout << seed << endl;
		for (int i = 0;  i < 1000; ++i) {
			long  i1 = mrand48();
			if      (i1 < -1000000L) { i1 = (i1 / 10000) ; }
			else if (i1 >  1000000L) { i1 = (i1 / 10000) ; }
			long  i2 = mrand48();
			if      (i2 < -1000000L) { i2 = (i2 / 10000) ; }
			else if (i2 >  1000000L) { i2 = (i2 / 10000) ; }
			if (i1 < i2) {
				cout  << " " << i1 << " " << i2  ;
			} else {
				cout  << " " << i2 << " " << i1 ;
			}
		}
		cout << endl;
		seed = mrand48();
	}
}

