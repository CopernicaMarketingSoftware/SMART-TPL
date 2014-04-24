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
     *  Map values to the modifiers that created them so we know who
     *  needs to clean them up
     */
    std::map<Modifier*, std::set<Value*>> _destroy_later;

    /**
     *  Map with the 'iterators', we basically just map where we are in
     *  looping through Value*
     */
    std::map<Value*, size_t> _iterators;

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
     *  In here we map our magic foreach keys to actual values, we're basically
     *  injecting the variable callbacks
     */
    std::map<const char *, Value*, cmp_str> _loop_values;

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
    virtual ~Handler()
    {
        // Loop through all the modifiers in the _destroy_later map
        for (auto & m : _destroy_later)
        {
            // For each modifier loop through all the values and clean them up
            for (auto & v : m.second) m.first->cleanup(v);
        }
    }
    
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
        auto iter = _loop_values.find(name);
        if (iter != _loop_values.end()) return iter->second;
        // get the variable from the data object
        return _data->value(name,size);
    }

    bool iterate(Value *value, const char *key, size_t size)
    {
        // Retrieve the amount of members in value
        size_t len = value->memberCount();

        // We can't even iterate over this...
        if (len == 0) return false;

        // Let's look up where we were with iterating
        auto iter = _iterators.find(value);
        if (iter == _iterators.end())
        {
            _iterators[value] = 0;
            _loop_values[key] = value->memberAt(0);
            return true;
        }
        else
        {
            size_t newpos = ++_iterators[value];
            if (newpos >= len)
            {
                _iterators.erase(iter);
                auto liter = _loop_values.find(key);
                if (liter != _loop_values.end()) _loop_values.erase(liter);
                return false;
            }
            _loop_values[key] = value->memberAt(newpos);
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
     *  Mark a value as clean up later on
     *  @param modifier
     *  @param value
     */
    void destroyValue(Modifier *modifier, Value* value)
    {
        _destroy_later[modifier].insert(value);
    }
};

/**
 *  End namespace
 */
}

