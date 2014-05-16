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

public:
    /**
     *  Constructor
     *  @param  token
     */
    LiteralVariable(Token *token) :
        _name(token) {}

    /**
     *  Destructor
     */
    virtual ~LiteralVariable() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const { return Type::Value; }

    /**
     *  Generate the output that leaves a pointer to the variable
     *  @param  generator
     */
    virtual void pointer(Generator *generator) const override
    {
        // generate the code to get a variable pointer
        generator->varPointer(*_name);
    }

};

/**
 *  End of namespace
 */
}}