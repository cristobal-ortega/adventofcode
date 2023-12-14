#include <algorithm>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


// This function should be improved style-wised...
void push_rocks(std::vector<std::string>& matrix, int direction) {

    int di  = 1;
    int dj  = 1;
    int dii = 0;
    int djj = 0;
    int reverse = 0;
    switch(direction) {
    	case 0:
    		dii = 1;
            djj = 0;
    		break;
    	case 2:
            di = -1;
            dj = -1;
    		dii = -1;
            reverse = 1;
    		break;
    	case 1:
            dii = 0;
    		djj = 1;
    		break;
    	case 3:
            di = -1;
            dj = -1;
            djj = -1;
            dii = 0;
            reverse = 1;
    		break;
    }

    int iStart = reverse ? matrix.size()-1:0;
    int iEnd   = reverse ? -1:matrix.size();
    for(int i = iStart; i != iEnd; i += di) {

        int jStart = reverse ? matrix[i].length()-1:0;
        int jEnd   = reverse ? -1:matrix[i].length();
        for(int j = jStart; j != jEnd; j += dj) {
            if (matrix[i][j] == 'O') {
				
				int ii  = i - dii;
				int jj  = j - djj;
				while (ii >= 0 && ii < matrix.size() &&
                       jj >= 0 && jj < matrix[ii].size() ) {
                    if (matrix[ii][jj] == '.') std::swap(matrix[ii][jj], matrix[ii+dii][jj+djj]);
					else break;
					ii -= dii;
                    jj -= djj;
				}
            }

        }
    }


}

unsigned long long int total_load_north(std::vector<std::string> &matrix) {

    unsigned long long int res = 0;

    for(int i = 0; i < matrix.size(); ++i) {
        for(int j = 0; j < matrix[i].length(); ++j) {
            if (matrix[i][j] == 'O') res += matrix.size() - i;
            
        }
    }

    return res;
}

int length_string = 0;
std::string get_hash(std::vector<std::string> matrix) {

    std::string res;

    for(auto &s : matrix) {
        length_string = s.length();
        res += s;
    }

    return res;
}

std::vector<std::string> dehash(std::string hashed) {

    std::vector<std::string> res;

    for (int i = 0; i < hashed.size(); i += length_string)
        res.push_back(hashed.substr(i, length_string));

    return res;
}

#ifdef SECOND_PART
    #define ITER_TARGET 1000000000
#else
    #define ITER_TARGET 1
#endif


int main(int argc, char * argv[]){


    std::vector<std::string> matrix;

    std::string line;

    while(getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string token;
        
        iss >> token;

        matrix.push_back(token);

    }

    std::map<std::string, int> cache;

    for(int i = 0; i < ITER_TARGET; i++) {
        push_rocks(matrix, 0);
        #ifdef SECOND_PART
        push_rocks(matrix, 1);
        push_rocks(matrix, 2);
        push_rocks(matrix, 3);
        #endif

        std::string hashed = get_hash(matrix);
        if (cache.count(hashed)) {
            int iterations_to_cycle = cache[hashed];
            int length_cycle        = i - cache[hashed];
            int pos = (ITER_TARGET - iterations_to_cycle) % length_cycle - 1 + cache[hashed];
            for(auto &[k,v] : cache)
                if (v == pos) matrix = dehash(k);
            break;
        }
        cache[hashed] = i;
    }

    unsigned long long int sum = total_load_north(matrix);

    std::cout << "Result: " << sum << std::endl;

    return 0;
}



