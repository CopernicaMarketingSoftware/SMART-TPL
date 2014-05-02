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
namespace SmartTpl {

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
        // @todo remove the key and value from the local variables
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
     *  @return void*
     */
    void *key() const
    {
        return _source->key(_pos);
    }
    
    /**
     *  Retrieve pointer to the current member
     *  @return void*
     */
    void *value() const
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
}

