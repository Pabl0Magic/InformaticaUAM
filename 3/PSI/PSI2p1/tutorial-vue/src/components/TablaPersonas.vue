<!-- src/components/TablaPersonas.vue -->
<template>
  <div id="tabla-personas">
    <div v-if="!personas.length" class="alert alert-info" role="alert">
      No se han agregado personas.
    </div>
    <table class="table">
      <thead>
        <tr>
          <th>Nombre</th>
          <th>Apellido</th>
          <th>Email</th>
          <th>Acciones</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="persona in personas" :key="persona.id">
          <td v-if="editando === persona.id">
            <input type="text" class="form-control" v-model="persona.nombre" />
          </td>
          <td v-else>
            {{ persona.nombre }}
          </td>
          <td v-if="editando === persona.id">
            <input
              type="text"
              class="form-control"
              v-model="persona.apellido"
            />
          </td>
          <td v-else>
            {{ persona.apellido }}
          </td>
          <td v-if="editando === persona.id">
            <input type="email" class="form-control" v-model="persona.email" />
          </td>
          <td v-else>
            {{ persona.email }}
          </td>
          <td v-if="editando === persona.id">
            <button class="btn btn-success" @click="guardarPersona(persona)">
              &#x1F5AB; Guardar.
            </button>
            <button
              class="btn btn-secondary ml-2"
              @click="cancelarEdicion(persona)"
            >
              &#x1F5D9; Cancelar.
            </button>
          </td>
          <td v-else>
            <button
              class="btn btn-danger ml-2"
              @click="$emit('delete-persona', persona.id)"
            >
              &#x1F5D1; Eliminar
            </button>
            <button class="btn btn-info" @click="editarPersona(persona)">
              &#x1F58A; Editar
            </button>
          </td>
        </tr>
      </tbody>
    </table>
  </div>
</template>
<script>
export default {
  name: "tabla-personas",
  data() {
    return {
      editando: null,
    }
  },
  props: {
    personas: Array,
  },
  methods: {
    guardarPersona(persona) {
      if (!persona.nombre.length || !persona.apellido.length || !persona.email.length) {
        return;
      }
      this.$emit("actualizar-persona", persona.id, persona);
      this.editando = null;
    },
    cancelarEdicion(persona) {
      Object.assign(persona, this.personaEditada);
      this.editando = null;
    },
    editarPersona(persona) {
      this.personaEditada = Object.assign({}, persona);
      this.editando = persona.id;
    },
  },
};
</script>
<style scoped></style>