#pragma once

#ifndef TREE_H
#define TREE_H

#define ALPHABETSIZE 0x101
#define TERMINATIONVALUE 0x100

#include "vector.h"

class node
{
    friend class suffixtree;

    int active[ALPHABETSIZE];
    int size;
    node* children[ALPHABETSIZE];

public:
    int start;
    int end;
    node* link;

    node(const int start = -1, const int end = -1);
    ~node();

    void reset(const int start = -1, const int end = -1);

    node* getchild(const int value);
    void setchild(const int value, node* nd);
};

class nodelist : public vector<node*>
{
    int index;

public:
    nodelist() {
        index = 0;
    }

    void reset();
    node* create(const int start = -1, const int end = -1);
};

class suffixtree
{
    nodelist *nodes;
    node *root;
    node *link;
    node *active;
    vector<int> *data;

    int pos, rem, aLength, aPos, aVal, aEnd;

public:
    suffixtree();
    ~suffixtree();
    void getlongestsubstring(const int start, int& index, int& len);

    void initialize();

    void createtree(const BYTE* data, const int length);
    void add(const int val);

    inline void addLink(node *node)
    {
        if (link)
            link->link = node;
        link = node;
    }

    inline int getend(const node *node)
    {
        return node->end == -1 ? pos : node->end;
    }

    inline int getedge(const node *node)
    {
        return getend(node) - node->start;
    }

    inline node** getchildren()
    {
        return root->children;
    }
};

#endif