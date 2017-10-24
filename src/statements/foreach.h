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

    /**
     *  The statements to execute when there are no elements to loop through
     *  @var Statements
     */
    std::unique_ptr<Statements> _else_statements;

public:
    /**
     *  Constructor
     *  @param  target          The variable to loop through
     *  @param  value           Name of the value variable
     *  @param  statements      The statements to execute in the foreach loop
     *  @param  else_statements The statements to be executed if there is nothing to loop through
     */
    ForEachStatement(Variable *source, Token *value, Statements *statements, Statements *else_statements = nullptr) :
        _source(source), _value(value), _statements(statements), _else_statements(else_statements) {}

    /**
     *  Constructor
     *  @param  target          The variable to loop through
     *  @param  key             Name of the key variable
     *  @param  value           Name of the value variable
     *  @param  statements      The statements to execute in the foreach loop
     *  @param  else_statements The statements to be executed if there is nothing to loop through
     */
    ForEachStatement(Variable *source, Token *key, Token *value, Statements *statements, Statements *else_statements = nullptr) : 
        _source(source), _key(key), _value(value), _statements(statements), _else_statements(else_statements) {}

    /**
     *  Destructor
     */
    virtual ~ForEachStatement() {}

    /**
     *  Generate the output of this statement
     *  @param  generator
     */
    void generate(Generator *generator) const override
    {
        // if there is no key, we pass an empty string
        if (_key == nullptr) generator->foreach(_source.get(), std::string(""), *_value, _statements.get(), _else_statements.get());
    
        // otherwise we call the generator with a reference to the key
        else generator->foreach(_source.get(), *_key, *_value, _statements.get(), _else_statements.get());
    }
};

/**
 *  End of namespace
 */
}}
