/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "1805017.y"

#include<bits/stdc++.h>
#include "1805017.h"
#include"Info.h"


using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;

ofstream logout;
ofstream errorOut;
ofstream parseTreeOut;
ofstream asmOut;
ofstream tempAsmOut;
ofstream OptAsmOut;
ifstream tempInputFile;
ifstream asmInput;


extern int line_count;
extern int err_count;

int bucketSize = 11;
SymbolTable *st = new SymbolTable(bucketSize);

Node* parseTree = nullptr;

SymbolInfo currFunc;
vector<SymbolInfo> parameterList;

vector<string> globalVarDeclCodes;

int asmLabel = 0;

Info* expNow = nullptr;

void preTraversal(Node* root){

    string blanks;
    if( root != nullptr ){
        int level = root->level;

        while( level > 0 ){
            blanks += " ";
            level--;
        }



        parseTreeOut << blanks + root->text;

        for( Node* t : root->children ){
            if( t != nullptr )
                t->level = root->level + 1;
            preTraversal(t);
        }
    }

}

void deleteParseTree(Node* root){
    if( root != nullptr ){
        for( Node* t : root->children ){
            if( t != nullptr )
                t->level = root->level + 1;
            deleteParseTree(t);
        }

        delete root;
    }
}

void yyerror(string s)
{
}

void freeMemory(){

    if( st != nullptr )
        delete st;

    deleteParseTree(parseTree);

}

void multipleFunctionDeclarationError(SymbolInfo* si){

    errorOut << "Line# " << si->line_count << ": Multiple declaration of function"<< si->name <<"\n";
    err_count++;

}

void multipleFunctionDefinitionError(SymbolInfo* si){
    errorOut << "Line# " << si->line_count << ": '" << si->name << "' redeclared as different kind of symbol\n";
    err_count++;

}

void printSyntaxError(string body,string head,int lc){
    logout << "Error at line no " << lc << " : syntax error\n";
    errorOut << "Line# " << to_string(lc) << ": Syntax error at "<< body << " of " << head <<"\n";
    err_count++;
}

void parameterNameMissingErrorFuncDef(string funcID,int paramNo,int lc){
    errorOut << "Line# " << to_string(lc) << ": Parameter Name missing of "<< paramNo << "th parameter of function definition of " << funcID << "\n";
    err_count++;
}

void returnTypeConflictErrorFuncDef(string funcID,int lc){
    funcID = "'" + funcID + "'";
    errorOut << "Line# " << to_string(lc) << ": Conflicting types for " << funcID << "\n";
    err_count++;
}

void NumberOfParametersMismatchErrorFuncDef(string funcID,int lc){
    funcID = "'" + funcID + "'";
    errorOut << "Line# " << to_string(lc) << ": Conflicting types for " << funcID << "\n";
    err_count++;
}

void parameterTypeMismatchErrorFuncDef(string funcID,int paramNo,int lc){
    errorOut << "Line# " << to_string(lc) << ": Parameter type mismatch of "<< paramNo << "th parameter of function definition of " << funcID << "\n";
    err_count++;
}

void duplicateParameterNameError(string varID,int lc){
    errorOut << "Line# " << to_string(lc) << ": Redefinition of parameter '" << varID << "'\n";
    err_count++;
}

void ArraySizeFloatError(int lc){
    errorOut << "Line# " << lc << ": array size is float" << "\n";
    err_count++;
}

void dataTypeError(string varID,int lc){
    varID = "'" + varID + "'";
    errorOut << "Line# " << lc << ": Variable or field " << varID << " declared void\n";
    err_count++;
}

void multipleVarDeclarationError(string varID,int lc){
    varID = "'" + varID + "'";
    errorOut << "Line# " << to_string(lc) << ": Conflicting types for " << varID << "\n";
    err_count++;
}

void nestedFunctionError(int lc){
    errorOut << "Line# " << to_string(lc) << ": nested function\n";
    err_count++;
}

void undeclaredVariableError(string varID,int lc){
    varID = "'" + varID + "'";
    errorOut << "Line# " << to_string(lc) << ": Undeclared variable " << varID << "\n";
    err_count++;
}

void undeclaredFunctionError(string funcID,int lc){
    funcID = "'" + funcID + "'";
    errorOut << "Line# " << to_string(lc) << ": Undeclared function " << funcID << "\n";
    err_count++;
}

void isNotArrayError(string varID,int lc){
    varID = "'" + varID + "'";
    errorOut << "Line# " << to_string(lc) << ": " << varID << " is not an array\n";
    err_count++;
}

void invalidArrayIndexError(int lc){
    errorOut << "Line# " << to_string(lc) << ": Array subscript is not an integer\n";
    err_count++;    
}

void isArrayError(string varID,int lc){
    //errorOut << "Line# " << to_string(lc) << ": variable " << varID << " is an array\n";
    //err_count++;
}


void typeMismatchError(int lc){
    errorOut << "Line# " << to_string(lc) << ": type mismatch\n";
    err_count++;
}

void voidTypeAssignError(int lc){
    errorOut << "Line# " << to_string(lc) << ": Void cannot be used in expression \n";
    err_count++;
}

void voidTypecastError(int lc){
    errorOut << "Line# " << to_string(lc) << ": Void cannot be used in expression \n";
    err_count++;
}

void typecastError(int lc){
    errorOut << "Line# " << to_string(lc) << ": Incompatible Operand\n";
    err_count++;
}

void isNotFunctionError(string funcID,int lc){
    errorOut << "Line# " << to_string(lc) << ": " << funcID  << "is not a function" << "\n";
    err_count++;
}

void undefinedFunctionError(string funcID,int lc){
    errorOut << "Line# " << to_string(lc) << ": " << funcID  << "is not defined" << "\n";
    err_count++;
}

void NumberOfArgumentsMismatchErrorFunc(string funcID,int lc,bool tooFew){
    funcID = "'" + funcID + "'";
    if(tooFew)
        errorOut << "Line# " << to_string(lc) << ": Too few arguments to function " << funcID << "\n";
    else
        errorOut << "Line# " << to_string(lc) << ": Too many arguments to function " << funcID << "\n";

    err_count++;
}

void argumentTypeCastError(string funcID,int argNo,int lc){
    funcID = "'" + funcID + "'";
    errorOut << "Line# " << to_string(lc) << ": Type mismatch for argument " << argNo << " of " << funcID << "\n";
    err_count++;
}

void typecastModError(int lc){
    errorOut << "Line# " << to_string(lc) << ": Operands of modulus must be integers \n";
    err_count++;
}

void divideByZeroError(int lc){
    errorOut << "Line# " << to_string(lc) << ": Warning: division by zero i=0f=1Const=0\n";
    err_count++;
}

void assignmentOfFloattoIntWarning(int lc){
    errorOut << "Line# " << to_string(lc) << ": Warning: possible loss of data in assignment of FLOAT to INT\n";
    err_count++;
}

void returnFloatWarning(int lc){
    errorOut << "Line# " << to_string(lc) << ": Warning: possible loss of data in returning FLOAT from a function with return type of int\n";
    err_count++;
}

void returnError(int lc){
    errorOut << "Line# " << to_string(lc) << ": return statement with a value,in function returning 'void'\n";
    err_count++;
}

void noReturnError(int lc){
    errorOut << "Line# " << to_string(lc) << ": no return statement in function returning non-void\n";
    err_count++;
}

void verifyAssignop(Info* info,Info* info1,Info* info2){

    string leftOperand = info1->server,rightOperand = info2->server;

    if( leftOperand == "UNDEFINED" || rightOperand == "UNDEFINED" ){
        info->server = "UNDEFINED";
        return;
    }
    if( ( leftOperand == "INT" || leftOperand == "INT_ARRAY" ) && ( rightOperand == "INT" || rightOperand == "INT_ARRAY" ) ){
        info->server = "INT";
        return;
    }

    if( ( leftOperand == "INT" || leftOperand == "INT_ARRAY" ) && ( rightOperand == "FLOAT" || rightOperand == "FLOAT_ARRAY" ) ){
        info->server = "INT";
        assignmentOfFloattoIntWarning(info2->line_count);
        return;
    }

    if(( leftOperand == "FLOAT" || leftOperand == "FLOAT_ARRAY" ) && ( rightOperand != "VOID" )){
        info->server = "FLOAT";
        return;
    }
        
    if( leftOperand == "VOID" || rightOperand == "VOID" )
        voidTypeAssignError(info1->line_count);
    else
        typeMismatchError(info2->line_count);

    info->server = "UNDEFINED";

}

void logicalTypecast(Info* info,Info* info1,Info* info2){
    string leftOperand = info1->server,rightOperand = info2->server;
    string result;

    if( leftOperand == "UNDEFINED" || rightOperand == "UNDEFINED" )
        info->server = "UNDEFINED";
    else if( leftOperand == "VOID" || rightOperand == "VOID" ){
        voidTypecastError(info1->line_count);
        info->server = "UNDEFINED";
    }
    else if( ( leftOperand == "INT" || leftOperand == "INT_ARRAY" ) && ( rightOperand == "INT" || rightOperand == "INT_ARRAY" ) )
        info->server = "INT";
    else if( ( leftOperand == "INT" || leftOperand == "INT_ARRAY" ) && ( rightOperand == "FLOAT" || rightOperand == "FLOAT_ARRAY" ) )
        info->server = "INT";
    else if( ( leftOperand == "FLOAT" || leftOperand == "FLOAT_ARRAY" ) && ( rightOperand == "INT" || rightOperand == "INT_ARRAY" ) )
        info->server = "INT";
    else if( ( leftOperand == "FLOAT" || leftOperand == "FLOAT_ARRAY" ) && ( rightOperand == "FLOAT" || rightOperand == "FLOAT_ARRAY" ) )
        info->server = "INT";
    else{
        typecastError(info1->line_count);
        info->server = "UNDEFINED";
    }
}

void arithmeticTypecast(Info* info,Info* info1,Info* info2){
    string leftOperand = info1->server,rightOperand = info2->server;
    string result;
    //cout << leftOperand << " " << rightOperand << endl;

    if( leftOperand == "UNDEFINED" || rightOperand == "UNDEFINED" )
        info->server = "UNDEFINED";
    else if( leftOperand == "VOID" || rightOperand == "VOID" ){
        voidTypecastError(info1->line_count);
        info->server = "UNDEFINED";
    }
    else if( ( leftOperand == "INT" || leftOperand == "INT_ARRAY" ) && ( rightOperand == "INT" || rightOperand == "INT_ARRAY" ) )
        info->server = "INT";
    else if( ( leftOperand == "INT" || leftOperand == "INT_ARRAY" ) && ( rightOperand == "FLOAT" || rightOperand == "FLOAT_ARRAY" ) )
        info->server = "FLOAT";
    else if( ( leftOperand == "FLOAT" || leftOperand == "FLOAT_ARRAY" ) && ( rightOperand == "INT" || rightOperand == "INT_ARRAY" ) )
        info->server = "FLOAT";
    else if( ( leftOperand == "FLOAT" || leftOperand == "FLOAT_ARRAY" ) && ( rightOperand == "FLOAT" || rightOperand == "FLOAT_ARRAY" ) )
        info->server = "FLOAT";
    else{
        typecastError(info1->line_count);
        info->server = "UNDEFINED";
    }
}

void modTypecast(Info* info,Info* info1,Info* info2){
    string leftOperand = info1->server,rightOperand = info2->server;
    string result;

    if( leftOperand == "UNDEFINED" || rightOperand == "UNDEFINED" )
        info->server = "UNDEFINED";
    else if( leftOperand == "VOID" || rightOperand == "VOID" ){
        voidTypecastError(info1->line_count);
        info->server = "UNDEFINED";
    }
    else if( ( leftOperand == "INT" || leftOperand == "INT_ARRAY" ) && ( rightOperand == "INT" || rightOperand == "INT_ARRAY" ) )
        info->server = "INT";
    else if( ( leftOperand == "FLOAT" || leftOperand == "FLOAT_ARRAY" ) || ( rightOperand == "FLOAT" || rightOperand == "FLOAT_ARRAY" ) ){
        typecastModError(info1->line_count);
        info->server = "UNDEFINED";
    }
    else{
        typecastError(info1->line_count);
        info->server = "UNDEFINED";
    }
}

bool argumentTypeCast(string argType,string paramType){
    if( argType == "UNDEFINED" ) return true;

    if( paramType == "VOID" && argType == "VOID" ) return true;
    if( ( paramType == "INT" || paramType == "INT_ARRAY" ) && ( argType == "INT" || argType == "INT_ARRAY" ) ) return true;
    if( ( paramType == "FLOAT" || paramType == "FLOAT_ARRAY" ) && ( argType == "FLOAT" || argType == "FLOAT_ARRAY" ) ) return true;
    
    return false;
}

void checkReturnType(Info* info){
    if( info->server == "UNDEFINED" )return;
    if( ( info->server == "INT" || info->server == "INT_ARRAY" ) && (currFunc.dataType == "INT" || currFunc.dataType == "FLOAT") ) return;
    if( ( info->server == "FLOAT" || info->server == "FLOAT_ARRAY" ) && (currFunc.dataType == "INT") ){
        returnFloatWarning(info->line_count);
        return;
    }
    if( ( info->server == "FLOAT" || info->server == "FLOAT_ARRAY" ) && (currFunc.dataType == "FLOAT") ) return;

    if( (info->server == "") && currFunc.dataType == "VOID" ) return;
        
    returnError(info->line_count);

}

void VarNameError(string varID,int lc){
    errorOut << "Line# " << to_string(lc) << ": '" << varID  << "' is reserved." << "\n";
    err_count++;
}



bool isFuncNow = false;

void insertFuncDefToSymbolTable(SymbolInfo* si,string dataType){

    si->isFunction = true;
    si->isFunctionDeclared = false;
    si->dataType = dataType;

    currFunc = *si;

    for(SymbolInfo s : parameterList){
        si->params.push_back(s.dataType);
    }

    if(!st->insertSymbol(*si)){

        SymbolInfo* prevFunc = st->lookUpSymbol(si->name);
        if( prevFunc->isFunctionDeclared == false ){
            multipleFunctionDefinitionError(si);
        }else{
            if( prevFunc->dataType != si->dataType ){
                returnTypeConflictErrorFuncDef(si->name,si->line_count);
            }

            if( prevFunc->params.size() != si->params.size() ){
                NumberOfParametersMismatchErrorFuncDef(si->name,si->line_count);
            }else{
                for(int i = 0;i < prevFunc->params.size();i++){
                    if( prevFunc->params[i] != si->params[i] ){
                        parameterTypeMismatchErrorFuncDef(si->name,i+1,si->line_count);
                        break;
                    }
                }            
            }

            prevFunc->isFunctionDeclared = false;
        }

    }else{
        SymbolInfo* func = st->lookUpSymbol(si->name);
        for(int i = 0;i < parameterList.size();i++){
            if(parameterList[i].name == "NO_IDENTIFIER_NAME"){
                parameterNameMissingErrorFuncDef(func->name,i+1,si->line_count);
            }
        }
    }

}



void printToLogRule(string head,string body){
    logout << head << " : " << body << " \n";
}

string getRuleString(string head,string body,int lc1,int lc2){
    string text = head + " : " + body ;

    if( lc2 == -1 ){
            text += "\t<Line: " + to_string(lc1) + ">\n";
    }else{
        text += " \t<Line: " + to_string(lc1) + "-" + to_string(lc2) + ">\n";
    }

    return text;
}

void insertTOKEN(Info* info,SymbolInfo* si){
    string text = getRuleString(si->getType(),si->getName(),si->line_count,-1);
    Node* terminal = new Node(100,si->getType(),si->getName(),text);

    info->root->children.push_back(terminal);

}


void enterNewScope(){
    st->enterScope();
    if(isFuncNow){
        int stackPos = parameterList.size()*2 + 2;
        for(SymbolInfo s : parameterList){
            if( s.name == "NO_IDENTIFIER_NAME" )
                continue;
            // cout << s.name << endl;
            s.isParam = true;
            s.stackPos = stackPos;
            if(!st->insertSymbol(s)){
                duplicateParameterNameError(s.name,s.line_count);
            }

            stackPos-=2;
        }
    }
}



unordered_map<int,string> labelMap;

void backPatch(vector<int> lines,string label){
    for(int i : lines){
        labelMap[i] = label;
    }
}

int tempAsmLineCount = 0;

void printLabel(int label){
    tempAsmOut << "L" << label << ":\n";
    tempAsmLineCount++;    
    // cout << tempAsmLineCount << endl;

}

void printCmd(string cmd){
    tempAsmOut << tab << cmd ;
    tempAsmLineCount++;
    // cout << tempAsmLineCount << endl;
}

void initFuncAsmCode(SymbolInfo* funcID){
    tempAsmOut << funcID->name << " PROC\n";tempAsmLineCount++;
    if( funcID->name == "main" ){
        printLabel(++asmLabel);
        printCmd("MOV AX, @DATA\n");
        printCmd("MOV DS, AX\n");
    }
    printLabel(++asmLabel);
    printCmd("PUSH BP\n");
    printCmd("MOV BP, SP\n");
    printLabel(++asmLabel);
}

