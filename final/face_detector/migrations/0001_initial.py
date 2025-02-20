# Generated by Django 3.2.12 on 2022-04-10 12:57

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='User',
            fields=[
                ('u_id', models.AutoField(primary_key=True, serialize=False)),
                ('u_name', models.CharField(max_length=18, unique=True)),
                ('u_icon', models.ImageField(upload_to='user_icon/')),
                ('u_password', models.CharField(max_length=254)),
                ('u_sign', models.TextField()),
                ('u_email', models.EmailField(max_length=254)),
                ('u_ticket', models.CharField(max_length=30, null=True)),
            ],
        ),
        migrations.CreateModel(
            name='UploadImage',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('image_h', models.PositiveIntegerField(default=200)),
                ('image_w', models.PositiveIntegerField(default=200)),
                ('img_path', models.ImageField(height_field=models.PositiveIntegerField(default=200), upload_to='user_photo/', width_field=models.PositiveIntegerField(default=200))),
                ('user', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='face_detector.user')),
            ],
        ),
        migrations.CreateModel(
            name='DoneImage',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('image_h', models.PositiveIntegerField(default=200)),
                ('image_w', models.PositiveIntegerField(default=200)),
                ('done_time', models.TimeField(auto_now_add=True)),
                ('image_done', models.ImageField(height_field=models.PositiveIntegerField(default=200), upload_to='img_done/', width_field=models.PositiveIntegerField(default=200))),
                ('upload_image', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='face_detector.uploadimage')),
            ],
        ),
    ]
