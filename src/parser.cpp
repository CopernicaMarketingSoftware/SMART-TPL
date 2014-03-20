/**
 *  Parser.cpp
 *
 *  Implementation file for the Parser class.
 * 
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include "includes.h"

/**
 *  The following functions are implemented in the Lemon.cpp file, but that
 *  file does not come with a header file, we redefine them here
 */
extern void *ParseAlloc(void *(*mallocProc)(size_t));
extern void  ParseFree(void *p, void (*freeProc)(void*));
extern void  Parse(void *yyp, int yymajor, SmartTpl::Token *token, SmartTpl::Parser *parser);

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Constructor
 */
Parser::Parser()
{
    // allocate the the parser
    _resource = ParseAlloc(malloc);
}

/**
 *  Destructor
 */
Parser::~Parser()
{
    // clean resources
    ParseFree(_resource, free);
}

/**
 *  Called by the tokenizer when a token is detected
 *  @param  id      Token identifier (see lemon.h)
 *  @param  token   Additional token information
 */
void Parser::process(int id, Token *token)
{
    // call the global Parse() function
    Parse(_resource, id, token, this);
}

/**
 *  End namespace
 */
}

