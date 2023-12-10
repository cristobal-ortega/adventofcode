#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>


// N, E, S, W
std::vector<int> get_directions(char current,
                                 int     row,
                                 int     col,
                                 int   p_row,
                                 int   p_col) {

    std::vector<int> directions;
    int north_en = 0;
    int south_en = 0;
    int  east_en = 0;
    int  west_en = 0;
    if ( (  row - p_row ) == 1 ) north_en = 1;
    if ( (p_row -   row ) == 1 ) south_en = 1;
    if ( (  col - p_col ) == 1 )  east_en = 1;
    if ( (p_col -   col ) == 1 )  west_en = 1;

    switch (current) {
        case '|':
            if (north_en) directions = {0, 0, 1, 0};
            if (south_en) directions = {1, 0, 0, 0};
            break;
        case '-':
            if (east_en) directions = {0, 1, 0, 0};
            if (west_en) directions = {0, 0, 0, 1};
            break;
        case 'L':
            if (north_en) directions = {0, 1, 0, 0};
            if (west_en ) directions = {1, 0, 0, 0};
            break;
        case 'J':
            if (north_en) directions = {0, 0, 0, 1};
            if (east_en ) directions = {1, 0, 0, 0};
            break;
        case '7':
            if (south_en) directions = {0, 0, 0, 1};
            if (east_en ) directions = {0, 0, 1, 0};
            break;
        case 'F':
            if (south_en) directions = {0, 1, 0, 0};
            if (west_en ) directions = {0, 0, 1, 0};
            break;
    }

    return directions;


}


int solve(std::vector<std::vector<char>> &matrix,
          std::vector<std::vector<int>> &visited,
                                  int     steps,
                                  int       row,
                                  int       col,
                                  int     p_row,
                                  int     p_col) {

    if (visited[row][col] == 1) return steps/2;

    visited[row][col] = 1;

    std::vector<int> directions = get_directions(matrix[row][col], row, col, p_row, p_col);

    int n_row = row;
    int n_col = col;
    if (directions[0]) --n_row;
    if (directions[1]) ++n_col;
    if (directions[2]) ++n_row;
    if (directions[3]) --n_col;


    return solve(matrix, visited, steps+1, n_row, n_col, row, col);

}


int solve_start(std::vector<std::vector<char>> &matrix,
                std::vector<std::vector<int>>  &visited,
                                        int         m,
                                        int         n,
                                        int       row,
                                        int       col) {

    visited[row][col] = 1;
    if ( (row+1 <  m) && ( (matrix[row+1][col] == '|') ||
                           (matrix[row+1][col] == 'L') ||
                           (matrix[row+1][col] == 'J') )) {
        return solve(matrix, visited, 1, row+1, col, row, col);
    }
    if ( (row-1 >= 0) && ( (matrix[row-1][col] == '|') ||
                           (matrix[row-1][col] == '7') ||
                           (matrix[row-1][col] == 'F') )) {
        return solve(matrix, visited, 1, row-1, col, row, col);
    }
    if ( (col+1 <  n) && ( (matrix[row  ][col+1] == '-') ||
                           (matrix[row  ][col+1] == 'J') ||
                           (matrix[row  ][col+1] == '7') )) {
        return solve(matrix, visited, 1, row  , col+1, row, col);
    }
    if ( (col-1 <  n) && ( (matrix[row  ][col-1] == '-') ||
                           (matrix[row  ][col-1] == 'L') ||
                           (matrix[row  ][col-1] == 'F') )) {
        return solve(matrix, visited, 1, row  , col+1, row, col);
    }

    return 0;
}


// From https://en.wikipedia.org/wiki/Point_in_polygon
// Example:
// ...........
// .S-------7.
// .|F-----7|.
// .||.....||.
// .||.....||.
// .|L-7.F-J|. <--
// .|..|.|..|.
// .L--J.L--J.
// ...........

// The line .|L-7.F-J|. needs a bit of processing to apply the point in polygon algorithm.
// The algorithm won't work since it "sees" multiple times the same border or wall:
// .F-J|. --> F, J, | = 3 walls! But it's 2 actually
//                          .F-J|.
// We could consider it as: .|..|.

// Therefore, we can keep track of the parity of the walls from left to right.
// When seeing:
// - F -->
//		   F--7 two walls are seen --> keep parity
//		   F--J one wall   is seen --> change parity
// - L -->
//		   L--7 one wall   is seen --> change parity
//		   L--J two walls are seen --> keep parity

// Always assume the input makes sense!

int get_tiles_outside(std::vector<std::vector<char>> &matrix ,
					  std::vector<std::vector< int>> &visited,
                                               int          m,
                                               int          n) {
	int num_tiles = 0;
	for(int i = 0; i < m; i++) {
		int inside = 0;
		int dir_connection = 0;
		for(int j = 0; j < n; j++) {

			char current = visited[i][j] ? matrix[i][j] : '.';

			if ( current == '.' && inside) {
				++num_tiles;
				matrix[i][j] = 'I';
			} else if (current == '.') {
				matrix[i][j] = 'O';
			} else if (current != '-'){
				if      (current == '|'                       ) inside = !inside;
				else if (current == 'S'                       ) inside = !inside;
				else if (current == 'F'                       ) dir_connection = 1;
				else if (current == 'L'                       ) dir_connection = 0;
				else if (current == '7' && dir_connection == 0) inside = !inside;
				else if (current == 'J' && dir_connection == 1) inside = !inside;
			}

		}

	}

	return num_tiles;

}

int main(int argc, char * argv[]){


    std::vector<std::vector<char>> matrix;
    std::vector<std::vector<int>> visited;

    std::string line;
    int n_rows = 0;
    int s_row = 0;
    int s_col = 0;
    int n_cols = 0;
    while(getline(std::cin, line)) {
        n_cols = 0;
        std::vector<char> row;
        std::vector<int > visited_r;
        for(auto &c : line) {
            if (c == 'S') {
                s_row = n_rows;
                s_col = n_cols;
            }
            row.push_back(c);
            visited_r.push_back(0);
            ++n_cols;
        }
        matrix.push_back(row);
        visited.push_back(visited_r);
        ++n_rows;
    }

    int steps = solve_start(matrix, visited, n_rows, n_cols, s_row, s_col);

    std::cout << "Result p1: " << std::endl;
    std::cout << steps << std::endl;

	int tiles_outside = get_tiles_outside(matrix, visited, n_rows, n_cols);
    // for(auto &i : matrix) {
    //     for(auto &j : i) {
    //         std::cout << j;
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << "Result p2: " << std::endl;
    std::cout << tiles_outside << std::endl;


    return 0;
}



