import { createStore } from 'vuex'

export default createStore({
    state: {
        participant: null,
        game: null
      },
    mutations: {
        setGame(state, payload) {
            state.game = payload;
        },
        setParticipant(state, payload){
            state.participant = payload
        }
    },
    actions: {
    
    },
    getters: {
    
    }
})