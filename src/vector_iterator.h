/**
 *  Vector_Iterator.h
 *
 *  Iterator for VectorValues
 *
 *  @author Toon Schoenmakers <toon.schonemakers@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class VectorIterator : public SmartTpl::Iterator
{
private:
    /**
     *  The vector we're iterating over
     *  @var std::vector
     */
    const std::vector<VariantValue> _vector;

    /**
     *  Iterator to the current position in our vector
     *  @var const_iterator
     */
    std::vector<VariantValue>::const_iterator _iter;

    /**
     *  End iterator which indicates where we should stop
     *  @var const_iterator
     */
    const std::vector<VariantValue>::const_iterator _end;

    /**
     *  A simple counter so we can at least return some kind of key
     *  @var integer_t
     */
    integer_t _count;

public:
    /**
     *  Constructor
     */
    VectorIterator(const std::vector<VariantValue> &value)
    : _vector(value),
      _iter(_vector.begin()),
      _end(_vector.end()),
      _count(0)
    {}

    /**
     *  Deconstructor
     */
    virtual ~VectorIterator() {}

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
        ++_count;
    }

    /**
     *  Retrieve pointer to the current member
     *  @return Variant
     */
    VariantValue value() const override
    {
        return *_iter;
    }

    /**
     *  Retrieve a pointer to the current key
     *  @return Variant
     */
    VariantValue key() const override
    {
        return _count;
    }
};

/**
 *  End namespace
 */
}}
