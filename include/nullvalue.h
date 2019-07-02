/**
 *  NullValue.h
 *
 *  A SmartTpl::Value which represents a nullptr
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class NullValue : public Value
{
public:
    /**
     *  Constructors
     */
    NullValue() {}

    /**
     *  Destructor
     */
    virtual ~NullValue() {};

    /**
     *  Convert the value to a string
     *  @return std::string
     */
    std::string toString() const override
    {
        return "";
    };

    /**
     *  Convert the variable to a numeric value
     *  @return integer_t
     */
    integer_t toNumeric() const override
    {
        return 0;
    };

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    bool toBoolean() const override
    {
        return false;
    };

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    double toDouble() const override
    {
        return 0.0;
    };

    /**
     *  Get access to a member value
     *
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Variant
     *
     */
    VariantValue member(const char *name, size_t size) const override
    {
        return nullptr;
    }

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    size_t memberCount() const override
    {
        return 0;
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return Variant
     */
    VariantValue member(size_t position) const override
    {
        return nullptr;
    }

    /**
     *  Create a new iterator that allows you to iterate over the subvalues
     *  feel free to return nullptr if you don't want to be able to iterate
     *  over your type
     *
     *  @return Newly allocated Iterator
     */
    Iterator *iterator() const override
    {
        return nullptr;
    }
};

/**
 *  End namespace
 */
}
