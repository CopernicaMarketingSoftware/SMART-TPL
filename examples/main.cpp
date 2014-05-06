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

        // construct data object
        SmartTpl::Data data;

        // assign variables
        SmartTpl::MapValue map;
        map.assign("member", "Test")
            .assign("anothermember", "Testing 1 2 3..");
        SmartTpl::DateValue date("%A %d %B %Y %T");
        data.assign("map", &map)
            .callback("name", []() { return "Toon"; })
            .assign("date", &date)
            .assign("x", "Mr. x");
        // do a number of attempts
        for (int x=0; x<10; x++)
        {
            // output the template
            std::cout << tpl.process(data) << std::endl;
            //tpl.process(data);
        }
    }
}

