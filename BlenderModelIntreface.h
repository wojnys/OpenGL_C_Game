#pragma once

// Product class

#include <string>

class BlenderModelIntreface
{
public:
	virtual void load(std::string filename) = 0;
	//virtual void render() = 0;
	virtual ~BlenderModelIntreface() = default;
};

