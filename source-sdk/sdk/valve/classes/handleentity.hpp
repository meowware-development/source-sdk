#pragma once
#include "../enums/sourcedefs.hpp"

class HandleEntity
{
public:
	virtual ~HandleEntity() {}
	virtual void SetRefEHandle(const EHANDLE& handle) = 0;
	virtual const EHANDLE& GetRefEHandle() const = 0;
};