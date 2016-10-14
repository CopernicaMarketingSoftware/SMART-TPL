/**
 *  Openssl.h
 *
 *  Simple helper class to dynamically load the openssl library.
 *
 *  @author Toon Schoenmakers<toon.schoenmakers@copernica.com>
 *  @copyright 2015 Copernica BV
 */

/**
 *  Include guard
 */
#pragma once

/**
 *  Dependencies
 */
#include "library.h"
#include "function.h"
#include <openssl/bio.h>

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class OpenSSL
{
private:
    /**
     *  The actual underlying library
     *  @var  Dynamic::Library
     */
    Dynamic::Library _lib;

    /**
     *  Constructor
     */
    OpenSSL() : _lib({
            // the following files are normally symlinks to the very latest
            // version, and that we try to use first
            "libssl.so",
            "libssl.so.1",
            "libssl.so.1.0",
            "libssl.so.1.0.0b",
            "libssl.so.1.0.0a",
            "libssl.so.1.0.0",

            // no symlink versions found, go look for a 1.0.2 version
            "libssl.so.1.0.2j",
            "libssl.so.1.0.2i",
            "libssl.so.1.0.2h",
            "libssl.so.1.0.2g",
            "libssl.so.1.0.2f",
            "libssl.so.1.0.2e",
            "libssl.so.1.0.2d",
            "libssl.so.1.0.2c",
            "libssl.so.1.0.2b",
            "libssl.so.1.0.2a",
            "libssl.so.1.0.2",

            // go look for a 1.0.1 version
            "libssl.so.1.0.1v",
            "libssl.so.1.0.1u",
            "libssl.so.1.0.1t",
            "libssl.so.1.0.1s",
            "libssl.so.1.0.1r",
            "libssl.so.1.0.1q",
            "libssl.so.1.0.1p",
            "libssl.so.1.0.1o",
            "libssl.so.1.0.1n",
            "libssl.so.1.0.1m",
            "libssl.so.1.0.1l",
            "libssl.so.1.0.1k",
            "libssl.so.1.0.1j",
            "libssl.so.1.0.1i",
            "libssl.so.1.0.1h",
            "libssl.so.1.0.1g",
            "libssl.so.1.0.1f",
            "libssl.so.1.0.1e",
            "libssl.so.1.0.1",

            // no working version found
            nullptr

        }),
        MD5(_lib, "MD5"),
        SHA1(_lib, "SHA1"),
        SHA256(_lib, "SHA256"),
        SHA512(_lib, "SHA512"),
        BIO_new(_lib, "BIO_new"),
        BIO_new_mem_buf(_lib, "BIO_new_mem_buf"),
        BIO_f_base64(_lib, "BIO_f_base64"),
        BIO_s_mem(_lib, "BIO_s_mem"),
        BIO_set_flags(_lib, "BIO_set_flags"),
        BIO_push(_lib, "BIO_push"),
        BIO_write(_lib, "BIO_write"),
        BIO_read(_lib, "BIO_read"),
        BIO_test_flags(_lib, "BIO_test_flags"),
        BIO_free_all(_lib, "BIO_free_all"),
        BIO_ctrl(_lib, "BIO_ctrl")
    {
    };

public:

    /**
     *  Destructor
     */
    virtual ~OpenSSL() {};

    /**
     *  Retrieve the singleton
     */
    static OpenSSL &instance()
    {
        // the single instance
        static OpenSSL ssl;

        // return reference
        return ssl;
    };

    /**
     *  Are we valid or not?
     */
    bool valid() const { return _lib.valid(); };
    operator bool() const { return valid(); }

    // MD5
    const Dynamic::Function<unsigned char*(const unsigned char *d, size_t n, unsigned char *md)> MD5;

    // SHA1, SHA256, SHA512
    const Dynamic::Function<unsigned char*(const unsigned char *d, size_t n, unsigned char *md)> SHA1;
    const Dynamic::Function<unsigned char*(const unsigned char *d, size_t n, unsigned char *md)> SHA256;
    const Dynamic::Function<unsigned char*(const unsigned char *d, size_t n, unsigned char *md)> SHA512;

    // BIO related methods
    const Dynamic::Function<BIO*(BIO_METHOD *type)> BIO_new;
    const Dynamic::Function<BIO*(void *buf, int len)> BIO_new_mem_buf;
    const Dynamic::Function<BIO_METHOD*()> BIO_f_base64;
    const Dynamic::Function<BIO_METHOD*()> BIO_s_mem;
    const Dynamic::Function<void(BIO *bio, int flags)> BIO_set_flags;
    const Dynamic::Function<BIO*(BIO *bio, BIO *append)> BIO_push;
    const Dynamic::Function<int(BIO *bio, const void *buf, int len)> BIO_write;
    const Dynamic::Function<int(BIO *bio, void *buf, int len)> BIO_read;
    const Dynamic::Function<int(BIO *bio, int flags)> BIO_test_flags;
    const Dynamic::Function<void(BIO *bio)> BIO_free_all;
    const Dynamic::Function<int(BIO *bio, int cmd, long larg, void *parg)> BIO_ctrl;
};

/**
 *  End namespace
 */
}}
