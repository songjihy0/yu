import base64
import os
import random
import socket
import sys
import threading
import time

import cv2
import face_recognition
from django.contrib.auth.hashers import make_password, check_password
from django.http import StreamingHttpResponse, HttpResponseRedirect, HttpResponse
from django.shortcuts import render

from .models import User

# 版本检查
if sys.version_info.major == 2:
    print('please run this program with python3')
    sys.exit(0)

debug = True


# 检查摄像头是否打开
def camera_is_opened():
    global stream, cap
    cap = cv2.VideoCapture(stream)


# 常规变量的定义
c = 80
width, height = c * 4, c * 3
width, height = 640, 480
# width,height = 320,240
resolution = str(width) + "x" + str(height)
orgFrame = None
encodedImage = None
Running = True
ret = False
stream = 0
# stream = 'rtsp://admin:abc12345@192.168.1.64'
face_locations = []
face_encoding = []
face_names = []
known_face_names = []
known_face_encodings = []
process_this_frame = True
try:
    camera_is_opened()
    cap = cv2.VideoCapture(stream)
except:
    print('Unable to detect camera! \n')

face_dict = {}
static_url = '/Users/yzp/PycharmProjects/final/static/media/'
for known_user_path in os.listdir('/Users/yzp/PycharmProjects/final/static/media/user_icon'):
    if known_user_path == '.DS_Store':
        continue
    load_img = face_recognition.load_image_file(static_url + 'user_icon/' + known_user_path)
    face_encode = face_recognition.face_encodings(load_img)[0]
    user_name = known_user_path.split('_')[0]
    face_dict[user_name] = face_encode


def get_encoded_img():
    return encodedImage


orgFrame = None
ret = False
Running = True


