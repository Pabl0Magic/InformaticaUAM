from django.urls import path
from django.conf.urls import url
from models import views as core_views
from . import views

urlpatterns = [
    path('', views.index, name='home_unsigned'),
    url(r'^signup/$', core_views.signup, name='signup')
]
