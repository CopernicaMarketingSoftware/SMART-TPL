%{
/**
 *  Tokenizer.yy
 *
 *  This file contains all the rules for splitting up a *.tpl template into
 *  tokens. This file can be compiled into a *.c file with the 'flex' command.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include "includes.h"

/**
 *  We keep track of the linenumber to ease error messages
 *  @var    int
 *
 *  @todo   enable this, but not by using a global variable
 */
//int line = 1;




%}

/**
 *  Normally, the program needs to implement a yywrap() method that is called
 *  when end-of-file was reached. The default one is good enough for now
 */
%option noyywrap

/**
 *  We are not a big fan of global variable, hence we turn this into a reentrant
 *  tokenizer
 */
%option reentrant

/**
 *  The user-supplied extra data that we store in the scanner object, is info
 *  about the current token that is being processed.
 */
%option extra-type="SmartTpl::Token *"

/**
 *  Output to tokenizer.cpp please
 */
%option outfile="src/tokenizer.cpp"

/**
 *  Exclusive parser mode "EXPRESSION" and "IDENTIFIER". This is exclusive, 
 *  because other tokens are disabled when in one of these modes
 */
%x EXPRESSION
%x IDENTIFIER

/**
 *  The rules start here
 *
 *  The special %% code is an instruction to the flex program that the rules
 *  start here.
 */
%%

    /**
     *  The rules that are active when the parser is in 'template' mode, and just
     *  processes all input until it recognizes something like {if}, {$var} or {foreach}
     */

[^{]+               { yyextra = new SmartTpl::Token(yytext, yyleng); return TOKEN_RAW; }
"{if"[ \t]+         { BEGIN(EXPRESSION); return TOKEN_IF; }
"{elseif"[ \t]+     { BEGIN(EXPRESSION); return TOKEN_ELSEIF; }
"{else}"            { return TOKEN_ELSE; }
"{$"                { BEGIN(EXPRESSION); yyless(1); return TOKEN_EXPRESSION; }
"{/if}"             { return TOKEN_ENDIF; }

    /**
     *  When in expression mode, we are tokenizing an expression inside an {if}
     *  statement or {$variable} or something similar
     */

<EXPRESSION>{
    [ \t]
    [\n]                        { /* @todo increment linenumber */ }
    "$"[a-zA-Z][a-zA-Z0-9]*     { yyextra = new SmartTpl::Token(yytext+1, yyleng-1); return TOKEN_VARIABLE; }
    "true"                      { return TOKEN_TRUE; }
    "false"                     { return TOKEN_FALSE; }
    "and"                       { return TOKEN_AND; }
    "or"                        { return TOKEN_OR; }
    \d+                         { yyextra = new SmartTpl::Token(yytext, yyleng); return TOKEN_INTEGER; }
    "("                         { return TOKEN_LPAREN; }
    ")"                         { return TOKEN_RPAREN; }
    "."                         { BEGIN(IDENTIFIER); return TOKEN_DOT; }
    "["                         { return TOKEN_LBRACK; }
    "]"                         { return TOKEN_RBRACK; }
    "+"                         { return TOKEN_PLUS; }
    "-"                         { return TOKEN_MINUS; }
    "*"                         { return TOKEN_MULTIPLY; }
    "/"                         { return TOKEN_DIVIDE; }
    "=="                        { return TOKEN_EQ; }
    "!="                        { return TOKEN_NE; }
    "<>"                        { return TOKEN_NE; }
    ">"                         { return TOKEN_GT; }
    "<"                         { return TOKEN_LT; }
    ">="                        { return TOKEN_GE; }
    "<="                        { return TOKEN_LE; }
    "&&"                        { return TOKEN_AND; }
    "||"                        { return TOKEN_OR; }
    "}"                         { BEGIN(INITIAL); }
}

<IDENTIFIER>{
    [a-zA-Z][a-zA-Z0-9]*        { BEGIN(EXPRESSION); yyextra = new SmartTpl::Token(yytext, yyleng); return TOKEN_IDENTIFIER; }
}

%%

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Constructor
 */
Tokenizer::Tokenizer()
{
    // initialize the scanner, and set the token as the user defined data
    yylex_init(&_scanner);
}

/**
 *  Destructor
 */
Tokenizer::~Tokenizer() 
{
    // destruct scannerl
    yylex_destroy(_scanner);
}

/**
 *  Run the tokenizer on an input buffer
 *  @param  parent
 *  @return bool
 */
bool Tokenizer::process(TokenProcessor *parent) const
{
    // ID of the current token
    int id;
    
    // keep fetching tokens
    while ((id = yylex(_scanner)) != 0)
    {
        // pass token to the parser
        parent->process(id, yyget_extra(_scanner));
        
        // reset current token for next iteration
        yyset_extra(nullptr, _scanner);
    }
    
    // pass the end-of-file to the parser
    parent->process(0, nullptr);
    
    // done
    return true;
}

/**
 *  Run the tokenizer on an input buffer
 *  @param  parent
 *  @param  buffer
 *  @param  size
 *  @return bool
 */
bool Tokenizer::process(TokenProcessor *parent, const char *buffer, size_t size) const
{
    // set the input buffer
    auto *state = yy_scan_bytes(buffer, size, _scanner);
    
    // run the algorithm
    bool result = process(parent);
    
    // delete the buffer
    yy_delete_buffer(state, _scanner);
    
    // done
    return result;
}

/**
 *  Process a file, and feed all the elements to the parser
 *  @param  parent      Object that is notified about tokens
 *  @param  filename    The file to process
 *  @return bool
 *
 *  @todo   check memory leaks if called multiple times in a row
 *
 */
bool Tokenizer::process(TokenProcessor *parent, const char *filename) const
{
    // open the file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return false;
    
    // restart the buffer
    yyrestart(fp, _scanner);

    // run the algorithm
    bool result = process(parent);
    
    // close the file
    fclose(fp);
    
    // done
    return result;
}

/**
 *  End namespace
 */
}

