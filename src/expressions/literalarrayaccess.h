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
     *  Generate a call that creates a pointer to a variable
     *  @param  str
     */
    virtual void generateVariable(std::ostream &str) const override
    {
        // call the member function
        str << "callbacks->member(";
        
        // generate a pointer to the underlying variable
        _var->generateVariable(str);
        
        // end of the member method
        str << ",\"" << *_key << "\")";
    }
};

/**
 *  End namespace
 */
}

