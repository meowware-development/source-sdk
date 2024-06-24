#pragma once
#include "../../math/matrix.hpp"

struct Material;

struct MaterialVar {
	virtual void* GetTextureValue(void) = 0;

	virtual char const* GetName(void) const = 0;
	virtual unsigned short	GetNameAsSymbol() const = 0;

	virtual void			SetFloatValue(float val) = 0;

	virtual void			SetIntValue(int val) = 0;

	virtual void			SetStringValue(char const* val) = 0;
	virtual char const* GetStringValue(void) const = 0;

	// Use FourCC values to pass app-defined data structures between
	// the proxy and the shader. The shader should ignore the data if
	// its FourCC type not correct.	
	virtual void			SetFourCCValue(unsigned long type, void* pData) = 0;
	virtual void			GetFourCCValue(unsigned long* type, void** ppData) = 0;

	// Vec (dim 2-4)
	virtual void			SetVecValue(float const* val, int numcomps) = 0;
	virtual void			SetVecValue(float x, float y) = 0;
	virtual void			SetVecValue(float x, float y, float z) = 0;
	virtual void			SetVecValue(float x, float y, float z, float w) = 0;
	virtual void			GetLinearVecValue(float* val, int numcomps) const = 0;

	// revisit: is this a good interface for textures?
	virtual void			SetTextureValue(void*) = 0;

	virtual Material* GetMaterialValue(void) = 0;
	virtual void			SetMaterialValue(Material*) = 0;

	virtual bool			IsDefined() const = 0;
	virtual void			SetUndefined() = 0;

	// Matrix
	virtual void			SetMatrixValue(Matrix4x4 const& matrix) = 0;
	virtual const Matrix4x4& GetMatrixValue() = 0;
	virtual bool			MatrixIsIdentity() const = 0;

	// Copy....
	virtual void			CopyFrom(MaterialVar* pMaterialVar) = 0;

	virtual void			SetValueAutodetectType(char const* val) = 0;

	virtual Material* GetOwningMaterial() = 0;

	//set just 1 component
	virtual void			SetVecComponentValue(float fVal, int nComponent) = 0;

protected:
	virtual int				GetIntValueInternal(void) const = 0;
	virtual float			GetFloatValueInternal(void) const = 0;
	virtual float const* GetVecValueInternal() const = 0;
	virtual void			GetVecValueInternal(float* val, int numcomps) const = 0;
	virtual int				VectorSizeInternal() const = 0;
};