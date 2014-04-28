/**
 *  Callbacks.h
 *
 *  When a *.tpl template is compiled into a *.so template, it will create
 *  C code that does calls to the following functions.
 *
 *  As a library-user, you do not have to use or call these functions.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <stddef.h>

/**
 *  Structure with all the callbacks
 */
struct smart_tpl_callbacks {
    void (*write)(void *userdata, const char *data, size_t size);
    void (*output)(void *userdata, void *variable);
    void *(*member)(void *userdata, void *variable, const char *name, size_t size);
    void *(*member_at)(void *userdata, void *variable, long position);
    int (*member_iter)(void *userdata, void *variable, const char *key, size_t size, const char *keyvar, size_t keyvar_size);
    void *(*variable)(void *userdata, const char *name, size_t size);
    const char *(*to_string)(void *userdata, void *variable);
    size_t (*to_numeric)(void *userdata, void *variable);
    int (*to_boolean)(void *userdata, void *variable);
    size_t (*size)(void *userdata, void *variable);
    void *(*modifier)(void *userdata, const char *name, size_t size);
    void *(*modify_variable)(void *userdata, void *modifier, void *variable);
    void *(*modify_numeric)(void *userdata, void *modifier, long value);
    void *(*modify_string)(void *userdata, void *modifier, const char *data, size_t size);
    void (*assign_numeric)(void *userdata, long value, const char *key, size_t keysize);
    void (*assign_boolean)(void *userdata, int boolean, const char *key, size_t keysize);
    void (*assign_string)(void *userdata, const char *buf, size_t buf_size, const char *key, size_t keysize);
    void (*assign)(void *userdata, void *variable, const char *key, size_t keysize);
    int (*strcmp)(void *userdata, const char *a, size_t a_len, const char *b, size_t b_len);
};