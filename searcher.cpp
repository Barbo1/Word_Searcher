#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <limits>
#include "./worst.hpp"

#define empty_buffer() std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

void search_word(unsigned MAX_SEARCH, std::string INITIAL_WORD){
    WordSet ws_acu;
    WordSet ws_old;
    WordSet ws_new;
    WordSet::iterator it_1;
    WordSet::iterator it_2;
    std::string com;
    std::string word;
    std::ofstream file("./words.txt");
    std::ofstream erro("./error.txt");
    int i = 0;
    int stat;
    int opt = 1;

    if(file.is_open() && erro.is_open()) {
        ws_acu.aggregate_word(INITIAL_WORD);
        ws_old = WordSet(ws_acu);
        it_1 = WordSet::iterator(ws_old);

        while(!it_1.is_finished() && i < MAX_SEARCH) {
            std::cout << "\t\titeration " << i << std::endl;
            
            word = *it_1;
            com = "python3 find_wr.py " + word;
            stat = system(com.c_str());
            ws_new = from_file_to_set("./def.txt");
            
            if(ws_new.get_words_number() == 0 || stat != 0) {
                ws_acu.delete_word(word);
                erro << word << std::endl;
            } else {
                for(it_2 = WordSet::iterator(ws_new); !it_2.is_finished(); ++it_2) {
                    if(!ws_acu.is_word(*it_2)) {
                        ws_acu.aggregate_word(*it_2);
                        ws_old.aggregate_word(*it_2);
                    }
                }
            }
            i++;
            ++it_1;
            ws_old.delete_word(word);
        }

        for(it_1 = WordSet::iterator(ws_acu); !it_1.is_finished(); ++it_1) {
            file << *it_1 << std::endl;
        }

        system("rm def.txt");
        file.flush();
        erro.flush();
    }
    file.close();
    erro.close();
}

void print_help(){

}

int main() {
    char option = 1;
    char letter;
    unsigned max_iteration = 10;
    std::string first_word = "stood";
    WordSet ws;

    while(option != 0) {
        system("clear");
        std::cout << "\t---------------------------------------\t\t Max iterations = " << max_iteration << std::endl;
        std::cout << "\t-            Word Searcher            -\t\t First word = " << first_word << std::endl;
        std::cout << "\t---------------------------------------" << std::endl;
        std::cout << "\t\tSelect an option:" << std::endl;
        std::cout << "\t\t\t0 - exit" << std::endl;
        std::cout << "\t\t\t1 - help" << std::endl;
        std::cout << "\t\t\t2 - change 'Max iterations'" << std::endl;
        std::cout << "\t\t\t3 - change 'First word'" << std::endl;
        std::cout << "\t\t\t4 - search" << std::endl;
        std::cout << "\t\t\t5 - print finded words" << std::endl; 
        std::cout << "\t\t\t6 - print error words" << std::endl; 
        std::cout << std::endl << "\t\toption:" << std::endl; 
        std::cout << "\t\t\t";
        
        option = getchar() - 48;
        switch(option){
            case 0: 
                    break;
            case 1:
                    print_help();
                    break;
            case 2:
                    empty_buffer();
                    max_iteration = 0;
                    system("clear");
                    std::cout << std::endl << "\t\t\tEnter the number of 'Max iterations':" << std::endl << "\t\t\t";
                    while((letter = getchar()) != EOF && 0 <= (letter -= 48) && letter < 10) {
                        max_iteration *= 10;
                        max_iteration += letter;
                    }
                    break;
            case 3:
                    empty_buffer();
                    first_word = "";
                    system("clear");
                    std::cout << std::endl << "\t\t\tEnter the word of 'first word':" << std::endl << "\t\t\t";
                    while((letter = getchar()) != EOF && 
                            ((65 <= letter && letter <= 90) ||
                            (97 <= letter && letter <= 122)) ) {
                        first_word += letter;
                    }
                    break;
            case 4:
                    system("clear");
                    search_word(max_iteration, first_word);
                    break;
            case 5:
                    ws = from_file_to_set("./words.txt");
                    for(WordSet::iterator it(ws); !it.is_finished(); ++it) {
                        std::cout << *it << ", ";
                    }
                    break;
            case 6:
                    ws = from_file_to_set("./error.txt");
                    for(WordSet::iterator it(ws); !it.is_finished(); ++it) {
                        std::cout << *it << ", ";
                    }
                    break;
            default:
                    std::cout << "\t\toption ingresed doesn't exist, please enter a existent one.";
        }
        std::cout << std::endl << "\t\tpress Any letter..." << std::endl;
        getchar();
        empty_buffer();
        system("clear");
    }
    return 0;
}
