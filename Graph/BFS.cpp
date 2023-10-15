#include <iostream>
#include <queue>
#define MAX_SIZE 50
using namespace std;

typedef struct Node{
	int data;
	Node* next;
} Node;

typedef struct graph{
	Node *adj[MAX_SIZE];
	bool visit[MAX_SIZE];
}graph;

Node* CreateNode(int);
void insert(graph*, int, int);
void BFS(int, graph*);
void buildgraph(graph*);

int main(int argc, char *argv[]) {
	graph* g = new graph;
	
	//buildgraph(g);
	insert(g, 0, 1);insert(g, 0, 3);
	insert(g, 1, 0);insert(g, 1, 3);insert(g, 1, 2);insert(g, 1, 5);insert(g, 1, 6);
	insert(g, 2, 1);insert(g, 2, 3);insert(g, 2, 5);insert(g, 2, 4);
	insert(g, 3, 0);insert(g, 3, 1);insert(g, 3, 2);insert(g, 3, 4);
	insert(g, 4, 2);insert(g, 4, 3);insert(g, 4, 6);
	insert(g, 5, 1);insert(g, 5, 2);
	insert(g, 6, 1);insert(g, 6, 6);
	
	BFS(0, g);
	
	return 0;
}

Node* CreateNode(int data){
	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void insert(graph* g, int v, int neighbor){
	Node* newNode = CreateNode(neighbor);
	newNode->next = g->adj[v];
	g->adj[v] = newNode;
}

void buildgraph(graph* g){
	for(int i = 0; i < MAX_SIZE; i++)
		g->visit[i] = false;
	
	int vertice, edge, neighbor;
	cout << "input the number of all the vertices: ";
	cin >> vertice;
	
	for(int i = 0; i < vertice; i++){
		printf("input total number of all the edges of node[%d]: ", i);
		cin >> edge;
		for(int j = 0; j < edge; j++){
			cout << "input the value: ";
			cin >> neighbor;
			insert(g, i, neighbor);
		}
	}
}

void BFS(int s, graph* g){
	queue<int> q;
	q.push(s);
	g->visit[s] = true;
	Node* head = g->adj[s];
	
	while( !q.empty() ){
		while( head ){
			if( !g->visit[head->data] ){
				q.push(head->data);
				g->visit[head->data] = true;
			}
			head = head->next;
		}
		cout << q.front() << ' ';
		q.pop();
		head = g->adj[q.front()];
	}
}



//#include <iostream>
//#include <queue>
//#define MAX_SIZE 50
//using namespace std;
//
//typedef struct graph{
//	int vertex, edge;
//	bool visit[MAX_SIZE];
//	int AM[MAX_SIZE][MAX_SIZE];
//} graph;
//
//graph* CreateGraph(int, int);
//void buildgraph(graph*);
//void BFS(graph*);
//
//int main(){
//	graph* g = CreateGraph(7, 22);
//	buildgraph(g);
//	BFS(g);
//	
//	return 0;
//}
//
//graph* CreateGraph(int vertexnum, int edgenum){
//	graph* g = new graph;
//	g->vertex = vertexnum;
//	g->edge = edgenum;
//	memset(g->visit, false, sizeof(g->visit));
//	memset(g->AM, 0, sizeof(g->AM));
//	return g;
//}
//
//void buildgraph(graph* g){
//	int start, end;
//	for(int i = 0; i < g->edge; i++){
//		cin >> start >> end;
//		g->AM[start][end] = g->AM[end][start] = 1;
//	}
//}
//
//void BFS(graph* g){
//	int s = 0, e;
//	queue<int> q;
//	q.push(s);
//	g->visit[s] = true;
//	
//	while( !q.empty() ){
//		for(e = 0; e < g->vertex; e++)
//			if( g->AM[s][e] && !g->visit[e] ){
//				q.push(e);
//				g->visit[e] = true;
//			}
//		cout << q.front() << ' ';
//		q.pop();
//		s = q.front();
//	}
//}