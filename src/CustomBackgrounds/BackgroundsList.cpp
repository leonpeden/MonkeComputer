#include "CustomBackgrounds/BackgroundsList.hpp"
#include "quest-cosmetic-loader/shared/FileUtils.hpp"
#include <algorithm>


std::string toLower(std::string in)
{
    std::string result;

    for (auto c : in)
    {
        result.push_back(c);
    }

    return result;
}


void BackgroundsList::Load()
{
    std::string folderPath = "sdcard/ModData/com.AnotherAxiom.GorillaTag/Mods/MonkeComputer/Backgrounds";
    
    FileUtils::makeFolder(folderPath);

    backgrounds.clear();
    FileUtils::GetFilesInFolderPath("png", folderPath, backgrounds);
    FileUtils::GetFilesInFolderPath("jpg", folderPath, backgrounds);

    std::sort(backgrounds.begin(), backgrounds.end(), [&](std::string first, std::string second) -> bool {
        first = toLower(first);
        second = toLower(second);

        return first < second;
    });
}

std::vector<std::string>& BackgroundsList::get_list()
{
    return backgrounds;
}

std::string BackgroundsList::get_fileName(int index)
{
    return backgrounds[index];
}