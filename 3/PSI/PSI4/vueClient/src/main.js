import { createApp } from 'vue'
// import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'

import './assets/main.css'

const app = createApp(App)

app.use(router)

app.use(store)

app.mount('#app')


// new Vue({
//     router,
//     store,
//     render: h => h(App)
//   }).$mount('#app')