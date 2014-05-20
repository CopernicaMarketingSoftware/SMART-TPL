/**
 *  Base64encode.h
 *
 *  Built-in "|base64_encode" modifier
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
class Base64EncodeModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~Base64EncodeModifier() {};

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

        // Create a memory BIO
        BIO *mem = BIO_new(BIO_s_mem());

        // Link the two BIOs together
        BIO_push(base64, mem);

        // Save the C string info of our input
        const char *data = input.toString();
        size_t len = input.size();

        // Keep looping as long as we still have bytes to write
        size_t wrote = 0;
        for (size_t pos = 0; pos < len; pos += wrote)
        {
            if ((wrote = BIO_write(base64, data + pos, len - pos)) <= 0)
            {
                // If the BIO_write method fails let's check if we should retry or not
                if (BIO_should_retry(base64))
                {
                    wrote = 0;
                    continue;
                }
                else
                {
                    // We shouldn't retry, cleanup and return original value
                    BIO_free_all(base64);
                    return input;
                }
            }
        }

        // Flush the base64 BIO to make sure everything is written
        BIO_flush(base64);

        // Get the char pointer and length of the mem BIO
        char *output;
        size_t outputlen = BIO_get_mem_data(mem, &output);

        // Copy the just retrieved output into a std::string
        std::string outputstr(output, outputlen);

        // Now free the BIO, must be in this order as this will zero out it's memory
        BIO_free_all(base64);

        // Return the just copied string
        return outputstr;
    }
};

/**
 *  End namespace
 */
}}