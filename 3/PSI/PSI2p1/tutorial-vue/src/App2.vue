<script>
import TablaPersonas from "@/components/TablaPersonas.vue";
import FormularioPersona from "@/components/FormularioPersona.vue";
export default {
  name: "app",
  components: {
    TablaPersonas,
    FormularioPersona,
  },
  data() {
    return {
      procesando: false,
      editando: null,
      correcto: false,
      error: false,
      personas: [],
    };
  },
  methods: {
    async listadoPersonas() {
      try {
        const myVar = import.meta.env.VITE_DJANGOURL;
        const response = await fetch(myVar);
        this.personas = await response.json();
      } catch (error) {
        console.error(error);
      }
    },
    async agregarPersona(persona) {
      try {
        const myVar = import.meta.env.VITE_DJANGOURL;
        const response = await fetch(myVar, {
          method: 'POST',
          body: JSON.stringify(persona),
          headers: { 'Content-type': 'application/json; charset=UTF-8' },
        });
        const personaCreada = await response.json();
        this.personas = [...this.personas, personaCreada];
      } catch (error) {
        console.error(error);
      }
    },
    async eliminarPersona(persona_id) {
      try {
        const myVar = import.meta.env.VITE_DJANGOURL;
        await fetch(myVar + persona_id + '/', {
          method: "DELETE"
        });
        this.personas = this.personas.filter(u => u.id !== persona_id);
      } catch (error) {
        console.error(error);
      }
    },
    async actualizarPersona(id, personaActualizada) {
      try {
        const myVar = import.meta.env.VITE_DJANGOURL;
        const response = await fetch(myVar + personaActualizada.id + '/', {
          method: 'PUT',
          body: JSON.stringify(personaActualizada),
          headers: { 'Content-type': 'application/json; charset=UTF-8' },
        });
        const personaActualizadaJS = await response.json();
        this.personas = this.personas.map(u => (u.id === personaActualizada.id ? personaActualizadaJS : u));
      } catch (error) {
        console.error(error);
      }
    },
  },
  mounted() {
    this.listadoPersonas();
  },
};
</script>

<template>
  <div id="app" class="container">
    <div class="row">
      <div class="col-md-12">
        <h1>Personas</h1>
      </div>
    </div>
    <div class="row">
      <div class="col-md-12">
        <formulario-persona @add-persona="agregarPersona" />
        <tabla-personas :personas="personas" @delete-persona="eliminarPersona" @actualizar-persona="actualizarPersona" />
      </div>
    </div>
  </div>
</template>

<style>
button {
  background: #009435;
  border: 1px solid #009435;
}
</style>
