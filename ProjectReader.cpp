#include "ProjectReader.h"
	void ProjectHandler::LoadFile(std::string FilePath)
	{
		std::ifstream Filehandle = std::ifstream(FilePath);
		if (!Filehandle)
		{
			std::cerr << "ERROR: File cannot be opened, is the path correct?\n";
		}
		else
		{

		}
	}

	void ProjectHandler::SaveFile()
	{

	}

	void ProjectHandler::CloseFile()
	{

	}