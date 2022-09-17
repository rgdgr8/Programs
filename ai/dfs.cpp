#include <vector>
#include <queue>
using namespace std;

void dfs(vector<pair<int, vector<int> > >& graph, int root, bool* v, vector<int>* traversal, int val, bool* flag, int limit = -1, int level = 0){
	if(limit>-1 && level>limit)
		return;

	v[root] = true;
	traversal[1].push_back(root);

	if(graph[root].first != val){
		for(int& i : graph[root].second){
			if(v[i]==false){
				dfs(graph, i, v, traversal, val, flag, limit, level+1);
				if(*flag==true){
					traversal[0].push_back(i);
					return;
				}
			}
		}
	}else
		*flag = true;
}



vector<int>* dfs(vector<pair<int, vector<int> > >& graph, int val, int limit = -1){
	vector<int>* traversal = new vector<int>[2];
	bool v[graph.size()];
	for(int i = 0; i < graph.size(); i++)
		v[i] = false;

	bool* flag = new bool();
	*flag = false;
	dfs(graph, 0, v, traversal, val, flag, limit);
	if(*flag==false){
		traversal[0].clear();
	}
	else{
		traversal[0].push_back(0);
		reverse(traversal[0].begin(), traversal[0].end());
	}
	delete flag;

	return traversal;
}	

vector<int>* ids(vector<pair<int, vector<int> > >& graph, int val, int maxDepth){
	vector<int>* traversal = new vector<int>[2];

	for(int i = 0; i <= maxDepth; i++){//max depth can be graph.size() if maxDepth passing is not allowed
		auto temp = dfs(graph, val, i);
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
