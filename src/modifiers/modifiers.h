/**
 *  Modifiers.h
 *
 *  List of modifiers that make up a filter
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class Modifiers
{
private:
    /**
     *  List of modifiers
     *  @var    std::list
     */
    std::list<std::unique_ptr<const ModifierExpression>> _modifiers;

public:
    typedef std::list<std::unique_ptr<const ModifierExpression>>::const_iterator const_iterator;

    /**
     *  Constructor
     *  @param  modifier
     */
    Modifiers(const ModifierExpression *modifier)
    {
        add(modifier);
    }
    
    /**
     *  Destructor
     */
    virtual ~Modifiers() {}
    
    /**
     *  Add a modifier to the list of modifiers
     *  @param  modifier
     */
    void add(const ModifierExpression *modifier)
    {
        _modifiers.push_back(std::unique_ptr<const ModifierExpression>(modifier));
    }

    void generate(Generator *generator, const Expression *expression) const
    {
        generator->modifiers(this, expression);
    }

    const_iterator begin() const { return _modifiers.begin(); }
    const_iterator end() const { return _modifiers.end(); }
};

/**
 *  End namespace
 */
}
