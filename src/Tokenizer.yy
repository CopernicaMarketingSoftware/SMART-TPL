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
#include "Token.h"
#include "Tokenizer.h"
#include "Parser.h"
#include "Lemon.h"

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
 *  Output to Tokenizer.cpp please
 */
%option outfile="src/Tokenizer.cpp"

/**
 *  Exclusive parser mode "EXPRESSION". This is exclusive, because other
 *  tokens are disabled when in expression mode.
 */
%x EXPRESSION

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

[^f{\n]+        { yyextra->value = yytext; yyextra->size = yyleng; return TOKEN_RAW; }
\n+             { yyextra->value = yytext; yyextra->size = yyleng; return TOKEN_RAW; }
"{if"           { BEGIN(EXPRESSION); return TOKEN_IF; }
"{elseif"       { BEGIN(EXPRESSION); return TOKEN_ELSEIF; }
"{else}"        { return TOKEN_ELSE; }
"{$"            { BEGIN(EXPRESSION); yyless(1); return TOKEN_EXPRESSION; }
"{/if}"         { return TOKEN_ENDIF; }

    /**
     *  When in expression mode, we are tokenizing an expression inside an {if}
     *  statement or {$variable} or something similar
     */

<EXPRESSION>{
    "$"[a-zA-Z][a-zA-Z0-9]*     { yyextra->value = yytext+1; yyextra->size = yyleng-1; return TOKEN_VARIABLE; }
    "}"                         { BEGIN(INITIAL); }
}

%%

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Run the tokenizer on an input buffer
 *  @param  buffer
 *  @param  size
 *  @return bool
 */
bool Tokenizer::process(const char *buffer, size_t size)
{
    // object holding current tokenizer state
    yyscan_t scanner;
    
    // initialize scanner
    yylex_init(&scanner);

    // store current token
    Token token;
    
    // the token should be accessible as global data
    yylex_init_extra(&token, &scanner);

    // ID of the current token
    int id;
    
    // keep fetching tokens
    while ((id = yylex(scanner)) != 0)
    {
        // pass token to the parser
        _parser->process(id, token);
        
        // reset current token for next iteration
        token.reset();
    }
    
    // destruct scannerl
    yylex_destroy(scanner);
    
    // done
    return true;
}

/**
 *  End namespace
 */
}

