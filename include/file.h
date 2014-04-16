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
    const std::string _name;
    
public:
    /**
     *  Constructor
     *  @param  name               Name of the file
     *  @throws std::runtime_error If the file doesn't seem to exist
     */
    File(const std::string& name) : File(name.c_str()) {};
    File(const char *name) : _name(name) {
        std::ifstream file(_name);
        if (!file)
            throw std::runtime_error("File doesn't exist");
        file.seekg(0, std::ios_base::end);
        size_t len = file.tellg();
        file.seekg(0, std::ios_base::beg);
        file.clear();
        char buf[len];
        file.read(buf, len);
        _buffer.append(buf, len);
    }
    
    /**
     *  Destructor
     */
    virtual ~File() {}

    /**
     *  Returns the filename of the file that was read into memory.
     *
     *  @return std::string
     */
    const std::string GetFilename() const { return _name; };
};
    
/**
 *  End namespace
 */
}
