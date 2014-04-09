/**
 *  Empty.h
 *
 *  Class that represents an empty variable
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
class EmptyValue : public Value
{
public:
    /**
     *  Convert the variable to a string
     *  @return const char *
     */
    virtual const char *toString() override
    {
        return "";
    }
    
    /**
     *  Convert the variable to a numeric value
     *  @return int
     */
    virtual int toNumeric() override
    {
        return 0;
    }
    
    /**
     *  Get access to a member variable
     * 
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Value
     */
    virtual Value *member(const char *name, int size) override
    {
        return this;
    }
    
    /**
     *  String length of the variable
     * 
     *  @return int
     */
    virtual int size() override
    {
        return 0;
    }
};

/**
 *  End namespace
 */
}
