#include "AskWindow.h"


AskWindow::AskWindow(string text, string* ans):Window(200,80,1,1),ans(ans)
{
	okButton = new TextButton(this,"OK",0,2,0,Pointf(-4,10));
	backButton = new TextButton(this,"Back",0,2,2,Pointf(-3,-4));
	answer = new TextControl(this,100,true,0,0,Pointf(5,10));
	info = new LabelControl(this,text,15,0,2,Pointf(0,-25));
	bg = new TextureControl(this,"Edytor\\okno.png",200,80);
}

void AskWindow::Update(double deltaTime)
{
	okButton->Update();
	backButton->Update();
	answer->Update();

	if(okButton->pressed)
	{
		if(answer->GetText() != "")
		{
			*ans = answer->GetText();
			eventQueue.push_back(new KillLastEvent());
			eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
		}
	}

	if(backButton->pressed)
	{
		*ans = "";
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
	}
}

void AskWindow::Draw()
{
	bg->Draw();
	okButton->Draw();
	backButton->Draw();
	answer->Draw();
	info->Draw();
}