void setupVarDeclCodes(string varName){
    SymbolInfo* si = st->lookUpSymbol(varName);
    if(si != nullptr){
        if(!isFuncNow){
            si->isGlobal = true;
            //cout << "******" << s.dataType << endl;
            if( si->dataType == "INT_ARRAY" ){
                // cout << "********" << s.arraySize << endl;
                string code = tab + varName + " DW " + to_string(si->arraySize) + " DUP (0)\n";
                globalVarDeclCodes.push_back(code);
            }else if( si->dataType == "INT" ){
                string code = tab + varName + " DW 1 DUP (0)\n";
                globalVarDeclCodes.push_back(code);
            }
            
        }else{
            if( si->dataType == "INT_ARRAY" ){

                printCmd("SUB SP, "+ to_string(2*si->arraySize)+"\n");
                si->stackPos = currFunc.stackPos + 2;
                currFunc.stackPos += 2*si->arraySize;


            }else if( si->dataType == "INT" ){
                //cout << "******" << s.dataType << endl;
                printCmd("SUB SP, 2\n");
                currFunc.stackPos += 2;
                si->stackPos = currFunc.stackPos;
            }
            
        }
    }
}

void loadVariablesCode(Info* var){
    if( var->lexeme != "NULL" ){
        if( var->typeICG == "CONST_INT" ){
            printCmd("MOV AX, " + var->lexeme + "\n");
        }else if( var->typeICG == "variable" ){
            SymbolInfo* si = st->lookUpSymbol(var->lexeme);
            if( si != nullptr ){
                if( si->isGlobal ){
                    printCmd("MOV AX, " + var->lexeme + "\n");
                }else{
                    if( si->isParam ){
                        printCmd("MOV AX, [BP+" + to_string(si->stackPos) + "]\n");                        
                    }else
                        printCmd("MOV AX, [BP-" + to_string(si->stackPos) + "]\n");
                }
            }
        }else if( var->typeICG == "INT_ARRAY" ){
            SymbolInfo* si = st->lookUpSymbol(var->lexeme);
            if( si != nullptr ){
                if( si->isGlobal ){
                    printCmd("POP SI\n");
                    printCmd("MOV AX, " + si->name +  "[SI]\n");
                }else{
                    printCmd("POP SI\n");
                    printCmd("MOV AX, SI\n");
                    printCmd("MOV CX, 2\n");
                    printCmd("CWD\n");
                    printCmd("MUL CX\n");
                    printCmd("MOV SI, AX\n");
                    printCmd("ADD SI, " + to_string(si->stackPos) + "\n");
                    printCmd("PUSH BP\n");
                    printCmd("SUB BP, SI\n");
                    printCmd("MOV AX, [BP]\n");
                    printCmd("POP BP\n");
                    
                
                }
            }      
            
            
            
        }

    }else{
        
        printCmd("POP AX\n");
    }
}

void loadAssignCode(Info* var){
    SymbolInfo* si = st->lookUpSymbol(var->lexeme);

    if(si != nullptr){
        if( var->typeICG == "variable" ){
            if( si->isGlobal ){
                printCmd("MOV " + si->name + ", AX\n");
            }else{
                // cout << si->name << " " << si->isParam << endl;
                if( si->isParam ){
                    printCmd("MOV [BP+" + to_string(si->stackPos) + "], AX\n");
                }else
                    printCmd("MOV [BP-" + to_string(si->stackPos) + "], AX\n");
            }
        }else if( var->typeICG == "INT_ARRAY" ) {
            if( si->isGlobal ){      
                printCmd("POP SI\n");              
                printCmd("MOV " + si->name + "[SI], AX\n");
            }else{
                printCmd("PUSH AX\n");
                printCmd("POP SI\n");
                printCmd("MOV AX, SI\n");
                printCmd("MOV CX, 2\n");
                printCmd("CWD\n");
                printCmd("MUL CX\n");
                printCmd("MOV SI, AX\n");
                printCmd("ADD SI, " + to_string(si->stackPos) + "\n");
                printCmd("PUSH BP\n");
                printCmd("SUB BP, SI\n");
                printCmd("POP AX\n");
                printCmd("MOV [BP], AX\n");
                printCmd("POP BP\n");
            }
        }
        
    }
}

void loadExpCode(Info* var){
    cout << var->isRelExp << " " << var->isBooleanExp << endl;
    if( !var->isRelExp && !var->isBooleanExp ){
        loadVariablesCode(var);
        printCmd("CMP AX, 0\n");
        printCmd("JNE L\n");
        var->trueList.push_back(tempAsmLineCount);
        printCmd("JMP L\n");
        var->falseList.push_back(tempAsmLineCount);          
    }
}

void loadLogicCode(Info* var1,SymbolInfo* logicOp){
    if( var1->lexeme == "NULL" ){

    }else{
        loadVariablesCode(var1);
        if( logicOp->name == "||" ){
            printCmd("CMP AX, 0\n");
            printCmd("JNE L\n");
            var1->trueList.push_back(tempAsmLineCount);
            printCmd("JMP L\n");
            var1->falseList.push_back(tempAsmLineCount);
               
        }else if( logicOp->name == "&&" ){
            printCmd("CMP AX, 0\n");
            printCmd("JNE L\n");
            var1->trueList.push_back(tempAsmLineCount);
            printCmd("JMP L\n");
            var1->falseList.push_back(tempAsmLineCount);
        }
    }
    
}

void loadLogicCode3(Info* var1){
    if(var1->lexeme == "NULL"){
        loadExpCode(var1);
    }else{
        loadVariablesCode(var1);
        printCmd("CMP AX, 0\n");
        printCmd("JNE L\n");
        var1->trueList.push_back(tempAsmLineCount);
        printCmd("JMP L\n");
        var1->falseList.push_back(tempAsmLineCount);
    }
        
    
}

void loadLogicCode2(Info* var){
    if( var->isBooleanExp){
        printLabel(++asmLabel);
        backPatch(var->trueList,to_string(asmLabel));
        printCmd("MOV AX, 1\n");
        printCmd("JMP L" +  to_string(asmLabel+2) + "\n");
        printLabel(++asmLabel);
        backPatch(var->falseList,to_string(asmLabel));
        printCmd("MOV AX, 0\n");
        printLabel(++asmLabel);
        printCmd("PUSH AX\n");               
    }
}

void loadRelCode(Info* var){
    if( var->isRelExp ){
        printLabel(++asmLabel);
        backPatch(var->trueList,to_string(asmLabel));
        printCmd("MOV AX, 1\n");
        printCmd("JMP L" +  to_string(asmLabel+2) + "\n");
        printLabel(++asmLabel);
        backPatch(var->falseList,to_string(asmLabel));
        printCmd("MOV AX, 0\n");
        printLabel(++asmLabel);
        printCmd("PUSH AX\n");               
    }
}



void free1(SymbolInfo* si){ if(si != NULL) ; }
void free2(Info* si){ if(si != NULL) ; }



#line 808 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    FOR = 260,                     /* FOR  */
    WHILE = 261,                   /* WHILE  */
    DO = 262,                      /* DO  */
    BREAK = 263,                   /* BREAK  */
    INT = 264,                     /* INT  */
    CHAR = 265,                    /* CHAR  */
    FLOAT = 266,                   /* FLOAT  */
    DOUBLE = 267,                  /* DOUBLE  */
    VOID = 268,                    /* VOID  */
    RETURN = 269,                  /* RETURN  */
    SWITCH = 270,                  /* SWITCH  */
    CASE = 271,                    /* CASE  */
    DEFAULT = 272,                 /* DEFAULT  */
    CONTINUE = 273,                /* CONTINUE  */
    ASSIGNOP = 274,                /* ASSIGNOP  */
    NOT = 275,                     /* NOT  */
    LPAREN = 276,                  /* LPAREN  */
    RPAREN = 277,                  /* RPAREN  */
    LCURL = 278,                   /* LCURL  */
    RCURL = 279,                   /* RCURL  */
    LSQUARE = 280,                 /* LSQUARE  */
    RSQUARE = 281,                 /* RSQUARE  */
    COMMA = 282,                   /* COMMA  */
    SEMICOLON = 283,               /* SEMICOLON  */
    ID = 284,                      /* ID  */
    ADDOP = 285,                   /* ADDOP  */
    MULOP = 286,                   /* MULOP  */
    RELOP = 287,                   /* RELOP  */
    LOGICOP = 288,                 /* LOGICOP  */
    INCOP = 289,                   /* INCOP  */
    BITOP = 290,                   /* BITOP  */
    CONST_INT = 291,               /* CONST_INT  */
    CONST_FLOAT = 292,             /* CONST_FLOAT  */
    PRINTLN = 293,                 /* PRINTLN  */
    LOWER_THAN_ELSE = 294          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define DO 262
#define BREAK 263
#define INT 264
#define CHAR 265
#define FLOAT 266
#define DOUBLE 267
#define VOID 268
#define RETURN 269
#define SWITCH 270
#define CASE 271
#define DEFAULT 272
#define CONTINUE 273
#define ASSIGNOP 274
#define NOT 275
#define LPAREN 276
#define RPAREN 277
#define LCURL 278
#define RCURL 279
#define LSQUARE 280
#define RSQUARE 281
#define COMMA 282
#define SEMICOLON 283
#define ID 284
#define ADDOP 285
#define MULOP 286
#define RELOP 287
#define LOGICOP 288
#define INCOP 289
#define BITOP 290
#define CONST_INT 291
#define CONST_FLOAT 292
#define PRINTLN 293
#define LOWER_THAN_ELSE 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 738 "1805017.y"

    SymbolInfo* si;
    Info* info;

