/**
 *  AnonymousVariable.h
 * 
 *  Class that holds a variable that does not have a name but rather is based
 *  on a literal, so that literals can be treated as variables (e.g. for usage
 *  with modifiers)
 * 
 *  @author     David van Erkelens <david.vanerkelens@copernica.com>
 *  @copyright  2019 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class AnonymousVariable : public Variable
{
private:
    /**
     *  The type of this anonymous variable
     *  @var Type
     */
    Type _type = Type::Value;

protected:
    /**
     *  Protected constructor, since this class should only be constructed by
     *  its (typed) children
     */
    AnonymousVariable(Type type): _type(type) {}

public:

    /**
     *  Destructor
     */
    virtual ~AnonymousVariable() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const override { return _type; }
};

/**
 *  End of namespace
 */
}}