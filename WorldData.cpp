#include "WorldData.h"


using json = nlohmann::json;

//
// Item JSON Conversions
//

void Item::from_json(const json& j, std::deque<Space3D>& vertexList)
{
	vertexList.clear();
	for (const auto& item : j) {
		Space3D vertex;
		item.get_to(vertex);
		vertexList.push_back(vertex);
	}
}

void to_json(json& j, const Item& I) 
{
	j = json::array();
	j.push_back({ "ID", I.ItemID });
	j.push_back({ "VertexIndex", I.VertexIndex });
	j.push_back({ "VertexList", I.VertexList });
}

void from_json(const json& j, Item& I) 
{
	j.at("ID").get_to(I.ItemID);
	j.at("VertexIndexList").get_to(I.VertexIndex);
}

void to_json(json& j, const std::deque<Space3D>& vertexList) 
{
	j = json::array();
	for (const auto& vertex : vertexList) {
		j.push_back(vertex);
	}
}

//
// Item Constructors
//

Item::Item()
{
	std::cerr << "Item Created as blank (Non-Fatal) Loading Example...\n";
	VertexList = { Space3D{1,2,3}, Space3D{3,2,3}, Space3D{3,2,1} };
	VertexIndex = { 0,1,2 };
	ItemID = "Example";
}

Item::Item(std::vector<Space3D> Points)
{
	for (auto i = Points.begin(); i != Points.end(); ++i)
	{
		this->VertexList.push_back(*i);
	}
}

Item::Item(std::vector<Space3D> Points, std::string ID)
{
	for (auto i = Points.begin(); i != Points.end(); ++i)
	{
		this->VertexList.push_back(*i);
	}
	ItemID = ID;
}

Item::Item(std::vector<Space3D> Points, std::vector<int> TriangleIndexs)
{
	for (auto i = Points.begin(); i != Points.end(); ++i)
	{
		this->VertexList.push_back(*i);
	}
	for (auto i = TriangleIndexs.begin(); i != TriangleIndexs.end(); ++i)
	{
		this->VertexIndex.push_back(*i);
	}
}

Item::Item(std::vector<Space3D> Points, std::vector<int> TriangleIndexs, std::string ID)
{
	for (auto i = Points.begin(); i != Points.end(); ++i)
	{
		this->VertexList.push_back(*i);
	}
	for (auto i = TriangleIndexs.begin(); i != TriangleIndexs.end(); ++i)
	{
		this->VertexIndex.push_back(*i);
	}
	ItemID = ID;
}

//
// Item Functions
//


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

//
// CompleteItem Constructors
//

CompleteItem::CompleteItem(std::string ID, Space3D InsertLocation)
{
	UniqueID = ID;
	Location = InsertLocation;
	VertexList = { { 1, 0, 0 },  {0, 1, 0 }, {0, 0, 1} };
	VertexIndex = { 0, 1, 2 };

	//TODO Create Default Detials and make a json function for it
}

void ItemCollection::DisplayItemList()
{
	for (int i = 0; i != ItemList.size(); i++)
	{
		std::cout << ItemList[i].UniqueID << " Is at (XYZ) " << ItemList[i].Location.X << "," << ItemList[i].Location.Y << "," << ItemList[i].Location.Z << "\n";
	}
}