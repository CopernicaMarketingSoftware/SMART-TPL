/**
 *  Modifiers.h
 *
 *  List of modifiers that make up a filter
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2018 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class Modifiers
{
public:
    /**
     *  const_iterator typedef
     */
    typedef std::list<std::unique_ptr<const ModifierExpression>>::const_iterator const_iterator;
    typedef std::list<std::unique_ptr<const ModifierExpression>>::const_reverse_iterator const_reverse_iterator;
private:
    /**
     *  List of modifiers
     *  @var    std::list
     */
    std::list<std::unique_ptr<const ModifierExpression>> _modifiers;

public:
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
        _modifiers.emplace_back(modifier);
    }

    /**
     *  Generate the output of these modifiers
     *  @param  generator
     *  @param  variable
     *  @note   pointer to a variable is added to the stack
     */
    void generate(Generator *generator, const Variable *variable) const
    {
        generator->modifiers(this, variable);
    }

    /**
     *  Generate the code for modifiers but turning it into a string
     *  @param  generator
     *  @param  variable
     */
    void generateString(Generator *generator, const Variable *variable) const
    {
        generator->modifiersString(this, variable);
    }

    /**
     *  Generate the code for modifiers but turning it into a boolean, this
     *  is mostly used for if statements
     *  @param  generator
     *  @param  variable
     */
    void generateBoolean(Generator *generator, const Variable *variable) const
    {
        generator->modifiersBoolean(this, variable);
    }

    /**
     *  Generate the code for modifiers but turning it into a double, this is mostly
     *  used for if statements
     *  @param  generator
     *  @param  variable
     */
    void generateDouble(Generator *generator, const Variable *variable) const
    {
        generator->modifiersDouble(this, variable);
    }

    /**
     *  Get the begin and end iterator
     */
    const_iterator begin() const { return _modifiers.begin(); }
    const_iterator end() const { return _modifiers.end(); }
    const_reverse_iterator rbegin() const { return _modifiers.rbegin(); }
    const_reverse_iterator rend() const { return _modifiers.rend(); }

    /**
     *  A simple size() method
     */
    std::size_t size() const { return _modifiers.size(); }
};

/**
 *  End namespace
 */
}}
