/**
 *  List.h
 *
 *  Class that represents a list with values
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
class ListValue : public Value
{
public:
    /**
     *  const_iterator typedef
     */
    typedef std::vector<Variant>::const_iterator const_iterator;
private:
    /**
     *  The actual list with values
     *  @var std::vector
     */
    std::vector<Variant> _list;

public:
    /**
     *  Constructor
     */
    ListValue() {}

    /**
     *  Destructor
     */
    virtual ~ListValue() {}

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
        // We don't support getting members using keys
        return nullptr;
    }

    /**
     *  Add data
     *  @param  number       Value of the variable
     *  @return ListValue    Same object for chaining
     */
    ListValue& add(numeric_t number)
    {
        // Push it into the list
        _list.push_back(number);

        // allow chaining
        return *this;
    }

    /**
     *  Add data
     *  @param  str          Value of the variable
     *  @return ListValue    Same object for chaining
     */
    ListValue& add(const std::string &str)
    {
        // Push it into the list
        _list.push_back(str);

        // allow chaining
        return *this;
    }

    /**
     *  Get access to the amount of members this value has
     */
    virtual size_t memberCount() const override
    {
        return _list.size();
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return Variant
     */
    virtual Variant member(size_t position) const override
    {
        // If we're out of bounds just return Variant()
        if (position >= memberCount()) return nullptr;

        // Just return it using the [] operator
        return _list[position];
    }

    /**
     *  Get access to the key at a certain position
     *  @param  position     Position of the key we want to retrieve
     *  @return Variant      Variant object, probably a string
     */
    virtual Variant key(size_t position) const override
    {
        return position;
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
    const_iterator begin() const { return _list.begin(); }
    const_iterator end() const { return _list.end(); }
};

/**
 *  End namespace
 */
}

