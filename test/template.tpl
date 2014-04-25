<html>
    <body>
        This is an example template.
        With a {$name|toupper|tolower}!

        hallo {$x|toupper}

        {if true}
            And a conditional text
        {/if}
        {$variable.member[0]}
        {for $key in $variable}
            {$key}
        {/for}
        {if $variable}
            sdfsdf
        {/if}
    </body>
</html>
