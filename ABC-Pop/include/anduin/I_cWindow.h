#pragma once
#include "I_cWidget.h"
#ifdef __ANDROID__
#include "../ABCPopCODE/include/I_cAnimate.h"
#else 
#include "include/I_cAnimate.h"
#endif




class I_cWindow
{
 public:
	 I_cWindow(std::string name);
	 I_cWindow();
	~I_cWindow();

	void SetActive(bool f);
	virtual void Draw(void);
    virtual void OnShow(void);
    virtual void OnClose(void);
	void AddWidget(I_cWidget *widget);
    void RemoveWidget(I_cWidget *ptr_widget);
	int GetControlCount(void);
	I_cWidget *GetControl(int num);  // TODO:  get widget
	I_cWidget *GetControl(SDL_Event *event);
	void SetBackgroundTexture(SDL_Texture *tex);
	void SetActiveWidget(I_cWidget *wdg);
	void DefocusAll(void);
	void HandleEvent(SDL_Event *event);
	void SetFadeActive(bool active);
	void Fadein(void);
	void Fadeout(void);
	void Fadein2(void);
	void Fadeout2(void);
	int alpha_;
	bool fadeIn_;
	bool fadeOut_;
	bool fadeActive_;
	std::vector<I_cWidget*>vWidgetList;
	bool inFocus_;
private:
	SDL_Texture *tex_window_;
    SDL_Texture *tex_fade_;
	std::string name_;
	void Init(std::string name);
    
    I_cAnimate anima_;
};