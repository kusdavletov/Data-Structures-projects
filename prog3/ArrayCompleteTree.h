//
// ArrayCompleteTree.h  (Version 1.1)
//
// Kusdavletov Ernar, 20152008, kusdavletov1@unist.ac.kr
//

#ifndef ASSIGNMENT3_ARRAYCOMPLETETREE_H
#define ASSIGNMENT3_ARRAYCOMPLETETREE_H

#include <iostream>
#include <stdexcept>

using namespace std;

template<typename E>
class ArrayCompleteTree {
    public:
        class Locator {
            int i;

            public:
                Locator(int _i){
                    i = _i;
                }
                friend class ArrayCompleteTree;
        };

        class LocationAwareEntry {
            E e;
            Locator *loc;

            public:
                LocationAwareEntry(){
                    loc = NULL;
                }
                LocationAwareEntry(E _e, int i){
                    e = _e;
                    Locator *new_loc = new Locator(i);
                    loc = new_loc;
                }
                LocationAwareEntry& operator=(const LocationAwareEntry& entry){
                    if (loc != NULL)
                        clear();
                    e = entry.e;
                    Locator *new_loc = new Locator(entry.loc->i);
                    loc = new_loc;
                }
                void clear(){
                    if (loc != NULL){
                        Locator* temp = loc;
                        delete temp;
                        temp = NULL;
                        loc = NULL;
                    }
                }
                friend class ArrayCompleteTree;
        };

        class Position {
            const ArrayCompleteTree* tree;
            public:
                Locator *loc;
                Position(){
                    tree = NULL;
                    loc = NULL;
                }
                Position(const ArrayCompleteTree *_tree, Locator *_loc){
                    tree = _tree;
                    Locator* new_loc = new Locator(_loc->i);
                    loc = new_loc;
                }
                E& operator*() const{
                    if (tree == NULL || loc == NULL) throw runtime_error("Cannot apply *operator to NULL position");
                    return tree->v[loc->i].e;
                }
                bool operator==(const Position& p) const{
                    return (tree == p.tree) && (loc->i == p.loc->i);
                }
                friend class ArrayCompleteTree;
        };

    private:
        LocationAwareEntry* v;
        int vsize;
        int n;

    public:
        ArrayCompleteTree(int _vsize = 10){
            vsize = _vsize;
            n = 0;
            v = new LocationAwareEntry[vsize];
        }
        ArrayCompleteTree(const ArrayCompleteTree& t){
            vsize = t.vsize;
            n = t.n;
            v = new LocationAwareEntry[vsize];
            for(int i = 0; i < n; i++){
                v[i] = LocationAwareEntry(t.v->e, i);
            }
        }
        ~ArrayCompleteTree(){
            for (int i = 0; i < vsize; i++){
                v[i].clear();
            }
            vsize = 0;
            n = 0;
            delete[] v;
        }
        int size() const{
            return n;
        }
        Position left(const Position& p) const{
            if (p.loc == NULL || (2 * p.loc->i + 1 >= n)) throw runtime_error("Locator of the position is NULL or index is out of range.");
            return Position(this, v[2 * p.loc->i + 1].loc);
        }
        Position right(const Position& p) const{
            if (p.loc == NULL || (2 * p.loc->i + 2 >= n)) throw runtime_error("Locator of the position is NULL or index is out of range.");
            return Position(this, v[2 * p.loc->i + 2].loc);
        }
        Position parent(const Position& p) const{
            if (p.loc == NULL || ((p.loc->i - 1) / 2 > n) || isRoot(p)) throw runtime_error("Locator of the position is NULL or index is out of range.");
            return Position(this, v[(p.loc->i - 1) / 2].loc);
        }
        bool hasLeft(const Position& p) const{
            if (p.loc == NULL) throw runtime_error("Locator of the position is NULL.");
            return 2 * p.loc->i + 1 < n;
        }
        bool hasRight(const Position& p) const{
            if (p.loc == NULL) throw runtime_error("Locator of the position is NULL.");
            return 2 * p.loc->i + 2 < n;
        }
        bool isRoot(const Position& p) const{
            if (p.loc == NULL) throw runtime_error("Locator of the position is NULL.");
            return p.loc->i == 0;
        }
        Position root(){
            if (v[0].loc == NULL) throw runtime_error("Array is empty.");
            return Position(this, v[0].loc);
        }
        Position last(){
            if (v[0].loc == NULL) throw runtime_error("Array is empty.");
            return Position(this, v[n - 1].loc);
        }
        void addLast(const E& e){
            if (n >= vsize){
                LocationAwareEntry *new_array = new LocationAwareEntry[2 * vsize];
                for (int i = 0; i < n; i++){
                    new_array[i] = LocationAwareEntry(v[i].e, i);
                    v[i].clear();
                }
                v = new_array;
                vsize = 2 * vsize;
            }
            *(v + n) = LocationAwareEntry(e, n);
            n = n + 1;
        }
        void removeLast(){
            if (v[0].loc == NULL) throw runtime_error("Array is empty.");
            v[n - 1].clear();
            n = n - 1;
        }
        void swap(const Position& p, const Position& q){
            if (p.loc == NULL || q.loc == NULL) throw runtime_error("Locator of the position is NULL.");
            E temp = *q;
            *q = *p;
            *p = temp;
        }
        void cleanup(){
            LocationAwareEntry *new_array = new LocationAwareEntry[n];
            for (int i = 0; i < n; i++){
                new_array[i] = LocationAwareEntry(v[i].e, i);
                v[i].clear();
            }
            v = new_array;
            vsize = n;
        }
};

#endif //ASSIGNMENT3_ARRAYCOMPLETETREE_H
