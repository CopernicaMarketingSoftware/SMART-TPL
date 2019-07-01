/**
 *  capitalize.h
 *
 *  Built-in "|capitaluze:bool" modifier
 *
 *  @author Youri Moll <youri.moll@copernica.com>
 *  @copyright 2019 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class CapitalizeModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~CapitalizeModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // copy the entire string
        std::string output(input.toString());   
    
        // our delimiters, we will capitalize after any of these characters are encountered
        const char* delims = " \t\r\n\f\v";
    
        // determine if words with digits will be processed
        bool processDigits = false;
    
        // did the user specify that we should also process words with digits
        if (params.size() == 1) processDigits = params[0].toBoolean();
        
        // helper variable to determine if a word contains a digit
        bool containsDigit = false;

        // We will loop backwards through our input string
        for (int i = output.size() - 1; i >= 0; --i)
        {
            // check if the word we are processing contains a digit
            if (isdigit(output[i])) containsDigit = true;
            
            // if we have found one of our delimiters in the string
            if (! strchr(delims, output[i])) continue;
            
            // Should we skip this word?
            if (!processDigits && containsDigit) 
            {
                // we set containsDigit to false
                containsDigit = false;
                    
                // and we skip
                continue;
            }

            // check if the first character of the word is valid and cast it to 
            // upper case      
            if (output[i + 1]) output[i + 1] = toupper(output[i + 1]);
                
            // we set containsDigit to false
            containsDigit = false;
        }

        // if the fist word contains a digit and we do not want to process those,
        // we are done
        if (!processDigits && containsDigit) return output;

        // process the first character
        output[0] = toupper(output[0]);
        
        //and return
        return output;
    }
};

/**
 *  End namespace
 */
}}
