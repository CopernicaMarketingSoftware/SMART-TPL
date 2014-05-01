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

public:
    /**
     *  Destructor
     */
    virtual ~Source() {}
    
    /**
     *  Name of the source
     * 
     *  This is the name by which the template is identifier. For file-templates
     *  this could be the filename, and for templates from other sources this
     *  could be a different name.
     * 
     *  @return const char*
     */
    virtual const char *name() const = 0;
    
    /**
     *  Is this a shared library?
     * 
     *  When the source represents a shared library, it means that that it could
     *  be opened by a call to dlopen(), and it is stored as a .so file on the
     *  system. The name() method should return the path to the shared library.
     * 
     *  @return bool
     */
    virtual bool library() const
    {
        // by default we return false, because this is the most likely
        // implementation for almost all source
        return false;
    }

    /**
     *  Returns a const char* to the start of the buffer, use size() to get the length
     *  of this buffer.
     *
     *  @return const char*
     */
    virtual const char *data() const = 0;

    /**
     *  Returns the size of the buffer.
     *
     *  @return size_t
     */
    virtual size_t size() const = 0;    

};

/**
 *  End namespace
 */
}

