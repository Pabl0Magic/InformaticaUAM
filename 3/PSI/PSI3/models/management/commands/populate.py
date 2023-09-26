# Populate database
# This file has to be placed within the
# catalog/management/commands directory in your project.
# If that directory doesn't exist, create it.
# The name of the script is the name of the custom command,
# that is, populate.py.
#
# execute python manage.py  populate
#
# use module Faker generator to generate data
# (https://zetcode.com/python/faker/)
import os

from django.core.management.base import BaseCommand
from models.models import User as User
from models.models import Questionnaire as Questionnaire
from models.models import Question as Question
from models.models import Answer as Answer
from models.models import Game as Game
from models.models import Participant as Participant

from faker import Faker


# The name of this class is not optional must be Command
# otherwise manage.py will not process it properly
class Command(BaseCommand):
    # helps and arguments shown when command python manage.py help populate
    # is executed.
    help = """populate kahootclone database
           """
    # if you want to pass an argument to the function
    # uncomment this line
    # def add_arguments(self, parser):
    #    parser.add_argument('publicId',
    #        type=int,
    #        help='game the participants will join to')
    #    parser.add_argument('sleep',
    #        type=float,
    #        default=2.,
    #        help='wait this seconds until inserting next participant')

    def __init__(self, sneaky=True, *args, **kwargs):
        super().__init__(*args, **kwargs)
        # "if 'RENDER'" allows you to deal with different
        # behaviour in render.com and locally
        # That is, we check a variable ('RENDER')
        # that is only defined in render.com
        if 'RENDER' in os.environ:
            pass
        else:
            pass

        self.NUMBERUSERS = 4
        self.NUMBERQESTIONARIES = 30
        self.NUMBERQUESTIONS = 100
        self.NUMBERPARTICIPANTS = 20
        self.NUMBERANSWERPERQUESTION = 4
        self.NUMBERGAMES = 4

    # handle is another compulsory name, do not change it"
    # handle function will be executed by 'manage populate'
    def handle(self, *args, **kwargs):
        "this function will be executed by default"

        self.cleanDataBase()   # clean database
        # The faker.Faker() creates and initializes a faker generator,
        self.faker = Faker()
        self.user()  # create users
        self.questionnaire()  # create questionaries
        self.question()  # create questions
        self.answer()  # create answers
        self.game()  # create games

    def cleanDataBase(self):
        # delete all models stored (clean table)
        # in database
        # order in which data is deleted is important
        # your code goes here...
        print("clean Database")

        Game.objects.all().delete()
        Question.objects.all().delete()
        Questionnaire.objects.all().delete()
        User.objects.all().delete()
        Participant.objects.all().delete()

    def user(self):
        " Insert users"
        # create user
        print("Users")

        users = [
            {'username': 'marcos',
             'password': 'password',
             'first_name': 'marcos',
             'last_name': 'bernuy',
             'email': 'marcos@gmail.com'},

            {'username': 'pablo',
             'password': 'password',
             'first_name': 'pablo',
             'last_name': 'almarza',
             'email': 'pablo@gmail.com'},

        ]

        for us in users:
            user = User(
                username=us['username'],
                first_name=us['first_name'],
                last_name=us['last_name'],
                email=us['email']
            )
            user.set_password(us['password'])
            user.save()

        # Creating admin user
        User.objects.create_superuser(
            'alumnodb',
            'alumnodb@gmail.com',
            'alumnodb'
        )

    def questionnaire(self):
        "insert questionnaires"
        print("questionnaire")

        questionnaires = [
            {'title': 'Animals'},
            {'title': 'Plants'},
            {'title': 'Maths'},
            {'title': 'Spanish'},
        ]

        # assign users randomly to the questionnaires
        for q in questionnaires:

            us = User.objects.order_by("?").first()
            questionnaire = Questionnaire(
                title=q['title'],
                user=us
            )
            questionnaire.save()

    def question(self):
        " insert questions, assign randomly to questionnaires"
        print("Question")

        questions = [
            {'answerTime': '50',
             'question': 'What is 2+2?'},
            {'answerTime': '60',
             'question': 'What is a mammal'},
            {'answerTime': '70',
             'question': 'Best student?'},
            {'answerTime': '75',
             'question': 'What is "silla"?'},
        ]

        # assign questions randomly to the questionnaires
        for q in questions:

            quest = Questionnaire.objects.order_by("?").first()
            question = Question(
                answerTime=q['answerTime'],
                question=q['question'],
                questionnaire=quest
            )
            question.save()

    def answer(self):
        "insert answers, one of them must be the correct one"
        print("Answer")

        answers = [
            {'answer': '4',
             'correct': True},
            {'answer': '5',
             'correct': False},
            {'answer': '6',
             'correct': False},
            {'answer': '3',
             'correct': False},

            {'answer': 'dolphin',
             'correct': True},
            {'answer': 'crocodile',
             'correct': False},
            {'answer': 'seagull',
             'correct': False},
            {'answer': 'eagle',
             'correct': False},

            {'answer': 'Jonas',
             'correct': True},
            {'answer': 'John',
             'correct': False},
            {'answer': 'Alex',
             'correct': False},
            {'answer': 'Robert',
             'correct': False},

            {'answer': 'Chair',
             'correct': True},
            {'answer': 'Table',
             'correct': False},
            {'answer': 'TV',
             'correct': False},
            {'answer': 'Desk',
             'correct': False},
        ]

        # assign answer randomly to the questions
        # maximum number of answers per question is four
        num_answers = 0
        for q in answers:

            if num_answers % 4 == 0:
                quest = Question.objects.filter(
                    noAnswer__lt=4).order_by("?").first()
            answer = Answer(
                correct=q['correct'],
                answer=q['answer'],
                question=quest
            )
            answer.save()
            num_answers += 1

    def game(self):
        "insert some games"
        print("Game")

        games = [
            {'state': '1',
             'countdownTime': '10',
             'questionNo': '0'},
            {'state': '1',
             'countdownTime': '10',
             'questionNo': '0'},
        ]

        # choose at random the questionnaries
        for g in games:
            quest = Questionnaire.objects.order_by("?").first()
            game = Game(
                state=g['state'],
                countdownTime=g['countdownTime'],
                questionnaire=quest,
                questionNo=g['questionNo']
            )
            game.save()
