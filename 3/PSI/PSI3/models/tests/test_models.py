from django.test import TestCase
from datetime import datetime, timezone, timedelta
from time import sleep
import random
import string

###################
# You may modify the following variables
from models.models import User as User
from models.models import Questionnaire as Questionnaire
from models.models import Question as Question
from models.models import Answer as Answer
from models.models import Game as Game
from models.models import Participant as Participant
from models.models import Guess as Guess
# we assume the different states are defined in constants.py
from models.constants import WAITING as WAITING

# Please do not modify anything below this line
###################


class ModelTests(TestCase):
    """Test the models"""

    def create_check(self, dictionary, ObjectClass, check=True):
        """ create an object of the class 'ObjectClass'
        using the dictionary. Then,
        check that all key-values in the
        dictionary are attributes in the object.
        return created object of class Object
        """
        # create object
        item = ObjectClass.objects.create(**dictionary)
        if check:
            # check that str function exists
            self.assertTrue(ObjectClass.__str__ is not object.__str__)
            for key, value in dictionary.items():
                self.assertEqual(getattr(item, key), value)
            # execute __str__() so all the code in models.py is checked
            item.__str__()
        return item

    def test01_C(self):
        # get data base name
        # this test will fail in heroku
        print("test databasename")
        from django.db import connection
        db_name = connection.settings_dict['NAME']
        self.assertEqual(db_name, 'test_psi',
                         msg='Database name is not "psi", '
                             'Note that this test will fail in heroku\n')

    def createQuestionnaire(self, check):
        def randStr(chars=string.ascii_uppercase + string.digits, N=10):
            return ''.join(random.choice(chars) for _ in range(N))

        self.userDict = {"username": randStr(),
                         "password": 'a',
                         "first_name": 'a',
                         "last_name": 'a',
                         "email": 'a@aa.es'}
        user = User.objects.create_user(**self.userDict)
        questionnaireDict = {
            'title': 'questionnaire_title',
            'user': user
            }
        return self.create_check(questionnaireDict, Questionnaire, check)

    def test02_questionnaire(self):
        "Test questionnaire model"
        print("test questionnaire")
        questionnaire = self.createQuestionnaire(check=True)
        # test date
        now = datetime.now(timezone.utc)
        self.assertTrue((now - questionnaire.created_at) <
                        timedelta(seconds=1))
        self.assertTrue((now - questionnaire.updated_at) <
                        timedelta(seconds=1))
        sleep(2)
        questionnaire.title = "new title"
        questionnaire.save()
        # test update_date is updated
        self.assertTrue((questionnaire.updated_at - now) >
                        timedelta(seconds=1))

    def createQuestion(self, check):
        questionnaire = self.createQuestionnaire(False)
        questionDict = {
            'question': 'question_text',
            'questionnaire': questionnaire,
            'answerTime': 20,
            }
        return self.create_check(questionDict, Question, check)

    def test03_question(self):
        "Test question model"
        print("test question")

        question = self.createQuestion(check=True)
        now = datetime.now(timezone.utc)
        self.assertTrue((now - question.created_at) < timedelta(seconds=1))
        self.assertTrue((now - question.updated_at) < timedelta(seconds=1))

    def createAnswer(self, check):
        question = self.createQuestion(check=True)
        answerDict = {
            'answer': 'answer_text',
            'question': question,
            'correct': True,
            }
        return self.create_check(answerDict, Answer, check)

    def test04_answer(self):
        "Test answer model"
        print("test answer")
        self.createAnswer(check=True)

    def createGame(self, check):
        questionnaire = self.createQuestionnaire(check=False)
        gameDict = {
            'questionnaire': questionnaire,
            'state': WAITING,
            'countdownTime': 10,
            'questionNo': 3,
            }
        return self.create_check(gameDict, Game, check)

    def test05_game(self):
        print("test game")
        game = self.createGame(check=True)
        now = datetime.now(timezone.utc)
        self.assertTrue((now - game.created_at) < timedelta(seconds=1))
        self.assertTrue((game.publicId > 0) and (game.publicId < 1000001))

    def createParticipant(self, check):
        game = self.createGame(check=False)
        participantDict = {
            'game': game,
            'alias': 'mialias',
            'points': 0,
            }
        return self.create_check(participantDict, Participant, check)

    def test06_participant(self):
        print("test participant")
        self.createParticipant(check=True)

    def createGuess(self, check):
        game = self.createGame(check=False)
        participant = self.createParticipant(check=False)
        answer = self.createAnswer(check=False)
        question = self.createQuestion(check=False)
        guessDict = {
            'game': game,
            'participant': participant,
            'question': question,
            'answer': answer,
            }
        return self.create_check(guessDict, Guess, check)

    def test07_guess(self):
        print("test guess")
        guess = self.createGuess(check=True)
        self.assertEqual(guess.participant.points, 1)


# Added by students
"""class QuestionnaireModelTest(TestCase):

    # Testing Labels
    def test_questionnaire_id_label(self):
        questionnaire = Questionnaire.objects.get(id=1)
        field_label = questionnaire._meta.get_field('questionnaire_id').verbose_name
        self.assertEqual(field_label, 'questionnaire_id')

    def test_title_label(self):
        questionnaire = Questionnaire.objects.get(id=1)
        field_label = questionnaire._meta.get_field('title').verbose_name
        self.assertEqual(field_label, 'title')

    def test_created_at_label(self):
        questionnaire = Questionnaire.objects.get(id=1)
        field_label = questionnaire._meta.get_field('created_at').verbose_name
        self.assertEqual(field_label, 'created at')

    def test_updated_at_label(self):
        questionnaire = Questionnaire.objects.get(id=1)
        field_label = questionnaire._meta.get_field('updated_at').verbose_name
        self.assertEqual(field_label, 'updated at')

    def test_user_label(self):
        questionnaire = Questionnaire.objects.get(id=1)
        field_label = questionnaire._meta.get_field('user').verbose_name
        self.assertEqual(field_label, 'User')

    # Testing attributes
    def test_title_max_length(self):
        questionnaire = Questionnaire.objects.get(id=1)
        max_length = questionnaire._meta.get_field('title').max_length
        self.assertEqual(max_length, 100)

    def test_str_function(self):
        questionnaire = Questionnaire.objects.get(id=1)
        expected_object_name = questionnaire.title
        self.assertEqual(str(questionnaire), expected_object_name)


"""