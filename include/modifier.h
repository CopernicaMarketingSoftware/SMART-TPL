/**
 *  Modifier.h
 *
 *  Interface that describes a variable modifier. If you want to create your
 *  own modifiers, you can do so by extending from this modifier base class,
 *  and implementing the pure virtual functions.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {
    
/**
 *  Class definition
 */
class Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~Modifier() {};

    /**
     *  Modify a variable value, and convert it into a different value
     *  @param  input       Initial value
     *  @return Value       Pointer to a new value object
     */
    virtual Value* modify(Value* input) = 0;
};
    
/**
 *  End namespace
 */
}

