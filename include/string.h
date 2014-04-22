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
     *  @param  value
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
    virtual const char *toString() override
    {
        return _value.c_str();
    }
    
    /**
     *  Convert the variable to a numeric value
     *  @see std::atoi
     *  @return int
     */
    virtual int toNumeric() override
    {
        return std::atoi(_value.c_str());
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() override
    {
        return _value.size() > 0;
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
     *  String length of the variable
     * 
     *  @return int
     */
    virtual size_t size() override
    {
        return _value.size();
    }
};

/**
 *  End namespace
 */
}
