/**
 *  CCode.h
 *
 *  Class that turns a template syntax tree into C code that can be compiled
 *  into a shared library.
 *
 *  This class overrides from the Generator base class, because it is one
 *  of the generators of the SmartTpl library (the template-to-c-code generator)
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class CCode : public Generator
{
private:
    /**
     *  Output stream
     *  @var    std::ostream
     */
    std::ostringstream _out;
    
public:
    /**
     *  Constructor
     *  @param  tree        The abstract syntax tree of the template
     */
    CCode(const SyntaxTree &tree);
    
    /**
     *  Destructor
     */
    virtual ~CCode() {}

    /**
     *  Output raw data
     *  @param  data        buffer to output
     */
    virtual void raw(const std::string &data) override;
        
    /**
     *  Generate the code to output a variable
     *  @param  variable    the variable to output
     */
    virtual void output(const Variable *variable) override;

    /**
     *  Generate a conditional statement
     *  @param  expression          the expression to evaluate
     *  @param  ifstatements        the statements in the 'if' part
     *  @param  elsestatements      the statements in the 'else' part
     */
    virtual void condition(const Expression *expression, const Statements *ifstatements, const  Statements *elsestatements) override;

    /**
     *  Generate the code to get a pointer to a variable
     *  @param  name                name of the variable
     */
    virtual void varPointer(const std::string &name) override;

};

/**
 *  End namespace
 */
}

