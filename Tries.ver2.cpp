//Based on http://practice.geeksforgeeks.org/problems/trie-insert-and-search/0
//to solve the https://www.hackerrank.com/challenges/ctci-contacts
//IMPLIMENTATION OF TRIE DATA STRUCTURE
//Slower but smaller storage required

#include <iostream>
#include<string>
#include<queue>

#define ALPHABET_NO (26) //Number of characters in the English alphabet
#define ALPHABET_INDEX(c) ((int)c - (int)'a') //find the position of a character in the alphabet
using namespace std;

struct trieNode{
    struct trieNode *children[ALPHABET_NO]; //dynamic array of children for each node
    bool isLeaf;
};

struct trieNode* newNode(){
    struct trieNode*newNode = new trieNode;
    if(newNode){
        newNode -> isLeaf = false;
        for (int i = 0; i <ALPHABET_NO; i++){
            newNode->children[i] = nullptr;
        }
    }
    return newNode;
};


void insertNode(struct trieNode* root, string s){
    int n = s.size();

    struct trieNode* cur = root;

    for (int i = 0; i < n; i++){
        int j = ALPHABET_INDEX(s[i]); //index of the character in the alphabet --> look up that on the array of children in cur node
        if(!cur->children[j]){
            cur->children[j] = newNode();};
        cur = cur->children[j];
    };
    cur->isLeaf = true; // at the end of the word, mark the leaf node
}

int partial_search(struct trieNode*root, string s){
    int Count = 0;
    int n = s.size();

    struct trieNode*cur = root;

    for (int i =0; i <n; i ++){
        int j = ALPHABET_INDEX(s[i]); //index of the character in the alphabet --> look up that on the array of children in cur node
        if(!cur->children[j]) return Count; // if in the middle of the string, we cannot find children --> no word
        else cur = cur->children[j];
    };

    // count the complete words
    queue<struct trieNode*> q;
    q.push(cur);
    while(!q.empty()){
        cur = q.front();
        if (cur-> isLeaf) Count++;

        for (int i = 0; i < ALPHABET_NO; i ++){
            if(cur->children[i]) q.push(cur->children[i]);
        }//end for

        q.pop(); // remove the processed node

    }//end while

    return Count;
}

//ignore the main part, it is just the user interface
int main(){
    int n;
    cin >> n;
    struct trieNode* Contact_book = newNode();
    for(int a0 = 0; a0 < n; a0++){
        string op;
        string contact;
        cin >> op >> contact;
        if (op == "add") insertNode(Contact_book, contact);
        else if (op == "find") cout << partial_search(Contact_book, contact)<<endl;
    }
    return 0;
}
