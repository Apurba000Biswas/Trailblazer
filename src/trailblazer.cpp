// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "trailblazer.h"
#include "queue.h"
#include "set.h"
#include "pqueue.h"
#include "point.h"
#include "map.h"
#include "stack.h"

using namespace std;

// this makes Path an alias for the type Vector<Vertex*>
typedef Vector<Vertex*> Path;

// the minimum difference for an alternate route
const double SUFFICIENT_DIFFERENCE = 0.2;
Path buildPath(Map<string, Vertex*>& predecesorMap,Vertex* start ,Vertex* end);


Path breadthFirstSearch(RoadGraph& graph, Vertex* start, Vertex* end) {
    Queue<Vertex*> queue;
    Set<Vertex*> visitedNeighbors;
    Map<string, Vertex*> predecesorMap;

    predecesorMap.add(start->name, start);
    queue.enqueue(start);

    while(!queue.isEmpty()){
        Vertex* currentVertex = queue.dequeue();// visiting the first vertex in the queue
        if(currentVertex == end) break; // when we reach our destination index, break the loop

        if(!visitedNeighbors.contains(currentVertex)){ // is this vertex visited before?
            visitedNeighbors.add(currentVertex);// make it visited
            currentVertex->setColor(GREEN); // set its color to be green

            Set<Vertex*> neighbors = graph.getNeighbors(currentVertex); // find all neighbors of the current vertex
            for(Vertex* curNeighbor : neighbors){
                curNeighbor->setColor(YELLOW); // mark each neighbor to be yellow
                if(!visitedNeighbors.contains(curNeighbor)){ // is this neighbor visited before?
                    queue.enqueue(curNeighbor); // if not then add this neighbor to the queue
                    if(!predecesorMap.containsKey(curNeighbor->name)){ // is this neighbor already has a predecessor?
                        predecesorMap.add(curNeighbor->name, currentVertex); // if not make the current vertex to its precessor
                    }
                }
            }
        }
    }

    return buildPath(predecesorMap,start ,end);
}

Path buildPath(Map<string, Vertex*>& predecesorMap,Vertex* start ,Vertex* end){
    for(string key : predecesorMap){
        cout << "$$$$ Map Has [Key] = " << key << " [Value] = " << predecesorMap.get(key)->name << endl;
    }
    Stack<Vertex*> pathStack;
    Path path;
    pathStack.push(end); // push first the end vertex
    Vertex* predecesor = predecesorMap.get(end->name);
    while(true){

        pathStack.push(predecesor);
        predecesor = predecesorMap.get(predecesor->name);

        if(predecesor == start){
            if(pathStack.peek()!= start){
                pathStack.push(start);
            }
            break;
        }


    }
    while (!pathStack.isEmpty()) {
        Vertex* pathNode = pathStack.pop();
        cout << "** Path = " << pathNode->name << endl;
        path.add(pathNode);
    }

    return path;
}









Path dijkstrasAlgorithm(RoadGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Path emptyPath;
    return emptyPath;
}


Path aStar(RoadGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Path emptyPath;
    return emptyPath;
}

Path alternativeRoute(RoadGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Path emptyPath;
    return emptyPath;
}

