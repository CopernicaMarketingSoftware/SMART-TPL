/**
 *  Main.cpp
 * 
 *  Example program that shows how to use a template
 * 
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include <smarttpl.h>
#include <iostream>

/**
 *  Main function
 *  @return int
 */
int main()
{
    // create a template object
    SmartTpl::Template tpl("template.tpl");
    
    // output the template
    std::cout << tpl.process() << std::endl;
    
    // done
    return 0;
}

