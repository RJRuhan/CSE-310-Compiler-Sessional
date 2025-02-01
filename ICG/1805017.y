%{
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


%}

%union{
    SymbolInfo* si;
    Info* info;
}

%token <si> IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE ASSIGNOP NOT LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE COMMA SEMICOLON ID ADDOP MULOP RELOP LOGICOP INCOP BITOP CONST_INT CONST_FLOAT PRINTLN

%type <info> m n p start program unit variable var_declaration type_specifier func_declaration func_definition parameter_list expression factor unary_expression term simple_expression rel_expression statement statements compound_statement logic_expression expression_statement arguments argument_list declaration_list




%destructor { free2($$);} <info>
%destructor { free1($$);} <si>


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%

start : program
    {
        $$->line_count = $1->line_count;

        string text = getRuleString("start","program",$$->line_count,line_count-1);
        parseTree = new Node(1,"start","program",text);
        parseTree->children.push_back($1->root);

        printToLogRule("start","program");

        delete $1;
    }
	;

program : program unit
    {
        $$ = new Info();
        $$->line_count = $1->line_count;

        string text = getRuleString("program","program unit",$$->line_count,line_count);
        $$->root = new Node(2,"program","program unit",text);
        $$->root->children.push_back($1->root);
        $$->root->children.push_back($2->root);

        printToLogRule("program","program unit");

        delete $1;delete $2;
    }
	| unit
	{
        $$ = new Info();
        $$->line_count = $1->line_count;

        string text = getRuleString("program","unit",$$->line_count,line_count);
        $$->root = new Node(3,"program","unit",text);
        $$->root->children.push_back($1->root);

        printToLogRule("program","unit");

        delete $1;
    }
	;

unit : var_declaration {
        $$ = new Info();
        $$->line_count = $1->line_count;

        string text = getRuleString("unit","var_declaration",$$->line_count,line_count);
        $$->root = new Node(4,"unit","var_declaration",text);
        $$->root->children.push_back($1->root);

        printToLogRule("unit","var_declaration");

        delete $1;
    }
     | func_declaration {
        $$ = new Info();
        $$->line_count = $1->line_count;

        string text = getRuleString("unit","func_declaration",$$->line_count,line_count);
        $$->root = new Node(5,"unit","func_declaration",text);
        $$->root->children.push_back($1->root);

        printToLogRule("unit","func_declaration");

        delete $1;
    }| func_definition {
        $$ = new Info();
        $$->line_count = $1->line_count;

        string text = getRuleString("unit","func_definition",$$->line_count,line_count);
        $$->root = new Node(6,"unit","func_definition",text);
        $$->root->children.push_back($1->root);

        printToLogRule("unit","func_definition");

        delete $1;
    }
     ;

