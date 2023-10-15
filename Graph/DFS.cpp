//#include <iostream>
//#include <stack>
//#define MAX_SIZE 50
//using namespace std;
//
//typedef struct graph{
//	int vertex, edge;
//	bool visit[MAX_SIZE];
//	int AM[MAX_SIZE][MAX_SIZE];
//} graph;
//
//void buildgraph(graph*);
//void DFS(graph*, int);
//
//int main(int argc, char *argv[]) {
//	graph* g = new graph;
//	buildgraph(g);
//	DFS(g, 0);
//	
//	return 0;
//}
//
//void buildgraph(graph* g){
//	int i, j;
//	memset(g->visit, false, sizeof(g->visit));
//	memset(g->AM, 0, sizeof(g->AM));
//	
//	cout << "type in number of vertices: "; cin >> g->vertex;
//	cout << "type in number of edges: "; cin >> g->edge;
//	
//	for(i = 0; i < g->edge; i++){
//		int s, e;
//		cout << "type in start and end index: ";  cin >> s >> e;
//		g->AM[s][e] = 1;
//	}
//}
//
//void DFS(graph* g, int index){
//	int s = index, e;
//	for(e = 0; e < g->vertex; e++){
//		if( g->AM[s][e] && !g->visit[e] ){
//			cout << e << ' ';
//			g->visit[e] = true;
//			DFS(g, e);
//		}
//	}
//}




#include <iostream>
using namespace std;

typedef struct Node{
	int data;
	Node* next;
} Node;

typedef struct graph{
	int vertex, edge;
	bool* visit;
	Node** adjlist;
} graph;

Node* CreateNode(int);
graph* CreateGraph(int);
void insert(graph*, int, int);
void DFS(graph*, int);

int main(){
	graph* g = CreateGraph(7);
	
	insert(g, 0, 1);insert(g, 0, 3);
	insert(g, 1, 0);insert(g, 1, 3);insert(g, 1, 2);insert(g, 1, 5);insert(g, 1, 6);
	insert(g, 2, 1);insert(g, 2, 3);insert(g, 2, 5);insert(g, 2, 4);
	insert(g, 3, 0);insert(g, 3, 1);insert(g, 3, 2);insert(g, 3, 4);
	insert(g, 4, 2);insert(g, 4, 3);insert(g, 4, 6);
	insert(g, 5, 1);insert(g, 5, 2);
	insert(g, 6, 1);insert(g, 6, 6);
	
	DFS(g, 0);
	
	return 0;
}

Node* CreateNode(int data){
	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

graph* CreateGraph(int vertex){
	graph* g = (graph*)malloc(sizeof(graph));
	g->vertex = vertex;
	g->visit = (bool*)malloc(sizeof(bool) * vertex);
	g->adjlist = (Node**)malloc(sizeof(Node*) * vertex);
	
	for(int i = 0; i < vertex; i++){
		g->visit[i] = false;
		g->adjlist[i] = NULL;
	}
	
	return g;
}

void insert(graph* g, int vertice, int neighbor){
	Node* newNode = CreateNode(neighbor);
	newNode->next = g->adjlist[vertice];
	g->adjlist[vertice] = newNode;
}

void DFS(graph* g, int s){
	Node* head = g->adjlist[s];
	while( head ){
		if( !g->visit[head->data] ){
			cout << head->data << ' ';
			g->visit[head->data] = true;
			DFS(g, head->data);
		}
		head = head->next;
	}
}