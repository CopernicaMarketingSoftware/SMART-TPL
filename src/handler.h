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
namespace SmartTpl { namespace Internal {

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
     *  The encoder to use for variables
     *  @var    Escaper
     */
    const Escaper *_encoder;

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
    std::map<const char *, const Value*, cmp_str> _local_values;

    /**
     *  Will contain the local values that were created just here and should
     *  because of that be deleted
     *
     *  Can also contain externally created Values that were made managed using manageValue(Value*)
     *  @see manageValue
     */
    std::list<std::unique_ptr<const Value>> _managed_local_values;

    /**
     *  List of iterators that we are managing
     *  @see manageIterator
     */
    std::list<std::unique_ptr<Iterator>> _managed_iterators;

    /**
     *  List of parameters that we are managing
     *  @see manageParameters
     */
    std::list<std::unique_ptr<SmartTpl::Parameters>> _managed_parameters;

    /**
     *  A list of strings that are meant to kept in scope so their buffers remain valid
     *  @see manageString
     */
    std::list<std::string> _managed_strings;

    /**
     *  Are we supposed to throw because of a runtime failure or not?
     */
    bool _failed = false;

public:
    /**
     *  Constructor
     *  @param  data        pointer to the data
     *  @param  escaper     the escaper to use for the printed variables
     */
    Handler(const Data *data, const Escaper *escaper) : _data(data), _encoder(escaper)
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
     *  Output the Value object and most importantly, encode it if needed
     *  @param  value
     *  @param  escape
     */
    void output(const Value *value, bool escape)
    {
        // Turn the value into a string
        std::string work = value->toString();

        // Should we escape the value?
        if (escape) work = _encoder->encode(work);

        // Append it to our buffer
        _buffer.append(work);
    }

    /**
     *  Output a numeric value
     *  @param  number   The numberic value to output
     */
    void outputNumeric(numeric_t number)
    {
        _buffer.append(std::to_string(number));
    }

    /**
     *  Get access to a variable
     *  @param  name
     *  @param  size
     *  @return Value
     */
    const Value *variable(const char *name, size_t size) const
    {
        // look through our local values first
        auto iter = _local_values.find(name);
        if (iter != _local_values.end()) return iter->second;

        // didn't find it? get the variable from the data object
        return _data->value(name, size);
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
    void assign(const char *key, size_t key_size, const VariantValue &value)
    {
        VariantValue *copy = new VariantValue(value);
        manageValue(copy);
        _local_values[key] = copy;
    }

    /**
     *  Assign an existing value to a local variable
     *
     *  @param value       The value we would like to assign
     *  @param key         The name for our local variable
     *  @param key_size    The size of key
     */
    void assign(const char *key, size_t key_size, VariantValue &&value)
    {
        VariantValue *copy = new VariantValue(std::move(value));
        manageValue(copy);
        _local_values[key] = copy;
    }

    /**
     *  Assign a just allocated Value to a specify key
     *
     *  @param  key         The name of our local variable
     *  @param  key_size    The size of key
     *  @param  value       The newly allocated value we would like to assign
     */
    void assign(const char *key, size_t key_size, const Value *value)
    {
        manageValue(value);
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
        assign(key, key_size, VariantValue(boolean));
    }

    /**
     *  Assign a numeric value to a local variable
     *  @param value        The numeric value we want to assign
     *  @param key          The name of our local variable
     *  @param key_size     The size of key
     */
    void assign(const char *key, size_t key_size, numeric_t value)
    {
        assign(key, key_size, VariantValue(value));
    }

    /**
     *  Assign a floating point value to a local variable
     *  @param value        The floating point value we want to assign
     *  @param key          The name of our local variable
     *  @param key_size     The size of key
     */
    void assign(const char *key, size_t key_size, double value)
    {
        assign(key, key_size, VariantValue(value));
    }

    /**
     *  Assign a string value to a local variable
     *  @param value          The string value we want to assign
     *  @param key            The name of our local variable
     *  @param key_size       The size of key
     */
    void assign(const char *key, size_t key_size, const std::string &value)
    {
        assign(key, key_size, VariantValue(value));
    }

    /**
     *  Make this value object managed by the handler
     *  @param  value    The value object to make managed
     *  @return True if we created a new shared pointer
     */
    bool manageValue(const Value *value)
    {
        // Check if someone is already managing value or not
        for (auto &v : _managed_local_values)
        {
            // In case we found it that means that we are already managed
            if (v.get() == value) return false;
        }

        // If they are not we start managing it
        _managed_local_values.emplace_back(value);

        // Return true to indicate that we are now managing value
        return true;
    }

    /**
     *  Make the following iterator managed
     */
    void manageIterator(Iterator *iter)
    {
        _managed_iterators.emplace_back(iter);
    }

    /**
     *  Make the following set of parameters managed
     */
    void manageParameters(SmartTpl::Parameters *params)
    {
        _managed_parameters.emplace_back(params);
    }

    /**
     *  Make a string managed and return the const char* pointer which will remain in scope
     */
    const char* manageString(std::string &&str)
    {
        // insert it in our managed strings list and return it
        return _managed_strings.insert(_managed_strings.end(), std::move(str))->c_str();
    }

    /**
     *  @return The escaper to use to print the variables
     */
    const Escaper *escaper() const { return _encoder; }

    /**
     *  Error related methods that allow us to mark our handler as failed
     */
    void markFailed() { _failed = true; };
    bool failed() const { return _failed; };
};

/**
 *  End namespace
 */
}}
