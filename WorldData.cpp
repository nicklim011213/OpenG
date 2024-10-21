#include "WorldData.h"

void Item::InsertVertex(const Space3D& Vertex, const unsigned int position)
{
	if (position > VertexList.size())
	{
		std::cerr << "Inserted index is at invalid position ignoring...\n";
		return;
	}

	VertexList.insert(VertexList.begin() + position, Vertex);

	// Correct Vertex Index Numbers
	for (int i = 0; i != VertexIndex.size(); ++i)
	{
		if (VertexIndex[i] >= position)
			VertexIndex[i] += 1;
	}
}

void Item::InsertVertex(const Space3D& Vertex, const bool Start)
{
	if (!Start)
	{
		VertexList.push_back(Vertex);
	}
	else
	{
		VertexList.push_front(Vertex);

		// Correct Vertex Index Numbers
		for (int i = 0; i != VertexIndex.size(); ++i)
		{
			VertexIndex[i] += 1;
		}
	}
}