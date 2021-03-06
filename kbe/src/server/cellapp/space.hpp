/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2012 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __SPACE_HPP__
#define __SPACE_HPP__

#include "cell.hpp"
#include "helper/debug_helper.hpp"
#include "cstdkbe/cstdkbe.hpp"
#include "cstdkbe/smartpointer.hpp"


namespace KBEngine{

class Entity;
typedef SmartPointer<Entity> EntityPtr;
typedef std::vector<EntityPtr> SPACE_ENTITIES;

class Space
{
public:
	Space(SPACE_ID spaceID);
	~Space();

	void loadSpaceGeometry(const char* path);

	void creatorID(ENTITY_ID id){ creatorID_ = id; }
	ENTITY_ID creatorID()const { return creatorID_; }

	/** 
		更新space中的内容 
	*/
	void update();

	void addEntity(Entity* pEntity);
	void removeEntity(Entity* pEntity);

	/**
		一个entity进入了游戏世界
	*/
	void onEnterWorld(Entity* pEntity);
	void _onEnterWorld(Entity* pEntity);
	void onLeaveWorld(Entity* pEntity);
	
	/**
		获得某个entityAOI范围内的所有entity
	*/
	void getAOIEntities(Entity* pEntity, SPACE_ENTITIES& aoiEntitys);

	/**
		广播当前aoi范围内的entity到当前entity的客户端
	*/
	void broadcastAOIEntitiesToEntity(Entity* pEntity);

	/**
		广播当前entity到其他entity的客户端
	*/
	void broadcastEntityToAOIEntities(Entity* pEntity, SPACE_ENTITIES& aoiEntitys);

	void onEntityAttachWitness(Entity* pEntity);

	SPACE_ID getID()const{ return id_; }

	const SPACE_ENTITIES& entities()const{ return entities_; }

	/**
		销毁
	*/
	bool destroy(ENTITY_ID entityID);

	/**
		这个space的cell
	*/
	Cell * pCell() const	{ return pCell_; }
	void pCell( Cell * pCell );
protected:
	// 这个space的ID
	SPACE_ID id_;	

	// 创造者ID 一般来说就是spaceEntity的ID
	ENTITY_ID creatorID_;								

	// 这个space上的entity
	SPACE_ENTITIES entities_;							

	// 是否加载过地形数据
	bool isLoadGeometry_;

	// 加载几何的路径
	std::string loadGeometryPathName_;					
	
	// 每个space最多只有一个cell
	Cell* pCell_;
};


}
#endif
