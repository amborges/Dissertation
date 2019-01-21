include ../VIDEOINFO.mk

dohevc:
	./TAppEncoderStatic -c $(HEVC_CFG).cfg --Profile=main-RExt -i $(VIDEO) -b ../../TRASH/hevcbin.h265 -o $(VID)/hevcDecode.yuv -wdt $(WIDTH) -hgt $(HEIGHT) -f $(FTBE) -fr 60 --QP=22 --MSBExtendedBitDepth=10 --InputBitDepth=10 --InternalBitDepth=10 > $(VID)/hevc.log 2>&1
	./../../AUX/CSV_2_QT $(QUALITY) $(FTBE) > ../../TRASH/csv2qt.log
	mv HEVC.csv $(VID)/HEVC.csv
	mv HEVC.qt $(VID)/HEVC.qt
	#cd $(VID) && python ../../../AUX/qt2png.py $(WIDTH) $(HEIGHT) HEVC.qt $(FTBE) 0

CPU=0
hevcloop:
	for vid in $(ALLVID) ; do \
		rm -rf $$vid ; \
		mkdir $$vid ; \
		taskset -c $(CPU) $(MAKE) dohevc VID=$$vid VIDEO=$(FONTE)/$$vid\.yuv ; \
	done

