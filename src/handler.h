/**
 *  Handler.h
 *
 *  Internal class that captures the output while the template is being
 *  processed.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class Handler
{
private:
    /**
     *  Output buffer
     *  @var    std::string
     */
    std::string _buffer;

    /**
     *  The underlying data
     *  @var    Data
     */
    const Data *_data;

    /**
     *  Compare functor necessary for the map
     */
    struct cmp_str
    {
        /**
         *  Invoke operator
         *  @param  a
         *  @param  b
         *  @return bool
         */
        bool operator()(char const *a, char const *b) const
        {
            return std::strcmp(a, b) < 0;
        }
    };

    /**
     *  This map will contain values assigned during runtime, these can be
     *  assigned using "assign .. to ..", or the magic values inside
     *  foreach loops
     */
    std::map<const char *, Value*, cmp_str> _local_values;

    /**
     *  Will contain the local values that were created just here and should
     *  because of that be deleted
     *
     *  Can also contain externally created Values that were made managed using manageValue(Value*)
     */
    std::list<std::unique_ptr<Value>> _managed_local_values;


public:
    /**
     *  Constructor
     *  @param  data        pointer to the data
     */
    Handler(const Data *data) : _data(data) 
    {
        // we reserve some space in the output buffer, so that it is not
        // necessary to reallocate all the time (which is slow)
        _buffer.reserve(4096);
    }

    /**
     *  Destructor
     */
    virtual ~Handler() {}

    /**
     *  Write data to the buffer
     *  @param  buffer
     *  @param  size
     */
    void write(const char *buffer, size_t size)
    {
        _buffer.append(buffer, size);
    }

    /**
     *  Get access to a variable
     *  @param  name
     *  @param  size
     *  @return Value
     */
    Value *variable(const char *name, size_t size)
    {
        // look through our local values first
        auto iter = _local_values.find(name);
        if (iter != _local_values.end()) return iter->second;

        // didn't find it? get the variable from the data object
        Value *value = _data->value(name, size);

        // check if our value is cacheable
        if (value->cacheable())
        {
            // As we are cacheable just use the cache() method and push that to our _local_values
            Value *output = new Variant(value->cache());
            _local_values[name] = output;

            // Make our duplicate of the cache() output managed
            _managed_local_values.push_back(std::unique_ptr<Value>(output));

            // Return the output
            return output;
        }

        // As we aren't cacheable just return the original value from _data
        return value;
    }

    /**
     *  Return the generated output
     *  @return std::string
     */
    const std::string &output() const
    {
        return _buffer;
    }

    /**
     *  Return a modifier by name
     *  @param name
     *  @param size
     *  @return Modifier
     */
    Modifier* modifier(const char* name, size_t size)
    {
        return _data->modifier(name, size);
    }

    /**
     *  Assign an existing value to a local variable
     *
     *  @param value       The value we would like to assign
     *  @param key         The name for our local variable
     *  @param key_size    The size of key
     */
    void assign(const char *key, size_t key_size, Value *value)
    {
        _local_values[key] = value;
    }

    /**
     *  Assign a boolean value to a local variable
     *  @param boolean     The boolean value we want to assign
     *  @param key         The name for our local variable
     *  @param key_size    The size of key
     */
    void assign(const char *key, size_t key_size, bool boolean)
    {
        _local_values[key] = BooleanValue::get(boolean);
    }

    /**
     *  Assign a numeric value to a local variable
     *  @param value        The numeric value we want to assign
     *  @param key          The name of our local variable
     *  @param key_size     The size of key
     */
    void assign(const char *key, size_t key_size, long value)
    {
        Value *v = new NumericValue(value);
        _managed_local_values.push_back(std::unique_ptr<Value>(v));
        _local_values[key] = v;
    }

    /**
     *  Assign a string value to a local variable
     *  @param value          The string value we want to assign
     *  @param key            The name of our local variable
     *  @param key_size       The size of key
     */
    void assign(const char *key, size_t key_size, const std::string &value)
    {
        Value *v = new StringValue(value);
        _managed_local_values.push_back(std::unique_ptr<Value>(v));
        _local_values[key] = v;
    }

    /**
     *  Make this value object managed by the handler
     *  @param value    The value object to make managed
     */
    void manageValue(Variant *value)
    {
        _managed_local_values.push_back(std::unique_ptr<Value>(value));
    }
};

/**
 *  End namespace
 */
}

