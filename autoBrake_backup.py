import cv2
from darkflow.net.build import TFNet
import numpy as np
import time
import datetime
import warnings
import serial
warnings.simplefilter('ignore', np.RankWarning)

serial_port = serial.Serial(port="/dev/ttyTHS0", baudrate=38400)

#----------------------- Traffic Light---------------------------------

# click listener
font = cv2.FONT_HERSHEY_SIMPLEX
def click_event(event, x, y, flag, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        strXY = str(x) + ', ' + str(y)
        print("coodinate: " + strXY)
        cv2.putText(frame, strXY, (x, y), font, .5, (0, 255, 255), 2)
        cv2.imshow('combine result', frame)

    if event == cv2.EVENT_RBUTTONDOWN:
        BGRcolor = frame[y, x, :]

        hsv = cv2.cvtColor(np.uint8([[BGRcolor]]), cv2.COLOR_BGR2HSV)
        print("bgr: " + str(BGRcolor))
        print("hsv: " + str(hsv[0][0]))
        print()

        cv2.putText(frame, str(hsv[0][0]), (x, y), font, .5, (255, 255, 0), 2)
        cv2.imshow('combine result', frame)

def T_process(img):

    height = img.shape[0]
    width = img.shape[1]

    # mask img
    top_left = (int(width*0.2), int(height*0.05))
    btm_right = (int(width*0.5), int(height*0.3))

    img_crop = img[top_left[1]:btm_right[1], top_left[0]:btm_right[0]]
    # img_crop = img; top_left=(0,0); btm_right=(0,0);     # remove mask
    hsv_crop = cv2.cvtColor(img_crop, cv2.COLOR_BGR2HSV)
    cv2.rectangle(resultImg, top_left, btm_right, (0, 0, 255), 10)
    

    

    # color range
    lower_red1 = np.array([0,150,180])
    upper_red1 = np.array([5,255,255])
    lower_red2 = np.array([170,150,180])
    upper_red2 = np.array([180,255,255])

    lower_yellow = np.array([20,150,200])
    upper_yellow = np.array([30,255,255])                        

    lower_green = np.array([80,100,180])
    upper_green = np.array([92,255,255])

    mask1 = cv2.inRange(hsv_crop, lower_red1, upper_red1)
    mask2 = cv2.inRange(hsv_crop, lower_red2, upper_red2)
    maskg = cv2.inRange(hsv_crop, lower_green, upper_green)
    masky = cv2.inRange(hsv_crop, lower_yellow, upper_yellow)
    maskr = cv2.add(mask1, mask2)

    # if at night 
    time = datetime.datetime.now()
    if time.hour>=18 or time.hour<=4:
        # morphological
        kernal = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (25,25))
        maskr = cv2.morphologyEx(maskr, cv2.MORPH_CLOSE, kernal)
        masky = cv2.morphologyEx(masky, cv2.MORPH_CLOSE, kernal)
        maskg = cv2.morphologyEx(maskg, cv2.MORPH_CLOSE, kernal)


    size = hsv_crop.shape
    # print(size)

    # hough circle detect
    r_circles = cv2.HoughCircles(maskr, cv2.HOUGH_GRADIENT, 1, 100,
                                 param1=100, param2=10, minRadius=0, maxRadius=30)

    g_circles = cv2.HoughCircles(maskg, cv2.HOUGH_GRADIENT, 1, 50,
                                 param1=100, param2=10, minRadius=0, maxRadius=30)

    y_circles = cv2.HoughCircles(masky, cv2.HOUGH_GRADIENT, 1, 100,
                                 param1=100, param2=6, minRadius=0, maxRadius=30)
 

    r = 5
    bound = 10.0 / 10

    # traffic light detect
    # red
    if r_circles is not None:
        r_circles = np.uint16(np.around(r_circles))

        for i in r_circles[0, :]:
            if i[0] > size[1] or i[1] > size[0] or i[1] > size[0]*bound:
                continue

            h, s = 0.0, 0.0
            for m in range(-r, r):
                for n in range(-r, r):

                    if (i[1]+m) >= size[0] or (i[0]+n) >= size[1]:
                        continue
                    h += maskr[i[1]+m, i[0]+n]
                    s += 1
            if h / s > 150:
                origin_position = (i[0]+top_left[0], i[1]+top_left[1])  # (x, y)
                cv2.circle(resultImg, origin_position, i[2]+10, (0, 0, 255), 2)
                cv2.circle(maskr, (i[0], i[1]), i[2]+10, (255, 255, 255), 2)
                cv2.putText(resultImg, str(i[2]), origin_position, font, 1,(0,0,0),1,cv2.LINE_AA)
                cv2.putText(infoBox, 'Traffic Light: '+'Red', (0,90), cv2.FONT_HERSHEY_COMPLEX, 0.9, (255,255,255),2)

                # let autoBrake stop working
                serial_port.write(b'R\n')

    # green
    if g_circles is not None:
        g_circles = np.uint16(np.around(g_circles))

        for i in g_circles[0, :]:
            if i[0] > size[1] or i[1] > size[0] or i[1] > size[0]*bound:
                continue

            h, s = 0.0, 0.0
            for m in range(-r, r):
                for n in range(-r, r):

                    if (i[1]+m) >= size[0] or (i[0]+n) >= size[1]:
                        continue
                    h += maskg[i[1]+m, i[0]+n]
                    s += 1

            if h / s > 150:
            
                origin_position = (i[0]+top_left[0], i[1]+top_left[1])  # (x, y)
                cv2.circle(resultImg, origin_position, i[2]+10, (0, 255, 0), 2)
                cv2.circle(maskg, (i[0], i[1]), i[2]+10, (255, 255, 255), 2)
                cv2.putText(infoBox, 'Traffic Light: '+'Green', (0,90), cv2.FONT_HERSHEY_COMPLEX, 0.9, (255,255,255),2)

    # yellow
    if y_circles is not None:
        y_circles = np.uint16(np.around(y_circles))

        for i in y_circles[0, :]:
            if i[0] > size[1] or i[1] > size[0] or i[1] > size[0]*bound:
                continue

            h, s = 0.0, 0.0
            for m in range(-r, r):
                for n in range(-r, r):
                    if (i[1]+m) >= size[0] or (i[0]+n) >= size[1]:
                        continue
                    h += masky[i[1]+m, i[0]+n]
                    s += 1

            if h / s > 40:
                origin_position = (i[0]+top_left[0], i[1]+top_left[1])  # (x, y)
                cv2.circle(resultImg, origin_position, i[2]+10, (0, 200, 200), 2)
                cv2.circle(masky, (i[0], i[1]), i[2]+10, (255, 255, 255), 2)
                cv2.putText(resultImg, 'Traffic Light: '+'Yellow', (0,90),  cv2.FONT_HERSHEY_COMPLEX, 0.9, (255,255,255),2)
                serial_port.write(b'R\n')

    
    cv2.imshow('maskr', maskr)
    cv2.imshow('maskg', maskg)
    cv2.imshow('masky', masky)
    # cv2.imshow('mor_r', mor_r)
    # cv2.imshow('mor_g', mor_g)
    # cv2.imshow('mor_y', mor_y)
    