# 从摄像头获取实时视频
def get_image():
    global orgFrame
    global ret
    global Running
    global stream, cap
    global width, height
    global encodedImage

    while True:
        if Running:
            try:
                if cap.isOpened():
                    # 读取视频的画面
                    ret, orgFrame = cap.read()
                    # 将画面变成原来大小的 1/4，使人脸识别更快
                    small_frame = cv2.resize(orgFrame, (0, 0), fx=0.25, fy=0.25)
                    # 将图片颜色的格式由 BGR 改为 RGB（由 OpenCV 获取的视频是 BGR 格式，人脸识别需要 RGB 格式）
                    rgb_small_frame = small_frame[:, :, ::-1]
                    if process_this_frame:
                        # 寻找人脸的位置，以及人脸是否匹配已知人脸
                        face_locations = face_recognition.face_locations(rgb_small_frame)
                        face_encodings = face_recognition.face_encodings(rgb_small_frame, face_locations)
                        face_names = []
                        # 为每一个人脸增加名字
                        for face_encoding in face_encodings:
                            for known_name in face_dict:
                                matches = face_recognition.compare_faces(face_dict[known_name], face_encodings)
                                name = "Unknown"
                                # 如果人脸匹配已知人脸，将已知人脸的名字加入
                                if str(matches[0]) == 'True':
                                    name = known_name
                                face_names.append(name)
                        # process_this_frame = not process_this_frame

                    # 将人脸框出
                    for (top, right, bottom, left), name in zip(face_locations, face_names):
                        top *= 4
                        right *= 4
                        bottom *= 4
                        left *= 4
                        cv2.rectangle(orgFrame, (left, top), (right, bottom), (0, 0, 255), 2)
                        cv2.rectangle(orgFrame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
                        font = cv2.FONT_HERSHEY_DUPLEX
                        cv2.putText(orgFrame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)
                    _, encodedImage = cv2.imencode(".jpg", orgFrame)

                    time.sleep(0.04)

                else:
                    time.sleep(0.04)
            except GeneratorExit:
                print("Client is disconnected-1!")
                time.sleep(0.04)
                cap = cv2.VideoCapture(stream)
            except Exception as e:
                print("Client is disconnected-3!")
                print(e)
                time.sleep(0.04)
                cap = cv2.VideoCapture(stream)
        else:
            time.sleep(0.05)


th1 = threading.Thread(target=get_image)
th1.setDaemon(True)
th1.start()


# 获取主机ip
def get_host_ip():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(('8.8.8.8', 80))
        ip = s.getsockname()[0]
    finally:
        s.close()

    return ip


# 获取服务端ip
def get_client_ip(request):
    x_forwarded_for = request.META.get('HTTP_X_FORWARDED_FOR')
    if x_forwarded_for:
        ip = x_forwarded_for.split(',')[0]  # 所以这里是真实的ip
    else:
        ip = request.META.get('REMOTE_ADDR')  # 这里获得代理ip
    return ip


class ImgSender:
    # width,height = 640,480
    width, height = 320, 240
    resolution = str(width) + "x" + str(height)
    ret = False

    def __init__(self):
        self.ret = False

    def __new__(cls):
        return super(ImgSender, cls).__new__(cls)

    def image_sender(self):
        while True:
            if Running:
                try:
                    encoded_image = get_encoded_img()
                    time.sleep(0.04)
                    yield (b'--frame\r\n'
                           b'Content-Type: image/jpeg\r\n\r\n' + encoded_image.tobytes() + b'\r\n')
                except GeneratorExit:
                    print("Client is disconnected-1!")
                    time.sleep(0.01)
                except Exception:
                    print("Client is disconnected-3!")
                    time.sleep(0.01)
            else:
                time.sleep(0.01)


# 将摄像头获取的画面转为图像流
def get_video(request):
    sender = ImgSender()
    try:
        if request is not None:
            return StreamingHttpResponse(sender.image_sender(), content_type='multipart/x-mixed-replace; boundary=frame')
        else:
            print("Client is disconnected")
    except GeneratorExit:
        print("Client is disconnected-2!")
        del sender
    except:
        print("Client is disconnected-4!")
        del sender


# 定义监控系统的主页
def home(request):
    context = {"Title": "Video", "LocalIP": get_host_ip(), "SessionID": get_client_ip(request),
               "url": "http://127.0.0.1:8000/get_video"}
    # context["url"] = "http://" + get_host_ip() + ":8000/getVideo"
    return render(request, 'index.html', context)


# 注册
def register(request):
    if request.method == 'GET':
        return render(request, 'register.html')
    if request.method == 'POST':
        # 注册开始
        uname = request.POST.get('username')
        if User.objects.filter(u_name=uname) is not None:
            # 密码加密
            password = request.POST.get('password')
            password = make_password(password)
            # 传入用户图像
            uicon = request.POST.get('face')
            type(uicon)
            # 删除编码前标记
            base64str = uicon[22:]
            if len(base64str) % 3 == 1:
                base64str += "=="
            elif len(base64str) % 3 == 2:
                base64str += "="
            # 解码
            img_str = base64.b64decode(base64str)
            # 文件地址
            url = u"/Users/yzp/PycharmProjects/final/static/media/"
            # 图片命名
            img_name = uname + '_icon_' + str(int(time.time())) + '.jpg'
            url = url + 'user_icon/' + img_name
            with open(url, 'wb') as f:
                f.write(img_str)
            uicon = 'user_icon/' + img_name

            User.objects.create(u_name=uname, u_password=password, u_icon=uicon)
            return HttpResponseRedirect('/')
        return render(request, 'register.html', {'name': uname})


# 登录
def login(request):
    if request.method == 'GET':
        return render(request, 'login.html')
    if request.method == 'POST':
        # 如果登录成功，绑定参数到 cookie 中，set_cookie
        name = request.POST.get('username')
        password = request.POST.get('password')

        # 检查用户是否在数据库中
        if User.objects.filter(u_name=name).exists():
            user = User.objects.get(u_name=name)
            print(user)
            if check_password(password, user.u_password):
                request.session['uname'] = user.u_name
                ticket = ''
                for i in range(15):
                    s = 'abcdefghijklmnopqrstuvwxyz'
                    # 获取随机的字符串
                    ticket += random.choice(s)
                now_time = int(time.time())
                ticket = 'TK' + ticket + str(now_time)
                # 绑定令牌到 cookie 里面
                response = HttpResponseRedirect('/main/')
                # max_age 存在时间
                response.set_cookie('ticket', ticket, max_age=10000)
                # 存在服务端
                user.u_ticket = ticket
                user.save()
                return response
            else:
                return render(request, 'login.html', {'password': '用户密码错误'})
        else:
            return render(request, 'login.html', {'name': '用户不存在'})


# 人脸登录
def face_login(request):
    if request.method == 'GET':
        return render(request, 'face_login.html')
    if request.method == 'POST':
        # 用户图像传入
        face_img = request.POST.get('face')
        # 删除 base64 的编码学习，提取 base64 编码数据
        base64str = face_img[22:]
        # 对 base64 数据进行补全，防止数据不能被编码成图片
        if len(base64str) % 3 == 1:
            base64str += "=="
        elif len(base64str) % 3 == 2:
            base64str += "="
        # 对 base64 数据进行解码
        img_str = base64.b64decode(base64str)
        # 准备写入图片，添加图片保存地址
        # 图片命名
        img_name = 'face_' + str(int(time.time())) + '.jpg'
        unknown_url = static_url + 'login_img/' + img_name
        # 写入图片
        with open(unknown_url, 'wb') as f:
            f.write(img_str)
        # 确保能加载传过来的图片
        time.sleep(1)
        # 创建空字典用于存放{user: face_encode}
        face_dic = face_dict
        try:
            load_unknow_img = face_recognition.load_image_file(unknown_url)
            unknown_img_encoding = face_recognition.face_encodings(load_unknow_img)
            for i in face_dic:
                results = face_recognition.compare_faces(face_dic[i], unknown_img_encoding)
                if str(results[0]) == 'True':
                    user = User.objects.get(u_name=i)
                    request.session['uname'] = user.u_name
                    ticket = ''
                    for i in range(15):
                        s = 'abcdefghijklmnopqrstuvwxyz'
                        # 获取随机的字符串
                        ticket += random.choice(s)
                    now_time = int(time.time())
                    ticket = 'TK' + ticket + str(now_time)
                    # 绑定令牌到cookie里面
                    response = HttpResponseRedirect('/main/')
                    # 保存时间
                    response.set_cookie('ticket', ticket, max_age=10000)
                    # 存在服务端
                    user.u_ticket = ticket
                    user.save()
                    return response
                else:
                    continue
            else:
                title = '用户不存在，请注册'
                msg = '用户不存在，请注册'
                return render(request, 'redirect.html', {'msg': msg, 'title': title})
        except Exception as e:
            print(e)
            title = '用户不存在，请注册'
            msg = '用户不存在，请注册'
            return render(request, 'redirect.html', {'msg': msg, 'title': title})


# 注销
def logout(request):
    if request.method == 'GET':
        # 删除用户 session
        response = HttpResponseRedirect('/')
        return response


def user_base_info(request):
    uname = request.session['uname']
    if request.method == 'GET':
        return render(request, 'user_base_info.html', {'uname': uname})
    if request.method == 'POST':
        user = User.objects.get(u_name=uname)
        new_user_icon: object = request.FILES.get('img')
        sign = request.POST.get('sign')
        email = request.POST.get('email')
        # 构造文件名以及文件路径
        new_user_icon.name = uname + '_icon_' + str(int(time.time())) + '.' + new_user_icon.name.split('.')[-1]
        if new_user_icon.name.split('.')[-1] not in ['jpeg', 'jpg', 'png']:
            return HttpResponse('输入文件有误')
        try:
            user.u_icon = new_user_icon
            print('图象>>>>>', user.u_icon)
            user.u_email = email
            user.u_sign = sign
            user.save()
            url = u"/Users/yzp/PycharmProjects/faceRec/static/media/"
            url = url + 'user_icon/' + new_user_icon.name
            print('图象url>>>>>', url)
            with open(url, 'wb') as f:
                # pic.chunks()循环读取图片内容，每次只从本地磁盘读取一部分图片内容，
                # 加载到内存中，并将这一部分内容写入到目录下，
                # 写完以后，内存清空；下一次再从本地磁盘读取一部分数据放入内存。
                # 就是为了节省内存空间。
                for data in new_user_icon.chunks():
                    f.write(data)
        except Exception as e:
            print(e)
        return render(request, 'user_base_info.html', {'uname': uname})




