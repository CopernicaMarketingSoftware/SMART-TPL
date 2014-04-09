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
        // get the variable from the data object
        return _data->value(name,size);
    }
    
    /**
     *  Return the generated output
     *  @return std::string
     */
    const std::string &output() const
    {
        return _buffer;
    }
};

/**
 *  End namespace
 */
}
