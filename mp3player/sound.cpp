
#include <3ds.h>


#include "sound.hpp"
#include "Decoder.hpp"
#include "common.hpp"
#include "STDirectory.hpp"


#include <iostream>
#include <atomic>
#include <unordered_map>


namespace
{






    
    std::vector<std::string> bgm;
    size_t currentSong         = 0;



    Result mp3::PlayFile(){
    
         STDirectory dir("/3ds/PKSM/songs");
        if (dir.good())
        {
             for (size_t i = 0; i < dir.count(); i++)
             {
                  if (!dir.folder(i))
                 {
                     auto decoder = Decoder::get("/3ds/PKSM/songs/" + dir.item(i));
                     if (decoder && decoder->good())
                     {
                    bgm.emplace_back("/3ds/PKSM/songs/" + dir.item(i));
                      }
                  }
             }

         return 0;
    
    }
}