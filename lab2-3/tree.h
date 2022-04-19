#pragma once
#include "node.h"

class TRBTree {
private:
    TRBNode* root = nullptr;
public:
    TRBTree () :
        root{nullptr}
    {}

    ~TRBTree () {
        DestroyTree(root);
    }

    TRBNode* Root() {
        return root;
    }

    int Insert(char* key, unsigned long long& value) {
        if (key == nullptr ) {
            return -3;
        }

        if (root == nullptr) {
            try {
                root = new(TRBNode);
            }
            catch(std::bad_alloc()) {
                root = nullptr; 
                return -1;
            }

            if (root->Key == nullptr) {
                root = nullptr; 
                return -1;
            }

            root->Left = nullptr;
            root->Right = nullptr;
            root->Parent = nullptr;
            root->Value = value;
            root->Key = strcpy(root->Key, key);
            root->Colour = BLACK;

            try {
                root->Right = new(TRBNode);
            }
            catch (std::bad_alloc()) {
                delete root;
                root = nullptr; 
                return -1;
            }
            
            try {
                root->Left = new(TRBNode);
            }
            catch (std::bad_alloc()) {
                delete root->Right;
                delete root;
                root = nullptr; 
                return -1;
            }

            if ((root->Left->Key == nullptr) || (root->Right->Key == nullptr)) {
                delete root->Right;
                delete root->Left;
                delete root;
                root = nullptr; 
                return -1;
            }

            root->Right->Parent = root;
            root->Left->Parent = root;
        }
        else {
            TRBNode* last = nullptr;
            TRBNode* cur = root;
            while (!cur->Islist()) {
                if(cur->Key == nullptr) {
                    return -4;
                }

                if (strequal(key, cur->Key) == 0) {
                    return -7;
                }
                if (strequal(key, cur->Key) > 0) {
                    last = cur;
                    cur = cur->Right;
                }
                else
                if (strequal(key, cur->Key) < 0) {
                    last = cur;
                    cur = cur->Left;
                }
            }
            cur->Parent = last; 
            cur->Key = strcpy(cur->Key,key);
            cur->Value = value;
            cur->Colour = RED;

            try {    
                cur->Right = new TRBNode;
            }
            catch (std::bad_alloc()) {
                cur->Key = strcpy(cur->Key,"");
                cur->Value = 0;
                cur->Colour = BLACK;
                cur->Right = nullptr;
                cur->Left = nullptr;
                return -1;
            }

            try {    
                cur->Left = new TRBNode;
            }
            catch (std::bad_alloc()) {
                delete cur->Right;
                cur->Key = strcpy(cur->Key,"");
                cur->Value = 0;
                cur->Colour = BLACK;
                cur->Right = nullptr;
                cur->Left = nullptr;
                return -1;
            }

            if(cur->Right->Key == nullptr || cur->Left->Key == nullptr) {
                
                if(cur->Left != nullptr) {
                    delete cur->Left;
                }

                if(cur->Right != nullptr) {
                    delete cur->Right;
                }

                cur->Key = strcpy(cur->Key,"");
                cur->Value = 0;
                cur->Colour = BLACK;
                cur->Right = nullptr;
                cur->Left = nullptr;
                return -1;
            }

            cur->Right->Parent = cur;
            cur->Left->Parent = cur;

            root = ISreballance(cur,root);
        }

        return 0;
    }

