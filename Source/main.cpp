#include "my_App.h"

main()
{	
	my_App* app;
	app = new my_App();
	app->Run();
	delete(app);
	return(0);
}