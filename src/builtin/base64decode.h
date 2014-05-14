/**
 *  Base64decode.h
 *
 *  Built-in "|base64_decode" modifier
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
class Base64DecodeModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~Base64DecodeModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual Variant modify(const Variant &input, const SmartTpl::Parameters &params) override
    {
        // This is mostly using the openssl library, so it is kind of dirty code :/
        // initialize our base64 encoder
        BIO *base64 = BIO_new(BIO_f_base64());
        BIO_set_flags(base64, BIO_FLAGS_BASE64_NO_NL);

        // Save the C string info of our input
        const char *data = input.toString();
        size_t len = input.size();

        // Create a memory BIO
        BIO *mem = BIO_new_mem_buf((void*) data, len);

        // Link the two BIOs together
        BIO_push(base64, mem);

        // initialize our output
        std::string output;

        // Read chunks of data from the base64 BIO into our output string
        // @todo Some form of error handling?
        char buf[1024 * 8];
        int ret = 0;
        do {
            ret = BIO_read(base64, buf, sizeof(buf));
            if (ret > 0) output.append(buf, ret);
        } while (ret > 0);

        // Now free the BIO
        BIO_free_all(base64);

        // Return our output
        return output;
    }
};

/**
 *  End namespace
 */
}}