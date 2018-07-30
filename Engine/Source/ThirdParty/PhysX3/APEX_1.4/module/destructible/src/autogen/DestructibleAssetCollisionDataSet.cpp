// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2017 NVIDIA Corporation. All rights reserved.

// This file was generated by NvParameterized/scripts/GenParameterized.pl


#include "DestructibleAssetCollisionDataSet.h"
#include <string.h>
#include <stdlib.h>

using namespace NvParameterized;

namespace nvidia
{
namespace destructible
{

using namespace DestructibleAssetCollisionDataSetNS;

const char* const DestructibleAssetCollisionDataSetFactory::vptr =
    NvParameterized::getVptr<DestructibleAssetCollisionDataSet, DestructibleAssetCollisionDataSet::ClassAlignment>();

const uint32_t NumParamDefs = 8;
static NvParameterized::DefinitionImpl* ParamDefTable; // now allocated in buildTree [NumParamDefs];


static const size_t ParamLookupChildrenTable[] =
{
	1, 2, 3, 4, 6, 5, 7,
};

#define TENUM(type) nvidia::##type
#define CHILDREN(index) &ParamLookupChildrenTable[index]
static const NvParameterized::ParamLookupNode ParamLookupTable[NumParamDefs] =
{
	{ TYPE_STRUCT, false, 0, CHILDREN(0), 5 },
	{ TYPE_STRING, false, (size_t)(&((ParametersStruct*)0)->assetName), NULL, 0 }, // assetName
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->cookingPlatform), NULL, 0 }, // cookingPlatform
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->cookingVersionNum), NULL, 0 }, // cookingVersionNum
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->scales), CHILDREN(5), 1 }, // scales
	{ TYPE_VEC3, false, 1 * sizeof(physx::PxVec3), NULL, 0 }, // scales[]
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->meshCookedCollisionStreamsAtScale), CHILDREN(6), 1 }, // meshCookedCollisionStreamsAtScale
	{ TYPE_REF, false, 1 * sizeof(NvParameterized::Interface*), NULL, 0 }, // meshCookedCollisionStreamsAtScale[]
};


bool DestructibleAssetCollisionDataSet::mBuiltFlag = false;
NvParameterized::MutexType DestructibleAssetCollisionDataSet::mBuiltFlagMutex;

DestructibleAssetCollisionDataSet::DestructibleAssetCollisionDataSet(NvParameterized::Traits* traits, void* buf, int32_t* refCount) :
	NvParameters(traits, buf, refCount)
{
	//mParameterizedTraits->registerFactory(className(), &DestructibleAssetCollisionDataSetFactoryInst);

	if (!buf) //Do not init data if it is inplace-deserialized
	{
		initDynamicArrays();
		initStrings();
		initReferences();
		initDefaults();
	}
}

DestructibleAssetCollisionDataSet::~DestructibleAssetCollisionDataSet()
{
	freeStrings();
	freeReferences();
	freeDynamicArrays();
}

void DestructibleAssetCollisionDataSet::destroy()
{
	// We cache these fields here to avoid overwrite in destructor
	bool doDeallocateSelf = mDoDeallocateSelf;
	NvParameterized::Traits* traits = mParameterizedTraits;
	int32_t* refCount = mRefCount;
	void* buf = mBuffer;

	this->~DestructibleAssetCollisionDataSet();

	NvParameters::destroy(this, traits, doDeallocateSelf, refCount, buf);
}

const NvParameterized::DefinitionImpl* DestructibleAssetCollisionDataSet::getParameterDefinitionTree(void)
{
	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

const NvParameterized::DefinitionImpl* DestructibleAssetCollisionDataSet::getParameterDefinitionTree(void) const
{
	DestructibleAssetCollisionDataSet* tmpParam = const_cast<DestructibleAssetCollisionDataSet*>(this);

	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			tmpParam->buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

NvParameterized::ErrorType DestructibleAssetCollisionDataSet::getParameterHandle(const char* long_name, Handle& handle) const
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

NvParameterized::ErrorType DestructibleAssetCollisionDataSet::getParameterHandle(const char* long_name, Handle& handle)
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

void DestructibleAssetCollisionDataSet::getVarPtr(const Handle& handle, void*& ptr, size_t& offset) const
{
	ptr = getVarPtrHelper(&ParamLookupTable[0], const_cast<DestructibleAssetCollisionDataSet::ParametersStruct*>(&parameters()), handle, offset);
}


/* Dynamic Handle Indices */
/* [0] - meshCookedCollisionStreamsAtScale (not an array of structs) */

void DestructibleAssetCollisionDataSet::freeParameterDefinitionTable(NvParameterized::Traits* traits)
{
	if (!traits)
	{
		return;
	}

	if (!mBuiltFlag) // Double-checked lock
	{
		return;
	}

	NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);

	if (!mBuiltFlag)
	{
		return;
	}

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		ParamDefTable[i].~DefinitionImpl();
	}

	traits->free(ParamDefTable);

	mBuiltFlag = false;
}

