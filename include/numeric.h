/**
 *  Numeric.h
 *
 *  Class that represents a numeric variable
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
class NumericValue : public Value
{
private:
    /**
     *  Underlying value
     *  @var numeric
     */
    const numeric_t _value;

    /**
     *  String representation
     *  @var std::string
     */
    std::string *_str = nullptr;

public:
    /**
     *  Constructor
     *  @param  value
     */
    NumericValue(numeric_t value) : _value(value) {}

    /**
     *  Destructor
     */
    virtual ~NumericValue() 
    {
        if (_str) delete _str;
    }

    /**
     *  Convert the variable to a string
     *  @return const char *
     */
    virtual const char *toString() override
    {
        if (_str) return _str->c_str();
        _str = new std::string(std::to_string(_value));
        return _str->c_str();
    }

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual numeric_t toNumeric() override
    {
        return _value;
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() override
    {
        return _value != 0;
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
        return nullptr;
    }

    /**
     *  Get access to the amount of members this value has
     */
    virtual size_t memberCount() override
    {
        return 0;
    }

    /**
     *  Get access to a member at a certain position
     *  @param position
     *  @return Value or nullptr if not present
     */
    virtual Value *memberAt(int position) override
    {
        return nullptr;
    }

    /**
     *  String length of the variable
     * 
     *  @return int
     */
    virtual size_t size() override
    {
        if (_str) return _str->size();
        _str = new std::string(std::to_string(_value));
        return _str->size();
    }
};

/**
 *  End namespace
 */
}

