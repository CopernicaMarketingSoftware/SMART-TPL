/**
 *  ArrayAccess.h
 *
 *  Class that is used to represent the [] operator to get access to an array
 *  member
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
class ArrayAccess : public Variable
{
protected:
    /**
     *  The underlying variable
     *  @var    Variable
     */
    std::unique_ptr<Variable> _var;

protected:
    /**
     *  Constructor
     *  @param  variable
     */
    ArrayAccess(Variable *variable) :
        _var(variable) {}

public:
    /**
     *  Destructor
     */
    virtual ~ArrayAccess() {}
};

/**
 *  End namespace
 */
}