#define PDEF_PTR(index) (&ParamDefTable[index])

void DestructibleAssetCollisionDataSet::buildTree(void)
{

	uint32_t allocSize = sizeof(NvParameterized::DefinitionImpl) * NumParamDefs;
	ParamDefTable = (NvParameterized::DefinitionImpl*)(mParameterizedTraits->alloc(allocSize));
	memset(ParamDefTable, 0, allocSize);

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		NV_PARAM_PLACEMENT_NEW(ParamDefTable + i, NvParameterized::DefinitionImpl)(*mParameterizedTraits);
	}

	// Initialize DefinitionImpl node: nodeIndex=0, longName=""
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[0];
		ParamDef->init("", TYPE_STRUCT, "STRUCT", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=1, longName="assetName"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[1];
		ParamDef->init("assetName", TYPE_STRING, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "The name of the asset for which convex hulls are cooked.\n					A convex hull may be cooked for each chunk in the asset, for each scale in the\n					scales array.", true);
		HintTable[1].init("shortDescription", "The name of the asset for which convex hulls are cooked", true);
		ParamDefTable[1].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=2, longName="cookingPlatform"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[2];
		ParamDef->init("cookingPlatform", TYPE_U32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "The cooking platform for convex cooking.  Currently unused.", true);
		HintTable[1].init("shortDescription", "Currently unused", true);
		ParamDefTable[2].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=3, longName="cookingVersionNum"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[3];
		ParamDef->init("cookingVersionNum", TYPE_U32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "A version number for convex cooking.  Currently unused.", true);
		HintTable[1].init("shortDescription", "Currently unused", true);
		ParamDefTable[3].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=4, longName="scales"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[4];
		ParamDef->init("scales", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "An array of scales at which chunks in the asset are cooked.\n					The size of the outer array of meshCookedCollisionStreamsAtScale\n					and scales must be equal.", true);
		HintTable[1].init("shortDescription", "An array of scales at which chunks in the asset are cooked", true);
		ParamDefTable[4].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */




		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=5, longName="scales[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[5];
		ParamDef->init("scales", TYPE_VEC3, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "An array of scales at which chunks in the asset are cooked.\n					The size of the outer array of meshCookedCollisionStreamsAtScale\n					and scales must be equal.", true);
		HintTable[1].init("shortDescription", "An array of scales at which chunks in the asset are cooked", true);
		ParamDefTable[5].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=6, longName="meshCookedCollisionStreamsAtScale"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[6];
		ParamDef->init("meshCookedCollisionStreamsAtScale", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("INCLUDED", uint64_t(1), true);
		ParamDefTable[6].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[3];
		static Hint* HintPtrTable[3] = { &HintTable[0], &HintTable[1], &HintTable[2], };
		HintTable[0].init("INCLUDED", uint64_t(1), true);
		HintTable[1].init("longDescription", "An array of arrays of collision hull byte streams.\n					The outer array corresponds to different scales (given in the scales array).\n					The inner array corresponds to different chunks within the asset.\n					The size of the outer array of meshCookedCollisionStreamsAtScale\n					and scales must be equal.", true);
		HintTable[2].init("shortDescription", "An array of arrays of collision hull byte streams", true);
		ParamDefTable[6].setHints((const NvParameterized::Hint**)HintPtrTable, 3);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */


		static const char* const RefVariantVals[] = { "MeshCookedCollisionStreamsAtScale" };
		ParamDefTable[6].setRefVariantVals((const char**)RefVariantVals, 1);


		ParamDef->setArraySize(-1);
		static const uint8_t dynHandleIndices[1] = { 0, };
		ParamDef->setDynamicHandleIndicesMap(dynHandleIndices, 1);

	}

	// Initialize DefinitionImpl node: nodeIndex=7, longName="meshCookedCollisionStreamsAtScale[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[7];
		ParamDef->init("meshCookedCollisionStreamsAtScale", TYPE_REF, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("INCLUDED", uint64_t(1), true);
		ParamDefTable[7].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[3];
		static Hint* HintPtrTable[3] = { &HintTable[0], &HintTable[1], &HintTable[2], };
		HintTable[0].init("INCLUDED", uint64_t(1), true);
		HintTable[1].init("longDescription", "An array of arrays of collision hull byte streams.\n					The outer array corresponds to different scales (given in the scales array).\n					The inner array corresponds to different chunks within the asset.\n					The size of the outer array of meshCookedCollisionStreamsAtScale\n					and scales must be equal.", true);
		HintTable[2].init("shortDescription", "An array of arrays of collision hull byte streams", true);
		ParamDefTable[7].setHints((const NvParameterized::Hint**)HintPtrTable, 3);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */


		static const char* const RefVariantVals[] = { "MeshCookedCollisionStreamsAtScale" };
		ParamDefTable[7].setRefVariantVals((const char**)RefVariantVals, 1);



	}

	// SetChildren for: nodeIndex=0, longName=""
	{
		static Definition* Children[5];
		Children[0] = PDEF_PTR(1);
		Children[1] = PDEF_PTR(2);
		Children[2] = PDEF_PTR(3);
		Children[3] = PDEF_PTR(4);
		Children[4] = PDEF_PTR(6);

		ParamDefTable[0].setChildren(Children, 5);
	}

	// SetChildren for: nodeIndex=4, longName="scales"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(5);

		ParamDefTable[4].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=6, longName="meshCookedCollisionStreamsAtScale"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(7);

		ParamDefTable[6].setChildren(Children, 1);
	}

	mBuiltFlag = true;

}
void DestructibleAssetCollisionDataSet::initStrings(void)
{
	assetName.isAllocated = true;
	assetName.buf = NULL;
}

