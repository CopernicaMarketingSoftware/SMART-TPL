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
     *  The raw data to be echo'ed
     *  @var    std::unique_ptr
     */
    std::unique_ptr<Variable> _key;

    std::unique_ptr<Variable> _target;

    std::unique_ptr<Statements> _statements;

public:
    /**
     *  Constructor
     *  @param key           The {foreach ... in ${variable}} part of the foreach
     *                       should probably always be a LiteralVariable, maybe just throw otherwise?
     *  @param target        The variable to loop through, this does NOT have to be a LiteralVariable
     *  @param statements    The statements to execute in the foreach loop
     */
    ForEachStatement(Variable *key, Variable *target, Statements *statements)
    : _key(key)
    , _target(target)
    , _statements(statements) {
        LiteralVariable *k = dynamic_cast<LiteralVariable*>(key);
        if (k == nullptr)
            throw std::runtime_error("The key in the foreach loop is of the wrong type");
        std::cout << ((LiteralVariable*) key)->token() << std::endl;
        LiteralVariable* t = dynamic_cast<LiteralVariable*>(target);
        if (t)
            std::cout << t->token() << std::endl;
        else
            std::cout << "Target is not of type LiteralVariable." << std::endl;
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
        // add write instruction of raw data
    }
};

/**
 *  End of namespace
 */
}

