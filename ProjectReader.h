#ifndef PROJECTFILEREADING
#define PROJECTFILEREADING
	#include <iostream>
	#include <fstream>
	#include <string>
	#include <unordered_map>
		class ProjectHandler
		{
		public:
			void LoadFile(std::string FilePath);
			void SaveFile();
			void CloseFile();
		private:
			std::string FilePath;
			void SendToRender(ItemCollection);
			
		};

		class Item
		{
			std::unordered_map<
		};

		class ItemCollection
		{
			std::unordered_map<unsigned int, Item> ItemList;
		};
#endif

