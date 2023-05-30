#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class KeywordFinder {
private:
    static const int MAX_WORDS = 10000;
    map<string, int> wordFrequencies;

public:
    void countWords(const string& text) {
        string word;
        int start = 0;
        int end = 0;
        while (end <= text.size()) {
            if (end == text.size() || text[end] == ' ') {
                word = text.substr(start, end - start);

                // Convert the word to lowercase
                transform(word.begin(), word.end(), word.begin(), ::tolower);

                wordFrequencies[word]++;

                start = end + 1;
            }

            end++;
        }
    }

    vector<pair<string, int>> getTopKeywords(int count) const {
        vector<pair<string, int>> topKeywords;
        for (const auto& pair : wordFrequencies) {
            topKeywords.push_back(pair);
        }

        sort(topKeywords.begin(), topKeywords.end(),
            [](const pair<string, int>& a, const pair<string, int>& b) {
                return a.second > b.second;
            });

        if (count > topKeywords.size()) {
            count = topKeywords.size();
        }

        topKeywords.resize(count);
        return topKeywords;
    }
};

int main() {
    string filePath;
    cout << "Enter the path to the file: ";
    cin >> filePath;

    ifstream inputFile(filePath);
    if (!inputFile) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string text;
    string line;
    while (getline(inputFile, line)) {
        text += line + " ";
    }

    KeywordFinder keywordFinder;
    keywordFinder.countWords(text);

    int keywordCount;
    cout << "Enter the number of keywords to find: ";
    cin >> keywordCount;

    vector<pair<string, int>> topKeywords = keywordFinder.getTopKeywords(keywordCount);

    cout << "Top " << keywordCount << " keywords in the article:" << endl;
    for (const auto& pair : topKeywords) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
