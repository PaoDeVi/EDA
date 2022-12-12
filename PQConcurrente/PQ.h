#pragma once
#ifndef PQ_H
#define PQ_H

#include "Skiplist.h"

#include <iostream>
#include <vector>
#include <thread>
using namespace std;

class PQueue
{
public:
   
    void insert(int p)
    {
        int ndatos = 100;
        for (int i = 0; i < ndatos; i++) {
            int  a = p + i;
            seq.insert_element(a);
        }
        
    }

    void minsert(int num) {
        int nt=2;
        vector<thread> threads(nt);
        for (int i = 0; i < nt; i++) {
            threads[i] = thread(&PQueue::insert, this, num);
        }
        for (int i = 0; i < nt; i++) {
            threads[i].join();
        }
    }


    void pop()
    {
        seq.pop_element();
    }

    int top()
    {
        return seq.top_element();
    }

    void print() {
        seq.display();
    }

    skiplist seq;
};

#endif
