from django.contrib import admin
from .models import User, UploadImage, DoneImage

# Register your models here.
admin.site.register(User)
admin.site.register(UploadImage)
admin.site.register(DoneImage)


class UserAdmin(admin.ModelAdmin):
    list_display = ['pk', 'u_name', 'u_icon', 'u_password', 'u_sign', 'u_email']
    list_filter = ['u_name']
    list_per_page = 5

