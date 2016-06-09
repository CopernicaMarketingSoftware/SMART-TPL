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
     *  A simple custom exception class which indicates that you do not intend
     *  to actually modify the input.
     */
    class NoModification : public std::exception {};

    /**
     *  Modify a variable value, and convert it into a different value
     *
     *  This method is called if the initial value object may not be modified!
     *
     *  @param  input        Initial value
     *  @param  params       Parameters used for this modification
     *  @return VariantValue A new value object
     *  @note   In case you end up NOT modifying the input, please throw a NoModification
     *          exception.
     */
    virtual VariantValue modify(const Value &input, const Parameters &params) = 0;
};

/**
 *  End namespace
 */
}

