#ifndef PROJECTFILEREADING
#define PROJECTFILEREADING
	#include <iostream>
	#include <fstream>
	#include <string>
	#include <unordered_map>
	#include <deque>
	#include <json.hpp>

		class ProjectHandler
		{
		public:
			void LoadFile(std::string FilePath);
			void SaveFile();
			void CloseFile();
		private:
			std::string FilePath;
			//void SendToRender(ItemCollection);
			
		};

		struct Space3D
		{
			unsigned int X, Y, Z;
		};

		class Item
		{
			private:
				// A unique ID to refrence the Item by
				//char* ItemID[512];
				std::string ItemID;

				// Holds a list of vertexs used in the model of the item
				std::deque<Space3D> VertexList;

				// Holds a deque of indexes of vertexs in Vertexlist that make up the triangles for renderings
				std::deque<int> VertexIndex;

			public:
				// Inserts a Vertex and shifts VertexIndexs +1 
				void InsertVertex(const Space3D&, const unsigned int position);

				// Overload that inserts at start or end if false
				void InsertVertex(const Space3D&, const bool Start);

				//TODO: Create a function that validates if VertexIndex contains only valid indexes

				// Inserts a Triangle 
				void InsertFace(int Index1, int Index2, int Index3);

				void AssignStuff()
				{
					VertexList = { Space3D{1,2,3}, Space3D{3,2,3}, Space3D{3,2,1} };
					VertexIndex = { 1,2,3 };
					ItemID = "Example";
				}

				Item()
				{
					AssignStuff();
					using json = nlohmann::json;
					{
						json j;
						for (int i = 0; i < VertexList.size(); i++)
						{
							j.push_back(VertexIndex[i]);
							j.push_back(VertexIndex);
							j.push_back(ItemID);
						}
						std::ofstream Output("Out.json");
						Output << j;
						Output.close();
					}
				}
		};

		class ItemCollection
		{
			std::unordered_map<unsigned int, Item> ItemList;
		};
#endif

