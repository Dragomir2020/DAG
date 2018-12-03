
/////////////////////////////
//FILE NAME: DAG.cpp//
/////////////////////////////

////////////////
//Contributers//
////////////////

///////////////////////////////////////////////

// NAME                   DATE           CHANGE
// Dillon Dragomir        11-09-2018     Started File
// Dillon Dragomir        11-12-2018     Add methods for topological sort
// Dillon Dragomir        11-12-2018     Created user interface for inputing data
///////////////////////////////////////////////

////////////////
//DEPENDANCIES//
////////////////

#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <deque>

namespace DataStructures{
    
    namespace Algorithms {
        
        // Holds edges of vert
        struct Edge{
            int value;
            Edge* nextEdge;
        };
        
        struct Node{
            std::string state; //P: Permanent, T: Temporary, U: Unmarked
            int vert;
        };
        
        
        // A class that represents an undirected graph
        class DiGraph
        {
            int vertNum;    // No. of vertices
            Edge* edges;
        public:
            // Constructor and destructor
            DiGraph(int num) {
                vertNum = num;
                edges = new Edge[num]();
                for(int i = 0; i < num; i++){
                    edges[i].value = -1;
                }
            }
            
            ~DiGraph(){
                // Delete Graph
                for(int i = 0; i < vertNum; i++){
                    Edge* loop = edges[i].nextEdge;
                    Edge* hold;
                    while(loop != NULL){
                        hold = loop;
                        delete loop;
                        loop = hold->nextEdge;
                    }
                }
                delete edges;
            }
            
            // functions to add and remove edge
            void AddEdge(int u, int v) {
                if(u >= vertNum || u < 0 || v >= vertNum || v < 0){
                    std::cout << "Vertex index out of bounds" << std::endl;
                    return;
                }
                // No edges added
                if(edges[u].value == -1){
                    edges[u].value = v;
                    return;
                }
                if(edges[u].nextEdge == NULL){
                    edges[u].nextEdge = new Edge();
                    edges[u].nextEdge->value = v;
                    return;
                }
                Edge* now = edges[u].nextEdge;
                while(now != NULL){
                    if(now->nextEdge == NULL){
                        now->nextEdge = new Edge();
                        now->nextEdge->value = v;
                        return;
                    }
                    now = now->nextEdge;
                }
                std::cout << "Broken if reached!" << std::endl;
            }

            
            void RemoveEdge(int u, int v)
            {
                if(u >= vertNum || u < 0 || v >= vertNum || v < 0){
                    std::cout << "Vertex index out of bounds" << std::endl;
                    return;
                }
                // No edges added
                if(edges[u].value == -1){
                    std::cout << "No vertex to delete" << std::endl;
                    return;
                }
                if(edges[u].value == v){
                    if(edges[u].nextEdge == NULL){
                        edges[u].value = -1;
                        return;
                    } else {
                        edges[u].value = edges[u].nextEdge->value;
                        if(edges[u].nextEdge->nextEdge == NULL){
                            delete edges[u].nextEdge;
                            edges[u].nextEdge = NULL;
                        } else {
                            Edge* hold = edges[u].nextEdge;
                            edges[u].nextEdge = hold->nextEdge;
                            delete hold;
                        }
                        return;
                    }
                }
                Edge* prev = &edges[u];
                Edge* now = edges[u].nextEdge;
                while(now != NULL){
                    if(now->value == v){
                        if(now->nextEdge == NULL){
                            prev->nextEdge = NULL;
                            delete now;
                            return;
                        }else{
                            prev->nextEdge = now->nextEdge;
                            delete now;
                            return;
                        }
                    }
                    prev = now;
                    now = now->nextEdge;
                }
                std::cout << "Edge does not exist 2" << std::endl;
            }
            
