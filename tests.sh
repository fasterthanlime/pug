#!/bin/bash

ROOT="$( cd "$( dirname "$0" )" && pwd )"

for sample in ${ROOT}/samples/*.pg; do
  echo ">>> ${sample}"
  ${ROOT}/build/pug ${sample}
done