void DestructibleAssetCollisionDataSet::initDynamicArrays(void)
{
	scales.buf = NULL;
	scales.isAllocated = true;
	scales.elementSize = sizeof(physx::PxVec3);
	scales.arraySizes[0] = 0;
	meshCookedCollisionStreamsAtScale.buf = NULL;
	meshCookedCollisionStreamsAtScale.isAllocated = true;
	meshCookedCollisionStreamsAtScale.elementSize = sizeof(NvParameterized::Interface*);
	meshCookedCollisionStreamsAtScale.arraySizes[0] = 0;
}

void DestructibleAssetCollisionDataSet::initDefaults(void)
{

	freeStrings();
	freeReferences();
	freeDynamicArrays();
	cookingPlatform = uint32_t(UINT32_MAX);
	cookingVersionNum = uint32_t(0);

	initDynamicArrays();
	initStrings();
	initReferences();
}

void DestructibleAssetCollisionDataSet::initReferences(void)
{
}

void DestructibleAssetCollisionDataSet::freeDynamicArrays(void)
{
	if (scales.isAllocated && scales.buf)
	{
		mParameterizedTraits->free(scales.buf);
	}
	if (meshCookedCollisionStreamsAtScale.isAllocated && meshCookedCollisionStreamsAtScale.buf)
	{
		mParameterizedTraits->free(meshCookedCollisionStreamsAtScale.buf);
	}
}

void DestructibleAssetCollisionDataSet::freeStrings(void)
{

	if (assetName.isAllocated && assetName.buf)
	{
		mParameterizedTraits->strfree((char*)assetName.buf);
	}
}

void DestructibleAssetCollisionDataSet::freeReferences(void)
{

	for (int i = 0; i < meshCookedCollisionStreamsAtScale.arraySizes[0]; ++i)
	{
		if (meshCookedCollisionStreamsAtScale.buf[i])
		{
			meshCookedCollisionStreamsAtScale.buf[i]->destroy();
		}
	}
}

} // namespace destructible
} // namespace nvidia
