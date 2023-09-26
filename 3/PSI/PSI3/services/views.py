from django.shortcuts import get_object_or_404
from django.contrib.auth.mixins import LoginRequiredMixin
from django.views.generic.edit import CreateView, UpdateView, DeleteView
from django.views import generic
from django.template.response import TemplateResponse
from django.urls import reverse_lazy
from django.http import JsonResponse
from models.models import Questionnaire, Question, Answer, Game, Participant
import random


class Home(LoginRequiredMixin, generic.ListView):

    model = Questionnaire
    template_name = 'home_signed.html'

    def get_queryset(self):
        return (
            Questionnaire.objects
            .filter(user=self.request.user)
            .order_by('updated_at')[:5]
        )


class QuestionnaireDetail(LoginRequiredMixin, generic.DetailView):

    model = Questionnaire
    template_name = 'models/questionnaire_detail.html'

    # If you are in a questionnaire-detail of marcos and change to
    # pablo, it gives a 404, which is good cause it does not show
    # the details of questionnaires of marcos, but it would probs be
    # good if it goes to services instead. (Idk how)
    def get_queryset(self):
        return (
            Questionnaire.objects
            .filter(user=self.request.user)
        )


class QuestionnaireList(LoginRequiredMixin, generic.ListView):

    model = Questionnaire
    template_name = 'models/questionnaire_list.html'

    def get_queryset(self):
        return (
            Questionnaire.objects
            .filter(user=self.request.user)
            .order_by('updated_at')
        )


class QuestionnaireRemove(LoginRequiredMixin, DeleteView):

    model = Questionnaire
    template_name = 'models/questionnaire_confirm_remove.html'
    success_url = reverse_lazy('questionnaire-list')


class QuestionnaireUpdate(LoginRequiredMixin, generic.UpdateView):
    model = Questionnaire
    fields = ['title']

    def form_valid(self, form):
        form.instance.user = self.request.user
        return super().form_valid(form)


class QuestionnaireCreate(LoginRequiredMixin, CreateView):

    model = Questionnaire
    fields = ['title']

    def form_valid(self, form):
        if form.is_valid():
            form.instance.user = self.request.user
            return super().form_valid(form)


class QuestionDetail(LoginRequiredMixin, generic.DetailView):
    model = Question
    template_name = 'models/question_detail.html'


class QuestionRemove(LoginRequiredMixin, DeleteView):
    model = Question
    template_name = 'models/question_remove.html'
    success_url = reverse_lazy('questionnaire-list')


class QuestionUpdate(LoginRequiredMixin, UpdateView):
    model = Question
    fields = ['question', 'answerTime']


class QuestionCreate(LoginRequiredMixin, CreateView):
    model = Question
    fields = ['question', 'answerTime']

    def form_valid(self, form):
        if form.is_valid():
            form.instance.questionnaireid = self.kwargs['questionnaireid']
            questionnaire = get_object_or_404(
                Questionnaire,
                pk=self.kwargs['questionnaireid']
            )
            form.instance.questionnaire = questionnaire

        return super().form_valid(form)

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        questionnaire = get_object_or_404(
            Questionnaire,
            pk=self.kwargs['questionnaireid']
        )
        context['questionnaire'] = questionnaire
        return context


class AnswerRemove(LoginRequiredMixin, generic.DeleteView):
    model = Answer
    template_name = 'models/answer_remove.html'

    def get_success_url(self):
        return reverse_lazy('question-detail',
                            kwargs={'pk': self.object.question.pk})


class AnswerUpdate(LoginRequiredMixin, UpdateView):
    model = Answer
    fields = ['answer', 'correct']

    def get_success_url(self):
        return reverse_lazy('question-detail',
                            kwargs={'pk': self.object.question.pk})


