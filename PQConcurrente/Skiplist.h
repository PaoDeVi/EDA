#pragma once
#ifndef SKIP_LIST_H
#define SKIP_LIST_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define MAX_LEVEL 10
const float P = 0.5;
using namespace std;

struct snode
{
    int value;
    snode** forw;
    snode(int level, int& value)
    {
        forw = new snode * [level + 1];
        memset(forw, 0, sizeof(snode*) * (level + 1));
        this->value = value;
    }
    ~snode()
    {
        delete[] forw;
    }
};
/*
 * Skip List Declaration
 */
struct skiplist
{
    snode* header;
    int value;
    int level;
    skiplist()
    {
        header = new snode(MAX_LEVEL, value);
        level = 0;
    }
    ~skiplist()
    {
        delete header;
    }
    
float frand()
{
    return (float)rand() / RAND_MAX;
}

int random_level()
{
    static bool first = true;
    if (first)
    {
        srand((unsigned)time(NULL));
        first = false;
    }
    int lvl = (int)(log(frand()) / log(1. - P));
    return lvl < MAX_LEVEL ? lvl : MAX_LEVEL;
}

void insert_element(int& value)
{
    snode* x = header;
    snode* update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(snode*) * (MAX_LEVEL + 1));
    for (int i = level; i >= 0; i--)
    {
        while (x->forw[i] != NULL && x->forw[i]->value < value)
        {
            x = x->forw[i];
        }
        update[i] = x;
    }
    x = x->forw[0];
    if (x == NULL || x->value != value)
    {
        int lvl = random_level();
        if (lvl > level)
        {
            for (int i = level + 1; i <= lvl; i++)
            {
                update[i] = header;
            }
            level = lvl;
        }
        x = new snode(lvl, value);
        for (int i = 0; i <= lvl; i++)
        {
            x->forw[i] = update[i]->forw[i];
            update[i]->forw[i] = x;
        }
    }
}

void delete_element(int& value)
{
    snode* x = header;
    snode* update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(snode*) * (MAX_LEVEL + 1));
    for (int i = level; i >= 0; i--)
    {
        while (x->forw[i] != NULL && x->forw[i]->value < value)
        {
            x = x->forw[i];
        }
        update[i] = x;
    }
    x = x->forw[0];
    if (x->value == value)
    {
        for (int i = 0; i <= level; i++)
        {
            if (update[i]->forw[i] != x)
                break;
            update[i]->forw[i] = x->forw[i];
        }
        delete x;
        while (level > 0 && header->forw[level] == NULL)
        {
            level--;
        }
    }
}

void pop_element() {
    snode* x = header;
    x = x->forw[0];
    delete_element(x->value);
}

int top_element() {
    snode* x = header;
    x = x->forw[0];
    return x->value;
}

/*
 * Display Elements of Skip List
 */
void display()
{
    const snode* x = header->forw[0];
    while (x != NULL)
    {
        cout << x->value;
        x = x->forw[0];
        if (x != NULL)
            cout << " - ";
    }
    cout << endl;
}

bool contains(int& s_value)
{
    snode* x = header;
    for (int i = level; i >= 0; i--)
    {
        while (x->forw[i] != NULL && x->forw[i]->value < s_value)
        {
            x = x->forw[i];
        }
    }
    x = x->forw[0];
    return x != NULL && x->value == s_value;
}

};
#endif
