/**
 *  Vector_Iterator.h
 *
 *  Iterator for Vectors
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
class VectorIterator : public SmartTpl::Iterator
{
private:
    const std::vector<Variant::Value> _vector;
    /**
     *  Iterator to the current position in our vector
     */
    std::vector<Variant::Value>::const_iterator _iter;

    /**
     *  End iterator which indicates where we should stop
     */
    const std::vector<Variant::Value>::const_iterator _end;

public:
    /**
     *  Constructor
     */
    VectorIterator(const std::vector<Variant::Value> &value)
    : _vector(value),
      _iter(_vector.begin()),
      _end(_vector.end())
    {}

    /**
     *  Deconstructor
     */
    virtual ~VectorIterator() {}

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
        return *_iter;
    }

    /**
     *  Retrieve a pointer to the current key
     *  @return Variant
     */
    virtual VariantValue key() const override
    {
        return nullptr;
    }
};

/**
 *  End namespace
 */
}}