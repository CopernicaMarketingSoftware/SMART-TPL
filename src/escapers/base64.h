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
class Base64Escaper : public Escaper
{
public:
    /**
     *  Constructor
     */
    Base64Escaper() : Escaper("base64") {};
    /**
     *  Destructor
     */
    virtual ~Base64Escaper() {}

    /**
     *  Encode the given input
     *  It is probably a good idea to directly modify the input instead of making
     *  a copy and modifying that.
     *  @param input
     */
    std::string &encode(std::string &input) const override
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
        const char *data = input.data();
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
        // We're casting the output to void here so the compiler will shut up about it
        (void) BIO_flush(base64);

        // Get the char pointer and length of the mem BIO
        char *output;
        size_t outputlen = BIO_get_mem_data(mem, &output);

        // Clear the input and fill it with our new data
        input.clear();
        input.append(output, outputlen);

        // Now free the BIO, must be in this order as this will zero out it's memory
        BIO_free_all(base64);

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
        // This is mostly using the openssl library, so it is kind of dirty code :/
        // initialize our base64 encoder
        BIO *base64 = BIO_new(BIO_f_base64());
        BIO_set_flags(base64, BIO_FLAGS_BASE64_NO_NL);

        // Create a copy of our input string, as we have to output in this string as well
        std::string work(input);

        // Save the C string info of our input
        const char *data = work.data();
        size_t len = work.size();

        // Create a memory BIO
        BIO *mem = BIO_new_mem_buf((void*) data, len);

        // Link the two BIOs together
        BIO_push(base64, mem);

        // Clear our input string, which is also our output
        input.clear();

        // Read chunks of data from the base64 BIO into our output string
        char buf[1024 * 8];
        int ret = 0;
        do {
            ret = BIO_read(base64, buf, sizeof(buf));
            if (ret == 0) break; // end of data stream
            else if (ret > 0) input.append(buf, ret);
            else if (ret < 0)
            {
                if (BIO_should_retry(base64)) continue; // If we should retry just pop back to the start of the loop
                else
                {
                    // We shouldn't retry, cleanup and return original value
                    BIO_free_all(base64);
                    return input;
                }
            }
        } while (true);

        // Now free the BIO
        BIO_free_all(base64);

        // Return our output buffer
        return input;
    }

};

/**
 *  End namespace
 */
}}