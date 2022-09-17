#include <vector>
#include <queue>
using namespace std;

vector<int>* bfs(vector<pair<int, vector<int> > >& graph, int val, int breadth = -1){
	queue<int> q;
	q.push(0);
	vector<int>* traversal = new vector<int>[2];
	int order[graph.size()];
	order[0] = 0;
	bool visited[graph.size()];
	visited[0] = true;
	for(int i=1;i<graph.size();i++)
		visited[i] = false;
	bool flag = false;

	while(!q.empty()){
		int v = q.front();
		q.pop();
		traversal[1].push_back(v);
		
		if(graph[v].first == val){
			flag = true;
			break;
		}

		if(breadth==-1)
			breadth = graph[v].second.size();
		else
			breadth = breadth > graph[v].second.size() ? graph[v].second.size() : breadth;

		for(int i=0;i<breadth;i++){
			int ind = graph[v].second[i];
			//cout<<v<<" "<<graph[v][i]<<" "<<visited[graph[v][i]]<<endl;
			if(visited[ind]==false){
				visited[ind] = true;
				order[ind] = v;
				q.push(ind);
			}
		}
	}
	
	if(flag==false)
		traversal[0].clear();
	else{
		int ind = traversal[1][traversal[1].size()-1];
		while(ind!=0){
			traversal[0].push_back(ind);
			ind = order[ind];
		}
		traversal[0].push_back(0);
		reverse(traversal[0].begin(), traversal[0].end());
	}

	return traversal;	
}

vector<int>* ibs(vector<pair<int, vector<int> > >& graph, int val, int maxBreadth){
	vector<int>* traversal = new vector<int>[2];

	for(int i = 0; i <= maxBreadth; i++){
		auto temp = bfs(graph, val, i);
		if(!temp[0].empty()){
			traversal[0] = temp[0];
			traversal[1].insert(traversal[1].end(), temp[1].begin(), temp[1].end());
			delete[] temp;
			break;
		}else{
			traversal[1].insert(traversal[1].end(), temp[1].begin(), temp[1].end());
			delete[] temp;
		}
	}

	return traversal;
}
