

//
// CircularList.h (Version 1.0)
//
// Kusdavletov Ernar, 20152008, kusdavletov@gmail.com
// Moreover, please describe the implementation of your functions here.

#ifndef ASSIGNMENT1_CIRCULAR_LIST
#define ASSIGNMENT1_CIRCULAR_LIST

#include <iostream>
#include <stdexcept>

using namespace std;


template<typename Elem>
class CNode{        // circularly linked list node
    public:
        Elem elem;      // linked list element value
        CNode *next;    // next item in the list

};

template<typename Elem>
class CircularList{
    private:
        CNode<Elem> *cursor;
        static CNode<Elem> *av;
        CNode<Elem>* GetNode();
        void RetNode(CNode<Elem> *&x);
        unsigned count;
    public:
        CircularList();     // constructor
        ~CircularList(){    // destructor
            cleanup();
        }
        bool empty() const{ // checking whether the list is empty
            return cursor == NULL;
        }
        Elem& front() const; // first element
        Elem& back() const;  // last element
        void advance(){      // advance cursor to the next element
            cursor = cursor -> next;
        }
        void add(const Elem& e); // add an element after the cursor
        void remove();       // remove the node after the cursor
        int size() const;    // return the number of elements in the list
        void reverse();      // reverse the circular list
        void cleanup();      // free the memory
};

template<typename Elem>
CNode<Elem>* CircularList<Elem>::av = 0;

template<typename Elem>
CNode<Elem>* CircularList<Elem>::GetNode(){
    CNode<Elem> *x;
    if (av){
        x = av;
        av = av -> next;
    }
    else{
        x = new CNode<Elem>;
    }
    return x;
}

template<typename Elem>
void CircularList<Elem>::RetNode(CNode<Elem> *&x){
    x -> next = av;
    av = x;
    x = 0;
}

template<typename Elem>
CircularList<Elem>::CircularList(){     // constructor
    cursor = NULL;
    count = 0;
}

template<typename Elem>
Elem& CircularList<Elem>::front() const{
    if (empty())
        throw runtime_error("List is empty");
    return cursor -> next -> elem;
}

template<typename Elem>
Elem& CircularList<Elem>::back() const{
    if (empty())
        throw runtime_error("List is empty");
    return cursor -> elem;
}

template<typename Elem>
void CircularList<Elem>::add(const Elem& e){ // add after cursor
    CNode<Elem> *new_node = GetNode(); // create a new node
    new_node -> elem = e;
    if (cursor == NULL){ // list is empty?
        new_node -> next = new_node; // v points to itself
        cursor = new_node; // cursor points to v
    }
    else { // list is nonempty?
        new_node -> next = cursor -> next; // link in v after cursor
        cursor -> next = new_node;
    }
    count += 1;
}

template<typename Elem>
void CircularList<Elem>::remove(){ // remove node after cursor
    if (empty())
        throw runtime_error("List is empty");
    CNode<Elem> *old = cursor -> next; // the node being removed
    if (old == cursor){ // removing the only node?
        cursor = NULL; // list is now empty
    }
    else {
        cursor -> next = old -> next; // link out the old node
    }
    count -= 1;
    RetNode(old);
}

template<typename Elem>
int CircularList<Elem>::size() const{
    return count;
}

template<typename Elem>
void CircularList<Elem>::reverse(){
    CircularList T;
    while (!empty()){
        Elem temp = front();
        remove();
        T.add(temp);
    }
    while (T.size() != 0){
        Elem temp = T.back();
        add(temp);
        for (int i = 1; i < T.count; i++)
            T.advance();
        T.remove();
    }
}

template<typename Elem>
void CircularList<Elem>::cleanup(){
    if (cursor){
        CNode<Elem> *first = cursor -> next;
        cursor -> next = av;
        av = first;
        cursor = 0;
    }
    count = 0;
}

#endif //ASSIGNMENT1_CIRCULAR_LIST
