/**
 *  File.h
 *
 *  Template source that can be used for templates that are fetched from
 *  the local filesystem.
 * 
 *  Explanation: when you instantiate a Template object, you need to pass
 *  a Source object to it to tell the Template object where it can be found.
 *  This File class is one of the available Source objects that can be used
 *  for templates that are stored on the local filesystem.
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
class File : public Source
{
private:
    /**
     *  Name of the file
     *  @var    std::string
     */
    std::string _name;
    
public:
    /**
     *  Constructor
     *  @param  name        Name of the file
     */
    File(const char *name) : _name(name) {}
    
    /**
     *  Destructor
     */
    virtual ~File() {}
    
    
};
    
/**
 *  End namespace
 */
}
