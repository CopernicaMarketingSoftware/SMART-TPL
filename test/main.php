<?php
require_once('Smarty/3/Smarty.class.php');

// loop through arguments
for ($arg=1; $arg<$argc; $arg++)
{
    // do number of attempts
    for ($x=0; $x<100000; $x++)
    {
        // create smarty object
        $smarty = new Smarty();
        $smarty->compile_dir = "/tmp/smarty_compile_dir";
        $smarty->force_compile = true;

        $template = $smarty->createTemplate($argv[$arg]);
        $template->force_compile = true;

        // assign variable
        $template->assign("variable","bla");

        // fetch the template
        $template->fetch();
    }
}


