/**
 *  Shared.h
 *
 *  Header file that describes the data structures that are needed to access
 *  a template when it has been turned into a shared library.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include <stddef.h>

/**
 *  Structure holding the callbacks
 *
 *  A template-compiled-into-a-shared-library has one public function: 
 *  show_template(). This function needs to be passed a pointer to a structure
 *  holding various callbacks. That is this structure
 */
typedef struct smarttpl_callbacks
{
    /**
     *  Pointer to a function to write data
     *
     *  This function will be called for all data in the template
     *
     *  The function gets two arguments: a pointer to a buffer to write,
     *  and the size of that buffer
     */
    void (*write)(const char *data, size_t size);
    
    /**
     *  Pointer to a function to retrieve a variable by name.
     *
     *  This function gets the variable name + size of the name, and should
     *  return a pointer to a variable. This pointer will be passed to other
     *  callbacks when the variable is further accessed.
     *
     *  It is _not_ allowed to return NULL. Even when the variable does not
     *  exist, a valid pointer should be returned.
     */
    void *(*variable)(const char *name, size_t size);
    
    /**
     *  Pointer to a function to output a variable
     * 
     *  This function gets a variable address, and should output the value
     *  of the variable.
     */
    void (*output)(void *variable);
    
    /**
     *  Get a member variable.
     *
     *  If a variable is indexed as if it is an associative array or object,
     *  using constructs like $var["x"] or $var.x, this method gets called.
     *
     *  It receives three parameters: a pointer to the variable, and the name
     *  and size of the name. The name is a null terminated string.
     *
     *  A new variable address should be returned.
     */
    void *(*member)(void *variable, const char *name, size_t size);
    
    /**
     *  Cast a variable to a numeric value
     *
     *  This function is called when a variable is used in a numeric context.
     *  The callback gets one parameter, the pointer to the variable to cast,
     *  and should return an integer value.
     */
    int (*to_numeric)(void *variable);
    
    /**
     *  Cast a variable to a string value
     *
     *  This function is called when a variable is used in a string context.
     *  The callback gets one parameter, the pointer to the variable to cast,
     *  and should return a pointer to a null terminated string.
     */
    const char *(*to_string)(void *variable);
    
    /**
     *  Retrieve the length of the string representation of a variable
     * 
     *  This function should do the same as strlen(to_string(variable)), but
     *  could be more efficient if the string length is already known.
     */
    size_t (*size)(void *variable);
    
    
} smarttpl_callbacks_t;

