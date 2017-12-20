//
// HeapPriorityQueue.h  (Version 1.0)
//
// Kusdavletov Ernar, 20152008, kusdavletov1@unist.ac.kr
//

#ifndef ASSIGNMENT3_HEAPPRIORITYQUEUE_H
#define ASSIGNMENT3_HEAPPRIORITYQUEUE_H

#include <iostream>
#include <stdexcept>
#include "ArrayCompleteTree.h"

using namespace std;

template<typename T>
class LessThanComparator {
    public:
        bool operator()(const T& a, const T& b) const {
            return a < b;
        }
};

template<typename E, typename C>
class HeapPriorityQueue {
    public:
        typedef typename ArrayCompleteTree<E>::Position Position;

    private:
        ArrayCompleteTree<E> T;
        C isLess;

    public:
        HeapPriorityQueue():T(){ }
        HeapPriorityQueue(const HeapPriorityQueue& q):T(q.T){}
        int size() const {
            return T.size();
        }
        bool empty() const{
            return T.size() == 0;
        }
        Position insert(const E& e){
            T.addLast(e);
            Position v = T.last();
            while (!T.isRoot(v)) {
                Position u = T.parent(v);
                if (!isLess(*v, *u))
                    break;
                T.swap(v, u);
            }
            return v;
        }
        const E& min(){
            return *(T.root());
        }
        void removeMin(){
            if (size() == 1)
                T.removeLast();
            else {
                Position u = T.root();
                T.swap(u, T.last());
                T.removeLast();
                while (T.hasLeft(u)) {
                    Position v = T.left(u);
                    if (T.hasRight(u) && isLess(*(T.right(u)), *v))
                        v = T.right(u);
                    if (isLess(*v, *u)) {
                        T.swap(u, v);
                    }
                    else
                        break;
                }
            }
        }
        void remove(const Position& u){
            if (u == T.root()){
                removeMin();
            }
            else {
                T.swap(u, T.last());
                T.removeLast();
                while (true){
                    if (u == T.root()){
                        break;
                    }
                    else if (isLess(*u, *(T.parent(u)))){
                        T.swap(u, T.parent(u));
                    }
                    else{
                        while (T.hasLeft(u)) {
                            Position v = T.left(u);
                            if (T.hasRight(u) && isLess(*(T.right(u)), *v))
                                v = T.right(u);
                            if (isLess(*v, *u)) {
                                T.swap(u, v);
                            }
                            else
                                break;
                        }
                        break;
                    }
                }
            }
        }
        Position replace(const Position& p, const E& e){
            *p = e;
            while (true){
                if (p == T.root()){
                    break;
                }
                else if (isLess(*p, *(T.parent(p)))){
                    T.swap(p, T.parent(p));
                }
                else{
                    while (T.hasLeft(p)) {
                        Position v = T.left(p);
                        if (T.hasRight(p) && isLess(*(T.right(p)), *v))
                            v = T.right(p);
                        if (isLess(*v, *p)) {
                            T.swap(p, v);
                        }
                        else
                            break;
                    }
                    break;
                }
            }
            return p;
        }
};

#endif //ASSIGNMENT3_HEAPPRIORITYQUEUE_H
