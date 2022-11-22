#include <iostream>
#include "Matrix.h"
#include "vector.h"
using namespace std;

int main()
{
	TDynamicVector<int> a(5), b(5), c(5);
	cout << a << b << c;
	return 0;
	
	
	
	
	
	/*TDynamicMatrix<int> a(5), b(5), c(5);
	int i, j;

	for (i = 0; i < 5; i++)
		for (j = i; j < 5; j++)
		{
			a[i][j] = i * 10 + j;
			b[i][j] = (i * 10 + j) * 100;
		}
	c = a + b;

	cout << "Matrix a = " << endl << a << endl;
	cout << "Matrix b = " << endl << b << endl;
	cout << "Matrix c = a + b" << endl << c << endl;
	return 0;
 */

}

