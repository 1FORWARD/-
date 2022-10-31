import sensor,image,lcd,utime
from machine import UART
from fpioa_manager import fm
from Maix import GPIO

#常用初始化
lcd.init()
sensor.reset()                      #复位摄像头
sensor.set_pixformat(sensor.RGB565) #设置像素格式 RGB565
sensor.set_framesize(sensor.QVGA)   #设置帧尺寸 QVGA (320x240)
sensor.skip_frames(time = 2000)     #跳过不稳定画面

#映射串口引脚
fm.register(8, fm.fpioa.UART1_RX, force=True)
fm.register(9, fm.fpioa.UART1_TX, force=True)

#初始化串口
uart = UART(UART.UART1, 115200, 8, 1, 0, timeout=1000 , read_buf_len=4096)

#红色阈值
red_threshold = (87, 21, 27, 93, -5, 92)
#蓝色阈值
blue_threshold = (14, 87, -83, 127, -113, -14)
#绿色阈值
green_threshold = (37, 97, -7, -101, -50, 47)
#黄色阈值
yellow_threshold =  (52, 100, -17, 1, 21, 127)

#色块阈值
block_threshold = (0,0,0,0,0,0)

#读取电平引脚映射
fm.register(10,fm.fpioa.GPIO1)
red=GPIO(GPIO.GPIO1,GPIO.IN)

fm.register(11,fm.fpioa.GPIO2)
blue=GPIO(GPIO.GPIO2,GPIO.IN)

fm.register(12,fm.fpioa.GPIO3)
green=GPIO(GPIO.GPIO3,GPIO.IN)

fm.register(13,fm.fpioa.GPIO4)
yellow=GPIO(GPIO.GPIO4,GPIO.IN)

#控制led引脚映射
fm.register(14,fm.fpioa.GPIO0)
led_r=GPIO(GPIO.GPIO0,GPIO.OUT)

fm.register(15,fm.fpioa.GPIO5)
led_g=GPIO(GPIO.GPIO5,GPIO.OUT)

fm.register(16,fm.fpioa.GPIO6)
led_b=GPIO(GPIO.GPIO6,GPIO.OUT)

fm.register(17,fm.fpioa.GPIO7)
led_y=GPIO(GPIO.GPIO7,GPIO.OUT)

#熄灭所有led
led_r.value(1)
led_g.value(1)
led_b.value(1)
led_y.value(1)

#跳出等待信号循环变量
i = 0

#寻找最大色块函数定义
def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob

#数据发送函数
def sending_data(cx,cy,cw,ch):
    global uart;
    data = ustruct.pack("<bbhhhhb",      #格式为俩个字符俩个短整型(2字节)
                   0x2C,                        #帧头1
                   0x12,                        #帧头2
                   int(cx), # up sample by 4    #数据1
                   int(cy), # up sample by 4    #数据2
                   int(cw), # up sample by 4    #数据1
                   int(ch), # up sample by 4    #数据2
                   0x5B)
    uart.write(data);   #必须要传入一个字节数组


#主循环
while True:

    while i==0:
        if red.value() == 1:
                block_threshold = red_threshold
                led_r.value(0)
                utime.sleep_ms(1000)
                i = 1;

        if blue.value() == 1:
                block_threshold = blue_threshold
                led_b.value(0)
                utime.sleep_ms(1000)
                i = 1;

        if green.value() == 1:
                block_threshold = green_threshold
                led_g.value(0)
                utime.sleep_ms(1000)
                i = 1;

        if yellow.value() == 1:
                block_threshold = yellow_threshold
                led_y.value(0)
                utime.sleep_ms(1000)
                i = 1;

    img=sensor.snapshot()
    blobs = img.find_blobs([block_threshold],merge=True)#把拍摄的一张图片里满足的色块纳入集合中

    if blobs:
          max_blob = find_max(blobs)#调用函数，返回最大色块
          img.draw_rectangle((max_blob.x(),max_blob.y(),max_blob.w(),max_blob.h()),color=(255,0,0))#用红色框出最大色块
          img.draw_string(max_blob.x(),max_blob.y(), "(x,y) =")
          img.draw_string(max_blob.x()+40,max_blob.y(), str(max_blob.cx()))
          img.draw_string(max_blob.x()+60,max_blob.y(), str(max_blob.cy()))#在框图左上角显示色块的中心坐标
          #print(max_blob.x(),max_blob.y(),max_blob.w(),max_blob.h())
          cx=int(max_blob[5]/2)
          cy=max_blob[6]
          cw=max_blob[2]
          ch=max_blob[3]
          OUT_DATA =bytearray([0x2C,0x12,cx,cy,cw,ch,0x5B])
          uart.write(OUT_DATA)
          #print(OUT_DATA)

    lcd.display(img)

