#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H


#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
#include<vector>

using namespace std;

const string tab = "\t";

class SymbolInfo{

public:

    string name,type;
    SymbolInfo* nextSymbol = nullptr;

    int line_count = -1;
    string dataType;

    bool isFunction = false;
    bool isFunctionDeclared = false;
    bool returnFlag = false;

    vector<string>params;

    bool isGlobal = false;
    int stackPos = 0;
    int arraySize = -1;
    int numLocalVar = 0;
    bool isParam = false;

    SymbolInfo(string name,string type,int line_count){
        this->name = name;
        this->type = type;
        this->line_count = line_count;
    }

    SymbolInfo(){}

    string getName(){ return name; }
    string getType(){ return type; }
    int getLine_count(){ return line_count; }
    SymbolInfo* getNextSymbol(){ return nextSymbol; }

    void setName(string name){ this->name = name; }
    void setType(string type){ this->type = type; }
    void setNextSymbol(SymbolInfo* next){ nextSymbol = next; };

    void print(){
        if(isFunction)
            cout << "<" << name << "," << " FUNCTION, " << dataType << ">" ;
        else 
            cout << "<" << name << ", " << dataType << ">" ; 
    }

    void printToFile(ofstream& out){
        if(isFunction)
            out << "<" << name << "," << " FUNCTION, " << dataType << "> " ;
        else if(dataType == "INT_ARRAY"){
            out << "<" << name << "," << " ARRAY, " << "INT" << "> " ;
        }else if(dataType == "FLOAT_ARRAY"){
            out << "<" << name << "," << " ARRAY, " << "FLOAT" << "> " ;
        }
        else 
            out << "<" << name << ", " << dataType << "> " ; 
    }

};

class ScopeTable{

    int id,NumOfBuckets;
    SymbolInfo** buckets;

    ScopeTable* parent_scope;

    unsigned long long SDBMHash(string str) {
        unsigned long long hash = 0;
        unsigned int i = 0;
        unsigned int len = str.length();

        for (i = 0; i < len; i++)
        {
            hash = ( (str[i]) % NumOfBuckets + (hash << 6) % NumOfBuckets + (hash << 16) % NumOfBuckets - hash % NumOfBuckets ) % NumOfBuckets;
        }

        return hash;
    }

    int hashFunc(string name){
        return SDBMHash(name)%NumOfBuckets;
    }
    int deleted = 0;
    void deleteBucket(int indx){
        SymbolInfo* curr = buckets[indx],*temp = nullptr;

        while( curr != nullptr ){
            temp = curr;
            curr = curr->getNextSymbol();
            delete temp;
            deleted++;
        }

    }

public:

    ScopeTable(int n){
        NumOfBuckets = n;
        buckets = new SymbolInfo*[n];
        parent_scope = nullptr;

        for( int i = 0;i < NumOfBuckets;i++ )
            buckets[i] = nullptr;
    }


    ~ScopeTable(){

        for( int i = 0;i < NumOfBuckets;i++ ){
            deleteBucket(i);
        }

        delete []buckets;
        //cout << "=================" << deleted << endl;
    }

    ScopeTable* getParentScope(){ return parent_scope; }
    void setParentScope(ScopeTable* parent_scope){ this->parent_scope = parent_scope; }

    bool insertThis(){
        return true;
    }

    bool insertSymbol(string name,string type){
        int indx = hashFunc(name);

        SymbolInfo* si = new SymbolInfo;
        si->setName(name);
        si->setType(type);

        int pos_j = 1;

        if( buckets[indx] == nullptr ){
            buckets[indx] = si;
            cout << tab << "Inserted in ScopeTable# " << id << " at position " << indx + 1 << ", " << pos_j << "\n";
            return true;
        }
        //cout << "here" << "\n";
        SymbolInfo* curr = buckets[indx],*next = curr->getNextSymbol();

        while(1){

            if( name == curr->getName() ){
                delete si;
                cout << tab << "'" << name << "' already exists in the current ScopeTable\n";
                return false;
            }

            pos_j++;
            if( next == nullptr )
                break;

            curr = next;
            next = next->getNextSymbol();

        }

        curr->setNextSymbol(si);
        cout << tab << "Inserted in ScopeTable# " << id << " at position " << indx + 1 << ", " << pos_j << "\n";

        return true;

    }

    bool insertSymbol(SymbolInfo symbolInfo){
        int indx = hashFunc(symbolInfo.name);

        SymbolInfo* si = new SymbolInfo;
        si->setName(symbolInfo.name);
        si->setType(symbolInfo.type);
        si->dataType = symbolInfo.dataType;
        si->isFunction = symbolInfo.isFunction;
        si->isFunctionDeclared = symbolInfo.isFunctionDeclared;
        si->params = symbolInfo.params;
        si->line_count = symbolInfo.line_count;
        si->returnFlag = symbolInfo.returnFlag;
        si->isGlobal = symbolInfo.isGlobal;
        si->stackPos = symbolInfo.stackPos;
        si->arraySize = symbolInfo.arraySize;
        si->numLocalVar = symbolInfo.numLocalVar;
        si->isParam = symbolInfo.isParam;

        int pos_j = 1;

        if( buckets[indx] == nullptr ){
            buckets[indx] = si;
            cout << tab << "Inserted in ScopeTable# " << id << " at position " << indx + 1 << ", " << pos_j << "\n";
            return true;
        }
        //cout << "here" << "\n";
        SymbolInfo* curr = buckets[indx],*next = curr->getNextSymbol();

        while(1){

            if( symbolInfo.name == curr->getName() ){
                delete si;
                cout << tab << "'" << symbolInfo.name << "' already exists in the current ScopeTable\n";
                return false;
            }

            pos_j++;
            if( next == nullptr )
                break;

            curr = next;
            next = next->getNextSymbol();

        }

        curr->setNextSymbol(si);
        cout << tab << "Inserted in ScopeTable# " << id << " at position " << indx + 1 << ", " << pos_j << "\n";

        return true;

    }


