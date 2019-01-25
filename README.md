# DAG
Codebase to calculate DAG of tasks with user interface included. Memory efficient solution using DFT.

Topologically sorts the information to print out which order the tasks should go if there are no cycles.

### Compile Code
```
g++ DAG.cpp -o DAG
```

### Run Code
```
./DAG
```

### User Interface
* Code walks user through running itself
* Type number of tasks and their names
* Give tasks relations to each other
* Code will attempt to determine if the graph is a DAG and return the order if it is

## Successfuly Calculates Topological Order
![Alt text](Success_DAG.png?raw=true "DAG Success")

## Example of Graph that is not Directed Acyclical
![Alt text](Not_DAG.png?raw=true "Not a DAG")

## Boundary Testing for Vertex Relation Creation
![Alt text](Vertex_Out_Of_Bounds.png?raw=true "Invalid Vertex Relation")

## Memory Analysis
Using valgrind memory is verified to be cleaned up.
![Alt text](Memory_Leak_Analysis.png?raw=true "Analyze Memory Leak")
