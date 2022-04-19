#include <iostream>
#include <map>
#include <chrono>

#include "tree.h"

using duration_t = std::chrono::microseconds;

int main() {
    std::map<std::string, unsigned long long> rb_tree;
    TRBTree tree; 

    char *str = (char*)calloc(257,sizeof(char)); 
    char *word = (char*)calloc(257,sizeof(char)); 
    unsigned long long inpval;

    if (str == NULL || str == nullptr || word == NULL || word == nullptr) {
        printf("ERROR: allocation error\n");
        return -1;
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t rb_ts = 0, bst_ts = 0;

    while (scanf("%s", str) != EOF) {
        if (strlen(str)>256) {
            printf("ERROR: uncorrect input\n");
            continue;
        }

        if (str[0] == '+') {
            if (scanf("%s %llu", word, &inpval) == EOF) {
                break;
            }

            if (strlen(word)>256) {
                printf("ERROR: uncorrect input\n");
                continue;
            }

            start = std::chrono::system_clock::now();
            rb_tree.insert( {word, inpval} );
            end = std::chrono::system_clock::now();
            rb_ts += std::chrono::duration_cast<duration_t>( end - start ).count();

            start = std::chrono::system_clock::now();
            int mrk = tree.Insert(word, inpval);
            end = std::chrono::system_clock::now();
            bst_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
        }
        else if (str[0] == '-') {
            if (scanf("%s", word) == EOF) {
                break;
            }

            if (strlen(word)>256) {
                printf("ERROR: uncorrect input\n");
                continue;
            }

            start = std::chrono::system_clock::now();
            rb_tree.erase(word);
            end = std::chrono::system_clock::now();
            rb_ts += std::chrono::duration_cast<duration_t>( end - start ).count();

            start = std::chrono::system_clock::now();
            int mrk = tree.Remove(word);
            end = std::chrono::system_clock::now();
            bst_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
        }
        else {
            start = std::chrono::system_clock::now();
            rb_tree.find(word);
            end = std::chrono::system_clock::now();
            rb_ts += std::chrono::duration_cast<duration_t>( end - start ).count();

            start = std::chrono::system_clock::now();
            tree.Search(word);
            end = std::chrono::system_clock::now();
            bst_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
        }
    }
    
    tree.Destroy(); 
    free(str);
    free(word);

    std::cout << "std::map ms = " << rb_ts << "\nrb ms = " << bst_ts << std::endl;

    return 0;
}