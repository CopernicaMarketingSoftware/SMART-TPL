%extra_argument { SmartTpl::Parser *pParser }
%token_type { const SmartTpl::Token* }
%token_prefix TOKEN_

%type   statement       {SmartTpl::Statement*}
%type   statements      {SmartTpl::Statements*}
%type   ifStatement     {SmartTpl::IfStatement*}
%type   elseStatement   {SmartTpl::Statements*}
%type   expression      {SmartTpl::Expression*}

%left AND.
%left OR.
%nonassoc EQ NE GT GE LT LE.
%left PLUS MINUS.
%left TIMES DIVIDE MOD.
%right EXP NOT.
   
%include 
{   
    #include "includes.h"
    #include <iostream>
    #include <assert.h>
}  

%parse_accept {
    // code that is executed when the file was accepted
    std::cout << "File accepted" << std::endl;
}

%parse_failure {
    // code that is execute when a parse error occured
    std::cout << "Parse failure" << std::endl;
}

%syntax_error 
{  
    // @todo    this should probably become an exception
    std::cout << "Syntax error!" << std::endl;  
}   

start           ::= statements(A) .                                         { pParser->add(A); }
statements(A)   ::= statements(B) statement(C) .                            { A = B; A->add(C); }
statements(A)   ::= statement(B) .                                          { A = new SmartTpl::Statements(B); }
statement(A)    ::= ifStatement(B) .                                        { A = B; }
statement(A)    ::= RAW(B) .                                                { A = new SmartTpl::EchoStatement(B); }
statement(A)    ::= EXPRESSION expression(B) .                              { A = B; }
ifStatement(A)  ::= IF expression(B) statements(C) elseStatement(D) .       { A = new SmartTpl::IfStatement(B,C,D); }
ifStatement(A)  ::= IF expression(B) statements(C) ENDIF.                   { A = new SmartTpl::IfStatement(B, C); }
elseStatement(A)::= ELSE statements(B) ENDIF .                              { A = B; }
elseStatement(A)::= ELSEIF expression(B) statements(C) elseStatement(D) .   { A = new SmartTpl::Statements(new SmartTpl::IfStatement(B,C,D)); }
expression(A)   ::= VARIABLE(B) .                                           { A = new SmartTpl::Variable(B); }

