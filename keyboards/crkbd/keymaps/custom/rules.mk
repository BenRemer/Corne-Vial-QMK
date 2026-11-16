# qmk compile -e MASTER=left -e CONVERT_TO=kb2040 --keyboard crkbd --keymap custom
# qmk compile -e MASTER=left --keyboard crkbd --keymap custom
VIA_ENABLE          = no
VIAL_ENABLE         = no
LTO_ENABLE          = yes
QMK_SETTINGS        = no
SPLIT_KEYBOARD      = yes

ifneq ($(strip $(CONVERT_TO)),kb2040)
    RGBLIGHT_ENABLE = yes
else
    RGBLIGHT_ENABLE = no
endif
RGB_MATRIX_ENABLE   = no # Can't have RGBLIGHT and RGB_MATRIX at the same time.
SLEEP_LED_ENABLE	= no

OLED_ENABLE         = yes
COMBO_ENABLE        = no
WPM_ENABLE          = yes

MOUSEKEY_ENABLE 	= no     # Mouse keys
EXTRAKEY_ENABLE     = yes
VIAL_TAP_DANCE_ENABLE   = no
VIAL_KEY_OVERRIDE_ENABLE = no
AUDIO_ENABLE 		= no
COMMAND_ENABLE 		= no
LEADER_ENABLE 		= no
BLUETOOTH_ENABLE 	= no
MIDI_ENABLE 		= no
UNICODE_ENABLE 		= no
BOOTMAGIC_ENABLE 	= yes
CONSOLE_ENABLE 		= no
MAGIC_ENABLE        = no
GRAVE_ESC_ENABLE    = no
SPACE_CADET_ENABLE  = no
CAPS_WORD_ENABLE    = no
LAYER_LOCK_ENABLE   = no
REPEAT_KEY_ENABLE   = no

ifeq ($(strip $(PLATFORM)),AVR)
    EXTRAFLAGS += -include avr/io.h
endif

# MCU = kb2040
# BOOTLOADER = rp2040
