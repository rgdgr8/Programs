#include<iostream>
using namespace std;

void printVector(vector<int>& v){
	for(int i : v)
		cout<<i<<" ";
	cout<<endl;
}

void printGraph(vector<pair<int, vector<int> > >& v){
	for(int i=0;i<v.size();i++){
		cout<<i<<" val:"<<v[i].first<<endl;
		printVector(v[i].second);
	}
}
