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

    /**
     *  Is this a shared library?
     *  @var    bool
     */
    bool _library = false;

    /**
     *  The full source code
     *  @var    std::string
     */
    std::string _source;

    /**
     *  Internal helper function to initialize
     */
    void initialize()
    {
        // find the file extension
        const char *extension = strrchr(name(), '.');

        // if the file extension is .so, we assume that it is a shared library
        _library = extension && strcasecmp(extension, ".so") == 0;

        // and if this is a shared library, we're not going to read the contents
        // because it most likely is binary code that we do not understand anyway
        if (_library) return;

        // we're going to read the entire file into a buffer, use a stream object
        std::ifstream file(_name);

        // skip if file is not valid
        if (!file) throw std::runtime_error("IO failure");

        // read the file into _buffer using istreambuf_iterators, this wil automatically buffer
        _source = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }

public:
    /**
     *  Constructor
     *  @param  name               Name of the file
     *  @throws std::runtime_error If the file doesn't seem to exist or some other IO operation failed
     */
    File(const char *name) : _name(name)
    {
        // initialize the object
        initialize();
    }

    /**
     *  Constructor
     *  @param  name               Name of the file
     *  @throws std::runtime_error If the file doesn't seem to exist or some other IO operation failed
     */
    File(const std::string &name) : _name(name)
    {
        // initialize the object
        initialize();
    }

    /**
     *  Destructor
     */
    virtual ~File() {}

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
        // return the filename
        return _name.c_str();
    }

    /**
     *  Is this a shared library?
     *
     *  When the source represents a shared library, it means that that it could
     *  be opened by a call to dlopen(), and it is stored as a .so file on the
     *  system. The name() method should return the path to the shared library.
     *
     *  @return bool
     */
    bool library() const override
    {
        // this is stored in a member variable
        return _library;
    }

    /**
     *  Returns a const char* to the start of the buffer, use size() to get the length
     *  of this buffer.
     *
     *  @return const char*
     */
    const char *data() const override
    {
        // already stored in a member
        return _source.c_str();
    }

    /**
     *  Returns the size of the buffer.
     *
     *  @return size_t
     */
    size_t size() const override
    {
        // check the source object
        return _source.size();
    }

};

/**
 *  End namespace
 */
}
