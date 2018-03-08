// Coleman Lyski
// Data Structures
// Assignment 3
// 20 November 2017

#include <iostream>
#include <iomanip>

using namespace std;

template <class T>
struct Node {
    Node *left, *right;
    T val;
    Node() : left(), right() {}
};

template <class T>
class Tree {
private:
    int height;
    Node<T>* root;

    void pSert(Node<T>* new_node, Node<T>** curr){
        if(*curr == NULL){
            *curr = new_node;
            return;
        }
        // recursive insert to find empty node
        if(new_node->val < (*curr)->val){
            pSert(new_node, &(*curr)->left);
        } else {
            pSert(new_node, &(*curr)->right);
        }
    }

    void pSear(Node<T>* s_node, Node<T>** curr, int key){
        // Base Cases: root is null or key is present at root
        if(*curr == NULL){
            *curr = s_node;
            return;
        }
        // Key is greater than root's key
        if(s_node->val > (*curr)->val){
            return pSear(s_node, &(*curr)->right, key);
        } else {
            // Key is smaller than root's key
            return pSear(s_node, &(*curr)->left, key);
        }
    }

    void pIO(Node<T>* curr, int indent=0) {
        if(curr != NULL) {
            if(curr->right) {
                pIO(curr->right, indent+4);
            }

            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }

            if (curr->right){
                std::cout<<" /\n" << std::setw(indent) << ' ';
            }

            std::cout<< curr->val << "\n ";

            if(curr->left) {
                std::cout << std::setw(indent) << ' ' <<" \\\n";
                pIO(curr->left, indent+4);
            }
        }

        /*
        if(curr != NULL) {
            if(curr->left) {
                pIO(curr->left, indent+4);
            }
            if(curr->right) {
                pIO(curr->right, indent+4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            cout<< curr->val << "\n ";
        }
         */
    }

    int pSize(Node<T>* curr){
        if (curr == NULL)
            return 0;
        else
            return(pSize(curr->left) + 1 + pSize(curr->right));
    }

    int pCount(Node<T>* curr){
        int c = 1;

        if (curr == NULL)
            return 0;
        else
        {
            c += pCount(curr->left);
            c += pCount(curr->right);
            return c;
        }
    }

    int pATA(Node<T>* curr, int &arr[], int i)
    {
        if(curr == NULL){
            return i;
        }

        arr[i] = curr->val;
        i++;
        if(curr->left != NULL)
            i = pATA(curr->left, arr, i);
        if(curr->right != NULL)
            i = pATA(curr->right, arr, i);

        return i;
    }


public:
    // Constructor
    Tree() : height(0), root() {}

    // In Order traversal of BST
    void inorder(){
        pIO(root);
    }

    // Insert Function
    void insert(T val){
        Node<T>* new_node = new Node<T>;
        new_node->val = val;
        pSert(new_node, &root);
    }

    // Search Function
    void search(T key){
        Node<T>* s_node = new Node<T>;
        s_node->val = key;
        pSear(s_node, &root, key);
    }

    // Number of entries in tree
    int size(){
        int count;
        count = pSize(root);
        return count;
    }

    int addToArray(int &arr[]){
        pATA(root, &arr[], 0);
    }


};

int main(){
    Tree<int> Tr;
    Tr.insert(2);
    Tr.insert(1);
    Tr.insert(3);
    Tr.insert(7);
    Tr.insert(10);
    Tr.insert(2);
    Tr.insert(5);
    Tr.insert(8);
    Tr.insert(6);
    Tr.insert(4);
    Tr.insert(69);

    Tr.inorder();

    cout << endl << "Size: " << Tr.size() << endl;

    int size = Tr.size();
    int arr[size] = {};
    cout << endl << "Array: " << Tr.addToArray(arr) << endl;

    getchar();
    getchar();
}