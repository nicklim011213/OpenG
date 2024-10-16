#include "ProjectReader.h"
	void ProjectHandler::LoadFile(std::string FilePath)
	{
		std::ifstream Filehandle = std::ifstream(FilePath);
		if (!Filehandle)
		{
			std::cerr << "ERROR: File cannot be opened, is the path correct?\n";
		}
		/*else
		{
			std::string VersionString;
			std::getline(Filehandle, VersionString);
			if (VersionString.find("Version: ") == VersionString.npos)
			{
				std::cerr << "ERROR: Failed to find version string, your project file may be croupted or invalid.\n";
			}

			if (VersionString.find("0.1A") != VersionString.npos)
			{
				std::cout << "Version 0.1 Alpha\n";
			}
		}
		*/

		Item Example;
		using json = nlohmann::json;

	}

	void ProjectHandler::SaveFile()
	{

	}

	void ProjectHandler::CloseFile()
	{

	}

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