/**
 *  VectorValue.h
 *
 *  A SmartTpl::Value which represents a vector with VariantValues
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
    VectorValue() : _value() {};
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
    virtual std::string toString() const override
    {
        return "";
    }

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual integer_t toNumeric() const override
    {
        return 0;
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const override
    {
        return !_value.empty();
    }

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    virtual double toDouble() const override
    {
        return 0.0;
    }

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    virtual size_t memberCount() const override
    {
        return _value.size();
    }

    /**
     *  Get access to a member value
     *
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Variant
     *
     */
    virtual VariantValue member(const char *name, size_t size) const override
    {
        // let's see if we can get a number out of the string
        try
        {
            // create string object
            std::string key(name, size);

            // convert to integer
            int idx = stoi(key);

            // use integer key for lookup
            return member(idx);
        }
        catch (...)
        {
            // no conversion possible
            return nullptr;
        }
        
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return Variant
     */
    virtual VariantValue member(size_t position) const override
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
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return VariantValue
     */
    virtual VariantValue member(const Value &position) const override
    {
        // use the position to lookup the member we're looking for
        return position.lookupIn(*this);
    }

    /**
     *  Use this value as index of another parent value
     *  @param  value       the value in which to look for this key
     *  @return VariantValue
     */
    virtual VariantValue lookupIn(const Value &value) const override
    {
        // we can not access another variable by using this vector
        return nullptr;
    }

    /**
     *  Create a new iterator that allows you to iterate over the subvalues
     *  feel free to return nullptr if you don't want to be able to iterate
     *  over your type
     *
     *  @return Newly allocated Iterator
     */
    virtual Iterator *iterator() const override;

    /**
     *  Regular vector push_back calls to later on expand your vector
     */
    void push_back(const VariantValue& value) { _value.push_back(value); }
    void push_back(VariantValue&& value) { _value.push_back(std::move(value)); }

    /**
     *  Regular emplace and emplace_back methods to later on expand your vector
     */
    template<typename ...Args>
    void emplace_back(Args&&... args) { _value.emplace_back(std::forward<Args>(args)...); }
};

/**
 *  End namespace
 */
}
