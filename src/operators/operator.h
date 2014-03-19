/**
 *  Operator.h
 *
 *  Base class for all operators
 *
 *  @author Emiel Bruijntnjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class Operator : public Expression
{
protected:
    /**
     *  This is a base class, not allowed to construct it directly,
     *  hence the protected constructor
     */
    Operator() {}

public:
    /**
     *  Destructor
     */
    virtual ~Operator() {}

};

/**
 *  End namespace
 */
}


