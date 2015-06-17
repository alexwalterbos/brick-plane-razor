#pragma once 

enum Material 
{
	razor = 0,
	plane = 1,
	brick = 2
};

inline bool winsOf(Material att, Material def)
{
	if (att == Material::razor)
		return def == Material::brick;
	if (att == Material::plane)
		return def == Material::razor;
	if (att == Material::brick)
		return def == Material::plane;

	return false;
};
