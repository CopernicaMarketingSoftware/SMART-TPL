/**
 *  Handler.h
 *
 *  Internal class that captures the output while the template is being
 *  processed.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
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
    std::map<const Value*, std::string> _managed_strings;

    /**
     *  An error message possibly set by markFailed, if this is empty
     *  there were simply no errors.
     *  @var std::string
     */
    std::string _error;

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
     *  Output a integer value
     *  @param  number   The integer value to output
     */
    void outputInteger(integer_t number)
    {
        _buffer.append(std::to_string(number));
    }

    /**
     *  Output a boolean value
     *  @param  value   The value to output
     */
    void outputBoolean(bool value)
    {
        _buffer.append(value ? "true" : "false");
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
    void assign(const char *key, size_t key_size, VariantValue value)
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
     *  Assign a integer value to a local variable
     *  @param key          The name of our local variable
     *  @param key_size     The size of key
     *  @param value        The integer value we want to assign
     */
    void assign(const char *key, size_t key_size, integer_t value)
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

        // if it is already hold by the data object we also do not have to manage it
        if (_data->contains(value)) return false;

        // If they are not we start managing it
        _managed_local_values.emplace_back(value);

        // Return true to indicate that we are now managing value
        return true;
    }

    /**
     *  Make the following iterator managed
     *  @param iter The iterator to make managed
     */
    void manageIterator(Iterator *iter)
    {
        _managed_iterators.emplace_back(iter);
    }

    /**
     *  Make the following set of parameters managed
     *  @param parameters_count The amount of parameters that will be placed into it
     */
    SmartTpl::Parameters* newParameters(size_t parameters_count)
    {
        // use emplace to place our new parameters object directly in place
        auto iter = _managed_parameters.emplace(_managed_parameters.begin(), new SmartTpl::Parameters());

        // reserve the parameters_count
        (*iter)->reserve(parameters_count);

        // return the raw pointer to our parameters
        return iter->get();
    }

    /**
     *  Return either a cached string associated with value or cache it right here right now
     *  @param value The Value to take the string of and make it managed
     */
    std::string* manageString(const Value* value)
    {
        // look for the string under the key value
        auto iter = _managed_strings.find(value);

        // if we're not cached we're gonna cache it
        if (iter == _managed_strings.end())
        {
            // turn value into a string using toString and insert it into our map
            auto inserted = _managed_strings.emplace(value, value->toString());

            // set our iterator to the first element of the return value of inserted
            // which is the iterator of the new element
            iter = inserted.first;
        }

        // return a pointer to the value of our iterator
        return &iter->second;
    }

    /**
     *  @return The escaper to use to print the variables
     */
    const Escaper *escaper() const { return _encoder; }

    /**
     *  Error related methods that allow us to mark our handler as failed
     */
    void markFailed(const char *error) { _error = error; };
    bool failed() const { return !_error.empty(); };
    const std::string &error() const { return _error; };
};

/**
 *  End namespace
 */
}}