            void Print(){
                std::cout << "Printing Edges!" << std::endl;
                for(int i = 0; i < vertNum; i++){
                    std::cout << std::to_string(i) << ": ";
                    Edge* loop = &edges[i];
                    while(loop != NULL){
                        if(loop->value != -1){
                            std::cout << loop->value;
                        }
                        if(loop->nextEdge != NULL){
                            std::cout << ", ";
                        }
                        loop = loop->nextEdge;
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }
            
            std::deque<int>* TopologicalSort(){
                std::deque<int>* sortedElements = new std::deque<int>();
                // Create vector of unmarked nodes
                std::vector<Node*>* nodes = new std::vector<Node*>();
                for(int i = 0; i < vertNum; i++){
                    Node* n = new Node();
                    n->state = "U";
                    n->vert = i;
                    nodes->push_back(n);
                }

                std::string v;
                for(int i = 0; i < nodes->size(); i++){
                    if(nodes->at(i)->state == "U"){
                        v = visit(nodes, i, sortedElements);
                    }
                    if(v == "Stop"){
                        sortedElements->push_front(-1);
                        return sortedElements;
                    }
                }
                return sortedElements;
            }
            
        private:
            
            std::string visit(std::vector<Node*>* nodes, int ind, std::deque<int>* sorted){
                if(nodes->at(ind)->state == "P"){
                    return "Continue";
                }
                if(nodes->at(ind)->state == "T"){
                    //std::cout << "Not a DAG!" << std::endl;
                    sorted->clear();
                    return "Stop";
                }
                nodes->at(ind)->state = "T";
                // Loop through all the edges
                Edge* loop = &edges[nodes->at(ind)->vert];
                std::string v;
                while(loop != NULL){
                    if(loop->value != -1){
                        v = visit(nodes, loop->value, sorted);
                    }
                    if(v == "Stop"){
                        return v;
                    }
                    loop = loop->nextEdge;
                }
                nodes->at(ind)->state = "P";
                sorted->push_front(nodes->at(ind)->vert);
                return "Continue";
            }
     
        };
        
    }

}


int main(int argc, char* argv[]){

    // Have user create tasks
    std::vector<std::string>* userInput = new std::vector<std::string>();
    std::string input;
    std::cout << "Input set of tasks!" << std::endl;
    while(input !="Done"){
        std::cout << "Input task " << std::to_string(userInput->size() + 1) << " or type \"Done\"" << std::endl;
        //std::cin >> input;
        getline(std::cin, input);
        if(input != "Done"){
            userInput->push_back(input);
            input = "";
        }
    }
    std::cout << std::endl;
    
    // Have user create task relations
    //std::string tasks[4] = {"1: Paint Walls", "2: Install Wiring", "3: Lay Foundation", "4: Roofing"};
    DataStructures::Algorithms::DiGraph* taskGraph = new DataStructures::Algorithms::DiGraph(userInput->size());
    std::cout << "Input set task relations as integer pairs!" << std::endl;
    int input1 = 0;
    int input2 = 0;
    while(input1 != -1 && input2 != -1){
        std::cout << "Input relation 1 or type \"-1\" if Done" << std::endl;
        std::cin >> input1;
        if(input1 == -1){
            break;
        }
        std::cout << "Input relation 2 or type \"-1\" if Done" << std::endl;
        std::cin >> input2;
        if(input2 == -1){
            break;
        }
        taskGraph->AddEdge(input1 - 1,input2 - 1); //Adjust for zero indexing
    }
    std::cout << std::endl;
    
    // Print relations
    taskGraph->Print();
    std::deque<int>* x = taskGraph->TopologicalSort();
    std::cout << "Topological Sort!" << std::endl;
    while(d->size() > 0){
        if(d->at(0) == -1){
            std::cout << "Not a DAG!" << std::endl;
            break;
        }
        std::cout << std::to_string(d->at(0) + 1) << ": " << userInput->at(d->at(0)) << std::endl;
        d->pop_front();
    }
    delete d;
    delete taskGraph;
    delete userInput;
    return 0;
}



