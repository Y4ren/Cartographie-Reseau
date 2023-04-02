<template>
	<v-container fluid style="height: 100vh;">
		<div id="svg-wrapper" style="height: 100%;">
			<svg id="svg" ref="svg"></svg>
		</div>
	</v-container>
</template>

<script>
import * as d3 from "d3";
import { nodes, links } from "../../server/resources/output3.json";

export default {
	name: "ForceDirectedGraph",
	data() {
		return {
			svg: undefined
		};
	},
	mounted() {
		this.svg = this.forceGraph({ nodes, links }, {});
		console.log(this.svg);
		svg.appendChild(this.svg);

	},
	methods: {
		// Copyright 2021 Observable, Inc.
		// Released under the ISC license.
		// https://observablehq.com/@d3/disjoint-force-directed-graph
		forceGraph({
			nodes, // an iterable of node objects (typically [{id}, …])
			links // an iterable of link objects (typically [{source, target}, …])
		}, {
			nodeId = d => d.id, // given d in nodes, returns a unique identifier (string)
			nodeGroup, // given d in nodes, returns an (ordinal) value for color
			nodeGroups, // an array of ordinal values representing the node groups
			nodeTitle, // given d in nodes, a title string
			nodeFill = "red", // node stroke fill (if not using a group color encoding)
			nodeStroke = "#fff", // node stroke color
			nodeStrokeWidth = 1.5, // node stroke width, in pixels
			nodeStrokeOpacity = 1, // node stroke opacity
			nodeRadius = 8, // node radius, in pixels
			nodeStrength,
			linkSource = ({ source }) => source, // given d in links, returns a node identifier string
			linkTarget = ({ target }) => target, // given d in links, returns a node identifier string
			linkStroke = "#999", // link stroke color
			linkStrokeOpacity = 0.6, // link stroke opacity
			linkStrokeWidth = 1.5, // given d in links, returns a stroke width in pixels
			linkStrokeLinecap = "round", // link stroke linecap
			linkStrength,
			colors = ["red", "blue"], // an array of color strings, for the node groups
			width = document.getElementById("svg-wrapper").offsetWidth, // outer width, in pixels
			height = document.getElementById("svg-wrapper").offsetHeight, // outer height, in pixels
			invalidation // when this promise resolves, stop the simulation
		} = {}) {
			// Compute values.
			//console.log(links)
			const N = d3.map(nodes, nodeId).map(intern);
			const LS = d3.map(links, linkSource).map(intern);
			const LT = d3.map(links, linkTarget).map(intern);

			// console.log('linkSource',linkSource)
			// console.log('linkTarget',linkTarget)
			//console.log('LS',LS)
			//console.log('LT',LT)
			if (nodeTitle === undefined) nodeTitle = (_, i) => N[i];
			const T = nodeTitle == null ? null : d3.map(nodes, nodeTitle);
			const G = nodeGroup == null ? null : d3.map(nodes, nodeGroup).map(intern);
			const W = typeof linkStrokeWidth !== "function" ? null : d3.map(links, linkStrokeWidth);

			// Replace the input nodes and links with mutable objects for the simulation.
			nodes = d3.map(nodes, (_, i) => ({ id: N[i] }));
			links = d3.map(links, (_, i) => ({ source: LS[i], target: LT[i] }));

			console.log(links);
			// Compute default domains.
			if (G && nodeGroups === undefined) nodeGroups = d3.sort(G);

			// Construct the scales.
			const color = nodeGroup == null ? null : d3.scaleOrdinal(nodeGroups, colors);

			// Construct the forces.
			const forceNode = d3.forceManyBody();
			const forceCollide = d3.forceCollide(3).strength(1).iterations(1);
			const forceLink = d3.forceLink(links).id(({ index: i }) => N[i]);
			if (nodeStrength !== undefined) forceNode.strength(nodeStrength);
			if (linkStrength !== undefined) forceLink.strength(linkStrength);

			const simulation = d3.forceSimulation(nodes)
				.force("link", forceLink)
				.force("charge", forceNode)
				//.force("collide", forceCollide)
				.force("x", d3.forceX())
				.force("y", d3.forceY())
				//.force("center",  d3.forceCenter())

				//.force("x", d3.forceX().strength(0.03))
				//.force("y", d3.forceY().strength(0.07))
				.on("tick", ticked);

			const svg = d3.select("#svg")
				.attr("width", width)
				.attr("height", height)
				.attr("viewBox", [-width / 2, -height / 2, width, height])
				.attr("style", "max-width: 100%; height: auto; height: intrinsic;");

			//console.log(svg)

			const link = svg.append("g")
				.attr("stroke", linkStroke)
				.attr("stroke-opacity", linkStrokeOpacity)
				.attr("stroke-width", typeof linkStrokeWidth !== "function" ? linkStrokeWidth : null)
				.attr("stroke-linecap", linkStrokeLinecap)
				.selectAll("line")
				.data(links)
				.join("line");

			if (W) link.attr("stroke-width", ({ index: i }) => W[i]);

			const node = svg.append("g")
				.attr("fill", nodeFill)
				.attr("stroke", nodeStroke)
				.attr("stroke-opacity", nodeStrokeOpacity)
				.attr("stroke-width", nodeStrokeWidth)
				.selectAll("circle")
				.data(nodes)
				.join("circle") // <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 576 512"><!--! Font Awesome Pro 6.3.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. --><path d="M64 0C28.7 0 0 28.7 0 64V352c0 35.3 28.7 64 64 64H240l-10.7 32H160c-17.7 0-32 14.3-32 32s14.3 32 32 32H416c17.7 0 32-14.3 32-32s-14.3-32-32-32H346.7L336 416H512c35.3 0 64-28.7 64-64V64c0-35.3-28.7-64-64-64H64zM512 64V288H64V64H512z"/></svg>
				.attr("r", nodeRadius)
				.call(drag(simulation));

			if (G) node.attr("fill", ({ index: i }) => color(G[i]));
			if (T) node.append("title").text(({ index: i }) => T[i]);

			// Handle invalidation.
			if (invalidation != null) invalidation.then(() => simulation.stop());

			function intern(value) {
				console.log(value);
				return value !== null && typeof value === "object" ? value.valueOf() : value;
			}

			function ticked() {
				link
					.attr("x1", d => d.source.x)
					.attr("y1", d => d.source.y)
					.attr("x2", d => d.target.x)
					.attr("y2", d => d.target.y);

				node
					.attr("cx", d => d.x)
					.attr("cy", d => d.y);
			}

			function drag(simulation) {
				function dragstarted(event) {
					if (!event.active) simulation.alphaTarget(0.3).restart();
					event.subject.fx = event.subject.x;
					event.subject.fy = event.subject.y;
				}

				function dragged(event) {
					event.subject.fx = event.x;
					event.subject.fy = event.y;
				}

				function dragended(event) {
					if (!event.active) simulation.alphaTarget(0);
					event.subject.fx = null;
					event.subject.fy = null;
				}

				return d3.drag()
					.on("start", dragstarted)
					.on("drag", dragged)
					.on("end", dragended);
			}

			return Object.assign(svg.node(), { scales: { color } });
		}
	}
};
</script>

<style scoped></style>