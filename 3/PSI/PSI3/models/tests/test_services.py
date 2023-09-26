# created by R. Marabini on mar ago 17 14:11:42 CEST 2021

from django.test import Client, TestCase
from django.urls import reverse

##Borrar
import logging
logger = logging.getLogger(__name__)
##Borrar

###################
# You may modify the following variables
from models.models import User as User
from models.models import Questionnaire as Questionnaire
from models.models import Question as Question
from models.models import Answer as Answer
from models.models import Game as Game
# from models.models import Participant as Participant
# from models.models import Guess as Guess

# XXX_SERVICE is the alias of the service we want to test
# XXX_KEY is the key, in the context diccionary, with the information
# that we want to pass to the template
# For example response.context['latest_questionnaire_list'] should contain
# the last five questionnaires created by the logged user

HOME_SERVICE = "home_signed"
HOME_QUESTIONNAIRE_LIST_KEY = 'questionnaire_list'

QUESTIONNAIRE_DETAIL_SERVICE = "questionnaire-detail"
QUESTIONNAIRE_DETAIL_KEY = "questionnaire"

QUESTIONNAIRE_REMOVE_SERVICE = "questionnaire-confirm-remove"

QUESTIONNAIRE_LIST_SERVICE = "questionnaire-list"
QUESTIONNAIRE_LIST_KEY = "questionnaire_list"

QUESTIONNAIRE_UPDATE_SERVICE = "questionnaire-update"
QUESTIONNAIRE_UPDATE_KEY = "questionnaire"

QUESTIONNAIRE_CREATE_SERVICE = "questionnaire-create"
QUESTIONNAIRE_CREATE_KEY = "questionnaire"

QUESTION_DETAIL_SERVICE = "question-detail"
QUESTION_DETAIL_KEY = "question"

QUESTION_REMOVE_SERVICE = "question-remove"

QUESTION_UPDATE_SERVICE = "question-update"
QUESTION_UPDATE_KEY = "question"

QUESTION_CREATE_SERVICE = "question-create"
QUESTION_CREATE_KEY = "question"

ANSWER_UPDATE_SERVICE = "answer-update"
ANSWER_UPDATE_KEY = "answer"

ANSWER_CREATE_SERVICE = "answer-create"
ANSWER_CREATE_KEY = "answer"

ANSWER_REMOVE_SERVICE = "answer-remove"

GAME_CREATE_SERVICE = "game-create"

LOGIN_SERVICE = "login"
LOGOUT_SERVICE = "logout"

# PLease, do not modify anything below this line
###################


class ServiceBaseTest(TestCase):
    def setUp(self):
        self.client1 = self.client
        self.client2 = Client()
        self.client3 = Client()
        # user
        self.userDict = {"username": 'a',
                         "password": 'a',
                         "first_name": 'a',
                         "last_name": 'a',
                         "email": 'a@aa.es'
                         }
        user, created = User.objects.get_or_create(**self.userDict)
        if created:
            user.set_password(self.userDict['password'])
            user.save()
        self.user = user

        # questionnaire
        self.questionnaireDict = {"title": 'newTitle',
                                  "user": self.user
                                  }
        self.questionnaire = Questionnaire.objects.get_or_create(
            **self.questionnaireDict)[0]

        # question
        self.questionDict = {"question": 'this is a question',
                             "questionnaire": self.questionnaire,
                             }
        self.question = Question.objects.get_or_create(**self.questionDict)[0]

        # question2
        self.questionDict2 = {"question": 'this is a question2',
                              "questionnaire": self.questionnaire,
                              }
        self.question2 = Question.objects.get_or_create(
            **self.questionDict2)[0]

        # answer
        self.answerDict = {"answer": 'this is an answer',
                           "question": self.question,
                           "correct": True
                           }
        self.answer = Answer.objects.get_or_create(**self.answerDict)[0]

        # answer2
        self.answerDict2 = {"answer": 'this is an answer2',
                            "question": self.question,
                            "correct": False
                            }
        self.answer2 = Answer.objects.get_or_create(**self.answerDict2)[0]

        # answer3
        self.answerDict3 = {"answer": 'this is an answer3',
                            "question": self.question2,
                            "correct": True
                            }
        self.answer3 = Answer.objects.get_or_create(**self.answerDict3)[0]

    def tearDown(self):
        # delete all models stored (clean table)
        # in database
        # ordering is important
        classList = [Answer, Game, Question, Questionnaire, User]
        for c in classList:
            c.objects.all().delete()

    @classmethod
    def decode(cls, txt):
        return txt.decode("utf-8")


