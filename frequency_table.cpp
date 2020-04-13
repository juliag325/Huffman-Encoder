#include <iostream>
#include "frequency_table.h"
#include <fstream>
#include <sstream>


frequency_table::frequency_table(const std::string &file_name) {
    //Takes in a text file of characters.

    char ch; 
    //read in file name
    std::fstream input(file_name, std::fstream::in); 

    if (input.fail()) {
        throw std::runtime_error ("File does not exist"); 
    }

    input >> std::noskipws; 

    //create hashmap 
    frequency_table m(); 

    //While the file is not done (don't skip whitespace)

    while (input >> ch) { 
        
        //if it exists 
        if (frequency_table::m.count(ch) > 0) { 
            frequency_table::m.at(ch)++; 
        } 

        else { 
            //doesn't exist
            frequency_table::m.insert(std::pair<char, int>(ch,1)); 
            
        } 
    } 

   
    

}

frequency_table::~frequency_table() {
    m.clear(); 
}

int frequency_table::get_frequency(char c) const {
    //Given a character c
    // Check if it exists - if it does, return the frequency int. 
    //else return runtime (does not exist?)
    int result; 

    // If c doesn't exist 
    if (m.find(c) == m.end()) { 
        result = 0; 
        return result; 
    }
    //c does exist!!
    else { 
        result = m.at(c); 
        return result; 
    }
}


/* Logic: 
Iterate through the text file, character by character (include spaces)
If character does not exist in the hashmap, put as key and add value count. 
else 
add value count to the character that already exists

if file is not found, return runtime error if file is not found 
*/ 