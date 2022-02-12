#include <iostream>
#include <chrono>
#include <ncurses.h>
#include <fstream>
#include <string>
#include <locale.h>
#include <vector>

#include "color.h"

std::vector <std::string> VEC_WORDS(10000);

void read_words();
int get_string(std::string str);
std::string pick_random_word();

int main() {

    read_words();
    srand(time(0));
    setlocale(LC_ALL, "");

    int yMax, xMax, typex, typey;

    initscr();
    getmaxyx(stdscr, yMax, xMax);

    WINDOW * type_input_win = newwin(7, 47, yMax/2, (xMax-42)/2);
    //box(type_input_win, 0, 0);
    refresh();
    getbegyx(type_input_win, typey, typex);

    typey++; typex++;
    int words_typed = 0, calc;
    long long total_time = 0;

    mvwprintw(type_input_win, 3, 0, "%ls", L"┌─────────────────────────────────────────────┐");
    mvwprintw(type_input_win, 4, 0, "%ls", L"│  >                                          │");
    mvwprintw(type_input_win, 5, 0, "%ls", L"└─────────────────────────────────────────────┘");

    while (1) {
        std::string temp_word = pick_random_word();
        mvwprintw(type_input_win, 2, 4, "                                ");
        mvwprintw(type_input_win, 2, 4, " %s", temp_word.c_str());
        wrefresh(type_input_win);
        move(typey+3, typex+4);
        refresh();
        int time = get_string(temp_word);
        total_time += time/1000000;
        if (time) {
            words_typed++;
            calc = (words_typed*60)/total_time;
        }
        mvwprintw(type_input_win, 4, 0, "%ls", L"│  >                                          │");
        mvwprintw(type_input_win, 2, 36, "WPM %d", calc);
        mvwprintw(type_input_win, 4, 36, "WRD %d", words_typed);
    }
    endwin();
}

void read_words() {
    std::ifstream file("words.txt");
    std::string temp_str;
    int i = 0;
    while (file >> temp_str) {
        VEC_WORDS[i] = temp_str;
        i++;
    }
    file.close();
} 

int get_string(std::string str) {
    auto start = std::chrono::high_resolution_clock::now();
    std::string input, temp = "";
    nocbreak();
    echo();

    char hello[40];
    scanw("%30s", hello);
    input = std::string(hello);

    cbreak();
    if (input == "!quit") {
        endwin();
        exit(0);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    if (input == str) {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        return duration.count();
    }
    return 0;
}

std::string pick_random_word() {
    int random_int = rand()%10000;
    return VEC_WORDS[random_int];
}