class ServiceTests(ServiceBaseTest):

    def checkNoLogin(self, SERVICE, KEY, args=None, redirectLoginPage=True):
        """ check key is not in response if user is not logged"""
        # no login, therefore key KEY should be empty
        # first logout just in case
        self.client1.get(reverse(LOGOUT_SERVICE), follow=True)
        if args is None:
            response = self.client1.get(
                reverse(SERVICE), follow=True)
        else:
            response = self.client1.get(
                reverse(SERVICE, args=args), follow=True)
        # check no active user
        self.assertFalse(response.context['user'].is_active)
        # check no latest_questionnaire_list
        try:
            self.assertFalse(KEY in response.context)
        except Exception as e:
            pass
        # return should be login page
        if redirectLoginPage:
            self.assertIn('username', self.decode(response.content))

        return response

    def checkLogin(self, SERVICE, KEY, args=None):
        """ log in and check key is in response when user is logged"""
        # log-in
        response = self.client1.post(reverse(LOGIN_SERVICE),
                                     self.userDict, follow=True)
        # after login session user should exist
        self.assertTrue(response.context['user'].is_active)
        if args is None:
            response = self.client1.get(
                reverse(SERVICE), follow=True)
        else:
            response = self.client1.get(
                reverse(SERVICE, args=args), follow=True)

        # latest_questionnaire_list should exist
        if KEY != "DO_NOT_CHECK_KEY":
            self.assertTrue(KEY in response.context)
        return response

    def checkLoginSecondPart(self, SERVICE, args, kwargs=None):
        """ for those cases in which there is a confirmation page
        or a form and a post should follow a get request"""
        if kwargs is None:
            response = self.client1.post(
                reverse(SERVICE, args=args), follow=True)
        else:
            response = self.client1.post(
                reverse(SERVICE, args=args), kwargs, follow=True)

        return response

# ==== HOME ====
    def test01_home(self):
        " check content in home_page view"
        # no login, therefore key should be empty
        self.checkNoLogin(HOME_SERVICE,
                          HOME_QUESTIONNAIRE_LIST_KEY,
                          redirectLoginPage=False)
        # login in
        response = self.checkLogin(HOME_SERVICE, HOME_QUESTIONNAIRE_LIST_KEY)

        # get five latest questionnaries and check that there
        # are in the response page
        questionnaires = Questionnaire.objects.filter(
            user=self.user).order_by('-updated_at')[:5]
        for q1, q2 in zip(questionnaires,
                          response.context[HOME_QUESTIONNAIRE_LIST_KEY]):
            self.assertEqual(q1, q2)

