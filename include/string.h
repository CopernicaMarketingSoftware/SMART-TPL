/**
 *  String.h
 *
 *  Class that represents a string variable
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class StringValue : public Value
{
private:
    /**
     *  Actual string value
     *  @var    std::string
     */
    const std::string _value;

public:
    /**
     *  Constructor
     *  @param  value   The string value we want to copy
     */
    StringValue(const std::string &value) : _value(value) {}
    StringValue(std::string &&value) : _value(std::move(value)) {}
    StringValue(const char *value, size_t size) : _value(value, size) {}

    /**
     *  Destructor
     */
    virtual ~StringValue() {}

    /**
     *  Convert the variable to a string
     *  @return const char *
     */
    virtual const char *toString() const override
    {
        return _value.c_str();
    }

    /**
     *  Convert the variable to a numeric value
     *  @see std::strtoul
     *  @return numeric
     */
    virtual numeric_t toNumeric() const override
    {
        return std::strtoul(_value.c_str(), (char**) NULL, 10);
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const override
    {
        return _value.size() > 0;
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
        return nullptr;
    }

    /**
     *  Get access to the amount of members this value has
     */
    virtual size_t memberCount() const override
    {
        return 0;
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return Variant
     */
    virtual Variant member(int position) const override
    {
        return nullptr;
    }

    /**
     *  Get access to the key at a certain position
     *  @param  position     Position of the key we want to retrieve
     *  @return Variant      Variant object, probably a string
     */
    virtual Variant key(int position) const override
    {
        return nullptr;
    }

    /**
     *  String length of the variable
     *
     *  @return int
     */
    virtual size_t size() const override
    {
        return _value.size();
    }
};

/**
 *  End namespace
 */
}

