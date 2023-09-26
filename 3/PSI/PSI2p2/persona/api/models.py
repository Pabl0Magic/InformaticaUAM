from django.db import models
import uuid  # Required for unique ids

# Create your models here.
class Persona(models.Model):
    
    # Fields
    id = models.UUIDField(primary_key=True, default=uuid.uuid4,
        help_text="Unique ID for this person")
    nombre = models.CharField(max_length=100)
    apellido = models.CharField(max_length=100)
    email = models.CharField(max_length=100)

    class Meta:
        ordering = ['-id']
