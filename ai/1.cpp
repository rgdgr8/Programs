#include <iostream>
#include <utility>
#include "bfs.cpp"
#include "dfs.cpp"
#include "utils.cpp"
using namespace std;

int main(){
	vector<pair<int, vector<int> > > graph;
	int inp = 0;
	cout<<"Enter the total number of vertices"<<endl;
	cin>>inp;
	cout<<"Vertices are numbered from 0"<<endl;
	int vertex = 0;
	while(vertex<inp){
		cout<<"Enter the value for vertex "<<vertex<<endl;
	       	int val;
		cin>>val;	
		pair<int, vector<int> > p;
		p.first = val;
		p.second = vector<int>();
		graph.push_back(p);
		
		cout<<"Enter the number of edges for vertex "<<vertex<<endl;
		int edges;
		cin>>edges;

		if(edges>0)
			cout<<"Enter the edgelist for vertex "<<vertex<<endl;
		for(int i=0;i<edges;i++){
			int edge;
			cin>>edge;
			graph[vertex].second.push_back(edge);
		}
		vertex++;
	}
	printGraph(graph);

	cout<<"Search value: ";
	int val;
	cin>>val;
	cout<<"1. BFS\n2. DFS\n3. Depth Limited Search\n4. Iterative deepening search\n5. Iterative broadening search\n*. Exit"<<endl;
	int opt = 0;
	cin>>opt;
	vector<int>* traversal;
	while(opt>0 && opt<6){
		int limit;
		switch(opt){
			case 1: traversal = bfs(graph, val);break;
			case 2: traversal = dfs(graph, val);break;
			case 3: cout<<"Enter limit:";
				cin>>limit;
				traversal = dfs(graph, val, limit);break;
			case 4: cout<<"Enter max depth of the graph/tree(src/root node depth is 0): ";
		                cin>>limit;
				traversal = ids(graph, val, limit);break;
			case 5: cout<<"Enter max no. of children a node can have in the graph/tree: ";
				cin>>limit;
				traversal = ibs(graph, val, limit);break;
		}

		if(traversal[0].empty())
			cout<<"Not found"<<endl;
		else{
			cout<<"Found at vertex "<<traversal[1][traversal[1].size()-1]<<endl;
			cout<<"Path:"<<endl;
			printVector(traversal[0]);
			cout<<"Order:"<<endl;
			printVector(traversal[1]);
		}
		delete[] traversal;//cleanup	

		cout<<"Search value: ";
		cin>>val;
		cout<<"1. BFS\n2. DFS\n3. Depth Limited Search\n4. Iterative deepening search\n5. Iterative broadening search\n*. Exit"<<endl;
		cin>>opt;
	};

	return 0;
}
