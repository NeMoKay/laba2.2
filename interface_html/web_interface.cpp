#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "/Users/kay/Proga/laba2.2/include/sequence.hpp"

using namespace std;

vector<int> parse_elements(const string& elements_str) {
    vector<int> elements;
    if (elements_str.empty()) return elements;
    
    stringstream ss(elements_str);
    string token;
    while (getline(ss, token, ',')) {
        try {
            elements.push_back(stoi(token));
        } catch (...) {

        }
    }
    return elements;
}


vector<bool> parse_bits(const string& bits_str) {
    vector<bool> bits;
    if (bits_str.empty()) return bits;
    
    stringstream ss(bits_str);
    string token;
    while (getline(ss, token, ',')) {
        try {
            bits.push_back(stoi(token) != 0);
        } catch (...) {

        }
    }
    return bits;
}


string sequence_to_string(Sequence<int>* seq) {
    if (!seq || seq->GetLength() == 0) return "Empty sequence";
    
    stringstream ss;
    ss << "[";
    for (int i = 0; i < seq->GetLength(); ++i) {
        if (i > 0) ss << ", ";
        ss << seq->Get(i);
    }
    ss << "]";
    return ss.str();
}

string bit_sequence_to_string(BitSequence<int>* seq) {
    if (!seq || seq->GetLength() == 0) return "Empty bit sequence";
    
    stringstream ss;
    ss << "[";
    for (int i = 0; i < seq->GetLength(); ++i) {
        if (i > 0) ss << ", ";
        ss << (seq->Get(i).operator bool() ? "1" : "0");
    }
    ss << "]";
    return ss.str();
}

void print_html(const string& result) {
    cout << "Content-Type: text/html\r\n\r\n";
    cout << "<html><body>";
    cout << "<h2>Operation Result:</h2>";
    cout << "<pre>" << result << "</pre>";
    cout << "<a href='/'>Back to main</a>";
    cout << "</body></html>";
}

int main() {
    cout << "Content-Type: text/html\r\n\r\n";
    
    cout << "<html><head><title>Sequence Interface</title></head><body>";
    cout << "<h1>Sequence Interface</h1>";
    cout << "<p>This is a placeholder for the actual interface.</p>";
    cout << "<p>The actual implementation would process your requests and show results here.</p>";
    cout << "<p>To use the interface, please access: <a href='/visual_http.html'>/visual_http.html</a></p>";
    cout << "</body></html>";
    
    return 0;
}