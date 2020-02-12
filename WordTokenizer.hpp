#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class WordTokenizer{
	bool IsDigit(char c);
	bool IsLetter(char c);
	char ToLower(char c);
	bool IsLetterOrDigit(char c);
public:
	vector<string> Tokenize(istream &f);
	vector<string> Tokenize(string s);
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

vector<string> WordTokenizer::Tokenize(string str){
	vector<string> words;
	int i = 0;

	while (i < str.length()){
		while ((i < str.length()) && !IsLetterOrDigit(str[i]))
			i++; 

		string word = "";

		while ((i < str.length()) && (IsLetterOrDigit(str[i]))){;
			word += ToLower(str[i]); 
			i++;
		}
		
		if(word != "")
			words.push_back(word);
	}

	return words;
}