#include <algorithm>
#include <stdio.h>
#include <string>
#include <sstream>
#include <map>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>
#include <iomanip>


int main(int argc, char * argv[]){

    std::map<std::string, std::pair<std::string, std::string>> directions;
    std::string line;

    getline(std::cin, line);

    std::istringstream iss(line);
    std::string instructions;

    iss >> instructions;
    getline(std::cin, line);

    std::vector<std::string> current_positions;
    while(getline(std::cin, line)) {

        std::replace( line.begin(), line.end(), '=', ' ');
        std::replace( line.begin(), line.end(), ')', ' ');
        std::replace( line.begin(), line.end(), '(', ' ');
        std::replace( line.begin(), line.end(), ',', ' ');
        iss.str(line);
        iss.clear();

        std::string id, left, right;
        iss >> id >> left >> right;

        directions[id] = std::make_pair(left ,right);

        #ifdef SECOND_PART
           if (id[2] == 'A') current_positions.push_back(id);
        #else
           if (id == "AAA") current_positions.push_back(id);
        #endif

    }

    unsigned long long int steps = 0;
    std::vector<unsigned long long int> results;
    for(int i = 0; i < current_positions.size(); i++) {

        unsigned long long int local_steps = 0;
        std::string current_position = current_positions[i];
        char        current_instr    = instructions[0];

        while(current_position[2] != 'Z') {
            current_position = current_instr == 'L' ? directions[current_position].first : 
                                                      directions[current_position].second;
            local_steps++;
            current_instr = instructions[local_steps % instructions.length()];
        }
        results.push_back(local_steps);
        steps += local_steps;
    }


    std::cout << "Result: ";
    #ifdef SECOND_PART
        std::cout << std::setprecision(15) << std::fixed;
        unsigned long long int result = 1.0;
        for(auto &i : results)
            result = std::lcm(result, i);
        std::cout << result << std::endl;
    #else
        std::cout << (unsigned long long int)steps<< std::endl;
    #endif

    return 0;
}




