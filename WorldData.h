#ifndef PROJECTWORLDREADING
#define PROJECTWORLDREADING

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <deque>
#include <optional>
#include <bitset>
#include <json.hpp>

using json = nlohmann::json;

struct Space3D
{
	float X, Y, Z;

	friend void to_json(json& j, const Space3D& vertex) {
		j = json{
			{"X", vertex.X},
			{"Y", vertex.Y},
			{"Z", vertex.Z}
		};
	}

	friend void from_json(const json& j, Space3D& vertex) {
		j.at("X").get_to(vertex.X);
		j.at("Y").get_to(vertex.Y);
		j.at("Z").get_to(vertex.Z);
	}
};

class Item
{
public:
	// A unique ID to refrence the Item by
	std::string ItemID;

	// Holds a list of vertexs used in the model of the item
	std::deque<Space3D> VertexList;

	// Holds a deque of indexes of vertexs in Vertexlist that make up the triangles for renderings
	std::deque<int> VertexIndex;

	// Inserts a Vertex and shifts VertexIndexs +1 
	void InsertVertex(const Space3D&, const unsigned int position);

	// Overload that inserts at start or end if false
	void InsertVertex(const Space3D&, const bool Start);

	Item();

	Item(std::vector<Space3D> Points);

	Item(std::vector<Space3D> Points, std::string ID);

	Item(std::vector<Space3D> Points, std::vector<int> TriangleIndexs);

	Item(std::vector<Space3D> Points, std::vector<int> TriangleIndexs, std::string ID);

	void to_json(json& j, const Item& I);

	void from_json(const json& j, Item& I);

	void to_json(json& j, const std::deque<Space3D>& vertexList);

	void from_json(const json& j, std::deque<Space3D>& vertexList);
};

struct PointRenderDetails
{
	char Texture;

	// Encoding
	// It is planned that to add a color to
	// a texture a new texture is generate
	// to reduce the size of data passed
};

class CompleteItem
{
	public:
		std::string UniqueID;
		Space3D Location;
		PointRenderDetails Details;
		std::deque<Space3D> VertexList;
		std::deque<int> VertexIndex;

		CompleteItem(std::string ID, Space3D InsertLocation);
};

class ItemCollection
{
public:
	std::deque<CompleteItem> ItemList;

	void DisplayItemList();
};

#endif