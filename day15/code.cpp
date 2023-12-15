#include <algorithm>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <list>
#include <vector>


int get_hash(std::string str) {

    int current_value = 0;
    for(auto &c : str) {
        int ascii_repr = (int) c;
        current_value = ((current_value + ascii_repr) * 17) % 256;
        // std::cout << "For " << c << " = " << current_value <<std::endl;
    }

    return current_value;
}

typedef struct {
    std::string name;
    int focal_length;
} Label;


void add_box(std::vector<std::list<Label>> &boxes, Label l) {
    
    std::list<Label> *current = &boxes[get_hash(l.name)];
    auto match = std::find_if((*current).begin(), (*current).end(), [l] (const Label s) {
                                                                    return s.name == l.name;
                                                                    });

    if (match != (*current).cend()) {
        match->focal_length = l.focal_length;
    } else {
        (*current).push_back(l);
    }

}

void rm_box(std::vector<std::list<Label>> &boxes, Label l) {

    std::list<Label> *current = &boxes[get_hash(l.name)];
    auto match = std::find_if((*current).begin(), (*current).end(), [l] (const Label s) {
                                                                    return s.name == l.name;
                                                                     });


    if (match != (*current).cend())
        (*current).erase(match);

}

int get_label(std::string str, Label &l) {

    int i = 0;
    l.name = "";
    for(i = 0; i < str.length(); i++) {
        if (str[i] == '-') return 0;
        if (str[i] == '=') break;
        l.name += str[i];
    }
    
    l.focal_length = stoi(str.substr(i+1, str.length()));
    
    return 1;

}

int main(int argc, char * argv[]){



    std::string line;

    getline(std::cin, line);

    std::stringstream input(line);
    std::string segment;

    std::vector<std::list<Label>> boxes(256);

    unsigned long long int sum = 0;
    while(std::getline(input, segment, ','))
    {
        int tmp = get_hash(segment);
        sum += get_hash(segment);

        Label l;
        if (get_label(segment, l)) {
            add_box(boxes, l);
        } else {
            rm_box(boxes, l);
        }
    }

    #ifdef SECOND_PART
        sum = 0;
        for(int i = 0; i < boxes.size(); i++) {
            std::list<Label> current = boxes[i];
            if (!current.empty()) {
                int j = 1;
                for(auto &it : current) {
                    sum += (i+1)*(j++)*it.focal_length; 
                }
            }
        }
    #endif

    std::cout << "Result: " << sum << std::endl;

    return 0;
}



