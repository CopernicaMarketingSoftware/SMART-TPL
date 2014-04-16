/**
 *  Source.h
 *
 *  Base class for classes that can fetch a template. There are various
 *  implementations for this base class:
 *
 *      File        File from the local filesystem
 *      Buffer      In-memory buffer holding the template
 * 
 *  You can create your own derived classes if you for example want to create
 *  template that are fetched from a database or from any other source.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica Marketing Software
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class Source
{
protected:
    /**
     *  Constructor
     * 
     *  The constructor is protected, you should create an instance of File,
     *  Buffer or an implementation of the Source class that you create yourself.
     */
    Source() {}

    /**
     *  Underlying buffer, if you're implementing the Source class put your data in here.
     */
    std::string _buffer;
    
public:
    /**
     *  Destructor
     */
    virtual ~Source() {}

    /**
     *  Returns a const char* to the start of the buffer, use size() to get the length
     *  of this buffer.
     *
     *  @return const char*
     */
    const char* data() const { return _buffer.data(); };

    /**
     *  Returns the size of the buffer.
     *
     *  @return size_t
     */
    size_t size() const { return _buffer.size(); };
    

};

/**
 *  End namespace
 */
}

