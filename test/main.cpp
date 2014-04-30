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
        for (int x=0; x<1; x++)
        {
            // construct data object
            SmartTpl::Data data;

            // assign variables
            SmartTpl::MapValue map;
            map.assign("member", "Test")
               .assign("anothermember", "Testing 1 2 3..");
            data.assign("map", &map)
                .callback("name", []() { return "Toon"; })
                .assign("x", "Mr. x");

            // output the template
            std::cout << tpl.process(data) << std::endl;
            //tpl.process(data);
        }
    }
}

