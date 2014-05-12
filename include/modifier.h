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
     *  @param  params      Parameters used for this modification
     *  @return Variant     A new value object
     *  @todo   Attempt to make the Value a Variant here
     */
    virtual Variant modify(const Value &input, const Parameters &params) = 0;
};

/**
 *  End namespace
 */
}

