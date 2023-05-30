#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <limits>
#include "./worst.hpp"

#define empty_buffer() std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

void search_word (unsigned MAX_SEARCH, std::string INITIAL_WORD){
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

    if (file.is_open() && erro.is_open()) {
        ws_acu.aggregate_word(INITIAL_WORD);
        ws_old = WordSet(ws_acu);
        it_1 = WordSet::iterator(ws_old);

        while (!it_1.is_finished() && i < MAX_SEARCH) {
            std::cout << "\t\titeration " << i << std::endl;
            
            word = *it_1;
            com = "python3 find_wr.py " + word;
            stat = system(com.c_str());
            ws_new = from_file_to_set("./.def.txt");
            
            if (ws_new.get_words_number() == 0 || stat != 0) {
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

        for (it_1 = WordSet::iterator(ws_acu); !it_1.is_finished(); ++it_1) {
            file << *it_1 << std::endl;
        }

        system("rm .def.txt");
        file.flush();
        erro.flush();
    }
    file.close();
    erro.close();
}

void print_help(){
    std::cout << "\thelp scream:" << std::endl;
    std::cout << "\t\tThis application is used to search words in the internet. The 'First word'" << std::endl;
    std::cout << "\t\tis searched in the WordReference dictionary, store the words of the definition" << std::endl;
    std::cout << "\t\tin a WordSet and search recursively the new finded words. because this process" << std::endl;
    std::cout << "\t\tcan be made so many times, there is a 'Max iterarions', the quantity of words" << std::endl;
    std::cout << "\t\tthat will be searched." << std::endl << std::endl;
    std::cout << "\t\tpossible options:" << std::endl;
    std::cout << "\t\t\t0\t Quit the application." << std::endl;
    std::cout << "\t\t\t1\t Print this help scream." << std::endl;
    std::cout << "\t\t\t2\t Change the quantity of iterations made to search words. This will take" << std::endl;
    std::cout << "\t\t\t\t the firsts characters ingressed that represent a number, if placed at the" << std::endl;
    std::cout << "\t\t\t\t beginning." << std::endl;
    std::cout << "\t\t\t3\t Change the first word that will be searched. This will take the firsts" << std::endl;
    std::cout << "\t\t\t\t characters ingressd that represent a word, if placed at the beginning." << std::endl;
    std::cout << "\t\t\t4\t Start the search operation." << std::endl;
    std::cout << "\t\t\t5\t Print the finded words given by 'words.txt'" << std::endl;
    std::cout << "\t\t\t6\t Print the words that trigger an error in 'error.txt'" << std::endl;
    std::cout << "\t\t\t" << std::endl;
    std::cout << "\t\t\t" << std::endl;
}

int main () {
    char option = 1;
    char residual;
    unsigned max_iteration = 10;
    std::string first_word = "stood";
    WordSet ws;
    WordSet::iterator it;

    while (option != 0) {
        system("clear");
        std::cout << "\t---------------------------------------\t\t Max iterations = " << max_iteration << std::endl;
        std::cout << "\t|            Word Searcher            |" << std::endl;
        std::cout << "\t---------------------------------------\t\t First word = " << first_word << std::endl;
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
        empty_buffer();
        system("clear");
        switch (option) {
            case 0: 
                    std::cout << "\t\tgoodbye :)" << std::endl;
                    break;
            case 1:
                    print_help();
                    break;
            case 2:
                    max_iteration = 0;
                    std::cout << std::endl << "\t\t\tEnter the number of 'Max iterations':" << std::endl << "\t\t\t";
                    while ((residual = getchar()) != EOF && 0 <= (residual -= 48) && residual < 10) {
                        max_iteration *= 10;
                        max_iteration += residual;
                    }
                    break;
            case 3:
                    first_word = "";
                    std::cout << std::endl << "\t\t\tEnter the word of 'first word':" << std::endl << "\t\t\t";
                    while ((residual = getchar()) != EOF && 
                            ((65 <= residual && residual <= 90) ||
                            (97 <= residual && residual <= 122)) ) {
                        first_word += residual;
                    }
                    break;
            case 4:
                    if (first_word != "") {
                        search_word(max_iteration, first_word);
                    } else {
                        std::cout << "\t\tThere is not a word. Please ingress one.";
                    }
                    break;
            case 5:
                    std::cout << "\t\twords finded:" << std::endl;
                    ws = from_file_to_set("./words.txt");
                    for (it = WordSet::iterator(ws); !it.is_finished(); ++it) {
                        std::cout << *it << ", ";
                    }
                    break;
            case 6:
                    std::cout << "\t\twords that trigger an error:" << std::endl;
                    ws = from_file_to_set("./error.txt");
                    for (it = WordSet::iterator(ws); !it.is_finished(); ++it) {
                        std::cout << *it << ", ";
                    }
                    break;
            default:
                    std::cout << "\t\toption ingresed doesn't exist, please enter a existent one.";
        }
        std::cout << std::endl << "\t\tpress Enter..." << std::endl;
        empty_buffer();
    }
    return 0;
}