#line 944 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_DO = 7,                         /* DO  */
  YYSYMBOL_BREAK = 8,                      /* BREAK  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_CHAR = 10,                      /* CHAR  */
  YYSYMBOL_FLOAT = 11,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 12,                    /* DOUBLE  */
  YYSYMBOL_VOID = 13,                      /* VOID  */
  YYSYMBOL_RETURN = 14,                    /* RETURN  */
  YYSYMBOL_SWITCH = 15,                    /* SWITCH  */
  YYSYMBOL_CASE = 16,                      /* CASE  */
  YYSYMBOL_DEFAULT = 17,                   /* DEFAULT  */
  YYSYMBOL_CONTINUE = 18,                  /* CONTINUE  */
  YYSYMBOL_ASSIGNOP = 19,                  /* ASSIGNOP  */
  YYSYMBOL_NOT = 20,                       /* NOT  */
  YYSYMBOL_LPAREN = 21,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 22,                    /* RPAREN  */
  YYSYMBOL_LCURL = 23,                     /* LCURL  */
  YYSYMBOL_RCURL = 24,                     /* RCURL  */
  YYSYMBOL_LSQUARE = 25,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 26,                   /* RSQUARE  */
  YYSYMBOL_COMMA = 27,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 28,                 /* SEMICOLON  */
  YYSYMBOL_ID = 29,                        /* ID  */
  YYSYMBOL_ADDOP = 30,                     /* ADDOP  */
  YYSYMBOL_MULOP = 31,                     /* MULOP  */
  YYSYMBOL_RELOP = 32,                     /* RELOP  */
  YYSYMBOL_LOGICOP = 33,                   /* LOGICOP  */
  YYSYMBOL_INCOP = 34,                     /* INCOP  */
  YYSYMBOL_BITOP = 35,                     /* BITOP  */
  YYSYMBOL_CONST_INT = 36,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 37,               /* CONST_FLOAT  */
  YYSYMBOL_PRINTLN = 38,                   /* PRINTLN  */
  YYSYMBOL_LOWER_THAN_ELSE = 39,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_start = 41,                     /* start  */
  YYSYMBOL_program = 42,                   /* program  */
  YYSYMBOL_unit = 43,                      /* unit  */
  YYSYMBOL_func_declaration = 44,          /* func_declaration  */
  YYSYMBOL_func_definition = 45,           /* func_definition  */
  YYSYMBOL_46_1 = 46,                      /* $@1  */
  YYSYMBOL_47_2 = 47,                      /* $@2  */
  YYSYMBOL_48_3 = 48,                      /* $@3  */
  YYSYMBOL_49_4 = 49,                      /* $@4  */
  YYSYMBOL_parameter_list = 50,            /* parameter_list  */
  YYSYMBOL_compound_statement = 51,        /* compound_statement  */
  YYSYMBOL_newscope = 52,                  /* newscope  */
  YYSYMBOL_var_declaration = 53,           /* var_declaration  */
  YYSYMBOL_type_specifier = 54,            /* type_specifier  */
  YYSYMBOL_declaration_list = 55,          /* declaration_list  */
  YYSYMBOL_statements = 56,                /* statements  */
  YYSYMBOL_statement = 57,                 /* statement  */
  YYSYMBOL_58_5 = 58,                      /* $@5  */
  YYSYMBOL_n = 59,                         /* n  */
  YYSYMBOL_expression_statement = 60,      /* expression_statement  */
  YYSYMBOL_variable = 61,                  /* variable  */
  YYSYMBOL_expression = 62,                /* expression  */
  YYSYMBOL_logic_expression = 63,          /* logic_expression  */
  YYSYMBOL_64_6 = 64,                      /* $@6  */
  YYSYMBOL_m = 65,                         /* m  */
  YYSYMBOL_p = 66,                         /* p  */
  YYSYMBOL_rel_expression = 67,            /* rel_expression  */
  YYSYMBOL_68_7 = 68,                      /* $@7  */
  YYSYMBOL_simple_expression = 69,         /* simple_expression  */
  YYSYMBOL_70_8 = 70,                      /* $@8  */
  YYSYMBOL_term = 71,                      /* term  */
  YYSYMBOL_72_9 = 72,                      /* $@9  */
  YYSYMBOL_unary_expression = 73,          /* unary_expression  */
  YYSYMBOL_factor = 74,                    /* factor  */
  YYSYMBOL_argument_list = 75,             /* argument_list  */
  YYSYMBOL_arguments = 76                  /* arguments  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   303

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  174

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   760,   760,   774,   788,   803,   815,   826,   840,   873,
     908,   944,   979,  1007,  1035,  1064,  1096,  1096,  1144,  1144,
    1169,  1169,  1212,  1212,  1240,  1260,  1282,  1305,  1330,  1348,
    1371,  1393,  1413,  1433,  1450,  1470,  1472,  1519,  1562,  1578,
    1593,  1612,  1634,  1658,  1685,  1711,  1738,  1767,  1781,  1801,
    1825,  1838,  1856,  1872,  1884,  1906,  1919,  1932,  1946,  1946,
    1977,  2007,  2039,  2067,  2100,  2146,  2152,  2168,  2202,  2225,
    2258,  2315,  2343,  2395,  2421,  2421,  2482,  2489,  2504,  2532,
    2532,  2598,  2624,  2624,  2669,  2696,  2696,  2754,  2785,  2827,
    2857,  2877,  2928,  2961,  2984,  3004,  3073,  3092,  3107,  3135
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "FOR",
  "WHILE", "DO", "BREAK", "INT", "CHAR", "FLOAT", "DOUBLE", "VOID",
  "RETURN", "SWITCH", "CASE", "DEFAULT", "CONTINUE", "ASSIGNOP", "NOT",
  "LPAREN", "RPAREN", "LCURL", "RCURL", "LSQUARE", "RSQUARE", "COMMA",
  "SEMICOLON", "ID", "ADDOP", "MULOP", "RELOP", "LOGICOP", "INCOP",
  "BITOP", "CONST_INT", "CONST_FLOAT", "PRINTLN", "LOWER_THAN_ELSE",
  "$accept", "start", "program", "unit", "func_declaration",
  "func_definition", "$@1", "$@2", "$@3", "$@4", "parameter_list",
  "compound_statement", "newscope", "var_declaration", "type_specifier",
  "declaration_list", "statements", "statement", "$@5", "n",
  "expression_statement", "variable", "expression", "logic_expression",
  "$@6", "m", "p", "rel_expression", "$@7", "simple_expression", "$@8",
  "term", "$@9", "unary_expression", "factor", "argument_list",
  "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-125)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-86)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     118,  -125,  -125,  -125,    14,   118,  -125,  -125,  -125,  -125,
      -8,  -125,  -125,    68,    10,    59,    16,    38,    74,  -125,
       3,    19,    32,    87,    71,   100,   105,  -125,   116,    27,
    -125,  -125,   123,     0,    33,   118,  -125,  -125,  -125,   125,
      41,  -125,  -125,   123,  -125,  -125,    35,   118,  -125,  -125,
     123,   124,    76,   128,   133,  -125,    81,  -125,  -125,   123,
     132,  -125,  -125,   138,   139,  -125,  -125,   193,   146,   148,
    -125,   115,   115,   115,  -125,  -125,    75,   115,  -125,  -125,
     151,  -125,  -125,  -125,  -125,   119,  -125,  -125,    -4,    23,
    -125,   140,    91,   143,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,   157,   115,    78,   154,   155,   142,  -125,   160,   115,
     115,  -125,   150,   229,  -125,  -125,   115,  -125,   156,  -125,
    -125,   158,   159,   161,   265,  -125,   166,  -125,   115,  -125,
    -125,  -125,   169,   170,   174,   179,  -125,  -125,  -125,  -125,
    -125,   115,   115,   115,  -125,    78,   181,  -125,   115,  -125,
     177,   115,   178,   143,  -125,   265,  -125,  -125,  -125,  -125,
    -125,   205,   115,   265,  -125,  -125,  -125,  -125,   188,   265,
    -125,  -125,   265,  -125
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    38,    39,    40,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    47,     0,     0,     0,     0,     0,    36,
       0,     0,     0,    29,     0,     0,     0,    37,    41,     0,
      13,    12,     0,     0,     0,     0,    28,    48,    49,    42,
       0,    15,    14,     0,    35,    21,     0,     0,     9,     8,
       0,    26,     0,     0,     0,    23,     0,    11,    10,     0,
      27,    17,    24,     0,     0,    43,    45,     0,     0,     0,
      76,     0,     0,     0,    33,    66,    69,     0,    93,    94,
       0,    55,    56,    57,    53,     0,    50,    54,    90,     0,
      71,    73,    78,    81,    84,    89,    19,    25,    44,    46,
      34,     0,     0,     0,     0,     0,    90,    88,     0,    97,
       0,    87,     0,     0,    30,    51,     0,    95,     0,    67,
      74,     0,     0,     0,     0,    32,     0,    76,     0,    64,
      92,    99,     0,    96,     0,     0,    31,    52,    72,    68,
      76,     0,     0,     0,    77,     0,     0,    91,     0,    70,
       0,     0,    80,    83,    86,     0,    77,    77,    98,    63,
      75,    60,     0,     0,    65,    58,    62,    76,     0,     0,
      76,    61,     0,    59
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -125,  -125,  -125,   206,    18,    62,  -125,  -125,  -125,  -125,
    -125,   -24,  -125,    64,    -3,  -125,   145,   -84,  -125,  -125,
     -96,   -68,   -71,  -103,  -125,  -124,   -19,    67,  -125,    79,
    -125,    73,  -125,   -67,  -125,  -125,  -125
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     4,     5,     6,    81,    82,    50,    59,    32,    43,
      22,    83,    56,    84,    10,    14,    85,    86,   168,   167,
      87,    88,    89,    90,   140,   104,   155,    91,   121,    92,
     122,    93,   123,    94,    95,   132,   133
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     105,   115,   108,   145,   106,   107,   131,   127,    45,   106,
     111,    17,    23,   138,    11,   116,   151,   115,     7,    55,
      30,    13,    46,     7,   118,    29,    61,    47,    41,   137,
     117,   126,    51,    33,    48,    96,    57,    18,    19,   134,
     137,   106,   -20,   169,    60,   158,   172,    31,   106,   156,
     -22,   119,    24,    25,    34,    42,   -16,   146,   -18,    35,
      20,    49,     8,    58,     9,    26,    27,     8,     1,     9,
       2,   161,     3,   106,   106,   106,   154,    53,    54,   166,
     106,    21,    67,   106,    68,   171,    69,    70,   173,    15,
       1,   165,     2,    16,     3,    71,   109,    37,    72,    73,
     110,    72,    73,    28,    44,    74,    75,    76,    77,    75,
      76,    77,    63,    64,    78,    79,    36,    78,    79,    80,
     113,   -82,    68,   -79,    69,    70,    38,     1,     1,     2,
       2,     3,     3,    71,    39,    72,    73,   162,   163,    72,
      73,    40,    44,   114,    76,    77,    44,    75,    76,    77,
      52,    78,    79,    62,    65,    78,    79,    80,   124,    66,
      68,    97,    69,    70,    98,    99,     1,   102,     2,   103,
       3,    71,   112,   120,   -85,   128,   117,    72,    73,   135,
      44,   125,   130,   129,   139,    75,    76,    77,   144,   142,
     141,   147,   143,    78,    79,    80,    68,   148,    69,    70,
     149,   150,     1,   157,     2,   159,     3,    71,   -82,   164,
     170,    12,   101,    72,    73,   153,    44,   100,   160,     0,
     152,    75,    76,    77,     0,     0,     0,     0,     0,    78,
      79,    80,    68,     0,    69,    70,     0,     0,     1,     0,
       2,     0,     3,    71,     0,     0,     0,     0,     0,    72,
      73,     0,    44,   136,     0,     0,     0,    75,    76,    77,
       0,     0,     0,     0,     0,    78,    79,    80,    68,     0,
      69,    70,     0,     0,     1,     0,     2,     0,     3,    71,
       0,     0,     0,     0,     0,    72,    73,     0,    44,     0,
       0,     0,     0,    75,    76,    77,     0,     0,     0,     0,
       0,    78,    79,    80
};

static const yytype_int16 yycheck[] =
{
      71,    85,    73,   127,    72,    72,   109,   103,    32,    77,
      77,     1,    15,   116,     0,    19,   140,   101,     0,    43,
       1,    29,    22,     5,     1,    22,    50,    27,     1,   113,
      34,   102,    35,     1,     1,    59,     1,    27,    28,   110,
     124,   109,    23,   167,    47,   148,   170,    28,   116,   145,
      23,    28,    36,    37,    22,    28,    23,   128,    23,    27,
       1,    28,     0,    28,     0,    27,    28,     5,     9,     5,
      11,   155,    13,   141,   142,   143,   143,    36,    37,   163,
     148,    22,     1,   151,     3,   169,     5,     6,   172,    21,
       9,   162,    11,    25,    13,    14,    21,    26,    20,    21,
      25,    20,    21,    29,    23,    24,    28,    29,    30,    28,
      29,    30,    36,    37,    36,    37,    29,    36,    37,    38,
       1,    30,     3,    32,     5,     6,    26,     9,     9,    11,
      11,    13,    13,    14,    29,    20,    21,   156,   157,    20,
      21,    25,    23,    24,    29,    30,    23,    28,    29,    30,
      25,    36,    37,    29,    26,    36,    37,    38,     1,    26,
       3,    29,     5,     6,    26,    26,     9,    21,    11,    21,
      13,    14,    21,    33,    31,    21,    34,    20,    21,    29,
      23,    24,    22,    28,    28,    28,    29,    30,    22,    30,
      32,    22,    31,    36,    37,    38,     3,    27,     5,     6,
      26,    22,     9,    22,    11,    28,    13,    14,    30,     4,
      22,     5,    67,    20,    21,   142,    23,    24,   151,    -1,
     141,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,
      37,    38,     3,    -1,     5,     6,    -1,    -1,     9,    -1,
      11,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,
      21,    -1,    23,    24,    -1,    -1,    -1,    28,    29,    30,
      -1,    -1,    -1,    -1,    -1,    36,    37,    38,     3,    -1,
       5,     6,    -1,    -1,     9,    -1,    11,    -1,    13,    14,
      -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    23,    -1,
      -1,    -1,    -1,    28,    29,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    11,    13,    41,    42,    43,    44,    45,    53,
      54,     0,    43,    29,    55,    21,    25,     1,    27,    28,
       1,    22,    50,    54,    36,    37,    27,    28,    29,    22,
       1,    28,    48,     1,    22,    27,    29,    26,    26,    29,
      25,     1,    28,    49,    23,    51,    22,    27,     1,    28,
      46,    54,    25,    36,    37,    51,    52,     1,    28,    47,
      54,    51,    29,    36,    37,    26,    26,     1,     3,     5,
       6,    14,    20,    21,    24,    28,    29,    30,    36,    37,
      38,    44,    45,    51,    53,    56,    57,    60,    61,    62,
      63,    67,    69,    71,    73,    74,    51,    29,    26,    26,
      24,    56,    21,    21,    65,    62,    61,    73,    62,    21,
      25,    73,    21,     1,    24,    57,    19,    34,     1,    28,
      33,    68,    70,    72,     1,    24,    62,    60,    21,    28,
      22,    63,    75,    76,    62,    29,    24,    57,    63,    28,
      64,    32,    30,    31,    22,    65,    62,    22,    27,    26,
      22,    65,    69,    71,    73,    66,    60,    22,    63,    28,
      67,    57,    66,    66,     4,    62,    57,    59,    58,    65,
      22,    57,    65,    57
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    44,    44,
      44,    44,    44,    44,    44,    44,    46,    45,    47,    45,
      48,    45,    49,    45,    50,    50,    50,    50,    50,    50,
      51,    51,    51,    51,    51,    52,    53,    53,    54,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      56,    56,    56,    57,    57,    57,    57,    57,    58,    57,
      57,    57,    57,    57,    57,    59,    60,    60,    60,    61,
      61,    62,    62,    63,    64,    63,    65,    66,    67,    68,
      67,    69,    70,    69,    71,    72,    71,    73,    73,    73,
      74,    74,    74,    74,    74,    74,    75,    75,    76,    76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     6,
       7,     7,     5,     5,     6,     6,     0,     7,     0,     8,
       0,     6,     0,     7,     4,     5,     3,     4,     2,     1,
       4,     5,     5,     3,     4,     0,     3,     4,     1,     1,
       1,     3,     4,     6,     7,     6,     7,     1,     4,     4,
       1,     2,     3,     1,     1,     1,     1,     1,     0,    11,
       6,    10,     7,     5,     3,     0,     1,     2,     3,     1,
       4,     1,     3,     1,     0,     5,     0,     0,     1,     0,
       4,     1,     0,     4,     1,     0,     4,     2,     2,     1,
       1,     4,     3,     1,     1,     2,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_IF: /* IF  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1885 "y.tab.c"
        break;

    case YYSYMBOL_ELSE: /* ELSE  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1891 "y.tab.c"
        break;

    case YYSYMBOL_FOR: /* FOR  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1897 "y.tab.c"
        break;

    case YYSYMBOL_WHILE: /* WHILE  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1903 "y.tab.c"
        break;

    case YYSYMBOL_DO: /* DO  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1909 "y.tab.c"
        break;

    case YYSYMBOL_BREAK: /* BREAK  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1915 "y.tab.c"
        break;

    case YYSYMBOL_INT: /* INT  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1921 "y.tab.c"
        break;

    case YYSYMBOL_CHAR: /* CHAR  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1927 "y.tab.c"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1933 "y.tab.c"
        break;

    case YYSYMBOL_DOUBLE: /* DOUBLE  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1939 "y.tab.c"
        break;

    case YYSYMBOL_VOID: /* VOID  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1945 "y.tab.c"
        break;

    case YYSYMBOL_RETURN: /* RETURN  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1951 "y.tab.c"
        break;

    case YYSYMBOL_SWITCH: /* SWITCH  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1957 "y.tab.c"
        break;

    case YYSYMBOL_CASE: /* CASE  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1963 "y.tab.c"
        break;

    case YYSYMBOL_DEFAULT: /* DEFAULT  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1969 "y.tab.c"
        break;

    case YYSYMBOL_CONTINUE: /* CONTINUE  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1975 "y.tab.c"
        break;

    case YYSYMBOL_ASSIGNOP: /* ASSIGNOP  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1981 "y.tab.c"
        break;

    case YYSYMBOL_NOT: /* NOT  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1987 "y.tab.c"
        break;

    case YYSYMBOL_LPAREN: /* LPAREN  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1993 "y.tab.c"
        break;

    case YYSYMBOL_RPAREN: /* RPAREN  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 1999 "y.tab.c"
        break;

    case YYSYMBOL_LCURL: /* LCURL  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2005 "y.tab.c"
        break;

    case YYSYMBOL_RCURL: /* RCURL  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2011 "y.tab.c"
        break;

    case YYSYMBOL_LSQUARE: /* LSQUARE  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2017 "y.tab.c"
        break;

    case YYSYMBOL_RSQUARE: /* RSQUARE  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2023 "y.tab.c"
        break;

    case YYSYMBOL_COMMA: /* COMMA  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2029 "y.tab.c"
        break;

    case YYSYMBOL_SEMICOLON: /* SEMICOLON  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2035 "y.tab.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2041 "y.tab.c"
        break;

    case YYSYMBOL_ADDOP: /* ADDOP  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2047 "y.tab.c"
        break;

    case YYSYMBOL_MULOP: /* MULOP  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2053 "y.tab.c"
        break;

    case YYSYMBOL_RELOP: /* RELOP  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2059 "y.tab.c"
        break;

    case YYSYMBOL_LOGICOP: /* LOGICOP  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2065 "y.tab.c"
        break;

    case YYSYMBOL_INCOP: /* INCOP  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2071 "y.tab.c"
        break;

    case YYSYMBOL_BITOP: /* BITOP  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2077 "y.tab.c"
        break;

    case YYSYMBOL_CONST_INT: /* CONST_INT  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2083 "y.tab.c"
        break;

    case YYSYMBOL_CONST_FLOAT: /* CONST_FLOAT  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2089 "y.tab.c"
        break;

    case YYSYMBOL_PRINTLN: /* PRINTLN  */
#line 751 "1805017.y"
            { free1(((*yyvaluep).si));}
#line 2095 "y.tab.c"
        break;

    case YYSYMBOL_start: /* start  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2101 "y.tab.c"
        break;

    case YYSYMBOL_program: /* program  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2107 "y.tab.c"
        break;

    case YYSYMBOL_unit: /* unit  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2113 "y.tab.c"
        break;

    case YYSYMBOL_func_declaration: /* func_declaration  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2119 "y.tab.c"
        break;

    case YYSYMBOL_func_definition: /* func_definition  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2125 "y.tab.c"
        break;

    case YYSYMBOL_parameter_list: /* parameter_list  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2131 "y.tab.c"
        break;

    case YYSYMBOL_compound_statement: /* compound_statement  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2137 "y.tab.c"
        break;

    case YYSYMBOL_var_declaration: /* var_declaration  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2143 "y.tab.c"
        break;

    case YYSYMBOL_type_specifier: /* type_specifier  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2149 "y.tab.c"
        break;

    case YYSYMBOL_declaration_list: /* declaration_list  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2155 "y.tab.c"
        break;

    case YYSYMBOL_statements: /* statements  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2161 "y.tab.c"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2167 "y.tab.c"
        break;

    case YYSYMBOL_n: /* n  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2173 "y.tab.c"
        break;

    case YYSYMBOL_expression_statement: /* expression_statement  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2179 "y.tab.c"
        break;

    case YYSYMBOL_variable: /* variable  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2185 "y.tab.c"
        break;

    case YYSYMBOL_expression: /* expression  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2191 "y.tab.c"
        break;

    case YYSYMBOL_logic_expression: /* logic_expression  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2197 "y.tab.c"
        break;

    case YYSYMBOL_m: /* m  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2203 "y.tab.c"
        break;

    case YYSYMBOL_p: /* p  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2209 "y.tab.c"
        break;

    case YYSYMBOL_rel_expression: /* rel_expression  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2215 "y.tab.c"
        break;

    case YYSYMBOL_simple_expression: /* simple_expression  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2221 "y.tab.c"
        break;

    case YYSYMBOL_term: /* term  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2227 "y.tab.c"
        break;

    case YYSYMBOL_unary_expression: /* unary_expression  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2233 "y.tab.c"
        break;

    case YYSYMBOL_factor: /* factor  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2239 "y.tab.c"
        break;

    case YYSYMBOL_argument_list: /* argument_list  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2245 "y.tab.c"
        break;

    case YYSYMBOL_arguments: /* arguments  */
#line 750 "1805017.y"
            { free2(((*yyvaluep).info));}
#line 2251 "y.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: program  */
#line 761 "1805017.y"
    {
        (yyval.info)->line_count = (yyvsp[0].info)->line_count;

        string text = getRuleString("start","program",(yyval.info)->line_count,line_count-1);
        parseTree = new Node(1,"start","program",text);
        parseTree->children.push_back((yyvsp[0].info)->root);

        printToLogRule("start","program");

        delete (yyvsp[0].info);
    }
#line 2531 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 775 "1805017.y"
    {
        (yyval.info) = new Info();
        (yyval.info)->line_count = (yyvsp[-1].info)->line_count;

        string text = getRuleString("program","program unit",(yyval.info)->line_count,line_count);
        (yyval.info)->root = new Node(2,"program","program unit",text);
        (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
        (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

        printToLogRule("program","program unit");

        delete (yyvsp[-1].info);delete (yyvsp[0].info);
    }
#line 2549 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 789 "1805017.y"
        {
        (yyval.info) = new Info();
        (yyval.info)->line_count = (yyvsp[0].info)->line_count;

        string text = getRuleString("program","unit",(yyval.info)->line_count,line_count);
        (yyval.info)->root = new Node(3,"program","unit",text);
        (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

        printToLogRule("program","unit");

        delete (yyvsp[0].info);
    }
#line 2566 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 803 "1805017.y"
                       {
        (yyval.info) = new Info();
        (yyval.info)->line_count = (yyvsp[0].info)->line_count;

        string text = getRuleString("unit","var_declaration",(yyval.info)->line_count,line_count);
        (yyval.info)->root = new Node(4,"unit","var_declaration",text);
        (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

        printToLogRule("unit","var_declaration");

        delete (yyvsp[0].info);
    }
#line 2583 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 815 "1805017.y"
                        {
        (yyval.info) = new Info();
        (yyval.info)->line_count = (yyvsp[0].info)->line_count;

        string text = getRuleString("unit","func_declaration",(yyval.info)->line_count,line_count);
        (yyval.info)->root = new Node(5,"unit","func_declaration",text);
        (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

        printToLogRule("unit","func_declaration");

        delete (yyvsp[0].info);
    }
#line 2600 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 826 "1805017.y"
                       {
        (yyval.info) = new Info();
        (yyval.info)->line_count = (yyvsp[0].info)->line_count;

        string text = getRuleString("unit","func_definition",(yyval.info)->line_count,line_count);
        (yyval.info)->root = new Node(6,"unit","func_definition",text);
        (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

        printToLogRule("unit","func_definition");

        delete (yyvsp[0].info);
    }
#line 2617 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 840 "1805017.y"
                                                                            {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-5].info)->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(7,"func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON",text);

            (yyval.info)->root->children.push_back((yyvsp[-5].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-4].si));
            insertTOKEN((yyval.info),(yyvsp[-3].si));
            (yyval.info)->root->children.push_back((yyvsp[-2].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-1].si));
            insertTOKEN((yyval.info),(yyvsp[0].si));

            printToLogRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");

            (yyvsp[-4].si)->dataType = (yyvsp[-5].info)->data;
            (yyvsp[-4].si)->isFunction = true;
            (yyvsp[-4].si)->isFunctionDeclared = true;

            for(SymbolInfo s : parameterList){
                (yyvsp[-4].si)->params.push_back(s.dataType);
            }

            if(!st->insertSymbol(*(yyvsp[-4].si))){
                multipleFunctionDeclarationError((yyvsp[-4].si));
            }

            parameterList.clear();

            delete (yyvsp[-5].info);delete (yyvsp[-2].info);
            delete (yyvsp[-4].si);delete (yyvsp[-3].si);delete (yyvsp[-1].si);delete (yyvsp[0].si);
        }
#line 2656 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN error  */
#line 873 "1805017.y"
                                                                {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-5].info)->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN parameter_list RPAREN error",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(-1,"func_declaration","type_specifier ID LPAREN parameter_list RPAREN error",text);

            (yyval.info)->root->children.push_back((yyvsp[-5].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-4].si));
            insertTOKEN((yyval.info),(yyvsp[-3].si));
            (yyval.info)->root->children.push_back((yyvsp[-2].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-1].si));

            printToLogRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN error");

            // $2->dataType = $1->data;
            // $2->isFunction = true;
            // $2->isFunctionDeclared = true;

            // for(SymbolInfo s : parameterList){
            //     $2->params.push_back(s.dataType);
            // }

            // if(!st->insertSymbol(*$2)){
            //     multipleFunctionDeclarationError($2);
            // }

            parameterList.clear();

            printSyntaxError("SEMICOLON","function declaration",(yyvsp[-1].si)->line_count);

            delete (yyvsp[-5].info);delete (yyvsp[-2].info);
            delete (yyvsp[-4].si);delete (yyvsp[-3].si);delete (yyvsp[-1].si);

        }
