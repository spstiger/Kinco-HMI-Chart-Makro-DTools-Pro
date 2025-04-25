#include <macro.h>

int Main()
{
	short Input;
    short Output;
    ReadVar(@MW0@,&Input);
    Input++;    
    	// Here to add macro code.
	Output = int(50 * sin(3.14*(float(Input)/100.0)) + 50);
    WriteVar(@MW2@,&Output);
    WriteVar(@MW0@,&Input);
	return CMD_OK;
}