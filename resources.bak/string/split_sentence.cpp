#include <bits/stdc++.h>
using namespace std;

// 	Se tiver lido alguma coisa antes com o cin
// 	É necessario limpar o buffer com cin.ignore();
// 	Exemplo:
// 		cin >> n; // Deixa o '\n' no buffer
// 		cin.ignore(); // Ignora esse '\n'

string read_line(){
	string s;
	getline(cin, s);
	return s;
}

vector<string> split_sentence(string s){
	stringstream ss(s);
	string word;
	vector<string> v;
	while(getline(ss, word, ' ')) v.push_back(word);
	return v;
}