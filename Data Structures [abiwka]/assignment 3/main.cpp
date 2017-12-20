#include "matrix.h"
#include <iostream>

// matrix test
using namespace std;

int main()
{
	ifstream A, B;
	A.open("matrix.txt");
	B.open ("matrix2.txt");
/*
	// empty constructor check
	Matrix<int> a (5, 10);
	//a.Print ();

	// create element check
	a.CreateElement (0, 0, 999);
	//a.Print ();
	a.CreateElement (4, 9, 111);
	//a.Print ();
	a.CreateElement (2, 4, 555);
	//a.Print ();

    //swap row/column check
	a.SwapRow (0, 4);
	a.Print ();
	a.SwapCol (0, 9);
	a.Print ();


    // matrix constructor, subtraction and addition check
    Matrix <double> a (5, 7), b (5, 7), c (5, 7), d (5, 7), e (5, 7), f (5, 7);
    a.CreateElement (0, 0, 1);
    b.CreateElement (0, 6, 2);
    b.CreateElement (4, 0, 3);
    c.CreateElement (4, 6, 4);
    d.CreateElement (0, 0, 4);
    e.CreateElement (0, 6, 3);
    e.CreateElement (4, 0, 2);
    f.CreateElement (4, 6, 1);

    (a + b + c - d - e - f).Print ();


    // matrix multiplication check
    Matrix <int> a (A), b (B);

    (a * a).Print ();

*/
    // matrix transpose check
    Matrix < int > a (A);
    a.Print ();
    a.Transpose ();
    a.Print ();

	return 0;
}
