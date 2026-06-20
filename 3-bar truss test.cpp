#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Node.h"
#include "Material.h"
#include "Member.h"
#include "Truss.h"
#include "Chromosome.h"
#include "GeneticAlgorithm.h"

using namespace std;

int main()
{

    Truss truss;

    // ================= NODES =================

    truss.nodes.push_back(Node(0.0, 0.0));
    truss.nodes.push_back(Node(5.0, 0.0));
    truss.nodes.push_back(Node(2.5, 4.0));

    // ================= SUPPORTS =================

    // Node 0 : pinned
    truss.nodes[0].fixX = true;
    truss.nodes[0].fixY = true;

    // Node 1 : roller
    truss.nodes[1].fixY = true;

    // ================= LOADS =================

    // 100 kN downward at node 2
    truss.nodes[2].loadY = -100000.0;

    // ================= MATERIAL =================

    truss.material = Material(
        200e9,      // Young's modulus (Pa)
        7850,       // density (kg/m^3)
        250e6       // allowable stress (Pa)
    );

    // ================= MEMBERS =================
    // Member(id, node1, node2, initial area)

    truss.members.push_back(Member(0, 0, 1, 0.002));
    truss.members.push_back(Member(1, 0, 2, 0.002));
    truss.members.push_back(Member(2, 1, 2, 0.002));

    // ================= GA PARAMETERS =================

    GeneticAlgorithm ga;

    ga.populationSize = 50;
    ga.generations = 100;
    ga.mutationRate = 0.05;
    ga.crossoverRate = 0.8;

    // ================= RUN =================

    ga.evolve(truss);

    cout << "\n================ BEST DESIGN ================\n";

    ga.printBest();

    // Solve again using best areas
    truss.updateAreas(ga.bestChromosome.areas);
    truss.solve();

    // ================= MEMBER RESULTS =================

    cout << "\n=============== MEMBER RESULTS ===============\n";

    for (auto &m : truss.members)
    {
        cout << "\nMember " << m.id + 1 << endl;

        cout << "Length = "
             << m.length
             << " m\n";

        cout << "Area = "
             << m.area
             << " m^2\n";

        cout << "Force = "
             << m.force
             << " N\n";

        cout << "Stress = "
             << m.stress / 1e6
             << " MPa\n";
    }

    // ================= DISPLACEMENTS =================

    cout << "\n=============== NODE DISPLACEMENTS ===============\n";

    for (size_t i = 0; i < truss.nodes.size(); i++)
    {
        cout << "\nNode " << i << endl;

        cout << "Ux = "
             << truss.displacement[2 * i]
             << " m\n";

        cout << "Uy = "
             << truss.displacement[2 * i + 1]
             << " m\n";
    }

    return 0;
}