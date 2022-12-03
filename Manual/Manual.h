//
// Created by Antony on 04.12.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_MANUAL_H
#define LAB3_SOUND_PROCESSOR_MANUAL_H
#include "..//Converter/Mixer/Mixer.h"
#include "..//Converter/Muter/Muter.h"
#include "..//Converter/Slow/Slow.h"
class Manual {
public:
  Manual() = default;
  static void get_manual() ;
 ~Manual() =default;

};
#endif //LAB3_SOUND_PROCESSOR_MANUAL_H
