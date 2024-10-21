#ifndef PROJECTWORLDREADING
#define PROJECTWORLDREADING

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <deque>
#include <json.hpp>

using json = nlohmann::json;

struct Space3D
{
	unsigned int X, Y, Z;

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
	//char* ItemID[512];
	std::string ItemID;

	// Holds a list of vertexs used in the model of the item
	std::deque<Space3D> VertexList;

	// Holds a deque of indexes of vertexs in Vertexlist that make up the triangles for renderings
	std::deque<int> VertexIndex;

	// Inserts a Vertex and shifts VertexIndexs +1 
	void InsertVertex(const Space3D&, const unsigned int position);

	// Overload that inserts at start or end if false
	void InsertVertex(const Space3D&, const bool Start);

	void ExampleItem()
	{
		VertexList = { Space3D{1,2,3}, Space3D{3,2,3}, Space3D{3,2,1} };
		VertexIndex = { 0,1,2 };
		ItemID = "Example";
	}

	Item()
	{
		std::cerr << "Item Created as blank (Non-Fatal)\n";
	}

	Item(std::vector<Space3D> Points)
	{
		for (auto i = Points.begin(); i != Points.end(); ++i)
		{
			this->VertexList.push_back(*i);
		}
	}

	Item(std::vector<Space3D> Points, std::string ID)
	{
		for (auto i = Points.begin(); i != Points.end(); ++i)
		{
			this->VertexList.push_back(*i);
		}
		ItemID = ID;
	}

	Item(std::vector<Space3D> Points, std::vector<int> TriangleIndexs)
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

	Item(std::vector<Space3D> Points, std::vector<int> TriangleIndexs, std::string ID)
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

	void to_json(json& j, const Item& I) {
		j = json::array();
		j.push_back({ "ID", I.ItemID });
		j.push_back({ "VertexIndex", I.VertexIndex });
		j.push_back({ "VertexList", I.VertexList });
	}

	void from_json(const json& j, Item& I) {
		j.at("ID").get_to(I.ItemID);
		j.at("VertexIndexList").get_to(I.VertexIndex);
	}

	void to_json(json& j, const std::deque<Space3D>& vertexList) {
		j = json::array();
		for (const auto& vertex : vertexList) {
			j.push_back(vertex);
		}
	}

	void from_json(const json& j, std::deque<Space3D>& vertexList) {
		vertexList.clear();
		for (const auto& item : j) {
			Space3D vertex;
			item.get_to(vertex);
			vertexList.push_back(vertex);
		}
	}
};

class ItemCollection
{
public:
	std::unordered_map<unsigned int, Item> ItemList;
};

#endif