    int Remove(char* inpkey) {
        if(inpkey == nullptr) {
            return -8;
        }
        TRBNode* cur = root;
        if (cur == nullptr) {
            return -8;
        }

        while (true) {
            if (cur->Key == nullptr) {
                return -1;
            }
            if (cur->Islist()) {
                return -8;
            }

            if (strequal(inpkey, cur->Key) == 0) {
                break;
            }
            else
            if (strequal(inpkey, cur->Key) > 0) {
                cur = cur->Right;
            }
            else
            if (strequal(inpkey, cur->Key) < 0) {
                cur = cur->Left;
            }
        }


        if (cur->Left->Islist() && cur->Right->Islist()) {
            if (cur == root) {
                root = nullptr;
                delete cur->Left;
                delete cur->Right;
                delete cur;

                return 0;
            }
            else if (cur->Colour == RED) {
                if (cur->Isleft()) {
                    cur->Left->Parent = cur->Parent;
                    cur->Parent->Left = cur->Left;
                }
                else {
                    cur->Left->Parent = cur->Parent;
                    cur->Parent->Right = cur->Left;
                }
                delete cur->Right;
                delete cur;
            }
            else {
                if (cur->Isleft()) {
                    if(cur->Parent!=nullptr)
                        cur->Parent->Left = cur->Left;

                    cur->Left->Parent = cur->Parent;
                    TRBNode* start = cur->Left;
                    delete cur->Right;
                    delete cur;
                    root = RMreballance(start, root);
                }
                else {
                    if (cur->Parent != nullptr)
                        cur->Parent->Right = cur->Left;

                    cur->Left->Parent = cur->Parent;
                    TRBNode* start = cur->Left;
                    delete cur->Right;
                    delete cur;
                    root = RMreballance(start, root);
                }
            }
        }
        else
        if (cur->Left->Islist()) {

            if (cur == root) {
                root = cur->Right;
                root->Colour = BLACK;
                root->Parent = nullptr;
                delete cur->Left;
                delete cur;

                return 0;
            }

            if (cur->Colour == RED) {
                if (cur->Isleft()) {
                    cur->Right->Parent = cur->Parent;
                    cur->Parent->Left = cur->Right;
                }
                else {
                    cur->Right->Parent = cur->Parent;
                    cur->Parent->Right = cur->Right;
                }
                delete cur->Left;
                delete cur;
            }
            else {
                if (cur->Right->Colour == RED) {
                    if (cur->Isleft()) {
                        cur->Right->Parent = cur->Parent;
                        cur->Right->Colour = BLACK;
                        cur->Parent->Left = cur->Right;
                    }
                    else {
                        cur->Right->Parent = cur->Parent;
                        cur->Right->Colour = BLACK;
                        cur->Parent->Right = cur->Right;
                    }
                    delete cur->Left;
                    delete cur;
                }
                else {
                    return -2;
                }
            }
        }
        else
        if (cur->Right->Islist()) {

            if (cur == root) {
                root = cur->Left;
                root->Colour = BLACK;
                root->Parent = nullptr;
                delete cur->Right;
                delete cur;

                return 0;
            }

            if (cur->Colour == RED) {
                if (cur->Isleft()) {
                    cur->Left->Parent = cur->Parent;
                    cur->Parent->Left = cur->Left;
                }
                else {
                    cur->Left->Parent = cur->Parent;
                    cur->Parent->Right = cur->Left;
                }
                delete cur->Right;
                delete cur;
            }
            else {
                if (cur->Left->Colour == RED) {
                    if (cur->Isleft()) {
                        cur->Left->Parent = cur->Parent;
                        cur->Left->Colour = BLACK;
                        cur->Parent->Left = cur->Left;
                    }
                    else {
                        cur->Left->Parent = cur->Parent;
                        cur->Left->Colour = BLACK;
                        cur->Parent->Right = cur->Left;
                    }
                    delete cur->Right;
                    delete cur;
                }
                else {
                    return -2;
                }
            }
        }
        else {
            TRBNode* cnb = cur->Right;
            while (!cnb->Left->Islist()) {
                cnb = cnb->Left;
            }
            
            try {
                Swap(cur, cnb);
            }
            catch (int err) {
                return -1;
            }
            cur = cnb;
            if (cur->Left->Islist() && cur->Right->Islist()) {
                if (cur == root) {
                    root = nullptr;
                    delete cur->Left;
                    delete cur->Right;
                    delete cur;

                    return 0;
                }
                else
                if (cur->Colour == RED) {
                    if (cur->Isleft()) {
                        cur->Left->Parent = cur->Parent;
                        cur->Parent->Left = cur->Left;
                    }
                    else {
                        cur->Left->Parent = cur->Parent;
                        cur->Parent->Right = cur->Left;
                    }
                    delete cur->Right;
                    delete cur;
                }
                else {
                    if (cur->Isleft()) {
                        if(cur->Parent!=nullptr)
                            cur->Parent->Left = cur->Left;

                        cur->Left->Parent = cur->Parent;
                        TRBNode* start = cur->Left;
                        delete cur->Right;
                        delete cur;
                        root = RMreballance(start, root);
                    }
                    else {
                        if (cur->Parent != nullptr)
                            cur->Parent->Right = cur->Left;

                        cur->Left->Parent = cur->Parent;
                        TRBNode* start = cur->Left;
                        delete cur->Right;
                        delete cur;
                        root = RMreballance(start, root);
                    }
                }
            }
            else
            if (cur->Left->Islist()) {

                if (cur == root) {
                    root = cur->Right;
                    root->Colour = BLACK;
                    root->Parent = nullptr;
                    delete cur->Left;
                    delete cur;

                    return 0;
                }

                if (cur->Colour == RED) {
                    if (cur->Isleft()) {
                        cur->Right->Parent = cur->Parent;
                        cur->Parent->Left = cur->Right;
                    }
                    else {
                        cur->Right->Parent = cur->Parent;
                        cur->Parent->Right = cur->Right;
                    }
                    delete cur->Left;
                    delete cur;
                }
                else {
                    if (cur->Right->Colour == RED) {
                        if (cur->Isleft()) {
                            cur->Right->Parent = cur->Parent;
                            cur->Right->Colour = BLACK;
                            cur->Parent->Left = cur->Right;
                        }
                        else {
                            cur->Right->Parent = cur->Parent;
                            cur->Right->Colour = BLACK;
                            cur->Parent->Right = cur->Right;
                        }
                        delete cur->Left;
                        delete cur;
                    }
                    else {
                        return -2;
                    }
                }
            }
            else
            if (cur->Right->Islist()) {

                if (cur == root) {
                    root = cur->Left;
                    root->Colour = BLACK;
                    root->Parent = nullptr;
                    delete cur->Right;
                    delete cur;

                    return 0;
                }

                if (cur->Colour == RED) {
                    if (cur->Isleft()) {
                        cur->Left->Parent = cur->Parent;
                        cur->Parent->Left = cur->Left;
                    }
                    else {
                        cur->Left->Parent = cur->Parent;
                        cur->Parent->Right = cur->Left;
                    }
                    delete cur->Right;
                    delete cur;
                }
                else {
                    if (cur->Left->Colour == RED) {
                        if (cur->Isleft()) {
                            cur->Left->Parent = cur->Parent;
                            cur->Left->Colour = BLACK;
                            cur->Parent->Left = cur->Left;
                        }
                        else {
                            cur->Left->Parent = cur->Parent;
                            cur->Left->Colour = BLACK;
                            cur->Parent->Right = cur->Left;
                        }
                        delete cur->Right;
                        delete cur;
                    }
                    else {
                        return -2;
                    }
                }
            }

        }

        return 0;
    }