#line 2697 "y.tab.c"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON  */
#line 908 "1805017.y"
                                                                         {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-6].info)->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(-1,"func_declaration","type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON",text);

            (yyval.info)->root->children.push_back((yyvsp[-6].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-5].si));
            insertTOKEN((yyval.info),(yyvsp[-4].si));
            (yyval.info)->root->children.push_back((yyvsp[-3].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-1].si));
            insertTOKEN((yyval.info),(yyvsp[0].si));

            printToLogRule("func_declaration","type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON");

            // $2->dataType = $1->data;
            // $2->isFunction = true;
            // $2->isFunctionDeclared = true;

            // for(SymbolInfo s : parameterList){
            //     $2->params.push_back(s.dataType);
            // }

            // if(!st->insertSymbol(*$2)){
            //     multipleFunctionDeclarationError($2);
            // }

            parameterList.clear();

            printSyntaxError("parameter list","function declaration",(yyvsp[-3].info)->line_count);

            delete (yyvsp[-6].info);delete (yyvsp[-3].info);
            delete (yyvsp[-5].si);delete (yyvsp[-4].si);delete (yyvsp[-1].si);delete (yyvsp[0].si);

        }
#line 2739 "y.tab.c"
    break;

  case 11: /* func_declaration: type_specifier ID LPAREN parameter_list error RPAREN error  */
#line 944 "1805017.y"
                                                                      {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-6].info)->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN parameter_list error RPAREN error",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(-1,"func_declaration","type_specifier ID LPAREN parameter_list error RPAREN error",text);

            (yyval.info)->root->children.push_back((yyvsp[-6].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-5].si));
            insertTOKEN((yyval.info),(yyvsp[-4].si));
            (yyval.info)->root->children.push_back((yyvsp[-3].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-1].si));

            printToLogRule("func_declaration","type_specifier ID LPAREN parameter_list error RPAREN error");

            // $2->dataType = $1->data;
            // $2->isFunction = true;
            // $2->isFunctionDeclared = true;

            // for(SymbolInfo s : parameterList){
            //     $2->params.push_back(s.dataType);
            // }

            // if(!st->insertSymbol(*$2)){
            //     multipleFunctionDeclarationError($2);
            // }
            printSyntaxError("parameter list","function declaration",(yyvsp[-3].info)->line_count);
            printSyntaxError("SEMICOLON","function declaration",(yyvsp[-1].si)->line_count);

            parameterList.clear();

            delete (yyvsp[-6].info);delete (yyvsp[-3].info);
            delete (yyvsp[-5].si);delete (yyvsp[-4].si);delete (yyvsp[-1].si);

        }
#line 2780 "y.tab.c"
    break;

  case 12: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 979 "1805017.y"
                                                     {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-4].info)->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(8,"func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON",text);

            (yyval.info)->root->children.push_back((yyvsp[-4].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-3].si));
            insertTOKEN((yyval.info),(yyvsp[-2].si));
            insertTOKEN((yyval.info),(yyvsp[-1].si));
            insertTOKEN((yyval.info),(yyvsp[0].si));

            printToLogRule("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");

            (yyvsp[-3].si)->dataType = (yyvsp[-4].info)->data;
            (yyvsp[-3].si)->isFunction = true;
            (yyvsp[-3].si)->isFunctionDeclared = true;

            if(!st->insertSymbol(*(yyvsp[-3].si))){
                multipleFunctionDeclarationError((yyvsp[-3].si));
            }

            parameterList.clear();

            delete (yyvsp[-4].info);
            delete (yyvsp[-3].si);delete (yyvsp[-2].si);delete (yyvsp[-1].si);delete (yyvsp[0].si);
        }
#line 2814 "y.tab.c"
    break;

  case 13: /* func_declaration: type_specifier ID LPAREN RPAREN error  */
#line 1007 "1805017.y"
                                                {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-4].info)->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN RPAREN error",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(-1,"func_declaration","type_specifier ID LPAREN RPAREN error",text);

            (yyval.info)->root->children.push_back((yyvsp[-4].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-3].si));
            insertTOKEN((yyval.info),(yyvsp[-2].si));
            insertTOKEN((yyval.info),(yyvsp[-1].si));

            printToLogRule("func_declaration","type_specifier ID LPAREN RPAREN error");

            // $2->dataType = $1->data;
            // $2->isFunction = true;
            // $2->isFunctionDeclared = true;

            // if(!st->insertSymbol(*$2)){
            //     multipleFunctionDeclarationError($2);
            // }

            parameterList.clear();
            printSyntaxError("SEMICOLON","function declaration",(yyvsp[-1].si)->line_count);

            delete (yyvsp[-4].info);
            delete (yyvsp[-3].si);delete (yyvsp[-2].si);delete (yyvsp[-1].si);
        }
#line 2848 "y.tab.c"
    break;

  case 14: /* func_declaration: type_specifier ID LPAREN error RPAREN SEMICOLON  */
#line 1035 "1805017.y"
                                                          {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-5].info)->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN error RPAREN SEMICOLON",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(-1,"func_declaration","type_specifier ID LPAREN error RPAREN SEMICOLON",text);

            (yyval.info)->root->children.push_back((yyvsp[-5].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-4].si));
            insertTOKEN((yyval.info),(yyvsp[-3].si));
            insertTOKEN((yyval.info),(yyvsp[-1].si));
            insertTOKEN((yyval.info),(yyvsp[0].si));

            printToLogRule("func_declaration","type_specifier ID LPAREN error RPAREN SEMICOLON");

            // $2->dataType = $1->data;
            // $2->isFunction = true;
            // $2->isFunctionDeclared = true;

            // if(!st->insertSymbol(*$2)){
            //     multipleFunctionDeclarationError($2);
            // }

            parameterList.clear();
            printSyntaxError("parameter list","function declaration",(yyvsp[-3].si)->line_count);

            delete (yyvsp[-5].info);
            delete (yyvsp[-4].si);delete (yyvsp[-3].si);delete (yyvsp[-1].si);delete (yyvsp[0].si);
        }
#line 2883 "y.tab.c"
    break;

  case 15: /* func_declaration: type_specifier ID LPAREN error RPAREN error  */
#line 1064 "1805017.y"
                                                      {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-5].info)->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN error RPAREN error",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(8,"func_declaration","type_specifier ID LPAREN error RPAREN error",text);

            (yyval.info)->root->children.push_back((yyvsp[-5].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-4].si));
            insertTOKEN((yyval.info),(yyvsp[-3].si));
            insertTOKEN((yyval.info),(yyvsp[-1].si));

            printToLogRule("func_declaration","type_specifier ID LPAREN error RPAREN error");

            // $2->dataType = $1->data;
            // $2->isFunction = true;
            // $2->isFunctionDeclared = true;

            // if(!st->insertSymbol(*$2)){
            //     multipleFunctionDeclarationError($2);
            // }

            parameterList.clear();
            printSyntaxError("parameter list","function declaration",(yyvsp[-3].si)->line_count);
            printSyntaxError("SEMICOLON","function declaration",(yyvsp[-1].si)->line_count);

            delete (yyvsp[-5].info);
            delete (yyvsp[-4].si);delete (yyvsp[-3].si);delete (yyvsp[-1].si);
        }
#line 2918 "y.tab.c"
    break;

  case 16: /* $@1: %empty  */
#line 1096 "1805017.y"
                                                                 { isFuncNow = true;insertFuncDefToSymbolTable((yyvsp[-3].si),(yyvsp[-4].info)->data);initFuncAsmCode((yyvsp[-3].si)); }
#line 2924 "y.tab.c"
    break;

  case 17: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 1096 "1805017.y"
                                                                                                                                                                      {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-6].info)->line_count;

            string text = getRuleString("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(9,"func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement",text);

            (yyval.info)->root->children.push_back((yyvsp[-6].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-5].si));
            insertTOKEN((yyval.info),(yyvsp[-4].si));
            (yyval.info)->root->children.push_back((yyvsp[-3].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-2].si));
            (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

            printToLogRule("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
            
            isFuncNow = false;
            int paramNum = parameterList.size();
            parameterList.clear();
            // cout << "*****" << currFunc.stackPos << endl;


            if(!currFunc.returnFlag && (yyvsp[-5].si)->dataType != "VOID"){
                noReturnError(line_count);
            }

            if( currFunc.stackPos > 0 )
                printCmd("ADD SP, " + to_string(currFunc.stackPos) + "\n");
            printCmd("POP BP\n");

            if((yyvsp[-5].si)->name == "main"){
                printCmd("MOV AX, 4CH\n");
                printCmd("INT 21H\n");
            }else{
                if( paramNum == 0 )
                    printCmd("RET\n");
                else
                    printCmd("RET " + to_string(paramNum*2) + "\n");
            }

            tempAsmOut << (yyvsp[-5].si)->name << " ENDP\n";tempAsmLineCount++;

            backPatch((yyvsp[0].info)->nextList,to_string(asmLabel));
            
            delete (yyvsp[-6].info);delete (yyvsp[-3].info);delete (yyvsp[0].info);
            delete (yyvsp[-5].si);delete (yyvsp[-4].si);delete (yyvsp[-2].si);

        }
#line 2978 "y.tab.c"
    break;

  case 18: /* $@2: %empty  */
#line 1144 "1805017.y"
                                                               {}
#line 2984 "y.tab.c"
    break;

  case 19: /* func_definition: type_specifier ID LPAREN parameter_list error RPAREN $@2 compound_statement  */
#line 1144 "1805017.y"
                                                                                     {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-7].info)->line_count;

            string text = getRuleString("func_definition","type_specifier ID LPAREN parameter_list error RPAREN",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(9,"func_definition","type_specifier ID LPAREN parameter_list error RPAREN",text);

            (yyval.info)->root->children.push_back((yyvsp[-7].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-6].si));
            insertTOKEN((yyval.info),(yyvsp[-5].si));
            (yyval.info)->root->children.push_back((yyvsp[-4].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-2].si));
            (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

            printToLogRule("func_definition","type_specifier ID LPAREN parameter_list error RPAREN");
            
            isFuncNow = false;
            parameterList.clear();
            
            printSyntaxError("parameter list","function definition",(yyvsp[-4].info)->line_count);

            delete (yyvsp[-7].info);delete (yyvsp[-4].info);delete (yyvsp[0].info);
            delete (yyvsp[-6].si);delete (yyvsp[-5].si);delete (yyvsp[-2].si);

        }
#line 3015 "y.tab.c"
    break;

  case 20: /* $@3: %empty  */
#line 1169 "1805017.y"
                                           { isFuncNow = true;insertFuncDefToSymbolTable((yyvsp[-2].si),(yyvsp[-3].info)->data);initFuncAsmCode((yyvsp[-2].si));}
#line 3021 "y.tab.c"
    break;

  case 21: /* func_definition: type_specifier ID LPAREN RPAREN $@3 compound_statement  */
#line 1169 "1805017.y"
                                                                                                                                               {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-5].info)->line_count;

            string text = getRuleString("func_definition","type_specifier ID LPAREN RPAREN compound_statement",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(10,"func_definition","type_specifier ID LPAREN RPAREN compound_statement",text);

            (yyval.info)->root->children.push_back((yyvsp[-5].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-4].si));
            insertTOKEN((yyval.info),(yyvsp[-3].si));
            insertTOKEN((yyval.info),(yyvsp[-2].si));
            (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

            printToLogRule("func_definition","type_specifier ID LPAREN RPAREN compound_statement");
            
            isFuncNow = false;
            parameterList.clear();
            // cout << "*****" << currFunc.stackPos << endl;

            if(!currFunc.returnFlag && (yyvsp[-4].si)->dataType != "VOID"){
                noReturnError(line_count);
            }

            if( currFunc.stackPos > 0 )
                printCmd("ADD SP, " + to_string(currFunc.stackPos) + "\n");
            // printLabel(++asmLabel);
            printCmd("POP BP\n");

            if((yyvsp[-4].si)->name == "main"){
                printCmd("MOV AX, 4CH\n");
                printCmd("INT 21H\n");
            }else{
                printCmd("RET\n");
            }

            tempAsmOut << (yyvsp[-4].si)->name << " ENDP\n";tempAsmLineCount++;

            backPatch((yyvsp[0].info)->nextList,to_string(asmLabel));
            
            delete (yyvsp[-5].info);delete (yyvsp[0].info);
            delete (yyvsp[-4].si);delete (yyvsp[-3].si);delete (yyvsp[-2].si);

        }
#line 3070 "y.tab.c"
    break;

  case 22: /* $@4: %empty  */
#line 1212 "1805017.y"
                                                 {}
#line 3076 "y.tab.c"
    break;

  case 23: /* func_definition: type_specifier ID LPAREN error RPAREN $@4 compound_statement  */
#line 1212 "1805017.y"
                                                                       {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-6].info)->line_count;

            string text = getRuleString("func_definition","type_specifier ID LPAREN error RPAREN compound_statement",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(10,"func_definition","type_specifier ID LPAREN error RPAREN compound_statement",text);

            (yyval.info)->root->children.push_back((yyvsp[-6].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-5].si));
            insertTOKEN((yyval.info),(yyvsp[-4].si));
            insertTOKEN((yyval.info),(yyvsp[-2].si));
            (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

            printToLogRule("func_definition","type_specifier ID LPAREN error RPAREN compound_statement");
            
            isFuncNow = false;
            parameterList.clear();
            
            printSyntaxError("parameter list","function definition",(yyvsp[-4].si)->line_count);
            
            delete (yyvsp[-6].info);delete (yyvsp[0].info);
            delete (yyvsp[-5].si);delete (yyvsp[-4].si);delete (yyvsp[-2].si);

        }
#line 3106 "y.tab.c"
    break;

  case 24: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 1240 "1805017.y"
                                                         {
            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-3].info)->line_count;

            string text = getRuleString("parameter_list","parameter_list COMMA type_specifier ID",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(11,"parameter_list","parameter_list COMMA type_specifier ID",text);

            (yyval.info)->root->children.push_back((yyvsp[-3].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-2].si));
            (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
            insertTOKEN((yyval.info),(yyvsp[0].si));

            printToLogRule("parameter_list","parameter_list COMMA type_specifier ID");

            (yyvsp[0].si)->dataType = (yyvsp[-1].info)->data; 
            parameterList.push_back(*(yyvsp[0].si));


            delete (yyvsp[-3].info);delete (yyvsp[-1].info);
            delete (yyvsp[-2].si);delete (yyvsp[0].si);
        }
#line 3132 "y.tab.c"
    break;

  case 25: /* parameter_list: parameter_list error COMMA type_specifier ID  */
#line 1260 "1805017.y"
                                                       {
            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-4].info)->line_count;

            string text = getRuleString("parameter_list","parameter_list error COMMA type_specifier ID",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(11,"parameter_list","parameter_list error COMMA type_specifier ID",text);

            (yyval.info)->root->children.push_back((yyvsp[-4].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-2].si));
            (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
            insertTOKEN((yyval.info),(yyvsp[0].si));

            printToLogRule("parameter_list","parameter_list error COMMA type_specifier ID");

            // $5->dataType = $4->data;
            // parameterList.push_back(*$5);

            printSyntaxError("parameter list","parameter list",(yyvsp[-4].info)->line_count);

            delete (yyvsp[-4].info);delete (yyvsp[-1].info);
            delete (yyvsp[-2].si);delete (yyvsp[0].si);

        }
#line 3160 "y.tab.c"
    break;

  case 26: /* parameter_list: parameter_list COMMA type_specifier  */
