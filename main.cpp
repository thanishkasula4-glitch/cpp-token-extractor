// Group 5: Compiler Syntax Token Unique Extractor & Categorizer
// Beginner version: no menu, asks for tokens, then shows the result
// Topics used: vector, set, string, functions, loops, if

#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

set<string> keywordList = {"int", "float", "double", "char", "bool", "void",
                           "if", "else", "for", "while", "do", "switch",
                           "case", "break", "continue", "return", "class",
                           "struct", "public", "private", "const", "static"};

set<string> operatorList = {"+", "-", "*", "/", "%", "=", "==", "!=", "<",
                            ">", "<=", ">=", "&&", "||", "!", "++", "--",
                            ";", ",", "(", ")", "{", "}", "[", "]"};

bool isKeyword(string token) {
    return keywordList.count(token) == 1;
}

bool isOperator(string token) {
    return operatorList.count(token) == 1;
}

bool isNumber(string token) {
    for (int i = 0; i < token.size(); i++) {
        if (token[i] < '0' || token[i] > '9') {
            return false;
        }
    }
    return true;
}

// Read tokens until the user types "end". Returns the vector of tokens.
vector<string> readTokens() {
    vector<string> tokens;
    string word;
    cout << "Enter the tokens separated by spaces (type end to finish):" << endl;
    while (cin >> word && word != "end") {
        tokens.push_back(word);
    }
    return tokens;
}

// Count how many times one word appears in the vector
int countWord(vector<string> tokens, string word) {
    int count = 0;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i] == word) {
            count++;
        }
    }
    return count;
}

// Put only the keywords into a set (unique + sorted A-Z)
set<string> getUniqueKeywords(vector<string> tokens) {
    set<string> unique;
    for (int i = 0; i < tokens.size(); i++) {
        if (isKeyword(tokens[i])) {
            unique.insert(tokens[i]);
        }
    }
    return unique;
}

void showUniqueSorted(set<string> unique) {
    cout << endl << "Unique keywords (sorted A-Z):" << endl;
    int number = 1;
    for (string kw : unique) {
        cout << number << ". " << kw << endl;
        number++;
    }
}

// Count every item of a set in the tokens, then arrange highest to lowest
void showCountsHighToLow(string title, vector<string> tokens, set<string> group) {
    cout << endl << title << " (highest to lowest):" << endl;

    if (group.empty()) {
        cout << "None" << endl;
        return;
    }

    vector<string> words;
    vector<int> counts;

    for (string item : group) {
        words.push_back(item);
        counts.push_back(countWord(tokens, item));
    }

    int size = counts.size();

    // bubble sort: the biggest count moves to the front
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (counts[j] < counts[j + 1]) {
                int tempCount = counts[j];
                counts[j] = counts[j + 1];
                counts[j + 1] = tempCount;

                string tempWord = words[j];
                words[j] = words[j + 1];
                words[j + 1] = tempWord;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        cout << words[i] << " : " << counts[i] << endl;
    }
}

// Split all tokens into 4 groups and count every group
void categorize(vector<string> tokens) {
    set<string> keywords, operators, numbers, identifiers;

    for (int i = 0; i < tokens.size(); i++) {
        if (isKeyword(tokens[i])) {
            keywords.insert(tokens[i]);
        } else if (isOperator(tokens[i])) {
            operators.insert(tokens[i]);
        } else if (isNumber(tokens[i])) {
            numbers.insert(tokens[i]);
        } else {
            identifiers.insert(tokens[i]);
        }
    }

    showCountsHighToLow("Keyword counts", tokens, keywords);
    showCountsHighToLow("Operator counts", tokens, operators);
    showCountsHighToLow("Number counts", tokens, numbers);
    showCountsHighToLow("Identifier counts", tokens, identifiers);

    cout << endl << "Summary:" << endl;
    cout << "Unique keywords    : " << keywords.size() << endl;
    cout << "Unique operators   : " << operators.size() << endl;
    cout << "Unique numbers     : " << numbers.size() << endl;
    cout << "Unique identifiers : " << identifiers.size() << endl;
}

int main() {
    vector<string> tokens;

    // Keep asking until the user gives at least one token
    while (tokens.empty()) {
        tokens = readTokens();

        if (tokens.empty()) {
            if (cin.fail()) {          // no more input at all
                cout << "There are no tokens." << endl;
                return 0;
            }
            cout << "There are no tokens. Please enter the tokens." << endl;
            cout << endl;
        }
    }

    cout << endl << "Total tokens entered: " << tokens.size() << endl;

    set<string> unique = getUniqueKeywords(tokens);
    if (unique.empty()) {
        cout << endl << "No keywords found in the tokens." << endl;
    } else {
        showUniqueSorted(unique);
    }

    categorize(tokens);

    // set insert, find and erase take O(log n) time (balanced tree)
    return 0;
}