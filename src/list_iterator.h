/**
 *  List_Iterator.h
 *
 *  Iterator for ListValues
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
class ListIterator : public SmartTpl::Iterator
{
private:
    /**
     *  Iterator to the actual list from ListValue
     */
    ListValue::const_iterator _iter;

    /**
     *  End iterator of the actual list from ListValue
     */
    const ListValue::const_iterator _end;

public:
    ListIterator(const ListValue *list)
    : _iter(list->begin())
    , _end(list->end()) {};

    /**
     *  Destructor
     */
    virtual ~ListIterator() {};

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
        return *_iter;
    }

    /**
     *  Retrieve a pointer to the current key
     *  @return Variant
     */
    virtual Variant key() const
    {
        return nullptr;
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