#----------------------- Line Detech---------------------------------
danger_count = 0

# cropped region
def L_region_of_interest(img):
    mask = np.zeros_like(img)

    height = img.shape[0]
    width = img.shape[1]
    ROI_vertices = [
        (0, 430),
        (230, 250),
        (670, 250),
        (860, height),
        (0, height)
    ]
    vertices = np.array([ROI_vertices], np.int32)

    cv2.fillPoly(mask, vertices, (255,255,255))
    masked_image = cv2.bitwise_and(img, mask)
    return masked_image

def drow_the_lines(img, lines):
    line_image = np.zeros((img.shape[0], img.shape[1], 3), dtype=np.uint8)
    line_ave_image = np.zeros((img.shape[0], img.shape[1], 3), dtype=np.uint8)
    left_fit = []
    right_fit = []
    
    catch_false = False

    for line in lines:
        for x1, y1, x2, y2 in line:
            parameters = np.polyfit((x1,x2), (y1,y2), 1)
            slope = parameters[0]
            intercept = parameters[1]

            # remove unconsidered line
            if abs(slope)>0.3 and abs(slope)<10 :  # set the slope range
                if slope < 0:
                    if x1 > width/2:
                        continue
                    left_fit.append((slope, intercept))
                    # print("L slope: "+str(slope))

                    # if abs(slope) > 5:
                    #     print()
                    #     print(round(slope,2), x1, x2, sep='  ')
                    #     cv2.line(line_image, (x1,y1), (x2,y2), (255, 255, 255), thickness=10)
                    #     catch_false = True
                    #     continue
                    
                        
                else:
                    if x2 < width/2:
                        continue
                    right_fit.append((slope, intercept))
                    # if abs(slope) > 5:
                    #     print()
                    #     print(round(slope,2), x1, x2, sep='  ')
                    #     cv2.line(line_image, (x1,y1), (x2,y2), (255, 255, 255), thickness=10)
                    #     catch_false = True
                    #     continue
                    
                cv2.line(line_image, (x1,y1), (x2,y2), (0, 255, 0), thickness=4)



    left_fit_average = np.average(left_fit, axis=0)
    right_fit_average = np.average(right_fit, axis=0)

    if(len(left_fit) != 0):
        line_ave_image = make_ave_line(line_ave_image,left_fit_average)
    if(len(right_fit) != 0):
        line_ave_image = make_ave_line(line_ave_image,right_fit_average)
        # deviation
    if(len(left_fit) != 0 and len(right_fit) != 0):
        L_slope, L_intercept = left_fit_average
        R_slope, R_intercept = right_fit_average
        Yposition = int(height*0.8)

        Lx = int((Yposition - L_intercept)/L_slope)
        Rx = int((Yposition - R_intercept)/R_slope)
        ave_x = int((Lx+Rx)/2)
        cv2.line(line_ave_image, (Lx,Yposition-10),(Lx,Yposition+10), (0, 0, 255), thickness=2)
        cv2.line(line_ave_image, (Rx,Yposition-10),(Rx,Yposition+10), (0, 0, 255), thickness=2)
        cv2.line(line_ave_image, (ave_x,Yposition-20),(ave_x,Yposition+20), (0, 0, 255), thickness=2)

        centerY = int(height*0.8)
        centerX = int(width/2)
        cv2.line(line_ave_image, (centerX,centerY-20), (centerX,centerY+20), (0, 255, 255), thickness=2)

        road_distance = Rx-Lx
        CenAve_distance = centerX-ave_x
        deviation = round(CenAve_distance/road_distance*100)
        cv2.putText(line_ave_image, str(deviation)+'%', (centerX, centerY), font, 2, (235, 173, 59), 2, cv2.LINE_AA)
        cv2.putText(infoBox, "Deviation: "+str(deviation)+'%', (0,60), cv2.FONT_HERSHEY_COMPLEX, 1, (255,255,255),2)

        if(deviation < -20 and L_slope > 4):
            danger_count += 1
            if(danger_count == 3):
            # danger state
                serial_port.write(b'D\n')
        else:
            danger_count = 0
        


    # if catch_false == True:
    #     cv2.waitKey(5000)

    cv2.imshow("line", line_image)
    cv2.imshow("line_ave", line_ave_image)

    global resultImg

    combine_img = cv2.addWeighted(line_image, 0.0, line_ave_image, 1, 0.0)
    resultImg = cv2.addWeighted(resultImg, 1, combine_img, 1, 0.0)


