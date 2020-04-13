#pragma once

#include <iostream>
#include <map>


class frequency_table {
    // Something to store the frequency of each character
     std::map<char, int> m; 

    public:
        frequency_table(const std::string &file_name);
        ~frequency_table();
        
        int get_frequency(char c) const;
};