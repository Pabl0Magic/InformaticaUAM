import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      component: HomeView
    },
    {
      path: '/page-one',
      name: 'pageone',
      component: () => import('../components/PageOne.vue')
    },
    {
      path: '/page-two',
      name: 'pagetwo',
      component: () => import('../components/PageTwo.vue')
    },
  ]
})
export default router
