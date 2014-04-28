<html>
    <body>
        This is an example template.
        With a {$name|toupper|tolower}!

        hallo {$x|toupper}

        {if true}
            And a conditional text
        {/if}
        {$variable.member}
        {foreach $map as $key => $value}
            Key: {$key}
            Value: {$value}
        {/foreach}
        {if $variable}
            sdfsdf
        {/if}
    </body>
</html>
