#include <iostream>
#include <stdexcept>
#include "HeapPriorityQueue.h"

using namespace std;


int main(){
	HeapPriorityQueue<int, bool> a;
	HeapPriorityQueue<int, bool> aa;
	//HeapPriorityQueue<int, bool> b(a);
	ArrayCompleteTree<int>::Position pos1;
	ArrayCompleteTree<int>::Position pos2;
	ArrayCompleteTree<int>::Position pos3;
	cout << "Size:" << a.size() << " isEmpty? " << a.empty() << endl;
	pos1 = a.insert(1);
	cout << "Size:" << a.size() << " isEmpty? " << a.empty() << endl;
	pos2 = a.insert(2);
	cout << "Size:" << a.size() << " isEmpty? " << a.empty() << endl;
	pos3 = a.insert(3);
	cout << "Size:" << a.size() << " isEmpty? " << a.empty() << endl;

	cout << "Min:" << a.min() << endl;
	a.removeMin();
	cout << "Min:" << a.min() << " Size:" << a.size() <<  endl;
	a.removeMin();
	cout << "Min:" << a.min() << " Size:" << a.size() <<  endl;
	
	ArrayCompleteTree<int>::Position posa1;
	ArrayCompleteTree<int>::Position posa2;
	ArrayCompleteTree<int>::Position posa3;
	ArrayCompleteTree<int>::Position posa4;
	ArrayCompleteTree<int>::Position posa5;

		
	posa1 = aa.insert(5);
	posa2 = aa.insert(4);
	posa3 = aa.insert(7);
	
	cout << endl << endl << "Min:" << aa.min() << " Size:" << aa.size() << endl;
	posa4 = aa.insert(2);
	posa5 = aa.insert(3);
	
	cout << "Min:" << aa.min() << " Size:" << aa.size() << endl;
	posa3 = aa.replace(posa3,1);
	cout << "Min:" << aa.min() << " Size:" << aa.size() << endl;
	aa.removeMin();
	cout << "Min:" << aa.min() << " Size:" << aa.size()  << "here" << endl;
	
	HeapPriorityQueue<int, bool> b(aa); //////////////
	cout <<  endl << "Min:" << b.min() << " Size:" << b.size() <<  endl;
	b.insert(1);
	aa.insert(21);
	cout << "Min:" << aa.min() << " Size:" << aa.size() <<  endl;
	cout << "Min:" << b.min() << " Size:" << b.size() <<  endl;
}

