/**
 *  Null.h
 *
 *  A null en/decoder, which doesn't modify the input at all
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class NullEscaper : public Escaper
{
public:
    /**
     *  Constructor
     */
    NullEscaper() : Escaper("null") {};
    /**
     *  Destructor
     */
    virtual ~NullEscaper() {}

    /**
     *  Encode the given input
     *  It is probably a good idea to directly modify the input instead of making
     *  a copy and modifying that.
     *  @param input
     */
    std::string &encode(std::string &input) const override
    {
        return input;
    }

    /**
     *  Decode the given input
     *  It is probably a good idea to directly modify the input instead of making
     *  a copy and modifying that.
     *  @param input
     */
    std::string &decode(std::string &input) const override
    {
        return input;
    }

};

/**
 *  End namespace
 */
}}