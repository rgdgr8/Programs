#include <iostream>
#include <string>
#include <cctype>
#include <utility>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<char,vector<string> > prods;

void rem_imm(char c)
{
	int n = prods[c].size();
        int j, l, i, k;
	string d, a, b, flag;
	d.push_back(c);
	a += d + "\'->";
	d += "->";
	b += d;
	for (int i = 0; i < n; i++)
	{
		flag = prods[c][i];
		d += flag;
		if (i != n - 1)
		{
			d += "|";	
		}
	}
	cout<<"For immediate left recursion removal the Production Rule is: ";
	cout<<d<<endl;
	vector<pair<int,string> > rep;

	for (i = 0, k = 3; i < n; i++)
	{
		string x;

		if (d[0] != d[k])
		{
			cout<<"Production: "<< i + 1;
			cout<<" does not have left recursion.";
			cout<<endl;

			/*if(isupper(d[k])){
				while(k<d.size() && d[k] !='|')
					x.push_back(d[k++]);
			}else{
				x.push_back(d[k++]);
			}*/
			while(k<d.size() && d[k] !='|')
				x.push_back(d[k++]);
			x.push_back(d[0]);
			x.push_back('\'');
			rep.push_back(make_pair(i,x));

			b += x;
			b.push_back('|');
		}
		else
		{
			cout<<"Production: "<< i + 1 ;
			cout<< " has left recursion";
			cout<< endl;
			
			k++;
			while(k<d.size() && d[k] != '|')
				x.push_back(d[k++]);
			x.push_back(d[0]);
			x.push_back('\'');
			prods[d[0]-65].push_back(x);
			rep.push_back(make_pair(i,""));

			a += x;
			a.push_back('|');
		}
		k++;
	}
	
	if(prods[d[0]-65].size()>0){
		prods[d[0]-65].push_back("#");

		for(pair<int,string> p : rep)
			prods[d[0]][p.first] = p.second;
		
		for(int i=n-1;i>-1;i--)
			if(prods[d[0]][i]=="")
				prods[d[0]].erase(prods[d[0]].begin()+i);

		a += "#";
		if(b.back()=='|')
			b.pop_back();
		cout << b << endl;
		cout << a << endl;
	}else{
		prods.erase((d[0]-65));
	}
	cout<<endl;
}

void rem_left_rec(vector<char> heads){
	for(int i=0;i<heads.size();i++){
		char ai = heads[i];
		for(int j=0;j<i;j++){
			char aj = heads[j];
			vector<string>& aiprods = prods[ai];

			vector<string> rep; //replacement bodies
			for(int k=aiprods.size()-1;k>-1;k--){
				string& bi = aiprods[k];
				if(bi[0] == aj){
					aiprods.erase(aiprods.begin() + k);
					for(string& bj : prods[aj]){
						string s = bj + bi.substr(1);
						rep.push_back(s);
					}
				}
			}
			aiprods.insert(aiprods.end(), rep.begin(), rep.end());
		}

		rem_imm(ai);
	}
}

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
