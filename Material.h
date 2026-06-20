#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

class Material
{
public:
    double E;
    double density;
    double sigmaMax;

    Material() {}

    Material(double E, double density, double sigmaMax)
        : E(E), density(density), sigmaMax(sigmaMax) {}
};

#endif