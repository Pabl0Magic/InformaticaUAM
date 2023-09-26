<template>
  <div id="participant-form">
    <h2>Join Kahoot Game</h2>
    <form @submit.prevent="agregarParticipant">
      <div class="container">
        <label>Alias</label>
        <input 
          ref="alias"
          type="text"
          v-model="participant.alias"
          :class="{ 'is-invalid': procesando && aliasInvalido }"
          @focus="resetEstado"
        />
        <label>Game</label>
        <input
          ref="game"
          type="number"
          v-model.number="participant.game"
          :class="{ 'is-invalid': procesando && gameInvalido }"
          @focus="resetEstado"
          />
        <button class="button">Submit</button>
      </div>
      <div
        v-if="error && procesando"
        class="alert alert-danger"
        role="alert"
      >
        Debes rellenar todos los campos!
      </div>
      <div v-if="correcto" class="alert alert-success" role="alert">
        El participante ha sido agregado correctamente!
      </div>
      <div v-if="errorAlias && procesando" class="alert alert-success" role="alert">
        El alias ya existe
      </div>
      <div v-if="errorGame && procesando" class="alert alert-success" role="alert">
        El Game no existe
      </div>
    </form>
  </div>

</template>

<script>
export default {
  name: "participant-form",
  data() {
    return {
      procesando: false,
      correcto: false,
      error: false,
      errorAlias: false,
      errorGame: false,
      participant: {
        alias: null,
        game: null,
      }
    }
  },

  methods: {
    resetEstado() {
      this.correcto = false;
      this.error = false;
      this.errorAlias = false;
      this.errorGame = false;
    },
    async agregarParticipant(participant) {
      try {
        this.procesando = true,
        this.resetEstado();
        if (this.aliasInvalido || this.gameInvalido){
          this.error = true;
          return;
        }
        const myVar = import.meta.env.VITE_DJANGOURL;
        const response = await fetch(myVar, {
          method: 'POST',
          body: JSON.stringify(this.participant),
          headers: {
            'Content-type': 'application/json; charset=UTF-8',
          }
        });

        // Managing errors of data inserted
        if (response.status === 403){
          this.errorAlias = true;
          console.error("Error 403");
          return
        }
        else if (response.status === 404){
          this.errorGame = true;
          console.error("Error 404");
          return
        }

        console.log(response)

        this.$refs.alias.focus();
        this.error = false;
        this.correcto = true;
        this.procesando = false;
        this.errorAlias = false;
        this.errorGame = false;

        // Aqui es donde obtenemos el uidp
        const participantCreado = await response.json();
        console.log("Participant:", participantCreado)
        console.log("Id participant:", participantCreado.id)
        this.participant = participantCreado;
        this.$store.commit('setGame', this.participant.game);
        this.$store.commit('setParticipant', this.participant);

        this.participant = {
          alias: null,
          game: null
        }
        this.$router.push('/game');
      } catch (error) {
        console.error(error);
      }
    },
  },

  computed:{
    aliasInvalido(){
      return this.participant.alias.length < 1;
    },
    gameInvalido(){
      return this.participant.game.length < 1;
    }
  }
  
}
</script>
