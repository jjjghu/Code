from p import settings
from .models import UserProfile, UserInformations # 將 UserProfile 引入
from django.shortcuts import render # 網頁渲染
from django.shortcuts import redirect # 重新定位
from django.http.response import JsonResponse
from django.core.mail import send_mail
from django.views.decorators.csrf import csrf_exempt
from django.http import HttpResponse
from django.contrib import messages # 確認訊息
from django.contrib.auth import authenticate, login, logout #登入登出驗證的東西
import json
import random 
from datetime import datetime, timedelta # 紀錄時間的東西

# Create your views here.
def welcome(request):
    return HttpResponse("Welcome")

@csrf_exempt
def send(request): # 最初的寄信, in 30 天
    if request.method == "POST":
        if request.body:
            try:
                send_mail("嘗試發送信件", "恭喜你成功發送訊息！", settings.DEFAULT_FROM_EMAIL, ["chiuliyou@gmail.com"])
                mess = {"message": "YES"}
            except Exception as e:
                print(e)
                mess = {"message": "ouch"}
        return JsonResponse(mess)

def home(request): # 當連接到這個網站之後, 顯示網站內容
    CurUser = request.user
    # 獲取目前發出請求的用戶
    if request.method == 'POST':
        #在獲取輸入之前要先檢查
        try:
            inform = CurUser.informations
            # 先確保CurUser.informations 存在
        except UserInformations.DoesNotExist:
            inform = UserInformations.objects.create(user_profile = CurUser)
            # 不存在就創建一個新的
        inform.token  = request.POST['token'] #獲取輸入, 設定UserInformation, 追求效率 => 只將有更改值的更新
        inform.gender = request.POST['gender']
        inform.fcm_id = request.POST['frm_id']
        inform.address= request.POST['address']
        inform.weight = request.POST['weight']
        CurUser.phone = request.POST['phone']
        CurUser.email = request.POST['email']
        CurUser.save() # 兩個都要個別更新
        inform.save()
        # 若加上沒有輸入就保持原樣卻又想要使用placeholder, 就會多出很多if else, 故使用此方式
        messages.success(request, "Woo, Successfully Save Data!")
        # 可以用try catch 去增加沒有成功存檔的情況
        return redirect('home')
    return render(request, "a/index.html", {'CurUser':CurUser, 'username':CurUser.username})
    #方便在html當中顯示用戶當前的個人資訊內容
def register(request):
    if request.method == "POST" :# 如果是 Post -> 表示提交表單
        name = request.POST['username'] # 取得獲取的資訊
        gmail = request.POST['gmail']
        userphone = request.POST['phone']
        if UserProfile.objects.filter(username=name) or UserProfile.objects.filter(email=gmail) or len(name) > 20:
            #姓名 / 信箱相同, 姓名過長...
            messages.error(request, "Guess what?...Invalid! Boo")
            return redirect('home')
        myuser = UserProfile.objects.create_user(username = name, phone = userphone, email = gmail, password = request.POST['password'])# 創建使用者
        myuser.save() # 存入使用者
        return redirect('signin') # 轉換到登入頁面
    return render(request, "a/register.html") # GET 就進入登入頁面 (POST以外的方式)
    # render = 渲染 HTML 前端網頁

def signin(request): # 登入
    if request.method == 'POST':
        user = authenticate(username=request.POST['username'], password=request.POST['password']) # 驗證是否正確
        if user:
            login(request, user)
            return redirect('home')
        else:
            messages.error(request, "NO") # 登入
            return redirect('home')
    return render(request, "a/signin.html") # 其他的請求就進入登入頁面

def signout(request):
    logout(request) # 登出
    messages.success(request, "Logged Out Successfully!!") # 訊息顯示成功
    return redirect('home') # 回到主頁面

def sendcode(request):
    if request.method == 'POST': # 收到表單
        try: #傳送驗證碼 
            code = str(random.randint(100000, 999999)) #需要記住, 0開頭...沒關係的...沒關係
            request.session['actual_code'] = code
            request.session['code_born'] = datetime.now().timestamp()
            send_mail("驗證碼", "{}".format(code), settings.DEFAULT_FROM_EMAIL, [request.POST['gmail']])
            return redirect('checkcode') #驗證介面
        except Exception as e: # 寄信失敗
            messages.error(request, "Fail to send the email!")
            return redirect('home')
    return render(request, 'a/sendcode.html') # 使用 GET 請求 => 準備打表單

def checkcode(request):
    if request.method == 'POST':
        # messages.success(request, "Success!") if request.session.get('actual_code') == request.POST['entercode'] and request.session.get('code_born') - datetime.now().timestamp else messages.error(request, "Fail!")
        # OMG it's so ugly no 
        if request.session.get('actual_code') == request.POST['entercode'] and datetime.now().timestamp() - request.session.get('code_born')< 60:
            messages.success(request, "Success")
            return redirect('resetPassword')
        else:# 超過時間或是驗證碼錯誤
            messages.error(request, "FAIL!")
            return redirect('home')
    return redirect(request, 'a/checkcode.html') # 自己當然是渲染自己得網頁類榮

def resetPassword(request):
    if request.method == 'POST':
        user = UserProfile.objects.get(username = request.POST['username']) # 獲取目標User
        user.set_password(request.POST['newpass'])# 設定新密碼
        user.save() # 蓋掉舊的資訊
        messages.success(request, "Successfully reset Password ! ") # 訊息傳送
        return redirect('home') # 回到主頁面   
    return render(request,'a/resetPassword.html')
# render 顯示內容
# redirect 轉換連結