
#include <Windows.h>
#include "NewTexture.h"
#include "Event.h"



NewTexture::NewTexture(GameObjectManager* gom, int* id):gom(gom),id(id)
{
	vector<link<Controlka*>> tmp = vector<link<Controlka*>>(6);
	tmp[0] = link<Controlka*>((Controlka**)&openButton,"openButton");
	tmp[1] = link<Controlka*>((Controlka**)&okButton,"okButton");
	tmp[2] = link<Controlka*>((Controlka**)&backButton,"backButton");
	tmp[3] = link<Controlka*>((Controlka**)&path,"path");
	tmp[4] = link<Controlka*>((Controlka**)&name,"name");
	tmp[5] = link<Controlka*>((Controlka**)&saveButton,"saveButton");

	LoadContent("Windows\\NewTexture.xml",tmp);
}


void NewTexture::Update(double deltaTime)
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Update();

	if(openButton->pressed)
	{
		openButton->pressed = false;
		OPENFILENAME ofn;       // common dialog box structure
		char szFile[250];       // buffer for file name
		//char absolutePath[250];
		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = nullptr;
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "PNG (*.png)\0*.png\0TGA (*.tga)\0*.tga\0JPG (*.jpg)\0*.jpg\0BMP (*.bmp)\0*.bmp\0All image files\0*.png;*.tga;*.jpg;*.bmp\0All files\0*.*\0\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		//ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileName(&ofn)==TRUE)
		{
			srcPath = ofn.lpstrFile;
			//string file = full.substr(full.find_last_of("\\")+1,99999);
			//GetModuleFileName(NULL,absolutePath,260);
			//s = string(absolutePath);
			//s = s.substr(0,s.find_last_of("\\")) + "\\Textures\\" + file;
			//CopyFile(ofn.lpstrFile,(s).c_str(),false);
			path->SetText(srcPath);
		}
	}

	if(saveButton->pressed)
	{
		saveButton->pressed = false;
		OPENFILENAME ofn;       // common dialog box structure
		char szFile[250];       // buffer for file name
		//char absolutePath[250];
		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = nullptr;
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "PNG (*.png)\0*.png\0TGA (*.tga)\0*.tga\0JPG (*.jpg)\0*.jpg\0BMP (*.bmp)\0*.bmp\0All image files\0*.png;*.tga;*.jpg;*.bmp\0All files\0*.*\0\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		ofn.lpstrInitialDir = ".\\Textures\\";
		if (GetSaveFileName(&ofn)==TRUE)
		{
			desPath = ofn.lpstrFile;
			if(desPath.find("Textures\\") == -1)
				desPath = "Destination folder sholud be in Textures";
			else
				desPath = desPath.substr(desPath.find("Textures\\")-8);
			name->SetText(desPath);
		}
	}

	if(okButton->pressed)
	{
		okButton->pressed = false;
		desPath = name->GetText();
		srcPath = path->GetText();
		if(srcPath != "" && desPath.find("Textures\\") != -1)
		{
			CopyFile(srcPath.c_str(),desPath.c_str(),false);
			*id = gom->AddNewTexture(new Texture(desPath),name->GetText()).Id;
			eventQueue.push_back(new KillLastEvent());
			eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
		}
		else
		{
			name->SetText("Destination folder sholud be in Textures");
		}
	}

	if(backButton->pressed)
	{
		*id = -1;
		eventQueue.push_back(new KillLastEvent());
		eventQueue.push_back(new SetLastActiveEvent(BOOL_TYPE::SET_TRUE));
	}
}

void NewTexture::Draw()
{
	for(unsigned int i = 0; i < controls.size(); i++) controls[i]->Draw();

	float y = (h - 16) / 2.0f;
}

