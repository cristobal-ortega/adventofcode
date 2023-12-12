#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <set>
#include <vector>


std::set<int> get_pos_with_no_galaxies_in_dim(std::vector<std::vector<char>> &matrix, int dim) {

    std::set<int> result;

    for(int i  = 0; i < matrix.size(); i++) {
        bool no_galaxy_in_dim = true;
        auto it = matrix[i];
        for(int j = 0; j < matrix[i].size(); ++j) {
            if (dim == 0) {
                if (matrix[i][j] != '.') {
                    no_galaxy_in_dim = false;
                    break;
                }
            
            } else {
                if (matrix[j][i] != '.') {
                    no_galaxy_in_dim = false;
					break;
                }
            }
        }
        if (no_galaxy_in_dim) {
            result.insert(i);
        }

    }

    return result;
}

std::pair<int,int> get_directions(std::pair<int, int> src, std::pair<int, int> dst) {

    std::pair<int, int> directions;
    directions.first = 0;
    if ( (dst.second - src.second ) == 0)
        directions.first = 1;

    if ( (dst.second - src.second) > 0)
        directions.second = 1;
    else if ( (dst.second - src.second) < 0 )
        directions.second = -1;

    return directions;

}

#ifdef SECOND_PART
	int incr = 1000000-1;
#else
	int incr = 1;
#endif

unsigned long long int dfs(std::vector<std::vector<char>> &matrix,
        std::pair<int, int> src,
        std::pair<int, int> dst,
        std::set <int>      rows_duplicated, 
        std::set <int>      cols_duplicated) {

    if (src == dst) return 0;

    std::pair<int,int> directions = get_directions(src, dst);

    std::pair<int, int> new_src = src;
    new_src.first  += directions.first;
    new_src.second += directions.second;

    unsigned long long int steps = 1;
    if (rows_duplicated.count(new_src.first )) steps += incr;
    if (cols_duplicated.count(new_src.second)) steps += incr;

    return steps+dfs(matrix, new_src, dst, rows_duplicated, cols_duplicated);

}


int main(int argc, char * argv[]){


    std::vector<std::vector<char>> matrix;
    std::vector<std::vector<int>> visited;

    std::string line;
    std::set<std::pair<int,int>> galaxies_location;

    int n_rows = 0;
    int n_galaxies = 1;
    while(getline(std::cin, line)) {
        std::vector<char> row(line.begin(), line.end());
        for(int j = 0; j < row.size(); ++j) {
            if (row[j] == '#') {
                galaxies_location.insert( std::make_pair(n_rows, j) );
                row[j] = '0' + (n_galaxies++);
            }
        }
        n_rows++;
        matrix.push_back( row );
    }

    std::set<int> rows_duplicated = get_pos_with_no_galaxies_in_dim(matrix, 0);
    std::set<int> cols_duplicated = get_pos_with_no_galaxies_in_dim(matrix, 1);

    unsigned long long int sum = 0;
    for(auto i = galaxies_location.begin(); i != galaxies_location.end(); ++i) {
        if (i == std::next(i)) break;
        for(auto j = std::next(i); j != galaxies_location.end(); ++j)
            sum = sum + dfs(matrix, *i, *j, rows_duplicated, cols_duplicated);
    }

    std::cout << "Result: " << std::endl;
    std::cout << sum << std::endl;

    return 0;
}



