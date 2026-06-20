#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <stdio.h>
#include <bits/stdc++.h>
#include "Truss.h"
#include "Chromosome.h"

using namespace std;

class GeneticAlgorithm
{

public:
    size_t populationSize;
    size_t generations;

    double mutationRate;
    double crossoverRate;

    Chromosome bestChromosome;

    vector<Chromosome> population;

    GeneticAlgorithm()
    {

        populationSize = 50;
        generations = 100;

        mutationRate = 0.05;
        crossoverRate = 0.8;
    }

    void initialize(Truss &truss)
    {
        population.resize(populationSize);

        for (auto &c : population)
        {
            c.randomInitialize(
                truss.members.size(),
                0.0001,
                0.01);

            c.evaluate(truss);
        }

        bestChromosome =
            *min_element(population.begin(),
                         population.end());
    }

    void evolve(Truss &truss)
    {
        initialize(truss);

        for (size_t gen = 0; gen < generations; gen++)
        {
            vector<Chromosome> newPopulation;

            sort(population.begin(),
                 population.end());

            // elitism
            newPopulation.push_back(population[0]);

            while (newPopulation.size() < populationSize)
            {
                Chromosome p1 =
                    tournamentSelection();

                Chromosome p2 =
                    tournamentSelection();

                auto children =
                    crossover(p1, p2);

                mutate(children.first);
                mutate(children.second);

                children.first.evaluate(truss);
                children.second.evaluate(truss);

                newPopulation.push_back(children.first);

                if (newPopulation.size() < populationSize)
                    newPopulation.push_back(children.second);
            }

            population = newPopulation;

            sort(population.begin(),
                 population.end());

            if (population[0].fitness <
                bestChromosome.fitness)
            {
                bestChromosome =
                    population[0];
            }

            cout << "Generation "
                 << gen
                 << " Best Weight = "
                 << population[0].weight
                 << endl;
        }
    }

    Chromosome tournamentSelection()
    {
        int a = rand() % populationSize;
        int b = rand() % populationSize;

        if (population[a].fitness <
            population[b].fitness)
            return population[a];

        return population[b];
    }

    pair<Chromosome, Chromosome>
    crossover(Chromosome p1,
              Chromosome p2)
    {
        Chromosome c1 = p1;
        Chromosome c2 = p2;

        double r = (double)rand() / RAND_MAX;

        if (r > crossoverRate)
            return {c1, c2};

        int n = p1.areas.size();

        int point = rand() % n;

        for (int i = point; i < n; i++)
        {
            swap(c1.areas[i], c2.areas[i]);
        }

        return {c1, c2};
    }

    void mutate(Chromosome &c)
    {
        for (auto &gene : c.areas)
        {
            double r = (double)rand() / RAND_MAX;

            if (r < mutationRate)
            {
                double delta =
                    ((double)rand() / RAND_MAX - 0.5) * 0.002;

                gene += delta;

                gene = max(0.0001, gene);
                gene = min(0.01, gene);
            }
        }
    }

    void printBest()
    {
        cout << "\nBest Weight = "
             << bestChromosome.weight
             << endl;

        cout << "\nAreas\n";

        for (size_t i = 0; i < bestChromosome.areas.size(); i++)
        {
            cout << "A" << i + 1 << " = "
                 << bestChromosome.areas[i]
                 << endl;
        }
    }
};

#endif