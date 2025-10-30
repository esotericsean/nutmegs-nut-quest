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
SRC += third_party/cbtfx/cbtfx.c
SRC += SfxCBTFX.c
endif

# Default hardware sprites size: SPRITES_8x16(default) or SPRITES_8x8
DEFAULT_SPRITES_SIZE = SPRITES_8x16

include $(ZGB_PATH)/src/MakefileCommon