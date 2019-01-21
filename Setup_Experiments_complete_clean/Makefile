#USAR: make do720 DO=1 CPU=0 & <e depois> disown
#CQs 20 32 43 55

do720:
	$(MAKE) -C 720 doit$(DO) CPU=$(CPU) CQ=$(CQ) DO=$(DO) > LOG/720_$(DO)_$(CQ).log

do1080:
	$(MAKE) -C 1080 doit$(DO) CPU=$(CPU) CQ=$(CQ) DO=$(DO) > LOG/1080_$(DO)_$(CQ).log

do4k:
	$(MAKE) -C 4K doit$(DO) CPU=$(CPU) CQ=$(CQ) DO=$(DO) > LOG/4K_$(DO)_$(CQ).log

generateav1:
	$(MAKE) -C aom_versions prepare
	$(MAKE) -C aom_versions generate TYPE=0
	$(MAKE) -C aom_versions generate TYPE=1
	$(MAKE) -C aom_versions generate TYPE=2
	$(MAKE) -C aom_versions generate TYPE=3
	$(MAKE) -C aom_versions generate TYPE=4

HM=HM-16.20
generatehevc:
	rm -rf $(HM)/bin/*
	$(MAKE) -C $(HM)/build/linux clean
	$(MAKE) -C $(HM)/build/linux
	cp $(HM)/bin/TAppEncoderStatic 720/HEVC/TAppEncoderStatic
	cp $(HM)/bin/TAppEncoderStatic 1080/HEVC/TAppEncoderStatic
	cp $(HM)/bin/TAppEncoderStatic 4K/HEVC/TAppEncoderStatic
	cp $(HM)/cfg/encoder_randomaccess_main.cfg 720/HEVC/encoder_randomaccess_main.cfg
	cp $(HM)/cfg/encoder_randomaccess_main.cfg 1080/HEVC/encoder_randomaccess_main.cfg
	cp $(HM)/cfg/encoder_randomaccess_main.cfg 4K/HEVC/encoder_randomaccess_main.cfg

generateAUX:
	gcc AUX/HEVCCSV_2_HEVCQT.c -o AUX/CSV_2_QT
	gcc AUX/AV1DPT_2_AV1QT.c -o AUX/DPT_2_QT
	gcc AUX/QTCOMPARE.c -o AUX/QT

downloadHM:
	svn checkout https://hevc.hhi.fraunhofer.de/svn/svn_HEVCSoftware/tags/$(HM)/
	cp aom_versions/toinstall/TEncGOP.cpp $(HM)/source/Lib/TLibEncoder/TEncGOP.cpp
	
teste:
	$(MAKE) generateav1
	$(MAKE) do720 DO=1 CQ=20 CPU=0
