//Based on http://practice.geeksforgeeks.org/problems/trie-insert-and-search/0
//to solve the https://www.hackerrank.com/challenges/ctci-contacts
//IMPLIMENTATION OF TRIE DATA STRUCTURE to find a partial word in a list
//Faster version but larger storage required

#include <iostream>
#include<string>
#include<queue>

#define ALPHABET_NO (26) //Number of characters in the English alphabet
#define ALPHABET_INDEX(c) ((int)c - (int)'a') //find the position of a character in the alphabet
using namespace std;

struct trieNode{
    struct trieNode *children[ALPHABET_NO]; //dynamic array of children for each node
    int no_words;//number of complete words
};

struct trieNode* newNode(){
    struct trieNode*newNode = new trieNode;
    if(newNode){
        newNode -> no_words = 0;
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
        cur->no_words++;
    };
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
    return cur->no_words;
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
