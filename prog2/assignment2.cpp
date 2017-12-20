//
// assignment2.cpp
//
// Kusdavletov Ernar, 20152008, kusdavletov@gmail.com
//

#include <iostream>
#include <stdexcept>
#include <list>
#include <stack>
#include <limits>
#include "LinkedBinaryTree.h"
#include "Symbol.h"
#include "assignment2.h"

LinkedBinaryTree<Symbol> parsePostfixExpression(list<string> tokens) {
    if (tokens.size() == 0) throw runtime_error("Invalid expression.");
    stack<LinkedBinaryTree<Symbol> > temp;
    list<string>::iterator it = tokens.begin();
    int s = tokens.size();
    for (int i = 0; i < s; i++){
        Symbol sm = *it;
        if (sm.isOperator()){
            if (temp.size() < 2) throw runtime_error("Invalid expression.");
            LinkedBinaryTree<Symbol> acc;
            acc.addRoot();
            *acc.root() = sm;
            acc.attachRightSubtree(acc.root(), temp.top());
            temp.pop();
            acc.attachLeftSubtree(acc.root(), temp.top());
            temp.pop();
            temp.push(acc);
        }
        else if (sm.isConstant() || sm.isVariable()){
            LinkedBinaryTree<Symbol> acc1;
			acc1.addRoot();
			*acc1.root() = sm;
			temp.push(acc1);
        }
        else
            throw runtime_error("Invalid expression.");
        ++it;
    }
    LinkedBinaryTree<Symbol> fin = temp.top();
    temp.pop();
    if (temp.size() != 0) throw runtime_error("Invalid expression.");
    return fin;
}

void inorder(const LinkedBinaryTree<Symbol>::Position pos){
    if((*pos).isVariable() || (*pos).isConstant())
		cout << *pos;
    else {
		cout << "(";
		inorder(pos.left());
		cout << " " << *pos << " ";
		inorder(pos.right());
		cout << ")";
	}
}

void print_inorder(const LinkedBinaryTree<Symbol>& tree){
    inorder(tree.root());
}

void postorder(const LinkedBinaryTree<Symbol>::Position pos){
    if (!pos.isNull()) {
        postorder(pos.left());
        postorder(pos.right());
        cout << *pos << " ";
    }
}

void print_postorder(const LinkedBinaryTree<Symbol>& tree){
    postorder(tree.root());
}

int minDepth(const LinkedBinaryTree<Symbol>::Position pos, const Symbol& sym, int level){
    if (pos.isNull())
        return 0;
    if(*pos == sym)
        return level;
    int left = minDepth(pos.left(), sym, level + 1);
    int right = minDepth(pos.right(), sym, level + 1);
    if (left == 0)
        if (right != 0)
            return right;
    if (right == 0)
        if (left != 0)
            return left;
    return min(left, right);
}

int findMinimumDepth(const LinkedBinaryTree<Symbol>& tree, const Symbol& sym){
    if (tree.empty())
        return -1;
    Symbol s = *tree.root();
    if (s == sym)
        return 0;
    else {
        int n = minDepth(tree.root(), sym, 0);
        return (n == 0) ? (-1) : n;
    }
}

void subs(const LinkedBinaryTree<Symbol>::Position pos, const Symbol& variable, const Symbol& constant){
    if (!pos.isNull()){
        if (*pos == variable)
            *pos = constant;
        subs(pos.left(), variable, constant);
        subs(pos.right(), variable, constant);
    }
}

void substitute(const LinkedBinaryTree<Symbol>& tree, const Symbol& variable, const Symbol& constant){
    subs(tree.root(), variable, constant);
}

void simplify(LinkedBinaryTree<Symbol>::Position root, LinkedBinaryTree<Symbol>& tree) {
	if(root.left().isNull() && root.right().isNull())
        return;
    simplify(root.left(), tree);
    simplify(root.right(), tree);
	if((*root.left()).isConstant() && (*root.right()).isConstant()){
		int left = (*root.left()).getConstant();
		int right = (*root.right()).getConstant();
		int fin = (*root).compute(left, right);
		Symbol temp = fin;
		*(root.right()) = temp;
		tree.removeAboveExternal(root.left());
	}
	else
        return;
}

void simplify_subtree(LinkedBinaryTree<Symbol>& tree) {
    if (!tree.empty())
        simplify(tree.root(), tree);
}
