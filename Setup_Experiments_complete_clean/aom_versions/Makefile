prepare:
	cp toinstall/av1.cmake aom_al1/av1/av1.cmake
	cp toinstall/av1.cmake aom_al2/av1/av1.cmake
	cp toinstall/av1.cmake aom_al3/av1/av1.cmake
	cp toinstall/av1.cmake aom_al4/av1/av1.cmake
	
	cp toinstall/decodeframe.c aom_al1/av1/decoder/decodeframe.c
	cp toinstall/decodeframe.c aom_al2/av1/decoder/decodeframe.c
	cp toinstall/decodeframe.c aom_al3/av1/decoder/decodeframe.c
	cp toinstall/decodeframe.c aom_al4/av1/decoder/decodeframe.c
	
	cp toinstall/encodeframe_al2.c aom_al1/av1/encoder/encodeframe.c
	cp toinstall/encodeframe_al2.c aom_al2/av1/encoder/encodeframe.c
	cp toinstall/encodeframe_al4.c aom_al3/av1/encoder/encodeframe.c
	cp toinstall/encodeframe_al4.c aom_al4/av1/encoder/encodeframe.c
	
	cp toinstall/Dissertacao_al2.h aom_al1/av1/encoder/Dissertacao.h
	cp toinstall/Dissertacao_al2.h aom_al2/av1/encoder/Dissertacao.h
	cp toinstall/Dissertacao_al4.h aom_al3/av1/encoder/Dissertacao.h
	cp toinstall/Dissertacao_al4.h aom_al4/av1/encoder/Dissertacao.h
	
	cp toinstall/Dissertacao_al1.c aom_al1/av1/encoder/Dissertacao.c
	cp toinstall/Dissertacao_al2.c aom_al2/av1/encoder/Dissertacao.c
	cp toinstall/Dissertacao_al3.c aom_al3/av1/encoder/Dissertacao.c
	cp toinstall/Dissertacao_al4.c aom_al4/av1/encoder/Dissertacao.c
	
	cp toinstall/rdopt.c aom_al3/av1/encoder/rdopt.c
	cp toinstall/rdopt.c aom_al4/av1/encoder/rdopt.c

generate:
	rm -rf BINARI/*
	cd BINARI && cmake -DAOM_TARGET_CPU=generic ../aom_al$(TYPE) && $(MAKE) all
	cp BINARI/aomenc ../720/aomenc_al$(TYPE)
	cp BINARI/aomenc ../1080/aomenc_al$(TYPE)
	cp BINARI/aomdec ../720/aomdec
	cp BINARI/aomdec ../1080/aomdec
	
