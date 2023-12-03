#include <algorithm>
#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

#define BLUE_pos 0
#define RED_pos  1
#define GREEN_pos 2

int get_pos(std::string color) {
    if (color == "red"  ) return RED_pos;
    if (color == "blue" ) return BLUE_pos;
    if (color == "green") return GREEN_pos;

    return 0;
}

int main(int argc, char * argv[]){

    // 12 red cubes, 13 green cubes, and 14 blue cubes
    std::vector<int> current_balls = {14, 12, 13};

    int sum = 0;
    std::string line;
    while (getline(std::cin, line)) {
        bool valid = true;
        std::replace( line.begin(), line.end(), ':', ' '); // Remove ':'
        std::replace( line.begin(), line.end(), ',', ' '); // Remove ','
        std::replace( line.begin(), line.end(), ';', ' '); // Remove ';'

        std::istringstream iss(line);
        std::string id;
        iss >> id >> id; // Game id

        int num_balls;
        std::string color;
        #ifdef SECOND_PART
            std::vector<int> max_balls = {0, 0, 0};
        #endif
        while(iss >> num_balls >> color) {
            std::cout << id << " " << num_balls << " " << color << std::endl;
            int color_pos = get_pos(color);
            #ifdef SECOND_PART
                valid = false;
                max_balls[color_pos] = std::max(max_balls[color_pos], num_balls);
            #endif
            if (num_balls > current_balls[get_pos(color)]) valid = false;
        }

        if (valid) sum += stoi(id);
        #ifdef SECOND_PART
            sum += max_balls[0] * max_balls[1] * max_balls[2];
        #endif
    }

    std::cout << "Result: " << sum << std::endl;
    return 0;
}




