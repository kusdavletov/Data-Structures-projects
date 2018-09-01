#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include "ArrayCompleteTree.h"

using namespace std;

int main(){
    ArrayCompleteTree<char> tree(2);
    cout << tree.size() << endl;
    tree.addLast('a');
    tree.addLast('b');
    tree.addLast('c');
    tree.addLast('d');
    cout << tree.size() << endl;
    cout << *tree.root() << endl;
    cout << *tree.last() << endl;
    cout << *(tree.parent(tree.last())) << endl;
    cout << *(tree.left(tree.root())) << endl;
    cout << tree.isRoot(tree.root()) << endl;
    return 0;
}
