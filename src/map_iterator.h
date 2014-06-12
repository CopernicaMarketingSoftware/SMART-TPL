/**
 *  Map_Iterator.h
 *
 *  Iterator for Maps
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
    const std::map<std::string, Variant::Value> _map;
    /**
     *  Iterator to the current position in our vector
     */
    std::map<std::string, Variant::Value>::const_iterator _iter;

    /**
     *  End iterator which indicates where we should stop
     */
    const std::map<std::string, Variant::Value>::const_iterator _end;

public:
    /**
     *  Constructor
     */
    MapIterator(const std::map<std::string, Variant::Value> &value)
    : _map(value)
    , _iter(_map.begin())
    , _end(_map.end())
    {}

    /**
     *  Deconstructor
     */
    virtual ~MapIterator() {}

    /**
     *  Check if the iterator is still valid
     *  @return bool
     */
    virtual bool valid() const override
    {
        return _iter != _end;
    }

    /**
     *  Move to the next position
     */
    virtual void next() override
    {
        ++_iter;
    }

    /**
     *  Retrieve pointer to the current member
     *  @return Variant
     */
    virtual VariantValue value() const override
    {
        return _iter->second;
    }

    /**
     *  Retrieve a pointer to the current key
     *  @return Variant
     */
    virtual VariantValue key() const override
    {
        return _iter->first;
    }
};

/**
 *  End namespace
 */
}}