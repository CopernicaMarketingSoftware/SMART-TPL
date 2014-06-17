<html>
    <body>
        {$date}
        This is an example template.

        Hello {$name|toupper|tolower|ucfirst}.

        {if true}
            And a conditional text
        {/if}
        {$variable.member}
        {foreach $key in $variable}
            {$key}
        {/foreach}
        {if $variable}
            sdfsdf
        {/if}
    </body>
</html>
