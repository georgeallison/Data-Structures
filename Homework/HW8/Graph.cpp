#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>
#include "Graph.hpp"
using namespace std;
 
Graph::Graph()
{
}
 
Graph::~Graph()
{
}
 
void Graph::addEdge(string v1, string v2, int dist)
{
	for(unsigned int i = 0; i < vertices.size(); i++)
	{
        if(vertices[i].name == v1)
        {
            for(unsigned int j = 0; j < vertices.size(); j++)
            {
                if(vertices[j].name == v2 && i != j)
                {
                    adjVertex av;
                    av.v = &vertices[j];
                    av.distance = dist;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}
 
void Graph::addVertex(string n)
{  
	if(findVertex(n) == NULL)
	{
		vertex v;
		v.name = n;
		v.visited = false;
		v.district = -1;
		vertices.push_back(v);
	}
}
 
void Graph::displayEdges()
{
    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i].district << ":" <<vertices[i].name << "-->";
        for(unsigned int j = 0; j < vertices[i].adj.size(); j++)
        {
            cout << vertices[i].adj[j].v->name;
            cout << " (" << vertices[i].adj[j].distance << " miles)";
            if (j != vertices[i].adj.size()-1)
                cout << "***";
        }
        cout << endl;
    }
}
 
void Graph::assignDistricts()
{
    // Starting district numbers at 1
    int distID = 1;
 
    // For each of the vertices
    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        // Only consider a vertex that has not been assigned a district.
        if (vertices[i].district == -1)
        {
            // Run breadth first traversal and assign each node in the network to this district.
            BFTraversalLabel(vertices[i].name,distID);
            distID++;
        }
    }
}
 
void Graph::BFTraversalLabel(std::string startingCity, int distID)
{
	queue<vertex*> q;
	vertex *start;
 
	for(unsigned int i = 0; i < vertices.size(); i++)
	{
		vertices[i].visited = false;
	}
 
	for(unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].name == startingCity)
		{
			start->visited = true;        
			start = &vertices[i];
			break;
		}
	}
	
	start->district = distID;
	q.push(start);
 
	while (q.empty() != true)
	{
		vertex * u = q.front();        
		q.pop();                       
		for(unsigned int i=0;i<u->adj.size();i++) 
		{
            if (u->adj[i].v->visited==false)
            {
                u->adj[i].v->visited = true;
                q.push(u->adj[i].v);
                u->adj[i].v->district = distID;
			}
		}
	}
}	
 
vertex * Graph::findVertex(std::string name)
{
	for(unsigned int i = 0; i < vertices.size(); i++)
	{
		if(vertices[i].name == name)
		{
			return &vertices[i];
		}
	}
		return NULL;
}
