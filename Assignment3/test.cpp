#include <iostream>
#include "ArrayCompleteTree.h"

using namespace std;

int main(){
	//ArrayCompleteTree<int>::LocationAwareEntry a(5,1);
	ArrayCompleteTree<int> a(10);
	cout << a.size() << endl; //0
	a.addLast(5);
	cout << a.size() << endl; //0
	ArrayCompleteTree<int>::Position root(a.root());
	cout << "hasLeft:" << a.hasLeft(root) << " hasRight:" << a.hasRight(root) << " isRoot:" << a.isRoot(root) << endl; //0 0 1
	a.addLast(7);
	cout << " size:" << a.size() << endl;
	cout << "hasLeft " << a.hasLeft(root) << "hasRight " << a.hasRight(root) << "isRoot " << a.isRoot(root) << endl;
	ArrayCompleteTree<int>::Position rootleft(a.left(root));
	cout << "root - left: hasLeft " << a.hasLeft(rootleft) << "hasRight " << a.hasRight(rootleft) << "isRoot " << a.isRoot(rootleft) << endl;
	a.addLast(11);
	cout << a.size() << endl;
	cout << "root: hasLeft " << a.hasLeft(root) << "hasRight " << a.hasRight(root) << "isRoot " << a.isRoot(root) << endl;
	ArrayCompleteTree<int>::Position rootright(a.right(root));
	cout << "root - right: hasLeft " << a.hasLeft(rootright) << "hasRight " << a.hasRight(rootright) << "isRoot " << a.isRoot(rootright) << endl;

	for(int i = 0; i < 10; i++)
	{
		a.addLast(2*i+1);
	}
	cout << a.size() << endl;
	cout << "hasLeft " << a.hasLeft(root) << "hasRight " << a.hasRight(root) << "isRoot " << a.isRoot(root) << endl;
	cout << "root - left: hasLeft " << a.hasLeft(rootleft) << "hasRight " << a.hasRight(rootleft) << "isRoot " << a.isRoot(rootleft) << endl;
	cout << "root - right: hasLeft " << a.hasLeft(rootright) << "hasRight " << a.hasRight(rootright) << "isRoot " << a.isRoot(rootright) << endl;

	a.removeLast();
	a.removeLast();
	a.removeLast();
	a.removeLast();
	cout << a.size() << endl;
	a.cleanup();
	cout << a.size() << endl;
	ArrayCompleteTree<int>::Position last(a.last());

	cout << "last: isRoot " << a.isRoot(last) << " " << last.operator*() << endl;
	cout << "root: isRoot " << a.isRoot(root) << " " << root.operator*() << endl;

	swap(last, root);

	cout << "last: isRoot " << a.isRoot(last) << " " << last.operator*() << endl;
	cout << "root: isRoot " << a.isRoot(root) << " " << root.operator*() << endl;

	ArrayCompleteTree<int>::Position secondroot(a.root());

	cout << "Position == check: " <<  (secondroot == root) << endl;
	cout << "Position == check: " <<  (secondroot == last) << endl;

	cout << a.parent(root).operator*() << endl;
	cout << a.parent(rootleft).operator*() << endl;
	//cout << a.parent(last).operator*() << endl;

	ArrayCompleteTree<int> b(a);
	b.removeLast();
	a.addLast(545);
	cout << b.root().operator*() << endl;
	cout << b.size() << " " << a.size();
//	cout <<  " " << b.size();
}
