/**
 *  Executor.h
 *
 *  Base class that is used for executing templates. This executor is
 *  implemented by ByteCode (which compiles a template on the fly) and by
 *  SharedLibrary (which loads a shared library)
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
class Executor
{
protected:
    /**
     *  Protected constructor
     */
    Executor() {}

public:
    /**
     *  Destructor
     */
    virtual ~Executor() {}

    /**
     *  Execute the template given a certain data source
     *  @param  data
     */
    virtual void process(Handler &handler) = 0;

    /**
     *  Compile the template into C code
     *  @return std::string
     */
    virtual std::string compile() = 0;

    /**
     *  Retrieve what encoding the 'template' has natively
     *  @return std::string
     */
    virtual std::string encoding() = 0;

    /**
     *  Does the template use personalisation data?
     *
     *  @return Whether the template uses any personalisation data
     */
    virtual bool personalized() const
    {
        // we assume it does
        return true;
    }

};

/**
 *  End namespace
 */
}}
