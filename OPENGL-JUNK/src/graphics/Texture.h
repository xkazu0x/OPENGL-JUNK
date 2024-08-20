#pragma once

#include "../Config.h"

class Texture {
public:
	Texture(const char* path, const char* name);

	void Generate();
	void Load(bool flip = true);

	void Bind();

public:
	int m_id = 0;
	unsigned int m_texture = 0;
	const char* m_name = "";

private:
	static int m_currentId;
	const char* m_path = "";
	int m_width = 0;
	int m_height = 0;
	int m_channels = 0;
};
