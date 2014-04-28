/**
 *  ForEach.h
 *
 *  Statement to simply loop through all the members of a multi member variable
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class ForEachStatement : public Statement
{
private:
    /**
     *  The variable that will contain the value during the loop
     */
    std::unique_ptr<LiteralVariable> _var;

    /**
     *  The variable that will contain the key during the loop
     *  @note This is not a requirement
     */
    std::unique_ptr<LiteralVariable> _keyvar;

    /**
     *  The variable to loop over
     */
    std::unique_ptr<Variable> _target;

    /**
     *  The statements to execute within the loop
     */
    std::unique_ptr<Statements> _statements;

public:
    /**
     *  Constructor
     *  @param key           The {foreach ... in ${variable}} part of the foreach
     *                       we demand that this is a LiteralVariable, otherwise we'll throw
     *  @param target        The variable to loop through, this does NOT have to be a LiteralVariable
     *  @param statements    The statements to execute in the foreach loop
     *  @throws std::runtime_error In case the key is not of type LiteralVariable
     */
    ForEachStatement(Variable *var, Variable *target, Statements *statements)
    : _target(target)
    , _statements(statements) {
        LiteralVariable *k = dynamic_cast<LiteralVariable*>(var);
        if (k == nullptr)
            throw std::runtime_error("The key in the foreach loop is of the wrong type");
        _var = std::unique_ptr<LiteralVariable>(k);
    }

    ForEachStatement(Variable *var, Variable *target, Variable *keyvar, Statements *statements)
    : ForEachStatement(var, target, statements) {
        LiteralVariable *k = dynamic_cast<LiteralVariable*>(keyvar);
        if (k == nullptr)
            throw std::runtime_error("The variable for the key in the foreach loop is of the wrong type");
        _keyvar = std::unique_ptr<LiteralVariable>(k);
    }

    /**
     *  Destructor
     */
    virtual ~ForEachStatement() {}

    /**
     *  Generate the output of this statement
     *  @param  generator
     */
    virtual void generate(Generator *generator) const override
    {
        generator->foreach(_var->token(), _target.get(), _statements.get(), (_keyvar) ? _keyvar->token() : "");
    }
};

/**
 *  End of namespace
 */
}

