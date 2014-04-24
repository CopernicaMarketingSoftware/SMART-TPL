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
    int (*member_iter)(void *userdata, void *variable, const char *key, size_t size);
    void *(*variable)(void *userdata, const char *name, size_t size);
    const char *(*to_string)(void *userdata, void *variable);
    size_t (*to_numeric)(void *userdata, void *variable);
    size_t (*to_boolean)(void *userdata, void *variable);
    size_t (*size)(void *userdata, void *variable);
    void *(*modifier)(void *userdata, const char *name, size_t size);
    void *(*modify_variable)(void *userdata, void *modifier, void *variable);
    void *(*modify_numeric)(void *userdata, void *modifier, long value);
    void *(*modify_string)(void *userdata, void *modifier, const char *data, size_t size);
};

