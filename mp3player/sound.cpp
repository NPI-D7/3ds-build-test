
#include <3ds.h>


#include "sound.hpp"
#include "Decoder.hpp"
#include "common.hpp"
#include "STDirectory.hpp"


#include <iostream>
#include <atomic>
#include <unordered_map>


namespace{





    constexpr size_t BUFFER_SIZE         = 32 * 1024;
    constexpr size_t NUM_CHANNELS        = 24;
    constexpr size_t BUFFERS_PER_CHANNEL = 2;
    s16* bufferMem                       = nullptr;
    std::array<ndspWaveBuf, NUM_CHANNELS * BUFFERS_PER_CHANNEL> buffers;
    std::array<std::unique_ptr<Decoder>, NUM_CHANNELS> decoders;
    // 0 is reserved for the background music
    std::atomic_flag occupiedChannels[NUM_CHANNELS];
    LightEvent frameEvent;

    std::unordered_map<std::string, std::string> effects; // effect name to file name
    std::vector<std::string> bgm;
    size_t currentSong         = 0;
    std::atomic<bool> playing  = false;
    std::atomic<bool> finished = true;
    u8 currentVolume           = 0;


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