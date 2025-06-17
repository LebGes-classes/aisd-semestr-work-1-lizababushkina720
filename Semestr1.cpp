#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct Node {
    int count;
    string chars;
};

//  подсчет частоты символов
vector<Node> countFrequencies(const string& input) {
    vector<Node> symbols;
    unordered_map<char, int> charIndex;

    for (char c : input) {
        if (charIndex.find(c) != charIndex.end()) {
            symbols[charIndex[c]].count++;
        }
        else {
            charIndex[c] = symbols.size();
            symbols.push_back({ 1, string(1, c) });
        }
    }
    return symbols;
}

//  построение дерева Хаффмана
vector<Node> buildHuffmanTree(vector<Node> symbols) {
    sort(symbols.begin(), symbols.end(), [](const Node& a, const Node& b) {
        return a.count < b.count;
        });

    while (symbols.size() > 2) {
        Node newNode = {
            symbols[0].count + symbols[1].count,
            symbols[0].chars + symbols[1].chars
        };

        symbols.erase(symbols.begin(), symbols.begin() + 2);

        auto it = symbols.begin();
        while (it != symbols.end() && it->count < newNode.count) {
            it++;
        }
        symbols.insert(it, newNode);
    }
    return symbols;
}

// генерация кодов для узла с префиксом 0
void generateFirstTypeCodes(const string& chars) {
    for (size_t i = 0; i < chars.size(); i++) {
        cout << chars[i] << " : 0";
        for (size_t j = 0; j < i; j++) {
            cout << '1';
        }
        if (i != chars.size() - 1) {
            cout << '0';
        }
        cout << '\n';
    }
}

// генерация кодов для узла с префиксом 1
void generateSecondTypeCodes(string chars) {
    reverse(chars.begin(), chars.end());
    for (size_t i = 0; i < chars.size(); i++) {
        cout << chars[i] << " : 1";
        for (size_t j = 0; j < i; j++) {
            cout << '0';
        }
        if (i != chars.size() - 1) {
            cout << '1';
        }
        cout << '\n';
    }
}

int main() {
    string input;
    getline(cin, input);

    if (input.empty()) {
        return 0;
    }

    vector<Node> symbols = countFrequencies(input);

    vector<Node> huffmanTree = buildHuffmanTree(move(symbols));

    if (huffmanTree.size() == 1) {
        generateFirstTypeCodes(huffmanTree[0].chars);
    }
    else if (huffmanTree.size() == 2) {
        generateFirstTypeCodes(huffmanTree[0].chars);
        generateSecondTypeCodes(huffmanTree[1].chars);
    }

    return 0;
}