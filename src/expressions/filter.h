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
class Filter : public Expression
{
private:
    /**
     *  The base expression
     *  @var    Expression
     */
    std::unique_ptr<const Expression> _expression;

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
    Filter(const Expression *expression, const Modifiers *modifiers) :
        _expression(expression), _modifiers(modifiers) {}

    /**
     *  Destructor
     */
    virtual ~Filter() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const { return Type::Value; };

    /**
     *  Generate the expression as string value
     *  @param  generator
     */
    virtual void string(Generator *generator) const override
    {
        _modifiers.get()->generate(generator, _expression.get());
    }

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
            return mod.get()->token() == "raw";
        });

        // Return whether we found the "raw" modifier or not
        return iter == _modifiers->end();
    }
};

/**
 *  End namespace
 */
}}