# ==== QUESTIONNAIRE ====
    def test02_questionnaireDetail(self):
        " check view questionary detail"
        id = self.questionnaire.id
        args = [str(id)]

        # no login, therefore key should be empty
        self.checkNoLogin(
            QUESTIONNAIRE_DETAIL_SERVICE,
            QUESTIONNAIRE_DETAIL_KEY,
            args=args)

        # login in
        response = self.checkLogin(
            QUESTIONNAIRE_DETAIL_SERVICE,
            QUESTIONNAIRE_DETAIL_KEY,
            args=args)

        # check the questioannaire detail are in the respònse
        # note that if I just use
        # self.assertEqual(self.questionnaire,
        #     response.context[QUESTIONNAIRE_DETAIL_KEY])
        # only the id are checked
        self.assertEqual(
            self.questionnaire.title,
            response.context[QUESTIONNAIRE_DETAIL_KEY].title)
        # if I change the title the object should be different
        self.questionnaire.title = "another title"
        self.assertNotEqual(
            self.questionnaire.title,
            response.context[QUESTIONNAIRE_DETAIL_KEY].title)

    def test03_questionnaireRemove(self):
        " check view questionnaire remove"
        id = self.questionnaire.id
        args = [str(id)]

        # no login, therefore key should be empty
        self.checkNoLogin(
            QUESTIONNAIRE_REMOVE_SERVICE, "DO_NOT_CHECK_KEY", args=args)
        self.assertTrue(Questionnaire.objects.filter(id=id).exists())

        # login in, two calls are needed because there is an intermediate
        # page asking to confirm the deletion. The first is a get
        # while the second is a post
        self.checkLogin(
            QUESTIONNAIRE_REMOVE_SERVICE, "DO_NOT_CHECK_KEY", args=args)
        self.checkLoginSecondPart(QUESTIONNAIRE_REMOVE_SERVICE, args=args)
        self.assertFalse(Questionnaire.objects.filter(id=id).exists())

    def test04_questionnaireList(self):
        "check questionaireList"

        # no login, therefore key should be empty
        self.checkNoLogin(QUESTIONNAIRE_LIST_SERVICE, QUESTIONNAIRE_LIST_KEY)

        # login in
        response = self.checkLogin(
            QUESTIONNAIRE_LIST_SERVICE, QUESTIONNAIRE_LIST_KEY)

        questionnaires = Questionnaire.objects.filter(user=self.user)
        # compare all questionnaires, both lists should be shorted by the same
        # field
        for q1, q2 in zip(questionnaires,
                          response.context[QUESTIONNAIRE_LIST_KEY]):
                self.assertEqual(q1, q2)

    def test05_questionnaireUpdate(self):
        "check questionaireUpdate"
        id = self.questionnaire.id
        args = [str(id)]

        # no login, therefore key should be empty
        self.checkNoLogin(
            QUESTIONNAIRE_UPDATE_SERVICE, QUESTIONNAIRE_UPDATE_KEY, args=args)

        # login in, two calls are needed because there is an intermediate
        # form  asking for the field 'title'
        self.checkLogin(
            QUESTIONNAIRE_UPDATE_SERVICE, QUESTIONNAIRE_UPDATE_KEY, args=args)
        # print("RESPONSE", self.decode(response.content))
        kwargs = {'title': 'newTitle'}
        self.checkLoginSecondPart(
            QUESTIONNAIRE_UPDATE_SERVICE, args=args, kwargs=kwargs)
        # print("RESPONSE", self.decode(response.content))
        # questionarie need to be reload, that is,
        # self.questionnarie has old values
        questionnaire = Questionnaire.objects.get(id=id)
        self.assertEqual(questionnaire.title, kwargs["title"])

    def test06_questionnaireCreate(self):
        "check questionnaireCreate"
        kwargs = {'title': 'newTitle'}

        # no login, therefore key should be empty
        self.checkNoLogin(
           QUESTIONNAIRE_CREATE_SERVICE, 'DO_NOT_CHECK_KEY', args=None)

        # login in, two calls are needed because there is an intermediate
        # form  asking for the field 'title'
        self.checkLogin(
            QUESTIONNAIRE_CREATE_SERVICE, 'DO_NOT_CHECK_KEY', args=None)
        # print("RESPONSE", self.decode(response.content))
        x = self.checkLoginSecondPart(
            QUESTIONNAIRE_CREATE_SERVICE, args=None, kwargs=kwargs)
        # print("RESPONSE", self.decode(response.content))
        # questionarie need to be reload, that is,
        # self.questionnarie has old values
        questionnaire = Questionnaire.objects.first()
        self.assertEqual(questionnaire.title, kwargs["title"])