def make_ave_line(img, param):
    slope, intercept = param
    y1 = height
    y2 = int(y1*0.6)
    x1 = int((y1 - intercept)/slope)
    x2 = int((y2 - intercept)/slope)
    cv2.line(img, (x1,y1), (x2,y2), (0, 0, 255), thickness=8)
    return img

def L_process(image):

   # get masked canny image
    img_gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    img_gray_blur = cv2.GaussianBlur(img_gray,(17, 17),0)
    

    img_canny = cv2.Canny(img_gray_blur, 30, 60)
    img_canny_masked = L_region_of_interest(img_canny)

    cv2.imshow('img_canny_masked', img_canny_masked)
    
    

    # get Hough lines
    lines = cv2.HoughLinesP(img_canny_masked,
                            rho=1,
                            theta=np.pi/180,
                            threshold=70,
                            lines=np.array([]),
                            minLineLength=40,
                            maxLineGap=30)

    
    if lines is not None:
        drow_the_lines(image, lines)

    cv2.circle(resultImg,(0+5,430), 5, (0,255,0), -1)
    cv2.circle(resultImg,(230, 250), 5, (0,255,0), -1)
    cv2.circle(resultImg,(670, 250), 5, (0,255,0), -1)
    cv2.circle(resultImg,(860, height-5), 5, (0,255,0), -1)

    # cv2.imshow('Line Detech', image)

    

