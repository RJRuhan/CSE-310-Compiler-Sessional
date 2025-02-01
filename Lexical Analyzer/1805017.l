%option noyywrap

%x CHAR_STATE
%x STRING_STATE
%x SL_COMMENT_STATE
%x ML_COMMENT_STATE

%{
#include<bits/stdc++.h>
#include "1805017.h"

using namespace std;

int line_count=1;
int error_count = 0;
int line_inside_cmnt_str = 0;

string char_literal;
string char_literal_plain;

string str;
string str_plain;

string comment;



ofstream logout;
ofstream Tokenout;

string UPPER(string s)
{
	for(auto& ch:s)
        ch = toupper(ch);
	return s;
}

int bucketSize = 10;
SymbolTable st(bucketSize);

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

{NEWLINE} {line_count++;}

if|else|for|while|do|break|int|char|float|double|void|return|switch|case|default|continue	{
				Tokenout << "<" << UPPER(yytext) << ", " << yytext <<  ">\n";
				logout<<"Line# "<< line_count <<": Token <"<<UPPER(yytext)<< "> Lexeme "<<yytext<<" found\n";
	 		}


{DIGIT}+ 	{
				Tokenout << "<CONST_INT, " << yytext << ">\n";
				logout << "Line# " << line_count << ": Token <CONST_INT> Lexeme " << yytext << " found\n";

			}

{FLOAT}    {
                Tokenout << "<CONST_FLOAT, " << yytext << ">\n";
				logout << "Line# " << line_count << ": Token <CONST_FLOAT> Lexeme " << yytext << " found\n";

            }

{DIGIT}*(\.{DIGIT}+)\.[0-9\.E]*  {
                                        //Error at line# 2: ILLFORMED_NUMBER 1E10.7
                                        error_count++;
                                        logout<<"Error at line# "<< line_count <<": TOO_MANY_DECIMAL_POINTS "<<yytext<<"\n";
                                    }


{DIGIT}*(\.{DIGIT}+)?[E][+-]?{DIGIT}*(\.)[0-9\.E+-]*  {
                                                                error_count++;
                                                                logout<<"Error at line# "<< line_count <<": ILLFORMED_NUMBER "<<yytext<<"\n";
                                                            }


"+"|"-"		{
                Tokenout << "<ADDOP, " << yytext << ">\n";
                logout << "Line# " << line_count << ": Token <ADDOP> Lexeme " << yytext << " found\n";

            }

"*"|"/"|"%"		{
                    Tokenout << "<MULOP, " << yytext << ">\n";
                    logout << "Line# " << line_count << ": Token <MULOP> Lexeme " << yytext << " found\n";
                }

"++"|"--"		{
                    Tokenout << "<INCOP, " << yytext << ">\n";
                    logout << "Line# " << line_count << ": Token <INCOP> Lexeme " << yytext << " found\n";
                }

{RELOP}   {
			Tokenout << "<RELOP, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <RELOP> Lexeme " << yytext << " found\n";
		}

"="		{
			Tokenout << "<ASSIGNOP, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <ASSIGNOP> Lexeme " << yytext << " found\n";
		}

"&&"|"||"   {
                Tokenout << "<LOGICOP, " << yytext << ">\n";
                logout << "Line# " << line_count << ": Token <LOGICOP> Lexeme " << yytext << " found\n";
            }

{BITOP}   {
			Tokenout << "<BITOP, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <BITOP> Lexeme " << yytext << " found\n";
		}

"!"		{
			Tokenout << "<NOT, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <NOT> Lexeme " << yytext << " found\n";
		}

"("		{
			Tokenout << "<LPAREN, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <LPAREN> Lexeme " << yytext << " found\n";
		}

")"		{
			Tokenout << "<RPAREN, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <RPAREN> Lexeme " << yytext << " found\n";
		}

"{"		{
			Tokenout << "<LCURL, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <LCURL> Lexeme " << yytext << " found\n";
            st.enterScope();
		}

"}"		{
			Tokenout << "<RCURL, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <RCURL> Lexeme " << yytext << " found\n";
            st.exitScope();
		}


"["		{
			Tokenout << "<LSQUARE, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <LSQUARE> Lexeme " << yytext << " found\n";
		}

"]"		{
			Tokenout << "<RSQUARE, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <RSQUARE> Lexeme " << yytext << " found\n";
		}

","		{
			Tokenout << "<COMMA, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <COMMA> Lexeme " << yytext << " found\n";
		}

";"		{
			Tokenout << "<SEMICOLON, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <SEMICOLON> Lexeme " << yytext << " found\n";
		}

{ID}  {
            Tokenout << "<ID, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <ID> Lexeme " << yytext << " found\n";

            if( st.insertSymbol(yytext,"ID") ){
                st.printAll(logout);
            }
            else
                logout << "\t" << yytext << " already exisits in the current ScopeTable\n";

      }

{DIGIT}+{ID}    {
                    error_count++;
                    logout<<"Error at line# "<< line_count <<": INVALID_ID_SUFFIX_NUM_PREFIX "<< yytext <<"\n";

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
                        error_count++;
                        logout<<"Error at line# "<< line_count <<": UNFINISHED_CONST_CHAR '" << char_literal_plain << "\n";
                        BEGIN INITIAL;
                    }

<CHAR_STATE>[\r]?\n {
                        error_count++;
                        logout<<"Error at line# "<< line_count <<": UNFINISHED_CONST_CHAR '"<< char_literal_plain << "\n";
                        line_count++;
                        BEGIN INITIAL;
                    }

<CHAR_STATE>\'	{
                    if( (int)char_literal.size() == 0 ){

                        if( char_literal_plain == "\\0" ){

                            Tokenout << "<CONST_CHAR, " << char_literal << ">\n";
                            logout<<"Line# "<< line_count <<": Token " <<"<CONST_CHAR>"<<" Lexeme "<< char_literal <<" found\n";
                        }
                        else{

                            error_count++;
                            logout<<"Error at line# "<< line_count <<": EMPTY_CONST_CHAR '"<<char_literal_plain << "'\n";
                        }
                    }
                    else if((int)char_literal.size()==1){

                            Tokenout << "<CONST_CHAR, " << char_literal <<">\n";
                            logout<<"Line# "<< line_count <<": Token " <<"<CONST_CHAR>"<<" Lexeme "<<char_literal<<" found\n";
                    }
                    else{
                            error_count++;
                            logout<<"Error at line# "<< line_count <<": MULTICHAR_CONST_CHAR '"<<char_literal_plain<< "'\n";
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
                            error_count++;
                            line_count += line_inside_cmnt_str;
                            logout<<"Error at line# "<< line_count <<": UNFINISHED_STRING \""<<str_plain<<"\n";
                            line_count++;
                            line_inside_cmnt_str = 0;

                            BEGIN(INITIAL);
                        }

<STRING_STATE><<EOF>>   {
                            error_count++;
                            line_count += line_inside_cmnt_str;

                            logout<<"Error at line# "<< line_count <<": UNFINISHED_STRING \""<<str_plain<<"\n";

                            line_inside_cmnt_str = 0;

                            BEGIN(INITIAL);
                        }

<STRING_STATE>\" {

                    if( line_inside_cmnt_str == 0 ){
                        Tokenout << "<SINGLE LINE STRING, " << str << ">\n";
                        logout << "Line# " << line_count << ": Token <SINGLE LINE STRING> Lexeme " << "\"" << str_plain << "\"" << " found\n";
                    }
                    else{
                        Tokenout << "<MULTI LINE STRING, " << str << ">\n";
                        logout << "Line# " << line_count << ": Token <MULTI LINE STRING> Lexeme " << "\"" << str_plain << "\"" << " found\n";
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
                                logout << "Line# " << line_count << ": Token <SINGLE LINE COMMENT> Lexeme " << comment << " found\n";

                                line_count += line_inside_cmnt_str;
                                line_inside_cmnt_str = 0;

                                BEGIN(INITIAL);
                            }

<SL_COMMENT_STATE><<EOF>>    {

                                logout<<"Line# "<< line_count <<": Token " <<"<SINGLE LINE COMMENT>"<<" Lexeme "<<comment<<" found\n";

                                line_count += line_inside_cmnt_str;
                                line_inside_cmnt_str = 0;

                                BEGIN(INITIAL);
                            }

<SL_COMMENT_STATE>.         { comment += yytext[0];}


<ML_COMMENT_STATE>\*\/      {

                                comment += "*/";
                                logout << "Line# " << line_count << ": Token <MULTI LINE COMMENT> Lexeme "<<comment<<" found\n";

                                line_count += line_inside_cmnt_str;
                                line_inside_cmnt_str = 0;

                                BEGIN(INITIAL);
                            }

<ML_COMMENT_STATE><<EOF>>   {

                                error_count++;
                                line_count += line_inside_cmnt_str;
                                logout<<"Error at line# "<< line_count <<": UNFINISHED_COMMENT "<<comment<< "\n";

                                line_inside_cmnt_str = 0;

                                BEGIN(INITIAL);
                            }

<ML_COMMENT_STATE>\r        { comment += "\r";}
<ML_COMMENT_STATE>\n        { line_inside_cmnt_str++; comment += "\n";}
<ML_COMMENT_STATE>.         { comment += yytext[0];}


@|`     {
            error_count++;
            logout<<"Error at line# "<< line_count <<": UNRECOGNIZED_CHAR "<< yytext <<"\n";
        }

%%

int main(int argc, char** argv) {

    st.enterScope();

	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}

	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}

	logout.open("log.txt");
	Tokenout.open("token.txt");


	yyin= fin;
	yylex();

	st.printAll(logout);
	logout << "Total lines: " << line_count << "\n";
	logout << "Total errors: " << error_count << "\n";


	fclose(yyin);
	Tokenout.close();
	logout.close();
	return 0;
}