# ==== QUESTION =====
    def test12_questionDetail(self):
        " check view question detail"
        id = self.question.id
        args = [str(id)]

        # no login, therefore key should be empty
        self.checkNoLogin(
            QUESTION_DETAIL_SERVICE, QUESTION_DETAIL_KEY, args=args)

        # login in
        response = self.checkLogin(
            QUESTION_DETAIL_SERVICE, QUESTION_DETAIL_KEY, args=args)

        # check the questioan detail are in the respònse
        self.assertEqual(
           self.question.question,
           response.context[QUESTION_DETAIL_KEY].question)
        # if I change the title the object should be different
        self.question.question = "another question"
        self.assertNotEqual(
            self.question.question,
            response.context[QUESTION_DETAIL_KEY].question)

    def test13_questionRemove(self):
        " check view question remove"
        id = self.question.id
        args = [str(id)]

        # no login, therefore key should be empty
        self.checkNoLogin(
            QUESTION_REMOVE_SERVICE, "DO_NOT_CHECK_KEY", args=args)
        self.assertTrue(Question.objects.filter(id=id).exists())

        # login in, two calls are needed because there is an intermediate
        # page asking to confirm the deletion. The first is a get
        # while the second is a post
        self.checkLogin(QUESTION_REMOVE_SERVICE, "DO_NOT_CHECK_KEY", args=args)
        self.checkLoginSecondPart(QUESTION_REMOVE_SERVICE, args=args)
        self.assertFalse(Question.objects.filter(id=id).exists())

    def test15_questionUpdate(self):
        "check questionUpdate"
        id = self.question.id
        args = [str(id)]

        # no login, therefore key should be empty
        self.checkNoLogin(
            QUESTION_UPDATE_SERVICE, QUESTION_UPDATE_KEY, args=args)

        # login in, two calls are needed because there is an intermediate
        # form  asking for the field 'title'
        self.checkLogin(
            QUESTION_UPDATE_SERVICE, QUESTION_UPDATE_KEY, args=args)
        # print("RESPONSE", self.decode(response.content))
        kwargs = {'question': 'another question'}
        self.checkLoginSecondPart(
            QUESTION_UPDATE_SERVICE, args=args, kwargs=kwargs)
        # print("RESPONSE", self.decode(response.content))
        # questionarie need to be reload,
        # that is, self.questionnarie has old values
        question = Question.objects.get(id=id)
        self.assertEqual(question.question, kwargs["question"])

    def test16_questionCreate(self):
        "check questionCreate"
        # delete all questions so it is easier
        # to check that a new question has been created
        Question.objects.all().delete()
        id = self.questionnaire.id
        args = [str(id)]
        kwargs = {'question': 'new question'}

        # no login, therefore key should be empty
        # response =
        self.checkNoLogin(QUESTION_CREATE_SERVICE,
                          'DO_NOT_CHECK_KEY', args=args)

        # login in, two calls are needed because there is an intermediate
        # form  asking for the field 'title'
        # response =
        self.checkLogin(QUESTION_CREATE_SERVICE, 'DO_NOT_CHECK_KEY', args=args)
        # print("RESPONSE", self.decode(response.content))
        # response =
        self.checkLoginSecondPart(QUESTION_CREATE_SERVICE,
                                  args=args, kwargs=kwargs)
        # print("RESPONSE", self.decode(response.content))
        # questionarie need to be reload, that is,
        # self.questionnarie has old values
        question = Question.objects.first()
        self.assertEqual(question.question, kwargs["question"])
        self.assertEqual(question.questionnaire.id, int(id))

