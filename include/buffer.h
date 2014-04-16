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
 *  @copyright 2014 Copernica BV
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
public:
    /**
     *  Constructor
     *  
     *  @param  buffer      Pointer to the buffer
     *  @param  size        Size of the buffer
     */
    Buffer(const char *buffer, size_t size) {
        _buffer.append(buffer, size);
    }

    /**
     *  Constructor
     *
     *  @param  buffer      Create buffer from a std::string
     */
    Buffer(const std::string& buffer) : Buffer(buffer.data(), buffer.size()) {};
    
    /**
     *  Destructor
     */
    virtual ~Buffer() {}
};
    
/**
 *  End namespace
 */
}
