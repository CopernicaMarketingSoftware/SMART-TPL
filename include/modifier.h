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
     * 
     *  This method is called if the initial value object may not be modified!
     * 
     *  @param  input       Initial value
     *  @return Value       Pointer to a new value object
     */
    virtual Value *modify(Value *input) = 0;

    /**
     *  Modify a numeric value, and convert it into a variable value
     * 
     *  @param  input       Numeric value
     *  @return Value       Pointer to a new value object
     */
    virtual Value *modify(int value) = 0;

    /**
     *  Modify a string value, and convert it into a variable object
     * 
     *  @param  input       String input
     *  @param  size        Size of the string
     *  @return Value       Pointer to a new value object
     */
    virtual Value *modify(const char *input, size_t size) = 0;

    /**
     *  Clean up the values you created
     *  @param value        The value to clean up
     */
    virtual void cleanup(Value* value) = 0;
};
    
/**
 *  End namespace
 */
}

