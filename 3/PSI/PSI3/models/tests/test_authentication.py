import re
from decimal import Decimal


from django.test import Client, TestCase  # , TransactionTestCase
from django.urls import reverse

try:
    from models.models import User
except ImportError:
    print('No custom defined User method defined in models.py')
    exit(0)

USER_SESSION_ID = "_auth_user_id"

###################
# You may modify the following variables

LOGIN_SERVICE = "login"
LOGOUT_SERVICE = "logout"
SIGNUP_SERVICE = "signup"

PAGE_AFTER_LOGIN = "home_signed"
PAGE_AFTER_LOGOUT = "home_unsigned"


SERVICE_DEF = {
     LOGIN_SERVICE: {
         "title": 'Log In',
         "pattern": r"Log In"
     },
}
# PLease do not modify anything below this line
###################

NUMBERUSERS = 5


class ServiceBaseTest(TestCase):
    """ Test create a temporary database and delete it when the test ends.
    This behavoiur may be avoided by inheriting
    from django.test.TransactionTestCase instead of TestCase.
    Then the data will be visible in the database."""
    def setUp(self):
        User.objects.all().delete()
        self.usersList = []
        self.users = []
        for i in range(0, NUMBERUSERS):
            user = {"username": "user_%d" % i,
                    "password": "password_%d" % i,
                    "first_name": "name_%d" % i,
                    "last_name": "last_%d" % i,
                    "email": "email_%d@gmail.com" % i}
            self.usersList.append(user)
            user = User.objects.create_user(**user)

            # store user id in list
            self.usersList[i]["id"] = user.id
            self.users.append(user)

        # create three clients so we can
        # test concurrency
        self.client1 = self.client
        self.client2 = Client()
        self.client3 = Client()

    # uncomment if you need to see the database
    # for debuging purposes
    # def tearDown(self):
    #    input(
    #        'Execution is paused and you can now inspect the database.\n'
    #        'Press return/enter key to continue:')

    @classmethod
    def decode(cls, txt):
        return txt.decode("utf-8")

    def validate_response(self, service, response, fail=False):
        definition = SERVICE_DEF[service]
        self.assertRegex(self.decode(response.content), definition["title"])
        if fail:
            # print(definition["patternfail"], self.decode(response.content))
            m = re.search(definition["patternfail"],
                          self.decode(response.content))
        else:
            # print(definition["pattern"], self.decode(response.content))
            m = re.search(definition["pattern"], self.decode(response.content))
        self.assertTrue(m)
        return m


class LogInOutServiceTests(ServiceBaseTest):

    def test01_log_page(self):
        """check log page but do not log in
         check that  no user is logged in
         actually, ask the value of the session variable
         USER_SESSION_ID. This variable should NOT
         exist is nobody is logged in
        """
        self.assertFalse(self.client1.session.get(USER_SESSION_ID, False))

        # call "login" service and check that "login" is in the title
        # LOGIN_SERVICE should match the label for your login url
        response = self.client1.get(reverse(LOGIN_SERVICE), follow=True)
        # The HTTP 200 code indicates that the request has succeeded
        self.assertEqual(response.status_code, 200)

        # check that the strings  SERVICE_DEF[LOGIN_SERVICE]
        # "title" and "pattern" are shown in login page
        self.validate_response(LOGIN_SERVICE, response)

        # so far we have just connected to the login page
        # but we have not log in so no user should be active
        self.assertFalse(self.client1.session.get(USER_SESSION_ID, False))

    def test02_log_in(self):
        "login and validate landing page"
        # no user logged in therefore, there should not be a
        # session variable named USER_SESSION_ID
        self.assertFalse(
            self.client1.session.get(USER_SESSION_ID, False))

        # log-in
        response = self.client1.post(reverse(LOGIN_SERVICE),
                                     self.usersList[0], follow=True)
        # after login session user should exist
        self.assertTrue(response.context['user'].is_active)

    def test03_log_in_several_users(self):
        """log in with 2 different users from two different
        clients/browsers. Then, request the home page and check
         the user name"""
        sessions = [
            {"client": self.client1, "user": self.usersList[0]},
            {"client": self.client2, "user": self.usersList[1]}
        ]
        # log in from two clients
        for session in sessions:
            session["client"].post(
                reverse(LOGIN_SERVICE), session["user"], follow=True)
        # connect to home (PAGE_AFTER_LOGIN) from two clients
        for session in sessions:
            response = session["client"].get(reverse(PAGE_AFTER_LOGIN),
                                             follow=True)
            self.assertTrue(response.context['user'].is_active)

    def test04_logout(self):
        "log in, then log out and test that user is not logged in"
        # check no user is logged in
        self.assertFalse(
            self.client1.session.get(USER_SESSION_ID, False))
        # log in
        self.client1.post(
            reverse(LOGIN_SERVICE), self.usersList[0], follow=True)

        # test user logged by checking user id
        self.assertEqual(Decimal(self.client1.session.get(USER_SESSION_ID)),
                         self.usersList[0]['id'])

        # logged out
        self.client1.get(reverse(LOGOUT_SERVICE), follow=True)

        # test user is logged out
        self.assertFalse(self.client1.session.get(USER_SESSION_ID, False))

    def test05_signup(self):
        # check  user does not exist
        i = NUMBERUSERS
        user = {"username": "user_%d" % i,
                "first_name": "name_%d" % i,
                "last_name": "last_%d" % i,
                "email": "email_%d@gmail.com" % i,
                "password": 'trekingff1',
                "password1": 'trekingff1',
                "password2": 'trekingff1'}
        self.assertFalse(
            User.objects.filter(username=user["username"]).exists())
        # send signup request
        self.client1.post(reverse(SIGNUP_SERVICE), user, follow=True)
        u = User.objects.filter(username="user_%d" % i)[0]
        # login
        # self.client1.post(reverse(LOGIN_SERVICE), user, follow=True)
        # print(self.decode(response.content))
        # check the user has been logged in
        self.assertTrue(self.client1.session.get(USER_SESSION_ID, False))

        # logout and login
        self.client1.get(reverse(LOGOUT_SERVICE), follow=True)
        # check no user is logged in
        self.assertFalse(
            self.client1.session.get(USER_SESSION_ID, False))
        # log in
        self.client1.post(
            reverse(LOGIN_SERVICE), user, follow=True)
        # test user logged by checking user id
        self.assertEqual(Decimal(self.client1.session.get(USER_SESSION_ID)),
                         u.id)