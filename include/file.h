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
        // if file failed to open it probably doesn't exist so we throw
        if (!file) throw std::runtime_error("File doesn't exist");

        // read the file into _buffer using istreambuf_iterators, this wil automatically buffer
        _buffer= std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
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
    const std::string filename() const { return _name; };
};

/**
 *  End namespace
 */
}
