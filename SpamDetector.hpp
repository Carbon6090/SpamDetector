#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
#include "WordTokenizer.hpp"
#include "TextReader.hpp"

using namespace std;

class SpamDetector{
	struct ClassStat{
		map<string, int> dictionary;
		int wordsCount;
		int textCount;
	};
	vector<Text> texts;
	ClassStat spamStat;
	ClassStat hamStat;
	map<string, int> allDictionary;
	map<string, int> MakeDictionary(string label = "");
	double GetScore(string label, const vector<string>& tokens);
public:
	void ReadTexts(const string& path);
	void ShowStat();
	bool CheckSpam(const vector<string>& tokens, bool verbose);
};

double SpamDetector::GetScore(string label, const vector<string>& tokens){
	ClassStat stat = label == "spam" ? spamStat : hamStat;
	double score = log((double)stat.textCount / texts.size());
	
	for (int i = 0; i < tokens.size(); i++){
		int wc = stat.dictionary.find(tokens[i]) != stat.dictionary.end() ? stat.dictionary[tokens[i]] : 0;
		score += log((wc + 1.0) / (stat.wordsCount + allDictionary.size()));
	}

	return score;
}

map<string, int> SpamDetector::MakeDictionary(string label){
	map<string, int> dict;

	for (int i = 0; i < texts.size(); i++){
		if (label == texts[i].label || label == ""){
			for (int j = 0; j < texts[i].tokens.size(); j++){
				if (dict.find(texts[i].tokens[j]) != dict.end())
					dict[texts[i].tokens[j]]++;
				else
					dict[texts[i].tokens[j]] = 1;
			}
		}
	}
	return dict;
}

void SpamDetector::ReadTexts(const string& path){
	ifstream f(path);
	WordTokenizer tokenizer;
	TextReader reader;

	if (!f)
		throw string("Unable to open file '") + path + "'";
	
	spamStat.wordsCount = 0;
	spamStat.textCount = 0;
	hamStat.wordsCount = 0;
	hamStat.textCount = 0;

	texts = reader.ReadTexts(f);
	
	for (int i = 0; i < texts.size(); i++){
		if (texts[i].label == "spam"){
			spamStat.textCount++;
			spamStat.wordsCount += texts[i].tokens.size();
		}
		else {
			hamStat.textCount++;
			hamStat.wordsCount += texts[i].tokens.size();
		}
	}
	
	spamStat.dictionary = MakeDictionary("spam");
	hamStat.dictionary = MakeDictionary("ham");
	allDictionary = MakeDictionary();
}

void SpamDetector::ShowStat(){
	cout << "total texts: " << texts.size() << endl;
	cout << "  ham texts: " << hamStat.textCount << endl;
	cout << " spam texts: " << spamStat.textCount << endl << endl;
	cout << "total unique words: " << allDictionary.size() << endl;
	cout << "  ham unique words: " << hamStat.dictionary.size() << endl;
	cout << " spam unique words: " << spamStat.dictionary.size() << endl << endl;
	cout << " ham total words: " << hamStat.wordsCount << endl;
	cout << "spam total words: " << spamStat.wordsCount << endl << endl;
}

bool SpamDetector::CheckSpam(const vector<string>& tokens, bool verbose){
	double ham = exp(GetScore("ham", tokens));
	double spam = exp(GetScore("spam", tokens));
	double sum = ham + spam;
	ham /= sum;
	spam /= sum;
	if (verbose){
		cout << "P(spam)" << spam << endl;
		cout << "P(ham)" << ham << endl;
	}
	return spam > 0.5;
}