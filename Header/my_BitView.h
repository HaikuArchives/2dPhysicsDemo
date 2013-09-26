#pragma once



class my_BitView : public BView{
public:
						my_BitView(BRect rect, const char* name);
virtual					~my_BitView();
virtual	void			Draw(BRect area);
virtual void 			MessageReceived(BMessage *msg);
virtual void			AttachedToWindow(void);
private:
inline	void			clear_8(uint8 color);
		BView*			mBack;
		BBitmap*		mBitmap;
		uint8*			mBits;
		int32			mBytesPerRow;
		int32			mBitsLength;
		int32			mHoehe;
		int32			mBreite;
		BCheckBox*		mWorldSpring;
		BCheckBox*		mBodySpring;
		BCheckBox*		mGravity;
		BCheckBox*		mDamping;
		BSlider*		mSlider;
		BButton* 		mInfoButton;
		int32			mSpeed;

		static int32 	thread_func(void *arg); 
      	int32 			threadFunc(void); 
		status_t 		Go(void);
		thread_id 		mThread;
		bool			mWasResized;
		bool			mRun;
};

