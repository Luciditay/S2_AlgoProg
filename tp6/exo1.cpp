#include "lib/tp6.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;

void Graph::buildFromAdjenciesMatrix(int **adjacencies, int nodeCount)
{// On va remplir le tableau de nodes selon la matrice adjacencies
        for (int i=0; i<nodeCount; i++)
        {
            GraphNode* sourceNode = new GraphNode(i);
            this->appendNewNode(sourceNode);

            for (int j=0; j<nodeCount; j++)
            {
                if(adjacencies[i][j]==1)
                {
                    this->nodes[i]->appendNewEdge(nodes[j], adjacencies[i][j]);
                }
            }
        }
}

void Graph::deepTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[])
{
    first->toString();
    visited[first->value] = true;
    nodes[nodesSize]=first;
    nodesSize++;

    for (first->edges; first->edges!=nullptr; first->edges= first->edges->next)
    {
        if (!first->edges->destination)
            this->deepTravel(first->edges->destination, nodes, nodesSize, visited);
    }
}

void Graph::wideTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[])
{
    std::queue<GraphNode*> nodeQueue;
    nodeQueue.push(first);
    visited[first->value]=true;

    while(!nodeQueue.empty())
    {
        GraphNode* tmpNode = nodeQueue.front();
        nodeQueue.pop();
        nodes[nodesSize]=tmpNode;
        nodesSize++;
        tmpNode->toString();
        visited[tmpNode->value]=true;

        for (tmpNode->edges; tmpNode->edges!=nullptr; tmpNode->edges=tmpNode->edges->next)
        {
            if (!visited[tmpNode->edges->destination->value])
                nodeQueue.push(tmpNode->edges->destination);
        }
    }

    //GraphNode* node = nodeQueue.front();
    //nodeQueue.pop();
}

bool Graph::detectCycle(GraphNode *first, bool visited[])
{
    visited[first->value]=true;

    for(first->edges; first->edges!=nullptr;  first->edges=first->edges->next)
    {
        if (!visited[first->edges->destination->value])
            return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow::instruction_duration = 150;
    w = new GraphWindow();
    w->show();

    return a.exec();
}
