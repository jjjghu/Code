from django.contrib import admin
from django.urls import path, include
urlpatterns =[
    path('admin/', admin.site.urls),
    path('',include('a.urls')),
    # p 接上 app.urls 當中的內容
]
