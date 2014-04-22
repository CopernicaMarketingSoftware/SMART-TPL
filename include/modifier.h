/**
 *  Modifier.h
 *
 *  Interface that describes a variable modifier.
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
     *  Modify the input value
     *  @param input The input value
     *  @return You should return a newly allocated Value
     */
    virtual Value* modify(Value* input) = 0;
};
    
/**
 *  End namespace
 */
}

