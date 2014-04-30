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
    .write          =   smart_tpl_write,
    .output         =   smart_tpl_output,
    .member         =   smart_tpl_member,
    .member_at      =   smart_tpl_member_at,
    .loop_start     =   smart_tpl_loop_start,
    .loop_stop      =   smart_tpl_loop_stop,
    .member_iter    =   smart_tpl_member_iter,
    .variable       =   smart_tpl_variable,
    .to_string      =   smart_tpl_to_string,
    .to_numeric     =   smart_tpl_to_numeric,
    .to_boolean     =   smart_tpl_to_boolean,
    .size           =   smart_tpl_size,
    .modifier       =   smart_tpl_modifier,
    .modify_variable=   smart_tpl_modify_variable,
    .modify_numeric =   smart_tpl_modify_numeric,
    .modify_string  =   smart_tpl_modify_string,
    .assign_numeric =   smart_tpl_assign_numeric,
    .assign_boolean =   smart_tpl_assign_boolean,
    .assign_string  =   smart_tpl_assign_string,
    .assign         =   smart_tpl_assign,
    .strcmp         =   smart_tpl_strcmp,
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

