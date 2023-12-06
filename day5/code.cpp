#include <climits>
#include <set>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>


struct cmpFunction {
    bool operator()(const std::pair<unsigned, unsigned>& a, const std::pair<unsigned, unsigned>& b) const {
        return a.first < b.first;
    }
};

typedef std::map<std::pair<unsigned , unsigned >, unsigned, cmpFunction> almanac;
typedef std::vector<std::pair<unsigned long long, unsigned long long>> interval_vec;

// Read lines with format dst src size into a dict of pairs
// dict[src,size] = dst
// Resulting dict is ordered by src
almanac read_dict(std::string line) {

    almanac dict;
    getline(std::cin, line);
    while(line != "") {
        std::istringstream iss;
        std::string dst, src, len;
        iss.str(line);
        iss >> dst >> src >> len;
        dict[std::make_pair(stoull(src), stoull(len))] = stoull(dst);
        getline(std::cin, line);
    }

    return dict;
}


int  translate(unsigned  int id, almanac dict) {

    for(auto &[k, v] : dict) {
        unsigned  int upper_limit = k.first + k.second;
        if (id >= k.first && id < upper_limit) {
			return v + (id - k.first);
        }
    }
    return id;
}


// Process intervals instead of single seeds:
// Ranges on the dictionary are ordered by (src) and the input 
// is assumed to have ranges well defined.
//
// For (start, lsize) traverse the ranges of the dictionary (src, size),
// if we can fit seeds into that range (i.e. src <= start <= src + size),
// update start and lsize to reflect the change.
// If after going through the dictionary there still seeds to locate,
// do not translate them as requested by the problem.
interval_vec translate_intervals(interval_vec ids, almanac dict) {

    interval_vec result_vector;

    for(int i = 0; i < ids.size(); i++) {
        unsigned long long int start = ids[i].first;
        unsigned long long int size  = ids[i].second;
        
		for(auto &[k, v] : dict) {
			unsigned long int upper_limit = k.first + k.second;
			if (start >= k.first && start <= upper_limit) {
				unsigned long int interval_start = v + (start - k.first);
				unsigned long int interval_size = std::min(upper_limit - start, size);
				result_vector.push_back(std::make_pair(interval_start, interval_size));
				start += interval_size;
				size -= interval_size;
			}
		}
		if (size)
			result_vector.push_back(std::make_pair(start, size));
    }

    return result_vector;

}

int main(int argc, char * argv[]){

    int sum = 0;
    std::string line;
    std::vector<unsigned long long> seeds;
    almanac seed_to_soil, soil_to_fert, fert_to_water, water_to_light, light_to_temp, temp_to_hum, hum_to_loc;
    while (getline(std::cin, line)) {

        std::istringstream iss;
        iss.str(line);
        std::string token;
        iss >> token; // seeds:
        while ( token.find("\n") == std::string::npos && iss >> token) {
            seeds.push_back( stoull(token) );
        }
        getline(std::cin, line);

        getline(std::cin, line);
        seed_to_soil = read_dict(line);

        getline(std::cin, line);
        soil_to_fert = read_dict(line);

        getline(std::cin, line);
        fert_to_water = read_dict(line);

        getline(std::cin, line);
        water_to_light = read_dict(line);

        getline(std::cin, line);
        light_to_temp = read_dict(line);

        getline(std::cin, line);
        temp_to_hum   = read_dict(line);

        getline(std::cin, line);
        hum_to_loc    = read_dict(line);

    }

    unsigned long long int min = ULLONG_MAX;

	#ifndef SECOND_PART
		for(int i = 0; i < seeds.size(); i++) {
			unsigned long long int  soil  = translate(seeds[i], seed_to_soil  );
			unsigned long long int  fert  = translate(soil    , soil_to_fert  );
			unsigned long long int  water = translate(fert    , fert_to_water );
			unsigned long long int  light = translate(water   , water_to_light);
			unsigned long long int  temp  = translate(light   , light_to_temp );
			unsigned long long int  hum   = translate(temp    , temp_to_hum   );
			unsigned long long int  loc   = translate(hum     , hum_to_loc    );
			min = std::min(min, loc);
		
		}
	#else
		for(int i = 0; i < seeds.size(); i+=2) {
			std::cout << "Planting seeds " << seeds[i] << " to " << seeds[i+1] << std::endl;
			interval_vec soil  = translate_intervals({std::make_pair(seeds[i],seeds[i+1])}, seed_to_soil  );
			interval_vec fert  = translate_intervals(soil, soil_to_fert  );
			interval_vec water = translate_intervals(fert , fert_to_water);
			interval_vec light = translate_intervals(water, water_to_light);
			interval_vec temp  = translate_intervals(light, light_to_temp);
			interval_vec hum   = translate_intervals(temp  , temp_to_hum);
			interval_vec loc   = translate_intervals(hum  , hum_to_loc);
			for(auto &it : loc)	min = std::min(it.first, min);
		}
	#endif

    std::cout << "Result: " << min << std::endl;
    return 0;
}




