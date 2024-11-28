from django.db import models

class File(models.Model):
    filename = models.CharField(max_length=255)
    uploaded_at = models.DateTimeField(auto_now_add=True)
    result = models.TextField(blank=True)

    def __str__(self):
        return self.filename
