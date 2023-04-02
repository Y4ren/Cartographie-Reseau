#!/bin/bash

if ! sudo ./lbnf $1 $2; then 
    exit 1;
fi 

cd Web/
node server/utils/linksNodes.js ../nodeFile.json
npm run dev