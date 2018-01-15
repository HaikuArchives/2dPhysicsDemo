#include 	"my_BitView.h"

#include	<string.h>	// memset

#include	<Application.h>
#include	<Bitmap.h>
#include	<Window.h>

#include 	"iface.h"

#define		TOGGLE_WORLD_SPRING		'TGWS'
#define		TOGGLE_BODY_SPRING		'TGBS'
#define		TOGGLE_GRAVITY			'TGLG'
#define		TOGGLE_DAMPING			'TGDA'
#define		NEW_SPEED				'NWSP'


const rgb_color c_blue 	= 	{100,100,255};
const rgb_color c_red 	= 	{255,100,100};
const rgb_color c_black = 	{0,50,50};
 

BView* view;

inline void my_BitView::clear_8(uint8 color){
	memset(mBits, color, mBitsLength);
}


my_BitView::my_BitView(BRect rect, const char* name)
	:BView(rect, name, B_FOLLOW_ALL, B_WILL_DRAW )
	,mBitmap(NULL)
	,mHoehe(rect.Height())
	,mBreite(rect.Width())
	,mWasResized(true)
	,mSpeed(0)
	,mRun(true)
{
	float width; float height;

	mBack = new BView(BRect(0,0,400,400),"back",B_FOLLOW_ALL, B_WILL_DRAW);
	mBitmap = new BBitmap(BRect(0,0,400,400),B_CMAP8, true);
	mBitmap->AddChild(mBack);
	mBits=(uint8*)mBitmap->Bits();
	mBytesPerRow=mBitmap->BytesPerRow();
	mBitsLength=mBitmap->BitsLength();
	SetViewColor(B_TRANSPARENT_32_BIT);
	view=mBack;
	BView* cView=new BView(BRect(0,400,400,450),"control",B_FOLLOW_ALL, B_WILL_DRAW);
	cView->SetViewColor(220,220,220);
	AddChild(cView);

	BMessage* msg1 = new BMessage(TOGGLE_WORLD_SPRING);
	BMessage* msg2 = new BMessage(TOGGLE_BODY_SPRING);
	BMessage* msg3 = new BMessage(TOGGLE_GRAVITY);
	BMessage* msg4 = new BMessage(TOGGLE_DAMPING);
	BMessage* msg5 = new BMessage(NEW_SPEED);
	BMessage* msg6 = new BMessage(B_ABOUT_REQUESTED);


	mWorldSpring = new BCheckBox(BRect(0,0,10,10),"mWorldSpring","World Spring",msg1);
	mWorldSpring->GetPreferredSize(&width,&height);
	mWorldSpring->ResizeTo(width,height);
	mWorldSpring->MoveBy(10,5);
	cView->AddChild(mWorldSpring);

	mBodySpring = new BCheckBox(BRect(0,0,10,10),"mBodySpring","Body Spring",msg2);
	mBodySpring->GetPreferredSize(&width,&height);
	mBodySpring->ResizeTo(width,height);
	mBodySpring->MoveBy(10,30);
	cView->AddChild(mBodySpring);

	mGravity = new BCheckBox(BRect(0,0,10,10),"mGravity","Gravity",msg3);
	mGravity->GetPreferredSize(&width,&height);
	mGravity->ResizeTo(width,height);
	mGravity->MoveBy(100,5);
	cView->AddChild(mGravity);

	mDamping = new BCheckBox(BRect(0,0,10,10),"mDamping","Damping",msg4);
	mDamping->GetPreferredSize(&width,&height);
	mDamping->ResizeTo(width,height);
	mDamping->MoveBy(100,30);
	cView->AddChild(mDamping);
 
    mSlider = new BSlider(BRect(180,2,350,52), "mSlider", "Speed", msg5, 0, 100, B_TRIANGLE_THUMB);
   	mSlider->SetBarColor(c_blue);
    mSlider->SetHashMarks(B_HASH_MARKS_BOTTOM); 
    mSlider->SetHashMarkCount(5);	
	mSlider->SetLimitLabels("Slow", "Fast");
	mSlider->UseFillColor(true, &c_red);
	cView->AddChild(mSlider);
		
	mInfoButton = new BButton(BRect(0,0,30,20),"infoButton","Info", msg6);	
	mInfoButton->MoveBy(365,20);
	mInfoButton->SetTarget(be_app);
	cView->AddChild(mInfoButton);
		
	Go(); // spawn_thread() ...
}

int32 my_BitView::thread_func(void* arg) 
{ 
	my_BitView *obj = (my_BitView*) arg; 
	return(obj->threadFunc()); 
}

int32 my_BitView::threadFunc(void) 
{ 
	static BRect arect(0,0,400,400);
	do{
		if(Window()->Lock()){
			Draw(arect);
			Window()->Unlock();
		}
		snooze(100300-mSpeed*1000);	
	}while(mRun);
	return (0); 
}

status_t my_BitView::Go(void) 
{ 
	mThread = spawn_thread(my_BitView::thread_func, "drawingThread", B_DISPLAY_PRIORITY, (void *)this); 	
	return (resume_thread(mThread)); 
}


void my_BitView::AttachedToWindow(void)
{
	mWorldSpring->SetTarget(this);
	mBodySpring->SetTarget(this);
	mGravity->SetTarget(this);
	mDamping->SetTarget(this);
	mSlider->SetTarget(this);
}


my_BitView::~my_BitView()
{
	status_t ret;
	mRun=false;
	kill_thread(mThread);
	snooze(200000);
	if(mBitmap!=NULL) delete mBitmap;
}



void my_BitView::Draw(BRect arect)
{
	if(mBitmap->Lock()){
		clear_8(255); 	
		mBack->SetHighColor(220,220,220);
		mBack->FillTriangle(BPoint(0,327), BPoint(0,400), BPoint(146,400)); // cosmetic
		mBack->SetHighColor(0,0,0);
		view->BeginLineArray(20);
		Run();
		view->EndLineArray();
		mBack->Sync();
		mBitmap->Unlock();
	}
	DrawBitmap(mBitmap);
}

void my_BitView::MessageReceived(BMessage *msg){
	switch(msg->what){
	case TOGGLE_WORLD_SPRING:
		ToggleWorldSpring();
	break;
	case TOGGLE_BODY_SPRING:
		ToggleBodySpring();
	break;
	case TOGGLE_GRAVITY:
		ToggleGravity();
	break;
	case TOGGLE_DAMPING:
		ToggleDamping();
	break;
	case NEW_SPEED:
		mSpeed = mSlider->Value();
	break;
	default: BView::MessageReceived(msg);
	}

}


/*----------------------------------------------------------------------------

iface.h functions

*/

void Line( int X0, int Y0, int X1, int Y1 )
{
	view->AddLine(BPoint(X0+200,200-Y0),BPoint(X1+200,200-Y1), c_black);
}

void FillPoly(BPolygon* poly, rgb_color color)
{
	view->SetHighColor(color);
	view->FillPolygon(poly);
	view->SetHighColor(c_black);
}

float GetTime( void )
{
	static int32 StartMilliseconds;
	if(!StartMilliseconds)
	{
		// yes, the first time through will be a 0 timestep
		StartMilliseconds = system_time();
	}

    int32 CurrentMilliseconds = system_time();
    return float(CurrentMilliseconds - StartMilliseconds) / 1000.0f;
}







