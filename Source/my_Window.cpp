#include "my_Window.h"


my_Window::my_Window(BRect fFrame, const char *fTitel, window_type type, uint32 flags)
					: BWindow(fFrame,fTitel, type, flags)
{	
}


void
my_Window::Quit(void)
{
	BWindow::Quit(); 
}


bool
my_Window::QuitRequested(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}


void my_Window::MessageReceived(BMessage *fMessage)
{
	
	switch (fMessage->what) {
		case 'xxxx' : 

		break;		
		default:
		BWindow::MessageReceived(fMessage);
    }
}


