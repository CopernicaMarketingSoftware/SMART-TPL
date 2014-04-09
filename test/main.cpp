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
int main(int argc, const char *argv[])
{
    // loop through the arguments
    for (int arg = 1; arg < argc; arg++)
    {
        // do a number of attempts
        for (int x=0; x<1; x++)
        {
            // create a template object
            SmartTpl::Template tpl(argv[arg]);

            // construct data object
            SmartTpl::Data data;
            
            // assign variables
            data.assign("variable", "bla");

            // output the template
            std::cout << tpl.process(data) << std::endl;
            //tpl.process(data);
        }
    }
}

