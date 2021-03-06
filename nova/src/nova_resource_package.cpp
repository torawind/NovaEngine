/***************************************************************************
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
#include "nova_stable_precompiled_headers.h"

#include "nova_resource_package.h"

#define NPK_MAIN_SIGNATURE			0x10AF00DF
#define NPK_VERSION(major,minor)	(nova::uint)(((nova::word)major & 0xffff) | ((((nova::uint)minor) & 0xffff) << 16))
#define NPK_SECOND_SIGNATURE(x)		(nova::uint)((nova::uint)x & NPK_MAIN_SIGNATURE)

namespace nova
{

#define NPK_VERSION_1_0				NPK_VERSION(1, 0)


CFilesPackage::CFilesPackage() : mFile(NULL), mIsOpened(false), 
	mWritePackage(false), mSelfOpen(false), mVersion(0), CBase("CFilesPackage")
{


}

CFilesPackage::~CFilesPackage()
{

}

void CFilesPackage::OpenPackage(const nstring & pkg, bool write)
{
	CGZFileStream *file = new CGZFileStream();

	if(!write)
		dynamic_cast<CGZFileStream *>(file)->Open(pkg, GZ_READ);
	else
		dynamic_cast<CGZFileStream *>(file)->Open(pkg, GZ_WRITE_WITH_COMPRESS_8);

	OpenPackage(file, write);


	mSelfOpen = true;
}

			
void CFilesPackage::OpenPackage(CDataStream *pkgstream, bool write)
{
	if(mIsOpened)
		throw NOVA_EXP("CFilesPackage::OpenPackage: package already opened!", BAD_OPERATION);
	mPackageMap.clear();

	if(!write)
	{
		mFile = pkgstream;

		mFile->Seek(0);
		TPackageHeader header;

		mFile->Read(&header, sizeof(TPackageHeader));

		if(header.m_signature != NPK_MAIN_SIGNATURE)
			throw NOVA_EXP("CFilesPackage::OpenPackage: package unknown main signature!", BAD_OPERATION);
		mVersion = header.version;

		if(mVersion == NPK_VERSION_1_0)
		{
			if(header.v_signature != NPK_SECOND_SIGNATURE(NPK_VERSION_1_0))
				throw NOVA_EXP("CFilesPackage::OpenPackage: package unknown version signature!", BAD_OPERATION);

			mPackageName.append(header.package_name);
			for(nova::uint i = 0; i < header.files_count; i++)
			{
				FileHeader f_header;
				mFile->Read(&f_header, sizeof(FileHeader));

				std::pair<nstring, FileHeader> pf;
				pf.first = nstring(f_header.file_name);
				pf.second = f_header;
				mPackageMap.insert(pf);

				mFile->Skip(f_header.size);

				if(mFile->Eof())
					break;
			}

			mFile->Seek(0);
		}
		else
		{
			/////
			throw NOVA_EXP("CFilesPackage::OpenPackage: package unknown version!", BAD_OPERATION);
		}

		mIsOpened = true;
		mWritePackage = false;
	}
	else
	{
		mIsOpened = false;
		mWritePackage = true;
	}
}

void CFilesPackage::ClosePackage(void)
{
	if(!mIsOpened)
		throw NOVA_EXP("CFilesPackage::ClosePackage: package not opened, open package file first!", BAD_OPERATION);

	mPackageMap.clear();
	if(mSelfOpen && mFile)
	{
		mFile->Close();
		delete mFile;
	}

	mIsOpened = false;
	mWritePackage = false;
	mFile = NULL;
}


nova::stl<nstring>::vector CFilesPackage::GetFileList(void)
{
	nova::stl<nstring>::vector result;
	stl<nstring, FileHeader>::map::iterator it;
	if(!mIsOpened)
		throw NOVA_EXP("CFilesPackage::GetFileList: package not opened, open package file first!", BAD_OPERATION);

	for(it = mPackageMap.begin(); it != mPackageMap.end(); it++)
	{
		result.push_back((*it).first);
	}

	return result;
}

nova::nstring CFilesPackage::GetFileExt(const nstring & name)
{
	stl<nstring, FileHeader>::map::iterator it;
	if(!mIsOpened)
		throw NOVA_EXP("CFilesPackage::GetFileExt: package not opened, open package file first!", BAD_OPERATION);

	if((it = mPackageMap.find(name)) != mPackageMap.end())
		return nstring((*it).second.ext);

	return nstring();
}

CMemoryBuffer CFilesPackage::GetFile(const nstring & name)
{
	stl<nstring, FileHeader>::map::iterator it;
	FileHeader header;
	
	if(!mIsOpened)
		throw NOVA_EXP("CFilesPackage::GetFile: package not opened, open package file first!", BAD_OPERATION);
	if(mWritePackage)
		throw NOVA_EXP("CFilesPackage::GetFile: package opened for writing!", BAD_OPERATION);

	if((it = mPackageMap.find(name)) != mPackageMap.end())
		header = (*it).second;
	else
		return CMemoryBuffer();

	CMemoryBuffer result;
	mFile->Seek(header.pos);

	result.AllocBuffer(header.size);
	mFile->Read(result);

	return result;
}

bool CFilesPackage::IsOpened(void)
{
	return mIsOpened;
}


}