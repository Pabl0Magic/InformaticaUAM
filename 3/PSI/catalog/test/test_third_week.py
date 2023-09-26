"""
Third Week Tests
Created by JAMI
EPS-UAM 2023
"""

from django.test import TestCase
from django.test import SimpleTestCase
from django.urls import reverse
import inspect
from django.contrib.auth.models import User, Permission
from catalog.models import Book, BookInstance

user = "user1"
password = "biblioteca"
email = "user@user.es"


class ThirdWeekTests(TestCase):
    @classmethod
    def setUpTestData(cls):
        # Set up non-modified objects used by all test methods
        try:
            from populate_catalog import populate
            populate()
            User.objects.create_user(user, email, password)
        except ImportError:
            print('The module populate_catalog does not exist')
        except NameError:
            print('The function populate() does not exist or is not correct')
        except Exception:
            print('Something went wrong :-(')
            raise


    def test_number_of_visits(self):
        response = self.client.get(reverse('index'))
        self.assertIsNotNone(self.client.session['num_visits'])
        self.assertIn(b'You have visited this page', response.content)


    def test_login(self):
        response = self.client.get(reverse('logout'), follow=True)
        self.assertEqual(response.status_code, 200)
        response = self.client.get(reverse('index'), follow=True)
        self.assertEqual(response.status_code, 200)  # redirection
        self.assertIn(b'Home', response.content)
        self.assertIn(b'All books', response.content)
        self.assertIn(b'All authors', response.content)
        self.assertIn(b'Login', response.content)
        self.assertNotIn(b'Logout', response.content)
        loginDict = {}
        loginDict["username"] = user
        loginDict["password"] = password
        response = self.client.post(reverse('login'), loginDict, follow=True)  # follow redirection
        self.assertEqual(response.status_code, 200)
        response = self.client.get(reverse('index'), follow=True)
        self.assertIn(b'Logout', response.content)
        self.assertIn(b'My Borrowed', response.content)
        self.assertNotIn(b'Login', response.content)


    def test_borrowed(self):
        u  = User.objects.get(username=user)
        bi = BookInstance.objects.filter(book__title='The Shining').first()
        bi.borrower = u
        bi.save()
        self.test_login()
        response = self.client.get(reverse('my-borrowed'), follow=True)
        self.assertIn(b'The Shining', response.content)


    def test_challenge_part8(self):
        u  = User.objects.get(username=user)
        u.is_staff = True
        permission = Permission.objects.get(codename='can_mark_returned')
        u.user_permissions.add(permission)
        u.save()
        bi = BookInstance.objects.filter(book__title='The Shining').first()
        bi.borrower = u
        bi.save()
        loginDict = {}
        loginDict["username"] = user
        loginDict["password"] = password
        response = self.client.post(reverse('login'), loginDict, follow=True)
        self.assertIn(b'Staff', response.content)
        self.assertIn(b'All borrowed', response.content)
        response = self.client.get(reverse('all-borrowed'), follow=True)
        self.assertIn(b'user1', response.content)


    def test_aurhor_form(self):
        u  = User.objects.get(username=user)
        u.is_staff = True
        permission = Permission.objects.get(codename='can_mark_returned')
        u.user_permissions.add(permission)
        u.save()
        loginDict = {}
        loginDict["username"] = user
        loginDict["password"] = password
        response = self.client.post(reverse('login'), loginDict, follow=True)
        authorDict = {}
        authorDict["first_name"] = 'Julio'
        authorDict["last_name"] = 'Verne'
        authorDict["birth_date"] = '1928-02-08'
        authorDict["die_date"] = '1905-03-24'
        response = self.client.post(reverse('author-create'), authorDict, follow=True)
        self.assertEqual(response.status_code, 200)
        self.assertIn(b'Author: Verne, Julio', response.content)


    def test_challenge_part9_one(self):
        u  = User.objects.get(username=user)
        loginDict = {}
        loginDict["username"] = user
        loginDict["password"] = password
        response = self.client.post(reverse('login'), loginDict, follow=True)
        response = self.client.get(reverse('book-create'), follow=True)
        self.assertEqual(response.status_code, 403)
        bi = Book.objects.filter(title__contains='The Shining').first()
        response = self.client.get(reverse('book-update', kwargs={'pk': bi.pk}))
        self.assertEqual(response.status_code, 403)
        response = self.client.get(reverse('book-delete', kwargs={'pk': bi.pk}))
        self.assertEqual(response.status_code, 403)


    def test_challenge_part9_two(self):
        u  = User.objects.get(username=user)
        u.is_staff = True
        permission = Permission.objects.get(codename='can_mark_returned')
        u.user_permissions.add(permission)
        u.save()
        loginDict = {}
        loginDict["username"] = user
        loginDict["password"] = password
        response = self.client.post(reverse('login'), loginDict, follow=True)
        response = self.client.get(reverse('book-create'), follow=True)
        self.assertEqual(response.status_code, 200)
        bi = Book.objects.filter(title__contains='The Shining').first()
        response = self.client.get(reverse('book-update', kwargs={'pk': bi.pk}))
        self.assertEqual(response.status_code, 200)
        response = self.client.get(reverse('book-delete', kwargs={'pk': bi.pk}))
        self.assertEqual(response.status_code, 200)


    def test_tests_models_exist(self):
        from catalog.tests.test_models import AuthorModelTest as c1
        self.assertTrue(len(str(inspect.getsourcelines(c1)))>=1000)
        self.assertIn('test_first_name_label', dir(c1))
        self.assertIn('test_date_of_death_label', dir(c1))
        self.assertIn('test_first_name_max_length', dir(c1))
        self.assertIn('test_object_name_is_last_name_comma_first_name', dir(c1))
        self.assertIn('test_get_absolute_url', dir(c1))


    def test_tests_forms_exist(self):
        from catalog.tests.test_forms import RenewBookFormTest as c2
        self.assertTrue(len(str(inspect.getsourcelines(c2)))>=1000)
        self.assertIn('test_renew_form_date_field_label', dir(c2))
        self.assertIn('test_renew_form_date_field_help_text', dir(c2))
        self.assertIn('test_renew_form_date_in_past', dir(c2))
        self.assertIn('test_renew_form_date_too_far_in_future', dir(c2))
        self.assertIn('test_renew_form_date_today', dir(c2))
        self.assertIn('test_renew_form_date_max', dir(c2))


    def test_tests_views_exist(self):
        from catalog.tests.test_views import AuthorListViewTest as c3
        self.assertTrue(len(str(inspect.getsourcelines(c3)))>=1000)
        self.assertIn('test_view_url_exists_at_desired_location', dir(c3))
        self.assertIn('test_view_url_accessible_by_name', dir(c3))
        self.assertIn('test_view_uses_correct_template', dir(c3))
        self.assertIn('test_pagination_is_ten', dir(c3))
        self.assertIn('test_lists_all_authors', dir(c3))
        from catalog.tests.test_views import LoanedBookInstancesByUserListViewTest as c4
        self.assertTrue(len(str(inspect.getsourcelines(c4)))>=1000)
        self.assertIn('test_redirect_if_not_logged_in', dir(c4))
        self.assertIn('test_logged_in_uses_correct_template', dir(c4))
        self.assertIn('test_only_borrowed_books_in_list', dir(c4))
        self.assertIn('test_pages_ordered_by_due_date', dir(c4))
        from catalog.tests.test_views import RenewBookInstancesViewTest as c5
        self.assertTrue(len(str(inspect.getsourcelines(c5)))>=1000)
        self.assertIn('test_redirect_if_not_logged_in', dir(c5))
        self.assertIn('test_forbidden_if_logged_in_but_not_correct_permission', dir(c5))
        self.assertIn('test_logged_in_with_permission_borrowed_book', dir(c5))
        self.assertIn('test_logged_in_with_permission_another_users_borrowed_book', dir(c5))
        self.assertIn('test_HTTP404_for_invalid_book_if_logged_in', dir(c5))
        self.assertIn('test_uses_correct_template', dir(c5))
        self.assertIn('test_form_renewal_date_initially_has_date_three_weeks_in_future', dir(c5))
        self.assertIn('test_redirects_to_all_borrowed_book_list_on_success', dir(c5))
        self.assertIn('test_form_invalid_renewal_date_past', dir(c5))
        self.assertIn('test_form_invalid_renewal_date_future', dir(c5))


    def test_challenge_one(self):
        from catalog.tests.test_views import AuthorCreateViewTest as c6
        self.assertTrue(len(str(inspect.getsourcelines(c6)))>=1000)
        self.assertIn('test_redirect_if_not_logged_in', dir(c6))
        self.assertIn('test_forbidden_if_logged_in_but_not_correct_permission', dir(c6))
        self.assertIn('test_logged_in_with_permission', dir(c6))
        self.assertIn('test_uses_correct_template', dir(c6))
        self.assertIn('test_form_date_of_death_initially_set_to_expected_date', dir(c6))
        self.assertIn('test_redirects_to_detail_view_on_success', dir(c6))
