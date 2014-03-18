/**
 *  Token.h
 *
 *  Structure that holds the current token that is being processed by the 
 *  Tokenizer. Note that the Tokenizer is implemented in Tokenizer.yy
 *  
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  The current parsed token
 */
class Token
{
public:
    /**
     *  The value of the token
     *  @var    const char *
     */
    const char *value = nullptr;
    
    /**
     *  Size of the current token
     *  @var    size_t
     */
    size_t size = 0;
    
    /**
     *  Reset the object
     */
    void reset() 
    { 
        value = nullptr; 
        size = 0; 
    }
};

/**
 *  End namespace
 */
}

