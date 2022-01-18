set(BOBBY_APP_NAME bobbyquad_comred)

add_definitions(
  -DUSER_SETUP_LOADED=1
  -DLOAD_GLCD=1
  -DLOAD_FONT2=1
  -DLOAD_FONT4=1
  -DLOAD_FONT7=1
  -DILI9341_DRIVER=1
  -DTFT_MOSI=13
  -DTFT_SCLK=15
  -DTFT_CS=14
  -DTFT_DC=12
  -DTFT_RST=2
  -DSPI_FREQUENCY=40000000
)

set(BOBBYCAR_BUILDFLAGS
# Pins
    -DPINS_GAS=34
    -DPINS_BREMS=35
#    -DPINS_RX1=4
#    -DPINS_TX1=5
#    -DPINS_RX2=22
#    -DPINS_TX2=23
#    -DPINS_MOSFET0=18
#    -DPINS_MOSFET1=19
#    -DPINS_MOSFET2=21
#    -DPINS_GAMETRAKX=34
#    -DPINS_GAMETRAKY=39
#    -DPINS_GAMETRAKDIST=36
    -DPINS_LEDBACKLIGHT=23
    -DPINS_LEDSTRIP=33

# Config flags
    -DFEATURE_ADC_IN
    -DFEATURE_CAN
#    -DFEATURE_SERIAL
#    -DFEATURE_MOSFETS
    -DFEATURE_WEBSERVER
    -DFEATURE_OTA
    -DFEATURE_BLE
#    -DFEATURE_BLUETOOTH
#    -DFEATURE_BMS
#    -DFEATURE_GAMETRAK
#    -DFEATURE_POWERSUPPLY
    -DFEATURE_LEDBACKLIGHT
    -DFEATURE_ESPNOW

    -DLEDBACKLIGHT_INVERTED
#    -DLEDSTRIP_WRONG_DIRECTION
    -DHEAP_LRGST_CRASH_TEXT_FIX

# Default values
    -DDEFAULT_SWAPSCREENBYTES=false
    -DDEFAULT_INVERTFRONTLEFT=false
    -DDEFAULT_INVERTFRONTRIGHT=true
    -DDEFAULT_INVERTBACKLEFT=false
    -DDEFAULT_INVERTBACKRIGHT=true
    -DDEFAULT_WHEELDIAMETER=200
    -DDEFAULT_IMOTMAX=28
    -DDEFAULT_IDCMAX=30
    -DDEFAULT_NMOTMAX=2000
    -DDEFAULT_FIELDWEAKMAX=17
    -DDEFAULT_FIELDADVMAX=40

# DPAD
#    -DFEATURE_DPAD_5WIRESW
#    -DPINS_DPAD_5WIRESW_OUT=4
#    -DPINS_DPAD_5WIRESW_IN1=5
#    -DPINS_DPAD_5WIRESW_IN2=27
#    -DPINS_DPAD_5WIRESW_IN3=18
#    -DPINS_DPAD_5WIRESW_IN4=19
#    -DPINS_DPAD_EXTRASW_IN5=25
    -DFEATURE_DPAD_6WIRESW
    -DPINS_DPAD_6WIRESW_OUT=4
    -DPINS_DPAD_6WIRESW_IN1=5
    -DPINS_DPAD_6WIRESW_IN2=27
    -DPINS_DPAD_6WIRESW_IN3=18
    -DPINS_DPAD_6WIRESW_IN4=19
    -DPINS_DPAD_6WIRESW_IN5=26
    -DFEATURE_GSCHISSENE_DIODE
)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ignore/lockscreen_plugin.cmake")
    include("${CMAKE_CURRENT_SOURCE_DIR}/ignore/lockscreen_plugin.cmake")
    message(WARNING "Including plugins")
endif()
