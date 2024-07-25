#!/usr/bin/env bash
MOD_NAXXRAMAS_LOGOUT_TELEPORT_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/" && pwd )"

source $MOD_NAXXRAMAS_LOGOUT_TELEPORT_ROOT"/conf/conf.sh.dist"

if [ -f $MOD_NAXXRAMAS_LOGOUT_TELEPORT_ROOT"/conf/conf.sh" ]; then
    source $MOD_NAXXRAMAS_LOGOUT_TELEPORT_ROOT"/conf/conf.sh"
fi
