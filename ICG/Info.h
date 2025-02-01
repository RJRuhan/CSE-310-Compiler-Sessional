#ifndef INFO_H
#define INFO_H

#include<vector>
#include<list>
#include"1805017.h"




class Node{

public:

    int ruleNo;
    string head;
    string body;
    string text;
    list<Node*> children;
    int level = 0;

    Node(int ruleNo,string head,string body,string text ){
        this->ruleNo = ruleNo;
        this->head = head;
        this->body = body;
        this->text = text;
    }

    Node(){}
};




struct Info{

    int line_count = -1;
    Node* root = nullptr;
    string data;
    vector<SymbolInfo> symbols;
    vector<string> arguments;
    string server;
    string lexeme;
    string typeICG;
    bool errorFlag = false;
    string arrIndx ;
    string label = "-1";
    vector<int> trueList;
    vector<int> falseList;
    vector<int> nextList;
    bool isBooleanExp = false;
    bool isRelExp = false;
    bool isExp = false;
};

#endif 