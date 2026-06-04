PROJECT_NAME = Nutmeg

all: build_gb

# Number of banks (must be a power of 2): A (Automatic), 2, 4, 8, 16, 32...
N_BANKS = A

# Music player: HUGETRACKER(default) or GBT_PLAYER
MUSIC_PLAYER = HUGETRACKER

# Optional: Enable CBT-FX SFX engine
# Usage: from build scripts or CLI pass USE_CBT_FX=1 to enable
ifeq ($(USE_CBT_FX),1)
CFLAGS += -DUSE_CBT_FX
CFLAGS += -Isrc/third_party/cbtfx
SRC += SfxCBTFX.c
SRC += CBTFX_SFX_Jump.c
SRC += CBTFX_SFX_Pickup.c
SRC += CBTFX_SFX_Stomp.c
SRC += CBTFX_SFX_Water.c
SRC += CBTFX_sfx_bundle.c
SRC += CBTFX_driver.c
endif

# Default hardware sprites size: SPRITES_8x16(default) or SPRITES_8x8
DEFAULT_SPRITES_SIZE = SPRITES_8x16

include $(ZGB_PATH)/src/MakefileCommon

# SfxSeq.c used #pragma bank 0 and overflows home ROM; keep disabled (see SfxSeq.c.disabled)
CLASSES := $(filter-out SfxSeq.c,$(CLASSES))
OBJS := $(filter-out $(OBJDIR)/SfxSeq.o,$(OBJS))