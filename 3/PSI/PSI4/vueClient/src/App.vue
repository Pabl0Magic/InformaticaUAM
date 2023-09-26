<script>
import ParticipantForm from "@/components/ParticipantForm.vue";
import axios from 'axios';
export default {
  name: "app",
  components: {
    ParticipantForm,
  },
  data() {
    return {
      participant: null,
    };
  },
  methods: {
    // async agregarParticipant(participant) {
    //   try {
    //     const myVar = import.meta.env.VITE_DJANGOURL;
    //     // axios
    //     //   .get(myVar)
    //     //   .then(response => (this.info = response))
    //     const response = await fetch(myVar, {
    //       method: 'POST',
    //       body: JSON.stringify(participant),
    //       headers: {
    //         'Content-type': 'application/json; charset=UTF-8',
    //       },
    //     });
    //     const participantCreado = await response.json();
    //     this.participant = participantCreado;
    //     this.$store.commit('setGameid', participant.game);
    //     this.$store.commit('setAlias', participant.alias);
    //     this.$router.push('/game');
    //     //router.push
    //   } catch (error) {
    //     console.error(error);
    //   }
    // },
    // mounted(){
    //   this
    // }
  },
};
</script>

<template>
  <div id="app" class="container">
    <!-- <participant-form @add-participant="agregarParticipant"/> -->
    <router-view></router-view>
  </div>
</template>

  