/**
 *  Boolean.h
 *
 *  Implementation of a literal boolean value
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
class LiteralBoolean : public Literal
{
private:
    /**
     *  The actual value
     *  @var    bool
     */
    bool _value;
    
public:
    /**
     *  Constructor
     *  @param  bool
     */
    LiteralBoolean(bool value) : _value(value) {}
    
    /**
     *  Destructor
     */
    virtual ~LiteralBoolean() {}


};

/**
 *  End namespace
 */
}

