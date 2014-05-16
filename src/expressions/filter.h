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
        // Loop through all the modifiers
        for (auto iter = _modifiers->begin(); iter != _modifiers->end(); ++iter)
        {
            // If one of them is named "raw" we know that we should not escape our output
            if (iter->get()->token() == "raw") return false;
        }

        // We didn't find the "raw" modifier, so we know we should escape
        return true;
    }
};

/**
 *  End namespace
 */
}}