#line 1282 "1805017.y"
                                               {
            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-2].info)->line_count;

            string text = getRuleString("parameter_list","parameter_list COMMA type_specifier",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(12,"parameter_list","parameter_list COMMA type_specifier",text);

            (yyval.info)->root->children.push_back((yyvsp[-2].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-1].si));
            (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

            printToLogRule("parameter_list","parameter_list COMMA type_specifier");

            SymbolInfo temp;
            temp.type = "";
            temp.name = "NO_IDENTIFIER_NAME";
            temp.dataType = (yyvsp[0].info)->data;

            parameterList.push_back(temp);

            delete (yyvsp[-2].info);delete (yyvsp[0].info);
            delete (yyvsp[-1].si);

		}
#line 3189 "y.tab.c"
    break;

  case 27: /* parameter_list: parameter_list error COMMA type_specifier  */
#line 1305 "1805017.y"
                                                             {
            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-3].info)->line_count;

            string text = getRuleString("parameter_list","parameter_list error COMMA type_specifier",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(12,"parameter_list","parameter_list error COMMA type_specifier",text);

            (yyval.info)->root->children.push_back((yyvsp[-3].info)->root);
            insertTOKEN((yyval.info),(yyvsp[-1].si));
            (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

            printToLogRule("parameter_list","parameter_list error COMMA type_specifier");

            // SymbolInfo temp;
            // temp.type = "";
            // temp.name = "NO_IDENTIFIER_NAME";
            // temp.dataType = $4->data;

            // parameterList.push_back(temp);

            printSyntaxError("parameter list","parameter list",(yyvsp[-3].info)->line_count);

            delete (yyvsp[-3].info);delete (yyvsp[0].info);
            delete (yyvsp[-1].si);

		}
#line 3220 "y.tab.c"
    break;

  case 28: /* parameter_list: type_specifier ID  */
#line 1330 "1805017.y"
                                     {
            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-1].info)->line_count;

            string text = getRuleString("parameter_list","type_specifier ID",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(13,"parameter_list","type_specifier ID",text);

            (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
            insertTOKEN((yyval.info),(yyvsp[0].si));

            printToLogRule("parameter_list","type_specifier ID");

            (yyvsp[0].si)->dataType = (yyvsp[-1].info)->data;
            parameterList.push_back(*(yyvsp[0].si));

            delete (yyvsp[-1].info);
            delete (yyvsp[0].si);

		}
#line 3244 "y.tab.c"
    break;

  case 29: /* parameter_list: type_specifier  */
#line 1348 "1805017.y"
                                  {
            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[0].info)->line_count;

            string text = getRuleString("parameter_list","type_specifier",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(14,"parameter_list","type_specifier",text);

            (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

            printToLogRule("parameter_list","type_specifier");

            SymbolInfo temp;
            temp.type = "";
            temp.name = "NO_IDENTIFIER_NAME";
            temp.dataType = (yyvsp[0].info)->data;

            parameterList.push_back(temp);

            delete (yyvsp[0].info);
		}
#line 3269 "y.tab.c"
    break;

  case 30: /* compound_statement: LCURL newscope statements RCURL  */
#line 1371 "1805017.y"
                                                     {

                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-3].si)->line_count;

                string text = getRuleString("compound_statement","LCURL statements RCURL",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(15,"compound_statement","LCURL statements RCURL",text);

                insertTOKEN((yyval.info),(yyvsp[-3].si));
                (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("compound_statement","LCURL statements RCURL");

                st->printAll(logout);
                st->exitScope();

                (yyval.info)->nextList = (yyvsp[-1].info)->nextList;

                delete (yyvsp[-1].info);
                delete (yyvsp[-3].si);delete (yyvsp[0].si);

            }
#line 3297 "y.tab.c"
    break;

  case 31: /* compound_statement: LCURL newscope statements error RCURL  */
#line 1393 "1805017.y"
                                                    {

                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-4].si)->line_count;

                string text = getRuleString("compound_statement","LCURL statements error RCURL",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(15,"compound_statement","LCURL statements error RCURL",text);

                insertTOKEN((yyval.info),(yyvsp[-4].si));
                (yyval.info)->root->children.push_back((yyvsp[-2].info)->root);
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("compound_statement","LCURL statements error RCURL");

                st->printAll(logout);
                st->exitScope();

                delete (yyvsp[-2].info);
                delete (yyvsp[-4].si);delete (yyvsp[0].si);

            }
#line 3323 "y.tab.c"
    break;

  case 32: /* compound_statement: LCURL newscope error statements RCURL  */
#line 1413 "1805017.y"
                                                    {

                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-4].si)->line_count;

                string text = getRuleString("compound_statement","LCURL error statements RCURL",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(15,"compound_statement","LCURL error statements RCURL",text);

                insertTOKEN((yyval.info),(yyvsp[-4].si));
                (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("compound_statement","LCURL error statements RCURL");

                st->printAll(logout);
                st->exitScope();

                delete (yyvsp[-1].info);
                delete (yyvsp[-4].si);delete (yyvsp[0].si);

            }
#line 3349 "y.tab.c"
    break;

  case 33: /* compound_statement: LCURL newscope RCURL  */
#line 1433 "1805017.y"
                                    {

                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-2].si)->line_count;

                string text = getRuleString("compound_statement","LCURL RCURL",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(16,"compound_statement","LCURL RCURL",text);

                insertTOKEN((yyval.info),(yyvsp[-2].si));
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("compound_statement","LCURL RCURL");

                st->printAll(logout);
                st->exitScope();

                delete (yyvsp[-2].si);delete (yyvsp[0].si);
            }
#line 3372 "y.tab.c"
    break;

  case 34: /* compound_statement: LCURL newscope error RCURL  */
#line 1450 "1805017.y"
                                          {

                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-3].si)->line_count;

                string text = getRuleString("compound_statement","LCURL error RCURL",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(16,"compound_statement","LCURL error RCURL",text);

                insertTOKEN((yyval.info),(yyvsp[-3].si));
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("compound_statement","LCURL error RCURL");

                st->printAll(logout);
                st->exitScope();

                delete (yyvsp[-3].si);delete (yyvsp[0].si);
            }
#line 3395 "y.tab.c"
    break;

  case 35: /* newscope: %empty  */
#line 1470 "1805017.y"
            {enterNewScope();}
#line 3401 "y.tab.c"
    break;

  case 36: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 1472 "1805017.y"
                                                            {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-2].info)->line_count;

            string text = getRuleString("var_declaration","type_specifier declaration_list SEMICOLON",(yyval.info)->line_count,line_count);

            (yyval.info)->root = new Node(17,"var_declaration","type_specifier declaration_list SEMICOLON",text);

            (yyval.info)->root->children.push_back((yyvsp[-2].info)->root);
            (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
            insertTOKEN((yyval.info),(yyvsp[0].si));

            printToLogRule("var_declaration","type_specifier declaration_list SEMICOLON");
            
            if((yyvsp[-2].info)->data == "VOID"){
                string varID = "";
                int lc = (yyvsp[-2].info)->line_count;
                if(!(yyvsp[-1].info)->symbols.empty()){
                    varID = (yyvsp[-1].info)->symbols[0].name;
                    lc = (yyvsp[-1].info)->symbols[0].line_count;
                }
                dataTypeError(varID,line_count);
            }else{
                for( SymbolInfo s : (yyvsp[-1].info)->symbols ){
                    if(s.dataType == "ARRAY")
                        s.dataType = (yyvsp[-2].info)->data + "_ARRAY";
                    else
                        s.dataType = (yyvsp[-2].info)->data;

                    if(s.name == "number" || s.name == "CR" || s.name == "LF"){
                        VarNameError(s.name,s.line_count);
                        continue;
                    }
                    if(!st->insertSymbol(s)){
                        multipleVarDeclarationError(s.name,s.line_count);
                    }else{
                        // cout << s.name << " " << s.dataType << endl;
                        setupVarDeclCodes(s.name);
                    }
                }
            }



            delete (yyvsp[-2].info);delete (yyvsp[-1].info);
            delete (yyvsp[0].si);
        }
#line 3454 "y.tab.c"
    break;

  case 37: /* var_declaration: type_specifier declaration_list error SEMICOLON  */
#line 1519 "1805017.y"
                                                          {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[-3].info)->line_count;

            string text = getRuleString("var_declaration","type_specifier declaration_list error SEMICOLON",(yyval.info)->line_count,line_count);

            (yyval.info)->root = new Node(17,"var_declaration","type_specifier declaration_list error SEMICOLON",text);

            (yyval.info)->root->children.push_back((yyvsp[-3].info)->root);
            (yyval.info)->root->children.push_back((yyvsp[-2].info)->root);
            insertTOKEN((yyval.info),(yyvsp[0].si));

            printToLogRule("var_declaration","type_specifier declaration_list error SEMICOLON");
            
            // if($1->data == "VOID"){
            //     string varID = "";
            //     int lc = $1->line_count;
            //     if(!$2->symbols.empty()){
            //         varID = $2->symbols[0].name;
            //         lc = $2->symbols[0].line_count;
            //     }
            //     dataTypeError(varID,line_count);
            // }else{
            //     for( SymbolInfo s : $2->symbols ){
            //         if(s.dataType == "ARRAY")
            //             s.dataType = $1->data + "_ARRAY";
            //         else
            //             s.dataType = $1->data;
                    
            //         if(!st->insertSymbol(s)){
            //             multipleVarDeclarationError(s.name,s.line_count);
            //         }
            //     }
            // }

            printSyntaxError("declaration list","variable declaration",(yyvsp[-2].info)->line_count);

            delete (yyvsp[-3].info);delete (yyvsp[-2].info);
            delete (yyvsp[0].si);
        }
#line 3500 "y.tab.c"
    break;

  case 38: /* type_specifier: INT  */
#line 1562 "1805017.y"
                      {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[0].si)->line_count;

            string text = getRuleString("type_specifier","INT",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(18,"type_specifier","INT",text);

            insertTOKEN((yyval.info),(yyvsp[0].si));

            printToLogRule("type_specifier","INT");

            (yyval.info)->data = (yyvsp[0].si)->type;

            delete (yyvsp[0].si);

        }
#line 3522 "y.tab.c"
    break;

  case 39: /* type_specifier: FLOAT  */
#line 1578 "1805017.y"
                 {
            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[0].si)->line_count;

            string text = getRuleString("type_specifier","FLOAT",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(19,"type_specifier","FLOAT",text);

            insertTOKEN((yyval.info),(yyvsp[0].si));

            printToLogRule("type_specifier","FLOAT");

            (yyval.info)->data = (yyvsp[0].si)->type;

            delete (yyvsp[0].si);

        }
#line 3543 "y.tab.c"
    break;

  case 40: /* type_specifier: VOID  */
#line 1593 "1805017.y"
                {

            (yyval.info) = new Info();
            (yyval.info)->line_count = (yyvsp[0].si)->line_count;

            string text = getRuleString("type_specifier","VOID",(yyval.info)->line_count,line_count);
            (yyval.info)->root = new Node(20,"type_specifier","VOID",text);

            insertTOKEN((yyval.info),(yyvsp[0].si));

            printToLogRule("type_specifier","VOID");

            (yyval.info)->data = (yyvsp[0].si)->type;

            delete (yyvsp[0].si);

        }
#line 3565 "y.tab.c"
    break;

  case 41: /* declaration_list: declaration_list COMMA ID  */
#line 1612 "1805017.y"
                                            {

                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-2].info)->line_count;

                string text = getRuleString("declaration_list","declaration_list COMMA ID",(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(21,"declaration_list","declaration_list COMMA ID",text);

                (yyval.info)->root->children.push_back((yyvsp[-2].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("declaration_list","declaration_list COMMA ID");

                (yyval.info)->symbols = (yyvsp[-2].info)->symbols;
                (yyval.info)->symbols.push_back(*(yyvsp[0].si));
                (yyval.info)->server = (yyvsp[-2].info)->server;

                delete (yyvsp[-2].info);
                delete (yyvsp[-1].si);delete (yyvsp[0].si);

            }
#line 3593 "y.tab.c"
    break;

  case 42: /* declaration_list: declaration_list error COMMA ID  */
#line 1634 "1805017.y"
                                             {

                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-3].info)->line_count;

                string text = getRuleString("declaration_list","declaration_list error COMMA ID",(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(21,"declaration_list","declaration_list error COMMA ID",text);

                (yyval.info)->root->children.push_back((yyvsp[-3].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("declaration_list","declaration_list error COMMA ID");

                // $$->symbols = $1->symbols;
                // $$->symbols.push_back(*$4);
                // $$->server = $1->server;

                printSyntaxError("declaration list","variable declaration",(yyvsp[-3].info)->line_count);

                delete (yyvsp[-3].info);
                delete (yyvsp[-1].si);delete (yyvsp[0].si);

            }
#line 3623 "y.tab.c"
    break;

  case 43: /* declaration_list: declaration_list COMMA ID LSQUARE CONST_INT RSQUARE  */
#line 1658 "1805017.y"
                                                                   {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-5].info)->line_count;

                string text = getRuleString("declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE",(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(22,"declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE",text);

                (yyval.info)->root->children.push_back((yyvsp[-5].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-4].si));
                insertTOKEN((yyval.info),(yyvsp[-3].si));
                insertTOKEN((yyval.info),(yyvsp[-2].si));
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
                
                (yyvsp[-3].si)->arraySize = stoi((yyvsp[-1].si)->name);
                //cout << "ttttttt" << $3->arraySize << endl;

                (yyval.info)->symbols = (yyvsp[-5].info)->symbols;
                (yyvsp[-3].si)->dataType = "ARRAY";
                (yyval.info)->symbols.push_back(*(yyvsp[-3].si));
                (yyval.info)->server = (yyvsp[-5].info)->server;

                delete (yyvsp[-5].info);
                delete (yyvsp[-4].si);delete (yyvsp[-3].si);delete (yyvsp[-2].si);delete (yyvsp[-1].si);delete (yyvsp[0].si);
            }
#line 3656 "y.tab.c"
    break;

  case 44: /* declaration_list: declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE  */
#line 1685 "1805017.y"
                                                                         {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-6].info)->line_count;

                string text = getRuleString("declaration_list","declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE",(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(22,"declaration_list","declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE",text);

                (yyval.info)->root->children.push_back((yyvsp[-6].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-4].si));
                insertTOKEN((yyval.info),(yyvsp[-3].si));
                insertTOKEN((yyval.info),(yyvsp[-2].si));
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("declaration_list","declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE");

                // $$->symbols = $1->symbols;
                // $3->dataType = "ARRAY";
                // $$->symbols.push_back(*$4);
                // $$->server = $1->server;

                printSyntaxError("declaration list","variable declaration",(yyvsp[-6].info)->line_count);

                delete (yyvsp[-6].info);
                delete (yyvsp[-4].si);delete (yyvsp[-3].si);delete (yyvsp[-2].si);delete (yyvsp[-1].si);delete (yyvsp[0].si);
            }
#line 3688 "y.tab.c"
    break;

  case 45: /* declaration_list: declaration_list COMMA ID LSQUARE CONST_FLOAT RSQUARE  */
#line 1711 "1805017.y"
                                                                     {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-5].info)->line_count;

                string text = getRuleString("declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE",(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(22,"declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE",text);

                (yyval.info)->root->children.push_back((yyvsp[-5].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-4].si));
                insertTOKEN((yyval.info),(yyvsp[-3].si));
                insertTOKEN((yyval.info),(yyvsp[-2].si));
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");


                (yyval.info)->symbols = (yyvsp[-5].info)->symbols;
                (yyvsp[-3].si)->dataType = "ARRAY";
                (yyval.info)->symbols.push_back(*(yyvsp[-3].si));

                ArraySizeFloatError((yyvsp[-1].si)->line_count);
                (yyval.info)->server = (yyvsp[-5].info)->server;

                delete (yyvsp[-5].info);
                delete (yyvsp[-4].si);delete (yyvsp[-3].si);delete (yyvsp[-2].si);delete (yyvsp[-1].si);delete (yyvsp[0].si);
            }
#line 3721 "y.tab.c"
    break;

  case 46: /* declaration_list: declaration_list error COMMA ID LSQUARE CONST_FLOAT RSQUARE  */
#line 1738 "1805017.y"
                                                                           {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-6].info)->line_count;

                string text = getRuleString("declaration_list","declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE",(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(22,"declaration_list","declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE",text);

                (yyval.info)->root->children.push_back((yyvsp[-6].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-4].si));
                insertTOKEN((yyval.info),(yyvsp[-3].si));
                insertTOKEN((yyval.info),(yyvsp[-2].si));
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("declaration_list","declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE");

                // $$->symbols = $1->symbols;
                // $3->dataType = "ARRAY";
                // $$->symbols.push_back(*$4);

                // ArraySizeFloatError($6->line_count);

                // $$->server = $1->server;
                printSyntaxError("declaration list","variable declaration",(yyvsp[-6].info)->line_count);


                delete (yyvsp[-6].info);
                delete (yyvsp[-4].si);delete (yyvsp[-3].si);delete (yyvsp[-2].si);delete (yyvsp[-1].si);delete (yyvsp[0].si);
            }
#line 3756 "y.tab.c"
    break;

  case 47: /* declaration_list: ID  */
#line 1767 "1805017.y"
                  {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].si)->line_count;

                string text = getRuleString("declaration_list","ID",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(23,"declaration_list","ID",text);

                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("declaration_list","ID");

                (yyval.info)->symbols.push_back(*(yyvsp[0].si));

                delete (yyvsp[0].si);
        }
