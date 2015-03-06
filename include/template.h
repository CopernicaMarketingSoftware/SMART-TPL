/**
 *  Template.h
 *
 *  This class represents a template file. A template can be constructed
 *  with a filename, or with a binary buffer.
 *  @see SmartTpl::File
 *  @see SmartTpl::Buffer
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Forward declarations
 *  @todo It is probably not a good idea to do a forward declaration to an interal class here!
 */
namespace Internal {
    class Executor;
}

/**
 *  Class definition
 */
class Template
{
private:
    /**
     *  The template 'executor'
     *
     *  This is a different object depending whether you constructed the template
     *  with a shared object (*.so file) or with a template source file (*.tpl)
     *
     *  @var    Executor
     */
    Internal::Executor *_executor = nullptr;

    /**
     *  Contains the human readable name of the encoding that is used natively
     *
     *  @var std::string
     */
    std::string _encoding = "raw";


public:
    /**
     *  Constructor
     *  @param  source             Source of your template
     *
     *  @throws CompileError       In case JIT compilation failed, the what() will describe what and where it went wrong
     */
    Template(const Source &source);

    /**
     *  Deleted copy constructor
     *  @param  that
     */
    Template(const Template &that) = delete;

    /**
     *  Move constructor
     *  @param  that
     */
    Template(Template &&that) : 
        _executor(that._executor),
        _encoding(std::move(that._encoding))
    {
        // reset other object
        that._executor = nullptr;
    }

    /**
     *  Destructor
     */
    virtual ~Template();

    /**
     *  Deleted assign operator
     *  @param  that
     */
    Template& operator=(const Template &that) = delete;

    /**
     *  Get the template representation in C that can be compiled into a shared
     *  object. This method only works for templates that were not already a
     *  shared library.
     *
     *  @return std::string
     */
    std::string compile() const;

    /**
     *  Process the template, given a certain data source
     *
     *  The data object that needs to be passed to this method is an object
     *  that contains the values of all variables that can be user inside the
     *  template.
     *
     *  @param  data         Data source
     *  @param  outencoding  The encoding that should be used for the output
     *  @return std::string
     */
    std::string process(const Data &data, const std::string &outencoding) const;

    /**
     *  Process the template, without any input, but a custom encoding
     *
     *  @param  outencoding  The encoding that should be used for the output
     *  @return std::string
     */
    std::string process(const std::string &outencoding) const
    {
        // start with an empty data object
        return process(Data(), outencoding);
    }

    /**
     *  Process the template, given a certain data source
     *  @param  data        Data source
     *  @return std::string
     */
    std::string process(const Data &data) const
    {
        return process(data, _encoding);
    }

    /**
     *  Process the template without any input
     *
     *  @return std::string
     */
    std::string process() const
    {
        return process(Data(), _encoding);
    }

    /**
     *  Used to retrieve what encoding this template is in, natively
     *  @return std::string
     */
    const std::string &encoding() const { return _encoding; };

};

/**
 *  Operator to quickly print the current template onto an output stream
 *  @param      os      The output stream to print to
 *  @param      tpl     The template to actually process, you can't process it with any data here
 */
inline std::ostream &operator<<(std::ostream &stream, const Template &tpl)
{
    return stream << tpl.process();
}

/**
 *  End namespace
 */
}
