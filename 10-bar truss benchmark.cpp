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
    // Coordinates in meters

    truss.nodes.push_back(Node(0.0, 9.144));      // 0
    truss.nodes.push_back(Node(9.144, 9.144));    // 1
    truss.nodes.push_back(Node(18.288, 9.144));   // 2

    truss.nodes.push_back(Node(0.0, 0.0));        // 3
    truss.nodes.push_back(Node(9.144, 0.0));      // 4
    truss.nodes.push_back(Node(18.288, 0.0));     // 5

    // ================= SUPPORTS =================

    truss.nodes[0].fixX = true;
    truss.nodes[0].fixY = true;

    truss.nodes[3].fixX = true;
    truss.nodes[3].fixY = true;

    // ================= LOADS =================
    // 100000 lb = 444822 N

    truss.nodes[1].loadY = -444822.0;
    truss.nodes[2].loadY = -444822.0;

    // ================= MATERIAL =================

    truss.material = Material(
        68.95e9,    // E = 1e7 psi = 68.95 GPa
        2768.0,     // density (kg/m³)
        172.37e6    // sigmaMax = 25000 psi = 172.37 MPa
    );

    // ================= MEMBERS =================

    double A0 = 0.01935;   // 30 in² = 0.01935 m²

    truss.members.push_back(Member(0,0,1,A0));
    truss.members.push_back(Member(1,1,2,A0));
    truss.members.push_back(Member(2,3,4,A0));
    truss.members.push_back(Member(3,4,5,A0));
    truss.members.push_back(Member(4,1,4,A0));
    truss.members.push_back(Member(5,2,5,A0));
    truss.members.push_back(Member(6,0,4,A0));
    truss.members.push_back(Member(7,1,3,A0));
    truss.members.push_back(Member(8,1,5,A0));
    truss.members.push_back(Member(9,2,4,A0));

    // ================= GA PARAMETERS =================

    GeneticAlgorithm ga;

    ga.populationSize = 100;
    ga.generations = 500;
    ga.mutationRate = 0.05;
    ga.crossoverRate = 0.8;



    // ================= OPTIMIZATION =================

    ga.evolve(truss);

    cout << "\n========== BEST DESIGN ==========\n\n";

    ga.printBest();

    truss.updateAreas(ga.bestChromosome.areas);
    truss.solve();

    // ================= MEMBER RESULTS =================

    cout << "\n========== MEMBER RESULTS ==========\n";

    for(size_t i=0;i<truss.members.size();i++)
    {
        auto &m=truss.members[i];

        cout << "\nMember " << i+1 << endl;

        cout << "Length = " << m.length << " m\n";

        cout << "Area = " << m.area << " m²\n";

        cout << "Force = " << m.force << " N\n";

        cout << "Stress = "
             << m.stress/1e6
             << " MPa\n";
    }

    // ================= NODE DISPLACEMENTS =================

    cout << "\n========== NODE DISPLACEMENTS ==========\n";

    for(size_t i=0;i<truss.nodes.size();i++)
    {
        cout << "\nNode " << i << endl;

        cout << "Ux = "
             << truss.displacement[2*i]
             << " m\n";

        cout << "Uy = "
             << truss.displacement[2*i+1]
             << " m\n";
    }

    return 0;
}