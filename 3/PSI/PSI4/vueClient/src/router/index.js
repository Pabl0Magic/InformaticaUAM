import { createRouter, createWebHistory } from 'vue-router'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'participant-form',
      component: () => import('../components/ParticipantForm.vue')
    },

    {
      path: '/game',
      name: 'game',
      component: () => import('../components/Game.vue')
    },
    {
      path: '/guess',
      name: 'guess',
      component: () => import('../components/Guess.vue')
    }
  ]
})

export default router
