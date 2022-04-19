#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>

const char BLACK = 1;
const char RED = 2;

class TRBNode {
public: 
    char* Key; 
    unsigned long long Value;
    char Colour = BLACK;

    TRBNode* Left = nullptr;
    TRBNode* Right = nullptr; 
    TRBNode* Parent = nullptr;

    TRBNode() {
        Key = (char*)calloc(257,sizeof(char));
        if(Key == nullptr) {
            throw std::bad_alloc();
        }
        Value = 0;
        Key = strcpy(Key,"");
    }

    TRBNode(char* k, unsigned long long v) {
        Key = (char*)calloc(257,sizeof(char));
        if(Key == nullptr) {
            throw std::bad_alloc();
        }
        Value = v;
        Key = strcpy(Key, k); 
    }

    ~TRBNode() {
        free(Key);
    }

    TRBNode* Sibling() {
        if (Parent != nullptr && Parent->Left != nullptr && Parent->Right != nullptr) {
            if (Parent->Left->Key == Key) {
                return Parent->Right; 
            }
            else {
                return Parent->Left;
            }
        }
        else {
            return nullptr;
        }
    }

    bool Isleft() {
        if (Parent != nullptr && Parent->Left != nullptr && Parent->Left->Key != nullptr && Parent->Left->Key == Key) {
            return true; 
        }
        else {
            return false;
        }
    }

    bool Islist() {
        if (Right == nullptr || Left == nullptr) {
            return true; 
        }
        else {
            return false;
        }
    }
};

int strequal (const char* lhs, const char* rhs) {
    if(lhs == nullptr || rhs == nullptr) {
        if(lhs == nullptr) {
            return -1;
        }
        if(rhs == nullptr) {
            return 1;
        }
    }

    size_t i=0;
    while (lhs[i]!=0 || rhs[i]!=0) {
        if (lhs[i] == rhs[i]) {
            ++i;
            continue;
        }
        else {
            char cmp_l = lhs[i];
            char cmp_r = rhs[i];
            if(lhs[i] >= 'A' && lhs[i] <= 'Z') {
                cmp_l = lhs[i] + ('a' - 'A');
            } 
            if(rhs[i] >= 'A' && rhs[i] <= 'Z') {
                cmp_r = rhs[i] + ('a' - 'A');
            } 
            
            if(cmp_l < cmp_r) {
                return -1;
            } else 
            if(cmp_l > cmp_r) {
                return 1;
            } else {
                ++i;
                continue;
            }
        }
    }
    if(lhs[i]!=0 || rhs[i]!=0)
    {
        if(lhs[i]==0) {
            return -1;
        } 
        if(rhs[i]==0) {
            return 1;
        }
    }

    return 0;
}

void Tree_print(TRBNode* start, int counter) { 
    if (start == nullptr) {
        return;
    }

    Tree_print(start->Right, counter + 1);
    for (int i = 0; i < counter; ++i) {
        printf("\t");
    }
    printf("( ");
    if(start->Parent!=nullptr) {
        printf("%s<-p|",start->Parent->Key);
    }
    else {
        printf("nullptr <-p|");
    }
    printf("%s",start->Key);
    printf(" | %llu ) - | ", start->Value);
    if (start->Colour == RED) {
        printf("RED");
    }
    else {
        printf("BLACK");
    }
    printf("|\n");
    Tree_print(start->Left, counter + 1);
}

void Swap(TRBNode* lhs, TRBNode* rhs) {
    char* tmpkey = (char*)calloc(300,sizeof(char));

    if(tmpkey == nullptr) {
        throw -1;
    }

    tmpkey = strcpy(tmpkey,rhs->Key);
    unsigned long long tmpval = rhs->Value;

    rhs->Key = strcpy(rhs->Key,lhs->Key);
    rhs->Value = lhs->Value; 

    lhs->Key = strcpy(lhs->Key,tmpkey);
    lhs->Value = tmpval;
    free(tmpkey);
}

