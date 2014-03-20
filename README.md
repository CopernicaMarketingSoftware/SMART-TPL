SMART-TPL
=========

Experimental library to see if it is somehow possible to compile Smarty templates into native code. 
Although Smarty is a PHP library, the SmartTpl project is _not_ limited to PHP. SmartTpl is a pure
C++ library to output templates.

The SmartTpl library converts templates into native binary code, which makes them much faster than
Smarty templates, which are running as PHP scripts.


How does this work?
-------------------

Templates are stored in *.tpl files, and normally contain HTML code, and special {$variables} and
{if} statements for variable content.

````html
<html>
 <body>
  Hello {$name}!
  
  {if $age > 18}
    You are older than 18.
  {/if}
 </body>
</html>
````

With the SmartTpl compiler you can turn such templates into binary code and store them as shared 
library *.so files. When a template is displayed, the webserver no longer has to load and process
the template.tpl file, but can use the already-compiled code from the shared library.


Work in progress
----------------

The project is a work in progress. At this moment, it is not yet in a usable state.
