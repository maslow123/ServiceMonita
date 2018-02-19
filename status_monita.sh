#!/bin/bash
status=$(sudo service monita-service status | grep "Running, the PID is");
if [[ -z "${status}" ]]; then
  echo 0;
  sudo service monita-service restart
else
  echo 1;
fi
#echo $status;
