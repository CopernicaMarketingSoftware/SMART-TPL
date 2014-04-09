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

/**
 *  Structure with all the callbacks
 */
struct smart_tpl_callbacks {
    void (*write)(void *userdata, const char *data, int size);
    void (*output)(void *userdata, void *variable);
    void *(*member)(void *userdata, void *variable, const char *name, int size);
    void *(*variable)(void *userdata, const char *name, int size);
    const char *(*to_string)(void *userdata, void *variable);
    int (*to_numeric)(void *userdata, void *variable);
    int (*size)(void *userdata, void *variable);
};

