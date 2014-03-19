/**
 *  LiteralInteger.h
 *
 *  Implementation of a literal integer value
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class LiteralInteger : public Literal
{
private:
    /**
     *  The actual value
     *  @var    int
     */
    int _value;
    
public:
    /**
     *  Constructor
     *  @param  bool
     * 
     *  @todo run atoi()
     */
    LiteralInteger(const Token *token) : _value(1234) {}
    
    /**
     *  Destructor
     */
    virtual ~LiteralInteger() {}
};

/**
 *  End namespace
 */
}

