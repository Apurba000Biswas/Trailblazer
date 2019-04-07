
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
                                          Vertex* end, bool isDijksatra, Map<string,
                                          Vertex*>& predecesorMap, Edge* ignoreEdge);
void buildEdgesFromBestPath(Vector<Edge*>& bestPathEdges, Path& bestPath
                            , RoadGraph& graph, Set<Vertex*>& bestPathNodes);
Path getBestAlterNativePath(Set<Vertex*>& bestPathNodes, PriorityQueue<Path>& alternativePathsPQ);




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
    dijkastraAstarHelper(graph, start, end, true, predecesorMap, nullptr);
    return buildPath(predecesorMap, start, end);
}

void dijkastraAstarHelper(RoadGraph& graph, Vertex* start,
                                          Vertex* end, bool isDijksatra,
                                          Map<string, Vertex*>& predecesorMap,
                                          Edge* ignoreEdge){
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
                if(curNeighborEdge == ignoreEdge)continue;
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
    dijkastraAstarHelper(graph, start, end, false , predecesorMap, nullptr);

    return buildPath(predecesorMap, start, end);
}

double heuristic(RoadGraph& graph, Vertex* start, Vertex* end){
    double crowFlyDistance = graph.getCrowFlyDistance(start, end);
    double maxRoadSpeed = graph.getMaxRoadSpeed();
    return crowFlyDistance/maxRoadSpeed;
}

Path alternativeRoute(RoadGraph& graph, Vertex* start, Vertex* end) {
    if(start == end){
        Path path;
        path.add(start);
        return path;
    }

    Map<string, Vertex*> predecesorMap;
    dijkastraAstarHelper(graph, start, end, false , predecesorMap, nullptr);
    Path bestPath = buildPath(predecesorMap, start, end);
    Vector<Edge*> bestPathEdges;
    Set<Vertex*> bestPathNodes;
    buildEdgesFromBestPath(bestPathEdges, bestPath, graph, bestPathNodes);

    PriorityQueue<Path> alternativePathsPQ;
    for(Edge* curEdge : bestPathEdges){
        predecesorMap.clear();
        dijkastraAstarHelper(graph, start, end, false , predecesorMap, curEdge);
        Path alternative = buildPath(predecesorMap, start, end);
        if(alternative.size() != 0){
            double pathCost = alternative.get(alternative.size()-1)->cost;
            alternativePathsPQ.enqueue(alternative, pathCost);
        }
    }

    Path alterNativePath = getBestAlterNativePath(bestPathNodes, alternativePathsPQ);
    return alterNativePath;
}

Path getBestAlterNativePath(Set<Vertex*>& bestPathNodes, PriorityQueue<Path>& alternativePathsPQ){
    double unFoundNode;
    double totalNode = bestPathNodes.size();

    while (!alternativePathsPQ.isEmpty()) {
        Path currentPath = alternativePathsPQ.dequeue();
        unFoundNode = 0.0;

        for(Vertex* node : currentPath){
            if(!bestPathNodes.contains(node)){
                unFoundNode = unFoundNode + 1.0;
            }
        }
        double diffrence = unFoundNode/totalNode;
        if(diffrence > SUFFICIENT_DIFFERENCE){
            return currentPath;
        }
    }

    Path emptyPath;
    return emptyPath;
}

void buildEdgesFromBestPath(Vector<Edge*>& bestPathEdges, Path& bestPath
                            , RoadGraph& graph, Set<Vertex*>& bestPathNodes){
    int i;
    for(i=0; i < (bestPath.size()-1); i++){
        Vertex* curPathNode = bestPath.get(i);
        Vertex* nextPathNode = bestPath.get(i+1);
        Edge* curEdge = graph.getEdge(curPathNode, nextPathNode);
        bestPathEdges.add(curEdge);
        bestPathNodes.add(curPathNode);
    }
    bestPathNodes.add(bestPath.get(i));
}

