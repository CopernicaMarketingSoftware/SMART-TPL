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

        // Keep looping as long as we are not done
        bool done = false;
        int res = 0;
        while (done == false)
        {
            // If this write goes correctly we are done
            res = BIO_write(base64, data, len);
            if (res <= 0)
            {
                // Should we retry? Just jump back to the start of the while loop then
                if (BIO_should_retry(base64)) continue;
                else
                {
                    // Free all the BIOs and return the original input
                    BIO_free_all(base64);
                    return input;
                }
            }
            else done = true;
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