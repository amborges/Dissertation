#Informacoes Compartilhadas entre os videos
FTBE    = 60
FONTE   = /home/alexborges/XIPH/4k
#FONTE   = /home/alex/Videos/XIPH/4k

#HEVC_CFG = encoder_lowdelay_main
HEVC_CFG = encoder_randomaccess_main
WIDTH		=	4096
HEIGHT	=	2160
QUALITY = 4k

#FPS
#1. 24 (1)
#2. 50 (3)
#3. 60 (4)

#Informacoes do video 1
VID1  = Netflix_BarScene_4096x2160_60fps_10bit_420_60f
VID2  = Netflix_BoxingPractice_4096x2160_60fps_10bit_420_60f
VID3  = Netflix_Dancers_4096x2160_60fps_10bit_420_60f
VID4  = Netflix_Narrator_4096x2160_60fps_10bit_420_60f
VID5  = Netflix_RitualDance_4096x2160_60fps_10bit_420_60f
VID6  = Netflix_ToddlerFountain_4096x2160_60fps_10bit_420_60f
VID7  = Netflix_WindAndNature_4096x2160_60fps_10bit_420_60f
VID8  = street_hdr_amazon_2160p

ALLVID = $(VID1) $(VID2) $(VID3) $(VID4) $(VID5) $(VID6) $(VID7) $(VID8)


