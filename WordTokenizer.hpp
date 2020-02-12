#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class WordTokenizer{
public:
	bool IsDigit(char c);
	bool IsLetter(char c);
	char ToLower(char c);
	bool IsLetterOrDigit(char c);
	vector<string> Tokenize(istream &f);
};

bool WordTokenizer::IsDigit(char c){
	return (c >= '0' && c <= '9');
}

char WordTokenizer::ToLower(char c){
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' - 'a');
	if (c >= 'À' && c <= 'ß')
		return (c - 'À' - 'à');

	return c;
}

bool WordTokenizer::IsLetter(char c){
	return (c >= 'a' && c <= 'z') || (c >= 'à' && c <= 'ÿ') || (c >= 'A' && c <= 'Z') || (c >= 'À' && c <= 'ß') || (c == '_');
}

bool WordTokenizer::IsLetterOrDigit(char c){
	return IsDigit(c) || IsLetter(c);
}

vector<string> WordTokenizer::Tokenize(istream &f){
	vector<string> words;
	char c = f.get();
	
	while (!f.eof()){
		while (!f.eof() && !IsLetterOrDigit(c))
			c = f.get(); 

		string word = "";

		while (!f.eof() && (IsLetterOrDigit(c))){;
			word += ToLower(c); 
			c = f.get();
		}
		
		if(word != "")
			words.push_back(word);
	}
	return words;
}