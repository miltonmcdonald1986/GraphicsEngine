#include "ShaderUtilities.h"

#include "Log.h"

namespace GraphicsEngine::ShaderUtilities
{

	auto GetSourceFromFile (const Types::Path& path) -> Types::String
	{
		if (path.empty ())
			return "";

		if (!std::filesystem::exists (path))
		{
			GetLog ()->Error (std::format ("Could not open '{}' because it does not exist.", path.string ()));
			return "";
		}

		std::ifstream ifs (path);
		std::stringstream buffer;
		buffer << ifs.rdbuf ();

		std::string str (buffer.str ());
		return str;
	}

}