#line 3776 "y.tab.c"
    break;

  case 48: /* declaration_list: ID LSQUARE CONST_INT RSQUARE  */
#line 1781 "1805017.y"
                                        {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-3].si)->line_count;

                string text = getRuleString("declaration_list","ID LSQUARE CONST_INT RSQUARE",(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(24,"declaration_list","ID LSQUARE CONST_INT RSQUARE",text);

                insertTOKEN((yyval.info),(yyvsp[-3].si));
                insertTOKEN((yyval.info),(yyvsp[-2].si));
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("declaration_list","ID LSQUARE CONST_INT RSQUARE");
                (yyvsp[-3].si)->arraySize = stoi((yyvsp[-1].si)->name);
                // cout << "ttttttttt" << $1->arraySize << endl;
                (yyvsp[-3].si)->dataType = "ARRAY";
                (yyval.info)->symbols.push_back(*(yyvsp[-3].si));

                delete (yyvsp[-3].si);delete (yyvsp[-2].si);delete (yyvsp[-1].si);delete (yyvsp[0].si);            
        }
#line 3802 "y.tab.c"
    break;

  case 49: /* declaration_list: ID LSQUARE CONST_FLOAT RSQUARE  */
#line 1801 "1805017.y"
                                          {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-3].si)->line_count;

                string text = getRuleString("declaration_list","ID LSQUARE CONST_INT RSQUARE",(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(24,"declaration_list","ID LSQUARE CONST_INT RSQUARE",text);

                insertTOKEN((yyval.info),(yyvsp[-3].si));
                insertTOKEN((yyval.info),(yyvsp[-2].si));
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule("declaration_list","ID LSQUARE CONST_INT RSQUARE");

                (yyvsp[-3].si)->dataType = "ARRAY";
                (yyval.info)->symbols.push_back(*(yyvsp[-3].si));

                ArraySizeFloatError((yyvsp[-1].si)->line_count);

                delete (yyvsp[-3].si);delete (yyvsp[-2].si);delete (yyvsp[-1].si);delete (yyvsp[0].si);            
        }
#line 3829 "y.tab.c"
    break;

  case 50: /* statements: statement  */
#line 1825 "1805017.y"
                      {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string text = getRuleString("statements","statement",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(25,"statements","statement",text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule("statements","statement");
                printLabel(++asmLabel);
                (yyval.info)->nextList = (yyvsp[0].info)->nextList;
                delete (yyvsp[0].info);
        }
#line 3848 "y.tab.c"
    break;

  case 51: /* statements: statements statement  */
#line 1838 "1805017.y"
                               {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-1].info)->line_count;

                string text = getRuleString("statements","statements statement",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(26,"statements","statements statement",text);

                (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule("statements","statements statement");
                printLabel(++asmLabel);

                copy((yyvsp[-1].info)->nextList.begin(), (yyvsp[-1].info)->nextList.end(), back_inserter((yyval.info)->nextList));
                copy((yyvsp[0].info)->nextList.begin(), (yyvsp[0].info)->nextList.end(), std::back_inserter((yyval.info)->nextList));

                delete (yyvsp[-1].info);delete (yyvsp[0].info);

        }
#line 3872 "y.tab.c"
    break;

  case 52: /* statements: statements error statement  */
#line 1856 "1805017.y"
                                    {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-2].info)->line_count;

                string text = getRuleString("statements","statements error statement",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(26,"statements","statements error statement",text);

                (yyval.info)->root->children.push_back((yyvsp[-2].info)->root);
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule("statements","statements error statement");
                delete (yyvsp[-2].info);delete (yyvsp[0].info);

        }
#line 3891 "y.tab.c"
    break;

  case 53: /* statement: var_declaration  */
#line 1872 "1805017.y"
                           {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string text = getRuleString("statement","var_declaration",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(27,"statement","var_declaration",text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule("statement","var_declaration");
                delete (yyvsp[0].info);

        }
#line 3909 "y.tab.c"
    break;

  case 54: /* statement: expression_statement  */
#line 1884 "1805017.y"
                               {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string text = getRuleString("statement","expression_statement",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(28,"statement","expression_statement",text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                (yyval.info)->server = (yyvsp[0].info)->server;
                (yyval.info)->lexeme = (yyvsp[0].info)->lexeme;
                (yyval.info)->typeICG = (yyvsp[0].info)->typeICG;

                (yyval.info)->isRelExp = (yyvsp[0].info)->isRelExp;
                (yyval.info)->isBooleanExp = (yyvsp[0].info)->isBooleanExp;
                (yyval.info)->trueList = (yyvsp[0].info)->trueList;
                (yyval.info)->falseList = (yyvsp[0].info)->falseList;                                
                (yyval.info)->nextList = (yyvsp[0].info)->nextList;      

                printToLogRule("statement","expression_statement");
                delete (yyvsp[0].info);

        }
#line 3937 "y.tab.c"
    break;

  case 55: /* statement: func_declaration  */
#line 1906 "1805017.y"
                          {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string text = getRuleString("statement","func_declaration",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(-1,"statement","func_declaration",text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                //printToLogRule("statement","func_declaration");
                nestedFunctionError((yyvsp[0].info)->line_count);
                delete (yyvsp[0].info);

        }
#line 3956 "y.tab.c"
    break;

  case 56: /* statement: func_definition  */
#line 1919 "1805017.y"
                         {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string text = getRuleString("statement","func_definition",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(-1,"statement","func_definition",text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                //printToLogRule("statement","func_definition");
                nestedFunctionError((yyvsp[0].info)->line_count);
                delete (yyvsp[0].info);

        }
#line 3975 "y.tab.c"
    break;

  case 57: /* statement: compound_statement  */
#line 1932 "1805017.y"
                             {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string text = getRuleString("statement","compound_statement",(yyval.info)->line_count,line_count);
                (yyval.info)->root = new Node(29,"statement","compound_statement",text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                (yyval.info)->nextList = (yyvsp[0].info)->nextList;

                printToLogRule("statement","compound_statement");
                delete (yyvsp[0].info);

        }
#line 3995 "y.tab.c"
    break;

  case 58: /* $@5: %empty  */
#line 1946 "1805017.y"
                                                                               {printCmd("POP AX\n");printCmd("JMP L" + (yyvsp[-3].info)->label + "\n");}
#line 4001 "y.tab.c"
    break;

  case 59: /* statement: FOR LPAREN expression_statement m expression_statement p expression $@5 RPAREN m statement  */
#line 1946 "1805017.y"
                                                                                                                                                              {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-10].si)->line_count;

                string head = "statement";
                string body = "FOR LPAREN expression_statement expression_statement expression RPAREN statement";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(30,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[-10].si));
                insertTOKEN((yyval.info),(yyvsp[-9].si));
                (yyval.info)->root->children.push_back((yyvsp[-8].info)->root);
                (yyval.info)->root->children.push_back((yyvsp[-6].info)->root);
                (yyval.info)->root->children.push_back((yyvsp[-4].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-2].si));
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);


                printCmd("JMP L" + (yyvsp[-5].info)->label + "\n");
                printLabel(++asmLabel);
                backPatch((yyvsp[-6].info)->falseList,to_string(asmLabel));
                backPatch((yyvsp[-6].info)->trueList,(yyvsp[-1].info)->label);


                delete (yyvsp[-8].info);delete (yyvsp[-7].info);delete (yyvsp[-6].info);delete (yyvsp[-4].info);delete (yyvsp[-1].info);delete (yyvsp[0].info);
                delete (yyvsp[-10].si);delete (yyvsp[-9].si);delete (yyvsp[-5].info);delete (yyvsp[-2].si);

        }
#line 4038 "y.tab.c"
    break;

  case 60: /* statement: IF LPAREN expression RPAREN p statement  */
#line 1977 "1805017.y"
                                                                        {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-5].si)->line_count;

                string head = "statement";
                string body = "IF LPAREN expression RPAREN statement";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(31,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[-5].si));
                insertTOKEN((yyval.info),(yyvsp[-4].si));
                (yyval.info)->root->children.push_back((yyvsp[-3].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-2].si));
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);
                

                // cout << $3->isBooleanExp << " " << $3->isRelExp << endl;

                backPatch((yyvsp[-3].info)->trueList,(yyvsp[-1].info)->label);
                // printLabel(++asmLabel);
                backPatch((yyvsp[-3].info)->falseList,to_string(asmLabel));

                (yyval.info)->nextList = (yyvsp[0].info)->nextList;

                delete (yyvsp[-3].info);delete (yyvsp[0].info);
                delete (yyvsp[-5].si);delete (yyvsp[-4].si);delete (yyvsp[-2].si);
        }
#line 4074 "y.tab.c"
    break;

  case 61: /* statement: IF LPAREN expression RPAREN p statement ELSE n m statement  */
#line 2007 "1805017.y"
                                                                     {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-9].si)->line_count;

                string head = "statement";
                string body = "IF LPAREN expression RPAREN statement ELSE statement";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(32,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[-9].si));
                insertTOKEN((yyval.info),(yyvsp[-8].si));
                (yyval.info)->root->children.push_back((yyvsp[-7].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-6].si));
                (yyval.info)->root->children.push_back((yyvsp[-4].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-3].si));
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                backPatch((yyvsp[-7].info)->trueList,(yyvsp[-5].info)->label);
                // printLabel(++asmLabel);
                backPatch((yyvsp[-7].info)->falseList,(yyvsp[-1].info)->label);
                backPatch((yyvsp[-2].info)->nextList,to_string(asmLabel));

                copy((yyvsp[-4].info)->nextList.begin(), (yyvsp[-4].info)->nextList.end(), back_inserter((yyval.info)->nextList));
                copy((yyvsp[0].info)->nextList.begin(), (yyvsp[0].info)->nextList.end(), std::back_inserter((yyval.info)->nextList));

                delete (yyvsp[-7].info);delete (yyvsp[-4].info);delete (yyvsp[0].info);delete (yyvsp[-1].info);delete (yyvsp[-3].si);
                delete (yyvsp[-9].si);delete (yyvsp[-8].si);delete (yyvsp[-6].si);delete (yyvsp[-2].info);delete (yyvsp[-5].info);

        }
#line 4112 "y.tab.c"
    break;

  case 62: /* statement: WHILE m LPAREN expression RPAREN p statement  */
#line 2039 "1805017.y"
                                                       {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-6].si)->line_count;

                string head = "statement";
                string body = "WHILE LPAREN expression RPAREN statement";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(33,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[-6].si));
                insertTOKEN((yyval.info),(yyvsp[-4].si));
                (yyval.info)->root->children.push_back((yyvsp[-3].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-2].si));
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                backPatch((yyvsp[-3].info)->trueList,(yyvsp[-1].info)->label);

                printCmd("JMP L" + (yyvsp[-5].info)->label + "\n");
                printLabel(++asmLabel);
                backPatch((yyvsp[-3].info)->falseList,to_string(asmLabel));

                delete (yyvsp[-4].si);delete (yyvsp[-2].si);delete (yyvsp[-1].info);delete (yyvsp[0].info);
                delete (yyvsp[-6].si);delete (yyvsp[-5].info);delete (yyvsp[-3].info);

        }
#line 4146 "y.tab.c"
    break;

  case 63: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 2067 "1805017.y"
                                             {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-4].si)->line_count;

                string head = "statement";
                string body = "PRINTLN LPAREN ID RPAREN SEMICOLON";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(34,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[-4].si));
                insertTOKEN((yyval.info),(yyvsp[-3].si));
                insertTOKEN((yyval.info),(yyvsp[-2].si));
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule(head,body);

                if( !st->lookUpSymbol((yyvsp[-2].si)->name) ){
                    undeclaredVariableError((yyvsp[-2].si)->name,(yyvsp[-2].si)->line_count);
                    (yyval.info)->server = "UNDEFINED";
                }

                Info temp;
                temp.lexeme = (yyvsp[-2].si)->name;
                temp.typeICG = "variable";
                loadVariablesCode(&temp);
                printCmd("CALL print_output\n");
                printCmd("CALL new_line\n");

                delete (yyvsp[-4].si);delete (yyvsp[-3].si);delete (yyvsp[-2].si);delete (yyvsp[-1].si);delete (yyvsp[0].si);

        }
#line 4185 "y.tab.c"
    break;

  case 64: /* statement: RETURN expression SEMICOLON  */
#line 2100 "1805017.y"
                                      {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-2].si)->line_count;

                string head = "statement";
                string body = "RETURN expression SEMICOLON";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(35,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[-2].si));
                (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule(head,body);

                //cout << $2->server << endl;
                if(!isFuncNow){
                    
                }else{
                    // cout << "herh" << endl;
                    checkReturnType((yyvsp[-1].info));
                    currFunc.returnFlag = true;
                    loadVariablesCode((yyvsp[-1].info));
                    printCmd("JMP L\n");
                    (yyval.info)->nextList.push_back(tempAsmLineCount);
                }

                (yyval.info)->server = (yyvsp[-1].info)->server;
                (yyval.info)->lexeme = (yyvsp[-1].info)->lexeme;
                (yyval.info)->typeICG = (yyvsp[-1].info)->typeICG;

                (yyval.info)->isRelExp = (yyvsp[-1].info)->isRelExp;
                (yyval.info)->isBooleanExp = (yyvsp[-1].info)->isBooleanExp;
                (yyval.info)->trueList = (yyvsp[-1].info)->trueList;
                (yyval.info)->falseList = (yyvsp[-1].info)->falseList;                                
                (yyval.info)->nextList = (yyvsp[-1].info)->nextList;      
                

                delete (yyvsp[-1].info);
                delete (yyvsp[-2].si);delete (yyvsp[0].si);

        }
#line 4234 "y.tab.c"
    break;

  case 65: /* n: %empty  */
#line 2146 "1805017.y"
     { (yyval.info) = new Info();
    printCmd("JMP L\n");(yyval.info)->nextList.push_back(tempAsmLineCount);
    }
#line 4242 "y.tab.c"
    break;

  case 66: /* expression_statement: SEMICOLON  */
#line 2152 "1805017.y"
                                   {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].si)->line_count;

                string head = "expression_statement";
                string body = "SEMICOLON";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(36,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule(head,body);

                delete (yyvsp[0].si);
        }
#line 4264 "y.tab.c"
    break;

  case 67: /* expression_statement: expression SEMICOLON  */
#line 2168 "1805017.y"
                               {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-1].info)->line_count;

                string head = "expression_statement";
                string body = "expression SEMICOLON";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(37,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule(head,body);
                cout <<  "--------" << (yyvsp[-1].info)->isBooleanExp << " " << (yyvsp[-1].info)->isRelExp << endl;
                if( !(yyvsp[-1].info)->isBooleanExp && !(yyvsp[-1].info)->isRelExp )
                    printCmd("POP AX\n");

                (yyval.info)->server = (yyvsp[-1].info)->server;
                (yyval.info)->lexeme = (yyvsp[-1].info)->lexeme;
                (yyval.info)->typeICG = (yyvsp[-1].info)->typeICG;

                (yyval.info)->isRelExp = (yyvsp[-1].info)->isRelExp;
                (yyval.info)->trueList = (yyvsp[-1].info)->trueList;
                (yyval.info)->falseList = (yyvsp[-1].info)->falseList;
                (yyval.info)->nextList = (yyvsp[-1].info)->nextList;
                (yyval.info)->isBooleanExp = (yyvsp[-1].info)->isBooleanExp;

                expNow = (yyval.info);
                expNow->isExp = true;

                delete (yyvsp[-1].info);
                delete (yyvsp[0].si);
        }
#line 4304 "y.tab.c"
    break;

  case 68: /* expression_statement: expression error SEMICOLON  */
#line 2202 "1805017.y"
                                     {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-2].info)->line_count;

                string head = "expression_statement";
                string body = "expression error SEMICOLON";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(37,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[-2].info)->root);
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule(head,body);

                printSyntaxError("expression","expression statement",(yyvsp[-2].info)->line_count);

                delete (yyvsp[-2].info);
                delete (yyvsp[0].si);
        }
#line 4330 "y.tab.c"
    break;

  case 69: /* variable: ID  */
#line 2225 "1805017.y"
             {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].si)->line_count;

                string head = "variable";
                string body = "ID";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(38,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule(head,body);

                SymbolInfo* si = st->lookUpSymbol((yyvsp[0].si)->name);
                if( !si ){
                    undeclaredVariableError((yyvsp[0].si)->name,(yyvsp[0].si)->line_count);
                    (yyval.info)->server = "UNDEFINED";
                }else{
                    if( si->dataType == "INT_ARRAY" || si->dataType == "FLOAT_ARRAY" ){
                        //isArrayError($1->name,$1->line_count);
                        //$$->server = "UNDEFINED";
                    }else{
                        (yyval.info)->server = si->dataType;
                    }

                    (yyval.info)->lexeme = (yyvsp[0].si)->name;
                    (yyval.info)->typeICG = "variable";
                }

                delete (yyvsp[0].si);

        }
#line 4369 "y.tab.c"
    break;

  case 70: /* variable: ID LSQUARE expression RSQUARE  */
