/**
 *  Map_Iterator.h
 *
 *  Iterator for MapValues
 *
 *  @author Toon Schoenmakers <toon.schonemakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class MapIterator : public SmartTpl::Iterator
{
private:
    /**
     *  Iterator of the actual std::map of MapValue
     */
    MapValue::const_iterator _iter;

    /**
     *  End iterator of the actual std::map of MapValue
     */
    const MapValue::const_iterator _end;

public:
    MapIterator(const MapValue *map)
    : _iter(map->begin())
    , _end(map->end()) {};

    /**
     *  Destructor
     */
    virtual ~MapIterator() {};

    /**
     *  Check if the iterator is still valid
     *  @return bool
     */
    virtual bool valid() const
    {
        return _iter != _end;
    }

    /**
     *  Retrieve pointer to the current member
     *  @return Variant
     */
    virtual Variant value() const
    {
        return _iter->second;
    }

    /**
     *  Retrieve a pointer to the current key
     *  @return Variant
     */
    virtual Variant key() const
    {
        return _iter->first;
    }

    /**
     *  Move to the next position
     */
    virtual void next()
    {
        ++_iter;
    }
};

/**
 *  End namespace
 */
}}