class AnswerCreate(LoginRequiredMixin, CreateView):
    model = Answer
    fields = ['answer', 'correct']

    def form_valid(self, form):
        if form.is_valid():
            form.instance.questionid = self.kwargs['questionid']
            question = get_object_or_404(
                Question,
                pk=self.kwargs['questionid']
            )

            form.instance.question = question
        return super().form_valid(form)

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        question = get_object_or_404(
            Question,
            pk=self.kwargs['questionid']
        )
        context['question'] = question
        return context

    def get_success_url(self):
        return reverse_lazy('question-detail',
                            kwargs={'pk': self.object.question.pk})


class GameCreate(LoginRequiredMixin, CreateView):
    model = Game
    fields = ['countdownTime']

    def form_valid(self, form):
        form.instance.questionnaireid = self.kwargs['questionnaireid']
        questionnaire = get_object_or_404(
            Questionnaire,
            pk=self.kwargs['questionnaireid']
        )
        form.instance.questionnaire = questionnaire
        form.instance.publicId = random.randint(1, 1000000)
        form.instance.state = Game.GameState.WAITING
        form.instance.questionNo = len(Question.objects
                                       .filter(questionnaire=questionnaire))
        return super().form_valid(form)

    def get_success_url(self):
        return reverse_lazy('game-detail', kwargs={'pk': self.object.pk})


class GameDetail(LoginRequiredMixin, generic.DetailView):
    model = Game
    template_name = "models/game_detail.html"

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        gameid = self.kwargs['pk']
        participants = Participant.objects.filter(
            game=gameid)
        context['game'] = Game.objects.get(pk=gameid)
        context['participants'] = participants
        return context


# class GameUpdateParticipant(generic.DetailView):
#     model = Participant

#     def get_queryset(self):
#         return (
#             Participant.objects
#             .filter(game=get_object_or_404(
#                     Game, pk=self.request.session
#                     ))
#             .values('alias')
#         )

class GameUpdateParticipant(generic.DetailView):
    model = Participant
    template_name = "models/game_update_participant.html"

    def get(self, request, *args, **kwargs):
        publicId = kwargs.get('publicid')
        game = get_object_or_404(Game, publicId=publicId)
        participants = (
            Participant.objects
            .filter(game=game)
            .values('alias')
        )
        response = JsonResponse(list(participants), safe=False, content_type='application/json')
        print("Response", response)
        return response


class GameCountDown(generic.DetailView):
    model = Game

    list_template = ['models/game_countdown_question.html',
                     'models/game_countdown_answer.html',
                     'models/game_countdown_leaderboard.html']
    index = None

    def get_template_names(self):

        if ('countdownwaiting' in self.request.META.get('HTTP_REFERER')):
            template = "models/game_countdown_question.html"
        elif ('countdownquestion' in self.request.META.get('HTTP_REFERER')):
            template = "models/game_countdown_answer.html"
        elif ('countdownanswer' in self.request.META.get('HTTP_REFERER')):
            template = "models/game_countdown_leaderboard.html"
        elif ('countdownleaderboard' in self.request.META.get('HTTP_REFERER')):
            template = "models/game_countdown_question.html"
        else:
            template = "models/game_countdown_waiting.html"

        if self.object.questionNo == 1 and ('countdownleaderboard'
                                            in self.request.META
                                            .get('HTTP_REFERER')):
            template = "home_signed.html"

        return template

    def post(self, request, *args, **kwargs):
        # do something here to update some_condition
        return TemplateResponse(request, self.get_template_names())

    def get_context_data(self, **kwargs):

        context = super().get_context_data(**kwargs)
        gameid = self.kwargs['pk']
        participants = Participant.objects.filter(
            game=gameid)

        questions = Question.objects.order_by("question")
        question = questions[self.object.questionNo]
        self.object.questionNo -= 1

        context['game'] = Game.objects.get(pk=gameid)
        context['question'] = question
        context['answers'] = Answer.objects.filter(question=question)
        context['participants'] = participants
        return context
