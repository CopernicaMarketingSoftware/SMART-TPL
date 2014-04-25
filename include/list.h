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
    typedef std::vector<Value*>::const_iterator const_iterator;
private:
    /**
     *  The actual list with values
     *  @var std::vector
     */
    std::vector<Value*> _list;

    /**
     *  A list with values that should be destroyed later on
     *  mostly for Value objects created in place
     *  @var std::set
     */
    std::set<std::unique_ptr<Value>> _destroy_later;

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
        // Create the NumericValue
        Value *value = new NumericValue(number);

        // Push it into the list
        _list.push_back(value);

        // Push it into our destroy later list
        _destroy_later.insert(std::unique_ptr<Value>(value));

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
        // Create the StringValue
        Value *value = new StringValue(str);

        // Push it into the list
        _list.push_back(value);

        // Push it into our destroy later list
        _destroy_later.insert(std::unique_ptr<Value>(value));

        // allow chaining
        return *this;
    }

    /**
     *  Add data
     *  @param  value        The actual value
     *  @return ListValue    Same object for chaining
     */
    ListValue& add(Value* value) {
        // Just add it to the list and we're done with it
        _list.push_back(value);

        // Allow chaining
        return *this;
    };

    /**
     *  Get access to the amount of members this value has
     */
    virtual size_t memberCount() override
    {
        return _list.size();
    }

    /**
     *  Get access to a member at a certain position
     *  @param position
     *  @return Value or nullptr if not present
     */
    virtual Value *memberAt(int position) override
    {
        // If we're out of bounds just return nullptr
        if (position < 0 || position >= memberCount()) return nullptr;

        // Just return it using the [] operator
        return _list[position];
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
     *  Get the begin and end iterator
     */
    const_iterator begin() const { return _list.begin(); }
    const_iterator end() const { return _list.end(); }
};

/**
 *  End namespace
 */
}

