/**
 *  Md5.h
 *
 *  Built-in "|md5" modifier
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include "../dynamic/openssl.h"

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class Md5Modifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~Md5Modifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // in case we don't have a valid openssl library we are simply returning the original input
        if (!OpenSSL::instance()) throw NoModification();

        // initialize our output
        unsigned char digest[MD5_DIGEST_LENGTH];

        std::string str(input.toString());
        // Call the openssl md5 method
        OpenSSL::instance().MD5((unsigned char*) str.c_str(), str.size(), (unsigned char*) &digest);

        std::ostringstream stream;
        stream << std::setfill('0') << std::hex;

        for (size_t i = 0; i < sizeof(digest); ++i) stream << std::setw(2) << ((unsigned int) digest[i]);

        // Return our stream as a string
        return stream.str();
    }
};

/**
 *  End namespace
 */
}}