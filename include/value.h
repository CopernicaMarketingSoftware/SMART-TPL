/**
 *  Value.h
 *
 *  Interface that describes a value. This class can be extended to create
 *  your own custom template variables.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Typedef for a general numeric type, if we ever decide to change it we'll just
 *  have to modify this. For backwards compatibility, we also support the numeric_t
 */
using integer_t = int64_t;
using numeric_t = integer_t;

/**
 *  Forward declaration of VariantValue so we can return VariantValue
 */
class VariantValue;

/**
 *  Class definition
 */
class Value
{
public:
    /**
     *  Destructor
     */
    virtual ~Value() {};

    /**
     *  If this type was used in an arithmetric operation, should it then be
     *  treated as a floating point number, or as a regular integer?
     *  @return bool
     */
    virtual bool arithmeticFloat() const;

    /**
     *  Convert the value to a string
     *  @return std::string
     */
    virtual std::string toString() const;

    /**
     *  Convert the variable to a numeric value (this is a deprecated method)
     *  @return numeric_t
     */
    virtual numeric_t toNumeric() const;
    
    /**
     *  Convert the variable to an integer value
     *  @return integer_t
     */
    virtual integer_t toInteger() const;

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const;

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    virtual double toDouble() const;

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    virtual size_t memberCount() const;

    /**
     *  Get access to a member value
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return VariantValue
     */
    virtual VariantValue member(const char *name, size_t size) const;

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return VariantValue
     */
    virtual VariantValue member(size_t position) const;

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return VariantValue
     */
    virtual VariantValue member(const Value &position) const;

    /**
     *  Use this value as index of another parent value
     *  @param  value       the value in which to look for this key
     *  @return VariantValue
     */
    virtual VariantValue lookupIn(const Value &value) const;

    /**
     *  Create a new iterator that allows you to iterate over the subvalues
     *  feel free to return nullptr if you don't want to be able to iterate
     *  over your type
     *
     *  @return Newly allocated Iterator
     */
    virtual Iterator *iterator() const;
};

/**
 *  End namespace
 */
}
