#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include "HeapPriorityQueue.h"
#include "Simulator.h"


using namespace std;

#define les <

int main(){
    HeapPriorityQueue<string, les> heap;
    cout << heap.size() << endl;
    heap.insert("hi");
    return 0;
}
