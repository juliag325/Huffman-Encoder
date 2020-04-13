#include "huffman_encoder.h"
#include "frequency_table.h"
#include <queue>
#include <vector>
#include <map> 
#include <fstream>
#include <sstream>


using namespace std; 

huffman_encoder::huffman_encoder(const frequency_table &table){
    //we have a frequency table, with the chars and frequencies 
    //See https://www.techiedelight.com/huffman-coding/ for reference 
    
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, Comparable> pq; 

    for (int i = 0; i < 128; i++) { 
        if (table.get_frequency(i) > 0) {

            int frequency = table.get_frequency(i); 
            MinHeapNode* newNode = new MinHeapNode(); 
            newNode->data = i; 
            newNode->freq = frequency; 


            //Initialize left and right to null (prevents segmentation fault)
            newNode->left = NULL;
            newNode->right = NULL; 

            count.insert(std::pair<char, MinHeapNode*>(i,newNode)); 
            pq.push(newNode);

        }
    }

    // For single letter
    if (pq.size() == 1) { 
        root = pq.top(); 
    }

    //If there is nothing in the priority queue, root is null
    else if (pq.size() == 0) { 
        root = NULL; 
    }

    else {
        while (pq.size() > 1) { 
            
            MinHeapNode* predecessor = new MinHeapNode(); 
            predecessor->data = '\0'; 
            predecessor->freq = 0; 

            predecessor->left = NULL; 
            predecessor->right = NULL; 

            MinHeapNode* first = pq.top(); 
            first->p = predecessor; 
            predecessor->left = first;
            pq.pop();

           MinHeapNode* second = pq.top(); 
            second->p = predecessor; 
            predecessor->right = second;
            pq.pop();

            //The parent, or internal node is the sum of both nodes we popped off the queue. 
            predecessor->freq = first->freq+second->freq; 
            pq.push(predecessor); //our new node pushed to the queue!
        }

        //Set the root of the tree to the top of the queue. Tree complete. 
        root = pq.top(); 
    }

    

}

huffman_encoder::~huffman_encoder(){
  delete root;  
}


std::string huffman_encoder::get_character_code(char character) const {
    map<char, string> map; 

  return ""; 

}

std::string huffman_encoder::encode(const std::string &file_name) const {
   
    
   return "";
 

}

    
std::string huffman_encoder::decode(const std::string &string_to_decode) const {
    
    return "";
 
    
}

