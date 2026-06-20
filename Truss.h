#ifndef TRUSS_H
#define TRUSS_H

#include <stdio.h>
#include <bits/stdc++.h>
#include "Node.h"
#include "Material.h"
#include "Member.h"
#include "Matrix.h"

using namespace std;

class Truss
{
public:
    vector<Node> nodes;
    vector<Member> members;
    Material material;

    vector<double> displacement;

    Truss() {}

    void solve()
    {
        computeLengths();

        auto K = assembleGlobalK();

        auto F = buildLoadVector();

        applyBoundaryConditions(K, F);

        displacement =
            Matrix::solveGaussian(K, F);

        computeMemberForces();
    }

    void computeLengths()
    {
        for (auto &m : members)
        {
            Node &n1 = nodes[m.node1];
            Node &n2 = nodes[m.node2];

            double dx = n2.x - n1.x;
            double dy = n2.y - n1.y;

            m.length = sqrt(dx * dx + dy * dy);

            m.c = dx / m.length;
            m.s = dy / m.length;
        }
    }

    vector<vector<double>> assembleGlobalK()
    {
        int totalDOF = 2 * nodes.size();

        vector<vector<double>> K(
            totalDOF,
            vector<double>(totalDOF, 0));

        for (auto &m : members)
        {
            double coeff =
                m.area * material.E / m.length;

            double c = m.c;
            double s = m.s;

            double k[4][4] = {
                {c * c, c * s, -c * c, -c * s},
                {c * s, s * s, -c * s, -s * s},
                {-c * c, -c * s, c * c, c * s},
                {-c * s, -s * s, c * s, s * s}};

            int dof[4] = {
                2 * m.node1,
                2 * m.node1 + 1,
                2 * m.node2,
                2 * m.node2 + 1};

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    K[dof[i]][dof[j]] += coeff * k[i][j];
                }
            }
        }

        return K;
    }

    vector<double> buildLoadVector()
    {
        int totalDOF = 2 * nodes.size();

        vector<double> F(totalDOF, 0);

        for(size_t i=0;i<nodes.size();i++)
        {
            F[2*i]   = nodes[i].loadX;
            F[2*i+1] = nodes[i].loadY;
        }

        return F;
    }

    void applyBoundaryConditions(
        vector<vector<double>> &K,
        vector<double> &F)
    {
        int totalDOF = 2 * nodes.size();

        for(size_t i=0;i<nodes.size();i++)
        {
            if (nodes[i].fixX)
            {
                int d = 2 * i;

                for (int j = 0; j < totalDOF; j++)
                {
                    K[d][j] = 0;
                    K[j][d] = 0;
                }

                K[d][d] = 1;
                F[d] = 0;
            }

            if (nodes[i].fixY)
            {
                int d = 2 * i + 1;

                for (int j = 0; j < totalDOF; j++)
                {
                    K[d][j] = 0;
                    K[j][d] = 0;
                }

                K[d][d] = 1;
                F[d] = 0;
            }
        }
    }

    void computeMemberForces()
    {
        for (auto &m : members)
        {
            int i = m.node1;
            int j = m.node2;

            double u1x = displacement[2 * i];
            double u1y = displacement[2 * i + 1];

            double u2x = displacement[2 * j];
            double u2y = displacement[2 * j + 1];

            double delta =
                -m.c * u1x - m.s * u1y + m.c * u2x + m.s * u2y;

            m.force =
                m.area * material.E *
                delta / m.length;

            m.stress =
                m.force / m.area;
        }
    }

    double computeWeight()
    {
        double weight = 0;

        for (auto &m : members)
        {
            weight += material.density *
                      m.area *
                      m.length;
        }

        return weight;
    }

    void updateAreas(vector<double> &areas)
    {
        for (size_t i = 0; i < members.size(); i++)
            members[i].area = areas[i];
    }
};

#endif