/**
 *  ErrorLabel.h
 *
 *  A grouped label and description for an error
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2018 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class ErrorLabel
{
private:
    /**
     *  Error description
     *  @var    const char *
     */
    const char *_message;

    /**
     *  The label where we can jump to in case of an error
     *  @var    jit_label
     */
    jit_label _label;

public:
    /**
     *  Constructor
     *  @param  function
     *  @param  description
     */
    ErrorLabel(jit_function &function, const char *message) : 
        _message(message),
        _label(function.new_label()) {}
        
    /**
     *  Forbidden copying
     *  @param  that
     */
    ErrorLabel(const ErrorLabel &that) = delete;
    
    /**
     *  Destructor
     */
    virtual ~ErrorLabel() = default;
    
    /**
     *  Get the error message
     *  @return const char *
     */
    const char *message() const { return _message; }
    
    /**
     *  Get the label
     *  @return jib_label
     */
    jit_label &label() { return _label; }
};

/**
 *  End of namespace
 */
}}
