//
// HashMap.h  (Version 1.0)
//
// Kusdavletov Ernar, 20152008, kusdavletov1@unist.ac.kr
//

#ifndef ASSIGNMENT3_HASHMAP_H
#define ASSIGNMENT3_HASHMAP_H

#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

using namespace std;

class IntHashComparator {
    public:
        int operator()(const int& a) const {
            return a;
        }
};

template <typename K, typename V, typename H>
class HashMap {
    public:
        class Entry {
            public:
                Entry(const K& k = K(), const V& v = V()) : _key(k), _value(v) { }
                const K& key() const {
                    return _key;
                }
                const V& value() const {
                    return _value;
                }
                void setValue(const V& v) {
                    _value = v;
                }
                friend class HashMap;
            public:
                const K _key;
                V _value;
        };

    protected:
        typedef std::list<Entry> Bucket;
        typedef std::vector<Bucket> BktArray;
        typedef typename BktArray::iterator BItor;
        typedef typename Bucket::iterator EItor;

    public:
        class Iterator {
            private:
                EItor ent;
                BItor bkt;
                const BktArray* ba;
                Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor()) : ent(q), bkt(b), ba(&a) { }
            public:
                Entry& operator*() const{
                    return *ent;
                }
                bool operator==(const Iterator& p) const{
                    if (ba != p.ba || bkt != p.bkt)
                        return false;
                    else if (bkt == ba->end())
                        return true;
                    else
                        return (ent == p.ent);
                }
                Iterator& operator++(){
                    ++ent;
                    if (endOfBkt(*this)) {
                        ++bkt;
                        while (bkt != ba->end() && bkt->empty())
                            ++bkt;
                        if (bkt == ba->end())
                            return *this;
                        ent = bkt->begin();
                    }
                    return *this;
                }

                friend class HashMap;
        };

    public:
        HashMap(int capacity = 100) : n(0), B(capacity) { }
        int size() const{
            return n;
        }
        bool empty() const{
            return size() == 0;
        }
        Iterator find(const K& k){
            Iterator p = finder(k);
            if (endOfBkt(p))
                return end();
            else
                return p;
        }
        Iterator put(const K& k, const V& v){
            Iterator p = finder(k);
            if (endOfBkt(p)) {
                return inserter(p, Entry(k, v));
            }
            else {
                p.ent->setValue(v);
                return p;
            }
        }
        void erase(const K& k){
            Iterator p = finder(k);
            if (endOfBkt(p)) throw runtime_error("Erase of nonexistent");
            eraser(p);
        }
        void erase(const Iterator& p){
            eraser(p);
        }
        Iterator begin(){
            if (empty())
                return end();
            BItor bkt = B.begin();
            while (bkt->empty())
                ++bkt;
            return Iterator(B, bkt, bkt->begin());
        }
        Iterator end(){
            return Iterator(B, B.end());
        }
        V& operator[] (const K& key){
            Iterator p = find(key);
            if (p == end()){
                V new_val;
                Iterator new_iter = put(key, new_val);
                return new_iter.ent->_value;
            }
            Iterator new_iter2 = find(key);
            return new_iter2.ent->_value;
        }

    protected:
        Iterator finder(const K& k){
            int i = hash(k) % B.size();
            BItor bkt = B.begin() + i;
            Iterator p(B, bkt, bkt->begin());
            while (!endOfBkt(p) && (*p).key() != k)
                nextEntry(p);
            return p;
        }
        Iterator inserter(const Iterator& p, const Entry& e){
            EItor ins = p.bkt->insert(p.ent, e);
            n++;
            return Iterator(B, p.bkt, ins);
        }
        void eraser(const Iterator& p){
            p.bkt->erase(p.ent);
            n--;
        }
        static void nextEntry(Iterator& p){
            ++p.ent;
        }
        static bool endOfBkt(const Iterator& p){
            return p.ent == p.bkt->end();
        }
    private:
        int n;
        H hash;
        BktArray B;
};

#endif //ASSIGNMENT3_HASHMAP_H
