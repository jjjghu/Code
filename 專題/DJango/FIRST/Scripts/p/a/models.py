from django.db import models
from django.contrib.auth.models import AbstractUser
class UserProfile(AbstractUser): # 繼承自AbstractUser
    phone = models.CharField(max_length = 20) # 其他都已經在 AbstractUser 當中有了
    class Meta:
        db_table = 'user_profile'

    groups = models.ManyToManyField(
        'auth.Group',
        verbose_name='groups',
        blank=True,
        help_text='The groups this user belongs to. A user will get all permissions granted to each of their groups.',
        related_name="%(app_label)s_%(class)s_related",
        related_query_name="%(app_label)s_%(class)ss",
    )

    user_permissions = models.ManyToManyField(
        'auth.Permission',
        verbose_name='user permissions',
        blank=True,
        help_text='Specific permissions for this user.',
        related_name="%(app_label)s_%(class)s_related",
        related_query_name="%(app_label)s_%(class)ss",
    )
    #甚麼反向字段甚麼鬼的, 使用 Chat GPT 4 解決

class UserInformations(models.Model):#使用UserSet 將兩個物件關聯起來
    # ForeignKey 一對多
    # OneToOneField 如其名
    user_profile = models.OneToOneField(UserProfile, on_delete=models.CASCADE, related_name='informations')
    # 將兩個class 連接起來 # 可以使用 user_profile.informations 來訪問 UserInformations
    token = models.CharField(max_length = 20)
    gender = models.IntegerField(default=0) # 預設為未選擇 
    fcm_id = models.CharField(max_length = 20)
    address = models.CharField(max_length = 50)
    weight = models.CharField(max_length = 20)