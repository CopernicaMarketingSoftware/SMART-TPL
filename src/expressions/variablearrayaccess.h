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
namespace SmartTpl {

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
     *  Generate a call that creates a pointer to a variable
     *  @param  str
     */
    virtual void generateVariable(std::ostream &str) const override
    {
        // call the member function
        str << "callbacks->member(";
        
        // generate a pointer to the underlying variable
        _var->generateVariable(str);

        // split parameters
        str << ",";

        // generate the code to convert a expression into a "const char *"
        _key->generateString(str);
        
        // end of the member method
        str << ")";
    }

};

/**
 *  End namespace
 */
}

