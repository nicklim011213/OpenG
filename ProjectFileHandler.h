#ifndef PROJECTFILEHANDLING
#define PROJECTFILEHANDLING
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
#endif

