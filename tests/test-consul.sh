#!/bin/bash
# Run test consul. usage: test-consul.sh start|stop

case "$1" in
start)
    consul info >/dev/null
    if [ $? -eq 0 ]; then
        echo "Consul is already running"
        exit 1
    fi

    DATA_DIR=test-consul-data
    rm -rf $DATA_DIR
    consul agent -bootstrap-expect=1 -server -dc=ppconsul_test "-data-dir=$DATA_DIR" >/dev/null &
    sleep 3s
    consul info >/dev/null
    if [ $? -ne 0 ]; then
        echo "Failed to start consul"
        exit 1
    else
        echo "Consul started successfully"
    fi
    ;;
stop)
    consul info >/dev/null
    if [ $? -ne 0 ]; then
        echo "Consul is not running"
        exit 0
    fi
    consul leave || exit 1
    ;;
*)
    echo "Usage: test-consul.sh start|stop"
    exit 2
    ;;
esac