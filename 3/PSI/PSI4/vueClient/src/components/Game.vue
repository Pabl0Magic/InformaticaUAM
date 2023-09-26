<template>
  <div id="gamepage">
    <h2>Thanks for joining the game with PIN:</h2>
    <h2>{{ game.publicId }}</h2>
    <h2>The game will start soon.</h2>
    <p>state: {{ game.state }}</p>
    <div 
      v-if="game.state === 1"
      v-on:input="startGame">
    </div>
  </div>
</template>

<script>
export default {
  name: "game",
  
  computed:{
    game() {
      return this.$store.state.game
    }
  },
  
  methods: {
    async checkGameState() {
      const v = this.game.publicId.toString()
      const myVar = import.meta.env.VITE_DJANGOURL_GAME;
      const response = await fetch(myVar+v+'/');
      const data = await response.json()
      console.log("Response", data)
      const gameState = data.state;
      if (gameState === 2) {
        //clearInterval(this.intervalId);
        this.$router.push('/guess');
      }
    },
  },

  mounted() {
    this.intervalId = setInterval(() => {
      this.checkGameState();
    }, 2000)
  },
}
</script>