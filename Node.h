#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    // int id;
    double x, y;
    bool fixX, fixY;
    double loadX, loadY;

    Node() {}

    Node(double x, double y)
        :  x(x), y(y),
          fixX(false), fixY(false),
          loadX(0), loadY(0) {}
};

#endif