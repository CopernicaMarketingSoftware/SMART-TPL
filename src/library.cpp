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
namespace SmartTpl { namespace Internal {

/**
 *  Structure with all the callbacks
 *  @var    smart_tpl_callbacks
 */
static struct smart_tpl_callbacks callbacks = {
    .write                 = smart_tpl_write,
    .output                = smart_tpl_output,
    .output_numeric        = smart_tpl_output_numeric,
    .member                = smart_tpl_member,
    .member_at             = smart_tpl_member_at,
    .create_iterator       = smart_tpl_create_iterator,
    .delete_iterator       = smart_tpl_delete_iterator,
    .valid_iterator        = smart_tpl_valid_iterator,
    .iterator_key          = smart_tpl_iterator_key,
    .iterator_value        = smart_tpl_iterator_value,
    .iterator_next         = smart_tpl_iterator_next,
    .variable              = smart_tpl_variable,
    .to_string             = smart_tpl_to_string,
    .to_numeric            = smart_tpl_to_numeric,
    .to_double             = smart_tpl_to_double,
    .to_boolean            = smart_tpl_to_boolean,
    .size                  = smart_tpl_size,
    .modifier              = smart_tpl_modifier,
    .modify_variable       = smart_tpl_modify_variable,
    .assign_numeric        = smart_tpl_assign_numeric,
    .assign_double         = smart_tpl_assign_double,
    .assign_boolean        = smart_tpl_assign_boolean,
    .assign_string         = smart_tpl_assign_string,
    .assign                = smart_tpl_assign,
    .strcmp                = smart_tpl_strcmp,
    .create_params         = smart_tpl_create_params,
    .delete_params         = smart_tpl_delete_params,
    .params_append_numeric = smart_tpl_params_append_numeric,
    .params_append_string  = smart_tpl_params_append_string,
    .params_append_boolean = smart_tpl_params_append_boolean,
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
}}