<html>
    <body>
        {$date}
        This is an example template.

        Hello {$name|toupper|tolower|ucfirst}.

        {if true}
            And a conditional text
        {/if}
        {$variable.member[0]}
        {foreach $key in $variable}
            {$key}
        {/foreach}
        {if $variable}
            sdfsdf
        {/if}
    </body>
</html>
