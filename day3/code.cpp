#include <algorithm>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

std::vector<std::string> get_nums(std::vector<std::string> &matrix, int row, int col) {

    std::string left  = "";
    std::string right = "";
    int j = col - 1;
    while(j >= 0                    && isdigit(matrix[row][j])) { left  = matrix[row][j] + left ; matrix[row][j--] = '.'; }
        j = col + 1;
    while(j <  matrix[row].length() && isdigit(matrix[row][j])) { right = right + matrix[row][j]; matrix[row][j++] = '.'; }

    std::vector<std::string> result;
    if ( isdigit(matrix[row][col]) ) {
        result.push_back(left + matrix[row][col] + right);
    } else {
        if (!left .empty()) result.push_back(left );
        if (!right.empty()) result.push_back(right);
    }
    matrix[row][col] = '.';

    return result;

}

int solve(std::vector<std::string> &matrix, int row, int col) {

    #ifdef SECOND_PART
        if (matrix[row][col] != '*') return 0;
    #endif
    std::vector<std::string> top = get_nums(matrix, row - 1, col);
    std::vector<std::string> mid = get_nums(matrix, row    , col);
    std::vector<std::string> bot = get_nums(matrix, row + 1, col);

    #ifdef SECOND_PART
        if (top.size() + mid.size() + bot.size() != 2) return 0;
        int sum = 1;
        for(auto &i : top) sum *= stoi(i);
        for(auto &i : mid) sum *= stoi(i);
        for(auto &i : bot) sum *= stoi(i);
    #else
        int sum = 0;
        for(auto &i : top) sum += stoi(i);
        for(auto &i : mid) sum += stoi(i);
        for(auto &i : bot) sum += stoi(i);
    #endif
    return sum;
}

int get_sum_from_symbols(std::vector<std::string> &matrix) {

    int sum = 0;
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].length(); ++j) {
            if (matrix[i][j] != '.' && !isdigit(matrix[i][j])) sum += solve(matrix, i, j);
        }
    }

    return sum;
}


int main(int argc, char * argv[]){

    std::vector<std::string> matrix;

    std::string line;
    while (getline(std::cin, line)) {
        matrix.push_back(line);
    }

    int sum = get_sum_from_symbols(matrix);

    std::cout << "Result: " << sum << std::endl;
    return 0;
}




