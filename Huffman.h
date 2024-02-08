#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include "map"
#include <iomanip>

using namespace std;

struct node{
    char id;
    long long int freq;
    string code;
    node *left, *right;
    node(){
        left = nullptr;
        right = nullptr;
    }
};



class huffman{
private:
    node * ASCII[128]; // For 128 character of ASCII
    node * root;
    char id;
    fstream in_file, out_file;
    string in_file_name, out_file_name;
    class compare{
    public:
        bool operator()(const node * a, const node * b) const
        {
            return a->freq > b->freq;
        }
    };
    priority_queue<node *, vector<node *>, compare> pq;
    map<string, char> decode;

public:
    huffman(string, string);        // Constructor
    void create_array();        // ASCII array
    void traverse(node *, const string&);
    int BTD(string&);       // Convert an 8-bit binary code to a decimal integer
    string DTB(int);		// Convert a decimal integer to an 8-bit 0/1 string of binary code
    void createPriorityqueue();      // Create PQ
    void createTree();          // Create huffman tree
    void calculateCodes();      // Calculate every char binary code
    void coding();         // Save Coding into file

    void decoding();         // Save decoding into file
    void calculatecodeDecode();         // Recreate huffman tree with help of info in file
    void traverseDecode(node *, const string&);

};

#endif
