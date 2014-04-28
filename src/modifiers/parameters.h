/**
 *  Parameters.h
 *
 *  Parameters that are passed to a modifier function.
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
 *  @todo Actually start using this class?
 */
class Parameters
{
private:
    /**
     *  List of parameters
     *  @var    std::list
     */
    std::list<std::unique_ptr<const Expression>> _parameters;

public:
    /**
     *  Constructor
     *  @param  expression
     */
    Parameters(const Expression *expression) 
    {
        add(expression);
    }

    /**
     *  Destructor
     */
    virtual ~Parameters() {}

    /**
     *  Add a parameter
     *  @param  expression
     */
    void add(const Expression *expression)
    {
        _parameters.push_back(std::unique_ptr<const Expression>(expression));
    }
};

/**
 *  End namespace
 */
}

