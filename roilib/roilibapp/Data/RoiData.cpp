#include "StdAfx.h"
#include "MainFrm.h"
#include "RoiData.h"
#include "Utils/Direct_Info.h"
#include "Utils/Utils.h"

CRoiData::CRoiData(void)
{
	theApp.m_nSelectCh = theApp.m_nSelectCh;
}

CRoiData::~CRoiData(void)
{
}

int CRoiData::AddParam(CParam param)
{
	m_vecParams.push_back(param);
	return 0;
}

BOOL CRoiData::IsRegWorkList(CString sName)
{

	int size = g_cRecipeData->m_vecWorkRoiData[m_nCh].size();
	for (int i = 0; i < size; i++){
		CString name = g_cRecipeData->m_vecWorkRoiData[m_nCh][i]->m_sName;
		if (name == sName)
			return TRUE;
	}
	return FALSE;
}

CParam* CRoiData::getParam(CString sName)
{
	int size = m_vecParams.size();
	for (int i = 0; i < size; i++)
	{
		if (_tcscmp(sName, m_vecParams[i].Name.c_str()) == 0)
		{
			return &m_vecParams[i];
		}
	}
	return NULL;
}

BOOL	CRoiData::LoadImageData(CString path)
{
	CString sFileName;
	extern CDirect_Info * g_pDirectory;
	sFileName.Format(_T("%s"), path);
	if(g_pDirectory->Search_FileName(sFileName)){
		if (iplTemplate){
			cvReleaseImage(&iplTemplate);
			iplTemplate = NULL;
		}
		CT2A ascii(sFileName);
		iplTemplate = cvLoadImage(ascii,0);

	}
	return TRUE;
}

BOOL	CRoiData::SaveImageData(CString path)
{
	if (iplTemplate != NULL)
	{
		CT2A ascii(path); cvSaveImage(ascii, iplTemplate);
	}
	return TRUE;
}
