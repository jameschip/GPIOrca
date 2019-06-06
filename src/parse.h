
/*
A NOTE ON COMMANDS THAT CAN BE PARSED!
The first 2 letters of the command are the identifier for what kind of io action is to be taken.
The next letter is the io number that we are modifying
The next letter of the command will be the value that the pin will be set to.
Everything after this will be ignored.

IO SET COMMAND:
io<pin><val>
set a digital io high or low. A value in <val> of non zero will set the pin high and a 0 will set it low. <pin> is the pin number to set.

OUTPUT PULSE COMMAND
op<pin><time>
*/

#ifndef PARSE_H
#define PARSE_H

/*
Struct that holds data about the IO that is being manipulated
*/
typedef struct parse_r
{   
    unsigned int io;
    unsigned int value;
} parse_r;

char initParser();

/*
check the buffer for a valid command and then 
place the data into a struct.

returns char: -1 if no valid command can be parsed 1 if a valid command was parsed.
*/
char parseBuffer(char *buffer, int length, parse_r *data);

#endif