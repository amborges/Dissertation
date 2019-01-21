#Informacoes Compartilhadas entre os videos
FTBE    = 5
#FONTE   = /home/alexborges/XIPH/1080
FONTE   = /home/alex/Videos/XIPH/1080

#HEVC_CFG = encoder_lowdelay_main
HEVC_CFG = encoder_randomaccess_main
WIDTH		=	1920
HEIGHT	=	1080
QUALITY = $(HEIGHT)

#FPS
#1. 24 (1)
#2. 50 (3)
#3. 60 (4)

#Informacoes do video 1
VID1  = ducks_take_off_1080p50_60f
VID2  = life_1080p30_60f
VID3  = Netflix_Boat_1920x1080_60fps_8bit_420_60f
VID4  = Netflix_FoodMarket_1920x1080_60fps_8bit_420_60f
VID5  = Netflix_SquareAndTimelapse_1920x1080_60fps_8bit_420_60f
VID6  = Netflix_TunnelFlag_1920x1080_60fps_8bit_420_60f
VID7  = rush_hour_1080p25_60f
VID8  = seaplane_hdr_amazon_1080p

ALLVID = $(VID1) $(VID2) $(VID3) $(VID4) $(VID5) $(VID6) $(VID7) $(VID8)
