#include <set>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>


int main(int argc, char * argv[]){

    int sum = 0;
    std::unordered_map<int, int> owned_cards;
    std::string line;
    while (getline(std::cin, line)) {

        std::istringstream iss(line);
        std::string token;
        iss >> token >> token; // Card id:
        token.pop_back();
        
        int id_card = stoi(token);
        owned_cards[id_card]++;
        
        std::set<int> winners;
        iss >> token;
        while ( token.find('|') == std::string::npos) {
            winners.insert( stoi(token) );
            iss >> token;
        }

        int matches = 0;
        while (iss >> token)
            if (winners.count( stoi(token) )) ++matches;

        #ifdef SECOND_PART
            if (matches) {
                while(matches) {
                    owned_cards[id_card + matches] += (owned_cards[id_card]);
                    --matches;
                }
            }
            sum += owned_cards[id_card];
        #else
            if (matches) {
                int local_sum = 1; matches--;
                while (matches--) local_sum *= 2;
                sum += local_sum;
                
            }
        #endif
    }

    std::cout << "Result: " << sum << std::endl;
    return 0;
}




