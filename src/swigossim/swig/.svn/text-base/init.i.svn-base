%module jossim
%{
#include <ossim/init/ossimInit.h>	
%}	

%include "various.i"

%apply char **STRING_ARRAY { char **argv };

class ossimInit
{
public:
	static ossimInit* instance();
	void initialize( int argc, char **argv);
	
protected:
	ossimInit();
};			
