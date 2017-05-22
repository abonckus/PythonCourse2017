from django.db import models


class Commissioner(models.Model):
    first_name = models.CharField(max_length=30)
    last_name = models.CharField(max_length=30)
    position = models.CharField(max_length=50, default='fights teutons')

    def __str__(self):
        return self.first_name + ' ' + self.last_name


class DocumentSeries(models.Model):
    series_code = models.CharField(max_length=2, primary_key=True)
    description = models.CharField(max_length=50)

    def __str__(self):
        return self.series_code


class Settings(models.Model):
    company_name = models.CharField(max_length=50, default='COMPANY')
    commission_members = models.ManyToManyField(Commissioner, max_length=4)
    document_series = models.ManyToManyField(DocumentSeries)

    def __str__(self):
        return self.company_name


class Document(models.Model):
    number = models.IntegerField(primary_key=True)
    series = models.ForeignKey(DocumentSeries)
    seller = models.CharField(max_length=50)
    created_date = models.DateField()

    def __str__(self):
        return self.series.series_code + str(self.number)


class Item(models.Model):
    document = models.ForeignKey(Document)
    name = models.CharField(max_length=50)
    unit_of_measurement = models.CharField(max_length=10)
    quantity = models.IntegerField()
    price = models.DecimalField(decimal_places=2, max_digits=7)
    purpose = models.CharField(max_length=100)
