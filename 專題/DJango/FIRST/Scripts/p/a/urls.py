from django.contrib import admin
from django.urls import path, include 
from a import views # 獲取 app / views
urlpatterns =[
    # 當連結到這個網頁時 獲取 app / views 下的 welcome並執行
    path('a', views.welcome),
    path('send', views.send),
    path('', views.home, name = "home"), # 初始頁面
    path('register', views.register, name = "register"),
    path('signin', views.signin, name = "signin"),
    path('signout', views.signout, name = "signout"), # 取名就像 const, 其他地方用 signout 來指代, 要改只要改一處
    path('sendcode', views.sendcode, name = "sendCode"),
    path('checkcode', views.checkcode, name = "checkcode"),
    path('resetPassword', views.resetPassword, name = "resetPassword")
]
