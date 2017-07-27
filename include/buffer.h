/**
 *  Buffer.h
 *
 *  Template source that can be used for templates that are fetched from
 *  memory.
 *
 *  Explanation: when you instantiate a Template object, you need to pass
 *  a Source object to it to tell the Template object where it can be found.
 *  This Buffer class is one of the available Source objects that can be used
 *  for templates that are already in memory.
 *
 *  Important: the buffer that is passed to the constructor should be valid
 *  for as long as the Memory object exists!
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2017 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class Buffer : public Source
{
private:
    /**
     *  The internal buffer
     *  @var std::string
     */
    std::string _buffer;

public:
    /**
     *  Constructor
     *
     *  @param  buffer      Pointer to the buffer
     *  @param  size        Size of the buffer
     *  @param  version     Source code version (2 is more forgiving)
     */
    Buffer(const char *buffer, size_t size, size_t version = 1) : Source(version), _buffer(buffer, size) {}

    /**
     *  Constructor
     *
     *  @param  buffer      Pointer to the buffer
     */
    Buffer(const char *buffer) : Source(1), _buffer(buffer) {}

    /**
     *  Constructor
     *
     *  @param  buffer      Create buffer from a std::string
     *  @param  version     Source code version (2 is more forgiving)
     */
    Buffer(const std::string &buffer, size_t version = 1) : Source(version), _buffer(buffer) {}
    Buffer(std::string &&buffer, size_t version = 1) : Source(version), _buffer(std::move(buffer)) {}

    /**
     *  Destructor
     */
    virtual ~Buffer() {}

    /**
     *  Name of the source
     *
     *  This is the name by which the template is identifier. For file-templates
     *  this could be the filename, and for templates from other sources this
     *  could be a different name.
     *
     *  @return const char*
     */
    const char *name() const override
    {
        // an in-memory buffer does not have a variable name, return an empty string instead
        return "";
    }

    /**
     *  Returns a const char* to the start of the buffer, use size() to get the length
     *  of this buffer.
     *
     *  @return const char*
     */
    const char *data() const override
    {
        // stored in a member
        return _buffer.data();
    }

    /**
     *  Returns the size of the buffer.
     *
     *  @return size_t
     */
    size_t size() const override
    {
        // stored in a member
        return _buffer.size();
    }
    
    /**
     *  Is the buffer empty
     * 
     *  @return bool
     */
    bool empty() const
    {
        // pass on to buffer
        return _buffer.empty();
    }
    
    /**
     *  Cast the buffer to a string
     *  @return std::string
     */
    operator const std::string&() const
    {
        return _buffer;
    }
};

/**
 *  End namespace
 */
}
