#pragma once


class my_App : public BApplication 
{
public:
						my_App();			
virtual					~my_App();
virtual	bool			QuitRequested(void);						
virtual	void			ReadyToRun(void);							
virtual void			AboutRequested(void);						
virtual	void			MessageReceived(BMessage* fmessage);		

private:
	
};