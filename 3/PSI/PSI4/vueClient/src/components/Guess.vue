<template>
    <div class="main-div">
        <div>
            <button class="button" v-for="(answer, index) in answerButtons" 
            :key="index" :style="{ backgroundColor: colors[index] }" @click.prevent="submitGuess(index)">
            </button>
        </div>
        <div v-if="clicked" class="alert alert-success" role="alert">
        You have answered!
        </div>
        <div v-if="procesando" class="alert alert-neutral" role="alert">
        Wait for the question...
        </div>
        <div v-if="errorAnswer" class="alert alert-danger" role="alert">
        The answer you clicked does not exist
        </div>
    </div> 
</template>

<script>
export default {
    name: "guess",

    data() {
        return {
        answerButtons: ['bOne', 'bTwo', 'bThree', 'bFour'],
        colors: ["lightcoral", "lightblue", "lightgreen", "violet"],
        procesando: false,
        clicked: false,
        errorAnswer: null,
        selected: null
        }
    },

    methods: {
        async submitGuess(index) {
            // Avoid clicking more than once
            if (this.procesando === true){
                console.log("Unable to click in a page different to question")
                return
            }
            if (this.clicked === true) {
                console.log("You have already answered")
                return
            }
            this.procesando = true
            this.clicked = true
            this.selected = index
            console.log(this.$store.state)
            const myVar = import.meta.env.VITE_DJANGOURL_GUESS
            console.log("Index:", index)

            const response = await fetch(myVar, {
            method: 'POST',
            body: JSON.stringify({
                'uuidp': this.$store.state.participant.id.toString(),
                'gameId': this.$store.state.game.publicId.toString(),
                'noAnswer': index,
            }),
            headers: {
                'Content-type': 'application/json; charset=UTF-8',
            }
            });

            // Checking error with less than 4 possible answers
            if (response.status === 409){
                this.errorAnswer = true
            }
            console.log(response)

            this.procesando = false
            this.errorAnswer = false
        
        },
        
        async checkGameState() {
            const v = this.$store.state.game.publicId.toString()
            const myVar = import.meta.env.VITE_DJANGOURL_GAME;
            const response = await fetch(myVar+v+'/');
            const data = await response.json()
            console.log("Response", data)
            const gameState = data.state;
            if (gameState !== 2) {
                this.procesando = true
                this.clicked = false
            } else if (this.clicked === false) {
                this.procesando = false
            }
        }
    },
    mounted() {
    this.intervalId = setInterval(() => {
      this.checkGameState();
    }, 1000)
  },

}
</script>

<style>
.button {
  color: white;
  padding: 10px;
  border-radius: 5px;
  border: none;
  margin: 5px;
  height: 10vh;
  width: 10vh;
}

.main-div {
    align-items: center;
}
</style>
