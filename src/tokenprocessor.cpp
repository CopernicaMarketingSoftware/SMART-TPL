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
void *SmartTplParseAlloc(void *(*mallocProc)(size_t));
void  SmartTplParseFree(void *p, void (*freeProc)(void*));
void  SmartTplParse(void *yyp, int yymajor, SmartTpl::Internal::Token *token, SmartTpl::Internal::TokenProcessor *processor);

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Constructor
 */
TokenProcessor::TokenProcessor()
: _encoding(new Token("raw", 3)) {
    // allocate the the parser
    _resource = SmartTplParseAlloc(malloc);
}

/**
 *  Destructor
 */
TokenProcessor::~TokenProcessor()
{
    SmartTplParseFree(_resource, free);
}

/**
 *  Called by the tokenizer when a token is detected
 *  @param  id      Token identifier (see lemon.h)
 *  @param  token   Additional token information
 *  @return false if an error occured
 */
bool TokenProcessor::process(int id, Token *token)
{
    // call the global Parse() function
    SmartTplParse(_resource, id, token, this);

    // check if there is something in _error by moving to the end and looking up that position
    if (_error.seekg(0, _error.end).tellg() > 0)
    {
        // If there is something in _error move back to the begin and return false
        _error.seekg(0, _error.beg);
        return false;
    }
    return true;
}

/**
 *  End namespace
 */
}}