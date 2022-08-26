from django.urls import path

from . import views

urlpatterns = [
    path('main/', views.home),   # 监控系统主要
    path('get_video', views.get_video),     # 监控系统摄像头的接口
    path('register/', views.register),    # 注册
    path('', views.login),     # 登录
    path('face_login/', views.face_login),   # 人脸登录
    path('baseinfo/', views.user_base_info)  # 用户信息
]
