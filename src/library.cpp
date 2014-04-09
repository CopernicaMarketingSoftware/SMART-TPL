/**
 *  Library.cpp
 * 
 *  Implementation file for the Library class
 * 
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include "includes.h"

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Structure with all the callbacks
 *  @var    smart_tpl_callbacks
 */
static struct smart_tpl_callbacks callbacks = {
    .write      =   smart_tpl_write,
    .output     =   smart_tpl_output,
    .member     =   smart_tpl_member,
    .variable   =   smart_tpl_variable,
    .to_string  =   smart_tpl_to_string,
    .to_numeric =   smart_tpl_to_numeric,
    .size       =   smart_tpl_size
};
    
/**
 *  Execute the template given a certain data source
 *  @param  data
 */
void Library::process(Handler &handler)
{
    // call the function
    _function(&callbacks, &handler);
}

/**
 *  End namespace
 */
}