func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON",$$->line_count,line_count);
            $$->root = new Node(7,"func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            insertTOKEN($$,$3);
            $$->root->children.push_back($4->root);
            insertTOKEN($$,$5);
            insertTOKEN($$,$6);

            printToLogRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");

            $2->dataType = $1->data;
            $2->isFunction = true;
            $2->isFunctionDeclared = true;

            for(SymbolInfo s : parameterList){
                $2->params.push_back(s.dataType);
            }

            if(!st->insertSymbol(*$2)){
                multipleFunctionDeclarationError($2);
            }

            parameterList.clear();

            delete $1;delete $4;
            delete $2;delete $3;delete $5;delete $6;
        }| type_specifier ID LPAREN parameter_list RPAREN error {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN parameter_list RPAREN error",$$->line_count,line_count);
            $$->root = new Node(-1,"func_declaration","type_specifier ID LPAREN parameter_list RPAREN error",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            insertTOKEN($$,$3);
            $$->root->children.push_back($4->root);
            insertTOKEN($$,$5);

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

            printSyntaxError("SEMICOLON","function declaration",$5->line_count);

            delete $1;delete $4;
            delete $2;delete $3;delete $5;

        }| type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON{

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON",$$->line_count,line_count);
            $$->root = new Node(-1,"func_declaration","type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            insertTOKEN($$,$3);
            $$->root->children.push_back($4->root);
            insertTOKEN($$,$6);
            insertTOKEN($$,$7);

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

            printSyntaxError("parameter list","function declaration",$4->line_count);

            delete $1;delete $4;
            delete $2;delete $3;delete $6;delete $7;

        }| type_specifier ID LPAREN parameter_list error RPAREN error {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN parameter_list error RPAREN error",$$->line_count,line_count);
            $$->root = new Node(-1,"func_declaration","type_specifier ID LPAREN parameter_list error RPAREN error",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            insertTOKEN($$,$3);
            $$->root->children.push_back($4->root);
            insertTOKEN($$,$6);

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
            printSyntaxError("parameter list","function declaration",$4->line_count);
            printSyntaxError("SEMICOLON","function declaration",$6->line_count);

            parameterList.clear();

            delete $1;delete $4;
            delete $2;delete $3;delete $6;

        }| type_specifier ID LPAREN RPAREN SEMICOLON {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON",$$->line_count,line_count);
            $$->root = new Node(8,"func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            insertTOKEN($$,$3);
            insertTOKEN($$,$4);
            insertTOKEN($$,$5);

            printToLogRule("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");

            $2->dataType = $1->data;
            $2->isFunction = true;
            $2->isFunctionDeclared = true;

            if(!st->insertSymbol(*$2)){
                multipleFunctionDeclarationError($2);
            }

            parameterList.clear();

            delete $1;
            delete $2;delete $3;delete $4;delete $5;
        }|type_specifier ID LPAREN RPAREN error {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN RPAREN error",$$->line_count,line_count);
            $$->root = new Node(-1,"func_declaration","type_specifier ID LPAREN RPAREN error",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            insertTOKEN($$,$3);
            insertTOKEN($$,$4);

            printToLogRule("func_declaration","type_specifier ID LPAREN RPAREN error");

            // $2->dataType = $1->data;
            // $2->isFunction = true;
            // $2->isFunctionDeclared = true;

            // if(!st->insertSymbol(*$2)){
            //     multipleFunctionDeclarationError($2);
            // }

            parameterList.clear();
            printSyntaxError("SEMICOLON","function declaration",$4->line_count);

            delete $1;
            delete $2;delete $3;delete $4;
        }|type_specifier ID LPAREN error RPAREN SEMICOLON {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN error RPAREN SEMICOLON",$$->line_count,line_count);
            $$->root = new Node(-1,"func_declaration","type_specifier ID LPAREN error RPAREN SEMICOLON",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            insertTOKEN($$,$3);
            insertTOKEN($$,$5);
            insertTOKEN($$,$6);

            printToLogRule("func_declaration","type_specifier ID LPAREN error RPAREN SEMICOLON");

            // $2->dataType = $1->data;
            // $2->isFunction = true;
            // $2->isFunctionDeclared = true;

            // if(!st->insertSymbol(*$2)){
            //     multipleFunctionDeclarationError($2);
            // }

            parameterList.clear();
            printSyntaxError("parameter list","function declaration",$3->line_count);

            delete $1;
            delete $2;delete $3;delete $5;delete $6;
        }|type_specifier ID LPAREN error RPAREN error {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("func_declaration","type_specifier ID LPAREN error RPAREN error",$$->line_count,line_count);
            $$->root = new Node(8,"func_declaration","type_specifier ID LPAREN error RPAREN error",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            insertTOKEN($$,$3);
            insertTOKEN($$,$5);

            printToLogRule("func_declaration","type_specifier ID LPAREN error RPAREN error");

            // $2->dataType = $1->data;
            // $2->isFunction = true;
            // $2->isFunctionDeclared = true;

            // if(!st->insertSymbol(*$2)){
            //     multipleFunctionDeclarationError($2);
            // }

            parameterList.clear();
            printSyntaxError("parameter list","function declaration",$3->line_count);
            printSyntaxError("SEMICOLON","function declaration",$5->line_count);

            delete $1;
            delete $2;delete $3;delete $5;
        }
		;

func_definition : type_specifier ID LPAREN parameter_list RPAREN { isFuncNow = true;insertFuncDefToSymbolTable($2,$1->data);initFuncAsmCode($2); } compound_statement {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement",$$->line_count,line_count);
            $$->root = new Node(9,"func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            insertTOKEN($$,$3);
            $$->root->children.push_back($4->root);
            insertTOKEN($$,$5);
            $$->root->children.push_back($7->root);

            printToLogRule("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
            
            isFuncNow = false;
            int paramNum = parameterList.size();
            parameterList.clear();
            // cout << "*****" << currFunc.stackPos << endl;


            if(!currFunc.returnFlag && $2->dataType != "VOID"){
                noReturnError(line_count);
            }

            if( currFunc.stackPos > 0 )
                printCmd("ADD SP, " + to_string(currFunc.stackPos) + "\n");
            printCmd("POP BP\n");

            if($2->name == "main"){
                printCmd("MOV AX, 4CH\n");
                printCmd("INT 21H\n");
            }else{
                if( paramNum == 0 )
                    printCmd("RET\n");
                else
                    printCmd("RET " + to_string(paramNum*2) + "\n");
            }

            tempAsmOut << $2->name << " ENDP\n";tempAsmLineCount++;

            backPatch($7->nextList,to_string(asmLabel));
            
            delete $1;delete $4;delete $7;
            delete $2;delete $3;delete $5;

        }|type_specifier ID LPAREN parameter_list error RPAREN {} compound_statement {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("func_definition","type_specifier ID LPAREN parameter_list error RPAREN",$$->line_count,line_count);
            $$->root = new Node(9,"func_definition","type_specifier ID LPAREN parameter_list error RPAREN",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            insertTOKEN($$,$3);
            $$->root->children.push_back($4->root);
            insertTOKEN($$,$6);
            $$->root->children.push_back($8->root);

            printToLogRule("func_definition","type_specifier ID LPAREN parameter_list error RPAREN");
            
            isFuncNow = false;
            parameterList.clear();
            
            printSyntaxError("parameter list","function definition",$4->line_count);

            delete $1;delete $4;delete $8;
            delete $2;delete $3;delete $6;

        }| type_specifier ID LPAREN RPAREN { isFuncNow = true;insertFuncDefToSymbolTable($2,$1->data);initFuncAsmCode($2);} compound_statement {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("func_definition","type_specifier ID LPAREN RPAREN compound_statement",$$->line_count,line_count);
            $$->root = new Node(10,"func_definition","type_specifier ID LPAREN RPAREN compound_statement",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            insertTOKEN($$,$3);
            insertTOKEN($$,$4);
            $$->root->children.push_back($6->root);

            printToLogRule("func_definition","type_specifier ID LPAREN RPAREN compound_statement");
            
            isFuncNow = false;
            parameterList.clear();
            // cout << "*****" << currFunc.stackPos << endl;

            if(!currFunc.returnFlag && $2->dataType != "VOID"){
                noReturnError(line_count);
            }

            if( currFunc.stackPos > 0 )
                printCmd("ADD SP, " + to_string(currFunc.stackPos) + "\n");
            // printLabel(++asmLabel);
            printCmd("POP BP\n");

            if($2->name == "main"){
                printCmd("MOV AX, 4CH\n");
                printCmd("INT 21H\n");
            }else{
                printCmd("RET\n");
            }

            tempAsmOut << $2->name << " ENDP\n";tempAsmLineCount++;

            backPatch($6->nextList,to_string(asmLabel));
            
            delete $1;delete $6;
            delete $2;delete $3;delete $4;

        }| type_specifier ID LPAREN error RPAREN {} compound_statement {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("func_definition","type_specifier ID LPAREN error RPAREN compound_statement",$$->line_count,line_count);
            $$->root = new Node(10,"func_definition","type_specifier ID LPAREN error RPAREN compound_statement",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            insertTOKEN($$,$3);
            insertTOKEN($$,$5);
            $$->root->children.push_back($7->root);

            printToLogRule("func_definition","type_specifier ID LPAREN error RPAREN compound_statement");
            
            isFuncNow = false;
            parameterList.clear();
            
            printSyntaxError("parameter list","function definition",$3->line_count);
            
            delete $1;delete $7;
            delete $2;delete $3;delete $5;

        }
 		;


parameter_list  : parameter_list COMMA type_specifier ID {
            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("parameter_list","parameter_list COMMA type_specifier ID",$$->line_count,line_count);
            $$->root = new Node(11,"parameter_list","parameter_list COMMA type_specifier ID",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            $$->root->children.push_back($3->root);
            insertTOKEN($$,$4);

            printToLogRule("parameter_list","parameter_list COMMA type_specifier ID");

            $4->dataType = $3->data; 
            parameterList.push_back(*$4);


            delete $1;delete $3;
            delete $2;delete $4;
        }|parameter_list error COMMA type_specifier ID {
            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("parameter_list","parameter_list error COMMA type_specifier ID",$$->line_count,line_count);
            $$->root = new Node(11,"parameter_list","parameter_list error COMMA type_specifier ID",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$3);
            $$->root->children.push_back($4->root);
            insertTOKEN($$,$5);

            printToLogRule("parameter_list","parameter_list error COMMA type_specifier ID");

            // $5->dataType = $4->data;
            // parameterList.push_back(*$5);

            printSyntaxError("parameter list","parameter list",$1->line_count);

            delete $1;delete $4;
            delete $3;delete $5;

        }| parameter_list COMMA type_specifier {
            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("parameter_list","parameter_list COMMA type_specifier",$$->line_count,line_count);
            $$->root = new Node(12,"parameter_list","parameter_list COMMA type_specifier",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);
            $$->root->children.push_back($3->root);

            printToLogRule("parameter_list","parameter_list COMMA type_specifier");

            SymbolInfo temp;
            temp.type = "";
            temp.name = "NO_IDENTIFIER_NAME";
            temp.dataType = $3->data;

            parameterList.push_back(temp);

            delete $1;delete $3;
            delete $2;

		}| parameter_list error COMMA type_specifier {
            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("parameter_list","parameter_list error COMMA type_specifier",$$->line_count,line_count);
            $$->root = new Node(12,"parameter_list","parameter_list error COMMA type_specifier",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$3);
            $$->root->children.push_back($4->root);

            printToLogRule("parameter_list","parameter_list error COMMA type_specifier");

            // SymbolInfo temp;
            // temp.type = "";
            // temp.name = "NO_IDENTIFIER_NAME";
            // temp.dataType = $4->data;

            // parameterList.push_back(temp);

            printSyntaxError("parameter list","parameter list",$1->line_count);

            delete $1;delete $4;
            delete $3;

		}| type_specifier ID {
            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("parameter_list","type_specifier ID",$$->line_count,line_count);
            $$->root = new Node(13,"parameter_list","type_specifier ID",text);

            $$->root->children.push_back($1->root);
            insertTOKEN($$,$2);

            printToLogRule("parameter_list","type_specifier ID");

            $2->dataType = $1->data;
            parameterList.push_back(*$2);

            delete $1;
            delete $2;

		}| type_specifier {
            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("parameter_list","type_specifier",$$->line_count,line_count);
            $$->root = new Node(14,"parameter_list","type_specifier",text);

            $$->root->children.push_back($1->root);

            printToLogRule("parameter_list","type_specifier");

            SymbolInfo temp;
            temp.type = "";
            temp.name = "NO_IDENTIFIER_NAME";
            temp.dataType = $1->data;

            parameterList.push_back(temp);

            delete $1;
		}
 		;


compound_statement : LCURL newscope statements RCURL {

                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("compound_statement","LCURL statements RCURL",$$->line_count,line_count);
                $$->root = new Node(15,"compound_statement","LCURL statements RCURL",text);

                insertTOKEN($$,$1);
                $$->root->children.push_back($3->root);
                insertTOKEN($$,$4);

                printToLogRule("compound_statement","LCURL statements RCURL");

                st->printAll(logout);
                st->exitScope();

                $$->nextList = $3->nextList;

                delete $3;
                delete $1;delete $4;

            }|LCURL newscope statements error RCURL {

                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("compound_statement","LCURL statements error RCURL",$$->line_count,line_count);
                $$->root = new Node(15,"compound_statement","LCURL statements error RCURL",text);

                insertTOKEN($$,$1);
                $$->root->children.push_back($3->root);
                insertTOKEN($$,$5);

                printToLogRule("compound_statement","LCURL statements error RCURL");

                st->printAll(logout);
                st->exitScope();

                delete $3;
                delete $1;delete $5;

            }|LCURL newscope error statements RCURL {

                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("compound_statement","LCURL error statements RCURL",$$->line_count,line_count);
                $$->root = new Node(15,"compound_statement","LCURL error statements RCURL",text);

                insertTOKEN($$,$1);
                $$->root->children.push_back($4->root);
                insertTOKEN($$,$5);

                printToLogRule("compound_statement","LCURL error statements RCURL");

                st->printAll(logout);
                st->exitScope();

                delete $4;
                delete $1;delete $5;

            }| LCURL newscope RCURL {

                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("compound_statement","LCURL RCURL",$$->line_count,line_count);
                $$->root = new Node(16,"compound_statement","LCURL RCURL",text);

                insertTOKEN($$,$1);
                insertTOKEN($$,$3);

                printToLogRule("compound_statement","LCURL RCURL");

                st->printAll(logout);
                st->exitScope();

                delete $1;delete $3;
            }| LCURL newscope error RCURL {

                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("compound_statement","LCURL error RCURL",$$->line_count,line_count);
                $$->root = new Node(16,"compound_statement","LCURL error RCURL",text);

                insertTOKEN($$,$1);
                insertTOKEN($$,$4);

                printToLogRule("compound_statement","LCURL error RCURL");

                st->printAll(logout);
                st->exitScope();

                delete $1;delete $4;
            }
 		    ;

newscope :  {enterNewScope();}

var_declaration : type_specifier declaration_list SEMICOLON {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("var_declaration","type_specifier declaration_list SEMICOLON",$$->line_count,line_count);

            $$->root = new Node(17,"var_declaration","type_specifier declaration_list SEMICOLON",text);

            $$->root->children.push_back($1->root);
            $$->root->children.push_back($2->root);
            insertTOKEN($$,$3);

            printToLogRule("var_declaration","type_specifier declaration_list SEMICOLON");
            
            if($1->data == "VOID"){
                string varID = "";
                int lc = $1->line_count;
                if(!$2->symbols.empty()){
                    varID = $2->symbols[0].name;
                    lc = $2->symbols[0].line_count;
                }
                dataTypeError(varID,line_count);
            }else{
                for( SymbolInfo s : $2->symbols ){
                    if(s.dataType == "ARRAY")
                        s.dataType = $1->data + "_ARRAY";
                    else
                        s.dataType = $1->data;

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



            delete $1;delete $2;
            delete $3;
        }|type_specifier declaration_list error SEMICOLON {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("var_declaration","type_specifier declaration_list error SEMICOLON",$$->line_count,line_count);

            $$->root = new Node(17,"var_declaration","type_specifier declaration_list error SEMICOLON",text);

            $$->root->children.push_back($1->root);
            $$->root->children.push_back($2->root);
            insertTOKEN($$,$4);

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

            printSyntaxError("declaration list","variable declaration",$2->line_count);

            delete $1;delete $2;
            delete $4;
        }
 		 ;

type_specifier	: INT {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("type_specifier","INT",$$->line_count,line_count);
            $$->root = new Node(18,"type_specifier","INT",text);

            insertTOKEN($$,$1);

            printToLogRule("type_specifier","INT");

            $$->data = $1->type;

            delete $1;

        }| FLOAT {
            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("type_specifier","FLOAT",$$->line_count,line_count);
            $$->root = new Node(19,"type_specifier","FLOAT",text);

            insertTOKEN($$,$1);

            printToLogRule("type_specifier","FLOAT");

            $$->data = $1->type;

            delete $1;

        }| VOID {

            $$ = new Info();
            $$->line_count = $1->line_count;

            string text = getRuleString("type_specifier","VOID",$$->line_count,line_count);
            $$->root = new Node(20,"type_specifier","VOID",text);

            insertTOKEN($$,$1);

            printToLogRule("type_specifier","VOID");

            $$->data = $1->type;

            delete $1;

        }
 		;

declaration_list : declaration_list COMMA ID{

                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("declaration_list","declaration_list COMMA ID",$$->line_count,line_count);

                $$->root = new Node(21,"declaration_list","declaration_list COMMA ID",text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$2);
                insertTOKEN($$,$3);

                printToLogRule("declaration_list","declaration_list COMMA ID");

                $$->symbols = $1->symbols;
                $$->symbols.push_back(*$3);
                $$->server = $1->server;

                delete $1;
                delete $2;delete $3;

            }|declaration_list error COMMA ID{

                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("declaration_list","declaration_list error COMMA ID",$$->line_count,line_count);

                $$->root = new Node(21,"declaration_list","declaration_list error COMMA ID",text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$3);
                insertTOKEN($$,$4);

                printToLogRule("declaration_list","declaration_list error COMMA ID");

                // $$->symbols = $1->symbols;
                // $$->symbols.push_back(*$4);
                // $$->server = $1->server;

                printSyntaxError("declaration list","variable declaration",$1->line_count);

                delete $1;
                delete $3;delete $4;

            }| declaration_list COMMA ID LSQUARE CONST_INT RSQUARE {
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE",$$->line_count,line_count);

                $$->root = new Node(22,"declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE",text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$2);
                insertTOKEN($$,$3);
                insertTOKEN($$,$4);
                insertTOKEN($$,$5);
                insertTOKEN($$,$6);

                printToLogRule("declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
                
                $3->arraySize = stoi($5->name);
                //cout << "ttttttt" << $3->arraySize << endl;

                $$->symbols = $1->symbols;
                $3->dataType = "ARRAY";
                $$->symbols.push_back(*$3);
                $$->server = $1->server;

                delete $1;
                delete $2;delete $3;delete $4;delete $5;delete $6;
            }| declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE {
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("declaration_list","declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE",$$->line_count,line_count);

                $$->root = new Node(22,"declaration_list","declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE",text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$3);
                insertTOKEN($$,$4);
                insertTOKEN($$,$5);
                insertTOKEN($$,$6);
                insertTOKEN($$,$7);

                printToLogRule("declaration_list","declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE");

                // $$->symbols = $1->symbols;
                // $3->dataType = "ARRAY";
                // $$->symbols.push_back(*$4);
                // $$->server = $1->server;

                printSyntaxError("declaration list","variable declaration",$1->line_count);

                delete $1;
                delete $3;delete $4;delete $5;delete $6;delete $7;
            }| declaration_list COMMA ID LSQUARE CONST_FLOAT RSQUARE {
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE",$$->line_count,line_count);

                $$->root = new Node(22,"declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE",text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$2);
                insertTOKEN($$,$3);
                insertTOKEN($$,$4);
                insertTOKEN($$,$5);
                insertTOKEN($$,$6);

                printToLogRule("declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");


                $$->symbols = $1->symbols;
                $3->dataType = "ARRAY";
                $$->symbols.push_back(*$3);

                ArraySizeFloatError($5->line_count);
                $$->server = $1->server;

                delete $1;
                delete $2;delete $3;delete $4;delete $5;delete $6;
            }| declaration_list error COMMA ID LSQUARE CONST_FLOAT RSQUARE {
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("declaration_list","declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE",$$->line_count,line_count);

                $$->root = new Node(22,"declaration_list","declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE",text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$3);
                insertTOKEN($$,$4);
                insertTOKEN($$,$5);
                insertTOKEN($$,$6);
                insertTOKEN($$,$7);

                printToLogRule("declaration_list","declaration_list error COMMA ID LSQUARE CONST_INT RSQUARE");

                // $$->symbols = $1->symbols;
                // $3->dataType = "ARRAY";
                // $$->symbols.push_back(*$4);

                // ArraySizeFloatError($6->line_count);

                // $$->server = $1->server;
                printSyntaxError("declaration list","variable declaration",$1->line_count);


                delete $1;
                delete $3;delete $4;delete $5;delete $6;delete $7;
            }| ID {
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("declaration_list","ID",$$->line_count,line_count);
                $$->root = new Node(23,"declaration_list","ID",text);

                insertTOKEN($$,$1);

                printToLogRule("declaration_list","ID");

                $$->symbols.push_back(*$1);

                delete $1;
        }| ID LSQUARE CONST_INT RSQUARE {
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("declaration_list","ID LSQUARE CONST_INT RSQUARE",$$->line_count,line_count);

                $$->root = new Node(24,"declaration_list","ID LSQUARE CONST_INT RSQUARE",text);

                insertTOKEN($$,$1);
                insertTOKEN($$,$2);
                insertTOKEN($$,$3);
                insertTOKEN($$,$4);

                printToLogRule("declaration_list","ID LSQUARE CONST_INT RSQUARE");
                $1->arraySize = stoi($3->name);
                // cout << "ttttttttt" << $1->arraySize << endl;
                $1->dataType = "ARRAY";
                $$->symbols.push_back(*$1);

                delete $1;delete $2;delete $3;delete $4;            
        }| ID LSQUARE CONST_FLOAT RSQUARE {
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("declaration_list","ID LSQUARE CONST_INT RSQUARE",$$->line_count,line_count);

                $$->root = new Node(24,"declaration_list","ID LSQUARE CONST_INT RSQUARE",text);

                insertTOKEN($$,$1);
                insertTOKEN($$,$2);
                insertTOKEN($$,$3);
                insertTOKEN($$,$4);

                printToLogRule("declaration_list","ID LSQUARE CONST_INT RSQUARE");

                $1->dataType = "ARRAY";
                $$->symbols.push_back(*$1);

                ArraySizeFloatError($3->line_count);

                delete $1;delete $2;delete $3;delete $4;            
        }
 		  ;

statements : statement{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("statements","statement",$$->line_count,line_count);
                $$->root = new Node(25,"statements","statement",text);

                $$->root->children.push_back($1->root);

                printToLogRule("statements","statement");
                printLabel(++asmLabel);
                $$->nextList = $1->nextList;
                delete $1;
        }| statements statement{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("statements","statements statement",$$->line_count,line_count);
                $$->root = new Node(26,"statements","statements statement",text);

                $$->root->children.push_back($1->root);
                $$->root->children.push_back($2->root);

                printToLogRule("statements","statements statement");
                printLabel(++asmLabel);

                copy($1->nextList.begin(), $1->nextList.end(), back_inserter($$->nextList));
                copy($2->nextList.begin(), $2->nextList.end(), std::back_inserter($$->nextList));

                delete $1;delete $2;

        }|statements error statement{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("statements","statements error statement",$$->line_count,line_count);
                $$->root = new Node(26,"statements","statements error statement",text);

                $$->root->children.push_back($1->root);
                $$->root->children.push_back($3->root);

                printToLogRule("statements","statements error statement");
                delete $1;delete $3;

        }
	   ;

statement : var_declaration{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("statement","var_declaration",$$->line_count,line_count);
                $$->root = new Node(27,"statement","var_declaration",text);

                $$->root->children.push_back($1->root);

                printToLogRule("statement","var_declaration");
                delete $1;

        }| expression_statement{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("statement","expression_statement",$$->line_count,line_count);
                $$->root = new Node(28,"statement","expression_statement",text);

                $$->root->children.push_back($1->root);

                $$->server = $1->server;
                $$->lexeme = $1->lexeme;
                $$->typeICG = $1->typeICG;

                $$->isRelExp = $1->isRelExp;
                $$->isBooleanExp = $1->isBooleanExp;
                $$->trueList = $1->trueList;
                $$->falseList = $1->falseList;                                
                $$->nextList = $1->nextList;      

                printToLogRule("statement","expression_statement");
                delete $1;

        }|func_declaration{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("statement","func_declaration",$$->line_count,line_count);
                $$->root = new Node(-1,"statement","func_declaration",text);

                $$->root->children.push_back($1->root);

                //printToLogRule("statement","func_declaration");
                nestedFunctionError($1->line_count);
                delete $1;

        }|func_definition{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("statement","func_definition",$$->line_count,line_count);
                $$->root = new Node(-1,"statement","func_definition",text);

                $$->root->children.push_back($1->root);

                //printToLogRule("statement","func_definition");
                nestedFunctionError($1->line_count);
                delete $1;

        }| compound_statement{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string text = getRuleString("statement","compound_statement",$$->line_count,line_count);
                $$->root = new Node(29,"statement","compound_statement",text);

                $$->root->children.push_back($1->root);

                $$->nextList = $1->nextList;

                printToLogRule("statement","compound_statement");
                delete $1;

        }| FOR LPAREN expression_statement m expression_statement p expression {printCmd("POP AX\n");printCmd("JMP L" + $4->label + "\n");} RPAREN m statement{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "statement";
                string body = "FOR LPAREN expression_statement expression_statement expression RPAREN statement";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(30,head,body,text);

                insertTOKEN($$,$1);
                insertTOKEN($$,$2);
                $$->root->children.push_back($3->root);
                $$->root->children.push_back($5->root);
                $$->root->children.push_back($7->root);
                insertTOKEN($$,$9);
                $$->root->children.push_back($11->root);

                printToLogRule(head,body);


                printCmd("JMP L" + $6->label + "\n");
                printLabel(++asmLabel);
                backPatch($5->falseList,to_string(asmLabel));
                backPatch($5->trueList,$10->label);


                delete $3;delete $4;delete $5;delete $7;delete $10;delete $11;
                delete $1;delete $2;delete $6;delete $9;

        }| IF LPAREN expression RPAREN p statement %prec LOWER_THAN_ELSE{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "statement";
                string body = "IF LPAREN expression RPAREN statement";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(31,head,body,text);

                insertTOKEN($$,$1);
                insertTOKEN($$,$2);
                $$->root->children.push_back($3->root);
                insertTOKEN($$,$4);
                $$->root->children.push_back($6->root);

                printToLogRule(head,body);
                

                // cout << $3->isBooleanExp << " " << $3->isRelExp << endl;

                backPatch($3->trueList,$5->label);
                // printLabel(++asmLabel);
                backPatch($3->falseList,to_string(asmLabel));

                $$->nextList = $6->nextList;

                delete $3;delete $6;
                delete $1;delete $2;delete $4;
        }| IF LPAREN expression RPAREN p statement ELSE n m statement{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "statement";
                string body = "IF LPAREN expression RPAREN statement ELSE statement";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(32,head,body,text);

                insertTOKEN($$,$1);
                insertTOKEN($$,$2);
                $$->root->children.push_back($3->root);
                insertTOKEN($$,$4);
                $$->root->children.push_back($6->root);
                insertTOKEN($$,$7);
                $$->root->children.push_back($10->root);

                printToLogRule(head,body);

                backPatch($3->trueList,$5->label);
                // printLabel(++asmLabel);
                backPatch($3->falseList,$9->label);
                backPatch($8->nextList,to_string(asmLabel));

                copy($6->nextList.begin(), $6->nextList.end(), back_inserter($$->nextList));
                copy($10->nextList.begin(), $10->nextList.end(), std::back_inserter($$->nextList));

                delete $3;delete $6;delete $10;delete $9;delete $7;
                delete $1;delete $2;delete $4;delete $8;delete $5;

        }| WHILE m LPAREN expression RPAREN p statement{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "statement";
                string body = "WHILE LPAREN expression RPAREN statement";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(33,head,body,text);

                insertTOKEN($$,$1);
                insertTOKEN($$,$3);
                $$->root->children.push_back($4->root);
                insertTOKEN($$,$5);
                $$->root->children.push_back($7->root);

                printToLogRule(head,body);

                backPatch($4->trueList,$6->label);

                printCmd("JMP L" + $2->label + "\n");
                printLabel(++asmLabel);
                backPatch($4->falseList,to_string(asmLabel));

                delete $3;delete $5;delete $6;delete $7;
                delete $1;delete $2;delete $4;

        }| PRINTLN LPAREN ID RPAREN SEMICOLON{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "statement";
                string body = "PRINTLN LPAREN ID RPAREN SEMICOLON";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(34,head,body,text);

                insertTOKEN($$,$1);
                insertTOKEN($$,$2);
                insertTOKEN($$,$3);
                insertTOKEN($$,$4);
                insertTOKEN($$,$5);

                printToLogRule(head,body);

                if( !st->lookUpSymbol($3->name) ){
                    undeclaredVariableError($3->name,$3->line_count);
                    $$->server = "UNDEFINED";
                }

                Info temp;
                temp.lexeme = $3->name;
                temp.typeICG = "variable";
                loadVariablesCode(&temp);
                printCmd("CALL print_output\n");
                printCmd("CALL new_line\n");

                delete $1;delete $2;delete $3;delete $4;delete $5;

        }| RETURN expression SEMICOLON{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "statement";
                string body = "RETURN expression SEMICOLON";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(35,head,body,text);

                insertTOKEN($$,$1);
                $$->root->children.push_back($2->root);
                insertTOKEN($$,$3);

                printToLogRule(head,body);

                //cout << $2->server << endl;
                if(!isFuncNow){
                    
                }else{
                    // cout << "herh" << endl;
                    checkReturnType($2);
                    currFunc.returnFlag = true;
                    loadVariablesCode($2);
                    printCmd("JMP L\n");
                    $$->nextList.push_back(tempAsmLineCount);
                }

                // $$->server = $2->server;
                // $$->lexeme = $2->lexeme;
                // $$->typeICG = $2->typeICG;

                // $$->isRelExp = $2->isRelExp;
                // $$->isBooleanExp = $2->isBooleanExp;
                // $$->trueList = $2->trueList;
                // $$->falseList = $2->falseList;                                
                // $$->nextList = $2->nextList;      
                

                delete $2;
                delete $1;delete $3;

        }
	  ;

n :  { $$ = new Info();
    printCmd("JMP L\n");$$->nextList.push_back(tempAsmLineCount);
    }



expression_statement 	: SEMICOLON{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "expression_statement";
                string body = "SEMICOLON";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(36,head,body,text);

                insertTOKEN($$,$1);

                printToLogRule(head,body);

                delete $1;
        }| expression SEMICOLON{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "expression_statement";
                string body = "expression SEMICOLON";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(37,head,body,text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$2);

                printToLogRule(head,body);
                cout <<  "--------" << $1->isBooleanExp << " " << $1->isRelExp << endl;
                if( !$1->isBooleanExp && !$1->isRelExp )
                    printCmd("POP AX\n");

                $$->server = $1->server;
                $$->lexeme = $1->lexeme;
                $$->typeICG = $1->typeICG;

                $$->isRelExp = $1->isRelExp;
                $$->trueList = $1->trueList;
                $$->falseList = $1->falseList;
                $$->nextList = $1->nextList;
                $$->isBooleanExp = $1->isBooleanExp;

                expNow = $$;
                expNow->isExp = true;

                delete $1;
                delete $2;
        }| expression error SEMICOLON{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "expression_statement";
                string body = "expression error SEMICOLON";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(37,head,body,text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$3);

                printToLogRule(head,body);

                printSyntaxError("expression","expression statement",$1->line_count);

                delete $1;
                delete $3;
        }
        ;

variable : ID{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "variable";
                string body = "ID";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(38,head,body,text);

                insertTOKEN($$,$1);

                printToLogRule(head,body);

                SymbolInfo* si = st->lookUpSymbol($1->name);
                if( !si ){
                    undeclaredVariableError($1->name,$1->line_count);
                    $$->server = "UNDEFINED";
                }else{
                    if( si->dataType == "INT_ARRAY" || si->dataType == "FLOAT_ARRAY" ){
                        //isArrayError($1->name,$1->line_count);
                        //$$->server = "UNDEFINED";
                    }else{
                        $$->server = si->dataType;
                    }

                    $$->lexeme = $1->name;
                    $$->typeICG = "variable";
                }

                delete $1;

        }| ID LSQUARE expression RSQUARE{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "variable";
                string body = "ID LSQUARE expression RSQUARE";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(39,head,body,text);

                insertTOKEN($$,$1);
                insertTOKEN($$,$2);
                $$->root->children.push_back($3->root);
                insertTOKEN($$,$4);

                printToLogRule(head,body);

                SymbolInfo* si = st->lookUpSymbol($1->name);
                if( !si ){
                    undeclaredVariableError($1->name,$1->line_count);
                    $$->server = "UNDEFINED";

                }else{
                    if( si->dataType == "INT" || si->dataType == "FLOAT" ){
                        isNotArrayError($1->name,$1->line_count);
                        $$->server = "UNDEFINED";

                    }else{
                        $$->server = si->dataType; 
                        $$->lexeme = $1->name;
                        $$->typeICG = "INT_ARRAY";
                        $$->arrIndx = $3->lexeme;

                        SymbolInfo* si = st->lookUpSymbol($1->name);
                        if(si != nullptr){
                            if( $3->lexeme == "NULL" ){
                                printCmd("POP AX\n");
                                printCmd("MOV SI, AX\n");
                            }else
                                printCmd("MOV SI, " + $3->lexeme + "\n");

                            printCmd("PUSH SI\n");
                            
                        }
                    }
                }

                if($3->server != "INT"){
                    invalidArrayIndexError($3->line_count);
                }

                delete $3;
                delete $1;delete $2;delete $4;
        }
	 ;

 expression : logic_expression{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "expression";
                string body = "logic_expression";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(40,head,body,text);

                $$->root->children.push_back($1->root);

                printToLogRule(head,body);

                $$->server = $1->server;
                $$->lexeme = $1->lexeme;
                $$->typeICG = $1->typeICG;
                $$->isRelExp = $1->isRelExp;
                $$->trueList = $1->trueList;
                $$->falseList = $1->falseList;
                $$->isBooleanExp = $1->isBooleanExp;

                expNow = $$;
                expNow->isExp = true;

                delete $1;

        }| variable ASSIGNOP logic_expression{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "expression";
                string body = "variable ASSIGNOP logic_expression";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(41,head,body,text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$2);
                $$->root->children.push_back($3->root);

                printToLogRule(head,body);

                verifyAssignop($$,$1,$3);
            
                $$->lexeme = "NULL";

                loadLogicCode2($3);
                loadRelCode($3);

                if( $3->isRelExp ){
                    printLabel(++asmLabel);
                    backPatch($3->trueList,to_string(asmLabel));
                    printCmd("MOV AX, 1\n");
                    printCmd("JMP L" +  to_string(asmLabel+2) + "\n");
                    printLabel(++asmLabel);
                    backPatch($3->falseList,to_string(asmLabel));
                    printCmd("MOV AX, 0\n");
                    printLabel(++asmLabel);
                    printCmd("PUSH AX\n");               
                }
                

                loadVariablesCode($3);
                
                // cout << "-------" << $1->lexeme << " " << $1->typeICG <<  endl;
                
                loadAssignCode($1);

                printCmd("PUSH AX\n");

                delete $1;delete $3;
                delete $2;
        }
	   ;



logic_expression : rel_expression{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "logic_expression";
                string body = "rel_expression";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(42,head,body,text);

                $$->root->children.push_back($1->root);

                printToLogRule(head,body);

                $$->server = $1->server;
                $$->lexeme = $1->lexeme;
                $$->typeICG = $1->typeICG;

                $$->isRelExp = $1->isRelExp;
                $$->trueList = $1->trueList;
                $$->falseList = $1->falseList;
                $$->nextList = $1->nextList;
                $$->isBooleanExp = $1->isBooleanExp;

                delete $1;
        }| rel_expression LOGICOP {loadLogicCode($1,$2);} m rel_expression{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "logic_expression";
                string body = "rel_expression LOGICOP rel_expression";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(43,head,body,text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$2);
                $$->root->children.push_back($5->root);

                printToLogRule(head,body);

                logicalTypecast($$,$1,$5);

                // printLabel(++asmLabel);
                loadLogicCode($5,$2);
                $$->lexeme = "NULL";

                // string trueLabel = to_string(++asmLabel);
                // printLabel(asmLabel);
                // printCmd("MOV AX, 1\n");
                // printCmd("JMP L" +  to_string(asmLabel+2) + "\n");
                // string falseLabel = to_string(++asmLabel);
                // printLabel(asmLabel);
                // printCmd("MOV AX, 0\n");
                // printLabel(++asmLabel);
                // printCmd("PUSH AX\n");

                if( $2->name == "||" ){
                    copy($1->trueList.begin(), $1->trueList.end(), back_inserter($$->trueList));
                    copy($5->trueList.begin(), $5->trueList.end(), std::back_inserter($$->trueList));
                    $$->falseList = $5->falseList;                    
                    
                    backPatch($1->falseList,$4->label);
                    // backPatch($1->trueList,trueLabel);
                    // backPatch($5->falseList,falseLabel);
                    // backPatch($5->trueList,trueLabel);

                }else if( $2->name == "&&" ){
                    $$->trueList = $5->trueList;
                    copy($1->falseList.begin(), $1->falseList.end(), back_inserter($$->falseList));
                    copy($5->falseList.begin(), $5->falseList.end(), std::back_inserter($$->falseList));                    
                    // backPatch($1->falseList,falseLabel);
                    backPatch($1->trueList,$4->label);
                    // backPatch($5->falseList,falseLabel);
                    // backPatch($5->trueList,trueLabel);     

                }

                $$->isBooleanExp = true;
                
                delete $1;delete $5;
                delete $2;delete $4;
        }
		 ;

m :  {
    $$ = new Info();
    $$->label = to_string(++asmLabel);
    printLabel(asmLabel);

}

p : {

    if( expNow != nullptr ){
        if( expNow->isExp ){
            loadExpCode(expNow);
        }
    }

    $$ = new Info();
    $$->label = to_string(++asmLabel);
    printLabel(asmLabel);
    
}


rel_expression	: simple_expression{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "rel_expression";
                string body = "simple_expression";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(44,head,body,text);

                $$->root->children.push_back($1->root);

                printToLogRule(head,body);

                $$->server = $1->server;
                $$->lexeme = $1->lexeme;
                $$->typeICG = $1->typeICG;
                

                $$->isRelExp = $1->isRelExp;
                $$->isBooleanExp = $1->isBooleanExp;
                $$->trueList = $1->trueList;
                $$->falseList = $1->falseList;                                
                $$->nextList = $1->nextList;                   

                delete $1;
        }
		| simple_expression {loadLogicCode2($1);loadRelCode($1);} RELOP simple_expression{
                //cout << "HERE2\n";
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "rel_expression";
                string body = "simple_expression RELOP simple_expression";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(45,head,body,text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$3);
                $$->root->children.push_back($4->root);

                printToLogRule(head,body);

                logicalTypecast($$,$1,$4);

                // $$->lexeme = $1->lexeme;

                $$->lexeme = "NULL";
                $$->isRelExp = true;

                // cout << "------------" << $1->lexeme << endl;
                loadRelCode($4);                
                loadLogicCode2($4);
                loadVariablesCode($4);
                printCmd("MOV DX, AX\n"); 
                // cout << "-------" << $1->lexeme << " " << $1->typeICG <<  endl;
                loadVariablesCode($1);
                printCmd("CMP AX, DX\n");

                if( $3->name == "<" ){
                    printCmd("JL L\n");
                }else if( $3->name == "<=" ){
                    printCmd("JLE L\n");
                }else if( $3->name == "==" ){
                    printCmd("JE L\n");
                }else if( $3->name == "!=" ){
                    printCmd("JNE L\n");
                }else if( $3->name == ">=" ){
                    printCmd("JGE L\n");
                }else if( $3->name == ">" ){
                    printCmd("JG L\n");
                }

                $$->trueList.push_back(tempAsmLineCount);
                
                printCmd("JMP L\n");
                $$->falseList.push_back(tempAsmLineCount);

                // printLabel(++asmLabel);
                // printCmd("MOV AX, 1\n");
                // printCmd("JMP L" +  to_string(asmLabel+2) + "\n");
                // printLabel(++asmLabel);
                // printCmd("MOV AX, 0\n");
                // printLabel(++asmLabel);
                // printCmd("PUSH AX\n");

                delete $1;delete $4;
                delete $3;
        }
		;

simple_expression : term{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "simple_expression";
                string body = "term";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(46,head,body,text);

                $$->root->children.push_back($1->root);

                printToLogRule(head,body);

                $$->server = $1->server;
                $$->lexeme = $1->lexeme;
                $$->typeICG = $1->typeICG;

                $$->isRelExp = $1->isRelExp;
                $$->isBooleanExp = $1->isBooleanExp;
                $$->trueList = $1->trueList;
                $$->falseList = $1->falseList;                                
                $$->nextList = $1->nextList;      

                delete $1;
        }| simple_expression {loadLogicCode2($1);loadRelCode($1);} ADDOP term{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "simple_expression";
                string body = "simple_expression ADDOP term";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(47,head,body,text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$3);
                $$->root->children.push_back($4->root);

                printToLogRule(head,body);

                arithmeticTypecast($$,$1,$4);


                $$->lexeme = "NULL";
                // cout << "-------" << $3->lexeme << " " << $3->typeICG <<  endl;
                loadRelCode($4);                
                loadLogicCode2($4);
                loadVariablesCode($4);
                
                printCmd("MOV DX, AX\n"); 

                // cout << "-------" << $1->lexeme << " " << $1->typeICG <<  endl;

                loadVariablesCode($1);

                if( $3->name == "+" ){
                    printCmd("ADD AX, DX\n");
                }else if( $3->name == "-" ){
                    printCmd("SUB AX, DX\n");
                }

                printCmd("PUSH AX\n");

                delete $1;delete $4;
                delete $3;
        }
		  ;

term :	unary_expression{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "term";
                string body = "unary_expression";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(48,head,body,text);

                $$->root->children.push_back($1->root);

                printToLogRule(head,body);

                $$->server = $1->server;
                $$->lexeme = $1->lexeme;
                $$->typeICG = $1->typeICG;
                
                $$->isRelExp = $1->isRelExp;
                $$->isBooleanExp = $1->isBooleanExp;
                $$->trueList = $1->trueList;
                $$->falseList = $1->falseList;                                
                $$->nextList = $1->nextList;                    

                delete $1;

        }| term {loadLogicCode2($1);loadRelCode($1);} MULOP unary_expression{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "term";
                string body = "term MULOP unary_expression";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(49,head,body,text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$3);
                $$->root->children.push_back($4->root);

                printToLogRule(head,body);

                if($3->name == "%" || $3->name == "/"){
                    if($4->lexeme == "0"){
                        divideByZeroError($4->line_count);
                        $$->server = "UNDEFINED";
                    }else
                        modTypecast($$,$1,$4);
                    
                }else{
                    arithmeticTypecast($$,$1,$4);
                }

                $$->lexeme = "NULL";
                // cout << "-------" << $3->lexeme << " " << $3->typeICG <<  endl;
                loadRelCode($4);
                loadLogicCode2($4);
                loadVariablesCode($4);
                
                printCmd("MOV CX, AX\n"); 

                // cout << "-------" << $1->lexeme << " " << $1->typeICG <<  endl;

                loadVariablesCode($1);

                printCmd("CWD\n");
                if( $3->name == "*" ){
                    printCmd("MUL CX\n");
                    printCmd("PUSH AX\n");
                }else if( $3->name == "/" ){
                    printCmd("DIV CX\n");
                    printCmd("PUSH AX\n");
                }else if( $3->name == "%" ){
                    printCmd("DIV CX\n");
                    printCmd("PUSH DX\n");
                }
                

                delete $1;delete $4;
                delete $3;
        }
     ;

unary_expression : ADDOP unary_expression{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "unary_expression";
                string body = "ADDOP unary_expression";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(50,head,body,text);

                insertTOKEN($$,$1);
                $$->root->children.push_back($2->root);

                printToLogRule(head,body);

                $$->server = $2->server;

                loadRelCode($2);
                loadLogicCode2($2);
                loadVariablesCode($2);
                if( $1->name == "-" ){
                    printCmd("NEG AX\n");
                }

                printCmd("PUSH AX\n");

                $$->lexeme = "NULL";

                delete $2;
                delete $1;
        }| NOT unary_expression{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "unary_expression";
                string body = "NOT unary_expression";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(51,head,body,text);

                insertTOKEN($$,$1);
                $$->root->children.push_back($2->root);

                printToLogRule(head,body);

                $$->server = $2->server;
                $$->lexeme = "NULL";

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

                loadLogicCode3($2);

                $$->isRelExp = $2->isRelExp;
                $$->isBooleanExp = true;
                $$->trueList = $2->falseList;
                $$->falseList = $2->trueList;                                
                $$->nextList = $2->nextList;      

                delete $2;
                delete $1;
        }| factor{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "unary_expression";
                string body = "factor";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(52,head,body,text);

                $$->root->children.push_back($1->root);

                printToLogRule(head,body);

                $$->server = $1->server;
                $$->lexeme = $1->lexeme;
                $$->typeICG = $1->typeICG;

                $$->isRelExp = $1->isRelExp;
                $$->isBooleanExp = $1->isBooleanExp;
                $$->trueList = $1->trueList;
                $$->falseList = $1->falseList;                                
                $$->nextList = $1->nextList;       

                delete $1;

        }
		 ;

factor	: variable{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "factor";
                string body = "variable";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(53,head,body,text);

                $$->root->children.push_back($1->root);

                printToLogRule(head,body);

                $$->server = $1->server;
                $$->lexeme = $1->lexeme;
                $$->typeICG = $1->typeICG;

                delete $1;
        }| ID LPAREN argument_list RPAREN{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "factor";
                string body = "ID LPAREN argument_list RPAREN";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(54,head,body,text);

                insertTOKEN($$,$1);
                insertTOKEN($$,$2);
                $$->root->children.push_back($3->root);
                insertTOKEN($$,$4);

                printToLogRule(head,body);

                SymbolInfo* si = st->lookUpSymbol($1->name);
                if(!si){
                    undeclaredFunctionError($1->name,$1->line_count);
                    $$->server = "UNDEFINED";
                }else{
                    if(!si->isFunction){
                        $$->server = "UNDEFINED";
                        isNotFunctionError($1->name,$1->line_count);
                    }else{
                        $$->server = si->dataType;

                        if(si->isFunctionDeclared){
                            undefinedFunctionError($1->name,$1->line_count);
                        }else{
                            if( si->params.size() != $3->arguments.size() ){
                                NumberOfArgumentsMismatchErrorFunc(si->name,$1->line_count,si->params.size() > $3->arguments.size());
                            }else{
                                int argumentNum = si->params.size();
                                for(int i = 0;i < argumentNum;i++){
                                    if( !argumentTypeCast($3->arguments[i],si->params[i]) ){
                                        argumentTypeCastError(si->name,i+1,$1->line_count);
                                    }
                                }
                            }
                        }
                    }
                }

                printCmd("CALL " + $1->name + "\n");
                printCmd("PUSH AX\n");
                $$->lexeme = "NULL";
                delete $3;
                delete $1;delete $2;delete $4;
        }| LPAREN expression RPAREN{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "factor";
                string body = "LPAREN expression RPAREN";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(55,head,body,text);

                insertTOKEN($$,$1);
                $$->root->children.push_back($2->root);
                insertTOKEN($$,$3);

                printToLogRule(head,body);

                $$->server = $2->server;
                // cout << "------------" << $2->lexeme << endl;

                $$->lexeme = $2->lexeme;
                $$->typeICG = $2->typeICG;

                

                $$->isRelExp = $2->isRelExp;
                $$->isBooleanExp = $2->isBooleanExp;
                $$->trueList = $2->trueList;
                $$->falseList = $2->falseList;                                
                $$->nextList = $2->nextList;                                

                delete $2;
                delete $1;delete $3;
        }| CONST_INT{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "factor";
                string body = "CONST_INT";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(56,head,body,text);

                insertTOKEN($$,$1);

                printToLogRule(head,body);

                $$->server = "INT";
                $$->lexeme = $1->name;
                $$->typeICG = "CONST_INT";

                // tempAsmOut << "MOV AX, " << $1->name << "\n";

                delete $1;

        }| CONST_FLOAT{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "factor";
                string body = "CONST_FLOAT";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(57,head,body,text);

                insertTOKEN($$,$1);

                printToLogRule(head,body);

                $$->server = "FLOAT";
                $$->lexeme = $1->name;

                delete $1;

        }| variable INCOP{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "factor";
                string body = "variable INCOP";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(58,head,body,text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$2);

                printToLogRule(head,body);

                
                loadVariablesCode($1);
                printCmd("PUSH AX\n");

                if( $2->name == "++" ){
                    printCmd("INC AX\n");
                }else if($2->name == "--"){
                    printCmd("DEC AX\n");
                }

                SymbolInfo* si = st->lookUpSymbol($1->lexeme);

                if(si != nullptr){
                    if( $1->typeICG == "variable" ){
                        if( si->isGlobal ){
                            printCmd("MOV " + si->name + ", AX\n");
                        }else{
                            if(si->isParam){
                                printCmd("MOV [BP+" + to_string(si->stackPos) + "], AX\n");
                            }else
                                printCmd("MOV [BP-" + to_string(si->stackPos) + "], AX\n");
                        }
                    }else if( $1->typeICG == "INT_ARRAY" ) {
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


                $$->lexeme = "NULL";

                delete $1;
                delete $2;
        }
	;

argument_list : arguments{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "argument_list";
                string body = "arguments";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(60,head,body,text);

                $$->root->children.push_back($1->root);

                printToLogRule(head,body);

                $$->arguments = $1->arguments;

                delete $1;

        }| {
                $$ = new Info();
                $$->line_count = line_count;

                string head = "argument_list";
                string body = "";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(61,head,body,text);

                printToLogRule(head,body);
        }
        ;

arguments : arguments COMMA logic_expression{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "arguments";
                string body = "arguments COMMA logic_expression";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(62,head,body,text);

                $$->root->children.push_back($1->root);
                insertTOKEN($$,$2);
                $$->root->children.push_back($3->root);

                printToLogRule(head,body);

                $$->arguments = $1->arguments;
                $$->arguments.push_back($3->server);

                $$->lexeme = "NULL";
                loadRelCode($3);
                loadLogicCode2($3);
                loadVariablesCode($3);
                printCmd("PUSH AX\n");

                delete $1;delete $3;
                delete $2;
        }| logic_expression{
                $$ = new Info();
                $$->line_count = $1->line_count;

                string head = "arguments";
                string body = "logic_expression";

                string text = getRuleString(head,body,$$->line_count,line_count);

                $$->root = new Node(63,head,body,text);

                $$->root->children.push_back($1->root);

                $$->server = $1->server;
                $$->arguments.push_back($1->server);
                
                $$->lexeme = "NULL";
                loadRelCode($1);
                loadLogicCode2($1);
                loadVariablesCode($1);
                printCmd("PUSH AX\n");

                printToLogRule(head,body);
                delete $1;
        }
	      ;


%%

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


