from django.shortcuts import render, redirect
from django.template import loader
from django.contrib.auth import authenticate, login as log_in
from django.contrib.auth.decorators import login_required
from .forms import DocumentForm, ItemForm
from .models import Document, Item, Settings
from django.http import HttpResponse
import io as BytesIO
from xhtml2pdf import pisa
from django.template.loader import get_template
from django.template import Context
from django.http import HttpResponse
from cgi import escape


def index(request):
    return HttpResponse(render(request, 'forms/base.html'))


def login(request):
    if request.method == "POST":
        username = request.POST['username']
        password = request.POST['password']
        user = authenticate(request, username=username, password=password)
        if user is not None:
            log_in(request, user)
            return HttpResponse(render(request, 'forms/base.html'))
    else:
        return HttpResponse(render(request, 'forms/../templates/registration/login.html'))


@login_required()
def logout(request):
    logout(request)
    return HttpResponse(render(request, 'forms/../templates/registration/login.html'))


@login_required()
def documents(request):
    docs = Document.objects.all().order_by('-created_date')
    template = loader.get_template('forms/documents.html')
    context = {
        'documents': docs,
    }
    return HttpResponse(template.render(context, request))


@login_required()
def new_document(request):
    if request.method == 'POST':
        document_form = DocumentForm(request.POST)
        if document_form.is_valid():
            document = document_form.save()
            return redirect(document_items, series=document.series, number=document.number)
        else:
            return HttpResponse(render(request, 'forms/new_document.html', {'form': document_form}))
    else:
        document_form = DocumentForm()
        return HttpResponse(render(request, 'forms/new_document.html', {'form': document_form}))


@login_required()
def document_items(request, series, number):
    document = Document.objects.get(series=series, number=number)
    if request.method == 'POST':
        item_form = ItemForm(request.POST)
        if item_form.is_valid():
            item = item_form.instance
            item.document = document
            item.save()
    items = Item.objects.filter(document=number)
    item_form = ItemForm()
    template = loader.get_template('forms/document_items.html')
    context = {
        'document': document,
        'items': items,
        'form': item_form
    }
    return HttpResponse(template.render(context, request))


def render_to_pdf(template_src, context_dict):
    template = get_template(template_src)
    context = context_dict
    html = template.render(context)
    result = BytesIO.BytesIO()

    pdf = pisa.pisaDocument(BytesIO.BytesIO(html.encode("UTF-8")), result)
    if not pdf.err:
        return HttpResponse(result.getvalue(), content_type='application/pdf')
    return HttpResponse('We had some errors<pre>%s</pre>' % escape(html))


def get_pdf(request, document_number):
    document = Document.objects.get(number=document_number)
    items = Item.objects.filter(document=document_number)
    settings = Settings.objects.first()
    members = settings.commission_members.all()
    user = request.user
    return render_to_pdf(
            'pdf_template.html',
            {
                'pagesize': 'A4',
                'document': document,
                'items': items,
                'settings': settings,
                'members': members,
                'user': user
            }
        )