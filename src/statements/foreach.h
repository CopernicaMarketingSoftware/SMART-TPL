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
     *  @param  token
     */
    ForEachStatement(Variable *key, Variable *target, Statements *statements)
    : _key(key)
    , _target(target)
    , _statements(statements) {}

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

