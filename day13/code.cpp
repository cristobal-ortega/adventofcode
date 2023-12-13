#include <algorithm>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>


int check_lines(std::vector<std::string> matrix, int top, int bot, int &differences) {

    while(top <= bot) {
        for (int i = 0; i < matrix[top].length(); ++i) {
            if (matrix[top][i] != matrix[bot][i] ) ++differences;
        }
        ++top; --bot;
    }
    
    return top;
}

std::vector<std::string> transpose(std::vector<std::string> matrix) {

    std::vector<std::string> new_m(matrix[0].length());

    int k = 0;
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].length(); j++) {
            new_m[j].push_back(matrix[i][j]);
        }
    }

    return new_m;
}

int check_palindrome(std::vector<std::string> matrix, int smudges) {

    int res = 0;

    int tmp = 0;
    // this could be faster since we know the (i == 0 || j == matrix.size() - 1)...
    for(int i = 0; i < matrix.size(); i++) {
        int j = matrix.size() - 1;
        while(j > i) {
            int differences = 0;
            int reflection_at = check_lines(matrix, i, j, differences);
            if (differences == smudges &&
                ((j - i)%2)            &&
                (i==0||j==matrix.size()-1)) {
                tmp = reflection_at;
                break;
            }
            --j;
        }
    }
    res += tmp;

    return res;
}

#ifdef SECOND_PART
#define SMUDGES 1
#else
#define SMUDGES 0
#endif

int main(int argc, char * argv[]){


    std::vector<std::vector<std::string>> input;

    std::string line;

    std::vector<std::string> pattern;
    while(getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string token;
        
        iss >> token;

        if (!line.empty()) {
            pattern.push_back(token);
        } else {
            input.push_back(pattern);
            pattern = std::vector<std::string>();
        }

    }
    input.push_back(pattern);

    int sum = 0;
    for(int i = 0; i < input.size(); i++) {

        int horizontal = 100*check_palindrome(          input[i] , SMUDGES);
        int vertical   =     check_palindrome(transpose(input[i]), SMUDGES);

        if (horizontal) sum += horizontal;
        else sum += vertical;

    }

    std::cout << "Result: " << std::endl;
    std::cout << sum << std::endl;

    return 0;
}



