#ifndef SFXSEQ_H_
#define SFXSEQ_H_

// Tiny frame-based sequencer for short multi-note SFX
void SfxSeq_Init(void);
void SfxSeq_Update(void);

// Helpers
void SfxSeq_PlayTriadUp(void);     // e.g., C-E-G
void SfxSeq_PlayTriadDown(void);   // G-E-C
void SfxSeq_PlayOneUp(void);       // celebratory C-E-G-C'
void SfxSeq_PlayBow(void);         // magical twinkle sequence

#endif


