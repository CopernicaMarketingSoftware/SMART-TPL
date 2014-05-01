/**
 *  Data.h
 *
 *  When you process a template, you need to pass in a data object. This data
 *  object is filled with all the variables that can be used inside the 
 *  template.
 *
 *  In this header file this data class is defined.
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
class Data
{
private:
    /**
     *  Compare functor necessary for the map
     */
    struct cmp_str
    {
        /** 
         *  Invoke operator
         *  @param  a
         *  @param  b
         *  @return bool
         */
        bool operator()(char const *a, char const *b) const
        {
            return std::strcmp(a, b) < 0;
        }
    };

    /**
     *  All variables, indexed by name
     *  @var    std::map
     */
    std::map<const char *, Value*, cmp_str> _variables;

    /**
     *  This will contain all the variables created internally, this is purely
     *  to automatically clean them up afterwards.
     */
    std::list<std::unique_ptr<Value>> _managed_variables;

    /**
     *  All modifiers
     *  @var std::map
     */
    std::map<const char *, Modifier*, cmp_str> _modifiers;

    /**
     *  Callback methods and their cleanup methods
     *  The first function in the pair will be to create the value, the second one to clean it up
     *  @var std::map
     */
    std::map<const char *, std::function<Variant()>, cmp_str> _callbacks;

public:
    /**
     *  Constructor
     */
    Data();

    /**
     *  Destructor
     */
    virtual ~Data() {}

    /**
     *  Assign data
     *  @param  name        Name of the variable
     *  @param  value       Value of the variable
     *  @return Data        Same object for chaining
     */
    Data &assign(const char *name, const std::string &value);
    Data &assign(const char *name, numeric_t value);
    Data &assign(const char *name, Value *value);
    Data &callback(const char *name, const std::function<Variant()> &lambda);

    /**
     *  Register a modifier
     *  @param  name        Name of the modifier
     *  @param  modifier    Pointer to the modifier object
     *  @return Data        Same object for chaining
     */
    Data &modifier(const char *name, Modifier* modifier);

    /**
     *  Retrieve a variable pointer by name
     *  @param  name        the name
     *  @param  size        size of the name
     *  @return Value*      nullptr in case it isn't found
     */
    Value *value(const char *name, size_t size) const;

    /**
     *  Retrieve a modifier by name
     *  @param  name        the name of the modifier
     *  @param  size        size of the name
     *  @return Modifier*   nullptr in case it isn't found
     */
    Modifier *modifier(const char *name, size_t) const;

    /**
     *  Retrieve a value callback function
     *  @param  name         the name of the callback
     *  @param  size         the size of the name
     *  @return std::function<Variant()>
     */
    const std::function<Variant()> *callback(const char *name, size_t size) const;
};

/**
 *  End namespace
 */
}

