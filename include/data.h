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
    std::map<const char *,std::unique_ptr<Value>, cmp_str> _variables;
    
    
public:
    /**
     *  Constructor
     */
    Data() {}
    
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
    Data &assign(const char *name, int value);
    Data &assign(const char *name, Value *value);

    /**
     *  Retrieve a variable pointer by name
     *  @param  name        the name
     *  @param  size        size of the name
     *  @return Value*
     */
    Value *value(const char *name, size_t size) const;
};

/**
 *  End namespace
 */
}

