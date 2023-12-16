#include <algorithm>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

std::pair<int,int> UP    = {-1, 0};
std::pair<int,int> RIGHT = { 0, 1};
std::pair<int,int> DOWN  = { 1, 0};
std::pair<int,int> LEFT  = { 0,-1};

// / change first to second and change sign
//   UP    --> RIGHT
//   RIGHT --> UP
//   DOWN  --> LEFT
//   LEFT  --> DOWN
// 
// \ change first to second and keep sign
//   UP    --> LEFT
//   RIGHT --> DOWN
//   DOWN  --> RIGHT
//   LEFT  --> UP

void dfs(std::vector<std::string> &matrix,
         std::vector<std::string> &visited,
         std::vector<std::vector<std::pair<int,int>>> &routes,
         int row, int col, std::pair<int,int> d) {

    if (row < 0 || row >= matrix.size()       ) return;
    if (col < 0 || col >= matrix[row].length()) return;

    // Already visited
    if (visited[row][col] == '#' && routes[row][col] == d) return;
    visited[row][col] = '#';
    routes [row][col] = d;

    // empty
    if (matrix[row][col] == '/' || matrix[row][col] == '\\' ){
        std::swap(d.first, d.second);
        if (matrix[row][col] == '/' ) { d.first *= -1; d.second *=-1;}
    } else if (matrix[row][col] == '|' || matrix[row][col] == '-' ){
        if (matrix[row][col] == '|' && (d == RIGHT || d == LEFT)) {
            dfs(matrix, visited, routes, row + UP  .first, col + UP  .second, UP  );
            d = DOWN;
        } else if (matrix[row][col] == '-' && (d == UP    || d == DOWN)) {
            dfs(matrix, visited, routes, row + RIGHT.first, col + RIGHT.second, RIGHT);
            d = LEFT;
        }
    }

    dfs(matrix, visited, routes, row + d.first, col + d.second, d);
}


int count_energized_tiles(std::vector<std::string> &visited) {
    int sum = 0;
    for(int i = 0; i < visited.size(); ++i) {
        for(int j = 0; j < visited[i].length(); ++j) {
            if (visited[i][j] == '#') ++sum;
        }
    }
    return sum;
}

int main(int argc, char * argv[]){


    std::vector<std::string> matrix;
    std::vector<std::string> visited;
    std::string line;

    while(getline(std::cin, line)) {
        matrix.push_back(line);
        visited.push_back(line);
    };

    std::vector<std::vector<std::pair<int,int>>> routes(matrix.size(), std::vector<std::pair<int,int>>(matrix[0].size()));

    int sum = 0;

    #ifdef SECOND_PART
        std::vector<std::string> visited_back = visited; // bruteforce :)
        for(int i = 0; i < matrix[0].length(); i++) {
            visited = visited_back;
            // start TOP going down
            dfs(matrix, visited, routes, 0, i, DOWN);
            sum = std::max(sum, count_energized_tiles(visited));

            visited = visited_back;
            // start BOTTOM going up
            dfs(matrix, visited, routes, matrix.size()-1, i, UP);
            sum = std::max(sum, count_energized_tiles(visited));
        }
        for(int i = 0; i < matrix.size(); i++) {
            visited = visited_back;
            // start LEFT going right
            dfs(matrix, visited, routes, i, 0, RIGHT);
            sum = std::max(sum, count_energized_tiles(visited));

            visited = visited_back;
            // start BOTTOM going up
            dfs(matrix, visited, routes, i, matrix[0].length()-1, LEFT);
            sum = std::max(sum, count_energized_tiles(visited));
        }
    #else
        dfs(matrix, visited, routes, 0, 0, RIGHT);
        sum = count_energized_tiles(visited);
    #endif


    std::cout << "Result: " << sum << std::endl;

    return 0;
}



