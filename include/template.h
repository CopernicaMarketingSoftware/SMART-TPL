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
 */
class Executor;

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
    Executor *_executor = nullptr;
    
public:
    /**
     *  Constructor
     *  @param  source        Source of your template
     */
    Template(const Source &source);

    /**
     *  Deleted copy constructor
     *  @param  that
     */
    Template(const Template &that) = delete;

    /**
     *  Destructor
     */
    virtual ~Template();

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
     *  @param  data        Data source
     *  @return std::string
     */
    std::string process(const Data &data) const;
    
    /**
     *  Process the template, without any input
     * 
     *  @return std::string
     */
    std::string process() const
    {
        // start with an empty data object
        return process(Data());
    }
};

/**
 *  End namespace
 */
}

