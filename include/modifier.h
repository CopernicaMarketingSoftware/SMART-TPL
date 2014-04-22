/**
 *  VariableModifier.h
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
    virtual ~Modifier() {};
    virtual Value* modify(Value* input) = 0;
};
    
/**
 *  End namespace
 */
}