TRBNode* LeftRotate(TRBNode* centre) {
    if (centre->Parent != nullptr) {
        if (centre->Parent->Left == centre) {
            centre->Parent->Left = centre->Left;
        }
        else
        if (centre->Parent->Right == centre) {
            centre->Parent->Right = centre->Left;
        }
    }

    TRBNode* new_centre = centre->Left;
    centre->Left = centre->Left->Right;
    centre->Left->Parent = centre;
    
    new_centre->Parent = centre->Parent;
    new_centre->Right = centre;
    centre->Parent = new_centre;


    return new_centre;
}

TRBNode* RightRotate(TRBNode* centre) {
    if (centre->Parent != nullptr) {
        if (centre->Parent->Left == centre) {
            centre->Parent->Left = centre->Right;
        }
        else
        if (centre->Parent->Right == centre) {
            centre->Parent->Right = centre->Right;
        }
    }

    TRBNode* new_centre = centre->Right;
    centre->Right = centre->Right->Left;
    centre->Right->Parent = centre;

    new_centre->Parent = centre->Parent;
    new_centre->Left = centre;
    centre->Parent = new_centre;


    return new_centre;
}



TRBNode* RMreballance(TRBNode* start_element, TRBNode* root) {
    if (root == start_element) {
        return root;
    }
    else {
        TRBNode* sibl = start_element->Sibling();
    
        if (sibl->Colour == RED) {
            if (sibl->Isleft()) {
                
                if (start_element->Parent == root) {
                    root = LeftRotate(start_element->Parent);
                }
                else {
                    LeftRotate(start_element->Parent);
                }

                sibl->Colour = BLACK;
                sibl->Right->Colour = RED;//

                root = RMreballance(start_element, root);
            }
            else {
                if (start_element->Parent == root) {
                    root = RightRotate(start_element->Parent);
                }
                else {
                    RightRotate(start_element->Parent);
                }

                sibl->Colour = BLACK;
                sibl->Left->Colour = RED;

                root = RMreballance(start_element, root);
            }
        }
        else {
            if (sibl->Isleft()) {
                if (sibl->Left->Colour == BLACK && sibl->Right->Colour == BLACK && sibl->Parent->Colour == BLACK) {
                    sibl->Colour = RED;
                    sibl->Parent->Colour = BLACK;

                    root = RMreballance(start_element->Parent, root);
                }
                else
                if (sibl->Left->Colour == BLACK && sibl->Right->Colour == BLACK && sibl->Parent->Colour == RED) {
                    sibl->Colour = RED;
                    sibl->Parent->Colour = BLACK;
                }
                else
                if (sibl->Right->Colour == RED && sibl->Left->Colour == BLACK) {
                    sibl->Right->Colour = BLACK;
                    sibl->Colour = RED;
                    RightRotate(sibl);
                    
                    root = RMreballance(start_element, root);
                }
                else
                if (sibl->Left->Colour == RED) {
                    sibl->Colour = sibl->Parent->Colour;
                    sibl->Parent->Colour = BLACK;
                    //sibl->Right->Colour = BLACK;
                    sibl->Left->Colour = BLACK;

                    if (sibl->Parent == root) {
                        root = LeftRotate(sibl->Parent);
                    }
                    else {
                        LeftRotate(sibl->Parent);
                    }
                }
            }
            else
            {
                if (sibl->Left->Colour == BLACK && sibl->Right->Colour == BLACK && sibl->Parent->Colour == BLACK) {
                    sibl->Colour = RED;
                    sibl->Parent->Colour = BLACK;

                    root = RMreballance(start_element->Parent, root);
                }
                else
                if (sibl->Left->Colour == BLACK && sibl->Right->Colour == BLACK && sibl->Parent->Colour == RED) {
                    sibl->Colour = RED;
                    sibl->Parent->Colour = BLACK;
                }
                else
                if (sibl->Left->Colour == RED && sibl->Right->Colour == BLACK) {
                    sibl->Left->Colour = BLACK;
                    sibl->Colour = RED;
                    LeftRotate(sibl);

                    root = RMreballance(start_element, root);
                }
                else
                if (sibl->Right->Colour == RED) {
                    sibl->Colour = sibl->Parent->Colour;
                    sibl->Parent->Colour = BLACK;
                    sibl->Right->Colour = BLACK;

                    if (sibl->Parent == root) {
                        root = RightRotate(sibl->Parent);
                    }
                    else {
                        RightRotate(sibl->Parent);
                    }
                }
            }
        }

        return root;
    }
}

