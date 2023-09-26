from django.contrib import admin
from .models import Questionnaire, Question, Answer, Game, Participant, Guess, User


# Register your models here.
admin.site.register(Questionnaire)
admin.site.register(Question)
admin.site.register(Answer)
admin.site.register(Game)
admin.site.register(Participant)
admin.site.register(Guess)
admin.site.register(User)
