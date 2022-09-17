#include <iostream>
#include <string>
#include <cctype>
#include <utility>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<char,vector<string> > prods;

void printProds();
int main(){
	char in = 'y';
	vector<char> heads;
	while(in=='y'){
		char c;
		cout<<"Enter Non-Terminal(single capital letter): ";
		cin >> c;
		heads.push_back(c);
	
		int n;	
		cout<<"Enter number of productions: ";
		cin >> n;
		string flag;
		for (int i = 0; i < n; i++)
		{
			cout<<"Enter Production ";
			cout<<i + 1<<": ";
			cin >> flag;
			prods[c].push_back(flag);
		}

		cout<<"Enter productions for another non-terminal? [y/n] ";
		cin>>in;
	}
	printProds();
	
	rem_left_rec(heads);

	printProds();
}

void printProds(){
	for(auto i : prods){
		char k = i.first;
		if(k<65)
			cout<<(char)(k+65)<<"': ";
		else
			cout<<k<<": ";

		for(int i=0;i<prods[k].size();i++){
			cout<<prods[k][i];
			if(i!=prods[k].size()-1)
				cout<<" | ";
		}
		cout<<endl;
	}
}
