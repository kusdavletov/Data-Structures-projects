//
// CircularList.h (Version 1.0)
//
// Kusdavletov Ernar, 20152008, kusdavletov@gmail.com
//
//** pointer cursor:
//Pointer to the last element in the Circular list.
//
//** pointer av:
//Pointer to the first element in the available space list.
//
//** variable count:
//Used to count the number of elements in the Circular list.
//
//** variable av_count;
//Used to count the length of available space list.
//
//** CircularList():
//Constructor of the Circular list, initiates values to zero.
//
//** ~CircularList():
//Destructor of the Circular list, passes everything to available space list and delete the available space list.
//
//** empty() function:
//Check whether the circular list is empty.
//
//** front() function:
//Return a reference to the first element in the circular list.
//
//** back() function:
//Return a reference to the last element in the circular list.
//
//** advance() function:
//Advance the cursor to the next element in the circular list.
//
//** add() function:
//Add an element after the cursor. If possible use available space.
//
//** remove() function:
//Remove the node after the cursor and add to available space list.
//
//** size() function:
//Return the size of the circular list.
//
//** reverse() function:
//Reserve the circular list.
//
//** cleanup() function:
//Free the memory all unused nodes in the available space list.


#ifndef ASSIGNMENT1_CIRCULAR_LIST
#define ASSIGNMENT1_CIRCULAR_LIST

#include <iostream>
#include <stdexcept>

using namespace std;

template<typename Elem>
class CircularList{
    private:
        class CNode{
            Elem elem;
            CNode *next;

            friend class CircularList;
        };
        CNode *cursor;
        CNode *av;
        unsigned count;
        unsigned av_count;
    public:
        CircularList();
        ~CircularList();
        bool empty() const{
            return cursor == NULL;
        }
        Elem& front() const;
        Elem& back() const;
        void advance();
        void add(const Elem& e);
        void remove();
        int size() const;
        void reverse();
        void cleanup();
};

template<typename Elem>
CircularList<Elem>::CircularList(){
    cursor = NULL;
    av = NULL;
    count = 0;
    av_count = 0;
}

template <typename Elem>
CircularList<Elem>::~CircularList(){
    if (cursor){
        CNode *first = cursor -> next;
        cursor -> next = av;
        av = first;
        cursor = 0;
    }
    av_count += count;
    count = 0;
    cleanup();
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
void CircularList<Elem>::advance(){
    if (!empty())
        cursor = cursor -> next;
}

template<typename Elem>
void CircularList<Elem>::add(const Elem& e){
    CNode *new_node;
    if (av){
        new_node = av;
        av = av -> next;
        av_count -= 1;
    }
    else
        new_node = new CNode;
    new_node -> elem = e;
    if (cursor == NULL){
        new_node -> next = new_node;
        cursor = new_node;
    }
    else {
        new_node -> next = cursor -> next;
        cursor -> next = new_node;
    }
    count += 1;
}

template<typename Elem>
void CircularList<Elem>::remove(){
    if (empty())
        throw runtime_error("List is empty");
    CNode *old = cursor -> next;
    if (old == cursor){
        cursor = NULL;
    }
    else {
        cursor -> next = old -> next;
    }
    count -= 1;
    old -> next = av;
    av = old;
    old = 0;
    av_count += 1;
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
    CNode *first = av;
    for (int i = 1; i <= av_count; i++){
        CNode *temp = first -> next;
        delete first;
        first = temp;
    }
    av_count = 0;
}

#endif //ASSIGNMENT1_CIRCULAR_LIST
