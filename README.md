#  Truss Optimization using Finite Element Analysis and Genetic Algorithm in C++

A C++ implementation of a 2D truss analysis and optimization framework using the Finite Element Method (FEM) and Genetic Algorithms (GA). The project combines numerical methods, matrix computations, and evolutionary optimization to obtain lightweight structural designs while satisfying stress constraints.

---

## Mathematical Model

The structural response is obtained by solving

```math
K d = F
```

where

* `K` : Global stiffness matrix
* `d` : Nodal displacement vector
* `F` : External load vector

Member force is computed as

```math
F = \frac{AE}{L}\delta
```

and stress as

```math
\sigma = \frac{F}{A}
```

---

## Genetic Algorithm

Each chromosome stores cross-sectional areas of all members.

### Objective

```text
Minimize Weight

Subject to

|Stress| ≤ Allowable Stress
```

### Fitness Function

```text
Fitness = Weight + Penalty
```

where penalty is imposed for constraint violations.

---

## Workflow

```text
External Loads
      │
      ▼
Assemble Global Stiffness Matrix
      │
      ▼
Apply Boundary Conditions
      │
      ▼
Solve Kd = F
      │
      ▼
Compute Displacements
      │
      ▼
Compute Member Forces & Stresses
      │
      ▼
Evaluate Weight and Constraints
      │
      ▼
Genetic Algorithm
(Selection → Crossover → Mutation)
      │
      ▼
Update Member Areas
      │
      ▼
Repeat Until Convergence
      │
      ▼
Optimal Lightweight Design
```

---

## Algorithms Used

### Finite Element Analysis

1. Compute member geometry.
2. Assemble local stiffness matrices.
3. Form global stiffness matrix.
4. Apply boundary conditions.
5. Solve the linear system.
6. Compute member forces and stresses.

### Genetic Algorithm

1. Initialize population.
2. Evaluate fitness.
3. Tournament selection.
4. Crossover.
5. Mutation.
6. Elitism.
7. Repeat until convergence.



---

## Units

The implementation follows SI units throughout.

| Quantity        | Unit  |
| --------------- | ----- |
| Length          | m     |
| Force           | N     |
| Area            | m²    |
| Stress          | Pa    |
| Young's Modulus | Pa    |
| Density         | kg/m³ |
| Displacement    | m     |

---

## Concepts Used

* Object-Oriented Programming
* Matrix Operations
* Numerical Methods
* Finite Element Method
* Genetic Algorithms
* Optimization Techniques
* Linear Algebra
* Data Structures
* Evolutionary Computation

---

## Future Improvements

* Displacement Constraints
* Buckling Constraints
* Self-Weight Loading
* Multi-Material Optimization
* Parallel Genetic Algorithms
* Visualization of Deformed Shape
* File-Based Input and Output

---

## Author

**Tanmay Kumar**
