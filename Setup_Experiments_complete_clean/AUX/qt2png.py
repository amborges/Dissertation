from PIL import Image
import argparse
import math

parser = argparse.ArgumentParser(description='Optional app description')
parser.add_argument('resolutionW', type=int, help='Resolution valid Hight: 768, 1280, 1920, 2160, 2160')
parser.add_argument('resolutionH', type=int, help='Resolution valid Hight: 432, 720, 1080, 1440, 4096')
parser.add_argument('FileName', help='FileName.qt')
parser.add_argument('FTBE', type=int, help='Frames To Be Encode')
parser.add_argument('TYPE', type=int, help='Number of output (type of aomenc)')
args = parser.parse_args()

width  = args.resolutionW
height = args.resolutionH
wid = int(math.ceil(float(width)/128.0))
hei = int(math.ceil(float(height)/128.0))
frames = args.FTBE
numbertype = args.TYPE
qtfile = open(args.FileName)

def pinta(p, w, h, ch):
	if(w >= width or h >= height):
		return	
	
	RED    = (255,0,0)
	ORANGE = (255,165,0)
	YELLOW = (255,255,0)
	GREEN  = (0,255,0)
	BLUE   = (0,0,255)
	PURPLE = (128,0,128)

	#print("["+str(w)+","+str(h)+"]")

	for l1 in range(4):
		for l2 in range(4):
			if(qt == '0'):
				p[w+l1,h+l2] = RED
			elif(qt == '1'):
				p[w+l1,h+l2] = ORANGE
			elif(qt == '2'):
				p[w+l1,h+l2] = YELLOW
			elif(qt == '3'):
				p[w+l1,h+l2] = GREEN
			elif(qt == '4'):
				p[w+l1,h+l2] = BLUE
			elif(qt == '5'):
				p[w+l1,h+l2] = PURPLE

f = 0
while f < frames:
	im = Image.new("RGB", (width, height))
	pix = im.load()
	for hi in range(hei):
		for wi in range(wid):
			#qtch = ""
			for w in range(32):
				for h in range(32):
					qt = qtfile.read(1)
					posw = (wi * 128) + (w * 4)
					posh = (hi * 128) + (h * 4)
					pinta(pix, posw, posh, qt)
					#qtch = qtch + qt
				#qtch = qtch + "\n"
			#qtch = qtch + "\n"
			#qtch = qtch + "\n"
			#print (qtch)

	im.save("photo"+str(numbertype)+"offrame"+str(f)+".png", "PNG")
	f = f + 1
