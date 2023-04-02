<template>
    <v-navigation-drawer
            expand-on-hover
            rail
            @update:rail="handleUpdateRail($event)"
    >
        <v-list>
            <v-list-item
                    prepend-icon="mdi-filter"
                    title="Filtres"
            >
            </v-list-item>
        </v-list>

        <v-divider></v-divider>
        <template v-slot:append>
            <v-divider></v-divider>

            <div v-if="rail" class="pa-2">
                <v-list>
                    <v-list-item
                            title="NOM Prénom"
                    >
                    </v-list-item>
                    <v-list-item
                            title="NOM Prénom"
                    >
                    </v-list-item>
                    <v-list-item
                            title="NOM Prénom"
                    >
                    </v-list-item>
                    <v-list-item
                            title="NOM Prénom"
                    >
                    </v-list-item>
                </v-list>
            </div>
        </template>

    </v-navigation-drawer>

</template>

<script>
export default {
	name: "NavigationFilters",
	data: () => ({
		rail: false,
	}),
	methods: {
		handleUpdateRail(ev) {
			this.rail = !ev;
		}
	}
};
</script>

<style scoped>

</style>