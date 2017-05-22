from django.conf.urls import url
from . import views
from django.contrib.auth import views as auth_views

urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^login', auth_views.login, name='login'),
    url(r'^logout', auth_views.logout, name='logout'),
    url(r'^documents', views.documents, name='documents'),
    url(r'^new_document', views.new_document, name='new_document'),
    url(r'^items/(?P<series>[a-zA-Z]{2})/(?P<number>[0-9]+)/', views.document_items, name='items'),
    url(r'^get_pdf/(?P<document_number>[0-9]+)/', views.get_pdf, name='get_pdf')
]