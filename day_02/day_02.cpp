#include <iostream>
#include <map>
#include <string>

int win_points = 6;
int loss_points = 0;
int draw_points = 3;

int main() {
    int my_points = 0;
    int desired_points = 0;

    std::string input;
    int left, right;
    int theirs, mine;
    int desired_outcome = 0;
    while (std::getline(std::cin, input)) {
        left = static_cast<int>(input[0]); 
        right = static_cast<int>(input[2]);

        switch (left) {
            case 65: theirs = 1; break; // rock
            case 66: theirs = 2; break; // paper
            case 67: theirs = 3; break; // scissors
        }
        switch (right) {
            case 88: 
                mine = 1;
                desired_outcome = 0; // lose
                break; // rock
            case 89: 
                mine = 2; 
                desired_outcome = 1; // draw
                break; // paper
            case 90: 
                mine = 3; 
                desired_outcome = 2; // win
                break; // scissors
        }
        // actual
        if (mine == theirs) {
            my_points += mine + draw_points;
        } else {
            // wins
            int result = mine - theirs;
            if (result == 1 || result == -2) { my_points += mine + win_points; }
            // loss
            else { my_points += mine; }
        }
        // desired
        // draw
        if (desired_outcome == 1) { desired_points += theirs + draw_points; }
        // lose
        else if (desired_outcome == 0) {
            mine = theirs - 1 < 1 ? 3 : theirs - 1;
            desired_points += loss_points + mine;
        // win
        }else if (desired_outcome == 2) {
            mine = theirs + 1 > 3 ? 1 : theirs + 1;
            desired_points += win_points + mine;
        }
    }
    std::cout << "My points: " << my_points << std::endl;
    std::cout << "Desired points: " << desired_points << std::endl;
}