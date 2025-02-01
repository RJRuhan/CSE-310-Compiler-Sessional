%option noyywrap

%x CHAR_STATE
%x STRING_STATE
%x SL_COMMENT_STATE
%x ML_COMMENT_STATE

%{
#include<bits/stdc++.h>
#include "1805017.h"
#include"Info.h"
#include"y.tab.h"

using namespace std;

extern ofstream logout;
extern ofstream errorOut;

extern YYSTYPE yylval;
void yyerror(string );

int line_count=1;
int err_count = 0;
int line_inside_cmnt_str = 0;

string char_literal;
string char_literal_plain;

string str;
string str_plain;

string comment;

string UPPER(string s)
{
	for(auto& ch:s)
        ch = toupper(ch);
	return s;
}

void printToLogTokenFound(string type,string name,int lc){
    logout << "Line# " << lc << ": Token <" << type << "> Lexeme " << name << " found\n";
}


%}

WHITESPACE [ \t\f\r\v]+
LETTER [a-zA-Z_]
ALNUM [a-zA-Z0-9_]
DIGIT [0-9]
DECIMAL \.{DIGIT}+
EXPONENT E[+-]?{DIGIT}+
FLOAT1 {DIGIT}*{DECIMAL}{EXPONENT}?
FLOAT2 {DIGIT}+{EXPONENT}
FLOAT {FLOAT1}|{FLOAT2}
RELOP "<"|"<="|"=="|"!="|">="|">"
BITOP "&"|"|"|"^"|"<<"|">>"
ID {LETTER}{ALNUM}*
NEWLINE [\r]?\n

%%

{WHITESPACE} {}
{NEWLINE} {line_count++;}

"if" { SymbolInfo *s= new  SymbolInfo(yytext,"IF",line_count);yylval.si = s;printToLogTokenFound("IF",yytext,line_count);return IF; }
"else" { SymbolInfo *s= new  SymbolInfo(yytext,"ELSE",line_count);yylval.si = s;printToLogTokenFound("ELSE",yytext,line_count);return ELSE; }
"for" { SymbolInfo *s= new  SymbolInfo(yytext,"FOR",line_count);yylval.si = s;printToLogTokenFound("FOR",yytext,line_count);return FOR; }
"while" { SymbolInfo *s= new  SymbolInfo(yytext,"WHILE",line_count);yylval.si = s;printToLogTokenFound("WHILE",yytext,line_count);return WHILE; }
"do" { SymbolInfo *s= new  SymbolInfo(yytext,"DO",line_count);yylval.si = s;printToLogTokenFound("DO",yytext,line_count);return DO; }
"break" { SymbolInfo *s= new  SymbolInfo(yytext,"BREAK",line_count);yylval.si = s;printToLogTokenFound("BREAK",yytext,line_count);return BREAK; }
"int" { SymbolInfo *s= new  SymbolInfo(yytext,"INT",line_count);yylval.si = s;printToLogTokenFound("INT",yytext,line_count);return INT; }
"char" { SymbolInfo *s= new  SymbolInfo(yytext,"CHAR",line_count);yylval.si = s;printToLogTokenFound("CHAR",yytext,line_count);return CHAR; }
"float" { SymbolInfo *s= new  SymbolInfo(yytext,"FLOAT",line_count);yylval.si = s;printToLogTokenFound("FLOAT",yytext,line_count);return FLOAT; }
"double" { SymbolInfo *s= new  SymbolInfo(yytext,"DOUBLE",line_count);yylval.si = s;printToLogTokenFound("DOUBLE",yytext,line_count);return DOUBLE; }
"void" { SymbolInfo *s= new  SymbolInfo(yytext,"VOID",line_count);yylval.si = s;printToLogTokenFound("VOID",yytext,line_count);return VOID; }
"return" { SymbolInfo *s= new  SymbolInfo(yytext,"RETURN",line_count);yylval.si = s;printToLogTokenFound("RETURN",yytext,line_count);return RETURN; }
"switch" { SymbolInfo *s= new  SymbolInfo(yytext,"SWITCH",line_count);yylval.si = s;printToLogTokenFound("SWITCH",yytext,line_count);return SWITCH; }
"case" { SymbolInfo *s= new  SymbolInfo(yytext,"CASE",line_count);yylval.si = s;printToLogTokenFound("CASE",yytext,line_count);return CASE; }
"default" { SymbolInfo *s= new  SymbolInfo(yytext,"DEFAULT",line_count);yylval.si = s;printToLogTokenFound("DEFAULT",yytext,line_count);return DEFAULT; }
"continue" { SymbolInfo *s= new  SymbolInfo(yytext,"CONTINUE",line_count);yylval.si = s;printToLogTokenFound("CONTINUE",yytext,line_count);return CONTINUE; }
"println"	{ SymbolInfo *s= new  SymbolInfo(yytext,"PRINTLN",line_count);yylval.si = s;printToLogTokenFound("PRINTLN",yytext,line_count);return PRINTLN; }

