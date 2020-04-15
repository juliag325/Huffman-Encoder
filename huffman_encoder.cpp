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
      string charCode; 

      if (count.count(character) > 0) {
            MinHeapNode* curr = count.at(character); //curr node is the node, or key from the map.

        //Add a 1 or 0 based on if it's the left or right child of parent. 
            //If left child - add 0
            //If right child - add 1 
            while(curr->p) { 
                if(curr->p->left == curr) {
                    charCode = "0" + charCode; 
                }
                else if (curr->p->right == curr) {
                    charCode = "1" + charCode;
                }
                curr = curr->p;
            }
        }

    //Else return an empty string
        else {
            charCode = "\0"; 
            
        }
   
    return charCode;

   

}

std::string huffman_encoder::encode(const std::string &file_name) const {
    string encodedStr; 
    char ch; 

    //takes in file name 
   std::fstream input(file_name, std::fstream::in); 

    if (input.fail()) {
        throw std::runtime_error ("File does not exist"); 
    }

    input >> std::noskipws;

    if (count.size() == 1) { //if only one letter 
        return "0";
    }
    

        //Iterates through all characters in file
        while (input >> ch) { 
            //if character exists
            if (get_character_code(ch) != "") {
                encodedStr += get_character_code(ch); 

            }
           else { 
               encodedStr += get_character_code(ch); 
           }

          
        }
    
   return encodedStr;
 

}

    
std::string huffman_encoder::decode(const std::string &string_to_decode) const {
    //takes string from encode? and decodes that string 
    MinHeapNode* curr = root;
    string decodedStr;


    if (root == NULL) { //nothing in file 
        throw std::runtime_error("Nothing in file"); 
    }

    if (string_to_decode.length() == 1) { //if only one letter 
        return decodedStr = curr->data; 
    }

  else {
    //Traverse the tree! 
    for (int i = 0; i < string_to_decode.length(); i++) { 

        if (curr && curr->right && string_to_decode[i] == '1') { 
            curr = curr->right;
        }

        else if (curr && curr->left && string_to_decode[i] == '0'){ 
            curr = curr->left;
        }

        else { //if character isn't 0 or 1 
            return ""; 
        }


        //If a leaf node
        if (curr && !curr->left && !curr->right) { 
            decodedStr += curr->data; //add to the string 
            curr = root; //reset the curr to the root 
       
        } 
    }
    return decodedStr;
 }
    
}


