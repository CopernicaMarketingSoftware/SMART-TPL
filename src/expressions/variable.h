/**
 *  Variable.h
 *
 *  Expression that contains one variable.
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
class Variable : public Expression
{
protected:
    /**
     *  Constructor
     */
    Variable() {}

public:    
    /**
     *  Destructor
     */
    virtual ~Variable() {}
    
    /**
     *  Generate the output that leaves a pointer to the variable
     *  @param  str
     */
    virtual void generateVariable(std::ostream &str) const = 0;
    
    /**
     *  Generate the code to get the const char * to the expression
     *  @param  str
     */
    virtual void generateString(std::ostream &str) const override
    {
        // call the to_string method
        str << "callbacks->to_string(";

        // first generate a pointer to the variable
        generateVariable(str);
        
        // and then call the function to cast to a string
        str << ")";
    }
    
    /**
     *  Generate the code to get the numeric value of the expression
     *  @param  str
     */
    virtual void generateNumeric(std::ostream &str) const override
    {
        // call the to_numeric method
        str << "callbacks->to_numeric(";
        
        // generate a pointer to the variable
        generateVariable(str);
        
        // and the call
        str << ")";
    }
};

/**
 *  End of namespace
 */
}

