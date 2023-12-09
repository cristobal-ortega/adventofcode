#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>


std::pair<int,int> predict(std::vector<int> history) {

    std::vector<int> differences;

    bool all_zeroes = true;
    for(int i = 1; i < history.size(); i++) {
        int diff = history[i] - history[i-1];
        if (diff) all_zeroes = false;
        differences.push_back(diff);
    }

    if (all_zeroes) return std::make_pair(history[0], history[history.size()-1]);

	std::pair<int,int> extrapolated_values = predict(differences);

	extrapolated_values.first  = history[0]                - extrapolated_values.first;
	extrapolated_values.second = history[history.size()-1] + extrapolated_values.second;
    return extrapolated_values; 


}

int main(int argc, char * argv[]){


    std::vector<std::vector<int>> report_history;

    std::string line;
    while(getline(std::cin, line)) {

        std::vector<int> single_history;
        std::istringstream iss(line);
        std::string token;
        while( iss >> token ) {
            single_history.push_back(stoi(token));
        }

        report_history.push_back(single_history);
    }

    std::pair<int, int> sum = std::make_pair(0,0);
    for(int i = 0; i < report_history.size(); ++i) {
        std::pair<int,int> extrapolated_values = predict(report_history[i]);
		sum.first  += extrapolated_values.first ;
		sum.second += extrapolated_values.second;
    }

    std::cout << "Result: " << std::endl;
    std::cout << "left  extrapolation: " << sum.first  << std::endl;
    std::cout << "right extrapolation: " << sum.second << std::endl;

    return 0;
}