    SymbolInfo* lookUpSymbol(string name){

        int indx = hashFunc(name),pos_j = 1;
        SymbolInfo* curr = buckets[indx];


        while( curr != nullptr ){
            if( name == curr->getName() ){
                cout << tab << "'" << name << "' found in ScopeTable# " << id << " at position " << indx+1 << ", " << pos_j << "\n";
                break;
            }

            curr = curr->getNextSymbol();
            pos_j++;
        }

        return curr;

    }



    bool deleteSymbol(string name){

        SymbolInfo* prev ,*curr;
        int indx = hashFunc(name),pos_j = 1;
        prev = curr = buckets[indx];

        if( curr == nullptr ){
            cout << tab << "Not found in the current ScopeTable\n";
            return false;
        }

        if( name == curr->getName() ){
            buckets[indx] = curr->getNextSymbol();
            delete curr;
            cout << tab << "Deleted '" << name << "' from ScopeTable# " << id << " at position " << indx+1 << ", " << pos_j << "\n";
            return true;
        }

        ++pos_j;
        curr = curr->getNextSymbol();

        while( curr != nullptr ){

            if( name == curr->getName()  ){
                cout << tab << "Deleted '" << name << "' from ScopeTable# " << id << " at position " << indx+1 << ", " << pos_j << "\n";
                prev->setNextSymbol(curr->getNextSymbol());
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->getNextSymbol();
            pos_j++;
        }

        cout << tab << "Not found in the current ScopeTable\n";
        return false;

    }

    void print(){

        cout << tab << "ScopeTable# " << id << "\n";

        for( int i = 0;i < NumOfBuckets;i++ ){
            cout << tab;
            cout << i + 1 << "--> ";

            SymbolInfo* si = buckets[i];
            while( si != nullptr ){
                si->print();
                si = si->getNextSymbol();
                cout << " ";
            }

            cout << "\n";
        }


    }

    void printToFile(ofstream& out){

        out << tab << "ScopeTable# " << id << "\n";

        for( int i = 0;i < NumOfBuckets;i++ ){
            SymbolInfo* si = buckets[i];

            if( si == nullptr )
                continue;

            out << tab;
            out << i + 1 << "--> ";

            while( si != nullptr ){
                si->printToFile(out);
                si = si->getNextSymbol();
            }

            out << "\n";
        }


    }

    int getId(){ return id; }
    void setId(int id){ this->id = id; }

};


class SymbolTable{

    ScopeTable* currScopeTable;
    int bucketSize,NumOfScopeTables = 0;

public:

    SymbolTable(int bucketSize){
        this->bucketSize = bucketSize;
        currScopeTable = nullptr;
        enterScope();
    }

    ~SymbolTable(){
        ScopeTable* par = nullptr;
        while( currScopeTable != nullptr ){
            par = currScopeTable->getParentScope();
            cout << tab << "ScopeTable# " << currScopeTable->getId() << " removed\n" ;
            delete currScopeTable;
            currScopeTable = par;
        }

    }

    void enterScope(){
        ScopeTable* newScope = new ScopeTable(bucketSize);
        newScope->setId(++NumOfScopeTables);
        newScope->setParentScope(currScopeTable);
        currScopeTable = newScope;

        cout << tab << "ScopeTable# " << NumOfScopeTables << " created\n" ;
    }

    void exitScope(){
        ScopeTable* parentScope = currScopeTable->getParentScope();

        if( parentScope == nullptr ){
            cout << tab << "ScopeTable# " << currScopeTable->getId() << " cannot be removed\n" ;
            return;
        }

        cout << tab << "ScopeTable# " << currScopeTable->getId() << " removed\n" ;
        delete currScopeTable;
        currScopeTable = parentScope;

    }

    bool insertSymbol(string name,string type){
        if( currScopeTable == nullptr )
            return false;

        return currScopeTable->insertSymbol(name,type);
    }

    bool insertSymbol(SymbolInfo si){
        if( currScopeTable == nullptr )
            return false;

        return currScopeTable->insertSymbol(si);
    }

    bool removeSymbol(string name){
        if( currScopeTable == nullptr )
            return false;

        return currScopeTable->deleteSymbol(name);
    }

    SymbolInfo* lookUpSymbol(string name){

        ScopeTable* temp = currScopeTable;

        while(temp != nullptr){
            SymbolInfo* si = temp->lookUpSymbol(name);

            if( si != nullptr ){
                return si;
            }

            temp = temp->getParentScope();
        }

        cout << tab << "'" << name << "' not found in any of the ScopeTables\n";
        return nullptr;
    }

    void printCurrScopeTable(){
        if( currScopeTable == nullptr )
            return ;

        currScopeTable->print();
    }

    void printAllScopeTable(){

        ScopeTable* temp = currScopeTable;

        while(temp != nullptr){

            temp->print();

            temp = temp->getParentScope();
        }
    }

    int getCurrScopeTableId(){
        if( currScopeTable == nullptr )
            return -1;

        return currScopeTable->getId();

    }

    void printAll(ofstream& out){
        ScopeTable* temp = currScopeTable;

        while(temp != nullptr){

            temp->printToFile(out);

            temp = temp->getParentScope();
        }
    }

};


#endif