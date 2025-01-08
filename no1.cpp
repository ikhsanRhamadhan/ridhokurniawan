/*
    Program String Compression using Huffman Encoding
    Nama: Ridho Kurniawan
    NIM: 231011401209
*/

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Comparator for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Traverse Huffman Tree to generate codes
void buildCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }
    buildCodes(root->left, code + "0", huffmanCode);
    buildCodes(root->right, code + "1", huffmanCode);
}

// Build Huffman Tree
Node* buildHuffmanTree(const string& text) {
    unordered_map<char, int> freq;
    for (char ch : text) freq[ch]++;
    
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }
    
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }
    
    return pq.top();
}

// Encode string
string encode(const string& text, unordered_map<char, string>& huffmanCode) {
    string encoded = "";
    for (char ch : text) {
        encoded += huffmanCode[ch];
    }
    return encoded;
}

// Decode string
string decode(const string& encodedStr, Node* root) {
    string decoded = "";
    Node* curr = root;
    for (char bit : encodedStr) {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right) {
            decoded += curr->ch;
            curr = root;
        }
    }
    return decoded;
}

// Main function
int main() {
    string text;
    cout << "Enter text: ";
    cin >> text;

    Node* root = buildHuffmanTree(text);
    unordered_map<char, string> huffmanCode;
    buildCodes(root, "", huffmanCode);

    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << "\n";
    }

    string encodedStr = encode(text, huffmanCode);
    cout << "Encoded string: " << encodedStr << "\n";

    string decodedStr = decode(encodedStr, root);
    cout << "Decoded string: " << decodedStr << "\n";

    return 0;
}
