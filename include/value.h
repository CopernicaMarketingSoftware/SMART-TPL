/**
 *  Value.h
 *
 *  Interface that describes a value. This class can be extended to create
 *  your own custom template variables.
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
class Value
{
public:
    /**
     *  Convert the value to a string
     *  @return const char *
     */
    virtual const char *toString() = 0;
    
    /**
     *  Convert the variable to a numeric value
     *  @return int
     */
    virtual int toNumeric() = 0;
    
    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() = 0;
    
    /**
     *  Get access to a member value
     * 
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Value
     */
    virtual Value *member(const char *name, size_t size) = 0;

    /**
     *  Get access to the amount of members this value has
     */
    virtual size_t memberCount() = 0;
    
    /**
     *  String length of the variable
     * 
     *  @return size_t
     */
    virtual size_t size() = 0;
};
    
/**
 *  End namespace
 */
}

