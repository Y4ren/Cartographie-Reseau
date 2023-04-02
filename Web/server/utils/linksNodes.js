import fs from "fs";

if (process.argv.length < 3) {
  console.error("Usage: node script.js <file.json>");
  process.exit(1);
}

const filePath = process.argv[2];

const getNodes = (data) => {
  let nodesTab = [];
  let linksTab = [];

  for (const machine of data) {
    const copy = JSON.parse(JSON.stringify(machine));
    const node = {
      id: copy.MAC,
      group: "Cited Works",
      radius: 1,
      citing_patents_count: 1,
    };
    delete copy.protocols;

    let dest_count = 0;

    if (
      machine.protocols &&
      machine.protocols.length &&
      machine.protocols.filter((p) => p.destinations && p.destinations.length)
        .length
    ) {
      for (const proto of machine.protocols) {
        const protoCopy = JSON.parse(JSON.stringify(proto));
        dest_count += protoCopy.destinations.length;
        delete protoCopy.destinations;

        const toPush = proto.destinations.map((e) => ({
          source: node.id,
          target: e.MAC /*, proto : protoCopy*/,
          value: 2,
        }));
        linksTab.push(...toPush);
      }
    }

    node.radius = dest_count || 1;
    node.citing_patents_count = dest_count || 1;

    nodesTab.push(node);
  }

  console.log("- Nodes:\t " + nodesTab.length);
  console.log("- Links:\t " + linksTab.length);

  return { nodes: nodesTab, links: linksTab };
};

const saveFile = (jsonContent) => {
  //const filename = `../resources/output_${Date.now()}.json` //May not work on Windows
  const filename = "server/resources/output3.json"; //May not work on Windows
  fs.writeFile(filename, jsonContent, "utf8", function (err) {
    if (err) {
      console.log("An error occured while writing JSON Object to File.");
      return console.log(err);
    }

    console.log("JSON file has been saved as " + filename);
  });
};

fs.readFile(filePath, "utf8", (err, data) => {
  if (err) {
    console.error(`Error reading file: ${err}`);
    process.exit(1);
  }

  try {
    const obj = JSON.parse(data);
    const output = getNodes(obj);
    saveFile(JSON.stringify(output));
  } catch (e) {
    console.error(`Error parsing JSON: ${e}`);
    process.exit(1);
  }
});