TRBNode* ISreballance(TRBNode* start_element,TRBNode* root) {

    if (start_element->Parent == nullptr) {
        start_element->Colour = BLACK;
    }
    
    if (start_element->Colour == RED) {
        if (start_element->Parent != nullptr && start_element->Parent->Colour == RED) {
            if (start_element->Parent->Sibling() != nullptr) {
                if (start_element->Parent->Sibling()->Colour == BLACK) {
                    int rcm = 0;
                    TRBNode* new_centre;
                    if (!start_element->Parent->Isleft()) {
                        if (start_element->Isleft()) {
                            if (start_element->Parent->Parent == root) {
                                rcm = 1;
                            }
                    
                            new_centre = LeftRotate(start_element->Parent);
                            new_centre = RightRotate(start_element->Parent);

                            if (rcm == 1) {
                                root = new_centre;
                                rcm = 0;
                            }
                        }
                        else {
                            if (start_element->Parent->Parent == root) {
                                rcm = 1;
                            }
                            new_centre = RightRotate(start_element->Parent->Parent);

                            if (rcm == 1) {
                                root = new_centre;
                                rcm = 0;
                            }
                        }


                        new_centre->Colour = BLACK;
                        new_centre->Left->Colour = RED;
                        new_centre->Right->Colour = RED;
                    }
                    else {
                        if (!start_element->Isleft()) {
                            if (start_element->Parent->Parent == root) {
                                rcm = 1;
                            }

                            new_centre = RightRotate(start_element->Parent);
                            new_centre = LeftRotate(start_element->Parent);

                            if (rcm == 1) {
                                root = new_centre;
                                rcm = 0;
                            }
                        }
                        else {
                            if (start_element->Parent->Parent == root) {
                                rcm = 1;
                            }
                            new_centre = LeftRotate(start_element->Parent->Parent);

                            if (rcm == 1) {
                                root = new_centre;
                                rcm = 0;
                            }
                        }


                        new_centre->Colour = BLACK;
                        new_centre->Left->Colour = RED;
                        new_centre->Right->Colour = RED;
                    }

                }
                else {
                    start_element->Parent->Parent->Colour = RED;
                    start_element->Parent->Parent->Left->Colour = BLACK;
                    start_element->Parent->Parent->Right->Colour = BLACK;
                    root = ISreballance(start_element->Parent->Parent,root);
                }
            }
            else {
                if (start_element->Parent->Parent == nullptr) {
                    start_element->Parent->Colour = BLACK;
                }
                else {
                    start_element->Parent->Parent->Colour = RED;
                    start_element->Parent->Colour = BLACK;
                }
            }
        }
        else {
            return root;
        }
    }
    else {
        return root;
    }
    return root;
}

int BlackHeigth(TRBNode* start) {
    int counter = 0;
    while (!start->Islist()) {
        if (start->Colour == BLACK) {
            ++counter;
        }
        start = start->Right;
    }

    return counter;
}

int HeigthChecker(TRBNode* start,int maxheigth,int heigth) {
    if (start->Islist() && heigth!=maxheigth) {
        return -1;
    }
    else if (!start->Islist() && ((start->Parent != nullptr && !(start->Parent->Right == start || start->Parent->Left== start))||(start->Left->Parent!=start)||(start->Right->Parent!=start))) {
        return -1;
    }
    else {
        int nextheigth = heigth;
        if (start->Colour == BLACK) {
            nextheigth++;
        }

        if (!start->Islist()) {
            if (HeigthChecker(start->Right, maxheigth, nextheigth) != -1 && HeigthChecker(start->Left, maxheigth, nextheigth) != -1) {
                return 0;
            }
            else {
                return -1; 
            }
        }
        else {
            return 0;
        }
    }
}

