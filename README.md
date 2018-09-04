SMART-TPL
=========

Experimental library to see if it is somehow possible to compile Smarty templates 
into native code.  Although Smarty is a PHP library, the SmartTpl project is _not_ 
limited to PHP. SmartTpl is a pure C++ library to work with templates.
For help installing SMART-TPL please head over to [INSTALL.md](https://github.com/CopernicaMarketingSoftware/SMART-TPL/blob/master/INSTALL.md)

ABOUT
=====

SMART-TPL library is created and maintained by Copernica (www.copernica.com). 
Do you appreciate our work and are you looking for other high quality solutions? 

Then check out our other solutions:

* PHP-CPP (www.php-cpp.com)
* PHP-JS (www.php-js.com)
* Copernica Marketing Suite (www.copernica.com)
* MailerQ MTA (www.mailerq.com)
* Responsive Email web service (www.responsiveemail.com)

What does it do?
----------------

Templates are stored in *.tpl files, and contain HTML code mixed with special 
{$variables} and {if} and {foreach} statements for variable content.

````html
<html>
 <body>
  Hello {$name}!

  {if $age > 18}
    You are older than 18.
  {else}
    You are not that old.
  {/if}
  
  // You can define variables
  {$text = 'Lorem Ipsum'}
  {$text}
  
  // Modify all characters to lower case
  {$text|tolower}
  
  // And you can calculate
  {$total = $product_price * $product_qty}
  {$total}
  
 </body>
</html>
````

Templates are not limited to just HTML, you can also use them for other file
formats. The syntax of the templates is loosely based on the syntax that the
Smarty template engine offers.

The SmartTpl library does nothing exciting: it turns the templates into HTML, 
by replacing all the variables with their actual value, and evaluating the {if} 
and {foreach} statements.

SmartTpl is not a real programming language - it only offers very basic 
statements, and does not allow one to create and call functions or make 
complicated data structures. In this it also is (intentionally) less powerful
than Smarty. If you want to do real programming, you can combine SmartTpl with
a real programming language.


Compiling templates
-------------------

The SmartTpl library allows you to compile your templates into native executable
code. This makes your templates much faster, because they do not have to be
evaluated at runtime. By compiling your templates, they are directly turned
into native executable code that runs directly on the CPU. 

An added benefit of compiling templates is that the source code becomes next to 
unreadable. If you want to distribute your templates, but do not want external
parties to modify them, you can compile them to make editing much harder.

To compile a template, you simply use the 'smarttpl' compiler:

````
smarttpl mytemplate.tpl
````

This will turn your mytemplate.tpl into a mytemplate.so file, which can later
be passed to the Template class.


JIT compiler
------------

Compiling your templates is <i>optional</i>. If you choose not to compile them,
the template will be compiled to native code at runtime with the built-in 
Just-In-Time compiler. If you use the same template object a couple of times, 
it will only have to be runtime compiled once.

Therefore, with this JIT compiler, only the first time that a template is 
displayed it is a little slower. For all subsequent calls it is as fast as a 
compiled template.


Displaying a template
---------------------

A template object first need to be loaded from a certain source. The SmartTpl
library has two classes that can be used for this: The SmartTpl::File class
for templates that are loaded from the filesystem, and the SmartTpl::Buffer
class for templates that are "loaded" from an in-memory buffer.

Both the SmartTpl::Buffer and SmartTpl::File class are derived from the
SmartTpl::Source class. If you want to add an alternative template source 
(for example for templates that are loaded from a database) you can create your 
own class that also extends from SmartTpl::Source.

````c++
// required code
#include <smarttpl.h>

// example function that displays a template that is loaded from the filesystem
void example1()
{
    // use a template stored on the filesystem
    SmartTpl::File source("mytemplate.tpl");

    // create the template object
    SmartTpl::Template tpl(source);

    // output the template to stdout
    std::cout << tpl;
}

// example function that displays a template that is already stored in memory
void example2()
{
    // use a template available in mempory
    SmartTpl::Buffer source("<html>....</html>", 12345);

    // create the template object
    SmartTpl::Template tpl(source);

    // output the template to stdout
    std::cout << tpl;
}

// use an already-compiled template
void example3()
{
    // use a template stored on the filesystem
    SmartTpl::File source("mytemplate.so");

    // create the template object
    SmartTpl::Template tpl(source);

    // output the template to stdout
    std::cout << tpl;
}
````

Assigning data
--------------

Inside a template you can make use of {$variables}. Before you display a 
template, you should first assign the values of all these variables to a 
data object which is used by the template.

You can assign integers and strings to a data object.


````c++
// required code
#include <smarttpl.h>

// example how to assign data
void example()
{
    // create a template
    SmartTpl::Template tpl(SmartTpl::File("mytemplate.tpl"));

    // create a data object
    SmartTpl::Data data;

    // assign data
    data.assign("name", "John Doe")
        .assign("age", 32);

    // show the template
    std::cout << tpl.process(data);
}
````

More complicated data can be assigned to, like maps and vectors. These can be
used in the templates with variables like {$varname.member} or {$varname[0]}.

The next powerful feature of SmartTpl is that it supports callbacks. This is 
especially useful if you do not know if a variable is going to be used in a 
template, and you do not want to fetch all information in advance.

````c++
// required code
#include <smarttpl.h>

// example how to assign data
void example()
{
    // create a template
    SmartTpl::Template tpl(SmartTpl::File("mytemplate.tpl"));

    // create a data object
    SmartTpl::Data data;

    // assign data
    data.callback("name", []() -> std::string {

        // @todo find out the value of the name, for example by starting
        //       a database query

        return name;
    });

    // show the template
    std::cout << tpl.process(data);
}
````

In the example above the {$name} value is assigned to the template, but
the value is a callback function. Only when the {$name} value is actually
_used_, this callback gets called, and your application has to run the
algorithm to retrieve the name.

The SmartTpl template language allows you to use nested values. You can
use values like {$name.member.submember[$index].member}. To make this
fully flexible, you can override the SmartTpl::Value class to create
your own value.

````c++
// required code
#include <smarttpl.h>

/**
 *  our own value class
 */
class MyValue : public SmartTpl::Value
{
public:
    /**
     *  Method that gets called when the variable has to be turned into a
     *  string. This is for example called when a {$variable} is used in
     *  a template.
     *
     *  @return std::string
     */
    std::string toString() const override
    {
        return "abcd";
    }

    /**
     *  Method that gets called when the variable is used in a numeric 
     *  context, to turn the variable into an integer
     *
     *  @return numeric_t
     */
    numeric_t toNumeric() const override
    {
        return 0;
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    bool toBoolean() const override
    {
        return false;
    }

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    double toDouble() const override
    {
        return 0.0;
    }

    /**
     *  Method that gets called when a member is accessed. This is called
     *  when the variable is accessed in the template as {$var.x} or {$var[$x]}
     *
     *  This method should return a SmartTpl::VariantValue object.
     *
     *  @param  name        name of the member
     *  @param  size        size of name
     *  @return VariantValue
     */
    VariantValue member(const char *name, size_t size) const override
    {
        // check the name
        if (strcmp(name, "x") == 0) return SomeOtherValue();
        if (strcmp(name, "self") == 0) return this;

        // not found
        return nullptr;
    }

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    size_t memberCount() const override
    {
        return 1;
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return VariantValue
     */
    VariantValue member(size_t position) const override
    {
        // Not implemented, always return empty values
        return nullptr;
    }

    /**
     *  Create a new iterator that allows you to iterate over the subvalues
     *  feel free to return nullptr if you don't want to be able to iterate
     *  over your type
     *
     *  @return Newly allocated Iterator
     */
    Iterator *iterator() const override
    {
        // Return a custom implementation of Iterator
        return new CustomIterator(this);
    }
};

// example how to assign data
void example()
{
    // create a template
    SmartTpl::Template tpl(SmartTpl::File("mytemplate.tpl"));

    // create a data object
    SmartTpl::Data data;

    // assign data
    data.assignManaged("name", new MyValue());

    // show the template
    std::cout << tpl.process(data);
}

````

By overriding from SmartTpl::Value, you can create all sorts of variables
that behave like arrays or objects. The SmartTpl library already has built-in
types for a number of types.