#line 2258 "1805017.y"
                                        {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-3].si)->line_count;

                string head = "variable";
                string body = "ID LSQUARE expression RSQUARE";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(39,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[-3].si));
                insertTOKEN((yyval.info),(yyvsp[-2].si));
                (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule(head,body);

                SymbolInfo* si = st->lookUpSymbol((yyvsp[-3].si)->name);
                if( !si ){
                    undeclaredVariableError((yyvsp[-3].si)->name,(yyvsp[-3].si)->line_count);
                    (yyval.info)->server = "UNDEFINED";

                }else{
                    if( si->dataType == "INT" || si->dataType == "FLOAT" ){
                        isNotArrayError((yyvsp[-3].si)->name,(yyvsp[-3].si)->line_count);
                        (yyval.info)->server = "UNDEFINED";

                    }else{
                        (yyval.info)->server = si->dataType; 
                        (yyval.info)->lexeme = (yyvsp[-3].si)->name;
                        (yyval.info)->typeICG = "INT_ARRAY";
                        (yyval.info)->arrIndx = (yyvsp[-1].info)->lexeme;

                        SymbolInfo* si = st->lookUpSymbol((yyvsp[-3].si)->name);
                        if(si != nullptr){
                            if( (yyvsp[-1].info)->lexeme == "NULL" ){
                                printCmd("POP AX\n");
                                printCmd("MOV SI, AX\n");
                            }else
                                printCmd("MOV SI, " + (yyvsp[-1].info)->lexeme + "\n");

                            printCmd("PUSH SI\n");
                            
                        }
                    }
                }

                if((yyvsp[-1].info)->server != "INT"){
                    invalidArrayIndexError((yyvsp[-1].info)->line_count);
                }

                delete (yyvsp[-1].info);
                delete (yyvsp[-3].si);delete (yyvsp[-2].si);delete (yyvsp[0].si);
        }
#line 4429 "y.tab.c"
    break;

  case 71: /* expression: logic_expression  */
#line 2315 "1805017.y"
                              {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string head = "expression";
                string body = "logic_expression";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(40,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                (yyval.info)->server = (yyvsp[0].info)->server;
                (yyval.info)->lexeme = (yyvsp[0].info)->lexeme;
                (yyval.info)->typeICG = (yyvsp[0].info)->typeICG;
                (yyval.info)->isRelExp = (yyvsp[0].info)->isRelExp;
                (yyval.info)->trueList = (yyvsp[0].info)->trueList;
                (yyval.info)->falseList = (yyvsp[0].info)->falseList;
                (yyval.info)->isBooleanExp = (yyvsp[0].info)->isBooleanExp;

                expNow = (yyval.info);
                expNow->isExp = true;

                delete (yyvsp[0].info);

        }
#line 4463 "y.tab.c"
    break;

  case 72: /* expression: variable ASSIGNOP logic_expression  */
#line 2343 "1805017.y"
                                             {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-2].info)->line_count;

                string head = "expression";
                string body = "variable ASSIGNOP logic_expression";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(41,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[-2].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                verifyAssignop((yyval.info),(yyvsp[-2].info),(yyvsp[0].info));
            
                (yyval.info)->lexeme = "NULL";

                loadLogicCode2((yyvsp[0].info));
                loadRelCode((yyvsp[0].info));

                if( (yyvsp[0].info)->isRelExp ){
                    printLabel(++asmLabel);
                    backPatch((yyvsp[0].info)->trueList,to_string(asmLabel));
                    printCmd("MOV AX, 1\n");
                    printCmd("JMP L" +  to_string(asmLabel+2) + "\n");
                    printLabel(++asmLabel);
                    backPatch((yyvsp[0].info)->falseList,to_string(asmLabel));
                    printCmd("MOV AX, 0\n");
                    printLabel(++asmLabel);
                    printCmd("PUSH AX\n");               
                }
                

                loadVariablesCode((yyvsp[0].info));
                
                // cout << "-------" << $1->lexeme << " " << $1->typeICG <<  endl;
                
                loadAssignCode((yyvsp[-2].info));

                printCmd("PUSH AX\n");

                delete (yyvsp[-2].info);delete (yyvsp[0].info);
                delete (yyvsp[-1].si);
        }
#line 4516 "y.tab.c"
    break;

  case 73: /* logic_expression: rel_expression  */
#line 2395 "1805017.y"
                                 {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string head = "logic_expression";
                string body = "rel_expression";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(42,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                (yyval.info)->server = (yyvsp[0].info)->server;
                (yyval.info)->lexeme = (yyvsp[0].info)->lexeme;
                (yyval.info)->typeICG = (yyvsp[0].info)->typeICG;

                (yyval.info)->isRelExp = (yyvsp[0].info)->isRelExp;
                (yyval.info)->trueList = (yyvsp[0].info)->trueList;
                (yyval.info)->falseList = (yyvsp[0].info)->falseList;
                (yyval.info)->nextList = (yyvsp[0].info)->nextList;
                (yyval.info)->isBooleanExp = (yyvsp[0].info)->isBooleanExp;

                delete (yyvsp[0].info);
        }
#line 4548 "y.tab.c"
    break;

  case 74: /* $@6: %empty  */
#line 2421 "1805017.y"
                                  {loadLogicCode((yyvsp[-1].info),(yyvsp[0].si));}
#line 4554 "y.tab.c"
    break;

  case 75: /* logic_expression: rel_expression LOGICOP $@6 m rel_expression  */
#line 2421 "1805017.y"
                                                                          {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-4].info)->line_count;

                string head = "logic_expression";
                string body = "rel_expression LOGICOP rel_expression";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(43,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[-4].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-3].si));
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                logicalTypecast((yyval.info),(yyvsp[-4].info),(yyvsp[0].info));

                // printLabel(++asmLabel);
                loadLogicCode((yyvsp[0].info),(yyvsp[-3].si));
                (yyval.info)->lexeme = "NULL";

                // string trueLabel = to_string(++asmLabel);
                // printLabel(asmLabel);
                // printCmd("MOV AX, 1\n");
                // printCmd("JMP L" +  to_string(asmLabel+2) + "\n");
                // string falseLabel = to_string(++asmLabel);
                // printLabel(asmLabel);
                // printCmd("MOV AX, 0\n");
                // printLabel(++asmLabel);
                // printCmd("PUSH AX\n");

                if( (yyvsp[-3].si)->name == "||" ){
                    copy((yyvsp[-4].info)->trueList.begin(), (yyvsp[-4].info)->trueList.end(), back_inserter((yyval.info)->trueList));
                    copy((yyvsp[0].info)->trueList.begin(), (yyvsp[0].info)->trueList.end(), std::back_inserter((yyval.info)->trueList));
                    (yyval.info)->falseList = (yyvsp[0].info)->falseList;                    
                    
                    backPatch((yyvsp[-4].info)->falseList,(yyvsp[-1].info)->label);
                    // backPatch($1->trueList,trueLabel);
                    // backPatch($5->falseList,falseLabel);
                    // backPatch($5->trueList,trueLabel);

                }else if( (yyvsp[-3].si)->name == "&&" ){
                    (yyval.info)->trueList = (yyvsp[0].info)->trueList;
                    copy((yyvsp[-4].info)->falseList.begin(), (yyvsp[-4].info)->falseList.end(), back_inserter((yyval.info)->falseList));
                    copy((yyvsp[0].info)->falseList.begin(), (yyvsp[0].info)->falseList.end(), std::back_inserter((yyval.info)->falseList));                    
                    // backPatch($1->falseList,falseLabel);
                    backPatch((yyvsp[-4].info)->trueList,(yyvsp[-1].info)->label);
                    // backPatch($5->falseList,falseLabel);
                    // backPatch($5->trueList,trueLabel);     

                }

                (yyval.info)->isBooleanExp = true;
                
                delete (yyvsp[-4].info);delete (yyvsp[0].info);
                delete (yyvsp[-3].si);delete (yyvsp[-1].info);
        }
#line 4618 "y.tab.c"
    break;

  case 76: /* m: %empty  */
#line 2482 "1805017.y"
     {
    (yyval.info) = new Info();
    (yyval.info)->label = to_string(++asmLabel);
    printLabel(asmLabel);

}
#line 4629 "y.tab.c"
    break;

  case 77: /* p: %empty  */
#line 2489 "1805017.y"
    {

    if( expNow != nullptr ){
        if( expNow->isExp ){
            loadExpCode(expNow);
        }
    }

    (yyval.info) = new Info();
    (yyval.info)->label = to_string(++asmLabel);
    printLabel(asmLabel);
    
}
#line 4647 "y.tab.c"
    break;

  case 78: /* rel_expression: simple_expression  */
#line 2504 "1805017.y"
                                   {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string head = "rel_expression";
                string body = "simple_expression";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(44,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                (yyval.info)->server = (yyvsp[0].info)->server;
                (yyval.info)->lexeme = (yyvsp[0].info)->lexeme;
                (yyval.info)->typeICG = (yyvsp[0].info)->typeICG;
                

                (yyval.info)->isRelExp = (yyvsp[0].info)->isRelExp;
                (yyval.info)->isBooleanExp = (yyvsp[0].info)->isBooleanExp;
                (yyval.info)->trueList = (yyvsp[0].info)->trueList;
                (yyval.info)->falseList = (yyvsp[0].info)->falseList;                                
                (yyval.info)->nextList = (yyvsp[0].info)->nextList;                   

                delete (yyvsp[0].info);
        }
#line 4680 "y.tab.c"
    break;

  case 79: /* $@7: %empty  */
#line 2532 "1805017.y"
                                    {loadLogicCode2((yyvsp[0].info));loadRelCode((yyvsp[0].info));}
#line 4686 "y.tab.c"
    break;

  case 80: /* rel_expression: simple_expression $@7 RELOP simple_expression  */
#line 2532 "1805017.y"
                                                                                                 {
                //cout << "HERE2\n";
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-3].info)->line_count;

                string head = "rel_expression";
                string body = "simple_expression RELOP simple_expression";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(45,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[-3].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                logicalTypecast((yyval.info),(yyvsp[-3].info),(yyvsp[0].info));

                // $$->lexeme = $1->lexeme;

                (yyval.info)->lexeme = "NULL";
                (yyval.info)->isRelExp = true;

                // cout << "------------" << $1->lexeme << endl;
                loadRelCode((yyvsp[0].info));                
                loadLogicCode2((yyvsp[0].info));
                loadVariablesCode((yyvsp[0].info));
                printCmd("MOV DX, AX\n"); 
                // cout << "-------" << $1->lexeme << " " << $1->typeICG <<  endl;
                loadVariablesCode((yyvsp[-3].info));
                printCmd("CMP AX, DX\n");

                if( (yyvsp[-1].si)->name == "<" ){
                    printCmd("JL L\n");
                }else if( (yyvsp[-1].si)->name == "<=" ){
                    printCmd("JLE L\n");
                }else if( (yyvsp[-1].si)->name == "==" ){
                    printCmd("JE L\n");
                }else if( (yyvsp[-1].si)->name == "!=" ){
                    printCmd("JNE L\n");
                }else if( (yyvsp[-1].si)->name == ">=" ){
                    printCmd("JGE L\n");
                }else if( (yyvsp[-1].si)->name == ">" ){
                    printCmd("JG L\n");
                }

                (yyval.info)->trueList.push_back(tempAsmLineCount);
                
                printCmd("JMP L\n");
                (yyval.info)->falseList.push_back(tempAsmLineCount);

                // printLabel(++asmLabel);
                // printCmd("MOV AX, 1\n");
                // printCmd("JMP L" +  to_string(asmLabel+2) + "\n");
                // printLabel(++asmLabel);
                // printCmd("MOV AX, 0\n");
                // printLabel(++asmLabel);
                // printCmd("PUSH AX\n");

                delete (yyvsp[-3].info);delete (yyvsp[0].info);
                delete (yyvsp[-1].si);
        }
#line 4755 "y.tab.c"
    break;

  case 81: /* simple_expression: term  */
#line 2598 "1805017.y"
                        {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string head = "simple_expression";
                string body = "term";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(46,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                (yyval.info)->server = (yyvsp[0].info)->server;
                (yyval.info)->lexeme = (yyvsp[0].info)->lexeme;
                (yyval.info)->typeICG = (yyvsp[0].info)->typeICG;

                (yyval.info)->isRelExp = (yyvsp[0].info)->isRelExp;
                (yyval.info)->isBooleanExp = (yyvsp[0].info)->isBooleanExp;
                (yyval.info)->trueList = (yyvsp[0].info)->trueList;
                (yyval.info)->falseList = (yyvsp[0].info)->falseList;                                
                (yyval.info)->nextList = (yyvsp[0].info)->nextList;      

                delete (yyvsp[0].info);
        }
#line 4787 "y.tab.c"
    break;

  case 82: /* $@8: %empty  */
#line 2624 "1805017.y"
                             {loadLogicCode2((yyvsp[0].info));loadRelCode((yyvsp[0].info));}
#line 4793 "y.tab.c"
    break;

  case 83: /* simple_expression: simple_expression $@8 ADDOP term  */
#line 2624 "1805017.y"
                                                                             {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-3].info)->line_count;

                string head = "simple_expression";
                string body = "simple_expression ADDOP term";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(47,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[-3].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                arithmeticTypecast((yyval.info),(yyvsp[-3].info),(yyvsp[0].info));


                (yyval.info)->lexeme = "NULL";
                // cout << "-------" << $3->lexeme << " " << $3->typeICG <<  endl;
                loadRelCode((yyvsp[0].info));                
                loadLogicCode2((yyvsp[0].info));
                loadVariablesCode((yyvsp[0].info));
                
                printCmd("MOV DX, AX\n"); 

                // cout << "-------" << $1->lexeme << " " << $1->typeICG <<  endl;

                loadVariablesCode((yyvsp[-3].info));

                if( (yyvsp[-1].si)->name == "+" ){
                    printCmd("ADD AX, DX\n");
                }else if( (yyvsp[-1].si)->name == "-" ){
                    printCmd("SUB AX, DX\n");
                }

                printCmd("PUSH AX\n");

                delete (yyvsp[-3].info);delete (yyvsp[0].info);
                delete (yyvsp[-1].si);
        }
#line 4841 "y.tab.c"
    break;

  case 84: /* term: unary_expression  */
#line 2669 "1805017.y"
                        {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string head = "term";
                string body = "unary_expression";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(48,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                (yyval.info)->server = (yyvsp[0].info)->server;
                (yyval.info)->lexeme = (yyvsp[0].info)->lexeme;
                (yyval.info)->typeICG = (yyvsp[0].info)->typeICG;
                
                (yyval.info)->isRelExp = (yyvsp[0].info)->isRelExp;
                (yyval.info)->isBooleanExp = (yyvsp[0].info)->isBooleanExp;
                (yyval.info)->trueList = (yyvsp[0].info)->trueList;
                (yyval.info)->falseList = (yyvsp[0].info)->falseList;                                
                (yyval.info)->nextList = (yyvsp[0].info)->nextList;                    

                delete (yyvsp[0].info);

        }
#line 4874 "y.tab.c"
    break;

  case 85: /* $@9: %empty  */
#line 2696 "1805017.y"
                {loadLogicCode2((yyvsp[0].info));loadRelCode((yyvsp[0].info));}
#line 4880 "y.tab.c"
    break;

  case 86: /* term: term $@9 MULOP unary_expression  */
#line 2696 "1805017.y"
                                                                            {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-3].info)->line_count;

                string head = "term";
                string body = "term MULOP unary_expression";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(49,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[-3].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                if((yyvsp[-1].si)->name == "%" || (yyvsp[-1].si)->name == "/"){
                    if((yyvsp[0].info)->lexeme == "0"){
                        divideByZeroError((yyvsp[0].info)->line_count);
                        (yyval.info)->server = "UNDEFINED";
                    }else
                        modTypecast((yyval.info),(yyvsp[-3].info),(yyvsp[0].info));
                    
                }else{
                    arithmeticTypecast((yyval.info),(yyvsp[-3].info),(yyvsp[0].info));
                }

                (yyval.info)->lexeme = "NULL";
                // cout << "-------" << $3->lexeme << " " << $3->typeICG <<  endl;
                loadRelCode((yyvsp[0].info));
                loadLogicCode2((yyvsp[0].info));
                loadVariablesCode((yyvsp[0].info));
                
                printCmd("MOV CX, AX\n"); 

                // cout << "-------" << $1->lexeme << " " << $1->typeICG <<  endl;

                loadVariablesCode((yyvsp[-3].info));

                printCmd("CWD\n");
                if( (yyvsp[-1].si)->name == "*" ){
                    printCmd("MUL CX\n");
                    printCmd("PUSH AX\n");
                }else if( (yyvsp[-1].si)->name == "/" ){
                    printCmd("DIV CX\n");
                    printCmd("PUSH AX\n");
                }else if( (yyvsp[-1].si)->name == "%" ){
                    printCmd("DIV CX\n");
                    printCmd("PUSH DX\n");
                }
                

                delete (yyvsp[-3].info);delete (yyvsp[0].info);
                delete (yyvsp[-1].si);
        }
#line 4941 "y.tab.c"
    break;

  case 87: /* unary_expression: ADDOP unary_expression  */
#line 2754 "1805017.y"
                                         {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-1].si)->line_count;

                string head = "unary_expression";
                string body = "ADDOP unary_expression";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(50,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[-1].si));
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                (yyval.info)->server = (yyvsp[0].info)->server;

                loadRelCode((yyvsp[0].info));
                loadLogicCode2((yyvsp[0].info));
                loadVariablesCode((yyvsp[0].info));
                if( (yyvsp[-1].si)->name == "-" ){
                    printCmd("NEG AX\n");
                }

                printCmd("PUSH AX\n");

                (yyval.info)->lexeme = "NULL";

                delete (yyvsp[0].info);
                delete (yyvsp[-1].si);
        }
#line 4978 "y.tab.c"
    break;

  case 88: /* unary_expression: NOT unary_expression  */
