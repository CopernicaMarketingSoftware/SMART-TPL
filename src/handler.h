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
     *  Stack of our iterators
     *
     *  This is a stack of active {foreach} loops. The top of the stack
     *  contains the foreach loop that is now running. The stack contains just
     *  an integer with the current loop-counter/position in the Value
     */
    std::stack<unsigned int> _iterator_stack;

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
     *  assigned using "assign .. to ..", callbacks or they're simply the magic values in
     *  a foreach loop
     */
    std::map<const char *, Value*, cmp_str> _local_values;

    /**
     *  Will contain the local values that were created just here and should
     *  because of that be deleted
     *
     *  Can also contain externally created Values that were made managed using manageValue(Value*)
     */
    std::list<std::unique_ptr<Value>> _managed_local_values;

    /**
     *  Variant values coming directly from callbacks
     */
    std::list<Variant> _wrapped_values;

public:
    /**
     *  Constructor
     *  @param  data        pointer to the data
     */
    Handler(const Data *data) : _data(data) 
    {
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
        if (value != nullptr) return value;

        // if we still didn't find it let's look for a callback function
        auto callback = _data->callback(name, size);

        // Did we get a callback? No? nullptr it is
        if (callback == nullptr) return nullptr;

        // We got the callback, let's execute it and cache the output
        Variant *variant = new Variant((*callback)());
        manageValue(variant);
        _local_values[name] = variant;

        // Return the value
        return variant;
    }

    /**
     *  Start a new foreach loop and push the initial position of a for loop
     */
    void startLoop()
    {
        _iterator_stack.push(0);
    }

    /**
     *  Iterate over a multi value value object
     *  @param value       The value to iterate over
     *  @param key         The magic key to assign the next value to
     *  @param size        The size of the magic key
     *  @param keyvar      The magic key to assign the member key to
     *  @param keyvar_size The size of keyvar (may be 0!)
     *  @return True if we should continue looping, false otherwise
     */
    bool iterate(Value *value, const char *key, size_t size, const char* keyvar, size_t keyvar_size)
    {
        // In case our _iterator_stack is empty just return false
        if (_iterator_stack.empty()) return false;

        // Retrieve the amount of members in value
        size_t len = value->memberCount();

        // We can't even iterate over this...
        if (len == 0) return false;

        // get our iterator
        unsigned int &iter = _iterator_stack.top();

        // if our iterator goes out of bounds that means that we are done and should clean up
        if (iter >= len)
        {
            // remove our magic value
            auto liter = _local_values.find(key);
            if (liter != _local_values.end()) _local_values.erase(liter);

            // Let's look for our magic key var as well if we used it that is
            if (keyvar_size > 0)
            {
                liter = _local_values.find(keyvar);
                if (liter != _local_values.end()) _local_values.erase(liter);
            }

            // Remove this loop from the stack
            _iterator_stack.pop();

            // and tell the callback to stop looping
            return false;
        }
        else
        {
            // assign the next element in the iteration to our magic key
            _local_values[key] = value->member(iter);
            if (keyvar_size > 0)
            {
                // The foreach wants a key, so let's try to get one
                Value *k = value->key(iter);

                // Value isn't required to return a key so let's check if it is nullptr or not
                if (k != nullptr) _local_values[keyvar] = k;
            }

            // increase our iterator
            iter++;
            return true;
        }
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
     *  @param value       The value we would like to assign
     *  @param key         The name for our local variable
     *  @param key_size    The size of key
     */
    void assign(Value *value, const char *key, size_t key_size)
    {
        _local_values[key] = value;
    }

    /**
     *  Assign a boolean value to a local variable
     *  @param boolean     The boolean value we want to assign
     *  @param key         The name for our local variable
     *  @param key_size    The size of key
     */
    void assignBoolean(bool boolean, const char *key, size_t key_size)
    {
        _local_values[key] = BooleanValue::get(boolean);
    }

    /**
     *  Assign a numeric value to a local variable
     *  @param value        The numeric value we want to assign
     *  @param key          The name of our local variable
     *  @param key_size     The size of key
     */
    void assignNumeric(long value, const char *key, size_t key_size)
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
    void assignString(const std::string &value, const char *key, size_t key_size)
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

