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
private:
    /**
     *  Pointer to the buffer
     *  @var    const char *
     */
    const char *_buffer;
    
    /**
     *  Size of the buffer
     *  @var    size_t
     */
    size_t _size;
    
public:
    /**
     *  Constructor
     * 
     *  The buffer is not copied, you must make sure that the buffer parameter
     *  points to a valid memory buffer for the entire lifetime of the Buffer
     *  object.
     *  
     *  @param  buffer      Pointer to the buffer
     *  @param  size        Size of the buffer
     */
    Buffer(const char *buffer, size_t size) :
        _buffer(buffer), _size(size) {}
    
    /**
     *  Destructor
     */
    virtual ~Buffer() {}
};
    
/**
 *  End namespace
 */
}
