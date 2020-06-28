#importing necessary libraries

from imutils.video import VideoStream
from pyzbar import pyzbar
import argparse
import datetime
import imutils
import time
import cv2
import serial     # to connect raspberry pi to arduino



# construct the argument parser and parse the arguments

ap = argparse.ArgumentParser()
ap.add_argument("-o", "--output", type=str, default="barcodes.csv",
	help="path to store CSV file containing barcodes")
args = vars(ap.parse_args())
vs = VideoStream(usePiCamera=True).start()
time.sleep(2.0)

# open the output CSV file for writing and initialize the set of
# barcodes found thus far
csv = open(args["output"], "w")
found = set()

#defininng three pincodes whom we have to differentiate parcels
three_pincodes = ["303600","304044","304050"]

# loop over the frames from the video stream
while True:
	# grab the frame from the threaded video stream and resize it to
	# have a maximum width of 400 pixels
	frame = vs.read()
	frame = imutils.resize(frame, width=400)
	# find the barcodes in the frame and decode each of the barcodes
	barcodes = pyzbar.decode(frame)
	# loop over the detected barcodes

	for barcode in barcodes:
		# extract the bounding box location of the barcode and draw
		# the bounding box surrounding the barcode on the image
		(x, y, w, h) = barcode.rect
		cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
		# the barcode data is a bytes object so if we want to draw it
		# on our output image we need to convert it to a string first
		barcodeData = barcode.data.decode("utf-8")
		barcodeType = barcode.type
		# draw the barcode data and barcode type on the image
		text = "{} ({})".format(barcodeData, barcodeType)
		cv2.putText(frame, text, (x, y - 10),cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)


        # checking if barcode exist from these three pincodes then it will signal the arduino 
        	for i in range(3):
            		if (three_pincodes[i] == barcodeData):
               			if i == 0:                                      #if pincode 1 exist then it will signal arduino to go for path one
                    			ser = serial.Serial('/dev/ttyUSB0', 9600)
                    			ser.write(b'1')
                		elif i == 1:                                     #if pincode 2 exist then it will signal arduino to go for path two
                    			ser = serial.Serial('/dev/ttyUSB0', 9600)
                    			ser.write(b'2')
                		else:                                            #if pincode 3 exist then it will signal arduino to go for path three
                    			ser = serial.Serial('/dev/ttyUSB0', 9600)
                    			ser.write(b'2')
                		break
            		else:
                		pass
        

        # we stores csv file to check how many type of pincode we get to check we didnt get wroung parcel
		# if the barcode text is currently not in our CSV file, write
		# the timestamp + barcode to disk and update the set
		if barcodeData not in found:
			csv.write("{},{}\n".format(datetime.datetime.now(),
				barcodeData))
			csv.flush()
			found.add(barcodeData)

	# show the output frame
	cv2.imshow("Barcode Scanner", frame)
	key = cv2.waitKey(1) & 0xFF
 
	# if the `q` key was pressed, break from the loop
	if key == ord("q"):
		break

# closing csv file with storing barcode data
csv.close()
#closing all window
cv2.destroyAllWindows()
vs.stop()
