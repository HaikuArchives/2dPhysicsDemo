#include 	"my_App.h"

#include	<stdio.h>	// sprintf

#include	<Alert.h>

#include	"my_Window.h"
#include	"my_BitView.h"

const float		OFFSET_X 	=	100;
const float		OFFSET_Y	=	100;
const float		BREITE 		=	400;
const float		HOEHE		=	470;


my_App::my_App() : BApplication("application/x-vnd.2dPhysicsDemo")
{
	my_Window* win=new my_Window(BRect(OFFSET_X, OFFSET_Y, OFFSET_X+BREITE, OFFSET_Y+HOEHE)
								,"2D Demo"
								,B_TITLED_WINDOW
								,B_NOT_RESIZABLE | B_NOT_ZOOMABLE );
	my_BitView* view=new my_BitView(BRect(0, 0, BREITE, HOEHE),"BitView");
	win->AddChild(view);
	win->Show();
}

my_App::~my_App()
{

}

void my_App::ReadyToRun(void)
{

}


bool my_App::QuitRequested()
{
	BApplication::QuitRequested();
	return(true);
}

void my_App::AboutRequested(void) 
{
	char str[1000];
	sprintf(str, "2D Physics Test Program \na cheesy test harness for 2D physics \n\n(c) by Chris Hecker \n<http://www.d6.com/users/checker>\n\nVisit his Web-Page. He has written some great articles about 'Physically Based Modeling'\n\nported to BeOS by Andreas Kaenner \n <http://www.archi-line.de/kaenner>");
	BAlert *the_alert = new BAlert("", str, "OK");
	the_alert->Go();
}

void my_App::MessageReceived(BMessage* fmessage)
{	
	switch (fmessage->what) {
		case 'xxxx':			
		
		break;
		default:
		BApplication:MessageReceived(fmessage);
    }
}
