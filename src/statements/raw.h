/**
 *  RawStatement.h
 *
 *  Statement to simply echo raw output. Statements like this are created
 *  for text that was not inside a {template} instruction.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class RawStatement : public Statement
{
private:
    /**
     *  The raw data to be echo'ed
     *  @var    std::string
     */
    std::string _data;

public:
    /**
     *  Constructor
     *  @param  token
     */
    RawStatement(const Token *token) : _data(token->value, token->size) {}
    
    /**
     *  Destructor
     */
    virtual ~RawStatement() {}
    
    /**
     *  Generate the output of this statement
     *  @param  str     output stream
     */
    virtual void generate(std::ostream &str) const override
    {
        //
        // we are going to create the following C code
        //
        //      {
        //          char bytes[] = { 1, 2, 3, 4, 5};
        //          callbacks->write(bytes, count);
        //      }
        //
        // the bytes array contains a list of all ascii values of the raw data,
        // which is then sent to the callback that is supplied by the client
        // application.
        //
        
        // we ope
        str << "{char bytes[] = {";
        
        // loop through the array
        for (unsigned int i=0; i<_data.size(); i++) str << (int)_data[i] << ",";
        
        // final null character, and curly brace to close the bytes
        str << 0 << "};";
        
        // the actual write call
        str << "callbacks->write(bytes," << _data.size() << ");" << "}" << std::endl;
    }
};

/**
 *  End of namespace
 */
}

