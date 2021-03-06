// This file is a part of Akel
// CREATED : 29/09/2021
// UPDATED : 29/09/2021

#include <Shaders/build.h>

namespace Ak
{
    void buildBasics2D()
    {
        if(!std::filesystem::exists(Core::getShaderPath() + "basic_2D/basic_2D.frag.spv") && !std::filesystem::exists(Core::getShaderPath() + "basic_2D/basic_2D.vert.spv"))
        {
            std::system(std::string("glslangValidator -V " + Core::getShaderPath() + "basic_2D/basic_2D.frag -o " + Core::getShaderPath() + "basic_2D/basic_2D.frag.spv").c_str());
            std::system(std::string("glslangValidator -V " + Core::getShaderPath() + "basic_2D/basic_2D.vert -o " + Core::getShaderPath() + "basic_2D/basic_2D.vert.spv").c_str());
            if(!std::filesystem::exists(Core::getShaderPath() + "basic_2D/basic_2D.frag.spv") && !std::filesystem::exists(Core::getShaderPath() + "basic_2D/basic_2D.vert.spv"))
                Core::log::report(ERROR, "Shaders : basic 2D shader cannot be build");
            else
                Core::log::report(MESSAGE, "Shaders : basic 2D shader built");
        }
    }
}
