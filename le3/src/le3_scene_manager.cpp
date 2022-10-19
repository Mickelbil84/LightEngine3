#include "le3_scene_manager.h"

void LE3SceneManager::SaveAssets(std::string serializationPath) const
{
    std::ofstream fp(serializationPath, std::ofstream::out);
    {
        cereal::JSONOutputArchive oarchive(fp);
        oarchive(CEREAL_NVP(assets));
    }
}
void LE3SceneManager::LoadAssets(std::string serializationPath)
{
    std::ifstream fp(serializationPath, std::ofstream::in);
    {
        cereal::JSONInputArchive iarchive(fp);
        iarchive(assets);
    }
}