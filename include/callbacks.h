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
    void        (*write)                (void *userdata, const char *data, size_t size);
    void        (*output)               (void *userdata, void *variable, int escape);
    void       *(*member)               (void *userdata, void *variable, const char *name, size_t size);
    void       *(*member_at)            (void *userdata, void *variable, long position);
    void       *(*create_iterator)      (void *userdata, void *variable);
    void        (*delete_iterator)      (void *userdata, void *iterator);
    int         (*valid_iterator)       (void *userdata, void *iterator);
    void       *(*iterator_key)         (void *userdata, void *iterator);
    void       *(*iterator_value)       (void *userdata, void *iterator);
    void        (*iterator_next)        (void *userdata, void *iterator);
    void       *(*variable)             (void *userdata, const char *name, size_t size);
    const char *(*to_string)            (void *userdata, void *variable);
    int         (*to_numeric)           (void *userdata, void *variable);
    int         (*to_boolean)           (void *userdata, void *variable);
    size_t      (*size)                 (void *userdata, void *variable);
    void       *(*modifier)             (void *userdata, const char *name, size_t size);
    void       *(*modify_variable)      (void *userdata, void *variable, void *modifier, void *parameters);
    void        (*assign_numeric)       (void *userdata, const char *key, size_t keysize, long value);
    void        (*assign_boolean)       (void *userdata, const char *key, size_t keysize, int boolean);
    void        (*assign_string)        (void *userdata, const char *key, size_t keysize, const char *buf, size_t buf_size);
    void        (*assign)               (void *userdata, const char *key, size_t keysize, void *variable);
    int         (*strcmp)               (void *userdata, const char *a, size_t a_len, const char *b, size_t b_len);
    void       *(*create_params)        (void *userdata);
    void        (*delete_params)        (void *userdata, void *parameters);
    void        (*params_append_numeric)(void *userdata, void *parameters, long value);
    void        (*params_append_string) (void *userdata, void *parameters, const char *buf, size_t len);
    void        (*params_append_boolean)(void *userdata, void *parameters, int boolean);
};
