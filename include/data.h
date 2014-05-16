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
         *  @param  a      First string for the comparison
         *  @param  b      Second string for the comparison
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
    std::map<const char *, Variant, cmp_str> _variables;

    /**
     *  All modifiers
     *  @var std::map
     */
    std::map<const char *, Modifier*, cmp_str> _modifiers;

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
    Data &assign(const char *name, const Variant &value);

    /**
     *  Assign a callback
     *  The callback will only be called when a variable with the given name
     *  is used inside a template
     *  @param  name        Name of the variable
     *  @param  callback    Function to be called when the variable is accessed
     *  @param  cache       Should we cache calls to your callback?
     *  @return Data        Same object for chaining
     */
    Data &callback(const char *name, const Callback &callback, bool cache = false);

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
     *  @return Variant
     */
    Variant value(const char *name, size_t size) const;

    /**
     *  Retrieve a modifier by name
     *  @param  name        the name of the modifier
     *  @param  size        size of the name
     *  @return Modifier*   nullptr in case it isn't found
     */
    Modifier *modifier(const char *name, size_t size) const;
};

/**
 *  End namespace
 */
}

