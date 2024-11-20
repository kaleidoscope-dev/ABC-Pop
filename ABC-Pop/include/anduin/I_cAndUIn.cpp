#include "I_cAndUIn.h"
#include <string>


I_cAndUIn *gAnduin = NULL;




I_cAndUIn::I_cAndUIn()
{
}


I_cAndUIn::~I_cAndUIn()
{
}


I_cWindow *I_cAndUIn::CreateAnduinWindow(void)
{
 I_cWindow *window = new I_cWindow();
 vWindowList.push_back(window);
 return window;
}


// Fix: AddAnduinWindow
void I_cAndUIn::CreateAnduinWindow(I_cWindow *wnd) 
{
 vWindowList.push_back(wnd);
}



void I_cAndUIn::AddWidget(I_cWindow *parent_wnd, I_cWidget *wdg)
{
	parent_wnd->vWidgetList.push_back(wdg);
}



I_cWidget * I_cAndUIn::CreateWidget(I_cWindow *parent_wnd, ANDUIN_CONTROL_TYPE type)
{
 switch(type)
       {
	    case ANDUIN_CONTROL_TEXTBOX:
	    { 
		 I_cTextBox *tb = new I_cTextBox();
		 tb->type_ = ANDUIN_CONTROL_TEXTBOX;
		 parent_wnd->vWidgetList.push_back(tb);
		 return (I_cWidget*)tb;
		 break;
		}
		case ANDUIN_CONTROL_BUTTON:
		{
			I_cButton *bt = new I_cButton();
			bt->type_ = ANDUIN_CONTROL_BUTTON;
			parent_wnd->vWidgetList.push_back(bt);
			return (I_cWidget*)bt;
			break;
		}

		case ANDUIN_CONTROL_CHECK_BUTTON:
		{
			I_cCheckButton *bt = new I_cCheckButton();
			bt->type_ = ANDUIN_CONTROL_CHECK_BUTTON;
			parent_wnd->vWidgetList.push_back(bt);
			return (I_cWidget*)bt;
			break;
		}

		case ANDUIN_CONTROL_IMAGE_BUTTON:
		{
			I_cImageButton *bt = new I_cImageButton();
			bt->type_ = ANDUIN_CONTROL_IMAGE_BUTTON;
			parent_wnd->vWidgetList.push_back(bt);
			return (I_cWidget*)bt;
			break;
		}

		case ANDUIN_CONTROL_LABEL:
		{
			I_cLabel *lb = new I_cLabel();
			lb->type_ = ANDUIN_CONTROL_LABEL;
			parent_wnd->vWidgetList.push_back(lb);
			return (I_cWidget*)lb;
			break;
		}

		case ANDUIN_CONTROL_INPUTBOX:
		{
			I_cTextBoxInput *in = new I_cTextBoxInput();
			in->type_ = ANDUIN_CONTROL_INPUTBOX;
			parent_wnd->vWidgetList.push_back(in);
			return (I_cWidget*)in;
			break;
		}

		default: break;
		
 }
	
	return NULL;
}



// Used in the main loop 
void I_cAndUIn::HandleEvent(ANDUIN_EVENT_TYPE type)
{

	I_cWindow *wnd_active = GetActiveWindow();
	if (!wnd_active)
		return;

	switch (type)
	{
		case EVENT_BUTTON_UP:
		{
			size_t count = wnd_active->vWidgetList.size();
			for (size_t c = 0; c < wnd_active->vWidgetList.size(); c++)
			{
				I_cWidget *wdg = wnd_active->vWidgetList[c];
				if (wdg->type_ == ANDUIN_CONTROL_BUTTON)
				{
					I_cButton *btn = (I_cButton*)wdg;
					wdg->HandleEvent(type);
				}
			}
			break;
		}

		case EVENT_BUTTON_DOWN:
		{
			I_cWidget *focus = NULL;
			for (size_t c = 0; c < wnd_active->vWidgetList.size(); c++)
			{
				I_cWidget *wdg = wnd_active->vWidgetList[c];
				if (wdg->type_ == ANDUIN_CONTROL_BUTTON)
				{
					I_cButton *btn = (I_cButton*)wdg;
					wdg->HandleEvent(type);
				}
			}

			break;
		}
	}
	
}



void I_cAndUIn::HandleEvent(SDL_Event *event)
{
	I_cWindow *wnd_active = GetActiveWindow();
	if (!wnd_active)
		return;

		wnd_active->HandleEvent(event);

	

}




I_cWindow *I_cAndUIn::GetActiveWindow(void)
{

 for (size_t c=0;c<vWindowList.size();c++)
     {
	  I_cWindow *wnd = vWindowList[c];
	  if (wnd->inFocus_ == true)
	      return wnd;
	 }

 return 0;
}



void I_cAndUIn::SetActiveWindow(I_cWindow *window)
{
 I_cWindow *wnd_active = GetActiveWindow();
 if (wnd_active)   
     wnd_active->SetActive(false);


 window->SetActive(true);
}
