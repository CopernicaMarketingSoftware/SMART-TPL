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
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 *  @todo Actually start using this class?
 */
class Parameters
{
public:
    /**
     *  const_iterator typedef
     */
    typedef std::list<std::unique_ptr<const Expression>>::const_iterator const_iterator;
    typedef std::list<std::unique_ptr<const Expression>>::const_reverse_iterator const_reverse_iterator;
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

    /**
     *  Generate the output to construct these parameters on runtime
     *  @param  generator
     */
    void generate(Generator *generator) const
    {
        generator->parameters(this);
    }

    /**
     *  Get the begin and end iterator
     */
    const_iterator begin() const { return _parameters.begin(); }
    const_iterator end() const { return _parameters.end(); }
    const_reverse_iterator rbegin() const { return _parameters.rbegin(); }
    const_reverse_iterator rend() const { return _parameters.rend(); }
};

/**
 *  End namespace
 */
}}