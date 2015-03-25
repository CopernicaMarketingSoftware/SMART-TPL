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
     *  Constructor, in case the openssl library failed to load we simply are
     *               giving our base constructor a nullptr so it doesn't register us
     */
    Base64Escaper() : Escaper(OpenSSL::instance() ? "base64" : nullptr) {};

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
        // retrieve the openssl library
        auto &lib = OpenSSL::instance();

        // This is mostly using the openssl library, so it is kind of dirty code :/
        // initialize our base64 encoder
        BIO *base64 = lib.BIO_new(lib.BIO_f_base64());
        lib.BIO_set_flags(base64, BIO_FLAGS_BASE64_NO_NL);

        // Create a memory BIO
        BIO *mem = lib.BIO_new(lib.BIO_s_mem());

        // Link the two BIOs together
        lib.BIO_push(base64, mem);

        // Save the C string info of our input
        const char *data = input.data();
        size_t len = input.size();

        // Keep looping as long as we still have bytes to write
        size_t wrote = 0;
        for (size_t pos = 0; pos < len; pos += wrote)
        {
            if ((wrote = lib.BIO_write(base64, data + pos, len - pos)) <= 0)
            {
                // If the BIO_write method fails let's check if we should retry or not
                // we're using BIO_test_flags here as BIO_should_retry is a macro
                // #define BIO_should_retry(a)      BIO_test_flags(a, BIO_FLAGS_SHOULD_RETRY)
                if (lib.BIO_test_flags(base64, BIO_FLAGS_SHOULD_RETRY))
                {
                    wrote = 0;
                    continue;
                }
                else
                {
                    // We shouldn't retry, cleanup and return original value
                    lib.BIO_free_all(base64);
                    return input;
                }
            }
        }

        // Flush the base64 BIO to make sure everything is written, this is a BIO_ctrl
        // call as BIO_flush is a macro.
        // #define BIO_flush(b)     (int)BIO_ctrl(b,BIO_CTRL_FLUSH,0,NULL)
        lib.BIO_ctrl(base64, BIO_CTRL_FLUSH, 0, nullptr);

        // Get the char pointer and length of the mem BIO, we're using yet another
        // BIO_ctrl call here as BIO_get_mem_data is also a macro.
        // #define BIO_get_mem_data(b,pp)   BIO_ctrl(b,BIO_CTRL_INFO,0,(char *)pp)
        char *output;
        size_t outputlen = lib.BIO_ctrl(mem, BIO_CTRL_INFO, 0, (char*) &output);

        // Clear the input and fill it with our new data
        input.clear();
        input.append(output, outputlen);

        // Now free the BIO, must be in this order as this will zero out it's memory
        lib.BIO_free_all(base64);

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
        // retrieve the openssl library
        auto &lib = OpenSSL::instance();

        // This is mostly using the openssl library, so it is kind of dirty code :/
        // initialize our base64 encoder
        BIO *base64 = lib.BIO_new(lib.BIO_f_base64());
        lib.BIO_set_flags(base64, BIO_FLAGS_BASE64_NO_NL);

        // Create a copy of our input string, as we have to output in this string as well
        std::string work(input);

        // Save the C string info of our input
        const char *data = work.data();
        size_t len = work.size();

        // Create a memory BIO
        BIO *mem = lib.BIO_new_mem_buf((void*) data, len);

        // Link the two BIOs together
        lib.BIO_push(base64, mem);

        // Clear our input string, which is also our output
        input.clear();

        // Read chunks of data from the base64 BIO into our output string
        char buf[1024 * 8];
        int ret = 0;
        do {
            ret = lib.BIO_read(base64, buf, sizeof(buf));
            if (ret == 0) break; // end of data stream
            else if (ret > 0) input.append(buf, ret);
            else if (ret < 0)
            {
                // we're using BIO_test_flags here as BIO_should_retry is a macro
                // #define BIO_should_retry(a)      BIO_test_flags(a, BIO_FLAGS_SHOULD_RETRY)
                if (lib.BIO_test_flags(base64, BIO_FLAGS_SHOULD_RETRY)) continue; // If we should retry just pop back to the start of the loop
                else
                {
                    // We shouldn't retry, cleanup and return original value
                    lib.BIO_free_all(base64);
                    return input;
                }
            }
        } while (true);

        // Now free the BIO
        lib.BIO_free_all(base64);

        // Return our output buffer
        return input;
    }

};

/**
 *  End namespace
 */
}}