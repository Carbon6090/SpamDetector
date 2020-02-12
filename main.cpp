#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "WordTokenizer.hpp"
#include "SpamDetector.hpp"
#include "TextReader.hpp"

using namespace std;

void Evaluate(string trainPath, string testPath) {
	SpamDetector detector; 
	TextReader reader; 
	detector.ReadTexts(trainPath); 
	detector.ShowStat();

	ifstream f(testPath);
	WordTokenizer tokenizer;

	string line;
	int correct = 0;
	int total = 0;

	vector<Text> texts = reader.ReadTexts(f);
	
	for (int i = 0; i < texts.size(); i++){
		string predict = detector.CheckSpam(texts[i].tokens, false) ? "spam" : "ham";

		if (predict == texts[i].label)
			correct++;

		total++;
	}

	cout << "accuracy: " << correct * 100.0 / total << "%" << endl;
}

int main(){
	setlocale(LC_ALL, "russian"); 
	Evaluate("data/train.csv", "data/test.csv");
}