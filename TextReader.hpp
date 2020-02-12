#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct Text{
	string label;
	vector<string> tokens;
};

class TextReader{
public:
	vector<Text> ReadTexts(istream &f);
};

vector<Text> TextReader::ReadTexts(istream &f){
	vector<Text> texts;
	string line;
	WordTokenizer tokenizer;

	while (getline(f, line)) {	
		stringstream ss(line);
		string label;
		ss >> label;
		vector<string> text = tokenizer.Tokenize(ss);
		texts.push_back({label, text});
	}

	return texts;
}