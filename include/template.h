/**
 *  Template.h
 * 
 *  This class represents a template file. A template can be constructed
 *  with a filename, or with a binary buffer. 
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
    Executor *_executor;
    
public:
    /**
     *  Constructor
     *  @param  filename        Name of the template to load
     */
    Template(const char *filename);

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
};

/**
 *  End namespace
 */
}

