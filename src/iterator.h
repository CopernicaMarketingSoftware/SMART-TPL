/**
 *  Iterator.h
 *
 *  Class that internally keeps track of the status of a foreach loop
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Include guard
 */
#pragma once

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class Iterator
{
private:
    /**
     *  Iterator
     *
     *  @var SmartTpl::Iterator
     */
    std::unique_ptr<SmartTpl::Iterator> _iterator;

public:
    /**
     *  Constructor
     *  @param  source      The source value object to iterate over
     */
    Iterator(const Value *source) :
        _iterator(source->iterator()) {}

    /**
     *  Destructor
     */
    virtual ~Iterator()
    {
        // @todo remove the key and value from the local variables??
        //
        //       (although i do not think it is disastrous if we keep
        //       the loop-variables in scope after the loop if completed)
    }

    /**
     *  Check if the iterator is still valid
     *  @return bool
     */
    bool valid() const
    {
        // if we have a valid _iterator call the valid() method on it
        if (_iterator) return _iterator->valid();

        // Otherwise we'll be invalid
        return false;
    }

    /**
     *  Retrieve a pointer to the current key
     *  @return Variant
     */
    VariantValue key() const
    {
        return _iterator->key();
    }

    /**
     *  Retrieve pointer to the current member
     *  @return Variant
     */
    VariantValue value() const
    {
        return _iterator->value();
    }

    /**
     *  Move to the next position
     */
    void next()
    {
        // increment position
        _iterator->next();
    }
};

/**
 *  End of namespace
 */
}}