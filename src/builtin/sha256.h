/**
 *  Sha256.h
 *
 *  Built-in "|sha256" modifier
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
class Sha256Modifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~Sha256Modifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // initialize our output
        unsigned char digest[SHA256_DIGEST_LENGTH];

        std::string str(input.toString());
        // Call the openssl md5 method
        SHA256((unsigned char*) str.c_str(), str.size(), (unsigned char*) &digest);

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