{DIGIT}+ 	{

				SymbolInfo *s= new  SymbolInfo(yytext,"CONST_INT",line_count);
				yylval.si = s;
				printToLogTokenFound("CONST_INT",yytext,line_count);
				return CONST_INT;

			}

{FLOAT}    {
				SymbolInfo *s= new  SymbolInfo(yytext,"CONST_FLOAT",line_count);
                yylval.si = s;
                printToLogTokenFound("CONST_FLOAT",yytext,line_count);
                return CONST_FLOAT;
            }

{DIGIT}*(\.{DIGIT}+)\.[0-9\.E]*  {
                                        //Error at line# 2: ILLFORMED_NUMBER 1E10.7
                                        err_count++;
                                        errorOut<<"Error at line# "<< line_count <<": TOO_MANY_DECIMAL_POINTS "<<yytext<<"\n";
                                    }


{DIGIT}*(\.{DIGIT}+)?[E][+-]?{DIGIT}*(\.)[0-9\.E+-]*  {
                                                                err_count++;
                                                                errorOut<<"Error at line# "<< line_count <<": ILLFORMED_NUMBER "<<yytext<<"\n";
                                                        }


"+"|"-"		{
                SymbolInfo *s= new  SymbolInfo(yytext,"ADDOP",line_count);
                yylval.si = s;
				printToLogTokenFound("ADDOP",yytext,line_count);
                return ADDOP;
            }

"*"|"/"|"%"		{
                    SymbolInfo *s= new  SymbolInfo(yytext,"MULOP",line_count);
                    yylval.si = s;
                    printToLogTokenFound("MULOP",yytext,line_count);
                    return MULOP;
                }

"++"|"--"		{
                    SymbolInfo *s= new  SymbolInfo(yytext,"INCOP",line_count);
                    yylval.si = s;
                    printToLogTokenFound("INCOP",yytext,line_count);
                    return INCOP;
            }


{RELOP}   {
            SymbolInfo *s= new  SymbolInfo(yytext,"RELOP",line_count);
            yylval.si = s;
            printToLogTokenFound("RELOP",yytext,line_count);
			return RELOP;
		}

"="		{
            SymbolInfo *s= new  SymbolInfo(yytext,"ASSIGNOP",line_count);
            yylval.si = s;
            printToLogTokenFound("ASSIGNOP",yytext,line_count);
			return ASSIGNOP;
		}

"&&"|"||"   {
                SymbolInfo *s= new  SymbolInfo(yytext,"LOGICOP",line_count);
                yylval.si = s;
                printToLogTokenFound("LOGICOP",yytext,line_count);
                return LOGICOP;
            }

{BITOP}   {
            SymbolInfo *s= new  SymbolInfo(yytext,"BITOP",line_count);
            yylval.si = s;
            printToLogTokenFound("BITOP",yytext,line_count);
			return BITOP;
		}

"!"		{
            SymbolInfo *s= new  SymbolInfo(yytext,"NOT",line_count);
            yylval.si = s;
            printToLogTokenFound("NOT",yytext,line_count);
			return NOT;
		}

"("		{
            SymbolInfo *s= new  SymbolInfo(yytext,"LPAREN",line_count);
            yylval.si = s;
            printToLogTokenFound("LPAREN",yytext,line_count);
			return LPAREN;
		}

")"		{
			SymbolInfo *s= new  SymbolInfo(yytext,"RPAREN",line_count);
            yylval.si = s;
            printToLogTokenFound("RPAREN",yytext,line_count);
            return RPAREN;
		}

"{"		{
			SymbolInfo *s= new  SymbolInfo(yytext,"LCURL",line_count);
            yylval.si = s;
            printToLogTokenFound("LCURL",yytext,line_count);
            return LCURL;
		}

"}"		{
			SymbolInfo *s= new  SymbolInfo(yytext,"RCURL",line_count);
            yylval.si = s;
            printToLogTokenFound("RCURL",yytext,line_count);
			return RCURL;
		}


"["		{
            SymbolInfo *s= new  SymbolInfo(yytext,"LSQUARE",line_count);
            yylval.si = s;
            printToLogTokenFound("LSQUARE",yytext,line_count);
			return LSQUARE;
		}

