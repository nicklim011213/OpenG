#include "ProjectReader.h"
class ProjectHandler
{
public:
	void LoadFile(std::string FilePath)
	{
		std::ifstream Filehandle = std::ifstream(FilePath);
		if (!Filehandle)
		{
			std::cerr << "ERROR: File cannot be opened, is the path correct?\n";
		}
		else
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
				SendToRender(ItemParsing(Filehandle));
			}
		}

	}
	void SaveFile()
	{

	}
	void CloseFile()
	{

	}
private:
	std::string FilePath;
};