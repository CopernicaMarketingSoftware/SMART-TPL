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
     *  The map we're iterating over
     */
    const std::map<std::string, VariantValue> _map;

    /**
     *  Iterator to the current position in our map
     */
    std::map<std::string, VariantValue>::const_iterator _iter;

    /**
     *  End iterator which indicates where we should stop
     */
    const std::map<std::string, VariantValue>::const_iterator _end;

public:
    /**
     *  Constructor
     */
    MapIterator(const std::map<std::string, VariantValue> &value)
    : _map(value),
      _iter(_map.begin()),
      _end(_map.end())
    {}

    /**
     *  Deconstructor
     */
    virtual ~MapIterator() {}

    /**
     *  Check if the iterator is still valid
     *  @return bool
     */
    bool valid() const override
    {
        return _iter != _end;
    }

    /**
     *  Move to the next position
     */
    void next() override
    {
        ++_iter;
    }

    /**
     *  Retrieve pointer to the current member
     *  @return Variant
     */
    VariantValue value() const override
    {
        return _iter->second;
    }

    /**
     *  Retrieve a pointer to the current key
     *  @return Variant
     */
    VariantValue key() const override
    {
        return _iter->first;
    }
};

/**
 *  End namespace
 */
}}