"]"		{
            SymbolInfo *s= new  SymbolInfo(yytext,"RSQUARE",line_count);
            yylval.si = s;
            printToLogTokenFound("RSQUARE",yytext,line_count);
			return RSQUARE;
		}

","		{
			SymbolInfo *s= new  SymbolInfo(yytext,"COMMA",line_count);
            yylval.si = s;
            printToLogTokenFound("COMMA",yytext,line_count);
            return COMMA;
		}

";"		{
            SymbolInfo *s= new  SymbolInfo(yytext,"SEMICOLON",line_count);
            yylval.si = s;
            printToLogTokenFound("SEMICOLON",yytext,line_count);
			return SEMICOLON;
		}

{ID}  {
            SymbolInfo *s= new  SymbolInfo(yytext,"ID",line_count);
            yylval.si = s;
            printToLogTokenFound("ID",yytext,line_count);
            return ID;

      }

{DIGIT}+{ID}    {
                    err_count++;
                    errorOut<<"Error at line# "<< line_count <<": INVALID_ID_SUFFIX_NUM_PREFIX "<< yytext <<"\n";

                }

\'  {
        char_literal.clear();
        char_literal_plain.clear();
        BEGIN CHAR_STATE;
    }


\"  {
        line_inside_cmnt_str = 0;
        str.clear();
        str_plain.clear();
        BEGIN STRING_STATE;

    }

\/\/   {
            line_inside_cmnt_str = 0;
            comment.clear();
            comment += "//";
            BEGIN SL_COMMENT_STATE;

        }

\/\*   {
            line_inside_cmnt_str = 0;
            comment.clear();
            comment += "/*";
            BEGIN ML_COMMENT_STATE;

        }

<CHAR_STATE>\\0   {   char_literal += "\0"; char_literal_plain += "\\0"; }
<CHAR_STATE>\\n   {   char_literal += "\n"; char_literal_plain += "\\n"; }
<CHAR_STATE>\\a   {   char_literal += "\a"; char_literal_plain += "\\a"; }
<CHAR_STATE>\\b   {   char_literal += "\b"; char_literal_plain += "\\b"; }
<CHAR_STATE>\\v   {   char_literal += "\v"; char_literal_plain += "\\v"; }
<CHAR_STATE>\\t   {   char_literal += "\t"; char_literal_plain += "\\t"; }
<CHAR_STATE>\\f   {   char_literal += "\f"; char_literal_plain += "\\f"; }
<CHAR_STATE>\\r   {   char_literal += "\r"; char_literal_plain += "\\r"; }
<CHAR_STATE>\\\"  {   char_literal += "\""; char_literal_plain += "\\\""; }
<CHAR_STATE>\\\'  {  char_literal += "\'"; char_literal_plain += "\\\'"; }
<CHAR_STATE>\\\\  {  char_literal += "\\"; char_literal_plain += "\\\\"; }

<CHAR_STATE><<EOF>> {
                        err_count++;
                        //logout<<"Error at line# "<< line_count <<": UNFINISHED_CONST_CHAR '" << char_literal_plain << "\n";
                        BEGIN INITIAL;
                    }

<CHAR_STATE>[\r]?\n {
                        err_count++;
                        //logout<<"Error at line# "<< line_count <<": UNFINISHED_CONST_CHAR '"<< char_literal_plain << "\n";
                        line_count++;
                        BEGIN INITIAL;
                    }

<CHAR_STATE>\'	{
                    if( (int)char_literal.size() == 0 ){

                        if( char_literal_plain == "\\0" ){
                            //SymbolInfo *s= new  SymbolInfo(char_literal,"CONST_CHAR");
                            //yylval.si = s;
                            //return CONST_CHAR;
                        }
                        else{

                            err_count++;
                            //logout<<"Error at line# "<< line_count <<": EMPTY_CONST_CHAR '"<<char_literal_plain << "'\n";
                        }
                    }
                    else if((int)char_literal.size()==1){

                            //SymbolInfo *s= new  SymbolInfo(char_literal,"CONST_CHAR");
                            //yylval.si = s;
                            //return CONST_CHAR;
                    }
                    else{
                            err_count++;
                            //logout<<"Error at line# "<< line_count <<": MULTICHAR_CONST_CHAR '"<<char_literal_plain<< "'\n";
                            BEGIN INITIAL;
                    }

                    BEGIN INITIAL;
                }


<CHAR_STATE>.	{ char_literal += yytext[0]; char_literal_plain += yytext[0]; }



