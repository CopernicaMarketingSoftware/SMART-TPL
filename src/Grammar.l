%token_type {int}

%left PLUS MINUS.
%left DIVIDE TIMES.

%include {
#include <iostream>
#include "example1.h"
}

%syntax_error {
  std::cout << "Syntax error!" << std::endl;
}

program ::= expr(A).   { std::cout << "Result=" << A << std::endl; }

expr(A) ::= expr(B) MINUS   expr(C).   { A = B - C; }
expr(A) ::= expr(B) PLUS    expr(C).   { A = B + C; }
expr(A) ::= expr(B) TIMES   expr(C).   { A = B * C; }
expr(A) ::= expr(B) DIVIDE  expr(C).   {


         if(C != 0){
           A = B / C;
          }else{
           std::cout << "divide by zero" << std::endl;
           }
}  /* end of DIVIDE */

expr(A) ::= INTEGER(B). { A = B; }



2 ^ (3 ^ 4)

(2 ^ 3) ^ 4