    void Print() {
        Tree_print(root,0);
    }

    TRBNode* Search(char* inpkey) {
        if (inpkey == nullptr) {
            return nullptr;
        }
        TRBNode* cur = root; 
        if (cur == nullptr) {
            return nullptr;
        }

        while (true) {
            if (cur->Right == nullptr || cur->Left == nullptr) {
                return nullptr;
            }
            if (cur->Key == nullptr) {
                return nullptr;
            }

            if (strequal(inpkey, cur->Key) == 0) {
                break;
            }
            else
            if (strequal(inpkey, cur->Key) > 0) {
                cur = cur->Right;
            }
            else
            if (strequal(inpkey, cur->Key) < 0) {
                cur = cur->Left;
            }
        }

        return cur;
    }

    int SaveToDisk(const std::string& path) {
        try {
            std::ofstream fout;
            fout.open(path, std::ios::binary | std::ios::out);

            if(!fout.is_open()) {
                return -1;
            }

            char mark[3] = { 'r','b','t' };
            fout.write((char*)&mark[0], sizeof(char) * 3);

            if (SaveTree(fout, root) != 0) {
                fout.close();
                return -2;
            }
            fout.close();
        }
        catch (std::ios_base::failure& fail) {
            return -3;
        }

        return 0;
    }

    int LoadFromDisk(const std::string& path) {
        char mark[4];
        std::ifstream fin;
        try {
            fin = std::ifstream(path, std::ios::binary | std::ios::in);
            if(!fin.is_open()) {
                return -3;
            }
            fin.read((char*)mark, sizeof(char) * 3);
        }
        catch (std::ios_base::failure& fail) {
            fin.close();
            return -3;
        }

        if (!(mark[0] == 'r' && mark[1] == 'b' && mark[2] == 't')) {
            fin.close();
            return -2;
        }

        TRBNode *NewRoot = nullptr;
        NewRoot = LoadTree(fin, NewRoot);
        if (NewRoot != nullptr) {

            fin.close();
            DestroyTree(root);
            root = NewRoot;
            return 0;
        }

        DestroyTree(NewRoot);
        fin.close();
        return -1;
    }

    void Destroy() {
        DestroyTree(root);
        root = nullptr;
    }
};