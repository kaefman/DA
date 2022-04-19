#include "tree.h"

int main() {
    TRBTree tree; 

    char *str = (char*)calloc(257,sizeof(char)); 
    char *word = (char*)calloc(257,sizeof(char)); 
    unsigned long long inpval;

    if (str == NULL || str == nullptr || word == NULL || word == nullptr) {
        printf("ERROR: allocation error\n");
        return -1;
    }

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

            int mrk = tree.Insert(word, inpval);

            if (mrk == 0) {
                printf("OK\n");
            }
            else {
                if (mrk == -7) {
                    printf("Exist\n");
                }
                else if (mrk == -3) {
                    printf("ERROR: empty input\n");
                }
                else if (mrk == -4) {
                    printf("ERROR: untraced allocation error\n");
                }
                else if (mrk == -1) {
                    printf("ERROR: out of memory\n");
                }
                else {
                    printf("ERROR: unknown error\n");
                }
            }
        }
        else if (str[0] == '-') {
            if (scanf("%s", word) == EOF) {
                break;
            }

            if (strlen(word)>256) {
                printf("ERROR: uncorrect input\n");
                continue;
            }

            int mrk = tree.Remove(word);
            if (mrk == 0) {
                printf("OK\n");
            }
            else if (mrk == -8) {
                printf("NoSuchWord\n");
            }
            else if (mrk == -1) {
                printf("ERROR: out of memory\n");
            }
            else {
                printf("ERROR: unknown error\n");
            }
        }
        else if (str[0] == '!') {
            std::string path;
            if (scanf("%s", word) == EOF) {
                break;
            }

            if (strcmp(word, "Save") == 0) {
                std::cin >> path;
                
                int mrk = tree.SaveToDisk(path); 
                if (mrk == 0) {
                    printf("OK\n");
                    continue;
                }
                else if (mrk == 1) {
                    printf("OK\n");
                    continue;
                }
                else if (mrk == -1) {
                    printf("ERROR: unable to open file\n");
                    continue;
                }
                else if (mrk == -2) {
                    printf("ERROR: unable to write file\n");
                    continue;
                }
                else if (mrk == -3) {
                    printf("ERROR: file acsess error\n");
                    continue;
                }
                else {
                    printf("ERROR: something gone wrong\n");
                    continue;
                }
            }
            else if (strcmp(word, "Load") == 0) {
                std::cin >> path;

                int mrk = tree.LoadFromDisk(path); 
                if (mrk == 0) {
                    printf("OK\n");
                    continue;
                }
                else if (mrk == -1) {
                    printf("ERROR: file is damaged\n");
                    continue;
                }
                else if (mrk == -2) {
                    printf("ERROR: wrong format of file\n");
                    continue;
                }
                else if (mrk == -3) {
                    printf("ERROR: file acsess error\n");
                    continue;
                }
                else {
                    printf("ERROR: something gone wrong\n");
                    continue;
                }
            }
        }
        else {
            TRBNode* res = tree.Search(str);
            if (res != nullptr) {
                printf("OK: %llu\n",res->Value);
            }
            else {
                printf("NoSuchWord\n");
            }
        }
    }
    
    tree.Destroy(); 
    free(str);
    free(word);

    return 0;
}