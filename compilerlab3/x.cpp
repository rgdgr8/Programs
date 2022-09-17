#include <iostream>
#include <string>
#include <cctype>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<char,vector<string> > prods;

string[] rem_imm(char c)
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

	for (i = 0, k = 3; i < n; i++)
	{
		if (d[0] != d[k])
		{
			cout<<"Production: "<< i + 1;
			cout<<" does not have left recursion.";
			cout<<endl;

			if(isupper(d[k])){
				while(k<d.size() && d[k] !='|')
					b.push_back(d[k++]);
			}else{
				b.push_back(d[k++]);
			}
			
			b.push_back(d[0]);
			b += "'";
			
			if(i!=n-1)
				b += "|";
		}
		else
		{
			cout<<"Production: "<< i + 1 ;
			cout<< " has left recursion";
			cout<< endl;
			
			k++;
			while(k<d.size() && d[k] != '|')
				a.push_back(d[k++]);
			a.push_back(d[0]);
			a += "'|";
		}
		k++;
	}
	a += "#";
	cout << b << endl;
	cout << a << endl;
	return string[]{a,b};
}

void rem_left_rec(vector<char> heads){
	for(int i=0;i<heads.size();i++){
		ai = heads[i];
		for(int j=0;j<i;j++){
			aj = heads[j];
			vector<string>& aiprods = prods[ai];

			vector<string> rep; //replacement bodies
			for(int k=0;k<aiprods.size();k++){
				string& bi = aiprods[k];
				if(bi[0] == aj){
					aiprods.erase(advance(aiprods.begin(),k));
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

int main(){
	char in = 'y';
	vector<char> heads;
	while(in=='y'){
		char c;
		cout<<"Enter Non-Terminal(single capital letter): ";
		cin >> c;
		heads.push_back(c);
		
		cout<<"Enter number of productions: ";
		cin >> n;
		string flag;
		for (int i = 0; i < n; i++)
		{
			cout<<"Enter Production [terminating(if any) productions first]";
			cout<<i + 1<<" :";
			cin >> flag;
			prods[c].push_back(flag);
		}

		cout<<"Enter productions for another non-terminal? [y/n] ";
		cin>>in;
	}
	
	rem_left_rec(heads);
}
