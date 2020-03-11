#include "Window.h"
#include "Button.h"
#include "TextureControl.h"
#include "LabelControl.h"
#include "TextControl.h"
#include "FieldControl.h"
#include "SelectControl.h"
#include "MultiSelectControl.h"
#include "error.h"
#include "xml\irrXML.h"
using namespace irr::io;

void Window::LoadContent(string file, vector<link<Controlka*>>& tmp)
{
	IrrXMLReader* xml = createIrrXMLReader(file.c_str());

	if(xml && xml->read())
	{
		if(!strcmp(xml->getNodeName(),"Window"))
		{
			this->w = (!strcmp(xml->getAttributeValueSafe("w"),""))?screen->getWidth():xml->getAttributeValueAsFloat("w");
			this->h = (!strcmp(xml->getAttributeValueSafe("h"),""))?screen->getHeight():xml->getAttributeValueAsFloat("h");
			Pointf dock = (!strcmp(xml->getAttributeValueSafe("dock"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("dock")));
			this->offsetPX = (!strcmp(xml->getAttributeValueSafe("offsetPX"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPX")));
			this->offsetPC = (!strcmp(xml->getAttributeValueSafe("offsetPC"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPC")));

			while(xml->read() && (xml->getNodeType() != EXN_ELEMENT_END)) 
			{
				if(!strcmp(xml->getNodeName(),"ImageButton"))
				{
					string name = xml->getAttributeValueSafe("name");
			        string texturePath = xml->getAttributeValueSafe("file");
					Pointf dock = (!strcmp(xml->getAttributeValueSafe("dock"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("dock")));
					Pointf offsetPC = (!strcmp(xml->getAttributeValueSafe("offsetPC"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPC")));
					float scale = (!strcmp(xml->getAttributeValueSafe("scale"),""))?1:xml->getAttributeValueAsFloat("scale");

					for(unsigned int i = 0; i<tmp.size();i++){
						if (tmp[i].Name == name){
							(*tmp[i]) = new ImgButton(this,texturePath,dock[0],dock[1],offsetPX,offsetPC,scale);
							controls.push_back(*tmp[i]);
							}
					}
				}
				if(!strcmp(xml->getNodeName(),"ImgHintButton"))
				{
					string name = xml->getAttributeValueSafe("name");
			        string texturePath = xml->getAttributeValueSafe("file");
			  	Pointf offsetPC = (!strcmp(xml->getAttributeValueSafe("offsetPC"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPC")));
					float scale = (!strcmp(xml->getAttributeValueSafe("scale"),""))?1:xml->getAttributeValueAsFloat("scale");

					for(unsigned int i = 0; i<tmp.size();i++){
						if (tmp[i].Name == name){
							(*tmp[i]) = new ImgHintButton(this,texturePath,hint,dock[0],dock[1],offsetPX,offsetPC,scale);
							controls.push_back(*tmp[i]);
							}
					}
				}
				else if(!strcmp(xml->getNodeName(),"TextButton")){
					string name = xml->getAttributeValueSafe("name");
			        string text = xml->getAttributeValueSafe("text");
					float width = xml->getAttributeValueAsFloat("width");
					Pointf dock = (!strcmp(xml->getAttributeValueSafe("dock"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("dock")));
					Pointf offsetPX = (!strcmp(xml->getAttributeValueSafe("offsetPX"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPX")));
					Pointf offsetPC = (!strcmp(xml->getAttributeValueSafe("offsetPC"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPC")));
					float scale = (!strcmp(xml->getAttributeValueSafe("scale"),""))?1:xml->getAttributeValueAsFloat("scale");

					for(unsigned int i = 0; i<tmp.size();i++){
						if (tmp[i].Name == name){
							(*tmp[i]) = new TextButton(this,text,width,dock[0],dock[1],offsetPX,offsetPC,scale);
							controls.push_back(*tmp[i]);
							}
					}

				}
				else if(!strcmp(xml->getNodeName(),"MixedButton")){
					string name = xml->getAttributeValueSafe("name");
			        string text = xml->getAttributeValueSafe("text");
			        string texturePath = xml->getAttributeValueSafe("file");
					float width = xml->getAttributeValueAsFloat("width");
					Pointf dock = (!strcmp(xml->getAttributeValueSafe("dock"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("dock")));
					float scale = (!strcmp(xml->getAttributeValueSafe("scale"),""))?1:xml->getAttributeValueAsFloat("scale");

					for(unsigned int i = 0; i<tmp.size();i++){
						if (tmp[i].Name == name){
							(*tmp[i]) = new MixedButton(this, texturePath, text,width,dock[0],dock[1],offsetPX,offsetPC,scale);
							controls.push_back(*tmp[i]);
							}
					}

				}
				else if(!strcmp(xml->getNodeName(),"Texture")){
					string name = xml->getAttributeValueSafe("name");
					string file = xml->getAttributeValueSafe("file");
			        float w = xml->getAttributeValueAsFloat("w");
					float h = xml->getAttributeValueAsFloat("h");
					Pointf dock = (!strcmp(xml->getAttributeValueSafe("dock"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("dock")));
					Pointf offsetPX = (!strcmp(xml->getAttributeValueSafe("offsetPX"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPX")));
					Pointf offsetPC = (!strcmp(xml->getAttributeValueSafe("offsetPC"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPC")));

					if(name != ""){
						for(unsigned int i = 0; i<tmp.size();i++)
							if (tmp[i].Name == name){
								(*tmp[i]) = new TextureControl(this,file,w,h,dock[0],dock[1],offsetPX,offsetPC);
								controls.push_back(*tmp[i]);
							}
					}else
						controls.push_back(new TextureControl(this,file,w,h,dock[0],dock[1],offsetPX,offsetPC));
				}
				else if(!strcmp(xml->getNodeName(),"Label")){
					string name = xml->getAttributeValueSafe("name");
					string text = xml->getAttributeValueSafe("text");
					Pointf dock = (!strcmp(xml->getAttributeValueSafe("dock"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("dock")));
					Pointf offsetPX = (!strcmp(xml->getAttributeValueSafe("offsetPX"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPX")));
					Pointf offsetPC = (!strcmp(xml->getAttributeValueSafe("offsetPC"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPC")));
					Color3f color = (!strcmp(xml->getAttributeValueSafe("color"),""))?Color3f():Color3f(_strdup(xml->getAttributeValueSafe("color")));
					float scale = (!strcmp(xml->getAttributeValueSafe("scale"),""))?1:xml->getAttributeValueAsFloat("scale");
					if(name != ""){
						for(unsigned int i = 0; i<tmp.size();i++)
							if (tmp[i].Name == name){
								(*tmp[i]) = new LabelControl(this,text,color,dock[0],dock[1],offsetPX,offsetPC,scale);
								controls.push_back(*tmp[i]);
							}
					}else
						controls.push_back(new LabelControl(this,text,color,dock[0],dock[1],offsetPX,offsetPC,scale));
				}
				else if(!strcmp(xml->getNodeName(),"TextBox")){
					string name = xml->getAttributeValueSafe("name");
			        float w = xml->getAttributeValueAsFloat("width");
					int enable = ((!strcmp(xml->getAttributeValueSafe("enable"),""))?1:xml->getAttributeValueAsInt("enable"));
					Pointf offsetPX = (!strcmp(xml->getAttributeValueSafe("offsetPX"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPX")));
					Pointf offsetPC = (!strcmp(xml->getAttributeValueSafe("offsetPC"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPC")));
					float scale = (!strcmp(xml->getAttributeValueSafe("scale"),""))?1:xml->getAttributeValueAsFloat("scale");

					for(unsigned int i = 0; i<tmp.size();i++){
						if (tmp[i].Name == name){
							(*tmp[i]) = new TextControl(this,w,(enable)?true:false,dock[0],dock[1],offsetPX,offsetPC,scale);
							controls.push_back(*tmp[i]);
							}
					}
				}
				else if(!strcmp(xml->getNodeName(),"Field")){
					string name = xml->getAttributeValueSafe("name");
			        float w = xml->getAttributeValueAsFloat("w");
					float h = xml->getAttributeValueAsFloat("h");
					Pointf dock = (!strcmp(xml->getAttributeValueSafe("dock"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("dock")));
					Pointf offsetPC = (!strcmp(xml->getAttributeValueSafe("offsetPC"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPC")));

					for(unsigned int i = 0; i<tmp.size();i++){
						if (tmp[i].Name == name){
							(*tmp[i]) = new FieldControl(this,w,h,dock[0],dock[1],offsetPX,offsetPC);
							controls.push_back(*tmp[i]);
							}
					}
				}
				else if(!strcmp(xml->getNodeName(),"List")){
					string name = xml->getAttributeValueSafe("name");
			        float w = xml->getAttributeValueAsFloat("width");
					int max = xml->getAttributeValueAsInt("max");
					Pointf offsetPX = (!strcmp(xml->getAttributeValueSafe("offsetPX"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPX")));
					Pointf offsetPC = (!strcmp(xml->getAttributeValueSafe("offsetPC"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPC")));
					float scale = (!strcmp(xml->getAttributeValueSafe("scale"),""))?1:xml->getAttributeValueAsFloat("scale");

					for(unsigned int i = 0; i<tmp.size();i++){
						if (tmp[i].Name == name){
							(*tmp[i]) = new SelectControl(this,max,w,dock[0],dock[1],offsetPX,offsetPC,scale);
							controls.push_back(*tmp[i]);
							}
					}
				}
				else if(!strcmp(xml->getNodeName(),"MultiList")){
					string name = xml->getAttributeValueSafe("name");
			        float w = xml->getAttributeValueAsFloat("width");
					int max = xml->getAttributeValueAsInt("max");
					Pointf offsetPX = (!strcmp(xml->getAttributeValueSafe("offsetPX"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPX")));
					Pointf offsetPC = (!strcmp(xml->getAttributeValueSafe("offsetPC"),""))?Pointf():Pointf(_strdup(xml->getAttributeValueSafe("offsetPC")));
					float scale = (!strcmp(xml->getAttributeValueSafe("scale"),""))?1:xml->getAttributeValueAsFloat("scale");

					for(unsigned int i = 0; i<tmp.size();i++){
						if (tmp[i].Name == name){
							(*tmp[i]) = new MultiSelectControl(this,max,w,dock[0],dock[1],offsetPX,offsetPC,scale);
							controls.push_back(*tmp[i]);
							}
					}
				}
				//else
					//error("Unknow tag in file: %s",file.c_str(),xml->getNodeName());
			}
		}
		else
			fatal("Cannot parse first tag in file: %s",file.c_str());
	}
	else
		fatal("Cannot read file %s",file.c_str());
	
	delete xml;
}

std::vector<Window*> windowsQueue;



