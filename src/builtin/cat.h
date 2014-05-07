/**
 *  Cat.h
 *
 *  Built-in "|cat:"string"" modifier
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */
 
/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class CatModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~CatModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual Variant modify(Value *input, const Parameters *params) override
    {
        // copy the entire string
        std::string output(input->toString(), input->size());

        // Loop through the parameters and add all of them to the output string
        if (params)
        {
            for (auto param : *params) output.append(param.toString(), param.size());
        }

        // return it wrapped into a new StringValue
        return output;
    }
};

/**
 *  End namespace
 */
}

