#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

class Matrix
{
public:
    static vector<double>
    solveGaussian(vector<vector<double>> A,
                  vector<double> b)
    {

        int n = A.size();

        for (int i = 0; i < n; i++)
        {

            double pivot = A[i][i];

            for (int j = i; j < n; j++)
                A[i][j] /= pivot;

            b[i] /= pivot;

            for (int k = i + 1; k < n; k++)
            {

                double factor = A[k][i];

                for (int j = i; j < n; j++)
                    A[k][j] -= factor * A[i][j];

                b[k] -= factor * b[i];
            }
        }

        vector<double> x(n);

        for (int i = n - 1; i >= 0; i--)
        {

            x[i] = b[i];

            for (int j = i + 1; j < n; j++)
                x[i] -= A[i][j] * x[j];
        }

        return x;
    }
};

#endif