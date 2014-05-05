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
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class ForEachStatement : public Statement
{
private:
    /**
     *  The variable to loop over
     *  @var Variable
     */
    std::unique_ptr<Variable> _source;

    /**
     *  The variable that will contain the key during the loop
     *  @note This is not a requirement
     *  @var Token
     */
    std::unique_ptr<Token> _key;

    /**
     *  The variable name that will contain the value during the loop
     *  @var Token
     */
    std::unique_ptr<Token> _value;

    /**
     *  The statements to execute within the loop
     *  @var Statements
     */
    std::unique_ptr<Statements> _statements;

public:
    /**
     *  Constructor
     *  @param  target      The variable to loop through
     *  @param  value       Name of the value variable
     *  @param  statements  The statements to execute in the foreach loop
     */
    ForEachStatement(Variable *source, Token *value, Statements *statements) : 
        _source(source), _value(value), _statements(statements) {}

    /**
     *  Constructor
     *  @param  target      The variable to loop through
     *  @param  key         Name of the key variable
     *  @param  value       Name of the value variable
     *  @param  statements  The statements to execute in the foreach loop
     */
    ForEachStatement(Variable *source, Token *key, Token *value, Statements *statements) : 
        _source(source), _key(key), _value(value), _statements(statements) {}

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
        // call the generator
        generator->foreach(_source.get(), _key ? *_key.get() : std::string(""), *_value.get(), _statements.get());
    }
};

/**
 *  End of namespace
 */
}}