#-------------------------- YOLO ---------------------------------------

options = {
        'model': 'cfg/yolov2-tiny.cfg',
        'load': 'bin/yolov2-tiny.weights',
        'threshold': 0.5,
        'gpu': 0.45
    }

tfnet = TFNet(options)
colors = [(90,207,242), (124,242,97), (232,183,125)]
classType = 0;

def yolo(frame):
    front_class = ''
    front_classType = 0
    front_yLocation = 0
    
    results = tfnet.return_predict(frame)
    for result in results:
        tl = (result['topleft']['x'], result['topleft']['y'])
        br = (result['bottomright']['x'], result['bottomright']['y'])
        label = result['label']
        confidence = result['confidence']

        if label == 'car':                                           				
            color = colors[0] 
            classType = 2

        elif label == 'truck' or  label == 'bus':    						
            color = colors[1]
            classType = 3

        elif label == 'bicycle' or  label == 'motorbike' or label == 'person':               	
            color = colors[2]
            classType = 1

        else: continue

        Xcenter = (tl[0]+br[0])/2
        if( br[1] > front_yLocation and Xcenter > 200 and  Xcenter < 500):
            front_yLocation = br[1]
            front_class = label
            front_classType = classType


        text = '{}: {:.0f}%'.format(label, confidence * 100)
        cv2.rectangle(resultImg, tl, br, color, 5)
        cv2.putText(resultImg, text, tl, cv2.FONT_HERSHEY_COMPLEX, 0.5, (255, 255, 255), 1)

    #--------------------ReadDataFromArduino---------------------------------
    arduino_message = ""
    while serial_port.inWaiting() > 0:
        uno = serial_port.read()
        arduino_message = arduino_message + uno.decode("ISO-8859-15")
        if uno == "\n".encode():
            frame = cv2.putText(resultImg, "arduino: " + arduino_message , (10,25), cv2.FONT_HERSHEY_COMPLEX, 0.75, (255, 255, 255), 1)
            print(arduino_message)
            break

    if(arduino_message=="<\n"):
        serial_port.write(('V'+str(front_classType)+'\n').encode())
    arduino_message = ""

    cv2.putText(infoBox, "Front: "+front_class, (0,30), cv2.FONT_HERSHEY_COMPLEX, 1, (255,255,255),2)
    

#-------------------------- start ---------------------------------------

cap = cv2.VideoCapture('videos/v624/4_present.mp4')
# cap = cv2.VideoCapture(0)



while cap.isOpened():
    stime = time.time()
    ret, frame = cap.read()

    # resize
    frame = cv2.resize(frame, (960, 540), interpolation = cv2.INTER_AREA)

    
    height = frame.shape[0]
    width = frame.shape[1]

    resultImg = frame.copy()
    infoBox = np.zeros((100, 300, 3), dtype=np.uint8)
   
    cv2.rectangle(infoBox,(width,0),(0,100),(45, 68, 84),-1)
    cv2.putText(infoBox, "Front: ", (0,30), cv2.FONT_HERSHEY_COMPLEX, 1, (255,255,255),2)
    cv2.putText(infoBox, "Deviation: ", (0,60), cv2.FONT_HERSHEY_COMPLEX, 1, (255,255,255),2)
    cv2.putText(infoBox, "Traffic Light: ", (0,90), cv2.FONT_HERSHEY_COMPLEX, 0.9, (255,255,255),2)

    L_process(frame)
    T_process(frame)
    yolo(frame)

    area = resultImg[0:100,width-300:width] 
    area_info = cv2.addWeighted(area, 0.3, infoBox, 0.7, 0.0)
    resultImg[0:100,width-300:width] = area_info


    cv2.imshow("combine result", resultImg)

    cv2.setMouseCallback('combine result', click_event)
    print('FPS {:.1f}'.format(1 / (time.time() - stime)))
    



    wk = cv2.waitKey(1)
    if wk & 0xFF == ord('q'):
        cap.release()

    # while wk & 0xFF == ord(' '):
    #     wk = cv2.waitKey(40)
    #     if wk & 0xFF != ord(' '):
    #         print('break pause')


cv2.destroyAllWindows()

