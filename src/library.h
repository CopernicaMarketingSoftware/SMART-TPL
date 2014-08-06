/**
 *  Library.h
 *
 *  Implementation of a Smarty template based on a *.so file
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class Library : public Executor
{
private:
    /**
     *  Handle to the library
     *  @var    void*
     */
    void *_handle = nullptr;

    /**
     *  Signature of the ShowTemplate function
     */
    using ShowTemplate = void(struct smart_tpl_callbacks *callbacks, const void *userdata);

    /**
     *  The 'show_template' function
     *  @var    function
     */
    ShowTemplate *_function;

    /**
     *  The 'mode' function
     */
    const char *_mode;

public:
    /**
     *  Constructor
     *  @param  name        Filename of the *.so file
     */
    Library(const std::string &filename)
    {
        // load the library
        _handle = dlopen(filename.c_str(), RTLD_LAZY | RTLD_LOCAL);

        // must be open
        if (!_handle) throw std::runtime_error(dlerror());

        // find the show_template symbol
        _function = (ShowTemplate *) dlsym(_handle, "show_template");

        // function should exist
        if (!_function) throw std::runtime_error(dlerror());

        // find the mode symbol
        const char **mode_ptr = (const char **) dlsym(_handle, "mode");

        // Pointer to mode should exist
        if (!mode_ptr) throw std::runtime_error(dlerror());

        // Turn the const char ** into const char *
        _mode = *mode_ptr;
    }

    /**
     *  Destructor
     */
    virtual ~Library()
    {
        // close the library
        if (_handle) dlclose(_handle);
    }

    /**
     *  Execute the template given a certain data source
     *  @param  data
     */
    void process(Handler &handler) override;

    /**
     *  Compile the template into C code
     *  @return std::string
     */
    std::string compile() override
    {
        // a shared library can not be turned into C code, because it
        // already has been compiled to native code
        return "";
    }

    /**
     *  Retrieve what encoding the 'template' has natively
     *  @return std::string
     */
    std::string encoding() override
    {
        return _mode;
    }
};

/**
 *  End namespace
 */
}}