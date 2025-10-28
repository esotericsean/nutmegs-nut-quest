PROJECT_NAME = Nutmeg

all: build_gb

# Number of banks (must be a power of 2): A (Automatic), 2, 4, 8, 16, 32...
N_BANKS = A

# Music player: HUGETRACKER(default) or GBT_PLAYER
MUSIC_PLAYER = HUGETRACKER

# Default hardware sprites size: SPRITES_8x16(default) or SPRITES_8x8
DEFAULT_SPRITES_SIZE = SPRITES_8x16

# --- CBT-FX integration (must appear BEFORE MakefileCommon include) ---
# Define USE_CBT_FX and compile driver + SFX tables (no global include path to avoid header conflicts)
CFLAGS += -DUSE_CBT_FX
SRC += CBTFX_shim.c

include $(ZGB_PATH)/src/MakefileCommon