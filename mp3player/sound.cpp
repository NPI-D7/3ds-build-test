
#include <3ds.h>
#include "sound.hpp"
#include "Decoder.hpp"
#include "common.hpp"


void mp3::PlayFile(std::string file){
    Decoder::get(file);
}