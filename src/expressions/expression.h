/**
 *  Expression.h
 *
 *  Base class for all sorts of expressions
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
 */
class Expression
{
public:
    /**
     *  The supported expression types
     */
    enum class Type : std::int8_t {
        Numeric = 0,            // numeric type
        String = 1,             // string type
        Boolean = 2,            // boolean type
        Double = 3,             // a double type
        Value = 4               // variable that was modified by a modifier / type may be unknown
    };

protected:
    /**
     *  Constructor
     *
     *  The constructor is protected, because an expression is always
     *  implemented by one of its derived classes.
     */
    Expression() {}

public:
    /**
     *  Destructor
     */
    virtual ~Expression() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const = 0;

    /**
     *  Generate the expression as a numeric value
     *  @param  generator
     */
    virtual void numeric(Generator *generator) const
    {
        throw std::runtime_error("Default numeric implementation called");
    };

    /**
     *  Generate the expression as a double value
     *  @param  generator
     */
    virtual void double_type(Generator *generator) const
    {
        throw std::runtime_error("Default double_type implementation called");
    };

    /**
     *  Generate the expression as a boolean value
     *  @param  generator
     */
    virtual void boolean(Generator *generator) const
    {
        throw std::runtime_error("Default boolean implementation called");
    };

    /**
     *  Generate the expression as string value
     *  @param  generator
     */
    virtual void string(Generator *generator) const
    {
        throw std::runtime_error("Default string implementation called");
    };

    /**
     *  Generate the expression to output ourself
     *  @param  generator
     */
    virtual void output(Generator *generator) const
    {
        generator->write(this);
    }
};

/**
 *  End namespace
 */
}}