#include <algorithm>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<std::vector<unsigned long long int>>> Cache;

Cache cache; 

using VL   = std::vector<unsigned long long int>;
using VVL  = std::vector<VL>;
using VVVL = std::vector<VVL>;

unsigned long long int solve(std::vector<char> conditions,
										 int   i,
							  std::vector<int> groups,
										  int  j,
										int    cur_g) {

	if (i >= conditions.size()) return j == groups.size();

	if (cache[i][j][cur_g] != -1) return cache[i][j][cur_g];

	unsigned long long int res = 0;
	if ((conditions[i] == '.' || conditions[i] == '?') && cur_g == 0) {
		res += solve(conditions, i+1, groups, j, 0);
	}

	if ((conditions[i] == '#' || conditions[i] == '?') && j < groups.size()) {
		if ((cur_g + 1) == groups[j]) {
			if (((i+1) == conditions.size() || conditions[i+1] != '#')) {
				res +=  solve(conditions, i+2, groups, j+1, 0);
			}
		} else {
			res += solve(conditions, i+1, groups, j, cur_g+1);
		}
	}

	cache[i][j][cur_g] = res;
	return res;

}

int main(int argc, char * argv[]){


    std::vector<std::vector<char>> spring_conditions;
    std::vector<std::vector<int>> groups;

    std::string line;

    while(getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string conditions, contiguous_groups;
        iss >> conditions >> contiguous_groups;
        spring_conditions.push_back(std::vector<char>(conditions.begin(), conditions.end()));

        std::vector<int> number_groups;
        std::stringstream  ss(contiguous_groups);
        std::string str;
        while (getline(ss, str, ',')) {
            number_groups.push_back(stoi(str));
        }


        groups.push_back(number_groups);

    }

    unsigned long long int sum = 0;
    for(int i = 0; i < spring_conditions.size(); i++) {

        #ifdef SECOND_PART
		    std::vector<char> single_cond = spring_conditions[i];
		    std::vector<int> single_groups = groups[i];

		    spring_conditions[i].push_back('?');
		    spring_conditions[i].insert(spring_conditions[i].end(), single_cond.begin(), single_cond.end());
		    spring_conditions[i].push_back('?');
		    spring_conditions[i].insert(spring_conditions[i].end(), single_cond.begin(), single_cond.end());
		    spring_conditions[i].push_back('?');
		    spring_conditions[i].insert(spring_conditions[i].end(), single_cond.begin(), single_cond.end());
		    spring_conditions[i].push_back('?');
		    spring_conditions[i].insert(spring_conditions[i].end(), single_cond.begin(), single_cond.end());

		    groups[i].insert(groups[i].end(), single_groups.begin(), single_groups.end());
		    groups[i].insert(groups[i].end(), single_groups.begin(), single_groups.end());
		    groups[i].insert(groups[i].end(), single_groups.begin(), single_groups.end());
		    groups[i].insert(groups[i].end(), single_groups.begin(), single_groups.end());
        #endif

		int max_len = *max_element(groups[i].begin(), groups[i].end() );
		cache = Cache(spring_conditions[i].size(), VVL(groups[i].size()+1, VL(max_len+1, -1)));

		sum += solve(spring_conditions[i], 0, groups[i], 0, 0);

    }


    std::cout << "Result: " << std::endl;
    std::cout << sum << std::endl;

    return 0;
}



