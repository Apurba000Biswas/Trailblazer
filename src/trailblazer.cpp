
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
double heuristic(RoadGraph& graph, Vertex* start, Vertex* end);
void dijkastraAstarHelper(RoadGraph& graph, Vertex* start,
                                          Vertex* end, bool isDijksatra, Map<string, Vertex*>& predecesorMap);

Path breadthFirstSearch(RoadGraph& graph, Vertex* start, Vertex* end) {
    Queue<Vertex*> queue;
    Set<Vertex*> visitedNeighbors;
    Map<string, Vertex*> predecesorMap;

    if(start == end){
        Path path;
        path.add(start);
        return path;
    }

    predecesorMap.add(start->name, start);
    queue.enqueue(start);

    while(!queue.isEmpty()){
        Vertex* currentVertex = queue.dequeue();
        if(currentVertex == end) break;

        if(!visitedNeighbors.contains(currentVertex)){
            visitedNeighbors.add(currentVertex);
            currentVertex->setColor(GREEN);

            Set<Vertex*> neighbors = graph.getNeighbors(currentVertex);
            for(Vertex* curNeighbor : neighbors){

                if(!visitedNeighbors.contains(curNeighbor)){
                    queue.enqueue(curNeighbor);
                    curNeighbor->setColor(YELLOW);
                    if(!predecesorMap.containsKey(curNeighbor->name)){
                        predecesorMap.add(curNeighbor->name, currentVertex);
                    }
                }
            }
        }
    }

    return buildPath(predecesorMap,start ,end);
}

Path buildPath(Map<string, Vertex*>& predecesorMap,Vertex* start ,Vertex* end){
    if(!predecesorMap.containsKey(end->name)){
        Path path;
        return path;
    }

    Stack<Vertex*> pathStack;
    Path path;
    pathStack.push(end);
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
        path.add(pathNode);
    }
    return path;
}





Path dijkstrasAlgorithm(RoadGraph& graph, Vertex* start, Vertex* end) {

    if(start == end){
        Path path;
        path.add(start);
        return path;
    }

    Map<string, Vertex*> predecesorMap;
    dijkastraAstarHelper(graph, start, end, true, predecesorMap);
    return buildPath(predecesorMap, start, end);
}


void dijkastraAstarHelper(RoadGraph& graph, Vertex* start,
                                          Vertex* end, bool isDijksatra,
                                          Map<string, Vertex*>& predecesorMap){
    PriorityQueue<Vertex*> pQueue;
    Set<Vertex*> visited;
    Set<Vertex*> pQueueDataSet;

    predecesorMap.add(start->name, start);
    double priority = (isDijksatra)? 0.0 : heuristic(graph, start, end);
    pQueue.enqueue(start, priority);
    while(!pQueue.isEmpty()){
        Vertex* curVertex = pQueue.dequeue();
        visited.add(curVertex);
        curVertex->setColor(GREEN);
        if(curVertex == end) break;

        Set<Vertex*> neighbors = graph.getNeighbors(curVertex);
        for(Vertex* curNeighbor : neighbors){
            if(!visited.contains(curNeighbor)){
                Edge* curNeighborEdge = graph.getEdge(curVertex, curNeighbor);
                double newCost = curVertex->cost + curNeighborEdge->cost;

                if(pQueueDataSet.contains(curNeighbor)){
                    double oldCost = curNeighbor->cost;

                    if(newCost < oldCost){
                        curNeighbor->cost = newCost;
                        priority = (isDijksatra) ? newCost : (newCost + heuristic(graph, curNeighbor, end));
                        pQueue.changePriority(curNeighbor, priority);

                        pQueueDataSet.add(curNeighbor);
                        predecesorMap.add(curNeighbor->name, curVertex);
                    }
                }else{
                    // its brand new neighbor
                    curNeighbor->cost = newCost;
                    priority = (isDijksatra) ? newCost : (newCost + heuristic(graph, curNeighbor, end));
                    pQueue.enqueue(curNeighbor, priority);
                    pQueueDataSet.add(curNeighbor);
                    curNeighbor->setColor(YELLOW);
                    predecesorMap.add(curNeighbor->name, curVertex);
                }
            }
        }
    }
}



Path aStar(RoadGraph& graph, Vertex* start, Vertex* end) {

    if(start == end){
        Path path;
        path.add(start);
        return path;
    }

    Map<string, Vertex*> predecesorMap;
    dijkastraAstarHelper(graph, start, end, false , predecesorMap);

    return buildPath(predecesorMap, start, end);
}


double heuristic(RoadGraph& graph, Vertex* start, Vertex* end){
    double crowFlyDistance = graph.getCrowFlyDistance(start, end);
    double maxRoadSpeed = graph.getMaxRoadSpeed();
    return crowFlyDistance/maxRoadSpeed;
}

Path alternativeRoute(RoadGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Path emptyPath;
    return emptyPath;
}

