/**
 *  Literal.h
 *
 *  Base class for expressions that hold a literal value, for example a literal
 *  integer or literal boolean
 *
 *  @author Emiel Bruijntjes
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class Literal : public Expression
{
protected:
    /**
     *  Constructor is protected, only derived classes can be instantiated
     */
    Literal() {}
    
public:
    /**
     *  Destructor
     */
    virtual ~Literal() {}
};

/**
 *  End namespace
 */
}

