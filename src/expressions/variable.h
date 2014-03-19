/**
 *  Variable.h
 *
 *  Expression that contains one variable.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class Variable : public Expression
{
protected:
    /**
     *  Constructor
     */
    Variable() {}

public:    
    /**
     *  Destructor
     */
    virtual ~Variable() {}
};

/**
 *  End of namespace
 */
}

