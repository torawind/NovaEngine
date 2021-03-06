﻿/***************************************************************************
 *   Copyright (C) 2009 by Sirius										   *
 *	 Vdov Nikita Sergeevich	(c)											   *
 *	 siriusnick@gmail.com												   *
 *																		   *
 *	 This source file is part of NovaEngine								   *
 *	 (Object-oriented Game Development Engine)							   *
 *																		   *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program;					                           *
 ***************************************************************************/
#pragma once

#include "nova_mesh_box.h"
#include "nova_gzstreams.h"
#include "nova_color.h"
#include "nova_material.h"

namespace nova
{

class NOVA_EXPORT CMeshLoader : public CObjectConstructor
{
protected:

public:

	CMeshLoader();
	virtual ~CMeshLoader();

	virtual stl<CMeshBoxPtr>::vector LoadMeshList(void) = 0;

	virtual stl<CMaterialPtr>::vector LoadMaterialList(void) = 0;
};

class NOVA_EXPORT CMeshLoaderFactory : public CObjectConstructor
{
public:
	
	CMeshLoaderFactory() {}
	~CMeshLoaderFactory() {}

	virtual CMeshLoader *CreateMeshFactory(CDataStream & stream, bool geom, bool mult_thread) = 0;
};

}
