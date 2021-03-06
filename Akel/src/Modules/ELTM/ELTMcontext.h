// This file is a part of Akel
// CREATED : 12/05/2021
// UPDATED : 25/08/2021

#ifndef __AK_ELTM_CONTEXT__
#define __AK_ELTM_CONTEXT__

#include <Akpch.h>
#include <Modules/ELTM/ELTMerrors.h>
#include <Utils/utils.h>
#include <Core/profile.h>

#ifndef AK_ELTM_VERSION_1_0
	#define ELTMcontext ELTM
	#define newContext load
#endif

namespace Ak
{
	class ELTMcontext
	{
		public:
			explicit ELTMcontext();
			bool newContext(std::string file);
			static std::string getText(std::string ID, size_t line, std::string file, std::string function)
			{
				if(_isError)
					return "error";

				if(_texts.count(ID))
					return _texts[ID];

				std::string moduleName = "";
				std::string moduleID = "";
				size_t found = 0;

				if((found = ID.find(".")) != std::string::npos)
				{
					moduleName.append(ID, 0, found);
					if(_modules.count(moduleName))
					{
						moduleID.append(ID, found + 1, ID.length());
						if(_modules[moduleName].count(moduleID))
							return _modules[moduleName][moduleID];
					}
					else
					{
						ELTMerrors error = context_error(std::string("undefined module name : " + moduleName), file, function, line);
						std::cout << red << error.what() << def << std::endl;
						return "error";
					}
				}

				ELTMerrors error = context_error(std::string("undefined ID : " + ID), file, function, line);
				std::cout << red << error.what() << def << std::endl;
				return "error";
			}

			const char* getFile()
			{
				return _file;
			}

			~ELTMcontext() = default;

		private:
			bool setID(bool isNewID);

			static inline bool _isError = false;

			static inline std::unordered_map<std::string, std::string> _texts;
			static inline std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _modules;
			std::vector<ELTMcontext> _imports;

			StreamStack _stream;
			const char* _file;

			std::string _lastModuleName = "";

			std::array<bool, 2> _comments;
			size_t _last_line_long_comment = 0;

			size_t _line = 0;
	};

	#undef getText
	#define getText(ID) getText(ID, __LINE__, __FILE__, AK_FUNC_SIG)
}

#endif // __AK_ELTM_CONTEXT__
