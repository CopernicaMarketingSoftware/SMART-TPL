/**
 *  Map.h
 *
 *  Class that represents a map with values
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class MapValue : public Value
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
     *  All custom values, indexed by name
     *  @var    std::map
     */
    std::map<const char *,Value*, cmp_str> _custom_values;

    /**
     *  All other values, indexed by name
     *  @var std::map
     */
    std::map<const char *,std::unique_ptr<Value>, cmp_str> _values;

public:
    /**
     *  Constructor
     */
    MapValue() {}

    /**
     *  Destructor
     */
    virtual ~MapValue() {}

    /**
     *  Convert the variable to a string
     *  @return const char *
     */
    virtual const char *toString() override
    {
        return "";
    }

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual numeric_t toNumeric() override
    {
        return 0;
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() override
    {
        return false;
    }

    /**
     *  Get access to a member variable
     *
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Value
     */
    virtual Value *member(const char *name, size_t size) override
    {
        // first look through the 'custom' values
        auto c_iter = _custom_values.find(name);
        if (c_iter != _custom_values.end())
            return c_iter->second;

        // if we didn't find it yet let's look in _values
        auto iter = _values.find(name);
        if (iter == _values.end()) return nullptr;

        // get the pointer
        return iter->second.get();
    }

    /**
     *  Assign data
     *  @param  name        Name of the variable
     *  @param  value       Value of the variable
     *  @return MapValue    Same object for chaining
     */
    MapValue& assign(const char *name, numeric_t value)
    {
        // append variable
        _values[name] = std::unique_ptr<Value>(new NumericValue(value));

        // allow chaining
        return *this;
    }

    /**
     *  Assign data
     *  @param  name        Name of the variable
     *  @param  value       Value of the variable
     *  @return MapValue    Same object for chaining
     */
    MapValue& assign(const char *name, const std::string &value)
    {
        // append variable
        _values[name] = std::unique_ptr<Value>(new StringValue(value));

        // allow chaining
        return *this;
    }

    /**
     *  Assign a new value in this map
     *
     *  @param  name        name of the value
     *  @param  value       the actual value
     *  @return MapValue    Same object for chaining
     */
    MapValue& assign(const char* name, Value* value) {
        //Add to our values
        _custom_values[name] = value;

        // Allow chaining
        return *this;
    };

    /**
     *  Get access to the amount of members this value has
     */
    virtual size_t memberCount() override
    {
        return _values.size();
    }

    /**
     *  String length of the variable
     *
     *  @return size_t
     */
    virtual size_t size() override
    {
        return 0;
    }
};

/**
 *  End namespace
 */
}

