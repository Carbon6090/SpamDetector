#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "WordTokenizer.hpp"
#include "SpamDetector.hpp"
#include "TextReader.hpp"

using namespace std;

void Evaluate(string trainPath, string testPath) {
	double fspam = 0;
	double fham = 0;
	double tham = 0;
	double tspam = 0;
	SpamDetector detector; 
	TextReader reader; 
	detector.ReadTexts(trainPath); 
	detector.ShowStat();

	ifstream f(testPath);
	WordTokenizer tokenizer;

	int correct = 0;
	int total = 0;

	vector<Text> texts = reader.ReadTexts(f);
	
	for (int i = 0; i < texts.size(); i++){
		bool isSpam = detector.CheckSpam(texts[i].tokens, false);

		if (!isSpam && texts[i].label == "ham") {
			correct++;
			tham++;
		}

		if (isSpam && texts[i].label == "ham")
			fham++;

		if (isSpam && texts[i].label == "spam") {
			correct++;
			tspam++;
		}

		if (!isSpam && texts[i].label == "spam")
			fspam++;

		total++;
	}

	cout << "accuracy: " << correct * 100.0 / total << "%" << endl;

	double precisionSpam = tspam / (tspam + fspam);
	double recallSpam = tspam / (tspam + fham);
	double F1Spam = 2 * precisionSpam * recallSpam / (precisionSpam + recallSpam);

	double precisionHam = tham / (tham + fham);
	double recallHam = tham / (tham + fspam);
	double F1Ham = 2 * precisionHam * recallHam / (precisionHam + recallHam);

	cout << "Spam: precision: " << precisionSpam << ", recall: " << recallSpam << ", F1: " << F1Spam << endl;
	cout << "Ham: precision: " << precisionHam << ", recall: " << recallHam << ", F1: " << F1Ham << endl;
	cout << "F1: " << (F1Ham + F1Spam) / 2 << endl;
}

int main(){
	Evaluate("data/train.csv", "data/test.csv");
	setlocale(LC_ALL, "russian"); 
	string s;
	WordTokenizer tokenizer;
	SpamDetector detector;
	detector.ReadTexts("data/all.csv");
	while (true){
		cout << ">";
		getline(cin, s);
		if(s == "")
			break;
		detector.CheckSpam(tokenizer.Tokenize(s), true);
	}
}