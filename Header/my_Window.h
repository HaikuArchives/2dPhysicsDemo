#pragma once

class my_Window : public BWindow
{
public:
							my_Window(BRect fFrame, const char *fTitel, window_type type, uint32 flags);
virtual	void				Quit(void);
virtual bool 				QuitRequested(void);
virtual	void				MessageReceived(BMessage *fMessage);

private:

};







