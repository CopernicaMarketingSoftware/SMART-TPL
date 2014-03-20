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

    /**
     *  Generate the code to get the const char * to the expression
     *  @param  str
     */
    virtual void generateString(std::ostream &str) const override
    {
        // put the value between quotes
        str << "\"" << _value << "\"";
    }
    
    /**
     *  Generate the code to get the numeric value of the expression
     *  @param  str
     */
    virtual void generateNumeric(std::ostream &str) const override
    {
        // just output the value
        str << _value;
    }
};

/**
 *  End namespace
 */
}

