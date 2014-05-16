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

#define YY_NO_INPUT

%}

/**
 *  Normally, the program needs to implement a yywrap() method that is called
 *  when end-of-file was reached. The default one is good enough for now
 */
%option noyywrap

/**
 *  We are no using the method this creates, only causes a unused function warning
 */
%option nounput

/**
 *  We are not a big fan of global variable, hence we turn this into a reentrant
 *  tokenizer
 */
%option reentrant

/**
 *  The user-supplied extra data that we store in the scanner object, is info
 *  about the current token that is being processed.
 */
%option extra-type="SmartTpl::Internal::Tokenizer *"

/**
 *  Output to tokenizer.cpp please
 */
%option outfile="src/tokenizer.cpp"

/**
 *  Exclusive parser mode "INSIDE_CURLY_BRACES" and "IDENTIFIER" and "STRING". This is exclusive,
 *  because other tokens are disabled when in one of these modes
 */
%x INSIDE_CURLY_BRACES
%x IDENTIFIER
%x STRING

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
[\n]                { yyextra->increaseLine(); yyextra->setCurrentToken(new SmartTpl::Internal::Token("\n", 1)); return TOKEN_RAW; }
[^{\n]+             { yyextra->setCurrentToken(new SmartTpl::Internal::Token(yytext, yyleng)); return TOKEN_RAW; }
"{ldelim}"          { yyextra->setCurrentToken(new SmartTpl::Internal::Token("{", 1)); return TOKEN_RAW; }
"{rdelim}"          { yyextra->setCurrentToken(new SmartTpl::Internal::Token("}", 1)); return TOKEN_RAW; }
"{if"[ \t]+         { BEGIN(INSIDE_CURLY_BRACES); return TOKEN_IF; }
"{elseif"[ \t]+     { BEGIN(INSIDE_CURLY_BRACES); return TOKEN_ELSEIF; }
"{else}"            { return TOKEN_ELSE; }
"{foreach"[ \t]+    { BEGIN(INSIDE_CURLY_BRACES); return TOKEN_FOREACH; }
"{/foreach}"        { return TOKEN_ENDFOREACH; }
"{mode="            { BEGIN(IDENTIFIER); return TOKEN_MODE; }
"{escape}"          { return TOKEN_ESCAPE; }
"{assign"[ \t]+     { BEGIN(INSIDE_CURLY_BRACES); return TOKEN_ASSIGN; }
"{$"                { BEGIN(INSIDE_CURLY_BRACES); yyless(1); return TOKEN_EXPRESSION; }
"{/if}"             { return TOKEN_ENDIF; }
"{endif}"           { return TOKEN_ENDIF; }
"{foreachelse}"     { return TOKEN_FOREACH_ELSE; }
"{"                 { yyextra->setCurrentToken(new SmartTpl::Internal::Token(yytext, yyleng)); return TOKEN_RAW; }

    /**
     *  When in expression mode, we are tokenizing an expression inside an {if}
     *  statement or {$variable} or something similar
     */

<INSIDE_CURLY_BRACES>{
    [ \t]
    "$"[a-zA-Z][a-zA-Z0-9_-]*   { yyextra->setCurrentToken(new SmartTpl::Internal::Token(yytext+1, yyleng-1)); return TOKEN_VARIABLE; }
    "true"                      { return TOKEN_TRUE; }
    "false"                     { return TOKEN_FALSE; }
    "and"                       { return TOKEN_AND; }
    "or"                        { return TOKEN_OR; }
    "in"                        { return TOKEN_IN; }
    "as"                        { return TOKEN_AS; }
    "to"                        { return TOKEN_TO; }
    "="                         { return TOKEN_IS; }
    "=>"                        { return TOKEN_ASSIGN_FOREACH; }
    [+-]?[0-9]+                 { yyextra->setCurrentToken(new SmartTpl::Internal::Token(yytext, yyleng)); return TOKEN_INTEGER; }
    "\""                        { BEGIN(STRING); yyextra->setCurrentToken(new SmartTpl::Internal::Token()); }
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
    "|"                         { BEGIN(IDENTIFIER); return TOKEN_PIPE; }
    ":"                         { return TOKEN_COLON; }
    "}"                         { BEGIN(INITIAL); }
}

<IDENTIFIER>{
    [a-zA-Z][a-zA-Z0-9_]*       { BEGIN(INSIDE_CURLY_BRACES); yyextra->setCurrentToken(new SmartTpl::Internal::Token(yytext, yyleng)); return TOKEN_IDENTIFIER; }
}

<STRING>{
    [^\\\"]                     { yyextra->token()->append(yytext, yyleng); }
    "\\\""                      { yyextra->token()->append("\"", 1); }
    "\\"                        { yyextra->token()->append("\\", 1); }
    "\""                        { BEGIN(INSIDE_CURLY_BRACES); return TOKEN_STRING; }
}

%%

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Constructor
 */
Tokenizer::Tokenizer()
{
    // initialize the scanner, and set the tokenizer as the user defined data
    yylex_init_extra(this, &_scanner);
    _line = 1; // We start at line 1, not 0
    _token = nullptr;
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
 *  @param  parent      Parser object that is notified about tokens
 *  @param  buffer      The buffer to process
 *  @param  size        Size of the buffer
 *  @return true if parsing finished succesful, false otherwise
 */
bool Tokenizer::process(TokenProcessor *parent, const char *buffer, size_t size)
{
    // read our data into a buffer that flex wants
    auto *state = yy_scan_bytes(buffer, size, _scanner);

    // ID of the current token
    int id;

    // keep fetching tokens
    while ((id = yylex(_scanner)) != 0)
    {
        // pass token to the parser
        if (parent->process(id, _token) == false)
        {
            // Delete our current token, if there is one
            if (_token) delete _token;

            // clean up the buffer
            yy_delete_buffer(state, _scanner);
            return false;
        }

        // reset current token for next iteration
        _token = nullptr;
    }

    // pass the end-of-file to the parser
    parent->process(0, nullptr);

    // clean up the buffer
    yy_delete_buffer(state, _scanner);
    return true;
}

/**
 *  End namespace
 */
}}
