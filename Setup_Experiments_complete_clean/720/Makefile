include VIDEOINFO.mk

doaom:
	./../aomenc_al$(type) --verbose --psnr --frame-parallel=0 --tile-columns=0 --cpu-used=0 --threads=1 --end-usage=q --cq-level=$(CQ) --lag-in-frames=0 --kf-min-dist=1000 --kf-max-dist=1000 --limit=$(FTBE) --width=$(WIDTH) --height=$(HEIGHT) --fps=60/1 --i420 -o webm/av1_$(type).webm ../HEVC/$(VID)/hevcDecode.yuv > log/av1_$(type).log 2>&1
		

dophotos:
	python ../../AUX/qt2png.py $(WIDTH) $(HEIGHT) AV1_$(type).qt $(FTBE) $(type)
	i=0 && \
	while [ $$i -lt $(FTBE) ]; do \
		mv photo$(type)offrame$$i\.png photos/ ; \
		i=`expr $$i + 1` ; \
	done


tree:
	./../aomdec -o aom_$(type).y4m webm/av1_$(type).webm > AV1_$(type).dpt 2>&1
	./../../AUX/DPT_2_QT AV1_$(type).dpt > dpt2qt.log
	./../../AUX/QT $(QUALITY) $(FTBE) ../HEVC/$(VID)/HEVC.qt AV1_$(type).qt > log/tableQT_$(type).txt
	#$(MAKE) dophotos type=$(type)

clean:
	rm -rf *.dpt
	rm -rf *.y4m
	rm -rf *.qt
	rm -rf *.log

eachone:
	mkdir $(COD)
	mkdir $(COD)/webm
	mkdir $(COD)/log
	mkdir $(COD)/photos
	cp Makefile $(COD)/Makefile
	cp VIDEOINFO.mk $(COD)/VIDEOINFO.mk
	ln -s ../HEVC/$(VID)/HEVC.qt $(COD)/HEVC.qt
	$(MAKE) -C $(COD) doaom  VID=$(VID) CQ=$(CQ) type=0
	$(MAKE) -C $(COD) tree VID=$(VID) type=0
	$(MAKE) -C $(COD) doaom  VID=$(VID) CQ=$(CQ) type=1
	$(MAKE) -C $(COD) tree VID=$(VID) type=1
	$(MAKE) -C $(COD) doaom  VID=$(VID) CQ=$(CQ) type=2
	$(MAKE) -C $(COD) tree VID=$(VID) type=2
	$(MAKE) -C $(COD) doaom  VID=$(VID) CQ=$(CQ) type=3
	$(MAKE) -C $(COD) tree VID=$(VID) type=3
	$(MAKE) -C $(COD) doaom  VID=$(VID) CQ=$(CQ) type=4
	$(MAKE) -C $(COD) tree VID=$(VID) type=4
	$(MAKE) -C $(COD) clean
	echo "DONE"

hevcloop:
	$(MAKE) -C HEVC hevcloop CPU=0
	

doit1:	
	rm -rf $(VID1)_$(CQ)
	taskset -c $(CPU) $(MAKE) eachone COD=$(VID1)_$(CQ) VID=$(VID1) CQ=$(CQ)
	
doit2:
	rm -rf $(VID2)_$(CQ)
	taskset -c $(CPU) $(MAKE) eachone COD=$(VID2)_$(CQ) VID=$(VID2) CQ=$(CQ)
	
doit3:
	rm -rf $(VID3)_$(CQ)
	taskset -c $(CPU) $(MAKE) eachone COD=$(VID3)_$(CQ) VID=$(VID3) CQ=$(CQ)
	
doit4:
	rm -rf $(VID4)_$(CQ)
	taskset -c $(CPU) $(MAKE) eachone COD=$(VID4)_$(CQ) VID=$(VID4) CQ=$(CQ)
	
doit5:
	rm -rf $(VID5)_$(CQ)
	taskset -c $(CPU) $(MAKE) eachone COD=$(VID5)_$(CQ) VID=$(VID5) CQ=$(CQ)
	
doit6:
	rm -rf $(VID6)_$(CQ)
	taskset -c $(CPU) $(MAKE) eachone COD=$(VID6)_$(CQ) VID=$(VID6) CQ=$(CQ)
	
doit7:
	rm -rf $(VID7)_$(CQ)
	taskset -c $(CPU) $(MAKE) eachone COD=$(VID7)_$(CQ) VID=$(VID7) CQ=$(CQ)
	
doit8:
	rm -rf $(VID8)_$(CQ)
	taskset -c $(CPU) $(MAKE) eachone COD=$(VID8)_$(CQ) VID=$(VID8) CQ=$(CQ)
	
	
CONDITIONALEXAMPLE:
	if [ -f FRAMES.txt ]; then \
		mv FRAMES.txt webm/FRAMES_$(type).txt ; \
	fi
	