#line 2785 "1805017.y"
                               {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-1].si)->line_count;

                string head = "unary_expression";
                string body = "NOT unary_expression";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(51,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[-1].si));
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                (yyval.info)->server = (yyvsp[0].info)->server;
                (yyval.info)->lexeme = "NULL";

                // loadRelCode($2);
                // loadLogicCode2($2);
                // printCmd("CMP AX, 0\n");
                // printCmd("JE L" + to_string(asmLabel+1)+ "\n");
                // printCmd("JMP L" + to_string(asmLabel+2)+ "\n");
                // printLabel(++asmLabel);
                // printCmd("MOV AX, 1\n");
                // printCmd("JMP L" + to_string(asmLabel+2) + "\n");
                // printLabel(++asmLabel);
                // printCmd("MOV AX, 0\n");
                // printLabel(++asmLabel);
                // printCmd("PUSH AX\n");

                loadLogicCode3((yyvsp[0].info));

                (yyval.info)->isRelExp = (yyvsp[0].info)->isRelExp;
                (yyval.info)->isBooleanExp = true;
                (yyval.info)->trueList = (yyvsp[0].info)->falseList;
                (yyval.info)->falseList = (yyvsp[0].info)->trueList;                                
                (yyval.info)->nextList = (yyvsp[0].info)->nextList;      

                delete (yyvsp[0].info);
                delete (yyvsp[-1].si);
        }
#line 5026 "y.tab.c"
    break;

  case 89: /* unary_expression: factor  */
#line 2827 "1805017.y"
                 {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string head = "unary_expression";
                string body = "factor";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(52,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                (yyval.info)->server = (yyvsp[0].info)->server;
                (yyval.info)->lexeme = (yyvsp[0].info)->lexeme;
                (yyval.info)->typeICG = (yyvsp[0].info)->typeICG;

                (yyval.info)->isRelExp = (yyvsp[0].info)->isRelExp;
                (yyval.info)->isBooleanExp = (yyvsp[0].info)->isBooleanExp;
                (yyval.info)->trueList = (yyvsp[0].info)->trueList;
                (yyval.info)->falseList = (yyvsp[0].info)->falseList;                                
                (yyval.info)->nextList = (yyvsp[0].info)->nextList;       

                delete (yyvsp[0].info);

        }
#line 5059 "y.tab.c"
    break;

  case 90: /* factor: variable  */
#line 2857 "1805017.y"
                  {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string head = "factor";
                string body = "variable";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(53,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                (yyval.info)->server = (yyvsp[0].info)->server;
                (yyval.info)->lexeme = (yyvsp[0].info)->lexeme;
                (yyval.info)->typeICG = (yyvsp[0].info)->typeICG;

                delete (yyvsp[0].info);
        }
#line 5085 "y.tab.c"
    break;

  case 91: /* factor: ID LPAREN argument_list RPAREN  */
#line 2877 "1805017.y"
                                         {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-3].si)->line_count;

                string head = "factor";
                string body = "ID LPAREN argument_list RPAREN";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(54,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[-3].si));
                insertTOKEN((yyval.info),(yyvsp[-2].si));
                (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule(head,body);

                SymbolInfo* si = st->lookUpSymbol((yyvsp[-3].si)->name);
                if(!si){
                    undeclaredFunctionError((yyvsp[-3].si)->name,(yyvsp[-3].si)->line_count);
                    (yyval.info)->server = "UNDEFINED";
                }else{
                    if(!si->isFunction){
                        (yyval.info)->server = "UNDEFINED";
                        isNotFunctionError((yyvsp[-3].si)->name,(yyvsp[-3].si)->line_count);
                    }else{
                        (yyval.info)->server = si->dataType;

                        if(si->isFunctionDeclared){
                            undefinedFunctionError((yyvsp[-3].si)->name,(yyvsp[-3].si)->line_count);
                        }else{
                            if( si->params.size() != (yyvsp[-1].info)->arguments.size() ){
                                NumberOfArgumentsMismatchErrorFunc(si->name,(yyvsp[-3].si)->line_count,si->params.size() > (yyvsp[-1].info)->arguments.size());
                            }else{
                                int argumentNum = si->params.size();
                                for(int i = 0;i < argumentNum;i++){
                                    if( !argumentTypeCast((yyvsp[-1].info)->arguments[i],si->params[i]) ){
                                        argumentTypeCastError(si->name,i+1,(yyvsp[-3].si)->line_count);
                                    }
                                }
                            }
                        }
                    }
                }

                printCmd("CALL " + (yyvsp[-3].si)->name + "\n");
                printCmd("PUSH AX\n");
                (yyval.info)->lexeme = "NULL";
                delete (yyvsp[-1].info);
                delete (yyvsp[-3].si);delete (yyvsp[-2].si);delete (yyvsp[0].si);
        }
#line 5142 "y.tab.c"
    break;

  case 92: /* factor: LPAREN expression RPAREN  */
#line 2928 "1805017.y"
                                   {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-2].si)->line_count;

                string head = "factor";
                string body = "LPAREN expression RPAREN";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(55,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[-2].si));
                (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule(head,body);

                (yyval.info)->server = (yyvsp[-1].info)->server;
                // cout << "------------" << $2->lexeme << endl;

                (yyval.info)->lexeme = (yyvsp[-1].info)->lexeme;
                (yyval.info)->typeICG = (yyvsp[-1].info)->typeICG;

                

                (yyval.info)->isRelExp = (yyvsp[-1].info)->isRelExp;
                (yyval.info)->isBooleanExp = (yyvsp[-1].info)->isBooleanExp;
                (yyval.info)->trueList = (yyvsp[-1].info)->trueList;
                (yyval.info)->falseList = (yyvsp[-1].info)->falseList;                                
                (yyval.info)->nextList = (yyvsp[-1].info)->nextList;                                

                delete (yyvsp[-1].info);
                delete (yyvsp[-2].si);delete (yyvsp[0].si);
        }
#line 5181 "y.tab.c"
    break;

  case 93: /* factor: CONST_INT  */
#line 2961 "1805017.y"
                    {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].si)->line_count;

                string head = "factor";
                string body = "CONST_INT";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(56,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule(head,body);

                (yyval.info)->server = "INT";
                (yyval.info)->lexeme = (yyvsp[0].si)->name;
                (yyval.info)->typeICG = "CONST_INT";

                // tempAsmOut << "MOV AX, " << $1->name << "\n";

                delete (yyvsp[0].si);

        }
#line 5210 "y.tab.c"
    break;

  case 94: /* factor: CONST_FLOAT  */
#line 2984 "1805017.y"
                      {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].si)->line_count;

                string head = "factor";
                string body = "CONST_FLOAT";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(57,head,body,text);

                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule(head,body);

                (yyval.info)->server = "FLOAT";
                (yyval.info)->lexeme = (yyvsp[0].si)->name;

                delete (yyvsp[0].si);

        }
#line 5236 "y.tab.c"
    break;

  case 95: /* factor: variable INCOP  */
#line 3004 "1805017.y"
                         {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-1].info)->line_count;

                string head = "factor";
                string body = "variable INCOP";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(58,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[-1].info)->root);
                insertTOKEN((yyval.info),(yyvsp[0].si));

                printToLogRule(head,body);

                
                loadVariablesCode((yyvsp[-1].info));
                printCmd("PUSH AX\n");

                if( (yyvsp[0].si)->name == "++" ){
                    printCmd("INC AX\n");
                }else if((yyvsp[0].si)->name == "--"){
                    printCmd("DEC AX\n");
                }

                SymbolInfo* si = st->lookUpSymbol((yyvsp[-1].info)->lexeme);

                if(si != nullptr){
                    if( (yyvsp[-1].info)->typeICG == "variable" ){
                        if( si->isGlobal ){
                            printCmd("MOV " + si->name + ", AX\n");
                        }else{
                            if(si->isParam){
                                printCmd("MOV [BP+" + to_string(si->stackPos) + "], AX\n");
                            }else
                                printCmd("MOV [BP-" + to_string(si->stackPos) + "], AX\n");
                        }
                    }else if( (yyvsp[-1].info)->typeICG == "INT_ARRAY" ) {
                        if( si->isGlobal ){      
                            // printCmd()"POP SI\n";              
                            printCmd("MOV " + si->name + "[SI], AX\n");
                        }else{
                            // printCmd()"PUSH AX\n";
                            // printCmd()"POP SI\n";
                            // printCmd()"MOV AX, SI\n";
                            // printCmd()"MOV CX, 2\n";
                            // printCmd()"CWD\n";
                            // printCmd()"MUL CX\n";
                            // printCmd()"MOV SI, AX\n";
                            // printCmd()"ADD SI, " + si->stackPos + "\n";
                            printCmd("PUSH BP\n");
                            printCmd("SUB BP, SI\n");
                            // printCmd()"POP AX\n";
                            printCmd("MOV [BP], AX\n");
                            printCmd("POP BP\n");
                        }
                    }
                    
                }


                (yyval.info)->lexeme = "NULL";

                delete (yyvsp[-1].info);
                delete (yyvsp[0].si);
        }
#line 5308 "y.tab.c"
    break;

  case 96: /* argument_list: arguments  */
#line 3073 "1805017.y"
                         {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string head = "argument_list";
                string body = "arguments";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(60,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                (yyval.info)->arguments = (yyvsp[0].info)->arguments;

                delete (yyvsp[0].info);

        }
#line 5333 "y.tab.c"
    break;

  case 97: /* argument_list: %empty  */
#line 3092 "1805017.y"
           {
                (yyval.info) = new Info();
                (yyval.info)->line_count = line_count;

                string head = "argument_list";
                string body = "";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(61,head,body,text);

                printToLogRule(head,body);
        }
#line 5351 "y.tab.c"
    break;

  case 98: /* arguments: arguments COMMA logic_expression  */
#line 3107 "1805017.y"
                                            {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[-2].info)->line_count;

                string head = "arguments";
                string body = "arguments COMMA logic_expression";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(62,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[-2].info)->root);
                insertTOKEN((yyval.info),(yyvsp[-1].si));
                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                printToLogRule(head,body);

                (yyval.info)->arguments = (yyvsp[-2].info)->arguments;
                (yyval.info)->arguments.push_back((yyvsp[0].info)->server);

                (yyval.info)->lexeme = "NULL";
                loadRelCode((yyvsp[0].info));
                loadLogicCode2((yyvsp[0].info));
                loadVariablesCode((yyvsp[0].info));
                printCmd("PUSH AX\n");

                delete (yyvsp[-2].info);delete (yyvsp[0].info);
                delete (yyvsp[-1].si);
        }
#line 5385 "y.tab.c"
    break;

  case 99: /* arguments: logic_expression  */
#line 3135 "1805017.y"
                           {
                (yyval.info) = new Info();
                (yyval.info)->line_count = (yyvsp[0].info)->line_count;

                string head = "arguments";
                string body = "logic_expression";

                string text = getRuleString(head,body,(yyval.info)->line_count,line_count);

                (yyval.info)->root = new Node(63,head,body,text);

                (yyval.info)->root->children.push_back((yyvsp[0].info)->root);

                (yyval.info)->server = (yyvsp[0].info)->server;
                (yyval.info)->arguments.push_back((yyvsp[0].info)->server);
                
                (yyval.info)->lexeme = "NULL";
                loadRelCode((yyvsp[0].info));
                loadLogicCode2((yyvsp[0].info));
                loadVariablesCode((yyvsp[0].info));
                printCmd("PUSH AX\n");

                printToLogRule(head,body);
                delete (yyvsp[0].info);
        }
#line 5415 "y.tab.c"
    break;


#line 5419 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 3163 "1805017.y"


void addVariables(){
    SymbolInfo s;
    s.name = "number";
    s.type = "ID";
    s.dataType = "CHAR";
    s.isGlobal = true;

    st->insertSymbol(s);
    string code = tab + "number" + " DB \"00000$\"\n";
    globalVarDeclCodes.push_back(code);

    s.name = "CR";
    s.type = "ID";
    s.dataType = "";
    s.isGlobal = true;

    st->insertSymbol(s);
    code = tab + "CR" + " EQU 0DH\n";
    globalVarDeclCodes.push_back(code);

    s.name = "LF";
    s.type = "ID";
    s.dataType = "";
    s.isGlobal = true;

    st->insertSymbol(s);
    code = tab + "LF" + " EQU 0AH\n";
    globalVarDeclCodes.push_back(code);
}

void addFunction(){
    SymbolInfo s;
    s.name = "print_output";
    insertFuncDefToSymbolTable(&s,"VOID");
    s.name = "new_line";
    insertFuncDefToSymbolTable(&s,"VOID");
}

void initCodeFile(){
    asmOut << ";-------\n"
    ";\n"
    ";-------\n"
    ".MODEL SMALL\n"
    ".STACK 1000H\n"
    ".Data\n";

    for( string varDecl : globalVarDeclCodes ){
        asmOut << varDecl ;
    }

    asmOut << ".CODE\n";

    string line;
    int currLine = 1;

    while(getline(tempInputFile,line)){
        asmOut << line << labelMap[currLine] << endl;
        currLine++;
    }

    asmOut << "new_line PROC\n";
    asmOut << "\n";
    asmOut << tab << "push ax\n";
    asmOut << tab << "push dx\n";
    asmOut << tab << "mov ah,2\n";
    asmOut << tab << "mov dl,cr\n";
    asmOut << tab << "int 21h\n";
    asmOut << tab << "mov ah,2\n";
    asmOut << tab << "mov dl,lf\n";
    asmOut << tab << "int 21h\n";
    asmOut << tab << "pop dx\n";
    asmOut << tab << "pop ax\n";
    asmOut << tab << "ret\n";
    asmOut << "new_line endp\n";

    asmOut << "print_output proc  ;print what is in ax\n";
    asmOut << tab << "push ax\n";
    asmOut << tab << "push bx\n";
    asmOut << tab << "push cx\n";
    asmOut << tab << "push dx\n";
    asmOut << tab << "push si\n";
    asmOut << tab << "lea si,number\n";
    asmOut << tab << "mov bx,10\n";
    asmOut << tab << "add si,4\n";
    asmOut << tab << "cmp ax,0\n";
    asmOut << tab << "jnge negate\n";
    asmOut << "print:\n";
    asmOut << tab << "xor dx,dx\n";
    asmOut << tab << "div bx\n";
    asmOut << tab << "mov [si],dl\n";
    asmOut << tab << "add [si],'0'\n";
    asmOut << tab << "dec si\n";
    asmOut << tab << "cmp ax,0\n";
    asmOut << tab << "jne print\n";
    asmOut << tab << "inc si\n";
    asmOut << tab << "lea dx,si\n";
    asmOut << tab << "mov ah,9\n";
    asmOut << tab << "int 21h\n";
    asmOut << tab << "pop si\n";
    asmOut << tab << "pop dx\n";
    asmOut << tab << "pop cx\n";
    asmOut << tab << "pop bx\n";
    asmOut << tab << "pop ax\n";
    asmOut << tab << "ret\n";
    asmOut << "negate:\n";
    asmOut << tab << "push ax\n";
    asmOut << tab << "mov ah,2\n";
    asmOut << tab << "mov dl,'-'\n";
    asmOut << tab << "int 21h\n";
    asmOut << tab << "pop ax\n";
    asmOut << tab << "neg ax\n";
    asmOut << tab << "jmp print\n";
    asmOut << "print_output endp\n";

    asmOut << "END MAIN\n";
}

void writeOptimzedCode(){
    string line;
    string prevLine;

    vector<string> currWords;
    vector<string> prevWords;
    bool pushFlag = false;

    while(getline(asmInput,line)){
        if( line == "    ADD AX, 0" )
            continue;

        stringstream ss(line);
        string word;
        while (ss >> word) { // Extract word from the stream.
            currWords.push_back(word);
        }
        bool omitFlag = false;
        if( pushFlag ){
            if( currWords.size() == 2 ){
                if( currWords[0] == "POP" && prevWords[1] == currWords[1] )
                    omitFlag = true;
            }

            if(!omitFlag){
                OptAsmOut << prevLine << endl;
            }

            pushFlag = false;
        }

        if( currWords.size() == 2 ){
            if( currWords[0] == "PUSH" )
                pushFlag = true;
        }

        if(!pushFlag&&!omitFlag)
            OptAsmOut << line << endl;
        
        prevWords = currWords;
        prevLine = line;
        currWords.clear();
    }
}

int main(int argc,char *argv[])
{


	FILE *fin=fopen(argv[1],"r");

	if(fin==NULL){
		printf("Cannot open Input File\n");
		return 0;
	}

	logout.open("log.txt");
	errorOut.open("error.txt");
    parseTreeOut.open("parseTree.txt");
    asmOut.open("code.asm");
    tempAsmOut.open("tempCode.asm");

    
    addVariables();
    addFunction();

	yyin=fin;
	yyparse();

	parseTree->level = 0;
	preTraversal(parseTree);

    freeMemory();
	fclose(yyin);

    logout << "Total Lines: " << line_count << "\n";
    logout << "Total Errors: " << err_count << "\n";

    tempAsmOut.close();

    tempInputFile.open("tempCode.asm");

    initCodeFile();
    tempInputFile.close();
	logout.close();
	errorOut.close();
	parseTreeOut.close();
    asmOut.close();

    OptAsmOut.open("optimized_code.asm");
    asmInput.open("code.asm");

    writeOptimzedCode();

    OptAsmOut.close();
    asmInput.close();

	return 0;
}