<STRING_STATE>\\0   {   str += "\0"; str_plain += "\\0"; }
<STRING_STATE>\\n   {   str += "\n"; str_plain += "\\n"; }
<STRING_STATE>\\a   {   str += "\a"; str_plain += "\\a"; }
<STRING_STATE>\\b   {   str += "\b"; str_plain += "\\b"; }
<STRING_STATE>\\v   {   str += "\v"; str_plain += "\\v"; }
<STRING_STATE>\\t   {   str += "\t"; str_plain += "\\t"; }
<STRING_STATE>\\f   {   str += "\f"; str_plain += "\\f"; }
<STRING_STATE>\\r   {   str += "\r"; str_plain += "\\r"; }
<STRING_STATE>\\\"  {   str += "\""; str_plain += "\\\""; }
<STRING_STATE>\\\'  {   str += "\'"; str_plain += "\\\'"; }
<STRING_STATE>\\\\  {   str += "\\"; str_plain += "\\\\"; }



<STRING_STATE>\\\r\n    {
                            line_inside_cmnt_str++;
                            str_plain += "\\\r\n" ;
                        }

<STRING_STATE>\\\n      {
                            line_inside_cmnt_str++;
                            str_plain += "\\\n" ;
                        }

<STRING_STATE>[\r]?\n   {
                            err_count++;
                            line_count += line_inside_cmnt_str;
                            //logout<<"Error at line# "<< line_count <<": UNFINISHED_STRING \""<<str_plain<<"\n";
                            line_count++;
                            line_inside_cmnt_str = 0;

                            BEGIN(INITIAL);
                        }

<STRING_STATE><<EOF>>   {
                            err_count++;
                            line_count += line_inside_cmnt_str;

                            //logout<<"Error at line# "<< line_count <<": UNFINISHED_STRING \""<<str_plain<<"\n";

                            line_inside_cmnt_str = 0;

                            BEGIN(INITIAL);
                        }

<STRING_STATE>\" {

                    if( line_inside_cmnt_str == 0 ){
                        //SymbolInfo *s= new  SymbolInfo(str,"SINGLE_LINE_STRING");
                        //yylval.si = s;
                        //return SINGLE_LINE_STRING;
                    }
                    else{
                        //SymbolInfo *s= new  SymbolInfo(str,"MULTI_LINE_STRING");
                        //yylval.si = s;
                        //return MULTI_LINE_STRING;
                    }


                    line_count += line_inside_cmnt_str;
                    line_inside_cmnt_str = 0;
                    BEGIN INITIAL;

                }


<STRING_STATE>. {
                    str += yytext[0];str_plain += yytext[0];

                }


<SL_COMMENT_STATE>\\\r\n     {
                                line_inside_cmnt_str++;
                                comment += "\\\r\n";
                            }

<SL_COMMENT_STATE>\\\n       {
                                line_inside_cmnt_str++;
                                comment += "\\\n";
                            }

<SL_COMMENT_STATE>[\r]?\n    {

                                line_inside_cmnt_str++;
                                //logout << "Line# " << line_count << ": Token <SINGLE LINE COMMENT> Lexeme " << comment << " found\n";

                                line_count += line_inside_cmnt_str;
                                line_inside_cmnt_str = 0;

                                BEGIN(INITIAL);
                            }

<SL_COMMENT_STATE><<EOF>>    {

                                //logout<<"Line# "<< line_count <<": Token " <<"<SINGLE LINE COMMENT>"<<" Lexeme "<<comment<<" found\n";

                                line_count += line_inside_cmnt_str;
                                line_inside_cmnt_str = 0;

                                BEGIN(INITIAL);
                            }

<SL_COMMENT_STATE>.         { comment += yytext[0];}


<ML_COMMENT_STATE>\*\/      {

                                comment += "*/";
                                //logout << "Line# " << line_count << ": Token <MULTI LINE COMMENT> Lexeme "<<comment<<" found\n";

                                line_count += line_inside_cmnt_str;
                                line_inside_cmnt_str = 0;

                                BEGIN(INITIAL);
                            }

<ML_COMMENT_STATE><<EOF>>   {

                                err_count++;
                                line_count += line_inside_cmnt_str;
                                //logout<<"Error at line# "<< line_count <<": UNFINISHED_COMMENT "<<comment<< "\n";

                                line_inside_cmnt_str = 0;

                                BEGIN(INITIAL);
                            }

<ML_COMMENT_STATE>\r        { comment += "\r";}
<ML_COMMENT_STATE>\n        { line_inside_cmnt_str++; comment += "\n";}
<ML_COMMENT_STATE>.         { comment += yytext[0];}


. {
    err_count++;
    errorOut<<"Error at line# "<< line_count <<": UNRECOGNIZED_CHAR "<< yytext <<"\n";
}

%%

