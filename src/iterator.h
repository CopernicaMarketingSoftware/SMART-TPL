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
     *  The value object that is being iterated over
     *  @var Value*
     */
    Value *_source;

    /**
     *  Current position
     *
     *  @todo
     *      other sort of iterator implementation, in which we are not forced
     *      to use integers to keep the current index (which can be slow if 
     *      the underlying object is for example a std::map or std::list),
     *      the value class should have its own system for defining custom
     *      iterators.
     *
     *  @var int
     */
    int _pos = 0;

    /**
     *  Maximum position
     *  @var int
     */
    int _max;

public:
    /**
     *  Constructor
     *  @param  source      The source value object to iterate over
     */
    Iterator(Value *source) :
        _source(source), _max(source->memberCount()) {}

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
        // check if we have not yet reached the max
        return _pos < _max;
    }

    /**
     *  Retrieve a pointer to the current key
     *  @return Variant
     */
    Variant key() const
    {
        return _source->key(_pos);
    }

    /**
     *  Retrieve pointer to the current member
     *  @return Variant
     */
    Variant value() const
    {
        return _source->member(_pos);
    }

    /**
     *  Move to the next position
     */
    void next()
    {
        // increment position
        ++_pos;
    }
};

/**
 *  End of namespace
 */
}}