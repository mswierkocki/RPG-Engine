#include "GameObjectManager.h"

#include <io.h>
#include <fstream>

#include "xml/irrXML.h"
#include "error.h"

using namespace irr::io;

GameObjectManager::GameObjectManager()
{
	message("  Initialising...");
	LoadAllTextures();
	LoadAllObjects();
	LoadAllItems();
	LoadAllCreatures();
	LoadAllMaps();
}

GameObjectManager::~GameObjectManager()
{
	SaveAllTextures();
	SaveAllObjects();
	SaveAllItems();
	SaveAllCreatures();
	SaveAllMaps();

	SaveAllTextures("Content\\textures.xml");
	SaveAllObjects("Content\\objects.xml");
	SaveAllCreatures("Content\\creatures.xml");
	SaveAllItems("Content\\items.xml");
	SaveAllMaps("Content\\maps.xml");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::link<Texture>& GameObjectManager::GetTextureByID(unsigned id)
{
	if(id+1>textures.capacity()) textures.resize(id+1,nullptr);
	if(textures[id]==nullptr)
	{
		error("  Call to non-existing resource id. Creating empty placeholder...");
		textures[id] = std::link<Texture>(new Texture(),"empty",id);
	}
	if(textures[id]->texID==0) textures[id]->Load(textures[id]->file); //main development step
	return textures[id];
}

const std::link<Object>& GameObjectManager::GetObjectByID(unsigned id)
{
	if(id+1>objects.capacity()) objects.resize(id+1,nullptr);
	if(objects[id]==nullptr)
	{
		error("  Call to non-existing resource id. Creating empty placeholder...");
		objects[id] = std::link<Object>(new Object(),"empty",id);
	}
	return objects[id];
}

const std::link<Item>& GameObjectManager::GetItemByID(unsigned id)
{
	if(id+1>items.capacity()) items.resize(id+1,nullptr);
	if(items[id]==nullptr)
	{
		error("  Call to non-existing resource id. Creating empty placeholder...");
		items[id] = std::link<Item>(new Item(),"empty",id);
	}
	return items[id];
}

const std::link<Creature>& GameObjectManager::GetCreatureByID(unsigned id)
{
	if(id+1>creatures.capacity()) creatures.resize(id+1,nullptr);
	if(creatures[id]==nullptr)
	{
		error("  Call to non-existing resource id. Creating empty placeholder...");
		creatures[id] = std::link<Creature>(new Creature(),"empty",id);
	}
	return creatures[id];
}

const std::link<Map>& GameObjectManager::GetMapByID(unsigned id)
{
	if(id+1>maps.capacity()) maps.resize(id+1,nullptr);
	if(maps[id]==nullptr)
	{
		error("  Call to non-existing resource id. Creating empty placeholder...");
		maps[id] = std::link<Map>(new Map(),"empty",id);
	}
	return maps[id];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::link<Texture>& GameObjectManager::GetTextureByName(const std::string& name)
{
	for(unsigned i=0; i<textures.size(); i++)
	{
		if(textures[i].Name == name) return textures[i];
	}
	error("  Call to non-existing resource name. Creating empty placeholder...");
	textures.push_back(std::link<Texture>(new Texture(),"empty",textures.size()-1));
	return textures.back();
}

const std::link<Object>& GameObjectManager::GetObjectByName(const std::string& name)
{
	for(unsigned i=0; i<objects.size(); i++)
	{
		if(objects[i].Name == name) return objects[i];
	}
	error("  Call to non-existing resource name. Creating empty placeholder...");
	objects.push_back(std::link<Object>(new Object(),"empty",objects.size()-1));
	return objects.back();
}

const std::link<Item>& GameObjectManager::GetItemByName(const std::string& name)
{
	for(unsigned i=0; i<items.size(); i++)
	{
		if(items[i].Name == name) return items[i];
	}
	error("  Call to non-existing resource name. Creating empty placeholder...");
	items.push_back(std::link<Item>(new Item(),"empty",items.size()-1));
	return items.back();
}

const std::link<Creature>& GameObjectManager::GetCreatureByName(const std::string& name)
{
	for(unsigned i=0; i<creatures.size(); i++)
	{
		if(creatures[i].Name == name) return creatures[i];
	}
	error("  Call to non-existing resource name. Creating empty placeholder...");
	creatures.push_back(std::link<Creature>(new Creature(),"empty",creatures.size()-1));
	return creatures.back();
}

const std::link<Map>& GameObjectManager::GetMapByName(const std::string& name)
{
	for(unsigned i=0; i<maps.size(); i++)
	{
		if(maps[i].Name == name) return maps[i];
	}
	error("  Call to non-existing resource name. Creating empty placeholder...");
	maps.push_back(std::link<Map>(new Map(),"empty",maps.size()-1));
	return maps.back();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::link<Texture> GameObjectManager::CopyTextureByID(unsigned id)
{
	fatal("  Sorry, but copying textures makes no sense at the moment!");
	return nullptr;
}

std::link<Object> GameObjectManager::CopyObjectByID(unsigned id)
{
	const std::link<Object>& obj = GetObjectByID(id);

	std::link<Object> copy(new Object(obj->GetX(),obj->GetY(),obj->GetScale()),obj.Name,obj.Id);

	for(unsigned i=0; i<obj->GetAnimVecRef().size(); i++)
	{
		const std::link<Animation>& anim = obj->GetAnimVecRef().at(i);
		copy->GetAnimVecRef().push_back(std::link<Animation>(new Animation(*anim),anim.Name,anim.Id));
	}

	return copy;
}

std::link<Item> GameObjectManager::CopyItemByID(unsigned id)
{
	const std::link<Item>& item = GetItemByID(id);

	std::link<Item> copy(new Item(),item.Name,item.Id);

	for(unsigned i=0; i<item->GetAnimVecRef().size(); i++)
	{
		const std::link<Animation>& anim = item->GetAnimVecRef().at(i);
		copy->GetAnimVecRef().push_back(std::link<Animation>(new Animation(*anim),anim.Name,anim.Id));
	}

	return copy;
}

std::link<Creature> GameObjectManager::CopyCreatureByID(unsigned id)
{
	const std::link<Creature>& crit = GetCreatureByID(id);

	std::link<Creature> copy(new Creature(),crit.Name,crit.Id);

	for(unsigned i=0; i<crit->GetAnimVecRef().size(); i++)
	{
		const std::link<Animation>& anim = crit->GetAnimVecRef().at(i);
		copy->GetAnimVecRef().push_back(std::link<Animation>(new Animation(*anim),anim.Name,anim.Id));
	}

	return copy;
}

std::link<Map> GameObjectManager::CopyMapByID(unsigned id)
{
	const std::link<Map>& map = GetMapByID(id);

	std::link<Map> copy(new Map(map->GetWidth(),map->GetHeight()),map.Name,map.Id);

	//copy->SetTileMapName(map->GetTileMapName());
	for(unsigned i=0; i<map->GetWidth()*map->GetHeight(); i++)
	{
		copy->GetKafelkiPtr()[i] = map->GetKafelkiPtr()[i];
	}

	for(unsigned i=0; i<map->GetObjectVecRef().size(); i++)
	{
		const std::link<Object>& obj = map->GetObjectVecRef().at(i);

		copy->GetObjectVecRef().push_back(std::link<Object>(new Object(obj->GetX(),obj->GetY(),obj->GetScale()),obj.Name,obj.Id));

		for(unsigned j=0; j<obj->GetAnimVecRef().size(); j++)
		{
			const std::link<Animation>& anim = obj->GetAnimVecRef().at(j);
			copy->GetObjectVecRef().back()->GetAnimVecRef().push_back(std::link<Animation>(new Animation(*anim),anim.Name,anim.Id));
		}
	}

	return copy;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::link<Texture>& GameObjectManager::AddNewTexture(Texture* texture, const std::string& name)
{
	textures.push_back(texture);
	textures.back().Name = name;
	textures.back().Id = textures.size()-1;
	return textures.back();
}

const std::link<Object>& GameObjectManager::AddNewObject(Object* object, const std::string& name)
{
	objects.push_back(object);
	objects.back().Name = name;
	objects.back().Id = objects.size()-1;
	return objects.back();
}

const std::link<Item>& GameObjectManager::AddNewItem(Item* item, const std::string& name)
{
	items.push_back(item);
	items.back().Name = name;
	items.back().Id = items.size()-1;
	return items.back();
}

const std::link<Creature>& GameObjectManager::AddNewCreature(Creature* creature, const std::string& name)
{
	creatures.push_back(creature);
	creatures.back().Name = name;
	creatures.back().Id = creatures.size()-1;
	return creatures.back();
}

const std::link<Map>& GameObjectManager::AddNewMap(Map* map, const std::string& name)
{
	maps.push_back(map);
	maps.back().Name = name;
	maps.back().Id = maps.size()-1;
	return maps.back();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GameObjectManager::RemoveTextureByID(unsigned id)
{
	if(textures.at(id)._Ref==0)
	{
		delete textures.at(id);

		textures.at(id) = nullptr;

		return true;
	}
	else
	{
		error("  Can't remove selected texture! Name: '%s' ID: %d Refs: %d", textures.at(id).Name.c_str(), textures.at(id).Id, textures.at(id)._Ref);
		return false;
	}
}

bool GameObjectManager::RemoveObjectByID(unsigned id)
{
	if(objects.at(id)._Ref==0)
	{
		for(unsigned i=0; i<objects.at(id)->GetAnimVecRef().size(); i++)
		{
			delete objects.at(id)->GetAnimVecRef().at(i);
		}
		delete objects.at(id);

		objects.at(id) = nullptr;

		return true;
	}
	else
	{
		error("  Can't remove selected object! Name: '%s' ID: %d Refs: %d", objects.at(id).Name.c_str(), objects.at(id).Id, objects.at(id)._Ref);
		return false;
	}
}

bool GameObjectManager::RemoveItemByID(unsigned id)
{
	if(items.at(id)._Ref==0)
	{
		for(unsigned i=0; i<items.at(id)->GetAnimVecRef().size(); i++)
		{
			delete items.at(id)->GetAnimVecRef().at(i);
		}
		delete items.at(id);

		items.at(id) = nullptr;

		return true;
	}
	else
	{
		error("  Can't remove selected item! Name: '%s' ID: %d Refs: %d", items.at(id).Name.c_str(), items.at(id).Id, items.at(id)._Ref);
		return false;
	}
}

bool GameObjectManager::RemoveCreatureByID(unsigned id)
{
	if(creatures.at(id)._Ref==0)
	{
		for(unsigned i=0; i<creatures.at(id)->GetAnimVecRef().size(); i++)
		{
			delete creatures.at(id)->GetAnimVecRef().at(i);
		}
		delete creatures.at(id);

		creatures.at(id) = nullptr;

		return true;
	}
	else
	{
		error("  Can't remove selected creature! Name: '%s' ID: %d Refs: %d", creatures.at(id).Name.c_str(), creatures.at(id).Id, creatures.at(id)._Ref);
		return false;
	}
}

bool GameObjectManager::RemoveMapByID(unsigned id)
{
	//if(maps.at(id)._Ref==0)
	//{
		delete maps.at(id)->GetKafelkiPtr();
		for(unsigned i=0; i<maps.at(id)->GetObjectVecRef().size(); i++)
		{
			delete maps.at(id)->GetObjectVecRef().at(i);
		}
		delete maps.at(id);

		maps.at(id) = nullptr;

		return true;
	//}
	//else
	//{
	//	error("  Can't remove selected map! Name: '%s' ID: %d Refs: %d", maps.at(id).Name.c_str(), maps.at(id).Id, maps.at(id)._Ref);
	//	return false;
	//}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GameObjectManager::LoadAllTextures(char* xmlfile)
{
	IrrXMLReader* xml = createIrrXMLReader(xmlfile);
	
	if(xml && xml->read())
	{
		if(!strcmp(xml->getNodeName(),"Textures"))
		{
			if(textures.capacity()<(unsigned)xml->getAttributeValueAsInt("count"))
				textures.resize(xml->getAttributeValueAsInt("count"),nullptr);

			while(xml->read() && (xml->getNodeType() != EXN_ELEMENT_END))
			{
				if(!strcmp(xml->getNodeName(),"Texture"))
				{
					textures[xml->getAttributeValueAsInt("id")] = std::link<Texture>(new Texture(),xml->getAttributeValueSafe("name"),xml->getAttributeValueAsInt("id"));
					textures[xml->getAttributeValueAsInt("id")]->file = _strdup(xml->getAttributeValueSafe("file"));
					//if(!(textures[xml->getAttributeValueAsInt("id")] = std::link<Texture>(new Texture(),xml->getAttributeValueSafe("name"),xml->getAttributeValueAsInt("id")))->Load(xml->getAttributeValueSafe("file")))
					//	error("  Reading texture with id='%d' from file='%s' failed!\n",xml->getAttributeValueAsInt("id"),xml->getAttributeValueSafe("file"));
				}
			}
		}
	}
	else fatal("  Cannot find %s!",xmlfile);

	delete xml;

	//Read any additional textures images (JACOB)
	message("  Hoping to find some more textures to use...");

	char* format[] = {"PNG","TGA","JPG","BMP"};
	char* path[] = {"Textures\\*.png","Textures\\*.tga","Textures\\*.jpg","Textures\\*.bmp"};
	std::string name = "";
	std::string filename = "";
	bool exists;
	intptr_t handle;
	_finddata_t found;

	for(int i=0; i<sizeof(path)/sizeof(char*); i++)
	{
		if((handle=_findfirst(path[i],&found))!=-1)
		{
			exists = false;
			filename = found.name;
			name = filename.substr(0,filename.find_last_of('.'));
			filename = "Textures\\"+filename;

			for(unsigned i=0; i<textures.size(); i++)
			{
				if(textures[i]->file==filename) exists = true;
			}

			if(!exists)
			{
				textures.push_back(std::link<Texture>(new Texture(),name,textures.size()));
				textures.back()->file = _strdup(filename.c_str());
				//if(!(textures.back()->Load(filename)))
				//	error("  Reading texture with id='%d' from file='%s' failed!\n",textures.back().Id,name.c_str());
			}

			while(!_findnext(handle,&found))
			{
				exists = false;
				filename = found.name;
				name = filename.substr(0,filename.find_last_of('.'));
				filename = "Textures\\"+filename;

				for(unsigned i=0; i<textures.size(); i++)
				{
					if(textures[i]->file==filename) exists = true;
				}

				if(!exists)
				{
					textures.push_back(std::link<Texture>(new Texture(),name,textures.size()));
					textures.back()->file = _strdup(filename.c_str());
					//if(!(textures.back()->Load(filename)))
					//	error("  Reading texture with id='%d' from file='%s' failed!\n",textures.back().Id,name.c_str());
				}
			}

			_findclose(handle);
		}
		//else if(errno == ENOENT) message("  No %s image textures found.",format[i]);
		else if(errno != ENOENT) error("  Unspecified file search error! Stopped on: %s image, filter: %s",format[i],path[i]);
	}

	if(name!=filename) message("  YES! Loaded some additional textures! (It's for you, Jacob.)");

	return true;
}

bool GameObjectManager::LoadAllObjects(char* xmlfile)
{
	IrrXMLReader* xml = createIrrXMLReader(xmlfile);

	if(xml && xml->read())
	{
		if(!strcmp(xml->getNodeName(),"Objects"))
		{
			if(objects.capacity()<(unsigned)xml->getAttributeValueAsInt("count"))
				objects.resize(xml->getAttributeValueAsInt("count"),nullptr);

			while(xml->read() && (xml->getNodeType() != EXN_ELEMENT_END))
			{
				if(!strcmp(xml->getNodeName(),"Object"))
				{
					if(!(objects.at(xml->getAttributeValueAsInt("id")) = std::link<Object>(new Object(),xml->getAttributeValueSafe("name"),xml->getAttributeValueAsInt("id"))))
						error("  Reading object with id='%d' and name='%s' failed! \n",xml->getAttributeValueAsInt("id"),xml->getAttributeValueSafe("name"));

					std::link<Object>& lastObj = objects.at(xml->getAttributeValueAsInt("id"));
					while(xml->read() && (xml->getNodeType() != EXN_ELEMENT_END))
					{
						if(!strcmp(xml->getNodeName(),"Animation"))
						{
							lastObj->GetAnimVecRef().push_back(std::link<Animation>(new Animation(GetTextureByID(xml->getAttributeValueAsInt("texture")),xml->getAttributeValueAsInt("framecount"),xml->getAttributeValueAsFloat("framespeed")),xml->getAttributeValueSafe("name"),xml->getAttributeValueAsInt("id")));
						}
					}
				}
			}
		}
	}
	else fatal("  Cannot find %s!",xmlfile);

	delete xml;

	return true;
}

bool GameObjectManager::LoadAllItems(char* xmlfile)
{
	return true; //We've got a lot items in our stock, but we're too sleazy to load them...
}

bool GameObjectManager::LoadAllCreatures(char* xmlfile)
{
	return true; //We've got a lot creatures in our stock, but we're too sleazy to load them...
}

bool GameObjectManager::LoadAllMaps(char* xmlfile)
{
	IrrXMLReader* xml = createIrrXMLReader(xmlfile);

	if(xml && xml->read())
	{
		if(!strcmp(xml->getNodeName(),"Maps"))
		{
			if(maps.capacity()<(unsigned)xml->getAttributeValueAsInt("count"))
				maps.resize(xml->getAttributeValueAsInt("count"),nullptr);

			while(xml->read() && (xml->getNodeType() != EXN_ELEMENT_END))
			{
				if(!strcmp(xml->getNodeName(),"Map"))
				{
					if(!(maps.at(xml->getAttributeValueAsInt("id")) = std::link<Map>(new Map(xml->getAttributeValueAsInt("w"),xml->getAttributeValueAsInt("h")),xml->getAttributeValueSafe("name"),xml->getAttributeValueAsInt("id"))))
						error("  Reading map with id='%d' and name='%s' failed! \n",xml->getAttributeValueAsInt("id"),xml->getAttributeValueSafe("name"));

					std::link<Map>& lastMap = maps.at(xml->getAttributeValueAsInt("id"));

					std::string tilemap(xmlfile);
					tilemap = tilemap.substr(0,tilemap.find_last_of('\\')+1).append("tilemaps\\").append(xml->getAttributeValueSafe("name")).append(".tmap");

					std::ifstream tiles(tilemap, std::ios::binary);
					if(tiles.is_open())
					{
						Kafelek* kafelki = lastMap->GetKafelkiPtr();

						tiles.read((char*)kafelki,lastMap->GetWidth()*lastMap->GetHeight()*sizeof(Kafelek));
						tiles.close();

						lastMap->SetKafelkiPtr(kafelki);
					}
					else error("  Can't load map: %s!",tilemap.c_str());

					while(xml->read() && (xml->getNodeType() != EXN_ELEMENT_END))
					{
						if(!strcmp(xml->getNodeName(),"Objects"))
						{
							if(lastMap->GetObjectVecRef().capacity()<(unsigned)xml->getAttributeValueAsInt("count"))
								lastMap->GetObjectVecRef().reserve(xml->getAttributeValueAsInt("count"));

							while(xml->read() && (xml->getNodeType() != EXN_ELEMENT_END))
							{
								if(!strcmp(xml->getNodeName(),"Object"))
								{
									lastMap->GetObjectVecRef().push_back(CopyObjectByID(xml->getAttributeValueAsInt("id")));

									std::link<Object>& lastObj = lastMap->GetObjectVecRef().back();
									lastObj->Set(xml->getAttributeValueAsFloat("x"),xml->getAttributeValueAsFloat("y"),xml->getAttributeValueAsFloat("scale"));
								
									while(xml->read() && (xml->getNodeType() != EXN_ELEMENT_END))
									{
										if(!strcmp(xml->getNodeName(),"Animation"))
										{
											if(lastObj->GetAnimVecRef().capacity()<(unsigned)xml->getAttributeValueAsInt("id")+1)
												lastObj->GetAnimVecRef().resize(xml->getAttributeValueAsInt("id")+1);

											delete lastObj->GetAnimVecRef().at(xml->getAttributeValueAsInt("id"));
											lastObj->GetAnimVecRef().at(xml->getAttributeValueAsInt("id")) = std::link<Animation>(new Animation(GetTextureByID(xml->getAttributeValueAsInt("texture")),xml->getAttributeValueAsInt("framecount"),xml->getAttributeValueAsFloat("framespeed")),xml->getAttributeValueSafe("name"),xml->getAttributeValueAsInt("id"));
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else fatal("  Cannot find %s!",xmlfile);

	delete xml;

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GameObjectManager::SaveAllTextures(char* xmlfile)
{
	std::ofstream xml(xmlfile, std::ios::trunc);

	xml << "<Textures count=\"" << textures.size() << "\">" << std::endl;
	for(unsigned i=0; i<textures.size(); i++)
	{
		xml << "  <Texture id=\"" << textures[i].Id
			<< "\" file=\"" << textures[i]->file
			<< "\" name=\"" << textures[i].Name
			<< "\" />" << std::endl;
	}
	xml << "</Textures>" << std::endl;

	xml.close();

	return true;
}

bool GameObjectManager::SaveAllObjects(char* xmlfile)
{
	std::ofstream xml(xmlfile, std::ios::trunc);

	xml << "<Objects count=\"" << objects.size() << "\">" << std::endl;
	for(unsigned i=0; i<objects.size(); i++)
	{
		xml << "  <Object id=\"" << objects[i].Id << "\" name=\"" << objects[i].Name << "\">" << std::endl;
		
		const std::vector<std::link<Animation>>& anim = objects[i]->GetAnimVecRef();
		for(unsigned j=0; j<anim.size(); j++)
		{
			xml << "    <Animation id=\"" << anim[j].Id
			<< "\" texture=\"" << anim[j]->GetTexture().Id
			<< "\" framecount=\"" << anim[j]->GetFrameCount()
			<< "\" framespeed=\"" << anim[j]->GetFrameSpeed()
			<< "\" name=\"" << anim[j].Name
			<< "\" />" << std::endl;
		}
		xml << "  </Object>" << std::endl;
	}
	xml << "</Objects>" << std::endl;

	xml.close();

	return true;
}

bool GameObjectManager::SaveAllItems(char* xmlfile)
{
	return true;
}

bool GameObjectManager::SaveAllCreatures(char* xmlfile)
{
	return true;
}

bool GameObjectManager::SaveAllMaps(char* xmlfile)
{
	std::ofstream xml(xmlfile, std::ios::trunc);

	xml << "<Maps count=\"" << maps.size() << "\">" << std::endl;

	for(unsigned i=0; i<maps.size(); i++)
	{
		xml << "  <Map id=\"" << maps[i].Id
			<< "\" w=\"" << maps[i]->GetWidth()
			<< "\" h=\"" << maps[i]->GetHeight()
			<< "\" name=\"" << maps[i].Name
			<< "\">" << std::endl;

		std::string tilemap(xmlfile);
		tilemap = tilemap.substr(0,tilemap.find_last_of('\\')+1).append("tilemaps\\").append(maps[i].Name).append(".tmap");

		std::ofstream tiles(tilemap, std::ios::binary);
		if(tiles.is_open())
		{
			Kafelek* kafelki = maps[i]->GetKafelkiPtr();

			tiles.write((char*)kafelki,maps[i]->GetWidth()*maps[i]->GetHeight()*sizeof(Kafelek));
			tiles.close();
		}
		
		const std::vector<std::link<Object>>& obj = maps[i]->GetObjectVecRef();
		xml << "    <Objects count=\"" << obj.size() << (obj.size()?"\">":"\" />") << std::endl;
		for(unsigned j=0; j<obj.size(); j++)
		{
			xml << "      <Object id=\"" << obj[j].Id
				<< "\" x=\"" << obj[j]->GetX()
				<< "\" y=\"" << obj[j]->GetY()
				<< "\" scale=\"" << obj[j]->GetScale()
				<< "\">" << std::endl;

			const std::vector<std::link<Animation>>& anim = obj[j]->GetAnimVecRef();
			for(unsigned k=0; k<anim.size(); k++)
			{
				if(anim[k].Id > -1)
					xml << "        <Animation id=\"" << anim[k].Id
						<< "\" texture=\"" << anim[k]->GetTexture().Id
						<< "\" framecount=\"" << anim[k]->GetFrameCount()
						<< "\" framespeed=\"" << anim[k]->GetFrameSpeed()
						<< "\" name=\"" << anim[k].Name
						<< "\" />" << std::endl;
			}
			xml << "      </Object>" << std::endl;
		}
		if(obj.size()) xml << "    </Objects>" << std::endl;

		xml << "  </Map>" << std::endl;
	}
	xml << "</Maps>" << std::endl;

	xml.close();

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Texture* GameObjectManager::LoadTextureByID(unsigned id)
//{
//	message("WARNING! Dynamic loading not implemented yet!");
//	return new Texture();
//}
//
//Object* GameObjectManager::LoadObjectByID(unsigned id)
//{
//	message("WARNING! Dynamic loading not implemented yet!");
//	return new Object();
//}
//
//Item* GameObjectManager::LoadItemByID(unsigned id)
//{
//	message("WARNING! Dynamic loading not implemented yet!");
//	return new Item();
//}
//
//Creature* GameObjectManager::LoadCreatureByID(unsigned id)
//{
//	message("WARNING! Dynamic loading not implemented yet!");
//	return new Creature();
//}
//
//Map* GameObjectManager::LoadMapByID(unsigned id)
//{
//	message("WARNING! Dynamic loading not implemented yet!");
//	return new Map(0);
//}
