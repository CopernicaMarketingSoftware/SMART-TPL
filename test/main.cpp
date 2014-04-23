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
        SmartTpl::File file(argv[arg]);
        // create a template object
        SmartTpl::Template tpl(file);
        // do a number of attempts
        for (int x=0; x<10; x++)
        {
            // construct data object
            SmartTpl::Data data;
            
            // assign variables
            SmartTpl::MapValue map;
            map.assign("member", "Test");
            data.assign("variable", &map)
                .assign("name", "Testing..")
                .assign("x", "Mr. x");

            // output the template
            std::cout << tpl.process(data) << std::endl;
            //tpl.process(data);
        }
    }
}

