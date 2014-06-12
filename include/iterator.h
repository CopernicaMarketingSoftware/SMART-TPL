/**
 *  Iterator.h
 *
 *  Interface that describes an iterator. This class can be extended to create
 *  iterators for your own value classes.
 *
 *  @author Toon Schoenmakers <toon.schonemakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Forward declarations
 */
class VariantValue;

/**
 *  Class definition
 */
class Iterator
{
protected:
    /**
     *  Constructor
     *
     *  The constructor is protected, you should subclass this class instead.
     */
    Iterator() {}

public:
    /**
     *  Destructor
     */
    virtual ~Iterator() {};

    /**
     *  Check if the iterator is still valid
     *  @return bool
     */
    virtual bool valid() const = 0;

    /**
     *  Move to the next position
     */
    virtual void next() = 0;

    /**
     *  Retrieve pointer to the current member
     *  @return Variant
     */
    virtual VariantValue value() const = 0;

    /**
     *  Retrieve a pointer to the current key
     *  @return Variant
     */
    virtual VariantValue key() const = 0;
};

/**
 *  End namespace
 */
}

