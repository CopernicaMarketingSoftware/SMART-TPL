/**
 *  Filter.h
 *
 *  A filter combines an expression with a number of modifiers
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class Filter : public Variable
{
private:
    /**
     *  The base expression
     *  @var    Variable
     */
    std::unique_ptr<const Variable> _variable;

    /**
     *  The modifiers that should be applied
     *  @var    Modifiers
     */
    std::unique_ptr<const Modifiers> _modifiers;

public:
    /**
     *  Constructor
     *  @param  expression
     *  @param  modifiers
     */
    Filter(const Variable *variable, const Modifiers *modifiers) :
        _variable(variable), _modifiers(modifiers) {}

    /**
     *  Destructor
     */
    virtual ~Filter() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    Type type() const { return Type::Value; };

    /**
     *  Generate the output that leaves a pointer to the variable
     *  @param  generator
     */
    void pointer(Generator *generator) const override
    {
        _modifiers->generate(generator, _variable.get());
    }

    /**
     *  Generate the expression as string value
     *  @param  generator
     */
    void string(Generator *generator) const override
    {
        _modifiers->generate(generator, _variable.get());
    }

    /**
     *  Generate the expression as a numeric value
     *  @param  generator
     */
    void numeric(Generator *generator) const override
    {
        throw std::runtime_error("Non-default numeric implementation called");
    };

    /**
     *  Generate the expression as a double value
     *  @param  generator
     */
    void double_type(Generator *generator) const override
    {
        throw std::runtime_error("Non-default double_type implementation called");
    };

    /**
     *  Generate the expression as a boolean value
     *  @param  generator
     */
    void boolean(Generator *generator) const override
    {
        _modifiers->generateBoolean(generator, _variable.get());
    };

    /**
     *  Retrieve whether we should escape or not, this method will simply check
     *  for the "raw" modifier
     *  @return false if we shouldn't escape, true otherwise
     */
    bool escape() const
    {
        // Look for a modifier named "raw"
        auto iter = std::find_if(_modifiers->begin(), _modifiers->end()
                                ,[](const std::unique_ptr<const ModifierExpression> &mod) {
            return mod->token() == "raw";
        });

        // Return whether we found the "raw" modifier or not
        return iter == _modifiers->end();
    }

    /**
     *  Generate the expression to output ourself
     *  @param  generator
     */
    void output(Generator *generator) const override
    {
        generator->output(this);
    }
};

/**
 *  End namespace
 */
}}