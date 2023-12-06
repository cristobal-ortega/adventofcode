#include <cmath>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>


int compute_ways(std::vector<long long int> &times, std::vector<long long int> &distances, int pos) {

    long long int limit_time   = times[pos];
    long long int min_distance = distances[pos] + 1;

    // to ease writing the equations
    long long int a = -1;
    long long int b = limit_time;
    long long int c = min_distance;
        
    double root_positive = (-b + std::sqrt(b*b-4*a*(-c)))/(-2);
    double root_negative = (-b - std::sqrt(b*b-4*a*(-c)))/(-2);

    long long int min_sol = std::ceil (std::min(root_positive, root_negative));
    long long int max_sol = std::floor(std::max(root_positive, root_negative));

    return max_sol - min_sol + 1;

    // for(int i = limit_time - 1; i >= 1; i--) {
    //     int total_distance = (limit_time - i) * i;
    //     if (total_distance > min_distance) {
    //         ++ways;
    //         std::cout << "new way with: ";
    //         std::cout << " limit_time: " << limit_time;
    //         std::cout << " i: " << i;
    //         std::cout << std::endl;
    //     }
    // }

}

int main(int argc, char * argv[]){

    std::string line;
    std::vector<long long int> times, distances;
    getline(std::cin, line);

    std::istringstream iss;
    iss.str(line);
    std::string token;

    iss >> token; // Time:

    std::string total = "";
    while (iss >> token) {
        #ifndef SECOND_PART
            times.push_back(stoul(token));
        #endif
        total += token;
    }
    #ifdef SECOND_PART
        times.push_back(stoul(total));
    #endif

    getline(std::cin, line);
    iss.clear();
    iss.str(line);
    iss >> token; // Distance:
    total = "";
    while (iss >> token) {
        #ifndef SECOND_PART
            distances.push_back(stoul(token));
        #endif
        total += token;
    }
    #ifdef SECOND_PART
        distances.push_back(stoul(total));
    #endif

    int sum = 1;
    for(int i = 0; i < times.size(); i++) {
        sum *= compute_ways(times, distances, i);
    }

    std::cout << "Result: " << sum << std::endl;
    return 0;
}




