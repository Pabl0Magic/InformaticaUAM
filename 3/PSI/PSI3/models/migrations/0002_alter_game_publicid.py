# Generated by Django 3.2.17 on 2023-05-04 08:43

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('models', '0001_initial'),
    ]

    operations = [
        migrations.AlterField(
            model_name='game',
            name='publicId',
            field=models.IntegerField(default=925323, help_text='Unique public id for game'),
        ),
    ]