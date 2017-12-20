//
// LinkedBinaryTree.h (Version 1.0)
//
// Kusdavletov Ernar, 20152008, kusdavletov@gmail.com
//

#ifndef ASSIGNMENT2_LINKEDBINARYTREE
#define ASSIGNMENT2_LINKEDBINARYTREE

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <list>

using namespace std;

template<typename Elem>
class LinkedBinaryTree{
    protected:
        struct Node{
            Elem elem;
            Node* parent;
            Node* left;
            Node* right;
            Node() : elem(), parent(NULL), left(NULL), right(NULL) {}
        };
    public:
        class Position{
            private:
                Node* v;
            public:
                Position(Node* v1 = NULL) : v(v1) {}
                Elem& operator*() const{
                    return v -> elem;
                }
                Position left() const{
                    return Position(v -> left);
                }
                Position right() const{
                    return Position(v -> right);
                }
                Position parent() const{
                    return Position(v -> parent);
                }
                bool isRoot() const{
                    return v -> parent == NULL;
                }
                bool isExternal() const{
                    return v -> left == NULL && v -> right == NULL;
                }
                bool isNull() const{
                    return v == NULL;
                }
                friend class LinkedBinaryTree;
        };
        typedef list<Position> PositionList;
    public:
        LinkedBinaryTree() : root_pnt(NULL), num(0) {}
//        ~LinkedBinaryTree(){
//            removeSubtree(root());
//        }
        int size() const{ return num; }
        bool empty() const{ return num == 0; }
        Position root() const{ return Position(root_pnt); }
        PositionList positions() const{
            PositionList pl;
            preorder(root_pnt, pl);
            return PositionList(pl);
        }
        void addRoot(){
            if (!empty()) throw runtime_error("Root already exists!");
            root_pnt = new Node;
            num = 1;
        }
        void expandExternal(const Position& p){
            Node* v1 = p.v;
            if (v1 == NULL) throw runtime_error("Node of p is NULL");
            if (v1 -> left != NULL || v1 -> right != NULL) throw runtime_error("p is an internal node");
            v1 -> left = new Node;
            v1 -> right = new Node;
            v1 -> left -> parent = v1;
            v1 -> right -> parent = v1;
            num = num + 2;
        }
        Position removeAboveExternal(const Position& p){
            Node* w = p.v;
            if (w == NULL) throw runtime_error("Node of p is NULL");
            if (w -> left != NULL || w -> right != NULL) throw runtime_error("p is an internal node");
            if (w == root_pnt){
                delete w;
                num = num - 1;
                return Position(NULL);
            }
            Node* v = w -> parent;
            Node* sibling = (w == v -> left ? v -> right : v -> left);
            if (v == root_pnt){
                root_pnt = sibling;
                sibling -> parent = NULL;
            }
            else {
                Node* gparent = v -> parent;
                if (v == gparent -> left)
                    gparent -> left = sibling;
                else
                    gparent -> right = sibling;
                sibling -> parent = gparent;
            }
            delete w;
            delete v;
            num = num - 2;
            return Position(sibling);
        }
        int height() const;
        void attachLeftSubtree(const Position& p, LinkedBinaryTree& subtree);
        void attachRightSubtree(const Position& p, LinkedBinaryTree& subtree);
        void removeSubtree(const Position& p);
    protected:
        void preorder(Node* v, PositionList& pl) const;
        int maxHeight(Node* v) const;
    private:
        Node* root_pnt;
        int num;
};

template <typename Elem>
void LinkedBinaryTree<Elem>::preorder(Node* v, PositionList& pl) const{
    if (v != NULL)
        pl.push_back(Position(v));
    if (v -> left != NULL)
        preorder(v -> left, pl);
    if (v -> right != NULL)
        preorder(v -> right, pl);
}

template <typename Elem>
int LinkedBinaryTree<Elem>::maxHeight(Node* v) const{
   if (v == NULL)
       return 0;
   else{
       int leftHeight = maxHeight(v -> left);
       int rightHeight = maxHeight(v -> right);
       return 1 + max(leftHeight, rightHeight);
   }
}

template <typename Elem>
int LinkedBinaryTree<Elem>::height() const{
    if (empty()) throw runtime_error("Tree is empty");
    return maxHeight(root_pnt) - 1;
}

template <typename Elem>
void LinkedBinaryTree<Elem>::attachLeftSubtree(const Position& p, LinkedBinaryTree& subtree){
    if (!p.left().isNull()) throw runtime_error("Node is not empty");
    if (subtree.empty()) throw runtime_error("subtree is empty");
    Node* temp = subtree.root_pnt;
    p.v -> left = temp;
	temp -> parent = p.v;
	num = num + subtree.num;
	subtree.num = 0;
}

template <typename Elem>
void LinkedBinaryTree<Elem>::attachRightSubtree(const Position& p, LinkedBinaryTree& subtree){
    if (!p.right().isNull()) throw runtime_error("Node is not empty");
    if (subtree.empty()) throw runtime_error("subtree is empty");
    Node* temp = subtree.root_pnt;
    p.v -> right = temp;
	temp -> parent = p.v;
	num = num + subtree.num;
    subtree.num = 0;
}

template <typename Elem>
void LinkedBinaryTree<Elem>::removeSubtree(const Position& p){
    if (p.isNull())
        return;
    else{
        Node* temp = p.v;
        delete temp;
        temp = NULL;
        num = num - 1;
        removeSubtree(p.left());
        removeSubtree(p.right());
    }
}

#endif //ASSIGNMENT2_LINKEDBINARYTREE
