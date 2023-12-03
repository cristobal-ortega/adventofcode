#include <stdio.h>
#include <string>
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, int> wordToNumber = {
    {"one"  , 1},
    {"two"  , 2},
    {"three", 3},
    {"four" , 4},
    {"five" , 5},
    {"six"  , 6},
    {"seven", 7},
    {"eight", 8},
    {"nine" , 9},
    {"zero" , 0},
};


// From str[pos] check ALL possible words to str[pos+5] (5 chars maximum in numbers)
// Performance can be improved by checking chars w.r.t. chars in numbers
// Not sure if it pays off (even more with the reduced input)
// Due to this search, the algorithm takes O(n^2)
std::optional<int> get_number_from_word(std::string str, int pos) {

    int i = pos;

    std::string word = "";
    while( i < str.length() && i < (pos+5) ) {
        word += str[i++];
        if (wordToNumber.count(word)) return wordToNumber[word];
    }

    return {};

}

int get_number(std::string str, int pos, int increment) {

    while( pos >= 0 && pos < str.length() ) {
        if ( isdigit(str[pos])              ) return str[pos] - '0';
        #ifdef SECOND_PART
            if ( get_number_from_word(str, pos) ) return get_number_from_word(str, pos).value();
        #endif
        pos += increment;
    }

    return -1;
}

int main(int argc, char * argv[]){

    int sum = 0;
    std::string line;
    while (getline(std::cin, line)) {
        int first_num  = get_number(line, 0, 1);
        int second_num = get_number(line, line.length()-1, -1);
        sum += (first_num*10) + second_num;
    }

    std::cout << "Result: " << sum << std::endl;
    return 0;
}




