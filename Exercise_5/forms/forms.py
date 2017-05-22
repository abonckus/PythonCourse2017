from django import forms
from .models import Document, Item
from django.forms.extras import SelectDateWidget
from datetime import date
from django.views.generic.edit import CreateView

class ItemForm(forms.ModelForm):
    class Meta:
        model = Item
        fields = ['name', 'quantity', 'unit_of_measurement', 'price', 'purpose']


class DocumentForm(forms.ModelForm):
    created_date = forms.DateField(widget=SelectDateWidget(), initial=date.today())

    class Meta:
        model = Document
        fields = ['number', 'series', 'seller', 'created_date']

