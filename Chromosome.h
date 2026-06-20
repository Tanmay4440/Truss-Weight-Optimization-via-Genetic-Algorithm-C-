#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <stdio.h>
#include <bits/stdc++.h>
#include "Truss.h"

using namespace std;

class Chromosome
{
public:
    vector<double> areas;

    double weight;
    double fitness;
    double penalty;

    Chromosome()
    {
        weight = 0;
        fitness = numeric_limits<double>::max();
        penalty = 0;
    }

    void evaluate(Truss &truss)
    {
        truss.updateAreas(areas);

        truss.solve();

        weight = truss.computeWeight();

        penalty = 0;

        for (auto &m : truss.members)
        {
            double violation =
                abs(m.stress) - truss.material.sigmaMax;

            if (violation > 0)
                penalty += violation;
        }

        fitness =
            weight +
            1e10 * penalty;
    }

    bool operator<(const Chromosome &other) const
    {
        return fitness < other.fitness;
    }

    void randomInitialize(int numMembers,
                          double Amin,
                          double Amax)
    {
        areas.resize(numMembers);

        for (int i = 0; i < numMembers; i++)
        {
            double r =
                (double)rand() / RAND_MAX;

            areas[i] =
                Amin + r * (Amax - Amin);
        }
    }
};

#endif