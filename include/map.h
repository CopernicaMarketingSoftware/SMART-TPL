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
public:
    /**
     *  const_iterator typedef
     */
    typedef std::map<const char *,Variant>::const_iterator const_iterator;
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
     *  All values, indexed by name
     *  @var    std::map
     */
    std::map<const char *,Variant, cmp_str> _values;

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
    virtual const char *toString() const override
    {
        return "";
    }

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual numeric_t toNumeric() const override
    {
        return 0;
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const override
    {
        return false;
    }

    /**
     *  Get access to a member variable
     *
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Variant
     */
    virtual Variant member(const char *name, size_t size) const override
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
        // append variable
        _values[name] = number;

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
        // append the variable
        _values[name] = str;

        // allow chaining
        return *this;
    }

    /**
     *  Get access to the amount of members this value has
     */
    virtual size_t memberCount() const override
    {
        return _values.size();
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return Variant
     */
    virtual Variant member(size_t position) const override
    {
        // If we're out of bounds just return nullptr
        if (position >= memberCount()) return nullptr;

        // get the iterator of _values
        auto iter = _values.begin();

        // advance it by position
        std::advance(iter, position);

        // return the Value in the iterator
        return iter->second;
    }

    /**
     *  Get access to the key at a certain position
     *  @param  position     Position of the key we want to retrieve
     *  @return Variant      Variant object, probably a string
     */
    virtual Variant key(size_t position) const override
    {
        // If we're out of bounds just return nullptr
        if (position >= memberCount()) return nullptr;

        // get the iterator of _values
        auto iter = _values.begin();

        // advance it by position
        std::advance(iter, position);

        // Return the key
        return iter->first;
    }

    /**
     *  String length of the variable
     *
     *  @return size_t
     */
    virtual size_t size() const override
    {
        return 0;
    }

    /**
     *  Create a new iterator that allows you to iterate over the subvalues
     *  feel free to return nullptr from here in case memberCount returns 0
     *  as this method won't ever get called in that case anyway.
     *
     *  @return Newly allocated Iterator
     */
    virtual Iterator *iterator() const override;

    /**
     *  Get the begin and end iterator
     */
    const_iterator begin() const { return _values.begin(); }
    const_iterator end() const { return _values.end(); }
};

/**
 *  End namespace
 */
}

