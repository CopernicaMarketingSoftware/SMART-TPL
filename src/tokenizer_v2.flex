%{
/**
 *  Tokenizer_v2.yy
 *
 *  This file contains all the rules for splitting up a *.tpl template into
 *  tokens. This file can be compiled into a *.c file with the 'flex' command.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2017 Copernica BV
 */
#include "includes.h"

// Defining YY_NO_INPUT here stops flex from generating (and emiting) the unused yyinput() function
#define YY_NO_INPUT

// Defining ECHO here stops flex from sometimes printing failed to tokenize characters to stdout
#define ECHO

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
 *  Use the SmartTpl prefix to avoid colission with other flex generated parsers
 */
%option prefix="SmartTplv2"

/**
 *  Make this scanner case insensitive
 */
%option case-insensitive

/**
 *  The user-supplied extra data that we store in the scanner object, is info
 *  about the current token that is being processed.
 */
%option extra-type="SmartTpl::Internal::v2::Tokenizer *"

/**
 *  Output to tokenizer.cpp please
 */
%option outfile="src/tokenizer_v2.cpp"

/**
 *  Exclusive parser mode "INSIDE_CURLY_BRACES" and "IDENTIFIER" and "STRING". This is exclusive,
 *  because other tokens are disabled when in one of these modes
 */
%x RAW
%x INSIDE_CURLY_BRACES
%x IDENTIFIER
%x STRING_DOUBLE_QUOTES
%x STRING_SINGLE_QUOTES
%x LITERAL

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

"\n"                { yyextra->increaseLine(); yyextra->setCurrentToken(new SmartTpl::Internal::Token('\n')); BEGIN(RAW); }
[^{\n]+             { yyextra->setCurrentToken(new SmartTpl::Internal::Token(yytext, yyleng)); BEGIN(RAW); }
"{ldelim}"          { yyextra->setCurrentToken(new SmartTpl::Internal::Token('{')); BEGIN(RAW); }
"{rdelim}"          { yyextra->setCurrentToken(new SmartTpl::Internal::Token('}')); BEGIN(RAW); }
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
"{literal}"         { BEGIN(LITERAL); yyextra->setCurrentToken(new SmartTpl::Internal::Token()); } // We create an empty token here, we will just append to it later
"{"[ \t\n]          { yyextra->setCurrentToken(new SmartTpl::Internal::Token(yytext, yyleng)); return TOKEN_RAW; }
"{"                 { BEGIN(INSIDE_CURLY_BRACES); return TOKEN_EXPRESSION; }
"{"[a-z]*"}"        { return -1; };

    /**
     *  These rules are just to build up raw strings as one big string instead of a bunch of
     *  smaller strings. The EOF rule here is just so we can actually properly end with raw
     *  strings as well, which is rather common.
     */

<RAW>{
    "\n"                        { yyextra->increaseLine(); yyextra->token()->push_back('\n'); }
    [^{\n]+                     { yyextra->token()->append(yytext, yyleng); }
    "{ldelim}"                  { yyextra->token()->push_back('{'); }
    "{rdelim}"                  { yyextra->token()->push_back('}'); }
    "{"                         { BEGIN(INITIAL); unput('{'); return TOKEN_RAW; }
    <<EOF>>                     { BEGIN(INITIAL); return TOKEN_RAW; }
}

    /**
     *  When in expression mode, we are tokenizing an expression inside an {if}
     *  statement or {$variable} or something similar
     */

<INSIDE_CURLY_BRACES>{
    [ \t]
    "$"[a-z][a-z0-9_-]*         { yyextra->setCurrentToken(new SmartTpl::Internal::Token(yytext+1, yyleng-1)); return TOKEN_VARIABLE; }
    "true"                      { return TOKEN_TRUE; }
    "false"                     { return TOKEN_FALSE; }
    "and"                       { return TOKEN_AND; }
    "or"                        { return TOKEN_OR; }
    "in"                        { return TOKEN_IN; }
    "as"                        { return TOKEN_AS; }
    "to"                        { return TOKEN_TO; }
    "="                         { return TOKEN_IS; }
    "=>"                        { return TOKEN_ASSIGN_FOREACH; }
    [0-9]+                      { yyextra->setCurrentToken(new SmartTpl::Internal::Token(yytext, yyleng)); return TOKEN_INTEGER; }
    [0-9]+"."[0-9]+("e"[-+]?[0-9]+)? { yyextra->setCurrentToken(new SmartTpl::Internal::Token(yytext, yyleng)); return TOKEN_DOUBLE; }
    "\""                        { BEGIN(STRING_DOUBLE_QUOTES); yyextra->setCurrentToken(new SmartTpl::Internal::Token()); } // We create an empty token here, we will just append to it from STRING
    "\'"                        { BEGIN(STRING_SINGLE_QUOTES); yyextra->setCurrentToken(new SmartTpl::Internal::Token()); } // We create an empty token here, we will just append to it from STRING
    "("                         { return TOKEN_LPAREN; }
    ")"                         { return TOKEN_RPAREN; }
    "."                         { BEGIN(IDENTIFIER); return TOKEN_DOT; }
    "["                         { return TOKEN_LBRACK; }
    "]"                         { return TOKEN_RBRACK; }
    "+"                         { return TOKEN_PLUS; }
    "-"                         { return TOKEN_MINUS; }
    "*"                         { return TOKEN_MULTIPLY; }
    "/"                         { return TOKEN_DIVIDE; }
    "%"                         { return TOKEN_MOD; }
    "=="                        { return TOKEN_EQ; }
    "eq"                        { return TOKEN_EQ; }
    "!="                        { return TOKEN_NE; }
    "<>"                        { return TOKEN_NE; }
    "ne"                        { return TOKEN_NE; }
    ">"                         { return TOKEN_GT; }
    "gt"e?                      { return TOKEN_GT; }
    "<"                         { return TOKEN_LT; }
    "lt"e?                      { return TOKEN_LT; }
    ">="                        { return TOKEN_GE; }
    "ge"                        { return TOKEN_GE; }
    "<="                        { return TOKEN_LE; }
    "le"                        { return TOKEN_LE; }
    "not"                       { return TOKEN_NOT; }
    "!"                         { return TOKEN_NOT; }
    "&&"                        { return TOKEN_AND; }
    "||"                        { return TOKEN_OR; }
    "|"                         { BEGIN(IDENTIFIER); return TOKEN_PIPE; }
    ":"                         { return TOKEN_COLON; }
    "}"                         { BEGIN(INITIAL); return TOKEN_END_BRACES; }
    .                           { return -1; }
}

    /**
     *  This set of rules is for matching identifiers like modifiers
     */

<IDENTIFIER>{
    [a-z][a-z0-9_]*             { BEGIN(INSIDE_CURLY_BRACES); yyextra->setCurrentToken(new SmartTpl::Internal::Token(yytext, yyleng)); return TOKEN_IDENTIFIER; }
}

    /**
     *  This set of rules is for matching literal strings that are between double quotes
     */

<STRING_DOUBLE_QUOTES>{
    [^\\\"]+                    { yyextra->token()->append(yytext, yyleng); }
    "\\\""                      { yyextra->token()->push_back('\"'); }
    "\\"                        { yyextra->token()->push_back('\\'); }
    "\""                        { BEGIN(INSIDE_CURLY_BRACES); return TOKEN_STRING; }
}

    /**
     *  This set of rules is for matching literal strings that are between single quotes
     */

<STRING_SINGLE_QUOTES>{
    [^\\\']+                    { yyextra->token()->append(yytext, yyleng); }
    "\\\'"                      { yyextra->token()->push_back('\''); }
    "\\"                        { yyextra->token()->push_back('\\'); }
    "\'"                        { BEGIN(INSIDE_CURLY_BRACES); return TOKEN_STRING; }
}

    /**
     *  This set of rules is to make the {literal} block work correctly
     */

<LITERAL>{
    "\n"                        { yyextra->increaseLine(); yyextra->token()->push_back('\n'); }
    [^{\n]+                     { yyextra->token()->append(yytext, yyleng); }
    "{"                         { yyextra->token()->push_back('{'); }
    "{/literal}"                { BEGIN(INITIAL); return TOKEN_RAW; }
}

%%

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal { namespace v2 {

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
    // in case the size is 0 we will just accept it, running it through the actual parser
    // and all wastes time and will not even accept it!
    if (size == 0) return true;

    // read our data into a buffer that flex wants
    auto *state = yy_scan_bytes(buffer, size, _scanner);

    // ID of the current token
    int id;

    // keep fetching tokens
    while ((id = yylex(_scanner)) != 0)
    {
        // If the token id is -1 we know we got ourself an unknown token, so we error out
        if (id == -1)
        {
            // Set the error state to "Unknown token"
            parent->error("Unknown token");

            // clean up the buffer
            yy_delete_buffer(state, _scanner);

            // And error out
            return false;
        }
        // pass token to the parser
        else if (parent->process(id, _token) == false)
        {
            // Delete our current token, if there is one
            if (_token) delete _token;

            // clean up the buffer
            yy_delete_buffer(state, _scanner);

            // And error out
            return false;
        }

        // reset current token for next iteration
        _token = nullptr;
    }

    // clean up the buffer
    yy_delete_buffer(state, _scanner);

    // pass the end-of-file to the parser and return the result
    return parent->process(0, nullptr);
}

/**
 *  End namespace
 */
}}}