TRBNode* LoadNode(std::ifstream& fin,TRBNode* pst) {
    int siz[1]; siz[0] = 0;
    unsigned long long val[1]; val[0] = 0;
    char ch[1]; ch[0] = 0;
    try {
        fin.read((char*)&siz[0], sizeof(int) / sizeof(char));
        if(siz[0]<0||siz[0]>257) {
            throw -1;
        }

        char* stri = (char*)calloc(siz[0]+1,sizeof(char));
        if(stri == nullptr) {
            throw -1;
        }
    
        fin.read(&stri[0], siz[0]);

        stri[siz[0]] = 0;
        fin.read((char*)&val[0], sizeof(unsigned long long) / sizeof(char));
        fin.read(&ch[0], 1);
        TRBNode *ND = new(TRBNode);

        if(ND->Key == nullptr) {
            free(stri);
            delete ND;
            throw -1;
        }

        ND->Key = strcpy(ND->Key,stri);
        free(stri);
        ND->Value = val[0];
        ND->Colour = ch[0];
        ND->Parent = pst;

        if (siz[0] == 0) {
            delete ND;
            return nullptr;
        }
        return ND;
    }
    catch (std::ios_base::failure& fail) {
        throw -1; 
    }
    catch (std::bad_alloc()) {
        throw -1;
    }
}

void DestroyNode(TRBNode* dyb) {
    delete dyb;
}

void DestroyTree(TRBNode* root) {
    if (root != nullptr) {
        if (root->Left != nullptr) {
            DestroyTree(root->Left);
            root->Left = nullptr;
        }
        if (root->Right != nullptr) {
            DestroyTree(root->Right);
            root->Right = nullptr;
        }

        DestroyNode(root);
    }
}


TRBNode* LoadTree(std::ifstream& fin, TRBNode* root) {
    TRBNode* croot;
    try {
        croot = LoadNode(fin, root);
    }
    catch (int err) {
        return nullptr;
    }
    if (croot == nullptr) {
        try {
            croot = new(TRBNode);
        } 
        catch (std::bad_alloc()) {
            return nullptr;
        }

        if(croot->Key == nullptr) {
            delete croot;
            return nullptr;
        }

        croot->Key = strcpy(croot->Key,"");
        croot->Value = 0;
        croot->Colour = BLACK;
        croot->Parent = root;
        croot->Left = nullptr;
        croot->Right = nullptr;
        return croot;
    }

    croot->Left = LoadTree(fin, croot);
    croot->Right = LoadTree(fin, croot);

    if(croot->Left == nullptr || croot->Right == nullptr) {

        if(croot->Left != nullptr) {
            DestroyTree(croot->Left);
            croot->Left = nullptr;
        }

        if(croot->Right != nullptr) {
            DestroyTree(croot->Right);
            croot->Right = nullptr;
        }

        delete croot;
        return nullptr;
    }

    return croot;
}

int SaveNode(std::ofstream& fout, TRBNode* ldb) {
    try {
        int size = strlen(ldb->Key);
        fout.write((char*)&size, sizeof(size));
        fout.write(ldb->Key, size);
        fout.write((char*)&ldb->Value, sizeof(unsigned long long));
        fout.write(&ldb->Colour, 1);
    }
    catch (std::ios_base::failure& fail) {
        return -1;
    }

    return 0;
}

int SaveTree(std::ofstream& fout, TRBNode* root) {
    if (root == nullptr) {
        return 0;
    }
    if (SaveNode(fout, root) != 0) {
        return -1;
    }
    if (root->Left != nullptr) {
        if (SaveTree(fout, root->Left) != 0) {
            return -1;
        }
    }
    if (root->Right != nullptr) {
        if (SaveTree(fout, root->Right) != 0) {
            return -1;
        }
    }

    return 0;
}