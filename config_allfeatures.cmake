set(BOBBY_APP_NAME bobbyquad_allfeatures)

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
  -DDEFAULT_WHEELDIAMETER=200
#  -DFEATURE_MOSFETS
#  -DPINS_MOSFET0=18
#  -DPINS_MOSFET1=19
#  -DPINS_MOSFET2=21
  -DDEFAULT_IMOTMAX=28
  -DDEFAULT_IDCMAX=30
  -DDEFAULT_NMOTMAX=2000
  -DDEFAULT_FIELDWEAKMAX=7
  -DDEFAULT_FIELDADVMAX=40
  -DFEATURE_WEBSERVER
  -DFEATURE_OTA
#  -DFEATURE_DPAD_5WIRESW
#  -DPINS_DPAD_5WIRESW_OUT=4
#  -DPINS_DPAD_5WIRESW_IN1=5
#  -DPINS_DPAD_5WIRESW_IN2=27
#  -DPINS_DPAD_5WIRESW_IN3=18
#  -DPINS_DPAD_5WIRESW_IN4=19
#  -DPINS_DPAD_EXTRASW_IN5=25
  -DFEATURE_DPAD_6WIRESW
  -DPINS_DPAD_6WIRESW_OUT=4
  -DPINS_DPAD_6WIRESW_IN1=5
  -DPINS_DPAD_6WIRESW_IN2=27
  -DPINS_DPAD_6WIRESW_IN3=18
  -DPINS_DPAD_6WIRESW_IN4=19
  -DPINS_DPAD_6WIRESW_IN5=26

#  -DDPAD_5WIRESW_UP=1
#  -DDPAD_5WIRESW_DOWN=5
#  -DDPAD_5WIRESW_CONFIRM=2
#  -DDPAD_5WIRESW_BACK=6
#  -DDPAD_5WIRESW_PROFILE0=4
#  -DDPAD_5WIRESW_PROFILE1=0
#  -DDPAD_5WIRESW_PROFILE2=7
#  -DDPAD_5WIRESW_PROFILE3=3
#  -DDPAD_5WIRESW_DEBUG

   -DDPAD_6WIRESW_UP=1
   -DDPAD_6WIRESW_DOWN=5
   -DDPAD_6WIRESW_CONFIRM=2
   -DDPAD_6WIRESW_BACK=6
   -DDPAD_6WIRESW_PROFILE0=4
   -DDPAD_6WIRESW_PROFILE1=0
   -DDPAD_6WIRESW_PROFILE2=7
   -DDPAD_6WIRESW_PROFILE3=3
   -DDPAD_6WIRESW_BLINK_LEFT=8
   -DDPAD_6WIRESW_BLINK_RIGHT=9
#   -DDPAD_6WIRESW_DEBUG
   -DFEATURE_GSCHISSENE_DIODE

  -DDEFAULT_GASMIN=842
  -DDEFAULT_GASMAX=2480
  -DDEFAULT_BREMSMIN=826
  -DDEFAULT_BREMSMAX=2502
  -DFEATURE_BLE
#  -DFEATURE_BLUETOOTH
#  -DFEATURE_BMS
#  -DFEATURE_GAMETRAK
#  -DPINS_GAMETRAKX=34
#  -DPINS_GAMETRAKY=39
#  -DPINS_GAMETRAKDIST=36
#  -DDEFAULT_GAMETRAKXMIN=0
#  -DDEFAULT_GAMETRAKXMAX=4095
#  -DDEFAULT_GAMETRAKYMIN=0
#  -DDEFAULT_GAMETRAKYMAX=4095
#  -DDEFAULT_GAMETRAKDISTMIN=0
#  -DDEFAULT_GAMETRAKDISTMAX=4095
  -DFEATURE_POWERSUPPLY
  -DFEATURE_CLOUD
  -DFEATURE_UDPCLOUD
  -DFEATURE_LEDBACKLIGHT
  -DPINS_LEDBACKLIGHT=23
  -DLEDBACKLIGHT_INVERTED
  -DFEATURE_GARAGE
  -DFEATURE_NTP
  -DFEATURE_WIRELESS_CONFIG
  -DFEATURE_LEDSTRIP
  -DPINS_LEDSTRIP=33
  -DLEDSTRIP_LENGTH=288
  -DHEAP_LRGST_CRASH_TEXT_FIX
  -DLEDSTRIP_WRONG_DIRECTION
  -DLEDSTRIP_ANIMATION_DEFAULT=1
  -DLEDS_PER_METER=144
  -DOLD_NVS
  -DFEATURE_DNS_NS
  -DSWITCH_BLINK
  -DFEATURE_ESPNOW
)
