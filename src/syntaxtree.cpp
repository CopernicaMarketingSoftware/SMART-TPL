/**
 *  SyntaxTree.cpp
 *
 *  Implementation of the syntax tree
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include "includes.h"

/**
 *  Set up namespace
 */
namespace SmartTpl {
    
/**
 *  Called by the tokenizer when a token is detected
 *  @param  id      Token identifier (see lemon.h)
 *  @param  token   Additional token information
 */
void SyntaxTree::process(int id, const Token &token)
{
    // @todo add better implementation
    std::cout << "found token " << id << std::endl;
}
    
/**
 *  End namespace
 */
}

