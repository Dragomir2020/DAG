# DAG
Codebase to calculate DAG of tasks with user interface included. Memory efficient solution using DFT.

Topologically sorts the information to print out which order the tasks should go if there are no cycles.

## Successfuly Calculates Topological Order
![Alt text](Success_DAG.png?raw=true "DAG Success")

## Example of Graph that is not Directed Acyclical
![Alt text](Not_DAG.png?raw=true "Not a DAG")

## Boundary Testing for Vertex Relation Creation
![Alt text](Vertex_Out_Of_Bounds.png?raw=true "Invalid Vertex Relation")

## Memory Analysis
Using valgrind memory is verified to be cleaned up.
![Alt text](Memory_Leak_Analysis.png?raw=true "Analyze Memory Leak")
