from django.db import models
from django.urls import reverse
from django.contrib.auth.models import AbstractUser
from django.core.validators import MaxValueValidator, MinValueValidator
import random
import uuid
WAITING = 1
QUESTION = 2
ANSWER = 3
LEADERBOARD = 4


# TODO You need to create your oen class inherity from UserCreationForm
# and we must redefine the meta.

class User(AbstractUser):
    # Tambien authenticate?
    pass


class Questionnaire(models.Model):

    title = models.CharField(max_length=100)
    created_at = models.DateTimeField('created at', auto_now_add=True)
    updated_at = models.DateTimeField('updated at', auto_now=True)
    user = models.ForeignKey('User', on_delete=models.CASCADE)

    def get_absolute_url(self):
        """Returns the url to access a particular author instance."""
        return reverse('questionnaire-detail', args=[str(self.id)])

    def __str__(self):
        return self.title


class Question(models.Model):

    # question_id = models.UUIDField(primary_key=True, default=uuid.uuid4,
    #                                help_text="Unique id for question")
    question = models.TextField(max_length=500, help_text="Write the question")
    questionnaire = models.ForeignKey('Questionnaire',
                                      on_delete=models.CASCADE,
                                      )
    created_at = models.DateTimeField('created at', auto_now_add=True)
    updated_at = models.DateTimeField('updated at', auto_now=True)
    answerTime = models.PositiveIntegerField(
        'answer time',
        null=True,
        blank=True
    )
    noAnswer = models.PositiveIntegerField(
        'number answer',
        primary_key=False,
        validators=[MaxValueValidator(4), MinValueValidator(0)],
        default=0
    )

    def get_absolute_url(self):
        """Returns the url to access a particular author instance."""
        return reverse('question-detail', args=[str(self.id)])

    def __str__(self):
        return self.question


class Answer(models.Model):
    # answer_id = models.UUIDField(primary_key=True, default=uuid.uuid4,
    #                              help_text="Unique id for answer")
    answer = models.TextField(max_length=500, help_text="Write the answer")
    question = models.ForeignKey('Question', on_delete=models.CASCADE,
                                 )
    correct = models.BooleanField('correct')

    def save(self, *args, **kwargs):

        if self.pk is None:
            self.question.noAnswer += 1

        elif self.correct and not Answer.objects.filter(
            question=self.question, correct=True
                ).exclude(pk=self.pk).exists():
            self.question.noAnswer = 4 - Answer.objects.filter(
                question=self.question).exclude(pk=self.pk).count()

        self.question.save()
        super().save(*args, **kwargs)

    def delete(self, *args, **kwargs):
        question = self.question
        super().delete(*args, **kwargs)

        question.noAnswer = Answer.objects.filter(question=question).count()
        question.save()

    def __str__(self):
        return self.answer


class Game(models.Model):

    # game_id = models.UUIDField(primary_key=True, default=uuid.uuid4,
    #                            help_text="Unique id for game")
    questionnaire = models.ForeignKey('Questionnaire',
                                      on_delete=models.CASCADE,
                                      )
    created_at = models.DateTimeField('created at', auto_now_add=True)

    class GameState(models.IntegerChoices):
        WAITING = WAITING
        QUESTION = QUESTION
        ANSWER = ANSWER
        LEADERBOARD = LEADERBOARD
    state = models.IntegerField(choices=GameState.choices)

    """
    The attribute game.publicId is a unique integer number
    (as the primary key) in the [1 - 10] range
    """

    num = random.randint(1, 1000000)
    publicId = models.IntegerField(
        default=num,
        help_text="Unique public id for game"
    )

    countdownTime = models.PositiveIntegerField('countdown time',
                                                )
    questionNo = models.IntegerField("Question number", default=1)

    def __str__(self):
        return str(self.publicId)


class Participant(models.Model):

    participant_id = models.UUIDField(primary_key=True, default=uuid.uuid4,
                                      help_text="Unique id for participant")
    game = models.ForeignKey('Game', on_delete=models.CASCADE)
    alias = models.CharField(max_length=100)
    points = models.PositiveBigIntegerField('Points')
    uuidP = models.UUIDField(primary_key=False, default=uuid.uuid4,
                             help_text="Unique public id for participant")

    def __str__(self):
        return self.alias


class Guess(models.Model):

    guess_id = models.UUIDField(primary_key=True, default=uuid.uuid4,
                                help_text="Unique id for guess")

    # Repasar el on_delete
    participant = models.ForeignKey('Participant', on_delete=models.CASCADE)

    game = models.ForeignKey('Game', on_delete=models.CASCADE)

    question = models.ForeignKey('Question', on_delete=models.CASCADE)

    answer = models.ForeignKey('Answer', on_delete=models.CASCADE)

    def __str__(self):
        return '{0}: {1}'.format(self.participant, self.answer)
