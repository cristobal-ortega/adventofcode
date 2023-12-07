#include <algorithm>
#include <stdio.h>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <vector>


std::map<char, int> letter_to_int = {
    {'A',14},
    {'K',13},
    {'Q',12},
    #ifdef SECOND_PART
        {'J', 1},
    #else
        {'J',11},
    #endif
    {'T',10},
    {'9', 9},
    {'8', 8},
    {'7', 7},
    {'6', 6},
    {'5', 5},
    {'4', 4},
    {'3', 3},
    {'2', 2},
    #ifdef SECOND_PART
        {'J', 1},
    #endif
};

#define POINTS_FIVE     7
#define POINTS_FOUR     6
#define POINTS_FULL     5
#define POINTS_THREE    4
#define POINTS_TWO_PAIR 3
#define POINTS_ONE_PAIR 2
#define POINTS_UNIQUE   1

int get_points(std::map<int, int> num_cards) {

    #ifdef SECOND_PART
        // We have jokers
        if(num_cards[1] == 5) return POINTS_FIVE; // improves worst case
        if(num_cards[1]--) {
            int max_points = 0;
            for(int i = 2; i <= 14; ++i) {
                if (!num_cards[i]) continue;
                num_cards[i]++;
                max_points = std::max(max_points, get_points(num_cards));
                num_cards[i]--;
            }

            return max_points;

        }
    #endif

    bool three_en = false;
    int two_en   = 0;
    for(auto &[k, v] : num_cards) {
        if (v == 5) return POINTS_FIVE;
        if (v == 4) return POINTS_FOUR;
        if (v == 3) three_en = true;
        if (v == 2) two_en++;
    }

    if      (three_en && two_en     ) return POINTS_FULL;
    else if (three_en               ) return POINTS_THREE;
    else if (            two_en == 2) return POINTS_TWO_PAIR;
    else if (            two_en == 1) return POINTS_ONE_PAIR;

    return POINTS_UNIQUE;

}

struct hand {
    int bid;
    int points;
    std::vector<int> cards;
};

static bool comp(const hand& h1, const hand& h2){

    if (h1.points > h2.points) return true;
    if (h1.points < h2.points) return false;

    // same points
    for(int i = 0; i < h1.cards.size(); i++) {
        if (h1.cards[i] > h2.cards[i]) return true;
        if (h1.cards[i] < h2.cards[i]) return false;
    }

    return true;
}


int main(int argc, char * argv[]){

    std::string line;
    std::vector<hand> hands;

    while(getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string token;

        iss >> token;
        struct hand h;

        std::map<int, int> num_cards;
        for(auto &c : token) {
            h.cards.push_back(letter_to_int[c]);
            num_cards[letter_to_int[c]]++;
        }
        h.points = get_points(num_cards);

        iss >> token;
        h.bid = stoi(token);
        hands.push_back(h);

    }

    std::sort(hands.begin(), hands.end(), comp);

    int sum = 0;
    for(int i = 0; i < hands.size(); i++) {
        sum += (hands.size() - i) * hands[i].bid;
    }

    std::cout << "Result: " << sum << std::endl;
    return 0;
}