# ===== ANSWER =====
    def test26_answerCreate(self):
        "check answerCreate"
        # delete all questions so it is easier to check
        # if a new question has been created
        Answer.objects.all().delete()
        id = self.question.id
        args = [str(id)]
        kwargs = {'answer': 'new answer', "correct": True}

        # no login, therefore key should be empty
        # response =
        self.checkNoLogin(ANSWER_CREATE_SERVICE, 'DO_NOT_CHECK_KEY', args=args)

        # login in, two calls are needed because there is an intermediate
        # form  asking for the field 'title'
        # response =
        self.checkLogin(ANSWER_CREATE_SERVICE, 'DO_NOT_CHECK_KEY', args=args)
        # print("RESPONSE", self.decode(response.content))
        # response =
        self.checkLoginSecondPart(ANSWER_CREATE_SERVICE,
                                  args=args, kwargs=kwargs)
        # print("RESPONSE", self.decode(response.content))
        # questionarie need to be reload, that is,
        # self.questionnarie has old values
        answer = Answer.objects.first()
        self.assertEqual(answer.answer, kwargs["answer"])
        self.assertEqual(answer.question.id, int(id))
        self.assertEqual(answer.correct, kwargs["correct"])

    def test23_answerRemove(self):
        " check view answer remove"
        id = self.answer.id
        args = [str(id)]

        # no login, therefore key should be empty
        self.checkNoLogin(ANSWER_REMOVE_SERVICE, "DO_NOT_CHECK_KEY", args=args)
        self.assertTrue(Answer.objects.filter(id=id).exists())

        # login in, two calls are needed because there is an intermediate
        # page asking to confirm the deletion. The first is a get
        # while the second is a post
        # response =
        self.checkLogin(ANSWER_REMOVE_SERVICE, "DO_NOT_CHECK_KEY", args=args)
        # print("RESPONSE", self.decode(response.content))
        self.checkLoginSecondPart(ANSWER_REMOVE_SERVICE, args=args)
        self.assertFalse(Answer.objects.filter(id=id).exists())

    def test25_answerUpdate(self):
        "check answerUpdate"
        id = self.answer.id
        args = [str(id)]

        # no login, therefore key should be empty
        self.checkNoLogin(ANSWER_UPDATE_SERVICE, ANSWER_UPDATE_KEY, args=args)

        # login in, two calls are needed because there is an intermediate
        # form  asking for the field 'title'
        # response =
        self.checkLogin(ANSWER_UPDATE_SERVICE, ANSWER_UPDATE_KEY, args=args)
        # print("RESPONSE", self.decode(response.content))
        kwargs = {'answer': 'another answer', 'correct': False}
        # response =
        self.checkLoginSecondPart(ANSWER_UPDATE_SERVICE,
                                  args=args, kwargs=kwargs)
        # print("RESPONSE", self.decode(response.content))
        # questionarie need to be reload, that is,
        # self.questionnarie has old values
        answer = Answer.objects.get(id=id)
        self.assertEqual(answer.answer, kwargs["answer"])
        self.assertEqual(answer.correct, kwargs["correct"])

# ==== GAME ====
    def test36_gameCreate(self):
        "check gameCreate"
        from models.constants import WAITING
        id = self.questionnaire.id
        args = [str(id)]
        kwargs = {'state': WAITING}

        # no login, therefore key should be empty
        # response =
        self.checkNoLogin(GAME_CREATE_SERVICE, 'DO_NOT_CHECK_KEY', args=args)

        # form  asking for the field 'title'
        # response =
        response = self.checkLogin(
            GAME_CREATE_SERVICE, 'DO_NOT_CHECK_KEY', args=args)
        game = Game.objects.first()
        self.assertEqual(game.questionnaire.id, int(id))
        self.assertEqual(game.state, kwargs["state"])
        self.assertEqual(
            self.decode(
                response.content).find("does not belong to logged user"), -1)

        # create new user, it will be used for login
        # and will not be the owner of the questionnaire
        self.userDict = {"username": 'b',
                         "password": 'b',
                         "first_name": 'b',
                         "last_name": 'b',
                         "email": 'b@bb.es'}
        user, created = User.objects.get_or_create(**self.userDict)
        if created:
            user.set_password(self.userDict['password'])
            user.save()
        self.user = user
        response = self.checkLogin(
            GAME_CREATE_SERVICE, 'DO_NOT_CHECK_KEY', args=args)
        self.assertNotEqual(
             self.decode(
                 response.content).find("does not belong to logged user"), -1)