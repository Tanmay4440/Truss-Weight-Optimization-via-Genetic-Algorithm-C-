#ifndef MEMBER_H
#define MEMBER_H

#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

class Member
{
public:
    int id;
    int node1, node2;

    double area;
    double stress;
    double force;
    double length;

    double c, s;

    Member() {}

    Member(int id, int n1, int n2, double area)
        : id(id), node1(n1), node2(n2),
          area(area),
          stress(0),
          force(0),
          length(0),
          c(0),
          s(0)
    {
    }
};

#endif