%extra_argument { SmartTpl::Parser *pParser }
%token_type { const SmartTpl::Token* }
%token_prefix TOKEN_

%type   statement       {SmartTpl::Statement*}
%type   statements      {SmartTpl::Statements*}
%type   ifStatement     {SmartTpl::IfStatement*}
%type   elseStatement   {SmartTpl::Statements*}
%type   expression      {SmartTpl::Expression*}
%type   literal         {SmartTpl::Literal*}
%type   variable        {SmartTpl::Variable*}

%default_destructor { delete $$; }

%left OR.
%left AND.
%left EQ NE.
%left LT LE GT GE.
%left PLUS MINUS.
%left MULTIPLY DIVIDE MOD.
%right EXP NOT.
%left DOT LBRACKET RBRACKET.
   
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

start               ::= statements(A) .                                         { pParser->add(A); }
statements(A)       ::= statements(B) statement(C) .                            { A = B; A->add(C); }
statements(A)       ::= statement(B) .                                          { A = new SmartTpl::Statements(B); }
statement(A)        ::= ifStatement(B) .                                        { A = B; }
statement(A)        ::= RAW(B) .                                                { A = new SmartTpl::EchoStatement(B); }
statement(A)        ::= EXPRESSION expression(B) .                              { A = B; }
ifStatement(A)      ::= IF expression(B) statements(C) elseStatement(D) .       { A = new SmartTpl::IfStatement(B,C,D); }
ifStatement(A)      ::= IF expression(B) statements(C) ENDIF.                   { A = new SmartTpl::IfStatement(B, C); }
elseStatement(A)    ::= ELSE statements(B) ENDIF .                              { A = B; }
elseStatement(A)    ::= ELSEIF expression(B) statements(C) elseStatement(D) .   { A = new SmartTpl::Statements(new SmartTpl::IfStatement(B,C,D)); }
                    

expression(A)       ::= variable(B) .                                           { A = B; }
expression(A)       ::= literal(B) .                                           { A = B; }
expression(A)       ::= LPAREN expression(B) RPAREN .                           { A = B; }
expression(A)       ::= expression(B) PLUS expression(C) .                      { A = new SmartTpl::BinaryOperatorPlus(B, C); }
expression(A)       ::= expression(B) MINUS expression(C) .                     { A = new SmartTpl::BinaryOperatorMinus(B, C); }
expression(A)       ::= expression(B) MULTIPLY expression(C) .                  { A = new SmartTpl::BinaryOperatorMultiply(B, C); }
expression(A)       ::= expression(B) DIVIDE expression(C) .                    { A = new SmartTpl::BinaryOperatorDivide(B, C); }
expression(A)       ::= expression(B) EQ expression(C) .                        { A = new SmartTpl::BinaryOperatorEquals(B, C); }
expression(A)       ::= expression(B) NE expression(C) .                        { A = new SmartTpl::BinaryOperatorNotEquals(B, C); }
expression(A)       ::= expression(B) GT expression(C) .                        { A = new SmartTpl::BinaryOperatorGreater(B, C); }
expression(A)       ::= expression(B) GE expression(C) .                        { A = new SmartTpl::BinaryOperatorGreaterEquals(B, C); }
expression(A)       ::= expression(B) LT expression(C) .                        { A = new SmartTpl::BinaryOperatorLesser(B, C); }
expression(A)       ::= expression(B) LE expression(C) .                        { A = new SmartTpl::BinaryOperatorLesserEquals(B, C); }
expression(A)       ::= expression(B) AND expression(C) .                       { A = new SmartTpl::BinaryOperatorAnd(B, C); }
expression(A)       ::= expression(B) OR expression(C) .                        { A = new SmartTpl::BinaryOperatorOr(B, C); }
literal(A)          ::= TRUE .                                                  { A = new SmartTpl::LiteralBoolean(true); }
literal(A)          ::= FALSE .                                                 { A = new SmartTpl::LiteralBoolean(false); }
literal(A)          ::= INTEGER(B) .                                            { A = new SmartTpl::LiteralInteger(B); }
variable(A)         ::= VARIABLE(B) .                                           { A = new SmartTpl::LiteralVariable(B); }
variable(A)         ::= variable(B) LBRACK expression(C) RBRACK .               { A = new SmartTpl::VariableArrayAccess(B,C); }
variable(A)         ::= variable(B) DOT IDENTIFIER(C) .                         { A = new SmartTpl::LiteralArrayAccess(B,C); }

