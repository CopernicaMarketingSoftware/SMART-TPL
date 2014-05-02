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
     *  All values, indexed by name
     *  @var    std::map
     */
    std::map<const char *,Value*, cmp_str> _values;

    /**
     *  A list with all the interally created Values that
     *  should simply be destroyed later on
     */
    std::vector<std::unique_ptr<Value>> _destroy_later;

    /**
     *  A vector with all the Values created to return as keys
     */
    std::vector<std::unique_ptr<Value>> _key_cache;

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
        // look it up in _values return nullptr if we didn't find it
        auto iter = _values.find(name);
        if (iter == _values.end()) return nullptr;

        // get the pointer
        return iter->second;
    }

    /**
     *  Assign data
     *  @param  name        Name of the variable
     *  @param  number      Value of the variable
     *  @return MapValue    Same object for chaining
     */
    MapValue& assign(const char *name, numeric_t number)
    {
        // Create the value
        Value *value = new NumericValue(number);

        // append variable
        _values[name] = value;

        // and add it to our _destroy_later list
        _destroy_later.push_back(std::unique_ptr<Value>(value));

        // allow chaining
        return *this;
    }

    /**
     *  Assign data
     *  @param  name        Name of the variable
     *  @param  str         Value of the variable
     *  @return MapValue    Same object for chaining
     */
    MapValue& assign(const char *name, const std::string &str)
    {
        // Create the value
        Value *value = new StringValue(str);

        // append the variable
        _values[name] = value;

        // and add it to our _destroy_later list
        _destroy_later.push_back(std::unique_ptr<Value>(value));

        // allow chaining
        return *this;
    }

    /**
     *  Assign a new value in this map
     *  @param  name        name of the value
     *  @param  value       the actual value
     *  @return MapValue    Same object for chaining
     */
    MapValue& assign(const char* name, Value* value) {
        // Add to our values
        _values[name] = value;

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
     *  Get access to a member at a certain position
     *  @param position
     *  @return Value or nullptr if not present
     */
    virtual Value *member(int position) override
    {
        // If we're out of bounds just return nullptr
        if (position < 0 || position >= memberCount()) return nullptr;

        // get the iterator of _values
        auto iter = _values.begin();

        // advance it by position
        std::advance(iter, position);

        // return the Value in the iterator
        return iter->second;
    }

    /**
     *  Get access to the key at a certain position
     *  @param position
     *  @return The name of the key at position or nullptr otherwise
     */
    virtual Value *key(int position) override
    {
        // If we're out of bounds just return nullptr
        if (position < 0 || position >= memberCount()) return nullptr;

        // Resize the _key_cache to the amount of members we have
        _key_cache.resize(memberCount());

        // Check if we have it in our cache already, if we do return that one
        if (_key_cache[position]) return _key_cache[position].get();

        // get the iterator of _values
        auto iter = _values.begin();

        // advance it by position
        std::advance(iter, position);

        // Turn the key into a Value
        StringValue *value = new StringValue(iter->first, std::strlen(iter->first));

        // Add our new value to our _destroy_later set
        _key_cache[position] = std::unique_ptr<Value>(value);

        // return the value
        return value;
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

    /**
     *  Method used to get a instance of this value
     */
    virtual Variant cache() override
    {
        return Variant();
    }
};

/**
 *  End namespace
 */
}

