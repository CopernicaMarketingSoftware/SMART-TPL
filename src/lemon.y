%token_type {const SmartTpl::Token*}
%token_prefix TOKEN_

%left AND.
%left OR.
%nonassoc EQ NE GT GE LT LE.
%left PLUS MINUS.
%left TIMES DIVIDE MOD.
%right EXP NOT.
   
%include 
{   
    #include "token.h"
    #include <iostream>
    #include <assert.h>
}  
   
%syntax_error 
{  
    std::cout << "Syntax error!" << std::endl;  
}   

start           ::= statements .
statements      ::= statement statements .
statement       ::= expression .
statement       ::= ifStatement .
statement       ::= RAW .
statement       ::= EXPRESSION expression .
ifStatement     ::= IF expression statements elseStatement .
elseStatement   ::= ENDIF .
elseStatement   ::= ELSE statements ENDIF .
elseStatement   ::= ELSEIF expression statements elseStatement .
expression      ::= VARIABLE .

