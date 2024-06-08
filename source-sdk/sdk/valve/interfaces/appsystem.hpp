#pragma once

class AppSystem {
public:
	virtual bool Connect(void* createFunction) = 0;
	virtual void Disconnect() = 0;
	virtual void* QueryInterface(const char* interfaceName) = 0;
	virtual int Init() = 0;
	virtual void Shutdown() = 0;
};