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
namespace SmartTpl {

/**
 *  Class definition
 */
class LiteralArrayAccess : public ArrayAccess
{
protected:
    /**
     *  The key that is accessed
     *  @var    Expression
     */
    std::string _key;

public:
    /**
     *  Constructor
     *  @param  variable
     *  @param  key
     */
    LiteralArrayAccess(Variable *variable, const Token *token) : 
        ArrayAccess(variable),
        _key(token->value, token->size) {}

    /**
     *  Destructor
     */
    virtual ~LiteralArrayAccess() {}
};

/**
 *  End namespace
 */
}

