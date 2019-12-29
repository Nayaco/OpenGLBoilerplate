#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include "Core/Common.hpp"
#include "Core/Utility/Noise/Noise.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Light/BaseLight.hpp"
#include "Core/Graphics/Light/ALight.hpp"
#include "Core/Graphics/Light/PLight.hpp"

#include <stb_image.h>

class ResourceManager {
    static map<string, Shader>  shaders;
    static map<string, Texture> textures;
    static map<string, BaseLight*> lights;
public:
    static void loadVF(string const &shader_name, string const &shader_path);
    static void loadVTTF(string const &shader_name, string const &shader_path);
    static void loadVGF(string const &shader_name, string const &shader_path);
    static void loadVTTGF(string const &shader_name, string const &shader_path);
    static void setShader(string const &shader_name, Shader const &shader);
    static Shader getShader(string const &shader_name);

    
    static void Load2D(string const &tex_name, string const &tex_path);
    static void Load2DGC(string const &tex_name, string const &tex_path);
    static void Load2DCube(string const &tex_name, vector<string> const &tex_faces);
    static void Load2DDynamic(string const &tex_name, imap2d const &tex_map, int width, int height);
    static void Load3D(string const &tex_name, vector<string> const &tex_faces);
    static void setTexture(string const &tex_name, Texture const &tex);
    static Texture getTexture(string const &tex_name);

    static void GenPLight(string const &light_name, int light_id, glm::vec3 const &light_pos, glm::vec3 const &light_color);
    static void GenALisht(string const &light_name, int light_id, glm::vec3 const &light_dir, glm::vec3 const &light_color);
    static BaseLight* getLight(string const &light_name);
};
#endif