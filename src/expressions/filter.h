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
     *  Generate the code to construct the parameters, should be called before string()
     *  @param  generator
     */
    void parameters(Generator *generator) const
    {
        for (auto &modifier : *_modifiers)
        {
            auto *parameters = modifier->parameters();
            if (parameters)
            {
                parameters->generate(generator);
            }
        }
    }
};

/**
 *  End namespace
 */
}}