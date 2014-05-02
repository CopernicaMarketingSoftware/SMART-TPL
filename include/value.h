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
typedef int numeric_t;

/**
 *  Forward declaration of Variant so we can return Variant from cache()
 */
class Variant;

/**
 *  Class definition
 */
class Value
{
protected:
    /**
     *  Should this value be cached using cache() or not?
     *  False by default
     */
    bool _cacheable = false;
public:
    /**
     *  Destructor
     */
    virtual ~Value() {};

    /**
     *  Returns if this value is cachable or not
     */
    bool cacheable() const { return _cacheable; }

    /**
     *  Convert the value to a string
     *  @return const char *
     */
    virtual const char *toString() = 0;

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual numeric_t toNumeric() = 0;

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() = 0;

    /**
     *  Get access to a member value
     * 
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Value
     */
    virtual Value *member(const char *name, size_t size) = 0;

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    virtual size_t memberCount() = 0;

    /**
     *  Get access to a member at a certain position
     *  @param  position
     *  @return Value       Value object, or a nullptr if not present
     */
    virtual Value *member(int position) = 0;

    /**
     *  Get access to the key at a certain position
     *  @param position
     *  @return The name of the key at position or nullptr otherwise
     */
    virtual Value *key(int position) = 0;

    /**
     *  String length of the variable
     * 
     *  @return size_t
     */
    virtual size_t size() = 0;

    /**
     *  Method used to get a instance of this value
     */
    virtual Variant cache() = 0;
};

/**
 *  End namespace
 */
}

