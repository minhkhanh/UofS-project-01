#pragma once

#include "0812223-0812239.h"
#include "cDef.h"
#include "Functions.h"
#include "GameKeys.h"
#include "stdafx.h"

#include "TypeAObject.h"

class TypeAObject;
class TypeAMonster;

class TypeAMonster :	public TypeAObject
{
public:
	TypeAMonster(void);
	virtual ~TypeAMonster(void);
};
