/**
 *  VariableArrayAccess.h
 *
 *  Class that is used to represent the [] operator to get access to an array
 *  member, when used with a variable string (an expression)
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class VariableArrayAccess : public ArrayAccess
{
protected:
    /**
     *  The key that is accessed
     *  @var    Expression
     */
    std::unique_ptr<Expression> _key;

public:
    /**
     *  Constructor
     *  @param  variable
     *  @param  key
     */
    VariableArrayAccess(Variable *variable, Expression *key) :
        ArrayAccess(variable),
        _key(std::unique_ptr<Expression>(key)) {}

    /**
     *  Destructor
     */
    virtual ~VariableArrayAccess() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const { return Type::Value; }

    /**
     *  Generate a call that creates a pointer to a variable
     *  @param  generator
     */
    virtual void pointer(Generator *generator) const override
    {
        generator->varPointer(_var.get(), _key.get());
    }
};

/**
 *  End namespace
 */
}}