#Informacoes Compartilhadas entre os videos
FTBE    = 5
#FONTE   = /home/alexborges/XIPH/720
FONTE   = /home/alex/Videos/XIPH/720

#HEVC_CFG = encoder_lowdelay_main
HEVC_CFG = encoder_randomaccess_main
WIDTH		=	1280
HEIGHT	=	720
QUALITY = $(HEIGHT)

#FPS
#1. 24 (1)
#2. 50 (3)
#3. 60 (4)

#Informacoes do video 1
VID1  = boat_hdr_amazon_720p
VID2  = dark720p_120f
VID3  = gipsrestat720p_120f
VID4  = KristenAndSara_1280x720_60_120f
VID5  = Netflix_DrivingPOV_1280x720_60fps_8bit_420_120f
VID6  = Netflix_RollerCoaster_1280x720_60fps_8bit_420_120f
VID7  = vidyo1_720p_60fps_120f
VID8  = vidyo4_720p_60fps_120f

ALLVID = $(VID1) $(VID2) $(VID3) $(VID4) $(VID5) $(VID6) $(VID7) $(VID8)
