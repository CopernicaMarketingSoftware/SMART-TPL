/**
 *  IfStatement.h
 *
 *  Class that represents an if-statement
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
class IfStatement : public Statement
{
private:
    /**
     *  The condition
     *  @var    Expression
     */
    std::unique_ptr<Expression> _expression;
    
    /**
     *  The statements in the 'if' part
     *  @var    Statements
     */
    std::unique_ptr<Statements> _trueStatements;
    
    /**
     *  The statements in the 'else' part
     *  @var    Statement
     */
    std::unique_ptr<Statements> _falseStatements;
    
public:
    /**
     *  Constructor
     *  @param  expression
     *  @param  statements
     */
    IfStatement(Expression *expression, Statements *statements) :
        _expression(expression), _trueStatements(statements) {}
    
    /**
     *  Constructor
     *  @param  expression
     *  @param  trueStatements
     *  @param  falseStatements
     */
    IfStatement(Expression *expression, Statements *trueStatements, Statements *falseStatements) :
        _expression(expression), _trueStatements(trueStatements), _falseStatements(falseStatements) {}
        
    /**
     *  Destructor
     */
    virtual ~IfStatement() {}
    
    /**
     *  Generate the output of this statement
     *  @param  str     output stream
     */
    virtual void generate(std::ostream &str) const override
    {
        // this is going to be a regular C "if" statement
        str << "if (";
        
        // and now we generate the code that turns the expression into a boolean
        // (and because in C there are no boolean, we use a numeric value)
        _expression->generateNumeric(str);
        
        // close the if condition and open a curly brace to start a new code block
        str << "){" << std::endl;
        
        // now we generate all statements
        _trueStatements->generate(str);
        
        // do we have an else block?
        if (_falseStatements)
        {
            // close the if block and open the else block
            str << "}else{" << std::endl;
            
            // generate the else statements
            _falseStatements->generate(str);
        }
        
        // and of the block
        str << "}" << std::endl;
    }
};

/**
 *  End namespace
 */
}

