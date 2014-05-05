/**
 *  LiteralArrayAccess.h
 *
 *  Class that is used to represent the [] operator to get access to an array
 *  member, when used with a literal string (not an expression)
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
class LiteralArrayAccess : public ArrayAccess
{
protected:
    /**
     *  The key that is accessed
     *  @var    std::unique_ptr
     */
    std::unique_ptr<Token> _key;

public:
    /**
     *  Constructor
     *  @param  variable
     *  @param  key
     */
    LiteralArrayAccess(Variable *variable, Token *token) : 
        ArrayAccess(variable),
        _key(token) {}

    /**
     *  Destructor
     */
    virtual ~LiteralArrayAccess() {}

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
        // generate the code to access a member
        generator->varPointer(_var.get(), *_key);
    }
};

/**
 *  End namespace
 */
}}