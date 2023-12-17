from django.contrib import admin
from a.models import *

class UserInformationsInline(admin.StackedInline):
    # 繼承自admin.StackedInline, UserInformation 內嵌的設定
    model = UserInformations
    can_delete = False # 不可單獨刪除 UserInformation
    verbose_name_plural = 'user informations' #內嵌下顯示的名稱

class UserProfileAdmin(admin.ModelAdmin): # 設定要顯示的內容, 分組方式... 
    inlines = (UserInformationsInline, ) # 將UserInformationInline 內嵌到UserProfile當中
# Register your models here.
admin.site.register(UserProfile, UserProfileAdmin)