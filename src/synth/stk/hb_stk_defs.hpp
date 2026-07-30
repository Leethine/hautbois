#ifndef HB_STK_DEFS_HPP
#define HB_STK_DEFS_HPP

#define STK_DEFAULT_SAMPLE_RATE 44100
#define STK_RAWWAVES_DIR "/usr/share/stk/rawwaves/"

#define PREPARE_STK(RATE, PATH) ( \
  stk::Stk::setSampleRate(RATE);  \
  stk::Stk::setRawwavePath(PATH); \
)

#endif