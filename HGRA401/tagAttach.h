#pragma once
#include <vector>
#include <queue>


class TagAttach 
{
public:
	TagAttach();
	~TagAttach();
	//input
	bool in_v;
	int in;
	//output
	short out_tag;
	bool out_v;
	int out;
	std::queue<std::vector<int>> config_reg;
	std::vector<int> tag_container;

	unsigned int pointor;

	//func
	void tag_container_init();
	void tag_bind();
	void buffer_clear();



};
