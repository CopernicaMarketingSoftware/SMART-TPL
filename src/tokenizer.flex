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
%option extra-type="SmartTpl::Tokenizer *"

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
[\n]                { yyextra->increaseLine(); yyextra->setCurrentToken(new SmartTpl::Token("\n", 1)); return TOKEN_RAW; }
[^{\n]+             { yyextra->setCurrentToken(new SmartTpl::Token(yytext, yyleng)); return TOKEN_RAW; }
"{ldelim}"          { yyextra->setCurrentToken(new SmartTpl::Token("{", 1)); return TOKEN_RAW; }
"{rdelim}"          { yyextra->setCurrentToken(new SmartTpl::Token("}", 1)); return TOKEN_RAW; }
"{if"[ \t]+         { BEGIN(EXPRESSION); return TOKEN_IF; }
"{elseif"[ \t]+     { BEGIN(EXPRESSION); return TOKEN_ELSEIF; }
"{else}"            { return TOKEN_ELSE; }
"{foreach"[ \t]+    { BEGIN(EXPRESSION); return TOKEN_FOREACH; }
"{/foreach}"        { return TOKEN_ENDFOREACH; }
"{$"                { BEGIN(EXPRESSION); yyless(1); return TOKEN_EXPRESSION; }
"{/if}"             { return TOKEN_ENDIF; }
"{"                 { yyextra->setCurrentToken(new SmartTpl::Token(yytext, yyleng)); return TOKEN_RAW; }

    /**
     *  When in expression mode, we are tokenizing an expression inside an {if}
     *  statement or {$variable} or something similar
     */

<EXPRESSION>{
    [ \t]
    "$"[a-zA-Z][a-zA-Z0-9]*     { yyextra->setCurrentToken(new SmartTpl::Token(yytext+1, yyleng-1)); return TOKEN_VARIABLE; }
    "true"                      { return TOKEN_TRUE; }
    "false"                     { return TOKEN_FALSE; }
    "and"                       { return TOKEN_AND; }
    "or"                        { return TOKEN_OR; }
    "in"                        { return TOKEN_IN; }
    [0-9]+                      { yyextra->setCurrentToken(new SmartTpl::Token(yytext, yyleng)); return TOKEN_INTEGER; }
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
    [a-zA-Z][a-zA-Z0-9_]*       { BEGIN(EXPRESSION); yyextra->setCurrentToken(new SmartTpl::Token(yytext, yyleng)); return TOKEN_IDENTIFIER; }
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
    // initialize the scanner, and set the tokenizer as the user defined data
    yylex_init_extra(this, &_scanner);
    line = 1; // We start at line 1, not 0
    token = nullptr;
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
 *  @param  buffer
 *  @param  size
 *  @return bool
 *  @throws std::runtime_error In case something during the parsing went wrong
 *  @todo Get rid of this return value? Was originally for error handling, but
 *        this is kind of pointless now as we just throw an exception instead.
 */
bool Tokenizer::process(TokenProcessor *parent, const char *buffer, size_t size)
{
    auto *state = yy_scan_bytes(buffer, size, _scanner);
    try {
        // ID of the current token
        int id;

        // keep fetching tokens
        while ((id = yylex(_scanner)) != 0)
        {
            // pass token to the parser
            parent->process(id, token);

            // reset current token for next iteration
            token = nullptr;
        }

        // pass the end-of-file to the parser
        parent->process(0, nullptr);
    } catch (const std::runtime_error& error) {
        // clear our buffer
        yy_delete_buffer(state, _scanner);

        // add the line number to the original error and rethrow it
        std::stringstream stream;
        stream << error.what() << " at line " << line;
        throw std::runtime_error(stream.str());
    }
    yy_delete_buffer(state, _scanner);

    return true;
}

/**
 *  End namespace
 */
}

