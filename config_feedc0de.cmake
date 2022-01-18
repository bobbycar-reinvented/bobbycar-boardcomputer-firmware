set(BOBBY_APP_NAME bobbyquad_feedc0de)

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
  -DFEATURE_ADC_IN
  -DPINS_GAS=34
  -DPINS_BREMS=35
  -DDEFAULT_SWAPSCREENBYTES=false
  -DFEATURE_CAN
#  -DFEATURE_SERIAL
#  -DPINS_RX1=4
#  -DPINS_TX1=5
#  -DPINS_RX2=22
#  -DPINS_TX2=23
  -DDEFAULT_INVERTFRONTLEFT=false
  -DDEFAULT_INVERTFRONTRIGHT=true
  -DDEFAULT_INVERTBACKLEFT=false
  -DDEFAULT_INVERTBACKRIGHT=true
  -DDEFAULT_WHEELDIAMETER=255
  -DFEATURE_MOSFETS
  -DPINS_MOSFET0=4
  -DPINS_MOSFET1=5
  -DPINS_MOSFET2=25
  -DDEFAULT_IMOTMAX=40
  -DDEFAULT_IDCMAX=42
  -DDEFAULT_NMOTMAX=2000
  -DDEFAULT_FIELDWEAKMAX=17
  -DDEFAULT_FIELDADVMAX=40
  -DFEATURE_WEBSERVER
  -DFEATURE_OTA
  -DFEATURE_DPAD_5WIRESW_2OUT
  -DPINS_DPAD_5WIRESW_OUT1=18
  -DPINS_DPAD_5WIRESW_OUT2=19
  -DPINS_DPAD_5WIRESW_IN1=27
  -DPINS_DPAD_5WIRESW_IN2=32
  -DPINS_DPAD_5WIRESW_IN3=33
  -DFEATURE_BLE
#  -DFEATURE_BLUETOOTH
#  -DFEATURE_BMS
#  -DFEATURE_GAMETRAK
#  -DPINS_GAMETRAKX=34
#  -DPINS_GAMETRAKY=39
#  -DPINS_GAMETRAKDIST=36
  -DFEATURE_POWERSUPPLY
  -DFEATURE_LEDBACKLIGHT
  -DPINS_LEDBACKLIGHT=23
  -DLEDBACKLIGHT_INVERTED
  -DFEATURE_NTP
  -DFEATURE_WIRELESS_CONFIG
  -DPINS_LEDSTRIP=26
#  -DHEAP_LRGST_CRASH_TEXT_FIX
#  -DLEDSTRIP_WRONG_DIRECTION
#  -DFEATURE_ESPNOW
)
