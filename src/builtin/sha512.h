/**
 *  Sha512.h
 *
 *  Built-in "|sha512" modifier
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
class Sha512Modifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~Sha512Modifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // initialize our output
        unsigned char digest[SHA512_DIGEST_LENGTH];

        // Call the openssl md5 method
        SHA512((unsigned char*) input.toString(), input.size(), (unsigned char*) &digest);

        std::ostringstream stream;
        stream << std::setfill('0') << std::hex;

        for (int i = 0; i < sizeof(digest); ++i) stream << std::setw(2) << ((unsigned int) digest[i]);

        // Return our stream as a string
        return stream.str();
    }
};

/**
 *  End namespace
 */
}}