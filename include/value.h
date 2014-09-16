/**
 *  Value.h
 *
 *  Interface that describes a value. This class can be extended to create
 *  your own custom template variables.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Typedef for a general numeric type, if we ever decide to change it we'll just
 *  have to modify this.
 */
using numeric_t = int64_t;

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
     *  Convert the value to a string
     *  @return std::string
     */
    virtual std::string toString() const = 0;

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual numeric_t toNumeric() const = 0;

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const = 0;

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    virtual double toDouble() const = 0;

    /**
     *  Get access to a member value
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return VariantValue
     */
    virtual VariantValue member(const char *name, size_t size) const = 0;

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    virtual size_t memberCount() const = 0;

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return VariantValue
     */
    virtual VariantValue member(size_t position) const = 0;

    /**
     *  Create a new iterator that allows you to iterate over the subvalues
     *  feel free to return nullptr if you don't want to be able to iterate
     *  over your type
     *
     *  @return Newly allocated Iterator
     */
    virtual Iterator *iterator() const = 0;
};

/**
 *  End namespace
 */
}
