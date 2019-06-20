/**
 *  LiteralVariable.h
 *
 *  Expression that contains one variable.
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
class LiteralVariable : public Variable
{
private:
    /**
     *  Name of the variable
     *  @var    std::unique_ptr
     */
    std::unique_ptr<Token> _name;

    /**
     *  The type of the variable
     *  @var    Expression::Type
     */
    Type _type = Type::Value;

public:
    /**
     *  Constructor
     *  @param  token
     */
    LiteralVariable(Token *token, TypeHandler &handler) :
        _name(token),
        _type(handler.get(*_name)) {}

    /**
     *  Destructor
     */
    virtual ~LiteralVariable() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    Type type() const override { return _type; }

    /**
     *  Generate the output that leaves a pointer to the variable
     *  @param  generator
     */
    void pointer(Generator *generator) const override
    {
        // generate the code to get a variable pointer
        generator->varPointer(*_name);
    }

};

/**
 *  End of namespace
 */
}}