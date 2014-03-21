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
    

};

/**
 *  End namespace
 */
}

