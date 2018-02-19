#!/bin/bash
status=$(sudo service monita-service status | grep "Running, the PID is");
if [[ -z "${status}" ]]; then
  echo 0;
else
  echo 1;
fi
#echo $status;
