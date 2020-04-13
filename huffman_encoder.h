#pragma once

#include "frequency_table.h"
#include <vector> 

using namespace std; 

// struct for the nodes of the tree?
struct MinHeapNode { 
  
      char data; 
      int freq; 
  
    
     MinHeapNode *left, *right = NULL;  
     MinHeapNode* p = NULL; 

}; 
  
struct Comparable { 
    bool operator()(MinHeapNode* left, MinHeapNode* right) { 
        return left->freq > right->freq; 
    }
};

class huffman_encoder {
   
    MinHeapNode* root; 
    map<char, MinHeapNode*> count; 

    map<char, string> codes; 

    public:
        huffman_encoder(const frequency_table &table);
        ~huffman_encoder();

        std::string get_character_code(char c) const;
        std::string encode(const std::string &file_name) const;
        std::string decode(const std::string &file_name) const;
     
};