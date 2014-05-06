/**
 *  Parameters.h
 *
 *  A container of values that can be passed to the modifiers
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 *
 */
class Parameters
{
public:
    /**
     *  const_iterator typedef
     */
    typedef std::vector<Variant>::const_iterator const_iterator;
    typedef std::vector<Variant>::const_reverse_iterator const_reverse_iterator;
private:
    /**
     */
    std::vector<Variant> _values;

public:
    /**
     *  Constructor
     */
    Parameters() {};

    /**
     *  Deconstructor
     */
    virtual ~Parameters() {};

    /**
     *  Add a new value to the parameters
     */
    void add(const Variant &value)
    {
        _values.push_back(value);
    }

    /**
     *  Return the value at position
     *  @param  position    The position of the value you would like to retrieve
     *  @return Variant
     */
    Variant get(int position) const
    {
        // If we're out of bounds just return a empty Variant to avoid undefined behavior
        if (position >= _values.size()) return Variant();

        // Return the Variant store at position otherwise
        return _values[position];
    }

    /**
     *  Retrieve the amount of values in this Parameters object
     *  @return size_t      The amount of values
     */
    const size_t size() const
    {
        return _values.size();
    }

    /**
     *  Get the begin and end iterator
     */
    const_iterator begin() const { return _values.begin(); }
    const_iterator end() const { return _values.end(); }
    const_reverse_iterator rbegin() const { return _values.rbegin(); }
    const_reverse_iterator rend() const { return _values.rend(); }
};

/**
 *  End namespace
 */
}