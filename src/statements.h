/**
 *  Statements.h
 *
 *  Class representing a list of statements
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
class Statements
{
private:
    /**
     *  List of statements
     *  @var std::list
     */
    std::list<std::unique_ptr<Statement>> _statements;
    
public:
    /**
     *  Constructor
     */
    Statements();
    
    /**
     *  Constructor with already the first statement
     *  @param  statement
     */
    Statements(Statement *statement)
    {
        // add first statement
        add(statement);
    }
    
    /**
     *  Function to add a statement to the list
     *  @param  statement
     */
    void add(Statement *statement)
    {
        // add first statement
        _statements.push_back(std::unique_ptr<Statement>(statement));
    }
};

/**
 *  End of namespace
 */
}

