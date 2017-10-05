#include "suffixtree.h"

node::node(const int start, const int end)
{
    this->start = start;
    this->end = end;

    this->link = NULL;
    memset(this->children, NULL, ALPHABETSIZE * sizeof(node*));

    this->size = 0;
}

node::~node()
{
    for (int i = ALPHABETSIZE; --i >= 0; )
        if (children[i])
            delete children[i];
}

void node::reset(const int start, const int end)
{
    this->start = start;
    this->end = end;

    this->link = NULL;
    for (int i = size; --i >= 0; )
        children[active[i]] = NULL;
    size = 0;
}

node* node::getchild (const int value)
{
    return children[value];
}

void node::setchild(const int value, node* nd)
{
    if (nd && !children[value])
        active[size++] = value;

    children[value] = nd;
}

void nodelist::reset()
{
    index = 0;
}

node* nodelist::create(const int start, const int end)
{
    node *nd;
    if (++index > this->count)
    {
        nd = new node(start, end);
        push(nd);
        return nd;
    }

    nd = this->data[index - 1];
    nd->reset(start, end);
    return nd;
}

suffixtree::suffixtree()
{
    data = new vector<int>();
    nodes = new nodelist();
    root = new node();

    initialize();
}

suffixtree::~suffixtree()
{
    delete root;
    delete nodes;
    delete data;
}

void suffixtree::getlongestsubstring(const int start, int& index, int& len)
{
    int* src = data->getdata();
    int val = src[start];
    node *child = root->children[val];

    index = -1;
    len = 0;

    while (child)
    {
        if (child->start >= start)
            return;

        index = child->start;
        len += getedge(child);
        child = child->children[src[start + len]];
    }
}

void suffixtree::initialize()
{
    data->clear();
    nodes->reset();

    pos = -1;
    rem = 0;
    aLength = 0;
    aPos = 0;
    aEnd = 0;

    root->reset();
    active = root;
}

void suffixtree::createtree(const BYTE* data, const int length)
{
    initialize();

    if (!data)
        return;

    for (int i = 0; i < length; i++)
        add(data[i]);
    add(TERMINATIONVALUE);
}

void suffixtree::add(const int val)
{
    if (val < 0 || val > TERMINATIONVALUE)
        return;

    data->push(val);
    pos++;
    link = NULL;
    rem++;
    do
    {
        if (!aLength)
            aPos = pos;
        aVal = (*data)[aPos];        
        node *stem = active->getchild(aVal);

        if (!stem)
        {
            node *leaf = nodes->create(pos);
            active->setchild(aVal, leaf);
            addLink(active);
        }
        else
        {
            int edge = getedge(stem);
            if (aLength >= edge)
            {
                aPos += edge;
                aLength -= edge;
                active = stem;
                continue;
            }

            aEnd = stem->start + aLength;
            if ((*data)[aEnd] == val)
            {
                aLength++;
                addLink(active);
                break;
            }

            node *branch = nodes->create(stem->start, aEnd);
            active->setchild(aVal, branch);

            node *leaf = nodes->create(pos);
            branch->setchild(val, leaf);
            stem->start += aLength;
            branch->setchild((*data)[stem->start], stem);
            addLink(branch);
        }

        rem--;

        if (active == root && aLength > 0)
        {
            aLength--;
            aPos = pos - rem + 1;
        }
        else
            active = active->link ? active->link : root;
    } while (rem > 0);
}