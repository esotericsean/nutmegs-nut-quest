#ifndef PLAYFX_DISABLE_H_
#define PLAYFX_DISABLE_H_

#ifdef USE_CBT_FX
#undef PlayFx
#define PlayFx(...) do {} while(0)
#endif

#endif


