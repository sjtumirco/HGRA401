#include "tagAttach.h"


TagAttach::TagAttach() :pointor(0) { tag_container.resize(4); tag_container_init(); }
TagAttach::~TagAttach() {}

void TagAttach::tag_container_init()
{
	for (std::vector<int>::size_type i = 0; i < tag_container.size(); i++)
	{
		tag_container[i] = i;
	}
}

void TagAttach::tag_bind()
{
	if (in_v)
	{
		out_v = in_v;
		out = in;
		out_tag = tag_container[pointor];
		pointor++;
		if (pointor == 4)
		{
			pointor = 0;
		}
	}
}

void TagAttach::buffer_clear()
{
	//do nothing
}