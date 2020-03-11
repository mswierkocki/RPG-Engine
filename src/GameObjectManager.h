#pragma once

#include <vector>
#include "link.hpp"

#include "Texture.h"
#include "Object.h"
#include "Item.h"
#include "Creature.h"
#include "Map.h"
//#include "Quest.h"
#include "Player.h"

class GameObjectManager
{
private:
	std::vector<std::link<Texture>> textures;
	std::vector<std::link<Object>> objects;
	std::vector<std::link<Item>> items;
	std::vector<std::link<Creature>> creatures;
	std::vector<std::link<Map>> maps;
	//std::vector<Quest*> quests;
	Player* playerAvatar;

public:
	GameObjectManager();
	~GameObjectManager();

	std::vector<std::link<Texture>>& GetTextureVecRef() { return textures; }
	const std::link<Texture>& GetTextureByID(unsigned id);
	const std::link<Texture>& GetTextureByName(const std::string& name);
	std::link<Texture> CopyTextureByID(unsigned id); //Actually makes no sense.
	const std::link<Texture>& AddNewTexture(Texture* texture, const std::string& name);
	bool RemoveTextureByID(unsigned id);
	//Texture* LoadTextureByID(unsigned id);
	bool LoadAllTextures(char* xmlfile = "Content\\textures.xml");
	bool SaveAllTextures(char* xmlfile = "Content\\Autosave\\textures.xml");

	std::vector<std::link<Object>>& GetObjectVecRef() { return objects; }
	const std::link<Object>& GetObjectByID(unsigned id);
	const std::link<Object>& GetObjectByName(const std::string& name);
	std::link<Object> CopyObjectByID(unsigned id);
	const std::link<Object>& AddNewObject(Object* object, const std::string& name);
	bool RemoveObjectByID(unsigned id);
	//Object* LoadObjectByID(unsigned id);
	bool LoadAllObjects(char* xmlfile = "Content\\objects.xml");
	bool SaveAllObjects(char* xmlfile = "Content\\Autosave\\objects.xml");

	std::vector<std::link<Item>>& GetItemVecRef() { return items; }
	const std::link<Item>& GetItemByID(unsigned id);
	const std::link<Item>& GetItemByName(const std::string& name);
	std::link<Item> CopyItemByID(unsigned id);
	const std::link<Item>& AddNewItem(Item* item, const std::string& name);
	bool RemoveItemByID(unsigned id);
	//Item* LoadItemByID(unsigned id);
	bool LoadAllItems(char* xmlfile = "Content\\items.xml");
	bool SaveAllItems(char* xmlfile = "Content\\Autosave\\items.xml");

	std::vector<std::link<Creature>>& GetCreatureVecRef() { return creatures; }
	const std::link<Creature>& GetCreatureByID(unsigned id);
	const std::link<Creature>& GetCreatureByName(const std::string& name);
	std::link<Creature> CopyCreatureByID(unsigned id);
	const std::link<Creature>& AddNewCreature(Creature* creature, const std::string& name);
	bool RemoveCreatureByID(unsigned id);
	//Creature* LoadCreatureByID(unsigned id);
	bool LoadAllCreatures(char* xmlfile = "Content\\creatures.xml");
	bool SaveAllCreatures(char* xmlfile = "Content\\Autosave\\creatures.xml");

	std::vector<std::link<Map>>& GetMapVecRef() { return maps; }
	const std::link<Map>& GetMapByID(unsigned id);
	const std::link<Map>& GetMapByName(const std::string& name);
	std::link<Map> CopyMapByID(unsigned id); //Also makes no sense.
	const std::link<Map>& AddNewMap(Map* map, const std::string& name);
	bool RemoveMapByID(unsigned id);
	//Map* LoadMapByID(unsigned id);
	bool LoadAllMaps(char* xmlfile = "Content\\maps.xml");
	bool SaveAllMaps(char* xmlfile = "Content\\Autosave\\maps.xml");

	//std::vector<Quest*>& GetQuestsVecRef() { return quests; }
	//Quest* GetQuestByID(unsigned id);
	//Quest* LoadQuestByID(unsigned id);
	//bool LoadAllQuests();
};
