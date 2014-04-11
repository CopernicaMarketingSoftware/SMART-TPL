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
    std::list<std::unique_ptr<const Modifier>> _modifiers;

public:
    /**
     *  Constructor
     *  @param  modifier
     */
    Modifiers(const Modifier *modifier)
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
    void add(const Modifier *modifier)
    {
        _modifiers.push_back(std::unique_ptr<const Modifier>(modifier));
    }
};

/**
 *  End namespace
 */
}

