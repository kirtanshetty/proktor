#!/bin/bash

DEPS_DIR="deps"

download_nlohmanjson(){
  SHASUM="sha256sum";

  # for mac users
  if [ $(uname) == "Darwin" ]; then
    SHASUM="shasum -a 256 ";
  fi

  NLOHMAN_JSON_PATH=$DEPS_DIR/json
  NLOHMAN_JSON_HEADER_FILE=$NLOHMAN_JSON_PATH/json.hpp
  NLOHMAN_JSON_HEADER_FILE_SHASUM=d2eeb25d2e95bffeb08ebb7704cdffd2e8fca7113eba9a0b38d60a5c391ea09a
  NLOHMAN_JSON_HEADER_URL="https://github.com/nlohmann/json/releases/download/v3.6.1/json.hpp"

  mkdir -p $NLOHMAN_JSON_PATH
  DOWNLOAD_FILE=false;
  if [ ! -f $NLOHMAN_JSON_HEADER_FILE ]; then
    DOWNLOAD_FILE=true;
    echo "nlohmann json file not found.";
  elif [ "$($SHASUM $NLOHMAN_JSON_HEADER_FILE | awk '{print $1}')" != $NLOHMAN_JSON_HEADER_FILE_SHASUM ]; then
    DOWNLOAD_FILE=true;
    echo "new version of nlohmann json file found.";
  fi

  if [ $DOWNLOAD_FILE == "true" ] ; then
    echo "downloading...";
    curl -L $NLOHMAN_JSON_HEADER_URL > $NLOHMAN_JSON_HEADER_FILE
  else
    echo "nlohmann json file already present.";
  fi

}

init(){
  download_nlohmanjson;
}

init