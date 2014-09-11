/**
 *  VectorValue.h
 *
 *  A SmartTpl::Value which represents a vector with VariantValues
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
class VectorValue : public Value
{
private:
    /**
     *  The actual vector
     */
    std::vector<VariantValue> _value;

public:
    /**
     *  Constructors
     */
    VectorValue(const std::vector<VariantValue>& value) : _value(value) {};
    VectorValue(std::vector<VariantValue>&& value) : _value(std::move(value)) {};
    VectorValue(const std::initializer_list<VariantValue>& value) : _value(value) {};

    /**
     *  Destructor
     */
    virtual ~VectorValue() {};

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
     *  @return numeric
     */
    numeric_t toNumeric() const override
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
        return _value.size();
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return Variant
     */
    VariantValue member(size_t position) const override
    {
        try
        {
            return _value.at(position);
        }
        catch (...)
        {
            return nullptr;
        }
    }

    /**
     *  Get access to the key at a certain position
     *  @param  position     Position of the key we want to retrieve
     *  @return Variant      Variant object, probably a string
     */
    VariantValue key(size_t position) const override
    {
        return std::to_string(position);
    }

    /**
     *  String length of the variable
     *
     *  @return size_t
     */
    size_t size() const override
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
    Iterator *iterator() const override;
};

/**
 *  End namespace
 */
}