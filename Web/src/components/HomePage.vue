<script setup>
import NavigationFilters from "./NavigationFilters.vue";
import ForceDirectedGraph from "./ForceDirectedGraph.vue";

defineProps({
	msg: String,
});

</script>

<template>
    <v-container class="pa-0" fluid>
        <navigation-filters></navigation-filters>
        <force-directed-graph></force-directed-graph>
    </v-container>

</template>
